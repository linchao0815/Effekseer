#include "gpu_particles_common.h"

cbuffer cb0 : register(b0)
{
    DrawConstants constants;
};
cbuffer cb1 : register(b1)
{
    ParameterSet paramSet;
};
cbuffer cb2 : register(b2)
{
    Emitter emitter;
};

struct VS_Input
{
	float3 Pos : POSITION0;
	float3 Normal : NORMAL0;
	float3 Binormal : NORMAL1;
	float3 Tangent : NORMAL2;
    float2 UV : TEXCOORD0;
    float4 Color : NORMAL3;
    uint InstanceID : SV_InstanceID;
    uint VertexID : SV_VertexID;
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 Color : COLOR0;
	float3 WorldN : TEXCOORD1;
	float3 WorldB : TEXCOORD2;
	float3 WorldT : TEXCOORD3;
};

StructuredBuffer<Particle> Particles : register(t0);
StructuredBuffer<Trail> Trails : register(t1);

void transformSprite(Particle particle, inout float3 position)
{
    // Rotation and Scale Transform
    position = mul(float4(position, 0.0f), particle.Transform);

    // Billboard transform
    if (paramSet.ShapeData == 0) {
        // RotatedBillboard
        position = mul(float4(position, 0.0f), constants.BillboardMat);
    }
    else if (paramSet.ShapeData == 1) {
        // DirectionalBillboard
        float3 R, U, F;
        U = UnpackFloat4(particle.Velocity).xyz;
        if (length(U) < 0.0001f)
        {
            U = float3(0.0f, 1.0f, 0.0f);
        }

        F = constants.CameraFront;
        R = normalize(cross(U, F));
        U = normalize(cross(F, R));
        R = normalize(cross(U, F));
        position = mul(position, float3x3(R, U, F));
    }
    else if (paramSet.ShapeData == 2) {
        // YAxisFixed
        position = mul(float4(position, 0.0f), constants.YAxisFixedMat);
    }

    // Position transform
    position = position + particle.Transform[3];
}

void transformModel(Particle particle, inout float3 position)
{
    // Position and Rotation and Scale Transform
    position = mul(float4(position, 1.0f), particle.Transform).xyz;
}

void transformTrail(Particle particle, inout float3 position, inout float2 uv, uint instanceID, uint vertexID)
{
    // Trail Transform
    uint updateCount = (particle.FlagBits >> 1) & 0xFF;
    uint trailLength = min(paramSet.ShapeData, updateCount);
    float3 trailPosition;
    float3 trailDirection;

    if (vertexID / 2 == 0) {
        trailPosition = particle.Transform[3];
        trailDirection = normalize(UnpackFloat4(particle.Velocity).xyz);
    }
    else {
        uint trailID = emitter.TrailHead + instanceID * paramSet.ShapeData;
        uint trailIndex = min(vertexID / 2, trailLength);
        trailID += (paramSet.ShapeData + emitter.TrailPhase - trailIndex) % paramSet.ShapeData;
        Trail trail = Trails[trailID];
        trailPosition = trail.Position;
        trailDirection = normalize(UnpackNormalizedFloat3(trail.Direction));
        uv.y = float(trailIndex) / float(trailLength);
    }

    float3 trailTangent = normalize(cross(constants.CameraFront, trailDirection));
    position = trailTangent * position.x * paramSet.ShapeSize;
    position += trailPosition;
}

VS_Output main(const VS_Input input)
{
    VS_Output output;
    
    uint index = emitter.ParticleHead + input.InstanceID;
    Particle particle = Particles[index];
    if (particle.FlagBits & 0x01) {
        float3 position = input.Pos;
        float2 uv = input.UV;
        float4 color = input.Color;

        if (paramSet.ShapeType == 0) {
            transformSprite(particle, position);
        } else if (paramSet.ShapeType == 1) {
            transformModel(particle, position);
        } else if (paramSet.ShapeType == 2) {
            transformTrail(particle, position, uv, input.InstanceID, input.VertexID);
        }

        color *= UnpackColor(particle.Color);
        color.rgb *= paramSet.Emissive;
        
        output.Pos = mul(constants.ProjMat, mul(constants.CameraMat, float4(position, 1.0f)));
        output.UV = uv;
        output.Color = color;

        if (paramSet.MaterialType == 1) {
            output.WorldN = mul(float4(input.Normal, 0.0f), particle.Transform).xyz;
            output.WorldB = mul(float4(input.Binormal, 0.0f), particle.Transform).xyz;
            output.WorldT = mul(float4(input.Tangent, 0.0f), particle.Transform).xyz;
        }
    }
    else {
        output.Pos = float4(0.0f, 0.0f, 0.0f, 0.0f);
        output.UV = float2(0.0f, 0.0f);
        output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
        
        if (paramSet.MaterialType == 1) {
            output.WorldN = float3(0.0f, 0.0f, 0.0f);
            output.WorldB = float3(0.0f, 0.0f, 0.0f);
            output.WorldT = float3(0.0f, 0.0f, 0.0f);
        }
    }

    return output;
}
