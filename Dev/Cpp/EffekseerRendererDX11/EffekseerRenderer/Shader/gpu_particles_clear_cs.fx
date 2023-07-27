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
RWStructuredBuffer<Particle> Particles : register(u0);

[numthreads(256, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint particleID = ParticleHead + dtid.x;
    
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
