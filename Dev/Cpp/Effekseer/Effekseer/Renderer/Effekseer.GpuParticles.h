
#ifndef __EFFEKSEER_GPU_PARTICLES_H__
#define __EFFEKSEER_GPU_PARTICLES_H__

#include "../Effekseer.Base.h"
#include "../Effekseer.Vector3D.h"
#include "../Effekseer.Color.h"

namespace Effekseer
{

class GpuParticles;
using GpuParticlesRef = RefPtr<GpuParticles>;

class GpuParticles : public ReferenceObject
{
public:
	using float3 = Effekseer::Vector3D;
	using float4 = std::array<float, 4>;
	using float3x4 = Effekseer::Matrix43;
	using float4x4 = Effekseer::Matrix44;
	using float3x3 = std::array<float4, 3>;  // 16byte alignment needed

	struct Settings
	{
		uint32_t EmitterMaxCount = 0;
		uint32_t ParticleMaxCount = 0;
		uint32_t TrailMaxCount = 0;
	};

	struct ParameterSet
	{
		uint32_t EmitCount;
		std::array<int32_t, 2> LifeTime;
		std::array<float, 2> EmitOffset;
		std::array<float, 2> EmitInterval;

		uint32_t EmitShapeType;
		union
		{
			float Reserved[3][3];
			struct
			{
				float LineStart[3];
				float LineEnd[3];
				float LineWidth;
			};
			struct
			{
				float CircleAxis[3];
				float CircleInner;
				float CircleOuter;
			};
			struct
			{
				float SphereRadius;
			};
			struct
			{
				int32_t ModelIndex;
				float ModelSize;
			};
		} EmitShapeData;

		float3 Direction;
		float Spread;
		std::array<float, 2> InitialSpeed;
		std::array<float, 2> Damping;

		std::array<float3, 2> InitialAngle;
		std::array<float3, 2> AngularVelocity;

		std::array<float, 2> InitialScale;
		std::array<float, 2> TerminalScale;

		float3 Gravity;
		float VortexRotation;
		float VortexAttraction;
		float3 VortexCenter;
		float3 VortexAxis;
		float TurbulencePower;
		int32_t TurbulenceSeed;
		float TurbulenceScale;
		int32_t TurbulenceOctave;

		uint8_t BlendType;
		uint8_t ZWrite;
		uint8_t ZTest;
		uint8_t Reserved;

		uint32_t ShapeType;
		uint32_t ShapeData;
		float ShapeSize;

		uint32_t ColorFlags;
		std::array<uint32_t, 2> ColorStart;
		std::array<uint32_t, 2> ColorEnd;
		float Emissive;
		float FadeIn;
		float FadeOut;
		uint32_t ColorTexIndex;
		uint32_t NormalTexIndex;
		uint8_t ColorTexFilter;
		uint8_t NormalTexFilter;
		uint8_t ColorTexWrap;
		uint8_t NormalTexWrap;
	};
	using EmitterID = int32_t;
	using ParamID = int32_t;
	static constexpr int32_t InvalidID = -1;

public:
	GpuParticles() = default;

	virtual ~GpuParticles() = default;
	
	virtual void InitSystem(const Settings& settings) {}

	virtual void UpdateFrame(float deltaTime) {}

	virtual void RenderFrame() {}

	virtual ParamID AddParamSet(const ParameterSet& paramSet, const Effect* effect) { return InvalidID; }

	virtual void RemoveParamSet(ParamID paramID) {}

	virtual const ParameterSet* GetParamSet(ParamID paramID) const { return nullptr; }

	virtual EmitterID AddEmitter(ParamID paramID) { return InvalidID; }

	virtual void RemoveEmitter(EmitterID emitterID) {}

	virtual void StopEmitter(EmitterID emitterID) {}

	virtual void SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform) {}

	virtual void SetColor(EmitterID emitterID, Effekseer::Color color) {}

protected:
	Settings m_settings;
};

} // namespace Effekseer

#endif // __EFFEKSEER_GPU_PARTICLES_H__
