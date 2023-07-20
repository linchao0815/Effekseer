#pragma once

#include <random>
#include "EffekseerRenderer.Renderer.h"

namespace EffekseerRenderer
{

class GpuParticles : public Effekseer::GpuParticles
{
public:
	using ComputeShaderRef = Effekseer::Backend::ComputeShaderRef;
	using ComputeBufferRef = Effekseer::Backend::ComputeBufferRef;
	using UniformBufferRef = Effekseer::Backend::UniformBufferRef;
	using TextureRef = Effekseer::Backend::TextureRef;
	using ComputeCommand = Effekseer::Backend::DispatchParameter;
	using ShaderRef = Effekseer::Backend::ShaderRef;
	using VertexLayoutRef = Effekseer::Backend::VertexLayoutRef;
	using PipelineStateRef = Effekseer::Backend::PipelineStateRef;

public:
	GpuParticles(Renderer* renderer);

	virtual ~GpuParticles();

	virtual void InitSystem(const Settings& settings) override;

	virtual void InitShaders() = 0;

	virtual void UpdateFrame(float deltaTime) override;

	virtual void RenderFrame() override;

	virtual ParamID AddParamSet(const ParameterSet& paramSet, const Effekseer::Effect* effect) override;

	virtual void RemoveParamSet(ParamID paramID) override;

	virtual const ParameterSet* GetParamSet(ParamID paramID) const override;

	virtual EmitterID AddEmitter(ParamID paramID) override;

	virtual void RemoveEmitter(EmitterID emitterID) override;

	virtual void StopEmitter(EmitterID emitterID) override;

	virtual void SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform) override;

	virtual void SetColor(EmitterID emitterID, Effekseer::Color color) override;

protected:
	static constexpr uint32_t EmitterUnitSize = 16;
	static constexpr uint32_t ParticleUnitSize = 256;

	struct Emitter
	{
		uint32_t FlagBits;  // Alive:1, ParamID:10
		uint32_t Seed;
		uint32_t ParticleHead;
		uint32_t ParticleSize;
		uint32_t TrailHead;
		uint32_t TrailSize;
		uint32_t TrailPhase;
		float TimeCount;
		uint32_t NextEmitCount;
		uint32_t TotalEmitCount;
		uint32_t EmitPointCount;
		float3x4 Transform;
		float4 Color;

		bool IsAlive() const
		{
			return FlagBits & 0x01;
		}
		uint32_t GetParamID() const
		{
			return (FlagBits >> 1) & 0x3F;
		}
		void SetFlagBits(bool alive, uint32_t paramID)
		{
			FlagBits = (uint32_t)alive | (paramID << 1);
		}
	};
	struct Particle
	{
		uint32_t FlagBits;  // Alive:1, ParamID:10, UpdateCount:8
		uint32_t Seed;
		float LifeAge;
		uint32_t InheritColor;
		uint32_t Color;
		uint16_t Velocity[4];
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
		float3x3 BillboardMat;
		float3x3 YAxisBillboardMat;
		float3 CameraPos;
		float DeltaTime;
		float3 CameraFront;
		float Reserved;
	};
	struct ParticleArgs
	{
		uint32_t EmitterID;
		uint32_t ParticleHead;
		uint32_t TrailHead;
		uint32_t TrailJoints;
		uint32_t TrailPhase;
		uint32_t Reserved[3];
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
	UniformBufferRef m_ubufParticleArgs;

	ComputeBufferRef m_cbufParamSets;
	ComputeBufferRef m_cbufEmitters;
	ComputeBufferRef m_cbufParticles;
	ComputeBufferRef m_cbufTrails;

	ComputeShaderRef m_csParticleSpawn;
	ComputeShaderRef m_csParticleClear;
	ComputeShaderRef m_csParticleUpdate;

	ComputeCommand m_cmdParticleSpawn;
	ComputeCommand m_cmdParticleClear;
	ComputeCommand m_cmdParticleUpdate;

	TextureRef m_dummyVectorField;

	ShaderRef m_renderShader;
	VertexLayoutRef m_vertexLayout;
	Effekseer::ModelRef m_modelSprite;
	Effekseer::ModelRef m_modelTrail;
};

}
