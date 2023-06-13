#define NOMINMAX
#include "EffekseerRendererDX11.GpuParticles.h"
#include "EffekseerRendererDX11.Shader.h"
#include "EffekseerRendererDX11.RenderState.h"
#include "../Effekseer/Effekseer/Noise/CurlNoise.h"

namespace EffekseerRendererDX11
{

namespace
{

namespace CS_EmitterClear
{
#include "ShaderHeader/gpupt_emitter_clear_cs.h"
}

namespace CS_EmitterUpdate
{
#include "ShaderHeader/gpupt_emitter_update_cs.h"
}

namespace CS_ParticleClear
{
#include "ShaderHeader/gpupt_particle_clear_cs.h"
}

namespace CS_ParticleUpdate
{
#include "ShaderHeader/gpupt_particle_update_cs.h"
}

namespace VS_ParticleRender
{
#include "ShaderHeader/gpupt_particle_render_vs.h"
}

namespace PS_ParticleRender
{
#include "ShaderHeader/gpupt_particle_render_ps.h"
}

inline constexpr uint32_t RoundUp(uint32_t x, uint32_t unit)
{
	return (x + unit - 1) / unit * unit;
}

GpuParticles::ComputeShader CreateCS(ID3D11Device* device, const BYTE* binary, size_t binarySize)
{
	ID3D11ComputeShader* shader = nullptr;
	device->CreateComputeShader(binary, binarySize, nullptr, &shader);
	return GpuParticles::ComputeShader(shader);
}

#define ShaderData(shaderName) shaderName::g_main
#define ShaderSize(shaderName) sizeof(shaderName::g_main)

}

GpuParticles::ComputeBuffer GpuParticles::ComputeBuffer::Create(ID3D11Device* device,
	size_t elementSize, size_t elementCount, uint32_t cpuFlags, bool hasUAV, uint32_t uavFlags)
{
	ID3D11Buffer* buffer_ = nullptr;
	ID3D11ShaderResourceView* srv_ = nullptr;
	ID3D11UnorderedAccessView* uav_ = nullptr;

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(elementSize * elementCount);
	bufferDesc.StructureByteStride = static_cast<UINT>(elementSize);
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | ((hasUAV) ? D3D11_BIND_UNORDERED_ACCESS : 0);
	bufferDesc.Usage = (cpuFlags) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = cpuFlags;
	device->CreateBuffer(&bufferDesc, nullptr, &buffer_);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = static_cast<UINT>(elementCount);
	device->CreateShaderResourceView(buffer_, &srvDesc, &srv_);

	if (hasUAV)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = static_cast<UINT>(elementCount);
		uavDesc.Buffer.Flags = uavFlags;
		device->CreateUnorderedAccessView(buffer_, &uavDesc, &uav_);
	}

	return {
		Backend::D3D11BufferPtr(buffer_),
		Backend::D3D11ShaderResourceViewPtr(srv_),
		Backend::D3D11UnorderedAccessViewPtr(uav_),
	};
}

void GpuParticles::ComputeBuffer::UpdateData(ID3D11DeviceContext* context, size_t offset, const void* data, size_t size)
{
	D3D11_BOX dstBox{};
	dstBox.left = static_cast<UINT>(offset);
	dstBox.right = static_cast<UINT>(offset + size);
	dstBox.bottom = 1;
	dstBox.back = 1;
	context->UpdateSubresource(buffer.get(), 0, &dstBox, data, 0, 0);
}

void GpuParticles::ComputeBuffer::UpdateDynamicData(ID3D11DeviceContext* context, size_t offset, const void* data, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE mapped{};
	context->Map(buffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy((uint8_t*)mapped.pData + offset, data, size);
	context->Unmap(buffer.get(), 0);
}

GpuParticles::ConstantBuffer GpuParticles::ConstantBuffer::Create(ID3D11Device* device, const void* data, size_t size)
{
	ID3D11Buffer* buffer_ = nullptr;

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = (UINT)size;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA initialData;
	initialData.pSysMem = data;
	initialData.SysMemPitch = 0;
	initialData.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &initialData, &buffer_);

	return { Backend::D3D11BufferPtr(buffer_) };
}

