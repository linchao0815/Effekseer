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

cbuffer cb2 : register(b2)
{
    Emitter _88_emitter : packoffset(c0);
};

RWByteAddressBuffer Particles : register(u0);
cbuffer cb0 : register(b0)
{
    Constants _161_constants : packoffset(c0);
};

cbuffer cb1 : register(b1)
{
    ParameterSet _168_paramSet : packoffset(c0);
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
    uint particleID = _88_emitter.ParticleHead + dtid.x;
    Particle particle;
    particle.FlagBits = 0u;
    particle.Seed = 0u;
    particle.LifeAge = 0.0f;
    particle.InheritColor = 0u;
    particle.Color = 0u;
    particle.Padding = 0u;
    float3 param = 0.0f.xxx;
    float param_1 = 0.0f;
    particle.Velocity = PackFloat4(param, param_1);
    particle.Transform = float3x4(0.0f.xxxx, 0.0f.xxxx, 0.0f.xxxx);
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

[numthreads(256, 1, 1)]
void main(SPIRV_Cross_Input stage_input)
{
    gl_GlobalInvocationID = stage_input.gl_GlobalInvocationID;
    comp_main();
}
