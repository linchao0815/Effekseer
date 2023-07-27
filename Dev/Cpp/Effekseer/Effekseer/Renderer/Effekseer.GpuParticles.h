
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

	struct float3
	{
		float x, y, z;

		float3& operator=(const Effekseer::Vector3D& rhs)
		{
			x = rhs.X;
			y = rhs.Y;
			z = rhs.Z;
			return *this;
		}
	};
	struct float4
	{
		float x, y, z, w;

		float4& operator=(const std::array<float, 4>& rhs)
		{
			x = rhs[0];
			y = rhs[1];
			z = rhs[2];
			w = rhs[3];
			return *this;
		}
	};

	using float3x4 = std::array<float4, 3>; // row_major
	using float4x4 = Effekseer::Matrix44;

	struct Settings
	{
		uint32_t EmitterMaxCount = 256;
		uint32_t ParticleMaxCount = 1 * 1024 * 1024;
		uint32_t TrailMaxCount = 4 * 1024 * 1024;
	};

	enum class EmitShape : uint32_t
	{
		Point, Line, Circle, Sphere, Model,
	};
	enum class RenderShape : uint32_t
	{
		Sprite, Model, Trail,
	};

	struct ParameterSet
	{
		int32_t EmitCount;
		int32_t EmitPerFrame;
		float EmitOffset;
		uint32_t Padding0;
		std::array<float, 2> LifeTime;

		EmitShape EmitShapeType;
		uint32_t Padding1;
		union
		{
			float4 Reserved[2];
			struct
			{
				float3 LineStart;
				float Padding;
				float3 LineEnd;
				float LineWidth;
			};
			struct
			{
				float3 CircleAxis;
				float Padding;
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

		std::array<float4, 2> InitialAngleScale;
		std::array<float4, 2> TargetAngleScale;

		float3 Gravity;
		float Padding2;

		float3 VortexCenter;
		float VortexRotation;
		float3 VortexAxis;
		float VortexAttraction;

		float TurbulencePower;
		int32_t TurbulenceSeed;
		float TurbulenceScale;
		int32_t TurbulenceOctave;

		uint8_t BlendType;
		uint8_t ZWrite;
		uint8_t ZTest;
		uint8_t Reserved;

		RenderShape ShapeType;
		uint32_t ShapeData;
		float ShapeSize;

		float Emissive;
		float FadeIn;
		float FadeOut;
		uint32_t ColorFlags;
		std::array<uint32_t, 2> ColorStart;
		std::array<uint32_t, 2> ColorEnd;
		
		uint32_t ColorTexIndex;
		uint32_t NormalTexIndex;
		uint8_t ColorTexFilter;
		uint8_t NormalTexFilter;
		uint8_t ColorTexWrap;
		uint8_t NormalTexWrap;
		uint32_t Padding3;
	};
	using EmitterID = int32_t;
	using ParamID = int32_t;
	static constexpr int32_t InvalidID = -1;

public:
	GpuParticles() = default;

	virtual ~GpuParticles() = default;
	
	virtual bool InitSystem(const Settings& settings = {}) { return true; }

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
