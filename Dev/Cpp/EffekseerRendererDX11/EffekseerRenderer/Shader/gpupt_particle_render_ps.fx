#include "gpupt_common.h"

Texture2D<float4> ColorTex : register(t0);
SamplerState ColorSamp : register(s0);
Texture2D<float4> NormalTex : register(t1);
SamplerState NormalSamp : register(s1);

struct PS_Input
{
	float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 Color : COLOR0;
};

float4 main(const PS_Input Input) : SV_Target
{
    return Input.Color * ColorTex.Sample(NormalSamp, Input.UV);
}
