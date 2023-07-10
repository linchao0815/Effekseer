#include "gpu_particles_common.h"

cbuffer cb : register(b0)
{
    Constants constants;
};
cbuffer cb1 : register(b1)
{
    uint EmitterID;
    uint ParticleHead;
}

StructuredBuffer<ParameterSet> ParamSets : register(t0);
StructuredBuffer<Emitter> Emitters : register(t1);
RWStructuredBuffer<Particle> Particles : register(u0);

[numthreads(1, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    Emitter emitter = Emitters[EmitterID];
    uint paramID = (emitter.FlagBits >> 1) & 0x3FF;
    ParameterSet paramSet = ParamSets[paramID];
    
    float paramSeed = emitter.Seed ^ (emitter.TotalEmitCount + dtid.x);
    float3 position = emitter.Transform._m03_m13_m23;
    float3 direction = RandomSpread(paramSeed, paramSet.Direction, paramSet.Spread.x * 3.141592f / 180.0f);
    direction = mul(emitter.Transform, float4(direction, 0.0f)).xyz;
    float speed = RandomFloatRange(paramSeed, paramSet.InitialSpeed);

    if (paramSet.EmitShapeType == 1) {
        float3 lineStart = mul(emitter.Transform, float4(paramSet.EmitShapeData[0].xyz, 0.0f)).xyz;
        float3 lineEnd = mul(emitter.Transform, float4(paramSet.EmitShapeData[1].xyz, 0.0f)).xyz;
        float lineWidth = paramSet.EmitShapeData[1].w;
        position += lerp(lineStart, lineEnd, RandomFloat(paramSeed));
        position += RandomDirection(paramSeed) * lineWidth * 0.5f;
    } else if (paramSet.EmitShapeType == 2) {
        float3 circleAxis = mul(emitter.Transform, float4(paramSet.EmitShapeData[0].xyz, 0.0f)).xyz;
        float circleInner = paramSet.EmitShapeData[1].x;
        float circleOuter = paramSet.EmitShapeData[1].y;
        float circleRadius = lerp(circleInner, circleOuter, RandomFloat(paramSeed));
        position += RandomCircle(paramSeed, circleAxis) * circleRadius;
    } else if (paramSet.EmitShapeType == 3) {
        float sphereRadius = paramSet.EmitShapeData[0].x;
        position += RandomDirection(paramSeed) * sphereRadius;
    }

    uint particleID = emitter.ParticleHead + (emitter.TotalEmitCount + dtid.x) % emitter.ParticleSize;
    Particle particle = Particles[particleID];
    particle.FlagBits = 0x01 | (paramID << 1);
    particle.Seed = paramSeed;
    particle.LifeAge = 0.0f;
    
    if (paramSet.ColorFlags == 0) {
        particle.InheritColor = 0xFFFFFFFF;
    } else {
        particle.InheritColor = PackColor(emitter.Color);
    }
    
    particle.Transform._m03_m13_m23 = position;
    particle.Velocity = PackFloat4(direction * speed, 0.0f);
    Particles[particleID] = particle;
}
