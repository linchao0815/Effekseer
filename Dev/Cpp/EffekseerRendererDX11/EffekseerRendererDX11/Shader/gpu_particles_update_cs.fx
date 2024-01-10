#include "gpu_particles_common.h"

cbuffer cb0 : register(b0)
{
    ParameterSet paramSet;
}
cbuffer cb1 : register(b1)
{
    Emitter emitter;
}

RWStructuredBuffer<Particle> Particles : register(u0);
RWStructuredBuffer<Trail> Trails : register(u1);
Texture3D<float4> NoiseVFTex : register(t2);
SamplerState NoiseVFSamp : register(s2);

float3 Vortex(float rotation, float attraction, float3 center, float3 axis, float3 position, float4x3 transform) {
    
    center = transform[3] + center;
    axis = normalize(mul(float4(axis, 0.0f), transform));

    float3 diff = position - center;
    float distance = length(diff);
    if (distance == 0.0f) {
        return float3(0.0f, 0.0f, 0.0f);
    }

    float3 radial = diff / distance;
    float3 tangent = cross(axis, radial);
    radial = cross(tangent, axis);
    return tangent * rotation - radial * attraction;
}

[numthreads(256, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint particleID = emitter.ParticleHead + dtid.x;
    Particle particle = Particles[particleID];
    
    if (particle.FlagBits & 0x01) {
        uint updateCount = (particle.FlagBits >> 1) & 0xFF;
        float deltaTime = emitter.DeltaTime;

        // Randomize parameters
        uint seed = particle.Seed;
        float lifeTime = RandomFloatRange(seed, paramSet.LifeTime);
        float lifeRatio = particle.LifeAge / lifeTime;
        float damping = RandomFloatRange(seed, paramSet.Damping) * 0.01;
        float4 initialAngle = RandomFloat4Range(seed, paramSet.InitialAngle);
        float4 angularVelocity = RandomFloat4Range(seed, paramSet.TargetAngle);

        float3 position = particle.Transform[3];
        float3 velocity = UnpackFloat4(particle.Velocity).xyz;

        if (emitter.TrailSize > 0) {
            uint trailID = emitter.TrailHead + dtid.x * paramSet.ShapeData + emitter.TrailPhase;
            Trail trail;
            trail.Position = position;
            trail.Direction = PackNormalizedFloat3(velocity);
            Trails[trailID] = trail;
        }
        
        // Increase count
        particle.FlagBits &= ~(0xFF << 1);
        particle.FlagBits |= clamp(updateCount + 1, 0, 255) << 1;

        // Aging
        particle.LifeAge += deltaTime;
        if (particle.LifeAge >= lifeTime) {
            // Clear the alive flag
            particle.FlagBits &= ~1;
        }
        
        // Gravity
        velocity += paramSet.Gravity * deltaTime;
        
        // Vortex
        if (paramSet.VortexRotation != 0.0f || paramSet.VortexAttraction != 0.0f) {
            velocity += Vortex(paramSet.VortexRotation, paramSet.VortexAttraction, 
                paramSet.VortexCenter, paramSet.VortexAxis,
                position, emitter.Transform) * deltaTime;
        }
        // Turbulence
        if (paramSet.TurbulencePower != 0.0f) {
            float4 vfTexel = NoiseVFTex.SampleLevel(NoiseVFSamp, position / 8.0f + 0.5f, 0);
            velocity += (vfTexel.xyz * 2.0f - 1.0f) * paramSet.TurbulencePower * deltaTime;
        }

        // Damping
        float speed = length(velocity);
        if (speed > 0.0f) {
            float newSpeed = max(0.0f, speed - damping * deltaTime);
            velocity *= newSpeed / speed;
        }

        // Move from velocity
        position += velocity * deltaTime;

        // Rotation (Euler)
        float3 rotation = initialAngle.xyz + angularVelocity.xyz * particle.LifeAge;
        
        // Scale (XYZ+Single)
        float4 scale = float4(1.0f, 1.0f, 1.0f, 1.0f);
        uint scaleMode = paramSet.ScaleFlags & 0x07;
        if (scaleMode == 0) {
            scale = RandomFloat4Range(seed, paramSet.ScaleData1);
        } else if (scaleMode == 2) {
            float4 scale1 = RandomFloat4Range(seed, paramSet.ScaleData1);
            float4 scale2 = RandomFloat4Range(seed, paramSet.ScaleData2);
            scale = lerp(scale1, scale2, EasingSpeed(lifeRatio, paramSet.ScaleEasing));
        }

        // Color
        uint colorMode = paramSet.ColorFlags & 0x07;
        float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
        if (colorMode == 0) {
            color = paramSet.ColorData.x;
        } else if (colorMode == 1) {
            color = RandomColorRange(seed, paramSet.ColorData.xy);
        } else if (colorMode == 2) {
            float4 colorStart = RandomColorRange(seed, paramSet.ColorData.xy);
            float4 colorEnd = RandomColorRange(seed, paramSet.ColorData.zw);
            color = lerp(colorStart, colorEnd, EasingSpeed(lifeRatio, paramSet.ColorEasing));
        }
        
        // HSV
        if ((paramSet.ColorFlags >> 5) & 0x01) {
            color.rgb = HSV2RGB(color.rgb);
        }

        // Apply inheritation color
        uint colorInherit = (paramSet.ColorFlags >> 3) & 0x03;
        if (colorInherit == 2 || colorInherit == 3) {
            color *= UnpackColor(emitter.Color);
        } else {
            color *= UnpackColor(particle.InheritColor);
        }

        // Fade-in/out
        color.a *= clamp(particle.LifeAge / paramSet.FadeIn, 0.0, 1.0);
        color.a *= clamp((lifeTime - particle.LifeAge) / paramSet.FadeOut, 0.0, 1.0);

        particle.Transform = TRSMatrix(position, rotation, scale.xyz * scale.w * paramSet.ShapeSize);
        particle.Velocity = PackFloat4(velocity, 0.0f);
        particle.Color = PackColor(color);
        Particles[particleID] = particle;
    }
}
