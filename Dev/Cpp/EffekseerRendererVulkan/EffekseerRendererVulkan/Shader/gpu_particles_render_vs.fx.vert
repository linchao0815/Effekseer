#version 430

struct VS_Input
{
    vec3 Pos;
    vec3 Normal;
    vec3 Binormal;
    vec3 Tangent;
    vec2 UV;
    vec4 Color;
    uint InstanceID;
    uint VertexID;
};

struct VS_Output
{
    vec4 Pos;
    vec2 UV;
    vec4 Color;
};

struct Emitter
{
    uint FlagBits;
    uint Seed;
    uint ParticleHead;
    uint ParticleSize;
    uint TrailHead;
    uint TrailSize;
    uint TrailPhase;
    uint NextEmitCount;
    uint TotalEmitCount;
    uint EmitPointCount;
    float TimeCount;
    float TimeStopped;
    uint Reserved0;
    uint Reserved1;
    uint Reserved2;
    uint Color;
    mat4x3 Transform;
};

struct Particle
{
    uint FlagBits;
    uint Seed;
    float LifeAge;
    uint InheritColor;
    uvec2 Velocity;
    uint Color;
    uint Padding;
    mat4x3 Transform;
};

struct ParameterSet
{
    int EmitCount;
    int EmitPerFrame;
    float EmitOffset;
    uint Padding0;
    vec2 LifeTime;
    uint EmitShapeType;
    uint Padding1;
    vec4 EmitShapeData[2];
    vec3 Direction;
    float Spread;
    vec2 InitialSpeed;
    vec2 Damping;
    vec4 InitialAngleScale[2];
    vec4 TargetAngleScale[2];
    vec3 Gravity;
    uint Padding2;
    vec3 VortexCenter;
    float VortexRotation;
    vec3 VortexAxis;
    float VortexAttraction;
    float TurbulencePower;
    uint TurbulenceSeed;
    float TurbulenceScale;
    float TurbulenceOctave;
    uint RenderState;
    uint ShapeType;
    uint ShapeData;
    float ShapeSize;
    float Emissive;
    float FadeIn;
    float FadeOut;
    uint ColorFlags;
    uvec2 ColorStart;
    uvec2 ColorEnd;
    uint ColorTexIndex;
    uint NormalTexIndex;
    uint TexState;
    uint Padding3;
};

struct Constants
{
    vec3 CameraPos;
    float DeltaTime;
    vec3 CameraFront;
    float Reserved;
    mat4 ProjMat;
    mat4 CameraMat;
    mat4x3 BillboardMat;
    mat4x3 YAxisBillboardMat;
};

struct Trail
{
    vec3 Position;
    uint Direction;
};

layout(set = 0, binding = 2, std140) uniform cb2
{
    layout(row_major) Emitter emitter;
} _153;

layout(set = 2, binding = 0, std430) readonly buffer Particles
{
    layout(row_major) Particle _data[];
} Particles_1;

layout(set = 0, binding = 1, std140) uniform cb1
{
    ParameterSet paramSet;
} _223;

layout(set = 0, binding = 0, std140) uniform cb0
{
    layout(row_major) Constants constants;
} _249;

layout(set = 2, binding = 1, std430) readonly buffer Trails
{
    Trail _data[];
} Trails_1;

layout(location = 0) in vec3 input_Pos;
layout(location = 1) in vec3 input_Normal;
layout(location = 2) in vec3 input_Binormal;
layout(location = 3) in vec3 input_Tangent;
layout(location = 4) in vec2 input_UV;
layout(location = 5) in vec4 input_Color;
layout(location = 0) out vec2 _entryPointOutput_UV;
layout(location = 1) out vec4 _entryPointOutput_Color;

vec4 UnpackFloat4(uvec2 bits)
{
    return vec4(unpackHalf2x16(uvec4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).x).x, unpackHalf2x16(uvec4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).y).x, unpackHalf2x16(uvec4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).z).x, unpackHalf2x16(uvec4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).w).x);
}

vec3 UnpackNormalizedFloat3(uint bits)
{
    vec3 v = vec3(uvec3(bits, bits >> uint(10), bits >> uint(20)) & uvec3(1023u));
    return ((v / vec3(1023.0)) * 2.0) - vec3(1.0);
}

