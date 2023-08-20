#pragma once

#include <random>
#include "EffekseerRenderer.Renderer.h"

namespace EffekseerRenderer
{

class GpuParticles : public Effekseer::GpuParticles
{
public:
	using ComputeBufferRef = Effekseer::Backend::ComputeBufferRef;
	using UniformBufferRef = Effekseer::Backend::UniformBufferRef;
	using TextureRef = Effekseer::Backend::TextureRef;
	using ComputeCommand = Effekseer::Backend::DispatchParameter;
	using ShaderRef = Effekseer::Backend::ShaderRef;
	using VertexLayoutRef = Effekseer::Backend::VertexLayoutRef;
	using PipelineStateRef = Effekseer::Backend::PipelineStateRef;

	struct Shaders
	{
		ShaderRef csParticleClear;
		ShaderRef csParticleSpawn;
		ShaderRef csParticleUpdate;
		ShaderRef rsParticleRender;
	};

public:
	GpuParticles(Renderer* renderer);

	virtual ~GpuParticles();

	virtual bool InitSystem(const Settings& settings) override;

	virtual void SetShaders(const Shaders& shaders);

	virtual void UpdateFrame(float deltaTime) override;

	virtual void RenderFrame() override;

	virtual ParamID AddParamSet(const ParameterSet& paramSet, const Effekseer::Effect* effect) override;

	virtual void RemoveParamSet(ParamID paramID) override;

	virtual const ParameterSet* GetParamSet(ParamID paramID) const override;

	virtual EmitterID NewEmitter(ParamID paramID, ParticleGroupID groupID) override;

	virtual void StartEmit(EmitterID emitterID) override;

	virtual void StopEmit(EmitterID emitterID) override;

	virtual void KillParticles(ParticleGroupID groupID) override;

	virtual void SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform) override;

	virtual void SetColor(EmitterID emitterID, Effekseer::Color color) override;

	virtual int32_t GetParticleCountByGroup(ParticleGroupID groupID) override;

	virtual int32_t GetParticleCountByEmitter(EmitterID emitterID) override;

protected:
	void FreeEmitter(EmitterID emitterID);

	PipelineStateRef CreatePiplineState(const ParameterSet& paramSet);

protected:
	static constexpr uint32_t EmitterUnitSize = 16;
	static constexpr uint32_t ParticleUnitSize = 256;

	struct Emitter
	{
		uint32_t FlagBits;  // Alive:1, Emitting:1, ParamID:10
		uint32_t Seed;
		uint32_t ParticleHead;
		uint32_t ParticleSize;
		uint32_t TrailHead;
		uint32_t TrailSize;
		uint32_t TrailPhase;
		uint32_t NextEmitCount;
		uint32_t TotalEmitCount;
		uint32_t EmitPointCount;
		float TimeCount;
		float TimeStopped;
		ParticleGroupID GroupID;
		uint32_t Reserved;
		Effekseer::Color Color;
		float3x4 Transform;

		bool IsAlive() const
		{
			return (FlagBits & 1) != 0;
		}
		bool IsEmitting() const
		{
			return (FlagBits & 2) != 0;
		}
		uint32_t GetParamID() const
		{
			return (FlagBits >> 2) & 0x3F;
		}
		void SetFlagBits(bool alive, bool emission, uint32_t paramID)
		{
			FlagBits = ((uint32_t)alive) | ((uint32_t)emission << 1) | (paramID << 2);
		}
		void SetAlive(bool alive)
		{
			FlagBits = (FlagBits & ~1) | ((uint32_t)alive << 0);
		}
		void SetEmitting(bool emitting)
		{
			FlagBits = (FlagBits & ~2) | ((uint32_t)emitting << 1);
		}
	};
	struct Particle
	{
		uint32_t FlagBits;  // Alive:1, UpdateCount:8
		uint32_t Seed;
		float LifeAge;
		uint32_t InheritColor;
		uint16_t Velocity[4];
		uint32_t Color;
		uint32_t Padding;
		float3x4 Transform;
	};
	struct Trail
	{
		float3 Position;
		uint32_t Direction;
	};

	struct Constants
	{
		float4x4 ProjMat;
		float4x4 CameraMat;
		float3x4 BillboardMat;
		float3x4 YAxisBillboardMat;
		float3 CameraPos;
		float DeltaTime;
		float3 CameraFront;
		float Reserved;
	};
	struct Block
	{
		uint32_t offset;
		uint32_t size;
	};
	struct BlockAllocator
	{
		std::vector<Block> bufferBlocks;

		void Init(uint32_t bufferSize, uint32_t blockSize);
		Block Allocate(uint32_t size);
		void Deallocate(Block releasingBlock);
	};

	struct ParameterRes
	{
		const Effekseer::Effect* Effect = nullptr;
		PipelineStateRef PiplineState;
		TextureRef NoiseVectorField;
		ComputeBufferRef EmitPoints;
		uint32_t EmitPointCount = 0;
	};

	Renderer* m_rendererBase;
	std::mutex m_mutex;
	std::deque<ParamID> m_paramFreeList;
	std::deque<EmitterID> m_emitterFreeList;
	std::mt19937 m_random;

	std::vector<ParamID> m_newParamSetIDs;
	std::vector<ParameterSet> m_paramSets;
	std::vector<ParameterRes> m_resources;
	std::vector<EmitterID> m_newEmitterIDs;
	std::vector<Emitter> m_emitters;
	BlockAllocator m_particleAllocator;
	BlockAllocator m_trailAllocator;

	UniformBufferRef m_ubufConstants;
	std::vector<UniformBufferRef> m_ubufParamSets;
	std::vector<UniformBufferRef> m_ubufEmitters;

	ComputeBufferRef m_cbufParticles;
	ComputeBufferRef m_cbufTrails;

	PipelineStateRef m_pipelineParticleClear;
	PipelineStateRef m_pipelineParticleSpawn;
	PipelineStateRef m_pipelineParticleUpdate;

	Shaders m_shaders;

	TextureRef m_dummyVectorField;

	VertexLayoutRef m_vertexLayout;
	Effekseer::ModelRef m_modelSprite;
	Effekseer::ModelRef m_modelTrail;
};

}
