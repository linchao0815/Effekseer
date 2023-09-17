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
    row_major float3x4 Transform;
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

struct EmitPoint
{
    float3 Position;
    float3 Normal;
    float3 Binormal;
    float3 Tangent;
    float2 UV;
    uint VColor;
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
    row_major float3x4 Transform;
};

struct Constants
{
    column_major float4x4 ProjMat;
    column_major float4x4 CameraMat;
    row_major float3x4 BillboardMat;
    row_major float3x4 YAxisBillboardMat;
    float3 CameraPos;
    float DeltaTime;
    float3 CameraFront;
    float Reserved;
};

cbuffer cb2 : register(b2)
{
    Emitter _329_emitter : packoffset(c0);
};

cbuffer cb1 : register(b1)
{
    ParameterSet _362_paramSet : packoffset(c0);
};

ByteAddressBuffer EmitPoints : register(t1);
RWByteAddressBuffer Particles : register(u0);
cbuffer cb0 : register(b0)
{
    Constants _708_constants : packoffset(c0);
};


static uint3 gl_GlobalInvocationID;
struct SPIRV_Cross_Input
{
    uint3 gl_GlobalInvocationID : SV_DispatchThreadID;
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

uint RandomUint(inout uint seed)
{
    uint state = seed;
    seed = (seed * 747796405u) + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

float RandomFloat(inout uint seed)
{
    uint param = seed;
    uint _140 = RandomUint(param);
    seed = param;
    return float(_140) / 4294967296.0f;
}

float3 RandomSpread(inout uint seed, inout float3 baseDir, float angle)
{
    uint param = seed;
    float _254 = RandomFloat(param);
    seed = param;
    float theta = 6.28318023681640625f * _254;
    uint param_1 = seed;
    float _261 = RandomFloat(param_1);
    seed = param_1;
    float phi = angle * _261;
    float3 randDir = float3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
    baseDir = normalize(baseDir);
    if (abs(baseDir.z) != 1.0f)
    {
        float3 front = float3(0.0f, 0.0f, 1.0f);
        float3 right = normalize(cross(front, baseDir));
        float3 up = cross(baseDir, right);
        return mul(randDir, float3x3(float3(right), float3(up), float3(baseDir)));
    }
    else
    {
        return randDir * sign(baseDir.z);
    }
}

float RandomFloatRange(inout uint seed, float2 maxmin)
{
    uint param = seed;
    float _153 = RandomFloat(param);
    seed = param;
    return lerp(maxmin.y, maxmin.x, _153);
}

float3 RandomDirection(inout uint seed)
{
    uint param = seed;
    float _162 = RandomFloat(param);
    seed = param;
    float theta = 6.28318023681640625f * _162;
    uint param_1 = seed;
    float _168 = RandomFloat(param_1);
    seed = param_1;
    float phi = 6.28318023681640625f * _168;
    float3 randDir = float3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
    return randDir;
}

float3 RandomCircle(inout uint seed, inout float3 axis)
{
    uint param = seed;
    float _191 = RandomFloat(param);
    seed = param;
    float theta = 6.28318023681640625f * _191;
    float3 randDir = float3(cos(theta), 0.0f, sin(theta));
    axis = normalize(axis);
    if (abs(axis.y) != 1.0f)
    {
        float3 up = float3(0.0f, 1.0f, 0.0f);
        float3 right = normalize(cross(up, axis));
        float3 front = cross(axis, right);
        return mul(randDir, float3x3(float3(right), float3(axis), float3(front)));
    }
    else
    {
        return randDir * sign(axis.y);
    }
}

uint2 PackFloat4(float4 v)
{
    uint4 v16 = uint4(spvPackHalf2x16(float2(v.x, 0.0f)), spvPackHalf2x16(float2(v.y, 0.0f)), spvPackHalf2x16(float2(v.z, 0.0f)), spvPackHalf2x16(float2(v.w, 0.0f)));
    return uint2(v16.x | (v16.y << uint(16)), v16.z | (v16.w << uint(16)));
}

uint2 PackFloat4(float3 v3, float v1)
{
    float4 param = float4(v3, v1);
    return PackFloat4(param);
}

void _main(uint3 dtid)
{
    float paramSeed = float(_329_emitter.Seed ^ (_329_emitter.TotalEmitCount + dtid.x));
    float3 position = float3(_329_emitter.Transform[0].w, _329_emitter.Transform[1].w, _329_emitter.Transform[2].w);
    uint _355 = uint(paramSeed);
    uint param = _355;
    float3 param_1 = _362_paramSet.Direction;
    float param_2 = (_362_paramSet.Spread * 3.1415920257568359375f) / 180.0f;
    float3 _376 = RandomSpread(param, param_1, param_2);
    _355 = param;
    float3 direction = _376;
    uint _380 = uint(paramSeed);
    uint param_3 = _380;
    float2 param_4 = _362_paramSet.InitialSpeed;
    float _387 = RandomFloatRange(param_3, param_4);
    _380 = param_3;
    float speed = _387;
    if (_362_paramSet.EmitShapeType == 1u)
    {
        float3 lineStart = mul(_329_emitter.Transform, float4(_362_paramSet.EmitShapeData[0].xyz, 0.0f));
        float3 lineEnd = mul(_329_emitter.Transform, float4(_362_paramSet.EmitShapeData[1].xyz, 0.0f));
        float lineWidth = _362_paramSet.EmitShapeData[1].w;
        uint _426 = uint(paramSeed);
        uint param_5 = _426;
        float _428 = RandomFloat(param_5);
        _426 = param_5;
        position += lerp(lineStart, lineEnd, _428.xxx);
        uint _435 = uint(paramSeed);
        uint param_6 = _435;
        float3 _437 = RandomDirection(param_6);
        _435 = param_6;
        position += ((_437 * lineWidth) * 0.5f);
    }
    else
    {
        if (_362_paramSet.EmitShapeType == 2u)
        {
            float3 circleAxis = mul(_329_emitter.Transform, float4(_362_paramSet.EmitShapeData[0].xyz, 0.0f));
            float circleInner = _362_paramSet.EmitShapeData[1].x;
            float circleOuter = _362_paramSet.EmitShapeData[1].y;
            uint _472 = uint(paramSeed);
            uint param_7 = _472;
            float _474 = RandomFloat(param_7);
            _472 = param_7;
            float circleRadius = lerp(circleInner, circleOuter, _474);
            uint _478 = uint(paramSeed);
            uint param_8 = _478;
            float3 param_9 = circleAxis;
            float3 _482 = RandomCircle(param_8, param_9);
            _478 = param_8;
            position += (_482 * circleRadius);
        }
        else
        {
            if (_362_paramSet.EmitShapeType == 3u)
            {
                float sphereRadius = _362_paramSet.EmitShapeData[0].x;
                uint _498 = uint(paramSeed);
                uint param_10 = _498;
                float3 _500 = RandomDirection(param_10);
                _498 = param_10;
                position += (_500 * sphereRadius);
            }
            else
            {
                if (_362_paramSet.EmitShapeType == 4u)
                {
                    float modelSize = _362_paramSet.EmitShapeData[0].y;
                    if (_329_emitter.EmitPointCount > 0u)
                    {
                        uint _522 = uint(paramSeed);
                        uint param_11 = _522;
                        uint _524 = RandomUint(param_11);
                        _522 = param_11;
                        uint emitIndex = _524 % _329_emitter.EmitPointCount;
                        EmitPoint _540;
                        _540.Position = asfloat(EmitPoints.Load3(emitIndex * 80 + 0));
                        _540.Normal = asfloat(EmitPoints.Load3(emitIndex * 80 + 16));
                        _540.Binormal = asfloat(EmitPoints.Load3(emitIndex * 80 + 32));
                        _540.Tangent = asfloat(EmitPoints.Load3(emitIndex * 80 + 48));
                        _540.UV = asfloat(EmitPoints.Load2(emitIndex * 80 + 64));
                        _540.VColor = EmitPoints.Load(emitIndex * 80 + 72);
                        EmitPoint emitPoint;
                        emitPoint.Position = _540.Position;
                        emitPoint.Normal = _540.Normal;
                        emitPoint.Binormal = _540.Binormal;
                        emitPoint.Tangent = _540.Tangent;
                        emitPoint.UV = _540.UV;
                        emitPoint.VColor = _540.VColor;
                        position += mul(_329_emitter.Transform, float4(emitPoint.Position * modelSize, 0.0f));
                        direction = mul(direction, float3x3(float3(normalize(emitPoint.Tangent)), float3(normalize(emitPoint.Binormal)), float3(normalize(emitPoint.Normal))));
                    }
                }
            }
        }
    }
    direction = mul(_329_emitter.Transform, float4(direction, 0.0f));
    uint particleID = _329_emitter.ParticleHead + ((_329_emitter.TotalEmitCount + dtid.x) % _329_emitter.ParticleSize);
    Particle particle;
    particle.FlagBits = 1u;
    particle.Seed = uint(paramSeed);
    particle.LifeAge = 0.0f;
    if (_362_paramSet.ColorFlags == 0u)
    {
        particle.InheritColor = 4294967295u;
    }
    else
    {
        particle.InheritColor = _329_emitter.Color;
    }
    particle.Color = 4294967295u;
    particle.Padding = 0u;
    particle.Transform = float3x4(float4(float4(1.0f, 0.0f, 0.0f, position.x)), float4(float4(0.0f, 1.0f, 0.0f, position.y)), float4(float4(0.0f, 0.0f, 1.0f, position.z)));
    float3 param_12 = direction * speed;
    float param_13 = 0.0f;
    particle.Velocity = PackFloat4(param_12, param_13);
    Particles.Store(particleID * 80 + 0, particle.FlagBits);
    Particles.Store(particleID * 80 + 4, particle.Seed);
    Particles.Store(particleID * 80 + 8, asuint(particle.LifeAge));
    Particles.Store(particleID * 80 + 12, particle.InheritColor);
    Particles.Store2(particleID * 80 + 16, particle.Velocity);
    Particles.Store(particleID * 80 + 24, particle.Color);
    Particles.Store(particleID * 80 + 28, particle.Padding);
    Particles.Store4(particleID * 80 + 32, asuint(particle.Transform[0]));
    Particles.Store4(particleID * 80 + 48, asuint(particle.Transform[1]));
    Particles.Store4(particleID * 80 + 64, asuint(particle.Transform[2]));
}

void comp_main()
{
    uint3 dtid = gl_GlobalInvocationID;
    uint3 param = dtid;
    _main(param);
}

[numthreads(1, 1, 1)]
void main(SPIRV_Cross_Input stage_input)
{
    gl_GlobalInvocationID = stage_input.gl_GlobalInvocationID;
    comp_main();
}
