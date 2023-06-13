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

struct Trail
{
    float3 Position;
    uint Direction;
};

cbuffer cb2 : register(b2)
{
    Emitter _540_emitter : packoffset(c0);
};

RWByteAddressBuffer Particles : register(u0);
cbuffer cb0 : register(b0)
{
    Constants _595_constants : packoffset(c0);
};

cbuffer cb1 : register(b1)
{
    ParameterSet _609_paramSet : packoffset(c0);
};

RWByteAddressBuffer Trails : register(u1);
Texture3D<float4> NoiseVFTex : register(t2);
SamplerState NoiseVFSamp : register(s2);

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
    uint _443 = RandomUint(param);
    seed = param;
    return float(_443) / 4294967296.0f;
}

float RandomFloatRange(inout uint seed, float2 maxmin)
{
    uint param = seed;
    float _456 = RandomFloat(param);
    seed = param;
    return lerp(maxmin.y, maxmin.x, _456);
}

float4 RandomFloat4Range(inout uint seed, float4 maxmin[2])
{
    uint param = seed;
    float _467 = RandomFloat(param);
    seed = param;
    return lerp(maxmin[1], maxmin[0], _467.xxxx);
}

float4 UnpackColor(uint color32)
{
    return float4(float(color32 & 255u), float((color32 >> uint(8)) & 255u), float((color32 >> uint(16)) & 255u), float((color32 >> uint(24)) & 255u)) / 255.0f.xxxx;
}

float4 RandomColorRange(inout uint seed, uint2 maxmin)
{
    uint param = maxmin.y;
    uint param_1 = maxmin.x;
    uint param_2 = seed;
    float _483 = RandomFloat(param_2);
    seed = param_2;
    return lerp(UnpackColor(param), UnpackColor(param_1), _483.xxxx);
}

float4 UnpackFloat4(uint2 bits)
{
    return float4(spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).x).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).y).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).z).x, spvUnpackHalf2x16(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).w).x);
}

uint PackNormalizedFloat3(float3 v)
{
    uint3 i = uint3(((v + 1.0f.xxx) * 0.5f) * 1023.0f);
    return (i.x | (i.y << uint(10))) | (i.z << uint(20));
}

float3 Vortex(float rotation, float attraction, inout float3 center, inout float3 axis, float3 position, float4x3 transform)
{
    center = transform[3] + center;
    axis = normalize(mul(float4(axis, 0.0f), transform));
    float3 diff = position - center;
    float _distance = length(diff);
    if (_distance == 0.0f)
    {
        return 0.0f.xxx;
    }
    float3 radial = diff / _distance.xxx;
    float3 tangent = cross(axis, radial);
    radial = cross(tangent, axis);
    return (tangent * rotation) - (radial * attraction);
}

