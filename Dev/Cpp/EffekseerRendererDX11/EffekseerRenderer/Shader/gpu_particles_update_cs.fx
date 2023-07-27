#include "gpu_particles_common.h"

cbuffer cb0 : register(b0)
{
    Constants constants;
};
cbuffer cb1 : register(b1)
{
    ParameterSet paramSet;
}
cbuffer cb2 : register(b2)
{
    Emitter emitter;
}

RWStructuredBuffer<Particle> Particles : register(u0);
RWStructuredBuffer<Trail> Trails : register(u1);
Texture3D<float4> NoiseVFTex : register(t4);
SamplerState NoiseVFSamp : register(s4);

float3 Vortex(float rotation, float attraction, float3 center, float3 axis, float3 position, float3x4 transform) {
    
    center = transform._m03_m13_m23 + center;
    axis = normalize(mul(transform, float4(axis, 0.0f)));

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
        float deltaTime = constants.DeltaTime;

        // Randomize parameters
        uint paramSeed = particle.Seed;
        float lifeTime = RandomFloatRange(paramSeed, paramSet.LifeTime);
        float lifeRatio = particle.LifeAge / lifeTime;
        float damping = RandomFloatRange(paramSeed, paramSet.Damping) * 0.01;
        float4 initialAngleScale = RandomFloat4Range(paramSeed, paramSet.InitialAngleScale);
        float4 targetAngleScale = RandomFloat4Range(paramSeed, paramSet.TargetAngleScale);
        float3 initialAngle = initialAngleScale.xyz;
        float3 angularVelocity = targetAngleScale.xyz;
        float initialScale = initialAngleScale.w;
        float terminalScale = targetAngleScale.w;
        float4 colorStart = RandomColorRange(paramSeed, paramSet.ColorStart);
        float4 colorEnd = RandomColorRange(paramSeed, paramSet.ColorEnd);

        float3 position = particle.Transform._m03_m13_m23;
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
        particle.LifeAge += constants.DeltaTime;
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
        position += velocity * constants.DeltaTime;

        // Rotation
        float3 rotation = initialAngle + angularVelocity * particle.LifeAge;
        
        // Scale
        float scale = lerp(initialScale, terminalScale, lifeRatio) * paramSet.ShapeSize;

        // Color
        float4 color = lerp(colorStart, colorEnd, lifeRatio);
        // Apply inheritation color
        if (paramSet.ColorFlags == 2 || paramSet.ColorFlags == 3) {
            color *= UnpackColor(emitter.Color);
        } else {
            color *= UnpackColor(particle.InheritColor);
        }
        // Fade-in/out
        color.a *= clamp(particle.LifeAge / paramSet.FadeIn, 0.0, 1.0);
        color.a *= clamp((lifeTime - particle.LifeAge) / paramSet.FadeOut, 0.0, 1.0);

        particle.Transform = TRSMatrix(position, rotation, float3(scale, scale, scale));
        particle.Velocity = PackFloat4(velocity, 0.0f);
        particle.Color = PackColor(color);
        Particles[particleID] = particle;
    }
}
