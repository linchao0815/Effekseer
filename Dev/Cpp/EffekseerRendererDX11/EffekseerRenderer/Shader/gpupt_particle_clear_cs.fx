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
RWStructuredBuffer<Particle> Particles : register(u0);

[numthreads(256, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint particleID = bufferOffset + dtid.x + dtid.y * 256;
    Particle particle = Particles[particleID];
    
    particle.flagBits = 0;
    particle.seed = 0;
    particle.lifeAge = 0.0f;
    particle.color = 0;
    particle.position = float3(0.0f, 0.0f, 0.0f);
    particle.velocity = packFloat4(float3(0.0f, 0.0f, 0.1f), 0.0f);
    particle.rotscale = packFloat4(float3(0.0f, 0.0f, 0.0f), 0.0f);

    Particles[particleID] = particle;
}