void GpuParticles::ConstantBuffer::UpdateData(ID3D11DeviceContext* context, const void* data, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE mapped{};
	context->Map(buffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, data, size);
	context->Unmap(buffer.get(), 0);
}

void GpuParticles::ComputeCommand::Dispatch(ID3D11DeviceContext* context, uint32_t baseCount, uint32_t processCount)
{
	assert(shader);

	context->CSSetShader(shader, nullptr, 0);
	context->CSSetConstantBuffers(0, (UINT)csCBufs.size(), csCBufs.data());
	context->CSSetShaderResources(0, (UINT)csSRVs.size(), csSRVs.data());
	context->CSSetUnorderedAccessViews(0, (UINT)csUAVs.size(), csUAVs.data(), nullptr);
	context->Dispatch(1, processCount / baseCount, 1);

	std::array<ID3D11UnorderedAccessView*, 4> csClearUAVs = {};
	context->CSSetUnorderedAccessViews(0, (UINT)csClearUAVs.size(), csClearUAVs.data(), nullptr);
}

GpuParticles::GpuParticles(RendererImplemented* renderer, bool hasRefCount)
	: DeviceObject(renderer, hasRefCount)
{
	InitDevice();

	Settings settings;
	settings.EmitterMaxCount = 256;
	settings.ParticleMaxCount = 256 * 1024;
	InitSystem(settings);
}

GpuParticles::~GpuParticles()
{
	ReleaseDevice();
}

void GpuParticles::InitDevice()
{
	auto device = GetRenderer()->GetDevice();
}

void GpuParticles::ReleaseDevice()
{
}

void GpuParticles::OnLostDevice()
{
	ReleaseDevice();
}

void GpuParticles::OnResetDevice()
{
	InitDevice();
}

