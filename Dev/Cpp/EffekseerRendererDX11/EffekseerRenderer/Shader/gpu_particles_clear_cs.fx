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

[numthreads(256, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint particleID = emitter.ParticleHead + dtid.x;
    
    Particle particle;
    particle.FlagBits = 0;
    particle.Seed = 0;
    particle.LifeAge = 0.0f;
    particle.InheritColor = 0;
    particle.Color = 0;
    particle.Padding = 0;
    particle.Velocity = PackFloat4(float3(0.0f, 0.0f, 0.0f), 0.0f);
    particle.Transform = float3x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    
    Particles[particleID] = particle;
}
