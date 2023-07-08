#include "gpupt_common.h"

cbuffer cb : register(b0)
{
    Constants constants;
};
cbuffer cb1 : register(b1)
{
    uint ParticleHead;
    uint TrailHead;
    uint TrailJoints;
    uint TrailPhase;
}

StructuredBuffer<ParameterSet> ParamSets : register(t0);
StructuredBuffer<DynamicInput> DynamicInputs : register(t1);
StructuredBuffer<Emitter> Emitters : register(t2);
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
    uint particleID = ParticleHead + dtid.x;
    Particle particle = Particles[particleID];
    
    if (particle.FlagBits & 0x01) {
        uint paramID = (particle.FlagBits >> 1) & 0x3FF;
        uint emitterID = (particle.FlagBits >> 11) & 0x3FF;
        uint updateCount = (particle.FlagBits >> 21) & 0xFF;
        ParameterSet paramSet = ParamSets[paramID];
        DynamicInput input = DynamicInputs[emitterID];
        float deltaTime = constants.DeltaTime;

        // Randomize parameters
        uint paramSeed = particle.Seed;
        float lifeTime = (float)RandomUintRange(paramSeed, paramSet.LifeTime);
        float lifeRatio = particle.LifeAge / lifeTime;
        float damping = RandomFloatRange(paramSeed, paramSet.Damping) * 0.01;
        float3 initialAngle = RandomFloat3Range(paramSeed, paramSet.InitialAngle);
        float3 angularVelocity = RandomFloat3Range(paramSeed, paramSet.AngularVelocity);
        float initialScale = RandomFloatRange(paramSeed, paramSet.InitialScale);
        float terminalScale = RandomFloatRange(paramSeed, paramSet.TerminalScale);
        float4 colorStart = RandomColorRange(paramSeed, paramSet.ColorStart);
        float4 colorEnd = RandomColorRange(paramSeed, paramSet.ColorEnd);

        float3 position = particle.Transform._m03_m13_m23;
        float3 velocity = UnpackFloat4(particle.Velocity).xyz;

        if (TrailJoints > 0) {
            uint trailID = TrailHead + dtid.x * TrailJoints + TrailPhase;
            Trail trail;
            trail.Position = position;
            trail.Direction = PackNormalizedFloat3(velocity);
            Trails[trailID] = trail;
        }
        
        // Increase count
        particle.FlagBits &= ~(0xFF << 21);
        particle.FlagBits |= clamp(updateCount + 1, 0, 255) << 21;

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
                position, input.Transform) * deltaTime;
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
            color *= input.Color;
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
