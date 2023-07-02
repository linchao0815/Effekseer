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
    uint paramID = (emitter.FlagBits >> 1) & 0x3FF;
    ParameterSet paramSet = ParamSets[paramID];
    
    for (uint i = 0; i < input.NextEmitCount; i++) {
        float paramSeed = RandomUint(emitter.Seed);
        float3 position = input.Transform._m03_m13_m23;
        float3 direction = SpreadDir(paramSeed, paramSet.Direction, paramSet.Spread.x * 3.141592f / 180.0f);
        direction = mul(input.Transform, float4(direction, 0.0f)).xyz;
        float speed = RandomFloatRange(paramSeed, paramSet.InitialSpeed);

        uint particleOffset = (input.TotalEmitCount + i) % emitter.ParticleSize;
        uint particleID = emitter.ParticleHead + particleOffset;
        Particle particle = Particles[particleID];
        particle.FlagBits = 0x01 | (paramID << 1) | (emitterID << 11);
        particle.Seed = paramSeed;
        particle.LifeAge = 0.0f;
        
        if (paramSet.ColorFlags == 0) {
            particle.InheritColor = 0xFFFFFFFF;
        } else {
            particle.InheritColor = PackColor(input.Color);
        }
        
        particle.Transform._m03_m13_m23 = position;
        particle.Velocity = PackFloat4(direction * speed, 0.0f);
        Particles[particleID] = particle;
    }

    Emitters[emitterID] = emitter;
}
