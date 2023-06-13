#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

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
    float3x4 Transform;
};

struct cb2
{
    Emitter emitter;
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
    float4x3 Transform;
};

struct Particle_1
{
    uint FlagBits;
    uint Seed;
    float LifeAge;
    uint InheritColor;
    uint2 Velocity;
    uint Color;
    uint Padding;
    float3x4 Transform;
};

struct Particles
{
    Particle_1 _data[1];
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
    packed_float3 Direction;
    float Spread;
    float2 InitialSpeed;
    float2 Damping;
    float4 InitialAngleScale[2];
    float4 TargetAngleScale[2];
    packed_float3 Gravity;
    uint Padding2;
    packed_float3 VortexCenter;
    float VortexRotation;
    packed_float3 VortexAxis;
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

struct cb1
{
    ParameterSet paramSet;
};

struct Constants
{
    packed_float3 CameraPos;
    float DeltaTime;
    packed_float3 CameraFront;
    float Reserved;
    float4x4 ProjMat;
    float4x4 CameraMat;
    float3x4 BillboardMat;
    float3x4 YAxisBillboardMat;
};

struct cb0
{
    Constants constants;
};

struct Trail
{
    float3 Position;
    uint Direction;
};

struct Trail_1
{
    packed_float3 Position;
    uint Direction;
};

struct Trails
{
    Trail_1 _data[1];
};

struct main0_out
{
    float2 _entryPointOutput_UV [[user(locn0)]];
    float4 _entryPointOutput_Color [[user(locn1)]];
    float4 gl_Position [[position]];
};

struct main0_in
{
    float3 input_Pos [[attribute(0)]];
    float3 input_Normal [[attribute(1)]];
    float3 input_Binormal [[attribute(2)]];
    float3 input_Tangent [[attribute(3)]];
    float2 input_UV [[attribute(4)]];
    float4 input_Color [[attribute(5)]];
};

static inline __attribute__((always_inline))
float4 UnpackFloat4(thread const uint2& bits)
{
    return float4(float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).x)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).y)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).z)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).w)).x);
}

static inline __attribute__((always_inline))
float3 UnpackNormalizedFloat3(thread const uint& bits)
{
    float3 v = float3(uint3(bits, bits >> uint(10), bits >> uint(20)) & uint3(1023u));
    return ((v / float3(1023.0)) * 2.0) - float3(1.0);
}

static inline __attribute__((always_inline))
float4 UnpackColor(thread const uint& color32)
{
    return float4(float(color32 & 255u), float((color32 >> uint(8)) & 255u), float((color32 >> uint(16)) & 255u), float((color32 >> uint(24)) & 255u)) / float4(255.0);
}

static inline __attribute__((always_inline))
VS_Output _main(VS_Input _input, constant cb2& _153, const device Particles& Particles_1, constant cb1& _223, constant cb0& _249, const device Trails& Trails_1)
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
    particle.Transform = transpose(Particles_1._data[index].Transform);
    VS_Output _output;
    if ((particle.FlagBits & 1u) != 0u)
    {
        uint updateCount = (particle.FlagBits >> uint(1)) & 255u;
        float3 position = _input.Pos;
        float2 uv = _input.UV;
        float4 color = _input.Color;
        if (_223.paramSet.ShapeType == 0u)
        {
            position = particle.Transform * float4(position, 0.0);
            if (_223.paramSet.ShapeData == 0u)
            {
                position = float4(position, 0.0) * _249.constants.BillboardMat;
            }
            else
            {
                if (_223.paramSet.ShapeData == 1u)
                {
                    position = float4(position, 0.0) * _249.constants.YAxisBillboardMat;
                }
            }
            position += particle.Transform[3];
        }
        else
        {
            if (_223.paramSet.ShapeType == 1u)
            {
                position = particle.Transform * float4(position, 1.0);
            }
            else
            {
                if (_223.paramSet.ShapeType == 2u)
                {
                    uint trailLength = min(_223.paramSet.ShapeData, updateCount);
                    float3 trailPosition;
                    float3 trailDirection;
                    if ((_input.VertexID / 2u) == 0u)
                    {
                        trailPosition = particle.Transform[3];
                        uint2 param = particle.Velocity;
                        trailDirection = fast::normalize(UnpackFloat4(param).xyz);
                    }
                    else
                    {
                        uint trailID = _153.emitter.TrailHead + (_input.InstanceID * _223.paramSet.ShapeData);
                        uint trailIndex = min((_input.VertexID / 2u), trailLength);
                        trailID += (((_223.paramSet.ShapeData + _153.emitter.TrailPhase) - trailIndex) % _223.paramSet.ShapeData);
                        Trail trail;
                        trail.Position = float3(Trails_1._data[trailID].Position);
                        trail.Direction = Trails_1._data[trailID].Direction;
                        trailPosition = trail.Position;
                        uint param_1 = trail.Direction;
                        trailDirection = fast::normalize(UnpackNormalizedFloat3(param_1));
                        uv.y = float(trailIndex) / float(trailLength);
                    }
                    float3 trailTangent = fast::normalize(cross(float3(_249.constants.CameraFront), trailDirection));
                    position = (trailTangent * position.x) * _223.paramSet.ShapeSize;
                    position += trailPosition;
                }
            }
        }
        uint param_2 = particle.Color;
        color *= UnpackColor(param_2);
        float4 _400 = color;
        float3 _402 = _400.xyz * _223.paramSet.Emissive;
        color.x = _402.x;
        color.y = _402.y;
        color.z = _402.z;
        _output.Pos = _249.constants.ProjMat * (_249.constants.CameraMat * float4(position, 1.0));
        _output.UV = uv;
        _output.Color = color;
    }
    else
    {
        _output.Pos = float4(0.0);
        _output.UV = float2(0.0);
        _output.Color = float4(0.0);
    }
    return _output;
}

vertex main0_out main0(main0_in in [[stage_in]], constant cb0& _249 [[buffer(0)]], constant cb1& _223 [[buffer(1)]], constant cb2& _153 [[buffer(2)]], const device Particles& Particles_1 [[buffer(10)]], const device Trails& Trails_1 [[buffer(11)]], uint gl_InstanceIndex [[instance_id]], uint gl_VertexIndex [[vertex_id]])
{
    main0_out out = {};
    VS_Input _input;
    _input.Pos = in.input_Pos;
    _input.Normal = in.input_Normal;
    _input.Binormal = in.input_Binormal;
    _input.Tangent = in.input_Tangent;
    _input.UV = in.input_UV;
    _input.Color = in.input_Color;
    _input.InstanceID = gl_InstanceIndex;
    _input.VertexID = gl_VertexIndex;
    VS_Output flattenTemp = _main(_input, _153, Particles_1, _223, _249, Trails_1);
    out.gl_Position = flattenTemp.Pos;
    out._entryPointOutput_UV = flattenTemp.UV;
    out._entryPointOutput_Color = flattenTemp.Color;
    return out;
}

