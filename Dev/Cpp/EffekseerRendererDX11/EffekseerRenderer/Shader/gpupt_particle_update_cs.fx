#include "gpupt_common.h"

cbuffer cb : register(b0)
{
    Constants constants;
};
cbuffer cb1 : register(b1)
{
    uint bufferOffset;
}

StructuredBuffer<ParameterSet> ParamSets : register(t0);
StructuredBuffer<DynamicInput> DynamicInputs : register(t1);
RWStructuredBuffer<Particle> Particles : register(u0);
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
    uint particleID = bufferOffset + dtid.x + dtid.y * 256;
    Particle particle = Particles[particleID];
    
    if (particle.flagBits & 0x01) {
        uint paramID = (particle.flagBits >> 1) & 0x3F;
        uint emitterID = (particle.flagBits >> 11) & 0x3F;
        ParameterSet paramSet = ParamSets[paramID];
        DynamicInput input = DynamicInputs[emitterID];

        float deltaTime = constants.DeltaTime;
        uint paramSeed = particle.seed;
        float lifeTime = (float)randomUintRange(paramSeed, paramSet.LifeTime);
        float damping = randomFloatRange(paramSeed, paramSet.Damping) * 0.01;
        float3 angularVelocity = randomFloat3Range(paramSeed, paramSet.AngularVelocity);
        float initialScale = randomFloatRange(paramSeed, paramSet.InitialScale);
        float terminalScale = randomFloatRange(paramSeed, paramSet.TerminalScale);

        float3 position = particle.position;
        float3 velocity = unpackFloat4(particle.velocity).xyz;
        float4 rotscale = unpackFloat4(particle.rotscale);
        float3 rotation = rotscale.xyz;
        float scale = rotscale.w;
        //float4 color = unpackColor(particle.color);

        particle.lifeAge += constants.DeltaTime;
        if (particle.lifeAge >= lifeTime) {
            particle.flagBits &= ~1;
        }
        
        // Gravity
        velocity += paramSet.Gravity * deltaTime;
        
        // Vortex
        if (paramSet.VortexRotation != 0.0f || paramSet.VortexAttraction != 0.0f) {
            velocity += Vortex(paramSet.VortexRotation, paramSet.VortexAttraction, 
                paramSet.VortexCenter, paramSet.VortexAxis,
                position, input.transform) * deltaTime;
        }
        if (paramSet.TurbulencePower != 0.0f) {
            float4 vfTexel = NoiseVFTex.SampleLevel(NoiseVFSamp, position / 8.0f + 0.5f, 0);
            velocity += (vfTexel.xyz * 2.0f - 1.0f) * paramSet.TurbulencePower * deltaTime;
        }

        float speed = length(velocity);
        if (speed > 0.0f) {
            float newSpeed = max(0.0f, speed - damping * deltaTime);
            velocity *= newSpeed / speed;
        }
        position += velocity * constants.DeltaTime;

        // Rotation
        rotation += angularVelocity * constants.DeltaTime;
        
        // Scale
        scale = lerp(initialScale, terminalScale, particle.lifeAge / lifeTime);

        particle.position = position;
        particle.velocity = packFloat4(velocity, 0.0f);
        particle.rotscale = packFloat4(rotation, scale);
        //particle.color = packColor(color);
        Particles[particleID] = particle;
    }
}
