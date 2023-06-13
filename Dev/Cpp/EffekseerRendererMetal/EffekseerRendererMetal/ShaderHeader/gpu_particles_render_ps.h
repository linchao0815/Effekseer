static const char metal_gpu_particles_render_ps[] = R"(mtlcode
#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct PS_Input
{
    float4 Pos;
    float2 UV;
    float4 Color;
};

struct main0_out
{
    float4 _entryPointOutput [[color(0)]];
};

struct main0_in
{
    float2 input_UV [[user(locn0)]];
    float4 input_Color [[user(locn1)]];
};

static inline __attribute__((always_inline))
float4 _main(PS_Input _input, texture2d<float> ColorTex, sampler ColorSamp)
{
    return _input.Color * ColorTex.sample(ColorSamp, _input.UV);
}

fragment main0_out main0(main0_in in [[stage_in]], texture2d<float> ColorTex [[texture(2)]], sampler ColorSamp [[sampler(2)]], float4 gl_FragCoord [[position]])
{
    main0_out out = {};
    PS_Input _input;
    _input.Pos = gl_FragCoord;
    _input.UV = in.input_UV;
    _input.Color = in.input_Color;
    out._entryPointOutput = _main(_input, ColorTex, ColorSamp);
    return out;
}

)";

