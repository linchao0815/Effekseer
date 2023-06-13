#include "gpupt_common.h"

cbuffer cb : register(b0)
{
    Constants constants;
};

StructuredBuffer<ParameterSet> ParamSets : register(t0);
StructuredBuffer<DynamicInput> DynamicInputs : register(t1);
RWStructuredBuffer<Emitter> Emitters : register(u0);
RWStructuredBuffer<Particle> Particles : register(u1);

[numthreads(16, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint emitterID = dtid.x + dtid.y * 16;
    Emitter emitter = Emitters[emitterID];
    DynamicInput input = DynamicInputs[emitterID];
    uint paramID = (emitter.flagBits >> 1) & 0x3F;
    ParameterSet paramSet = ParamSets[paramID];
    
    for (uint i = 0; i < input.nextEmitCount; i++) {
        float paramSeed = randomUint(emitter.seed);
        float3 direction = spreadDir(paramSeed, paramSet.Direction, paramSet.Spread.x * 3.141592f / 180.0f);
        direction = mul(input.transform, float4(direction, 0.0f)).xyz;
        float speed = randomFloatRange(paramSeed, paramSet.InitialSpeed);
        float3 rotation = randomFloat3Range(paramSeed, paramSet.InitialAngle);
        float scale = randomFloatRange(paramSeed, paramSet.InitialScale);

        uint particleID = emitter.particlesHead + (input.totalEmitCount + i) % emitter.particlesSize;
        Particle particle = Particles[particleID];
        particle.flagBits = 0x01 | (paramID << 1) | (emitterID << 11);
        particle.seed = paramSeed;
        particle.lifeAge = 0.0f;
        
        if (paramSet.ColorFlags == 0) {
            particle.color = 0xFFFFFFFF;
        } else {
            particle.color = packColor(input.color);
        }
        
        particle.position = input.transform._m03_m13_m23;
        particle.velocity = packFloat4(direction * speed, 0.0f);
        particle.rotscale = packFloat4(rotation, scale);
        Particles[particleID] = particle;
    }

    Emitters[emitterID] = emitter;
}
