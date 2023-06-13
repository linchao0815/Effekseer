#pragma once

#include <random>
#include "EffekseerRendererDX11.DeviceObject.h"
#include "GraphicsDevice.h"

namespace EffekseerRendererDX11
{

class GpuParticles : public DeviceObject, public Effekseer::GpuParticles
{
public:
	using ComputeShader = Backend::D3D11ComputeShaderPtr;
	using VertexShader = Backend::D3D11VertexShaderPtr;
	using PixelShader = Backend::D3D11PixelShaderPtr;

	struct ComputeBuffer
	{
		Backend::D3D11BufferPtr buffer;
		Backend::D3D11ShaderResourceViewPtr srv;
		Backend::D3D11UnorderedAccessViewPtr uav;

		static ComputeBuffer Create(ID3D11Device* device, size_t elementSize, size_t elementCount, uint32_t cpuFlags, bool hasUAV = false, uint32_t uavFlags = 0);
		void UpdateData(ID3D11DeviceContext* context, size_t offset, const void* data, size_t size);
		void UpdateDynamicData(ID3D11DeviceContext* context, size_t offset, const void* data, size_t size);
	};

	struct ComputeCommand
	{
		ID3D11ComputeShader* shader = nullptr;
		std::array<ID3D11Buffer*, 4> csCBufs = {};
		std::array<ID3D11ShaderResourceView*, 4> csSRVs = {};
		std::array<ID3D11UnorderedAccessView*, 4> csUAVs = {};

		void Dispatch(ID3D11DeviceContext* context, uint32_t baseCount, uint32_t processCount);
	};

	struct ConstantBuffer
	{
		Backend::D3D11BufferPtr buffer;

		static ConstantBuffer Create(ID3D11Device* device, const void* data, size_t size);
		void UpdateData(ID3D11DeviceContext* context, const void* data, size_t size);
	};

public:
	GpuParticles(RendererImplemented* renderer, bool hasRefCount);

	virtual ~GpuParticles();

	void InitDevice();
	void ReleaseDevice();

public: // For device restore
	virtual void OnLostDevice();
	virtual void OnResetDevice();

public: // GpuParticles
	virtual void InitSystem(const Settings& settings) override;

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

private:
	static constexpr uint32_t EmitterUnitSize = 16;
	static constexpr uint32_t ParticleUnitSize = 256;

	struct DynamicInput
	{
		uint32_t nextEmitCount;
		uint32_t totalEmitCount;
		float3x4 transform;
		float4 color;
	};
	struct Emitter
	{
		uint32_t flagBits;  // Alive:1, ParamID:10
		uint32_t seed;
		uint32_t particlesHead;
		uint32_t particlesSize;

		bool IsAlive() const
		{
			return flagBits & 0x01;
		}
		uint32_t GetParamID() const
		{
			return (flagBits >> 1) & 0x3F;
		}
		void SetFlagBits(bool alive, uint32_t paramID)
		{
			flagBits = (uint32_t)alive | (paramID << 1);
		}
	};
	struct Particle
	{
		uint32_t flagBits;  // Alive:1, ParamID:10, EmitterID:10
		uint32_t seed;
		float lifeAge;
		uint32_t color;
		float3 position;
		uint16_t velocity[4];
		uint16_t rotscale[4];
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
		uint32_t bufferOffset;
		uint32_t reserved[3];
	};

	struct Vertex
	{
		float3 position;
	};
	struct Block
	{
		uint32_t offset;
		uint32_t size;
	};

	struct ParameterRes
	{
		const Effekseer::Effect* effect = nullptr;
		Backend::TextureRef noiseVectorField;
	};

	std::mutex m_mutex;
	std::deque<ParamID> m_paramFreeList;
	std::deque<EmitterID> m_emitterFreeList;
	std::mt19937 m_random;

	std::vector<ParamID> m_newParamSetIDs;
	std::vector<ParameterSet> m_paramSets;
	std::vector<ParameterRes> m_resources;
	std::vector<EmitterID> m_newEmitterIDs;
	std::vector<Emitter> m_emitters;
	std::vector<Block> m_bufferBlocks;
	bool m_firstTime = false;

	ConstantBuffer m_bufferConstants;
	ConstantBuffer m_bufferParticleArgs;

	std::vector<DynamicInput> m_dynamicInputs;
	ComputeBuffer m_bufviewParamSets;
	ComputeBuffer m_bufviewDynamicInput;
	ComputeBuffer m_bufviewEmitter;
	ComputeBuffer m_bufviewParticle;

	ComputeShader m_csEmitterClear;
	ComputeShader m_csEmitterUpdate;
	ComputeShader m_csParticleClear;
	ComputeShader m_csParticleUpdate;

	ComputeCommand m_cmdEmitterClear;
	ComputeCommand m_cmdEmitterUpdate;
	ComputeCommand m_cmdParticleClear;
	ComputeCommand m_cmdParticleUpdate;

	Backend::D3D11SamplerStatePtr m_vfSampler;

	std::unique_ptr<Shader> m_renderShader;
	Effekseer::ModelRef m_modelSprite;
};

}
