static const char metal_sprite_lit_vs[] = R"(mtlcode
#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct VS_Input
{
    float3 Pos;
    float4 Color;
    float4 Normal;
    float4 Tangent;
    float2 UV1;
    float2 UV2;
};

struct VS_Output
{
    float4 PosVS;
    float4 Color;
    float2 UV;
    float3 WorldN;
    float3 WorldB;
    float3 WorldT;
    float4 PosP;
};

struct VS_ConstantBuffer
{
    float4x4 mCamera;
    float4x4 mCameraProj;
    float4 mUVInversed;
    float4 mflipbookParameter;
};

struct main0_out
{
    float4 _entryPointOutput_Color [[user(locn0)]];
    float2 _entryPointOutput_UV [[user(locn1)]];
    float3 _entryPointOutput_WorldN [[user(locn2)]];
    float3 _entryPointOutput_WorldB [[user(locn3)]];
    float3 _entryPointOutput_WorldT [[user(locn4)]];
    float4 _entryPointOutput_PosP [[user(locn5)]];
    float4 gl_Position [[position]];
};

struct main0_in
{
    float3 Input_Pos [[attribute(0)]];
    float4 Input_Color [[attribute(1)]];
    float4 Input_Normal [[attribute(2)]];
    float4 Input_Tangent [[attribute(3)]];
    float2 Input_UV1 [[attribute(4)]];
    float2 Input_UV2 [[attribute(5)]];
};

static inline __attribute__((always_inline))
VS_Output _main(VS_Input Input, constant VS_ConstantBuffer& _73)
{
    VS_Output Output = VS_Output{ float4(0.0), float4(0.0), float2(0.0), float3(0.0), float3(0.0), float3(0.0), float4(0.0) };
    float4 worldNormal = float4((Input.Normal.xyz - float3(0.5)) * 2.0, 0.0);
    float4 worldTangent = float4((Input.Tangent.xyz - float3(0.5)) * 2.0, 0.0);
    float4 worldBinormal = float4(cross(worldNormal.xyz, worldTangent.xyz), 0.0);
    float4 worldPos = float4(Input.Pos.x, Input.Pos.y, Input.Pos.z, 1.0);
    Output.PosVS = _73.mCameraProj * worldPos;
    Output.Color = Input.Color;
    float2 uv1 = Input.UV1;
    uv1.y = _73.mUVInversed.x + (_73.mUVInversed.y * uv1.y);
    Output.UV = uv1;
    Output.WorldN = worldNormal.xyz;
    Output.WorldB = worldBinormal.xyz;
    Output.WorldT = worldTangent.xyz;
    Output.PosP = Output.PosVS;
    return Output;
}

vertex main0_out main0(main0_in in [[stage_in]], constant VS_ConstantBuffer& _73 [[buffer(0)]])
{
    main0_out out = {};
    VS_Input Input;
    Input.Pos = in.Input_Pos;
    Input.Color = in.Input_Color;
    Input.Normal = in.Input_Normal;
    Input.Tangent = in.Input_Tangent;
    Input.UV1 = in.Input_UV1;
    Input.UV2 = in.Input_UV2;
    VS_Output flattenTemp = _main(Input, _73);
    out.gl_Position = flattenTemp.PosVS;
    out._entryPointOutput_Color = flattenTemp.Color;
    out._entryPointOutput_UV = flattenTemp.UV;
    out._entryPointOutput_WorldN = flattenTemp.WorldN;
    out._entryPointOutput_WorldB = flattenTemp.WorldB;
    out._entryPointOutput_WorldT = flattenTemp.WorldT;
    out._entryPointOutput_PosP = flattenTemp.PosP;
    return out;
}

)";

