#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wmissing-braces"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

template<typename T, size_t Num>
struct spvUnsafeArray
{
    T elements[Num ? Num : 1];
    
    thread T& operator [] (size_t pos) thread
    {
        return elements[pos];
    }
    constexpr const thread T& operator [] (size_t pos) const thread
    {
        return elements[pos];
    }
    
    device T& operator [] (size_t pos) device
    {
        return elements[pos];
    }
    constexpr const device T& operator [] (size_t pos) const device
    {
        return elements[pos];
    }
    
    constexpr const constant T& operator [] (size_t pos) const constant
    {
        return elements[pos];
    }
    
    threadgroup T& operator [] (size_t pos) threadgroup
    {
        return elements[pos];
    }
    constexpr const threadgroup T& operator [] (size_t pos) const threadgroup
    {
        return elements[pos];
    }
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

static inline __attribute__((always_inline))
uint RandomUint(thread uint& seed)
{
    uint state = seed;
    seed = (seed * 747796405u) + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

static inline __attribute__((always_inline))
float RandomFloat(thread uint& seed)
{
    uint param = seed;
    uint _443 = RandomUint(param);
    seed = param;
    return float(_443) / 4294967296.0;
}

static inline __attribute__((always_inline))
float RandomFloatRange(thread uint& seed, thread const float2& maxmin)
{
    uint param = seed;
    float _456 = RandomFloat(param);
    seed = param;
    return mix(maxmin.y, maxmin.x, _456);
}

static inline __attribute__((always_inline))
float4 RandomFloat4Range(thread uint& seed, thread const spvUnsafeArray<float4, 2>& maxmin)
{
    uint param = seed;
    float _467 = RandomFloat(param);
    seed = param;
    return mix(maxmin[1], maxmin[0], float4(_467));
}

static inline __attribute__((always_inline))
float4 UnpackColor(thread const uint& color32)
{
    return float4(float(color32 & 255u), float((color32 >> uint(8)) & 255u), float((color32 >> uint(16)) & 255u), float((color32 >> uint(24)) & 255u)) / float4(255.0);
}

static inline __attribute__((always_inline))
float4 RandomColorRange(thread uint& seed, thread const uint2& maxmin)
{
    uint param = maxmin.y;
    uint param_1 = maxmin.x;
    uint param_2 = seed;
    float _483 = RandomFloat(param_2);
    seed = param_2;
    return mix(UnpackColor(param), UnpackColor(param_1), float4(_483));
}

static inline __attribute__((always_inline))
float4 UnpackFloat4(thread const uint2& bits)
{
    return float4(float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).x)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).y)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).z)).x, float2(as_type<half2>(uint4(bits.x, bits.x >> uint(16), bits.y, bits.y >> uint(16)).w)).x);
}

static inline __attribute__((always_inline))
uint PackNormalizedFloat3(thread const float3& v)
{
    uint3 i = uint3(((v + float3(1.0)) * 0.5) * 1023.0);
    return (i.x | (i.y << uint(10))) | (i.z << uint(20));
}

static inline __attribute__((always_inline))
float3 Vortex(thread const float& rotation, thread const float& attraction, thread float3& center, thread float3& axis, thread const float3& position, thread const float4x3& transform)
{
    center = transform[3] + center;
    axis = fast::normalize(transform * float4(axis, 0.0));
    float3 diff = position - center;
    float _distance = length(diff);
    if (_distance == 0.0)
    {
        return float3(0.0);
    }
    float3 radial = diff / float3(_distance);
    float3 tangent = cross(axis, radial);
    radial = cross(tangent, axis);
    return (tangent * rotation) - (radial * attraction);
}

static inline __attribute__((always_inline))
float4x3 TRSMatrix(thread const float3& translation, thread const float3& rotation, thread const float3& scale)
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

static inline __attribute__((always_inline))
uint2 PackFloat4(thread const float4& v)
{
    uint4 v16 = uint4(as_type<uint>(half2(float2(v.x, 0.0))), as_type<uint>(half2(float2(v.y, 0.0))), as_type<uint>(half2(float2(v.z, 0.0))), as_type<uint>(half2(float2(v.w, 0.0))));
    return uint2(v16.x | (v16.y << uint(16)), v16.z | (v16.w << uint(16)));
}

