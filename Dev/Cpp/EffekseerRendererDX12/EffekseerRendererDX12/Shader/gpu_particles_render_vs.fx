struct VS_Input
{
    float3 Pos;
    float3 Normal;
    float3 Binormal;
    float3 Tangent;
    float2 UV;
    float4 Color;
    uint InstanceID;
    uint VertexID;
};

struct VS_Output
{
    float4 Pos;
    float2 UV;
    float4 Color;
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
    column_major float4x3 Transform;
};

struct Particle
{
    uint FlagBits;
    uint Seed;
    float LifeAge;
    uint InheritColor;
    uint2 Velocity;
    uint Color;
    uint Padding;
    column_major float4x3 Transform;
};

struct ParameterSet
{
    int EmitCount;
    int EmitPerFrame;
    float EmitOffset;
    uint Padding0;
    float2 LifeTime;
    uint EmitShapeType;
    uint Padding1;
    float4 EmitShapeData[2];
    float3 Direction;
    float Spread;
    float2 InitialSpeed;
    float2 Damping;
    float4 InitialAngleScale[2];
    float4 TargetAngleScale[2];
    float3 Gravity;
    uint Padding2;
    float3 VortexCenter;
    float VortexRotation;
    float3 VortexAxis;
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
    uint2 ColorStart;
    uint2 ColorEnd;
    uint ColorTexIndex;
    uint NormalTexIndex;
    uint TexState;
    uint Padding3;
};

struct Constants
{
    float3 CameraPos;
    float DeltaTime;
    float3 CameraFront;
    float Reserved;
    column_major float4x4 ProjMat;
    column_major float4x4 CameraMat;
    column_major float4x3 BillboardMat;
    column_major float4x3 YAxisBillboardMat;
};

struct Trail
{
    float3 Position;
    uint Direction;
};

cbuffer cb2 : register(b2)
{
    Emitter _153_emitter : packoffset(c0);
};

ByteAddressBuffer Particles : register(t0);
cbuffer cb1 : register(b1)
{
    ParameterSet _223_paramSet : packoffset(c0);
};

cbuffer cb0 : register(b0)
{
    Constants _249_constants : packoffset(c0);
};

ByteAddressBuffer Trails : register(t1);

static float4 gl_Position;
static int gl_VertexIndex;
static int gl_InstanceIndex;
static float3 input_Pos;
static float3 input_Normal;
static float3 input_Binormal;
static float3 input_Tangent;
static float2 input_UV;
static float4 input_Color;
static float2 _entryPointOutput_UV;
static float4 _entryPointOutput_Color;

struct SPIRV_Cross_Input
{
    float3 input_Pos : TEXCOORD0;
    float3 input_Normal : TEXCOORD1;
    float3 input_Binormal : TEXCOORD2;
    float3 input_Tangent : TEXCOORD3;
    float2 input_UV : TEXCOORD4;
    float4 input_Color : TEXCOORD5;
    uint gl_VertexIndex : SV_VertexID;
    uint gl_InstanceIndex : SV_InstanceID;
};

struct SPIRV_Cross_Output
{
    float2 _entryPointOutput_UV : TEXCOORD0;
    float4 _entryPointOutput_Color : TEXCOORD1;
    float4 gl_Position : SV_Position;
};

uint spvPackHalf2x16(float2 value)
{
    uint2 Packed = f32tof16(value);
    return Packed.x | (Packed.y << 16);
}

float2 spvUnpackHalf2x16(uint value)
{
    return f16tof32(uint2(value & 0xffff, value >> 16));
}

float4 UnpackFloat4(uint2 bits)
{
    return float4(spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).x).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).y).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).z).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).w).x);
}

float3 UnpackNormalizedFloat3(uint bits)
{
    float3 v = float3(uint3(bits, bits >> uint(10), bits >> uint(20)) & uint3(1023u, 1023u, 1023u));
    return ((v / 1023.0f.xxx) * 2.0f) - 1.0f.xxx;
}

float4 UnpackColor(uint color32)
{
    return float4(float(color32 & 255u), float((color32 >> uint(8)) & 255u), float((color32 >> uint(16)) & 255u), float((color32 >> uint(24)) & 255u)) / 255.0f.xxxx;
}