void GpuParticles::InitSystem(const Settings& settings)
{
	auto device = GetRenderer()->GetDevice();

	m_settings = settings;
	m_paramSets.resize(settings.EmitterMaxCount);
	m_resources.resize(settings.EmitterMaxCount);
	m_emitters.resize(settings.EmitterMaxCount);
	m_dynamicInputs.resize(settings.EmitterMaxCount);

	for (uint32_t index = 0; index < settings.EmitterMaxCount; index++)
	{
		m_dynamicInputs[index].transform.Indentity();
		m_paramFreeList.push_back(index);
		m_emitterFreeList.push_back(index);
	}
	m_newParamSetIDs.reserve(settings.EmitterMaxCount);
	m_newEmitterIDs.reserve(settings.EmitterMaxCount);

	m_bufferBlocks.reserve(settings.ParticleMaxCount / ParticleUnitSize);
	m_bufferBlocks.push_back({0, settings.ParticleMaxCount});

	Constants cdata{};
	m_bufferConstants = ConstantBuffer::Create(device, &cdata, sizeof(Constants));
	ParticleArgs pargs{};
	m_bufferParticleArgs = ConstantBuffer::Create(device, &pargs, sizeof(ParticleArgs));
	
	m_bufviewParamSets = ComputeBuffer::Create(device, sizeof(ParameterSet), settings.EmitterMaxCount, 0);
	m_bufviewDynamicInput = ComputeBuffer::Create(device, sizeof(DynamicInput), settings.EmitterMaxCount, D3D11_CPU_ACCESS_WRITE);
	m_bufviewEmitter = ComputeBuffer::Create(device, sizeof(Emitter), settings.EmitterMaxCount, 0, true, 0);
	m_bufviewParticle = ComputeBuffer::Create(device, sizeof(Particle), settings.ParticleMaxCount, 0, true, 0);

	m_csEmitterClear = CreateCS(device, ShaderData(CS_EmitterClear), ShaderSize(CS_EmitterClear));
	m_csEmitterUpdate = CreateCS(device, ShaderData(CS_EmitterUpdate), ShaderSize(CS_EmitterUpdate));
	m_csParticleClear = CreateCS(device, ShaderData(CS_ParticleClear), ShaderSize(CS_ParticleClear));
	m_csParticleUpdate = CreateCS(device, ShaderData(CS_ParticleUpdate), ShaderSize(CS_ParticleUpdate));

	m_cmdEmitterClear.shader = m_csEmitterClear.get();
	m_cmdEmitterClear.csCBufs[0] = m_bufferConstants.buffer.get();
	m_cmdEmitterClear.csSRVs[0] = m_bufviewParamSets.srv.get();
	m_cmdEmitterClear.csUAVs[0] = m_bufviewEmitter.uav.get();

	m_cmdEmitterUpdate.shader = m_csEmitterUpdate.get();
	m_cmdEmitterUpdate.csCBufs[0] = m_bufferConstants.buffer.get();
	m_cmdEmitterUpdate.csSRVs[0] = m_bufviewParamSets.srv.get();
	m_cmdEmitterUpdate.csSRVs[1] = m_bufviewDynamicInput.srv.get();
	m_cmdEmitterUpdate.csUAVs[0] = m_bufviewEmitter.uav.get();
	m_cmdEmitterUpdate.csUAVs[1] = m_bufviewParticle.uav.get();

	m_cmdParticleClear.shader = m_csParticleClear.get();
	m_cmdParticleClear.csCBufs[0] = m_bufferConstants.buffer.get();
	m_cmdParticleClear.csCBufs[1] = m_bufferParticleArgs.buffer.get();
	m_cmdParticleClear.csSRVs[0] = m_bufviewParamSets.srv.get();
	m_cmdParticleClear.csUAVs[0] = m_bufviewParticle.uav.get();

	m_cmdParticleUpdate.shader = m_csParticleUpdate.get();
	m_cmdParticleUpdate.csCBufs[0] = m_bufferConstants.buffer.get();
	m_cmdParticleUpdate.csCBufs[1] = m_bufferParticleArgs.buffer.get();
	m_cmdParticleUpdate.csSRVs[0] = m_bufviewParamSets.srv.get();
	m_cmdParticleUpdate.csSRVs[1] = m_bufviewDynamicInput.srv.get();
	m_cmdParticleUpdate.csUAVs[0] = m_bufviewParticle.uav.get();

	auto graphics = GetRenderer()->GetGraphicsDevice();
	auto vertexLayout = EffekseerRenderer::GetModelRendererVertexLayout(graphics).DownCast<Backend::VertexLayout>();

	m_renderShader.reset(Shader::Create(graphics,
		graphics->CreateShaderFromBinary(
			ShaderData(VS_ParticleRender), ShaderSize(VS_ParticleRender),
			ShaderData(PS_ParticleRender), ShaderSize(PS_ParticleRender)),
		vertexLayout, "GpuParticleRender"
	));

	Effekseer::CustomVector<Effekseer::Model::Vertex> SpriteVertexes = {
		{ { -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {255, 255, 255, 255} },
		{ { -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {255, 255, 255, 255} },
		{ {  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {255, 255, 255, 255} },
		{ {  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {255, 255, 255, 255} },
	};
	Effekseer::CustomVector<Effekseer::Model::Face> SpriteFaces = {
		{ {0, 2, 1} }, { {1, 2, 3} }
	};
	m_modelSprite = Effekseer::MakeRefPtr<Effekseer::Model>(SpriteVertexes, SpriteFaces);
	m_modelSprite->StoreBufferToGPU(graphics.Get());

	{
		D3D11_SAMPLER_DESC samplerDesc{};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		ID3D11SamplerState* sampler = nullptr;
		device->CreateSamplerState(&samplerDesc, &sampler);
		m_vfSampler.reset(sampler);
	}

	m_firstTime = true;
}

void GpuParticles::UpdateFrame(float deltaTime)
{
	auto context = GetRenderer()->GetContext();

	if (m_firstTime)
	{
		m_cmdEmitterClear.Dispatch(context, 16, m_settings.EmitterMaxCount);
		m_firstTime = false;
	}

	// Update constant buffer
	Constants cdata{};
	cdata.ProjMat = GetRenderer()->GetProjectionMatrix();
	cdata.CameraMat = GetRenderer()->GetCameraMatrix();

	Effekseer::Matrix44	inv{};
	Effekseer::Matrix44::Inverse(inv, cdata.CameraMat);
	cdata.BillboardMat = {
		float4{ inv.Values[0][0], inv.Values[0][1], inv.Values[0][2], 0.0f },
		float4{ inv.Values[1][0], inv.Values[1][1], inv.Values[1][2], 0.0f },
		float4{ inv.Values[2][0], inv.Values[2][1], inv.Values[2][2], 0.0f }
	};
	cdata.YAxisBillboardMat = {
		float4{ inv.Values[0][0], 0.0f, inv.Values[0][2], 0.0f },
		float4{ inv.Values[1][0], 1.0f, inv.Values[1][2], 0.0f },
		float4{ inv.Values[2][0], 0.0f, inv.Values[2][2], 0.0f }
	};
	cdata.CameraPos = GetRenderer()->GetCameraPosition();
	cdata.CameraFront = GetRenderer()->GetCameraFrontDirection();
	cdata.DeltaTime = deltaTime;
	m_bufferConstants.UpdateData(context, &cdata, sizeof(Constants));

	for (auto paramID : m_newParamSetIDs)
	{
		// Initialize parameter data
		m_bufviewParamSets.UpdateData(context, paramID * sizeof(ParameterSet), &m_paramSets[paramID], sizeof(ParameterSet));
	}
	m_newParamSetIDs.clear();

	for (auto emitterID : m_newEmitterIDs)
	{
		// Initialize emitter data
		auto& emitter = m_emitters[emitterID];
		m_bufviewEmitter.UpdateData(context, emitterID * sizeof(Emitter), &emitter, sizeof(Emitter));

		// Initialize particle data region
		ParticleArgs pargs{};
		pargs.bufferOffset = emitter.particlesHead;
		m_bufferParticleArgs.UpdateData(context, &pargs, sizeof(pargs));
		m_cmdParticleClear.Dispatch(context, 256, emitter.particlesSize);
	}
	m_newEmitterIDs.clear();

	// Update dynamic inputs
	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& input = m_dynamicInputs[emitterID];
			input.totalEmitCount += input.nextEmitCount;
			input.nextEmitCount = std::min(
				(uint32_t)(deltaTime / paramSet.EmitInterval[0]), 
				paramSet.EmitCount - input.totalEmitCount);
		}
	}
	m_bufviewDynamicInput.UpdateDynamicData(context, 0, m_dynamicInputs.data(), sizeof(DynamicInput) * m_dynamicInputs.size());

	// Update emitters
	m_cmdEmitterUpdate.Dispatch(context, 16, m_settings.EmitterMaxCount);

	// Update particles
	{
		ID3D11SamplerState* samplers[1] = { m_vfSampler.get() };
		context->CSSetSamplers(4, 1, samplers);
	}
	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& paramRes = m_resources[emitter.GetParamID()];

			ParticleArgs pargs{};
			pargs.bufferOffset = emitter.particlesHead;
			m_bufferParticleArgs.UpdateData(context, &pargs, sizeof(pargs));

			if (paramRes.noiseVectorField) {
				ID3D11ShaderResourceView* vfSRVs[1] = { paramRes.noiseVectorField->GetSRV() };
				context->CSSetShaderResources(4, 1, vfSRVs);
			}

			m_cmdParticleUpdate.Dispatch(context, 256, emitter.particlesSize);
		}
	}
	{
		ID3D11SamplerState* samplers[1] = { nullptr };
		context->CSSetSamplers(4, 1, samplers);
	}
}