static inline __attribute__((always_inline))
uint2 PackFloat4(thread const float3& v3, thread const float& v1)
{
    float4 param = float4(v3, v1);
    return PackFloat4(param);
}

static inline __attribute__((always_inline))
uint PackColor(thread const float4& color)
{
    uint4 colori = uint4(fast::clamp(color * 255.0, float4(0.0), float4(255.0)));
    return ((colori.x | (colori.y << uint(8))) | (colori.z << uint(16))) | (colori.w << uint(24));
}

static inline __attribute__((always_inline))
void _main(thread const uint3& dtid, constant cb2& _540, device Particles& Particles_1, constant cb0& _595, constant cb1& _609, device Trails& Trails_1, texture3d<float> NoiseVFTex, sampler NoiseVFSamp)
{
    uint particleID = _540.emitter.ParticleHead + dtid.x;
    Particle particle;
    particle.FlagBits = Particles_1._data[particleID].FlagBits;
    particle.Seed = Particles_1._data[particleID].Seed;
    particle.LifeAge = Particles_1._data[particleID].LifeAge;
    particle.InheritColor = Particles_1._data[particleID].InheritColor;
    particle.Velocity = Particles_1._data[particleID].Velocity;
    particle.Color = Particles_1._data[particleID].Color;
    particle.Padding = Particles_1._data[particleID].Padding;
    particle.Transform = transpose(Particles_1._data[particleID].Transform);
    if ((particle.FlagBits & 1u) != 0u)
    {
        uint updateCount = (particle.FlagBits >> uint(1)) & 255u;
        float deltaTime = _595.constants.DeltaTime;
        uint seed = particle.Seed;
        uint param = seed;
        float2 param_1 = _609.paramSet.LifeTime;
        float _616 = RandomFloatRange(param, param_1);
        seed = param;
        float lifeTime = _616;
        float lifeRatio = particle.LifeAge / lifeTime;
        uint param_2 = seed;
        float2 param_3 = _609.paramSet.Damping;
        float _630 = RandomFloatRange(param_2, param_3);
        seed = param_2;
        float damping = _630 * 0.00999999977648258209228515625;
        uint param_4 = seed;
        spvUnsafeArray<float4, 2> param_5;
        param_5[0] = _609.paramSet.InitialAngleScale[0];
        param_5[1] = _609.paramSet.InitialAngleScale[1];
        float4 _646 = RandomFloat4Range(param_4, param_5);
        seed = param_4;
        float4 initialAngleScale = _646;
        uint param_6 = seed;
        spvUnsafeArray<float4, 2> param_7;
        param_7[0] = _609.paramSet.TargetAngleScale[0];
        param_7[1] = _609.paramSet.TargetAngleScale[1];
        float4 _660 = RandomFloat4Range(param_6, param_7);
        seed = param_6;
        float4 targetAngleScale = _660;
        float3 initialAngle = initialAngleScale.xyz;
        float3 angularVelocity = targetAngleScale.xyz;
        float initialScale = initialAngleScale.w;
        float terminalScale = targetAngleScale.w;
        uint param_8 = seed;
        uint2 param_9 = _609.paramSet.ColorStart;
        float4 _682 = RandomColorRange(param_8, param_9);
        seed = param_8;
        float4 colorStart = _682;
        uint param_10 = seed;
        uint2 param_11 = _609.paramSet.ColorEnd;
        float4 _691 = RandomColorRange(param_10, param_11);
        seed = param_10;
        float4 colorEnd = _691;
        float3 position = particle.Transform[3];
        uint2 param_12 = particle.Velocity;
        float3 velocity = UnpackFloat4(param_12).xyz;
        if (_540.emitter.TrailSize > 0u)
        {
            uint trailID = (_540.emitter.TrailHead + (dtid.x * _609.paramSet.ShapeData)) + _540.emitter.TrailPhase;
            Trail trail;
            trail.Position = position;
            float3 param_13 = velocity;
            trail.Direction = PackNormalizedFloat3(param_13);
            Trails_1._data[trailID].Position = trail.Position;
            Trails_1._data[trailID].Direction = trail.Direction;
        }
        particle.FlagBits &= 4294966785u;
        particle.FlagBits |= (clamp(updateCount + 1u, 0u, 255u) << uint(1));
        particle.LifeAge += _595.constants.DeltaTime;
        if (particle.LifeAge >= lifeTime)
        {
            particle.FlagBits &= 4294967294u;
        }
        velocity += (float3(_609.paramSet.Gravity) * deltaTime);
        if ((_609.paramSet.VortexRotation != 0.0) || (_609.paramSet.VortexAttraction != 0.0))
        {
            float param_14 = _609.paramSet.VortexRotation;
            float param_15 = _609.paramSet.VortexAttraction;
            float3 param_16 = float3(_609.paramSet.VortexCenter);
            float3 param_17 = float3(_609.paramSet.VortexAxis);
            float3 param_18 = position;
            float4x3 param_19 = transpose(_540.emitter.Transform);
            float3 _810 = Vortex(param_14, param_15, param_16, param_17, param_18, param_19);
            velocity += (_810 * deltaTime);
        }
        if (_609.paramSet.TurbulencePower != 0.0)
        {
            float4 vfTexel = NoiseVFTex.sample(NoiseVFSamp, ((position / float3(8.0)) + float3(0.5)), level(0.0));
            velocity += ((((vfTexel.xyz * 2.0) - float3(1.0)) * _609.paramSet.TurbulencePower) * deltaTime);
        }
        float speed = length(velocity);
        if (speed > 0.0)
        {
            float newSpeed = fast::max(0.0, speed - (damping * deltaTime));
            velocity *= (newSpeed / speed);
        }
        position += (velocity * _595.constants.DeltaTime);
        float3 rotation = initialAngle + (angularVelocity * particle.LifeAge);
        float scale = mix(initialScale, terminalScale, lifeRatio) * _609.paramSet.ShapeSize;
        float4 color = mix(colorStart, colorEnd, float4(lifeRatio));
        if ((_609.paramSet.ColorFlags == 2u) || (_609.paramSet.ColorFlags == 3u))
        {
            uint param_20 = _540.emitter.Color;
            color *= UnpackColor(param_20);
        }
        else
        {
            uint param_21 = particle.InheritColor;
            color *= UnpackColor(param_21);
        }
        color.w *= fast::clamp(particle.LifeAge / _609.paramSet.FadeIn, 0.0, 1.0);
        color.w *= fast::clamp((lifeTime - particle.LifeAge) / _609.paramSet.FadeOut, 0.0, 1.0);
        float3 param_22 = position;
        float3 param_23 = rotation;
        float3 param_24 = float3(scale, scale, scale);
        particle.Transform = TRSMatrix(param_22, param_23, param_24);
        float3 param_25 = velocity;
        float param_26 = 0.0;
        particle.Velocity = PackFloat4(param_25, param_26);
        float4 param_27 = color;
        particle.Color = PackColor(param_27);
        Particles_1._data[particleID].FlagBits = particle.FlagBits;
        Particles_1._data[particleID].Seed = particle.Seed;
        Particles_1._data[particleID].LifeAge = particle.LifeAge;
        Particles_1._data[particleID].InheritColor = particle.InheritColor;
        Particles_1._data[particleID].Velocity = particle.Velocity;
        Particles_1._data[particleID].Color = particle.Color;
        Particles_1._data[particleID].Padding = particle.Padding;
        Particles_1._data[particleID].Transform = transpose(particle.Transform);
    }
}

kernel void main0(constant cb0& _595 [[buffer(0)]], constant cb1& _609 [[buffer(1)]], constant cb2& _540 [[buffer(2)]], device Particles& Particles_1 [[buffer(10)]], device Trails& Trails_1 [[buffer(11)]], texture3d<float> NoiseVFTex [[texture(2)]], sampler NoiseVFSamp [[sampler(2)]], uint3 gl_GlobalInvocationID [[thread_position_in_grid]])
{
    uint3 dtid = gl_GlobalInvocationID;
    uint3 param = dtid;
    _main(param, _540, Particles_1, _595, _609, Trails_1, NoiseVFTex, NoiseVFSamp);
}

