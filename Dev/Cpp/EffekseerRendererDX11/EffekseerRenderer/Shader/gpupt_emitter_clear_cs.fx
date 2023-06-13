#include "gpupt_common.h"

StructuredBuffer<ParameterSet> ParamSets : register(t0);
RWStructuredBuffer<Emitter> Emitters : register(u0);

[numthreads(16, 1, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    uint emitterID = dtid.x + dtid.y * 16;
    Emitter emitter = Emitters[emitterID];
    emitter.flagBits = 0;
    emitter.seed = 0;
    Emitters[emitterID] = emitter;
}
