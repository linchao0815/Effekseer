
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
    uint flagBits;
    uint seed;
    uint particlesHead;
    uint particlesSize;
};

struct DynamicInput
{
    uint nextEmitCount;
    uint totalEmitCount;
    float3x4 transform;
    float4 color;
};

struct Particle
{
    uint flagBits;
    uint seed;
    float lifeAge;
    uint color;
    float3 position;
    uint2 velocity;
    uint2 rotscale;
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

float deg2rad(float deg) {
    return deg * 3.141592f / 180.0f;
}

uint packColor(float4 color)
{
    uint4 colori = uint4(clamp(color * 255.0f, 0.0, 255.0));
    return colori.r | (colori.g << 8) | (colori.b << 16) | (colori.a << 24);
}

float4 unpackColor(uint color32)
{
    return float4(
        (color32 & 0xFF),
        ((color32 >> 8) & 0xFF),
        ((color32 >> 16) & 0xFF),
        ((color32 >> 24) & 0xFF)) / 255.0f;
}

uint2 packFloat4(float4 v) {
    uint4 v16 = f32tof16(v);
    return uint2(v16.x | (v16.y << 16), v16.z | (v16.w << 16));
}

uint2 packFloat4(float3 v3, float v1) {
    return packFloat4(float4(v3, v1));
}

float4 unpackFloat4(uint2 v) {
    return f16tof32(uint4(v.x, v.x >> 16, v.y, v.y >> 16));
}

float3x3 rotationMatrix(float3 eulerAngles) {
    float3 s, c;
    sincos(eulerAngles, s, c);
    
    float3x3 m;
	m[0][0] = c.z * c.y + s.z * s.x * s.y;
	m[0][1] = s.z * c.x;
	m[0][2] = c.z * -s.y + s.z * s.x * c.y;
	m[1][0] = -s.z * c.y + c.z * s.x * s.y;
	m[1][1] = c.z * c.x;
	m[1][2] = -s.z * -s.y + c.z * s.x * c.y;
	m[2][0] = c.x * s.y;
	m[2][1] = -s.x;
	m[2][2] = c.x * c.y;
    return m;
}

uint randomUint(inout uint seed)
{
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    return seed;
}

float randomFloat(inout uint seed)
{
    return float(randomUint(seed)) / 4294967296.0;
}

float randomUintRange(inout uint seed, uint maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], randomFloat(seed));
}

float randomFloatRange(inout uint seed, float maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], randomFloat(seed));
}

float3 randomFloat3Range(inout uint seed, float3 maxmin[2])
{
    return lerp(maxmin[1], maxmin[0], randomFloat(seed));
}

float4 randomColorRange(inout uint seed, uint maxmin[2])
{
    return lerp(unpackColor(maxmin[1]), unpackColor(maxmin[0]), randomFloat(seed));
}

float3 spreadDir(inout uint seed, float3 baseDir, float angle)
{
    float theta = 2.0 * 3.14159 * randomFloat(seed);
    float phi = angle * randomFloat(seed);

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
