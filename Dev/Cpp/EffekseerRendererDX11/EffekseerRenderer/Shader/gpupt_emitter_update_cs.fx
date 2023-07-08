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
    uint emitterID = dtid.x;
    Emitter emitter = Emitters[emitterID];
    DynamicInput input = DynamicInputs[emitterID];
    uint paramID = (emitter.FlagBits >> 1) & 0x3FF;
    ParameterSet paramSet = ParamSets[paramID];
    
    for (uint i = 0; i < input.NextEmitCount; i++) {
        float paramSeed = RandomUint(emitter.Seed);
        float3 position = input.Transform._m03_m13_m23;
        float3 direction = RandomSpread(paramSeed, paramSet.Direction, paramSet.Spread.x * 3.141592f / 180.0f);
        direction = mul(input.Transform, float4(direction, 0.0f)).xyz;
        float speed = RandomFloatRange(paramSeed, paramSet.InitialSpeed);

        if (paramSet.EmitShapeType == 1) {
            float3 lineStart = mul(input.Transform, float4(paramSet.EmitShapeData[0], 0.0f)).xyz;
            float3 lineEnd = mul(input.Transform, float4(paramSet.EmitShapeData[1], 0.0f)).xyz;
            float lineWidth = paramSet.EmitShapeData[2].x;
            position += lerp(lineStart, lineEnd, RandomFloat(paramSeed));
            position += RandomDirection(paramSeed) * lineWidth * 0.5f;
        } else if (paramSet.EmitShapeType == 2) {
            float3 circleAxis = mul(input.Transform, float4(paramSet.EmitShapeData[0], 0.0f)).xyz;
            float circleInner = paramSet.EmitShapeData[1].x;
            float circleOuter = paramSet.EmitShapeData[1].y;
            float circleRadius = lerp(circleInner, circleOuter, RandomFloat(paramSeed));
            position += RandomCircle(paramSeed, circleAxis) * circleRadius;
        } else if (paramSet.EmitShapeType == 3) {
            float sphereRadius = paramSet.EmitShapeData[0].x;
            position += RandomDirection(paramSeed) * sphereRadius;
        }

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
