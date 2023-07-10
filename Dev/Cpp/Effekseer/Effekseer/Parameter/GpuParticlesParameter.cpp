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
	case 0:
		break;
	case 1:
		memcpy(&paramSet.EmitShapeData.LineStart, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.LineEnd, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.LineWidth, pos, sizeof(float));
		pos += sizeof(float);
		break;
	case 2:
		memcpy(&paramSet.EmitShapeData.CircleAxis, pos, sizeof(Vector3D));
		pos += sizeof(Vector3D);
		memcpy(&paramSet.EmitShapeData.CircleInner, pos, sizeof(float));
		pos += sizeof(float);
		memcpy(&paramSet.EmitShapeData.CircleOuter, pos, sizeof(float));
		pos += sizeof(float);
		break;
		break;
	case 3:
		memcpy(&paramSet.EmitShapeData.SphereRadius, pos, sizeof(float));
		pos += sizeof(float);
		break;
	case 4:
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

	memcpy(&paramSet.InitialAngleScale[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.InitialAngleScale[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetAngleScale[0], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);
	memcpy(&paramSet.TargetAngleScale[1], pos, sizeof(Vector3D));
	pos += sizeof(Vector3D);

	for (size_t i = 0; i < 2; i++)
	{
		// Degrees to Radians
		paramSet.InitialAngleScale[i].x *= EFK_PI / 180.0f;
		paramSet.InitialAngleScale[i].y *= EFK_PI / 180.0f;
		paramSet.InitialAngleScale[i].z *= EFK_PI / 180.0f;
		paramSet.TargetAngleScale[i].x *= EFK_PI / 180.0f;
		paramSet.TargetAngleScale[i].y *= EFK_PI / 180.0f;
		paramSet.TargetAngleScale[i].z *= EFK_PI / 180.0f;
	}

	memcpy(&paramSet.InitialAngleScale[0].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.InitialAngleScale[1].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TargetAngleScale[0].w, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.TargetAngleScale[1].w, pos, sizeof(float));
	pos += sizeof(float);

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

	uint32_t colorType = 0;
	memcpy(&colorType, pos, sizeof(uint32_t));
	pos += sizeof(uint32_t);

	if (colorType == 0) {
		memcpy(&paramSet.ColorStart[0], pos, sizeof(Color));
		pos += sizeof(Color);
		paramSet.ColorStart[1] = paramSet.ColorStart[0];
		paramSet.ColorEnd = paramSet.ColorStart;
	}
	else if (colorType == 1) {
		pos += 2;
		memcpy(&paramSet.ColorStart, pos, sizeof(Color) * 2);
		pos += sizeof(Color) * 2;
		paramSet.ColorEnd = paramSet.ColorStart;
	}
	else if (colorType == 2) {
		pos += 2;
		memcpy(&paramSet.ColorStart, pos, sizeof(Color) * 2);
		pos += sizeof(Color) * 2;
		pos += 2;
		memcpy(&paramSet.ColorEnd, pos, sizeof(Color) * 2);
		pos += sizeof(Color) * 2;
	}

	memcpy(&paramSet.Emissive, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.FadeIn, pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&paramSet.FadeOut, pos, sizeof(float));
	pos += sizeof(float);

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
