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

StructuredBuffer<EmitPoint> EmitPoints : register(t1);
RWStructuredBuffer<Particle> Particles : register(u0);

[numthreads(1, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint seed = emitter.Seed ^ (emitter.TotalEmitCount + dtid.x);
    float3 position = emitter.Transform[3];
    float3 direction = RandomSpread(seed, paramSet.Direction, paramSet.Spread * 3.141592f / 180.0f);
    float speed = RandomFloatRange(seed, paramSet.InitialSpeed);

    if (paramSet.EmitShapeType == 1) {
        float3 lineStart = mul(float4(paramSet.EmitShapeData[0].xyz, 0.0f), emitter.Transform).xyz;
        float3 lineEnd = mul(float4(paramSet.EmitShapeData[1].xyz, 0.0f), emitter.Transform).xyz;
        float lineWidth = paramSet.EmitShapeData[1].w;
        position += lerp(lineStart, lineEnd, RandomFloat(seed));
        position += RandomDirection(seed) * lineWidth * 0.5f;
    } else if (paramSet.EmitShapeType == 2) {
        float3 circleAxis = mul(float4(paramSet.EmitShapeData[0].xyz, 0.0f), emitter.Transform).xyz;
        float circleInner = paramSet.EmitShapeData[1].x;
        float circleOuter = paramSet.EmitShapeData[1].y;
        float circleRadius = lerp(circleInner, circleOuter, RandomFloat(seed));
        position += RandomCircle(seed, circleAxis) * circleRadius;
    } else if (paramSet.EmitShapeType == 3) {
        float sphereRadius = paramSet.EmitShapeData[0].x;
        position += RandomDirection(seed) * sphereRadius;
    } else if (paramSet.EmitShapeType == 4) {
        float modelSize = paramSet.EmitShapeData[0].y;
        if (emitter.EmitPointCount > 0) {
            uint emitIndex = RandomUint(seed) % emitter.EmitPointCount;
            EmitPoint emitPoint = EmitPoints[emitIndex];
            position += mul(float4(emitPoint.Position * modelSize, 0.0f), emitter.Transform).xyz;
            direction = mul(direction, float3x3(normalize(emitPoint.Tangent), normalize(emitPoint.Binormal), normalize(emitPoint.Normal)));
        }
    }

    direction = mul(float4(direction, 0.0f), emitter.Transform).xyz;

    uint particleID = emitter.ParticleHead + (emitter.TotalEmitCount + dtid.x) % emitter.ParticleSize;
    Particle particle;
    particle.FlagBits = 0x01;
    particle.Seed = seed;
    particle.LifeAge = 0.0f;
    
    if (paramSet.ColorFlags == 0) {
        particle.InheritColor = 0xFFFFFFFF;
    } else {
        particle.InheritColor = emitter.Color;
    }
    particle.Color = 0xFFFFFFFF;
    particle.Padding = 0;

    particle.Transform = TRSMatrix(position, float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0));
    particle.Velocity = PackFloat4(direction * speed, 0.0f);
    Particles[particleID] = particle;
}