void GpuParticles::RenderFrame()
{
	auto renderer = GetRenderer();
	auto context = renderer->GetContext();

	Shader* shader = m_renderShader.get();
	renderer->BeginShader(shader);
	renderer->SetLayout(shader);

	for (Emitter& emitter : m_emitters)
	{
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& paramRes = m_resources[emitter.GetParamID()];

			ParticleArgs pargs{};
			pargs.bufferOffset = emitter.particlesHead;
			m_bufferParticleArgs.UpdateData(context, &pargs, sizeof(pargs));

			ID3D11ShaderResourceView* vsSRVs[3] = {
				m_bufviewParticle.srv.get(),
				m_bufviewParamSets.srv.get(),
				m_bufviewDynamicInput.srv.get()
			};
			context->VSSetShaderResources(8, 3, vsSRVs);

			ID3D11Buffer* vsCBufs[2] = {
				m_bufferConstants.buffer.get(),
				m_bufferParticleArgs.buffer.get()
			};
			context->VSSetConstantBuffers(8, 2, vsCBufs);

			Effekseer::Backend::TextureRef textures[2];
			if (auto colorTex = paramRes.effect->GetColorImage(paramSet.ColorTexIndex))
			{
				textures[0] = colorTex->GetBackend();
			}
			else
			{
				textures[0] = renderer->GetImpl()->GetProxyTexture(EffekseerRenderer::ProxyTextureType::White);
			}

			if (auto normalTex = paramRes.effect->GetNormalImage(paramSet.NormalTexIndex))
			{
				textures[1] = normalTex->GetBackend();
			}
			else
			{
				textures[1] = renderer->GetImpl()->GetProxyTexture(EffekseerRenderer::ProxyTextureType::Normal);
			}
			renderer->SetTextures(shader, textures, 2);

			auto& state = renderer->GetRenderState()->Push();
			state.DepthTest = paramSet.ZTest;
			state.DepthWrite = paramSet.ZWrite;
			state.AlphaBlend = (Effekseer::AlphaBlendType)paramSet.BlendType;
			state.CullingType = Effekseer::CullingType::Front;

			state.TextureFilterTypes[0] = (Effekseer::TextureFilterType)paramSet.ColorTexFilter;
			state.TextureFilterTypes[1] = (Effekseer::TextureFilterType)paramSet.NormalTexFilter;
			state.TextureWrapTypes[0] = (Effekseer::TextureWrapType)paramSet.ColorTexWrap;
			state.TextureWrapTypes[1] = (Effekseer::TextureWrapType)paramSet.NormalTexWrap;

			renderer->GetRenderState()->Update(true);

			Effekseer::ModelRef model;
			if (paramSet.ShapeType == 1)
			{
				model = paramRes.effect->GetModel(paramSet.ShapeData);
			}
			else
			{
				model = m_modelSprite;
			}

			if (model)
			{
				if (!model->GetIsBufferStoredOnGPU())
				{
					model->StoreBufferToGPU(renderer->GetGraphicsDevice().Get());
				}

				int32_t modelFrameCount = model->GetFrameCount();
				for (int32_t i = 0; i < modelFrameCount; i++)
				{
					auto vertexBuffer = model->GetVertexBuffer(i).DownCast<Backend::VertexBuffer>();
					auto indexBuffer = model->GetIndexBuffer(i).DownCast<Backend::IndexBuffer>();
					renderer->SetVertexBuffer(vertexBuffer, sizeof(Effekseer::Model::Vertex));
					renderer->SetIndexBuffer(indexBuffer);
					renderer->DrawPolygonInstanced(model->GetVertexCount(), model->GetFaceCount() * 3, emitter.particlesSize);
				}
			}

			renderer->GetRenderState()->Pop();
		}
	}

	ID3D11ShaderResourceView* clearSRVs[2] = {};
	context->VSSetShaderResources(8, 2, clearSRVs);

	ID3D11Buffer* clearCBufs[2] = {};
	context->VSSetConstantBuffers(8, 2, clearCBufs);

	renderer->EndShader(shader);
}

