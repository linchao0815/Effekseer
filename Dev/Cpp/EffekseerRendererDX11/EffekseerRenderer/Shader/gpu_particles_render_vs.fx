#include "gpu_particles_common.h"

cbuffer cb0 : register(b0)
{
    Constants constants;
};
cbuffer cb1 : register(b1)
{
    ParameterSet paramSet;
}
cbuffer cb2 : register(b2)
{
    Emitter emitter;
}

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
};

StructuredBuffer<Particle> Particles : register(t8);
StructuredBuffer<Trail> Trails : register(t9);

VS_Output main(const VS_Input input)
{
    VS_Output output;
    
    uint index = emitter.ParticleHead + input.InstanceID;
    Particle particle = Particles[index];
    if (particle.FlagBits & 0x01) {
        uint paramID = (particle.FlagBits >> 1) & 0x3FF;
        uint updateCount = (particle.FlagBits >> 11) & 0xFF;
        
        float3 position = input.Pos;
        float2 uv = input.UV;
        float4 color = input.Color;

        if (paramSet.ShapeType == 0) {
            // Rotation and Scale Transform
            position = mul(particle.Transform, float4(position, 0.0f));
            // Billboard transform
            if (paramSet.ShapeData == 0) {
                position = mul(constants.BillboardMat, float4(position, 0.0f));
            } else if (paramSet.ShapeData == 1) {
                position = mul(constants.YAxisBillboardMat, float4(position, 0.0f));
            }
            // Position transform
            position = position + particle.Transform._m03_m13_m23;
        } else if (paramSet.ShapeType == 1) {
            // Position and Rotation and Scale Transform
            position = mul(particle.Transform, float4(position, 1.0f)).xyz;
        } else if (paramSet.ShapeType == 2) {
            // Trail Transform
            uint trailLength = min(paramSet.ShapeData, updateCount);
            float3 trailPosition;
            float3 trailDirection;
            if (input.VertexID / 2 == 0) {
                trailPosition = particle.Transform._m03_m13_m23;
                trailDirection = normalize(UnpackFloat4(particle.Velocity).xyz);
            } else {
                uint trailID = emitter.TrailHead + input.InstanceID * paramSet.ShapeData;
                uint trailIndex = min(input.VertexID / 2, trailLength);
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

        color *= UnpackColor(particle.Color);
        color.rgb *= paramSet.Emissive;
        
        output.Pos = mul(constants.ProjMat, mul(constants.CameraMat, float4(position, 1.0f)));
        output.UV = uv;
        output.Color = color;
    }
    else {
        output.Pos = float4(0.0f, 0.0f, 0.0f, 0.0f);
        output.UV = float2(0.0f, 0.0f);
        output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    return output;
}
