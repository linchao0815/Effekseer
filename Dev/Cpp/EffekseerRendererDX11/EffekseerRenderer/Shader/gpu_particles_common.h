
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
    float4x3 Transform;
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
    float4x3 Transform;
};

struct Trail
{
    float3 Position;
    uint Direction;
};

struct Constants
{
    float3 CameraPos;
    float DeltaTime;
    float3 CameraFront;
    float Reserved;
    float4x4 ProjMat;
    float4x4 CameraMat;
    float4x3 BillboardMat;
    float4x3 YAxisBillboardMat;
};

uint PackColor(float4 color)
{
    uint4 colori = uint4(clamp(color * 255.0f, 0.0, 255.0));
    return colori.r | (colori.g << 8) | (colori.b << 16) | (colori.a << 24);
}

float4 UnpackColor(uint color32)
{
    return float4(
        (color32 & 0xFF),
        ((color32 >> 8) & 0xFF),
        ((color32 >> 16) & 0xFF),
        ((color32 >> 24) & 0xFF)) / 255.0f;
}

uint2 PackFloat4(float4 v) {
    uint4 v16 = f32tof16(v);
    return uint2(v16.x | (v16.y << 16), v16.z | (v16.w << 16));
}

uint2 PackFloat4(float3 v3, float v1) {
    return PackFloat4(float4(v3, v1));
}

float4 UnpackFloat4(uint2 bits) {
    return f16tof32(uint4(bits.x, bits.x >> 16, bits.y, bits.y >> 16));
}

float PackNormalizedFloat3(float3 v) {
	uint3 i = uint3((v + 1.0f) * 0.5f * 1023.0f);
	return i.x | (i.y << 10) | (i.z << 20);
}

float3 UnpackNormalizedFloat3(uint bits) {
	float3 v = float3(uint3(bits, bits >> 10, bits >> 20) & 1023);
	return v / 1023.0f * 2.0f - 1.0f;
}

float4x3 TRSMatrix(float3 translation, float3 rotation, float3 scale) {
    float3 s, c;
    sincos(rotation, s, c);
    
    float4x3 m;
	m[0][0] = scale.x * (c.z * c.y + s.z * s.x * s.y);
	m[1][0] = scale.y * (s.z * c.x);
	m[2][0] = scale.z * (c.z * -s.y + s.z * s.x * c.y);
    m[3][0] = translation.x;
	m[0][1] = scale.x * (-s.z * c.y + c.z * s.x * s.y);
	m[1][1] = scale.y * (c.z * c.x);
	m[2][1] = scale.z * (-s.z * -s.y + c.z * s.x * c.y);
    m[3][1] = translation.y;
	m[0][2] = scale.x * (c.x * s.y);
	m[1][2] = scale.y * (-s.x);
	m[2][2] = scale.z * (c.x * c.y);
    m[3][2] = translation.z;
    return m;
}

uint RandomUint(inout uint seed)
{
    uint state = seed;
    seed = seed * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

float RandomFloat(inout uint seed)
{
    return float(RandomUint(seed)) / 4294967296.0;
}

float RandomUintRange(inout uint seed, uint2 maxmin)
{
    return lerp(maxmin.y, maxmin.x, RandomFloat(seed));
}

float RandomFloatRange(inout uint seed, float2 maxmin)
{
    return lerp(maxmin.y, maxmin.x, RandomFloat(seed));
}

float4 RandomFloat4Range(inout uint seed, float4 maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], RandomFloat(seed));
}

float4 RandomColorRange(inout uint seed, uint2 maxmin)
{
    return lerp(UnpackColor(maxmin.y), UnpackColor(maxmin.x), RandomFloat(seed));
}

float3 RandomDirection(inout uint seed)
{
    float theta = 2.0f * 3.14159f * RandomFloat(seed);
    float phi = 2.0f * 3.14159f * RandomFloat(seed);

    float3 randDir = float3(
        sin(phi) * cos(theta),
        sin(phi) * sin(theta),
        cos(phi));

    return randDir;
}

float3 RandomCircle(inout uint seed, float3 axis)
{
    float theta = 2.0f * 3.14159f * RandomFloat(seed);

    float3 randDir = float3(cos(theta), 0.0f, sin(theta));

    axis = normalize(axis);
    if (abs(axis.y) != 1.0f) {
        float3 up = float3(0.0f, 1.0f, 0.0f);
        float3 right = normalize(cross(up, axis));
        float3 front = cross(axis, right);
        return mul(randDir, float3x3(right, axis, front));
    }
    else {
        return randDir * sign(axis.y);
    }
    return randDir;
}

float3 RandomSpread(inout uint seed, float3 baseDir, float angle)
{
    float theta = 2.0f * 3.14159f * RandomFloat(seed);
    float phi = angle * RandomFloat(seed);

    float3 randDir = float3(
        sin(phi) * cos(theta),
        sin(phi) * sin(theta),
        cos(phi));

    baseDir = normalize(baseDir);
    if (abs(baseDir.z) != 1.0) {
        float3 front = float3(0.0f, 0.0f, 1.0f);
        float3 right = normalize(cross(front, baseDir));
        float3 up = cross(baseDir, right);
        return mul(randDir, float3x3(right, up, baseDir));
    }
    else {
        return randDir * sign(baseDir.z);
    }
}
