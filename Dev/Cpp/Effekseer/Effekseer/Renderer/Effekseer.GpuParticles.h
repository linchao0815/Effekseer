
#ifndef __EFFEKSEER_GPU_PARTICLES_H__
#define __EFFEKSEER_GPU_PARTICLES_H__

#include "../Effekseer.Base.h"
#include "../Effekseer.Vector2D.h"
#include "../Effekseer.Vector3D.h"
#include "../Effekseer.Color.h"

namespace Effekseer
{

class GpuParticles;
using GpuParticlesRef = RefPtr<GpuParticles>;

class GpuParticles : public ReferenceObject
{
public:

	struct float2 {
		float x, y;

		float2() = default;
		float2(float x, float y): x(x), y(y) {}
		float2(const Effekseer::Vector2D& rhs): x(rhs.X), y(rhs.Y) {}
		float2& operator=(const Effekseer::Vector2D& rhs) { return *this = float2(rhs); }
	};
	struct float3
	{
		float x, y, z;

		float3() = default;
		float3(float x, float y, float z): x(x), y(y), z(z) {}
		float3(const Effekseer::Vector3D& rhs): x(rhs.X), y(rhs.Y), z(rhs.Z) {}
		float3& operator=(const Effekseer::Vector3D& rhs) { return *this = float3(rhs); }
	};
	struct float4
	{
		float x, y, z, w;

		float4() = default;
		float4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
		float4(const std::array<float, 4>& rhs): x(rhs[0]), y(rhs[1]), z(rhs[2]), w(rhs[3]) {}
		float4& operator=(const std::array<float, 4>& rhs) { return *this = float4(rhs); }
	};

	using float4x3 = std::array<float4, 3>;
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
	enum class MaterialType : uint32_t
	{
		Unlit, Lighting,
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
				float LinePadding;
				float3 LineEnd;
				float LineWidth;
			};
			struct
			{
				float3 CircleAxis;
				float CirclePadding;
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

		std::array<float4, 2> InitialAngle;
		std::array<float4, 2> TargetAngle;

		std::array<float4, 2> ScaleData1;
		std::array<float4, 2> ScaleData2;
		float3 ScaleEasing;
		uint32_t ScaleFlags;

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
		uint8_t Padding4;

		std::array<uint32_t, 4> ColorData;
		std::array<float, 3> ColorEasing;
		uint32_t ColorFlags;

		MaterialType MaterialType;
		uint32_t ColorTexIndex;
		uint32_t NormalTexIndex;
		uint8_t ColorTexFilter;
		uint8_t NormalTexFilter;
		uint8_t ColorTexWrap;
		uint8_t NormalTexWrap;
	};
	using EmitterID = int32_t;
	using ParamID = int32_t;
	using ParticleGroupID = int64_t;
	static constexpr int32_t InvalidID = -1;

public:
	GpuParticles() = default;

	virtual ~GpuParticles() = default;
	
	virtual bool InitSystem(const Settings& settings) { return true; }

	virtual void ComputeFrame() {}

	virtual void RenderFrame() {}

	virtual ParamID AddParamSet(const ParameterSet& paramSet, const Effect* effect) { return InvalidID; }

	virtual void RemoveParamSet(ParamID paramID) {}

	virtual const ParameterSet* GetParamSet(ParamID paramID) const { return nullptr; }

	virtual EmitterID NewEmitter(ParamID paramID, ParticleGroupID groupID) { return InvalidID; }

	virtual void StartEmit(EmitterID emitterID) {}

	virtual void StopEmit(EmitterID emitterID) {}

	virtual void SetRandomSeed(EmitterID emitterID, uint32_t seed) {}

	virtual void SetDeltaTime(EmitterID emitterID, float deltaTime) {}

	virtual void SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform) {}

	virtual void SetColor(EmitterID emitterID, Effekseer::Color color) {}

	virtual void KillParticles(ParticleGroupID groupID) {}

	virtual int32_t GetParticleCount(ParticleGroupID groupID) { return 0; }

	virtual void ResetDeltaTime() {}

protected:
	Settings m_settings;
};

} // namespace Effekseer

#endif // __EFFEKSEER_GPU_PARTICLES_H__