vec4 UnpackColor(uint color32)
{
    return vec4(float(color32 & 255u), float((color32 >> uint(8)) & 255u), float((color32 >> uint(16)) & 255u), float((color32 >> uint(24)) & 255u)) / vec4(255.0);
}

VS_Output _main(VS_Input _input)
{
    uint index = _153.emitter.ParticleHead + _input.InstanceID;
    Particle particle;
    particle.FlagBits = Particles_1._data[index].FlagBits;
    particle.Seed = Particles_1._data[index].Seed;
    particle.LifeAge = Particles_1._data[index].LifeAge;
    particle.InheritColor = Particles_1._data[index].InheritColor;
    particle.Velocity = Particles_1._data[index].Velocity;
    particle.Color = Particles_1._data[index].Color;
    particle.Padding = Particles_1._data[index].Padding;
    particle.Transform = Particles_1._data[index].Transform;
    VS_Output _output;
    if ((particle.FlagBits & 1u) != 0u)
    {
        uint updateCount = (particle.FlagBits >> uint(1)) & 255u;
        vec3 position = _input.Pos;
        vec2 uv = _input.UV;
        vec4 color = _input.Color;
        if (_223.paramSet.ShapeType == 0u)
        {
            position = particle.Transform * vec4(position, 0.0);
            if (_223.paramSet.ShapeData == 0u)
            {
                position = _249.constants.BillboardMat * vec4(position, 0.0);
            }
            else
            {
                if (_223.paramSet.ShapeData == 1u)
                {
                    position = _249.constants.YAxisBillboardMat * vec4(position, 0.0);
                }
            }
            position += particle.Transform[3];
        }
        else
        {
            if (_223.paramSet.ShapeType == 1u)
            {
                position = particle.Transform * vec4(position, 1.0);
            }
            else
            {
                if (_223.paramSet.ShapeType == 2u)
                {
                    uint trailLength = min(_223.paramSet.ShapeData, updateCount);
                    vec3 trailPosition;
                    vec3 trailDirection;
                    if ((_input.VertexID / 2u) == 0u)
                    {
                        trailPosition = particle.Transform[3];
                        uvec2 param = particle.Velocity;
                        trailDirection = normalize(UnpackFloat4(param).xyz);
                    }
                    else
                    {
                        uint trailID = _153.emitter.TrailHead + (_input.InstanceID * _223.paramSet.ShapeData);
                        uint trailIndex = min((_input.VertexID / 2u), trailLength);
                        trailID += (((_223.paramSet.ShapeData + _153.emitter.TrailPhase) - trailIndex) % _223.paramSet.ShapeData);
                        Trail trail;
                        trail.Position = Trails_1._data[trailID].Position;
                        trail.Direction = Trails_1._data[trailID].Direction;
                        trailPosition = trail.Position;
                        uint param_1 = trail.Direction;
                        trailDirection = normalize(UnpackNormalizedFloat3(param_1));
                        uv.y = float(trailIndex) / float(trailLength);
                    }
                    vec3 trailTangent = normalize(cross(_249.constants.CameraFront, trailDirection));
                    position = (trailTangent * position.x) * _223.paramSet.ShapeSize;
                    position += trailPosition;
                }
            }
        }
        uint param_2 = particle.Color;
        color *= UnpackColor(param_2);
        vec4 _400 = color;
        vec3 _402 = _400.xyz * _223.paramSet.Emissive;
        color.x = _402.x;
        color.y = _402.y;
        color.z = _402.z;
        _output.Pos = (vec4(position, 1.0) * _249.constants.CameraMat) * _249.constants.ProjMat;
        _output.UV = uv;
        _output.Color = color;
    }
    else
    {
        _output.Pos = vec4(0.0);
        _output.UV = vec2(0.0);
        _output.Color = vec4(0.0);
    }
    return _output;
}

void main()
{
    VS_Input _input;
    _input.Pos = input_Pos;
    _input.Normal = input_Normal;
    _input.Binormal = input_Binormal;
    _input.Tangent = input_Tangent;
    _input.UV = input_UV;
    _input.Color = input_Color;
    _input.InstanceID = uint(gl_InstanceIndex);
    _input.VertexID = uint(gl_VertexIndex);
    VS_Output flattenTemp = _main(_input);
    vec4 _position = flattenTemp.Pos;
    _position.y = -_position.y;
    gl_Position = _position;
    _entryPointOutput_UV = flattenTemp.UV;
    _entryPointOutput_Color = flattenTemp.Color;
}