GpuParticles::ParamID GpuParticles::AddParamSet(const ParameterSet& paramSet, const Effekseer::Effect* effect)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_paramFreeList.size() == 0)
	{
		return InvalidID;
	}

	ParamID paramID = m_paramFreeList.front();
	m_paramFreeList.pop_front();
	m_paramSets[paramID] = paramSet;
	m_newParamSetIDs.emplace_back(paramID);

	ParameterRes paramRes;
	paramRes.effect = effect;

	if (paramSet.TurbulencePower != 0.0f)
	{
		Effekseer::LightCurlNoise noise(paramSet.TurbulenceSeed, paramSet.TurbulenceScale, paramSet.TurbulenceOctave);
		
		Effekseer::Backend::TextureParameter texParam;
		texParam.Format = Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM;
		texParam.Size = { 8, 8, 8 };
		texParam.Dimension = 3;

		Effekseer::CustomVector<uint8_t> initialData;
		initialData.resize(sizeof(uint32_t) * 8 * 8 * 8);
		memcpy(initialData.data(), noise.VectorField(), initialData.size());

		auto noiseVF = GetRenderer()->GetGraphicsDevice()->CreateTexture(texParam, initialData);
		paramRes.noiseVectorField = noiseVF.DownCast<Backend::Texture>();
	}
	m_resources[paramID] = paramRes;

	return paramID;
}