VS_Output _main(VS_Input _input)
{
    uint index = _153_emitter.ParticleHead + _input.InstanceID;
    Particle _173;
    _173.FlagBits = Particles.Load(index * 80 + 0);
    _173.Seed = Particles.Load(index * 80 + 4);
    _173.LifeAge = asfloat(Particles.Load(index * 80 + 8));
    _173.InheritColor = Particles.Load(index * 80 + 12);
    _173.Velocity = Particles.Load2(index * 80 + 16);
    _173.Color = Particles.Load(index * 80 + 24);
    _173.Padding = Particles.Load(index * 80 + 28);
    _173.Transform = asfloat(uint4x3(Particles.Load(index * 80 + 32), Particles.Load(index * 80 + 48), Particles.Load(index * 80 + 64), Particles.Load(index * 80 + 36), Particles.Load(index * 80 + 52), Particles.Load(index * 80 + 68), Particles.Load(index * 80 + 40), Particles.Load(index * 80 + 56), Particles.Load(index * 80 + 72), Particles.Load(index * 80 + 44), Particles.Load(index * 80 + 60), Particles.Load(index * 80 + 76)));
    Particle particle;
    particle.FlagBits = _173.FlagBits;
    particle.Seed = _173.Seed;
    particle.LifeAge = _173.LifeAge;
    particle.InheritColor = _173.InheritColor;
    particle.Velocity = _173.Velocity;
    particle.Color = _173.Color;
    particle.Padding = _173.Padding;
    particle.Transform = _173.Transform;
    VS_Output _output;
    if ((particle.FlagBits & 1u) != 0u)
    {
        uint updateCount = (particle.FlagBits >> uint(1)) & 255u;
        float3 position = _input.Pos;
        float2 uv = _input.UV;
        float4 color = _input.Color;
        if (_223_paramSet.ShapeType == 0u)
        {
            position = mul(float4(position, 0.0f), particle.Transform);
            if (_223_paramSet.ShapeData == 0u)
            {
                position = mul(float4(position, 0.0f), _249_constants.BillboardMat);
            }
            else
            {
                if (_223_paramSet.ShapeData == 1u)
                {
                    position = mul(float4(position, 0.0f), _249_constants.YAxisBillboardMat);
                }
            }
            position += particle.Transform[3];
        }
        else
        {
            if (_223_paramSet.ShapeType == 1u)
            {
                position = mul(float4(position, 1.0f), particle.Transform);
            }
            else
            {
                if (_223_paramSet.ShapeType == 2u)
                {
                    uint trailLength = min(_223_paramSet.ShapeData, updateCount);
                    float3 trailPosition;
                    float3 trailDirection;
                    if ((_input.VertexID / 2u) == 0u)
                    {
                        trailPosition = particle.Transform[3];
                        uint2 param = particle.Velocity;
                        trailDirection = normalize(UnpackFloat4(param).xyz);
                    }
                    else
                    {
                        uint trailID = _153_emitter.TrailHead + (_input.InstanceID * _223_paramSet.ShapeData);
                        uint trailIndex = min((_input.VertexID / 2u), trailLength);
                        trailID += (((_223_paramSet.ShapeData + _153_emitter.TrailPhase) - trailIndex) % _223_paramSet.ShapeData);
                        Trail _354;
                        _354.Position = asfloat(Trails.Load3(trailID * 16 + 0));
                        _354.Direction = Trails.Load(trailID * 16 + 12);
                        Trail trail;
                        trail.Position = _354.Position;
                        trail.Direction = _354.Direction;
                        trailPosition = trail.Position;
                        uint param_1 = trail.Direction;
                        trailDirection = normalize(UnpackNormalizedFloat3(param_1));
                        uv.y = float(trailIndex) / float(trailLength);
                    }
                    float3 trailTangent = normalize(cross(_249_constants.CameraFront, trailDirection));
                    position = (trailTangent * position.x) * _223_paramSet.ShapeSize;
                    position += trailPosition;
                }
            }
        }
        uint param_2 = particle.Color;
        color *= UnpackColor(param_2);
        float4 _400 = color;
        float3 _402 = _400.xyz * _223_paramSet.Emissive;
        color.x = _402.x;
        color.y = _402.y;
        color.z = _402.z;
        _output.Pos = mul(_249_constants.ProjMat, mul(_249_constants.CameraMat, float4(position, 1.0f)));
        _output.UV = uv;
        _output.Color = color;
    }
    else
    {
        _output.Pos = 0.0f.xxxx;
        _output.UV = 0.0f.xx;
        _output.Color = 0.0f.xxxx;
    }
    return _output;
}

void vert_main()
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
    gl_Position = flattenTemp.Pos;
    _entryPointOutput_UV = flattenTemp.UV;
    _entryPointOutput_Color = flattenTemp.Color;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    gl_VertexIndex = int(stage_input.gl_VertexIndex);
    gl_InstanceIndex = int(stage_input.gl_InstanceIndex);
    input_Pos = stage_input.input_Pos;
    input_Normal = stage_input.input_Normal;
    input_Binormal = stage_input.input_Binormal;
    input_Tangent = stage_input.input_Tangent;
    input_UV = stage_input.input_UV;
    input_Color = stage_input.input_Color;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output._entryPointOutput_UV = _entryPointOutput_UV;
    stage_output._entryPointOutput_Color = _entryPointOutput_Color;
    return stage_output;
}
