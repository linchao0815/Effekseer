
struct ParameterSet
{
    uint EmitCount;
    uint LifeTime[2];
    float EmitOffset[2];
    float EmitInterval[2];

    float3 Direction;
    float Spread;
    float InitialSpeed[2];
    float Damping[2];

    float3 InitialAngle[2];
    float3 AngularVelocity[2];
    
    float InitialScale[2];
    float TerminalScale[2];

    float3 Gravity;
    float VortexRotation;
    float VortexAttraction;
    float3 VortexCenter;
    float3 VortexAxis;
    float TurbulencePower;
    uint TurbulenceSeed;
    float TurbulenceScale;
    float TurbulenceOctave;

    uint RenderState;
    uint ShapeType;
    uint ShapeData;
    float ShapeSize;

    uint ColorFlags;
    uint ColorStart[2];
    uint ColorEnd[2];
    float Emissive;
    float FadeIn;
    float FadeOut;

    uint ColorTexIndex;
    uint NormalTexIndex;
    uint TexState;
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
};

struct DynamicInput
{
    uint NextEmitCount;
    uint TotalEmitCount;
    float3x4 Transform;
    float4 Color;
};

struct Particle
{
    uint FlagBits;
    uint Seed;
    float LifeAge;
    uint InheritColor;
    uint Color;
    uint2 Velocity;
    float3x4 Transform;
};

struct Trail
{
    float3 Position;
    uint Direction;
};

struct Constants
{
    float4x4 ProjMat;
    float4x4 CameraMat;
    float3x3 BillboardMat;
    float3x3 YAxisBillboardMat;
    float3 CameraPos;
    float DeltaTime;
    float3 CameraFront;
    float Reserved;
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

float3x4 TRSMatrix(float3 translation, float3 rotation, float3 scale) {
    float3 s, c;
    sincos(rotation, s, c);
    
    float3x4 m;
	m[0][0] = scale.x * (c.z * c.y + s.z * s.x * s.y);
	m[0][1] = scale.y * (s.z * c.x);
	m[0][2] = scale.z * (c.z * -s.y + s.z * s.x * c.y);
    m[0][3] = translation.x;
	m[1][0] = scale.x * (-s.z * c.y + c.z * s.x * s.y);
	m[1][1] = scale.y * (c.z * c.x);
	m[1][2] = scale.z * (-s.z * -s.y + c.z * s.x * c.y);
    m[1][3] = translation.y;
	m[2][0] = scale.x * (c.x * s.y);
	m[2][1] = scale.y * (-s.x);
	m[2][2] = scale.z * (c.x * c.y);
    m[2][3] = translation.z;
    return m;
}

uint RandomUint(inout uint seed)
{
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    return seed;
}

float RandomFloat(inout uint seed)
{
    return float(RandomUint(seed)) / 4294967296.0;
}

float RandomUintRange(inout uint seed, uint maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], RandomFloat(seed));
}

float RandomFloatRange(inout uint seed, float maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], RandomFloat(seed));
}

float3 RandomFloat3Range(inout uint seed, float3 maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], RandomFloat(seed));
}

float4 RandomColorRange(inout uint seed, uint maxmin[2])
{
    return lerp(UnpackColor(maxmin[1]), UnpackColor(maxmin[0]), RandomFloat(seed));
}

float3 SpreadDir(inout uint seed, float3 baseDir, float angle)
{
    float theta = 2.0 * 3.14159 * RandomFloat(seed);
    float phi = angle * RandomFloat(seed);

    float3 randDir = float3(
        sin(phi) * cos(theta),
        sin(phi) * sin(theta),
        cos(phi));

    baseDir = normalize(baseDir);
    if (abs(baseDir.z) != 1.0) {
        float3 up = float3(0, 0, 1);
        float3 right = normalize(cross(up, baseDir));
        up = cross(baseDir, right);
        return mul(randDir, float3x3(right, up, baseDir));
    }
    else {
        return randDir * sign(baseDir.z);
    }
}