void GpuParticles::RemoveParamSet(ParamID paramID)
{
	if (paramID < 0)
	{
		return;
	}

	std::lock_guard<std::mutex> lock(m_mutex);
	m_paramFreeList.push_front(paramID);
}

const GpuParticles::ParameterSet* GpuParticles::GetParamSet(ParamID paramID) const
{
	if (paramID < 0 || paramID >= m_paramSets.size())
	{
		return nullptr;
	}

	return &m_paramSets[paramID];
}

GpuParticles::EmitterID GpuParticles::AddEmitter(ParamID paramID)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_emitterFreeList.size() == 0)
	{
		return InvalidID;
	}

	EmitterID emitterID = m_emitterFreeList.front();
	
	auto& paramSet = m_paramSets[paramID];
	uint32_t particlesMaxCount = (uint32_t)((double)paramSet.LifeTime[0] / paramSet.EmitInterval[1]);
	particlesMaxCount = std::min(particlesMaxCount, paramSet.EmitCount);
	particlesMaxCount = RoundUp(particlesMaxCount, ParticleUnitSize);

	DynamicInput& input = m_dynamicInputs[emitterID];
	input.nextEmitCount = 0;
	input.totalEmitCount = 0;
	input.transform.Indentity();

	Emitter& emitter = m_emitters[emitterID];
	emitter.SetFlagBits(true, paramID);
	emitter.seed = m_random();
	emitter.particlesHead = 0;
	emitter.particlesSize = 0;

	for (size_t i = 0; i < m_bufferBlocks.size(); i++)
	{
		Block& block = m_bufferBlocks[i];
		if (block.size >= particlesMaxCount)
		{
			if (block.size == particlesMaxCount)
			{
				emitter.particlesHead = block.offset;
				emitter.particlesSize = particlesMaxCount;
				m_bufferBlocks.erase(m_bufferBlocks.begin() + i);
				break;
			}
			else
			{
				emitter.particlesHead = block.offset;
				emitter.particlesSize = particlesMaxCount;
				block.offset += particlesMaxCount;
				break;
			}
		}
	}
	if (emitter.particlesSize == 0)
	{
		return InvalidID;
	}

	m_newEmitterIDs.push_back(emitterID);
	m_emitterFreeList.pop_front();

	return emitterID;
}

void GpuParticles::RemoveEmitter(EmitterID emitterID)
{
	if (emitterID < 0 || emitterID >= (EmitterID)m_emitters.size())
	{
		return;
	}

	std::lock_guard<std::mutex> lock(m_mutex);

	Emitter& emitter = m_emitters[emitterID];
	emitter.flagBits = 0;
	m_newEmitterIDs.push_back(emitterID);

	uint32_t particlesTail = emitter.particlesHead + emitter.particlesSize;
	for (size_t i = 0; i < m_bufferBlocks.size(); i++)
	{
		Block& block = m_bufferBlocks[i];
		if (block.offset <= particlesTail)
		{
			if (block.offset == particlesTail)
			{
				block.offset -= emitter.particlesSize;
				break;
			}
			else
			{
				m_bufferBlocks.insert(m_bufferBlocks.begin() + i, {emitter.particlesHead, emitter.particlesSize});
				break;
			}
		}
	}

	m_emitterFreeList.push_front(emitterID);
}

void GpuParticles::StopEmitter(EmitterID emitterID)
{
	if (emitterID < 0 || emitterID >= (EmitterID)m_emitters.size())
	{
		return;
	}
}

void GpuParticles::SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform)
{
	if (emitterID < 0 || emitterID >= (EmitterID)m_emitters.size())
	{
		return;
	}

	auto& input = m_dynamicInputs[emitterID];
	input.transform = transform;
}

void GpuParticles::SetColor(EmitterID emitterID, Effekseer::Color color)
{
	if (emitterID < 0 || emitterID >= (EmitterID)m_emitters.size())
	{
		return;
	}

	auto& input = m_dynamicInputs[emitterID];
	input.color = color.ToFloat4();
}

}
