struct PS_Input
{
    float4 Pos;
    float2 UV;
    float4 Color;
};

Texture2D<float4> ColorTex : register(t2);
SamplerState ColorSamp : register(s2);
Texture2D<float4> NormalTex : register(t3);
SamplerState NormalSamp : register(s3);

static float4 gl_FragCoord;
static float2 input_UV;
static float4 input_Color;
static float4 _entryPointOutput;

struct SPIRV_Cross_Input
{
    float2 input_UV : TEXCOORD0;
    float4 input_Color : TEXCOORD1;
    float4 gl_FragCoord : SV_Position;
};

struct SPIRV_Cross_Output
{
    float4 _entryPointOutput : SV_Target0;
};

float4 _main(PS_Input _input)
{
    return _input.Color * ColorTex.Sample(ColorSamp, _input.UV);
}

void frag_main()
{
    PS_Input _input;
    _input.Pos = gl_FragCoord;
    _input.UV = input_UV;
    _input.Color = input_Color;
    _entryPointOutput = _main(_input);
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    gl_FragCoord = stage_input.gl_FragCoord;
    gl_FragCoord.w = 1.0 / gl_FragCoord.w;
    input_UV = stage_input.input_UV;
    input_Color = stage_input.input_Color;
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output._entryPointOutput = _entryPointOutput;
    return stage_output;
}
