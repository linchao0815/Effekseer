#version 430

struct PS_Input
{
    vec4 Pos;
    vec2 UV;
    vec4 Color;
};

layout(set = 1, binding = 2) uniform sampler2D Sampler_ColorSamp;

layout(location = 0) in vec2 input_UV;
layout(location = 1) in vec4 input_Color;
layout(location = 0) out vec4 _entryPointOutput;

vec4 _main(PS_Input _input)
{
    return _input.Color * texture(Sampler_ColorSamp, _input.UV);
}

void main()
{
    PS_Input _input;
    _input.Pos = gl_FragCoord;
    _input.UV = input_UV;
    _input.Color = input_Color;
    _entryPointOutput = _main(_input);
}

