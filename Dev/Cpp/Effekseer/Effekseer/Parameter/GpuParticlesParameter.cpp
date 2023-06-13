#include "GpuParticlesParameter.h"

namespace Effekseer
{

GpuParticles::ParameterSet LoadGpuParticlesParameter(uint8_t*& pos, int32_t version)
{
	GpuParticles::ParameterSet paramSet{};

	memcpy(&paramSet.EmitCount, pos, sizeof(int32_t));
	pos += sizeof(int32_t);
	memcpy(&paramSet.EmitPerFrame, pos, sizeof(int32_t));
	pos += sizeof(int32_t);
	memcpy(&paramSet.EmitOffset, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.LifeTime, pos, sizeof(float) * 2);
	pos += sizeof(float) * 2;

	memcpy(&paramSet.EmitShapeType, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	switch (paramSet.EmitShapeType)
	{
	case GpuParticles::EmitShape::Point:
		break;
	case GpuParticles::EmitShape::Line:
		memcpy(&paramSet.EmitShapeData.LineStart, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.LineEnd, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.LineWidth, pos, sizeof(float));
		pos += sizeof(float);
		break;
	case GpuParticles::EmitShape::Circle:
		memcpy(&paramSet.EmitShapeData.CircleAxis, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.CircleInner, pos, sizeof(float));
		pos += sizeof(float);
		memcpy(&paramSet.EmitShapeData.CircleOuter, pos, sizeof(float));
		pos += sizeof(float);
		break;
	case GpuParticles::EmitShape::Sphere:
		memcpy(&paramSet.EmitShapeData.SphereRadius, pos, sizeof(float));
		pos += sizeof(float);
		break;
	case GpuParticles::EmitShape::Model:
		memcpy(&paramSet.EmitShapeData.ModelIndex, pos, sizeof(int32_t));
		pos += sizeof(int32_t);
		memcpy(&paramSet.EmitShapeData.ModelSize, pos, sizeof(float));
		pos += sizeof(float);
		break;
	}

	memcpy(&paramSet.Direction, pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.Spread, pos, sizeof(float) * 2);
	pos += sizeof(float);
	memcpy(&paramSet.InitialSpeed, pos, sizeof(float) * 2);
	pos += sizeof(float) * 2;
	memcpy(&paramSet.Damping, pos, sizeof(float) * 2);
	pos += sizeof(float) * 2;

	memcpy(&paramSet.InitialAngle[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.InitialAngle[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetAngle[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetAngle[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);

	for (size_t i = 0; i < 2; i++)
	{
		// Degrees to Radians
		paramSet.InitialAngle[i].x *= EFK_PI / 180.0f;
		paramSet.InitialAngle[i].y *= EFK_PI / 180.0f;
		paramSet.InitialAngle[i].z *= EFK_PI / 180.0f;
		paramSet.InitialAngle[i].w = 0.0f;
		paramSet.TargetAngle[i].x *= EFK_PI / 180.0f;
		paramSet.TargetAngle[i].y *= EFK_PI / 180.0f;
		paramSet.TargetAngle[i].z *= EFK_PI / 180.0f;
		paramSet.TargetAngle[i].w = 0.0f;
	}

	memcpy(&paramSet.InitialScale[0].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.InitialScale[1].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.InitialScale[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.InitialScale[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetScale[0].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TargetScale[1].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TargetScale[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetScale[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);

	memcpy(&paramSet.Gravity, pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.VortexRotation, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.VortexAttraction, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.VortexCenter, pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.VortexAxis, pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TurbulencePower, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TurbulenceSeed, pos, sizeof(int32_t));
	pos += sizeof(int32_t);
	memcpy(&paramSet.TurbulenceScale, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TurbulenceOctave, pos, sizeof(int32_t));
	pos += sizeof(int32_t);

	memcpy(&paramSet.BlendType, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.ZWrite, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.ZTest, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.Reserved, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);

	memcpy(&paramSet.ShapeType, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	memcpy(&paramSet.ShapeData, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	memcpy(&paramSet.ShapeSize, pos, sizeof(float));
	pos += sizeof(float);

	memcpy(&paramSet.ColorFlags, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);

	switch (paramSet.ColorFlags & 0x07)
	{
	case 0:
		memcpy(&paramSet.ColorData[0], pos, sizeof(Color));
		pos += sizeof(Color);
		break;
	case 1:
		memcpy(&paramSet.ColorData[0], pos, sizeof(Color) * 2);
		pos += sizeof(Color) * 2;
		break;
	case 2:
		memcpy(&paramSet.ColorData[0], pos, sizeof(Color) * 4);
		pos += sizeof(Color) * 4;
		memcpy(&paramSet.ColorEasing, pos, sizeof(float) * 3);
		pos += sizeof(float) * 3;
		break;
	}

	memcpy(&paramSet.Emissive, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.FadeIn, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.FadeOut, pos, sizeof(float));
	pos += sizeof(float);

	memcpy(&paramSet.MaterialType, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	memcpy(&paramSet.ColorTexIndex, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	memcpy(&paramSet.NormalTexIndex, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);
	memcpy(&paramSet.ColorTexFilter, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.NormalTexFilter, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.ColorTexWrap, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(&paramSet.NormalTexWrap, pos, sizeof(uint8_t));
	pos += sizeof(uint8_t);

	return paramSet;
}

} // namespace Effekseer