float4x3 TRSMatrix(float3 translation, float3 rotation, float3 scale)
{
    float3 s = sin(rotation);
    float3 c = cos(rotation);
    float4x3 m;
    m[0].x = scale.x * ((c.z * c.y) + ((s.z * s.x) * s.y));
    m[1].x = scale.y * (s.z * c.x);
    m[2].x = scale.z * ((c.z * (-s.y)) + ((s.z * s.x) * c.y));
    m[3].x = translation.x;
    m[0].y = scale.x * (((-s.z) * c.y) + ((c.z * s.x) * s.y));
    m[1].y = scale.y * (c.z * c.x);
    m[2].y = scale.z * (((-s.z) * (-s.y)) + ((c.z * s.x) * c.y));
    m[3].y = translation.y;
    m[0].z = scale.x * (c.x * s.y);
    m[1].z = scale.y * (-s.x);
    m[2].z = scale.z * (c.x * c.y);
    m[3].z = translation.z;
    return m;
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

uint PackColor(float4 color)
{
    uint4 colori = uint4(clamp(color * 255.0f, 0.0f.xxxx, 255.0f.xxxx));
    return ((colori.x | (colori.y << uint(8))) | (colori.z << uint(16))) | (colori.w << uint(24));
}

void _main(uint3 dtid)
{
    uint particleID = _540_emitter.ParticleHead + dtid.x;
    Particle _558;
    _558.FlagBits = Particles.Load(particleID * 80 + 0);
    _558.Seed = Particles.Load(particleID * 80 + 4);
    _558.LifeAge = asfloat(Particles.Load(particleID * 80 + 8));
    _558.InheritColor = Particles.Load(particleID * 80 + 12);
    _558.Velocity = Particles.Load2(particleID * 80 + 16);
    _558.Color = Particles.Load(particleID * 80 + 24);
    _558.Padding = Particles.Load(particleID * 80 + 28);
    _558.Transform = asfloat(uint4x3(Particles.Load(particleID * 80 + 32), Particles.Load(particleID * 80 + 48), Particles.Load(particleID * 80 + 64), Particles.Load(particleID * 80 + 36), Particles.Load(particleID * 80 + 52), Particles.Load(particleID * 80 + 68), Particles.Load(particleID * 80 + 40), Particles.Load(particleID * 80 + 56), Particles.Load(particleID * 80 + 72), Particles.Load(particleID * 80 + 44), Particles.Load(particleID * 80 + 60), Particles.Load(particleID * 80 + 76)));
    Particle particle;
    particle.FlagBits = _558.FlagBits;
    particle.Seed = _558.Seed;
    particle.LifeAge = _558.LifeAge;
    particle.InheritColor = _558.InheritColor;
    particle.Velocity = _558.Velocity;
    particle.Color = _558.Color;
    particle.Padding = _558.Padding;
    particle.Transform = _558.Transform;
    if ((particle.FlagBits & 1u) != 0u)
    {
        uint updateCount = (particle.FlagBits >> uint(1)) & 255u;
        float deltaTime = _595_constants.DeltaTime;
        uint seed = particle.Seed;
        uint param = seed;
        float2 param_1 = _609_paramSet.LifeTime;
        float _616 = RandomFloatRange(param, param_1);
        seed = param;
        float lifeTime = _616;
        float lifeRatio = particle.LifeAge / lifeTime;
        uint param_2 = seed;
        float2 param_3 = _609_paramSet.Damping;
        float _630 = RandomFloatRange(param_2, param_3);
        seed = param_2;
        float damping = _630 * 0.00999999977648258209228515625f;
        uint param_4 = seed;
        float4 param_5[2];
        param_5[0] = _609_paramSet.InitialAngleScale[0];
        param_5[1] = _609_paramSet.InitialAngleScale[1];
        float4 _646 = RandomFloat4Range(param_4, param_5);
        seed = param_4;
        float4 initialAngleScale = _646;
        uint param_6 = seed;
        float4 param_7[2];
        param_7[0] = _609_paramSet.TargetAngleScale[0];
        param_7[1] = _609_paramSet.TargetAngleScale[1];
        float4 _660 = RandomFloat4Range(param_6, param_7);
        seed = param_6;
        float4 targetAngleScale = _660;
        float3 initialAngle = initialAngleScale.xyz;
        float3 angularVelocity = targetAngleScale.xyz;
        float initialScale = initialAngleScale.w;
        float terminalScale = targetAngleScale.w;
        uint param_8 = seed;
        uint2 param_9 = _609_paramSet.ColorStart;
        float4 _682 = RandomColorRange(param_8, param_9);
        seed = param_8;
        float4 colorStart = _682;
        uint param_10 = seed;
        uint2 param_11 = _609_paramSet.ColorEnd;
        float4 _691 = RandomColorRange(param_10, param_11);
        seed = param_10;
        float4 colorEnd = _691;
        float3 position = particle.Transform[3];
        uint2 param_12 = particle.Velocity;
        float3 velocity = UnpackFloat4(param_12).xyz;
        if (_540_emitter.TrailSize > 0u)
        {
            uint trailID = (_540_emitter.TrailHead + (dtid.x * _609_paramSet.ShapeData)) + _540_emitter.TrailPhase;
            Trail trail;
            trail.Position = position;
            float3 param_13 = velocity;
            trail.Direction = PackNormalizedFloat3(param_13);
            Trails.Store3(trailID * 16 + 0, asuint(trail.Position));
            Trails.Store(trailID * 16 + 12, trail.Direction);
        }
        particle.FlagBits &= 4294966785u;
        particle.FlagBits |= (clamp(updateCount + 1u, 0u, 255u) << uint(1));
        particle.LifeAge += _595_constants.DeltaTime;
        if (particle.LifeAge >= lifeTime)
        {
            particle.FlagBits &= 4294967294u;
        }
        velocity += (_609_paramSet.Gravity * deltaTime);
        if ((_609_paramSet.VortexRotation != 0.0f) || (_609_paramSet.VortexAttraction != 0.0f))
        {
            float param_14 = _609_paramSet.VortexRotation;
            float param_15 = _609_paramSet.VortexAttraction;
            float3 param_16 = _609_paramSet.VortexCenter;
            float3 param_17 = _609_paramSet.VortexAxis;
            float3 param_18 = position;
            float4x3 param_19 = _540_emitter.Transform;
            float3 _810 = Vortex(param_14, param_15, param_16, param_17, param_18, param_19);
            velocity += (_810 * deltaTime);
        }
        if (_609_paramSet.TurbulencePower != 0.0f)
        {
            float4 vfTexel = NoiseVFTex.SampleLevel(NoiseVFSamp, (position / 8.0f.xxx) + 0.5f.xxx, 0.0f);
            velocity += ((((vfTexel.xyz * 2.0f) - 1.0f.xxx) * _609_paramSet.TurbulencePower) * deltaTime);
        }
        float speed = length(velocity);
        if (speed > 0.0f)
        {
            float newSpeed = max(0.0f, speed - (damping * deltaTime));
            velocity *= (newSpeed / speed);
        }
        position += (velocity * _595_constants.DeltaTime);
        float3 rotation = initialAngle + (angularVelocity * particle.LifeAge);
        float scale = lerp(initialScale, terminalScale, lifeRatio) * _609_paramSet.ShapeSize;
        float4 color = lerp(colorStart, colorEnd, lifeRatio.xxxx);
        if ((_609_paramSet.ColorFlags == 2u) || (_609_paramSet.ColorFlags == 3u))
        {
            uint param_20 = _540_emitter.Color;
            color *= UnpackColor(param_20);
        }
        else
        {
            uint param_21 = particle.InheritColor;
            color *= UnpackColor(param_21);
        }
        color.w *= clamp(particle.LifeAge / _609_paramSet.FadeIn, 0.0f, 1.0f);
        color.w *= clamp((lifeTime - particle.LifeAge) / _609_paramSet.FadeOut, 0.0f, 1.0f);
        float3 param_22 = position;
        float3 param_23 = rotation;
        float3 param_24 = float3(scale, scale, scale);
        particle.Transform = TRSMatrix(param_22, param_23, param_24);
        float3 param_25 = velocity;
        float param_26 = 0.0f;
        particle.Velocity = PackFloat4(param_25, param_26);
        float4 param_27 = color;
        particle.Color = PackColor(param_27);
        Particles.Store(particleID * 80 + 0, particle.FlagBits);
        Particles.Store(particleID * 80 + 4, particle.Seed);
        Particles.Store(particleID * 80 + 8, asuint(particle.LifeAge));
        Particles.Store(particleID * 80 + 12, particle.InheritColor);
        Particles.Store2(particleID * 80 + 16, particle.Velocity);
        Particles.Store(particleID * 80 + 24, particle.Color);
        Particles.Store(particleID * 80 + 28, particle.Padding);
        Particles.Store(particleID * 80 + 32, asuint(particle.Transform[0].x));
        Particles.Store(particleID * 80 + 36, asuint(particle.Transform[1].x));
        Particles.Store(particleID * 80 + 40, asuint(particle.Transform[2].x));
        Particles.Store(particleID * 80 + 44, asuint(particle.Transform[3].x));
        Particles.Store(particleID * 80 + 48, asuint(particle.Transform[0].y));
        Particles.Store(particleID * 80 + 52, asuint(particle.Transform[1].y));
        Particles.Store(particleID * 80 + 56, asuint(particle.Transform[2].y));
        Particles.Store(particleID * 80 + 60, asuint(particle.Transform[3].y));
        Particles.Store(particleID * 80 + 64, asuint(particle.Transform[0].z));
        Particles.Store(particleID * 80 + 68, asuint(particle.Transform[1].z));
        Particles.Store(particleID * 80 + 72, asuint(particle.Transform[2].z));
        Particles.Store(particleID * 80 + 76, asuint(particle.Transform[3].z));
    }
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
