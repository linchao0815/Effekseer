#include "gpupt_common.h"

cbuffer cb : register(b8)
{
    Constants constants;
};
cbuffer cb1 : register(b9)
{
    uint bufferOffset;
}

struct VS_Input
{
	float3 Pos : POSITION0;
	float3 Normal : NORMAL0;
	float3 Binormal : NORMAL1;
	float3 Tangent : NORMAL2;
    float2 UV : TEXCOORD0;
    float4 Color : NORMAL3;
    uint InstanceID : SV_InstanceID;
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 Color : COLOR0;
};

StructuredBuffer<Particle> Particles : register(t8);
StructuredBuffer<ParameterSet> ParamSets : register(t9);
StructuredBuffer<DynamicInput> DynamicInputs : register(t10);

VS_Output main(const VS_Input Input)
{
    VS_Output Output;
    
    uint index = bufferOffset + Input.InstanceID;
    Particle particle = Particles[index];
    if (particle.flagBits & 0x01) {
        uint paramID = (particle.flagBits >> 1) & 0x3F;
        uint emitterID = (particle.flagBits >> 11) & 0x3F;
        ParameterSet paramSet = ParamSets[paramID];
        DynamicInput input = DynamicInputs[emitterID];
        uint paramSeed = particle.seed;
        float lifeTime = (float)randomUintRange(paramSeed, paramSet.LifeTime);
        float lifeRatio = particle.lifeAge / lifeTime;

        float3 position = Input.Pos;
        float4 rotscale = unpackFloat4(particle.rotscale);
        float3 rotation = rotscale.xyz;
        float scale = rotscale.w * paramSet.ShapeSize;
        float4 colorStart = randomColorRange(paramSeed, paramSet.ColorStart);
        float4 colorEnd = randomColorRange(paramSeed, paramSet.ColorEnd);

        // Rotation transform
        position = mul(rotationMatrix(rotation), position * scale);

        if (paramSet.ShapeType == 0) {
            // Billboard transform
            if (paramSet.ShapeData == 0) {
                position = mul(constants.BillboardMat, position);
            } else if (paramSet.ShapeData == 1) {
                position = mul(constants.YAxisBillboardMat, position);
            }
        }

        // Color calculation
        float4 color = Input.Color;
        color *= lerp(colorStart, colorEnd, lifeRatio);
        if (paramSet.ColorFlags == 2 || paramSet.ColorFlags == 3) {
            color = input.color;
        } else {
            color *= unpackColor(particle.color);
        }
        color.rgb *= paramSet.Emissive;
        color.a *= clamp(particle.lifeAge / paramSet.FadeIn, 0.0, 1.0);
        color.a *= clamp((lifeTime - particle.lifeAge) / paramSet.FadeOut, 0.0, 1.0);

        // Position transform
        float4 worldPos = float4(particle.position + position, 1.0f);
        Output.Pos = mul(constants.ProjMat, mul(constants.CameraMat, worldPos));
        Output.UV = Input.UV;
        Output.Color = color;
    }
    else {
        Output.Pos = float4(0.0f, 0.0f, 0.0f, 0.0f);
        Output.UV = float2(0.0f, 0.0f);
        Output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    return Output;
}
