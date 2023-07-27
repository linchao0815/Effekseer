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

StructuredBuffer<EmitPoint> EmitPoints : register(t0);
RWStructuredBuffer<Particle> Particles : register(u0);

[numthreads(1, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    float paramSeed = emitter.Seed ^ (emitter.TotalEmitCount + dtid.x);
    float3 position = emitter.Transform._m03_m13_m23;
    float3 direction = RandomSpread(paramSeed, paramSet.Direction, paramSet.Spread.x * 3.141592f / 180.0f);
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
    } else if (paramSet.EmitShapeType == 4) {
        float modelSize = paramSet.EmitShapeData[0].y;
        if (emitter.EmitPointCount > 0) {
            uint emitIndex = RandomUint(paramSeed) % emitter.EmitPointCount;
            EmitPoint emitPoint = EmitPoints[emitIndex];
            position += mul(emitter.Transform, float4(emitPoint.Position * modelSize, 0.0f)).xyz;
            direction = mul(direction, float3x3(normalize(emitPoint.Tangent), normalize(emitPoint.Binormal), normalize(emitPoint.Normal)));
        }
    }

    direction = mul(emitter.Transform, float4(direction, 0.0f)).xyz;

    uint particleID = emitter.ParticleHead + (emitter.TotalEmitCount + dtid.x) % emitter.ParticleSize;
    Particle particle;
    particle.FlagBits = 0x01;
    particle.Seed = paramSeed;
    particle.LifeAge = 0.0f;
    
    if (paramSet.ColorFlags == 0) {
        particle.InheritColor = 0xFFFFFFFF;
    } else {
        particle.InheritColor = emitter.Color;
    }
    particle.Color = 0xFFFFFFFF;
    particle.Padding = 0;

    particle.Transform = float3x4(
        float4(1.0f, 0.0f, 0.0f, position.x),
        float4(0.0f, 1.0f, 0.0f, position.y),
        float4(0.0f, 0.0f, 1.0f, position.z)
    );
    particle.Velocity = PackFloat4(direction * speed, 0.0f);
    Particles[particleID] = particle;
}
