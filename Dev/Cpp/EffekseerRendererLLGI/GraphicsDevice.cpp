#include "GraphicsDevice.h"
#include <LLGI.Shader.h>
#include <LLGI.Texture.h>

namespace EffekseerRendererLLGI
{
namespace Backend
{

std::vector<uint8_t> Serialize(const std::vector<LLGI::DataStructure>& data)
{
	int32_t size = sizeof(int);
	for (const auto& d : data)
	{
		size += (sizeof(int) + d.Size);
	}

	std::vector<uint8_t> ret(size);

	int offset = 0;
	int32_t data_count = static_cast<int32_t>(data.size());
	memcpy(ret.data() + offset, &data_count, sizeof(int));
	offset += sizeof(int);

	for (const auto& d : data)
	{
		memcpy(ret.data() + offset, &d.Size, sizeof(int));
		offset += sizeof(int);

		memcpy(ret.data() + offset, d.Data, d.Size);
		size += d.Size;
	}

	return ret;
}

std::vector<LLGI::DataStructure> Deserialize(const void* data, int32_t size)
{
	std::vector<LLGI::DataStructure> ret;

	int offset = 0;
	uint8_t* p = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(data));
	int data_count = 0;
	memcpy(&data_count, p + offset, sizeof(int));
	offset += sizeof(int);

	for (int i = 0; i < data_count; i++)
	{
		int32_t data_size = 0;
		memcpy(&data_size, p + offset, sizeof(int));
		offset += sizeof(int);

		LLGI::DataStructure dataStructure;
		dataStructure.Data = p + offset;
		dataStructure.Size = data_size;
		offset += data_size;
		ret.emplace_back(dataStructure);
	}

	return ret;
}

void DeviceObject::OnLostDevice()
{
}

void DeviceObject::OnResetDevice()
{
}

VertexBuffer::VertexBuffer(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

VertexBuffer::~VertexBuffer()
{
	graphicsDevice_->Unregister(this);
	ES_SAFE_RELEASE(graphicsDevice_);
}

bool VertexBuffer::Allocate(int32_t size, bool isDynamic)
{
	buffer_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateBuffer(LLGI::BufferUsageType::Vertex | LLGI::BufferUsageType::MapWrite, size));
	return true;
}

void VertexBuffer::Deallocate()
{
	buffer_.reset();
}

void VertexBuffer::OnLostDevice()
{
	Deallocate();
}

void VertexBuffer::OnResetDevice()
{
	Allocate(size_, isDynamic_);
}

bool VertexBuffer::Init(int32_t size, bool isDynamic)
{
	size_ = size;
	isDynamic_ = isDynamic;

	return Allocate(size_, isDynamic_);
}

void VertexBuffer::UpdateData(const void* src, int32_t size, int32_t offset)
{
	if (auto dst = static_cast<uint8_t*>(buffer_->Lock()))
	{
		memcpy(dst + offset, src, size);
		buffer_->Unlock();
	}
}

IndexBuffer::IndexBuffer(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

IndexBuffer::~IndexBuffer()
{
	graphicsDevice_->Unregister(this);
	ES_SAFE_RELEASE(graphicsDevice_);
}

bool IndexBuffer::Allocate(int32_t elementCount, int32_t stride)
{
	buffer_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateBuffer(LLGI::BufferUsageType::Index | LLGI::BufferUsageType::MapWrite, stride * elementCount));

	elementCount_ = elementCount;
	strideType_ = stride == 4 ? Effekseer::Backend::IndexBufferStrideType::Stride4 : Effekseer::Backend::IndexBufferStrideType::Stride2;

	return buffer_ != nullptr;
}

void IndexBuffer::Deallocate()
{
	buffer_.reset();
}

void IndexBuffer::OnLostDevice()
{
	Deallocate();
}

void IndexBuffer::OnResetDevice()
{
	Allocate(elementCount_, stride_);
}

bool IndexBuffer::Init(int32_t elementCount, int32_t stride)
{
	elementCount_ = elementCount;
	stride_ = stride;

	return Allocate(elementCount_, stride_);
}

void IndexBuffer::UpdateData(const void* src, int32_t size, int32_t offset)
{
	if (auto dst = static_cast<uint8_t*>(buffer_->Lock()))
	{
		memcpy(dst + offset, src, size);
		buffer_->Unlock();
	}
}

Texture::Texture(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

Texture::~Texture()
{
	if (onDisposed_)
	{
		onDisposed_();
	}
	graphicsDevice_->Unregister(this);
	ES_SAFE_RELEASE(graphicsDevice_);
}

bool Texture::Init(const Effekseer::Backend::TextureParameter& param, const Effekseer::CustomVector<uint8_t>& initialData)
{
	int mw = std::max(param.Size[0], param.Size[1]);
	int count = 1;

	while (mw > 1)
	{
		mw = mw << 1;
		count++;
	}

	LLGI::TextureInitializationParameter texParam;
	texParam.Size = LLGI::Vec2I(param.Size[0], param.Size[1]);
	texParam.MipMapCount = param.MipLevelCount < 1 ? count : param.MipLevelCount;

	// TODO : Fix it
	texParam.MipMapCount = 1;

	LLGI::TextureFormatType format = LLGI::TextureFormatType::R8G8B8A8_UNORM;

	if (param.Format == Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM)
	{
		texParam.Format = LLGI::TextureFormatType::R8G8B8A8_UNORM;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::B8G8R8A8_UNORM)
	{
		texParam.Format = LLGI::TextureFormatType::B8G8R8A8_UNORM;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::R8_UNORM)
	{
		texParam.Format = LLGI::TextureFormatType::R8_UNORM;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::R16G16_FLOAT)
	{
		texParam.Format = LLGI::TextureFormatType::R16G16_FLOAT;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::R16G16B16A16_FLOAT)
	{
		texParam.Format = LLGI::TextureFormatType::R16G16B16A16_FLOAT;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::R32G32B32A32_FLOAT)
	{
		texParam.Format = LLGI::TextureFormatType::R32G32B32A32_FLOAT;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC1)
	{
		texParam.Format = LLGI::TextureFormatType::BC1;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC2)
	{
		texParam.Format = LLGI::TextureFormatType::BC2;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC3)
	{
		texParam.Format = LLGI::TextureFormatType::BC3;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM_SRGB)
	{
		texParam.Format = LLGI::TextureFormatType::R8G8B8A8_UNORM_SRGB;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::B8G8R8A8_UNORM_SRGB)
	{
		texParam.Format = LLGI::TextureFormatType::B8G8R8A8_UNORM_SRGB;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC1_SRGB)
	{
		texParam.Format = LLGI::TextureFormatType::BC1_SRGB;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC2_SRGB)
	{
		texParam.Format = LLGI::TextureFormatType::BC2_SRGB;
	}
	else if (param.Format == Effekseer::Backend::TextureFormatType::BC3_SRGB)
	{
		texParam.Format = LLGI::TextureFormatType::BC3_SRGB;
	}
	else
	{
		// not supported
		Effekseer::Log(Effekseer::LogType::Error, "The format is not supported.(" + std::to_string(static_cast<int>(param.Format)) + ")");
		return false;
	}

	auto texture = graphicsDevice_->GetGraphics()->CreateTexture(texParam);
	auto buf = texture->Lock();

	if (initialData.size() > 0)
	{
		memcpy(buf, initialData.data(), initialData.size());
	}

	texture->Unlock();

	texture_ = LLGI::CreateSharedPtr(texture);
	param_ = param;
	return true;
}

bool Texture::Init(uint64_t id, std::function<void()> onDisposed)
{
	auto texture = graphicsDevice_->GetGraphics()->CreateTexture(id);
	if (texture == nullptr)
	{
		return false;
	}

	texture_ = LLGI::CreateSharedPtr(texture);
	onDisposed_ = onDisposed;

	param_.Format = Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM;
	param_.Dimension = 2;
	param_.Size = {
		texture->GetSizeAs2D().X,
		texture->GetSizeAs2D().Y,
		0};
	param_.MipLevelCount = texture_->GetMipmapCount();
	param_.SampleCount = texture_->GetSamplingCount();
	param_.Usage = Effekseer::Backend::TextureUsageType::External;
	return true;
}

bool Texture::Init(LLGI::Texture* texture)
{
	LLGI::SafeAddRef(texture);
	texture_ = LLGI::CreateSharedPtr(texture);

	param_.Format = Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM;
	param_.Dimension = 2;
	param_.Size = {
		texture->GetSizeAs2D().X,
		texture->GetSizeAs2D().Y,
		0};
	param_.MipLevelCount = texture_->GetMipmapCount();
	param_.SampleCount = texture_->GetSamplingCount();
	param_.Usage = Effekseer::Backend::TextureUsageType::External;

	return true;
}

bool VertexLayout::Init(const Effekseer::Backend::VertexLayoutElement* elements, int32_t elementCount)
{
	std::array<LLGI::VertexLayoutFormat, 6> formats;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R32_FLOAT)] = LLGI::VertexLayoutFormat::R32_FLOAT;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R32G32_FLOAT)] = LLGI::VertexLayoutFormat::R32G32_FLOAT;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R32G32B32_FLOAT)] = LLGI::VertexLayoutFormat::R32G32B32_FLOAT;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R32G32B32A32_FLOAT)] = LLGI::VertexLayoutFormat::R32G32B32A32_FLOAT;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R8G8B8A8_UNORM)] = LLGI::VertexLayoutFormat::R8G8B8A8_UNORM;
	formats[static_cast<int32_t>(Effekseer::Backend::VertexLayoutFormat::R8G8B8A8_UINT)] = LLGI::VertexLayoutFormat::R8G8B8A8_UINT;

	elements_.resize(elementCount);

	for (int32_t i = 0; i < elementCount; i++)
	{
		elements_[i].Format = formats[static_cast<int32_t>(elements[i].Format)];
		elements_[i].Name = elements[i].SemanticName;
		elements_[i].Semantic = elements[i].SemanticIndex;
	}

	return true;
}

void VertexLayout::MakeGenerated()
{
	for (size_t i = 0; i < elements_.size(); i++)
	{
		elements_[i].Name = "TEXCOORD";
		elements_[i].Semantic = static_cast<int32_t>(i);
	}
}

RenderPass::RenderPass(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

RenderPass::~RenderPass()
{
	graphicsDevice_->Unregister(this);
	Effekseer::SafeRelease(graphicsDevice_);
}

bool RenderPass::Init(Effekseer::FixedSizeVector<Effekseer::Backend::TextureRef, Effekseer::Backend::RenderTargetMax>& textures, Effekseer::Backend::TextureRef depthTexture)
{
	LLGI::Texture* llgiTextures[Effekseer::Backend::RenderTargetMax] = {};
	for (size_t i = 0; i < Effekseer::Backend::RenderTargetMax; i++)
	{
		llgiTextures[i] = textures.at(i).DownCast<Backend::Texture>()->GetTexture().get();
	}
	LLGI::Texture* llgiDepthTexture = depthTexture.DownCast<Backend::Texture>()->GetTexture().get();

	renderPass_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateRenderPass(llgiTextures, Effekseer::Backend::RenderTargetMax, llgiDepthTexture));
	if (renderPass_ == nullptr)
	{
		return false;
	}

	textures_ = textures;
	depthTexture_ = depthTexture;

	return true;
}

Shader::Shader(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

Shader ::~Shader()
{
	graphicsDevice_->Unregister(this);
	Effekseer::SafeRelease(graphicsDevice_);
}

bool Shader::Init(const void* vertexShaderData, int32_t vertexShaderDataSize, const void* pixelShaderData, int32_t pixelShaderDataSize)
{
	auto vsd = Deserialize(vertexShaderData, vertexShaderDataSize);
	auto psd = Deserialize(pixelShaderData, pixelShaderDataSize);

	vertexShader_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateShader(vsd.data(), static_cast<int32_t>(vsd.size())));
	pixelShader_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateShader(psd.data(), static_cast<int32_t>(psd.size())));
	return vertexShader_ != nullptr && pixelShader_ != nullptr;
}

bool Shader::InitAsCompute(const void* computeShaderData, int32_t computeShaderDataSize)
{
	auto csd = Deserialize(computeShaderData, computeShaderDataSize);

	computeShader_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateShader(csd.data(), static_cast<int32_t>(csd.size())));
	return computeShader_ != nullptr;
}

UniformBuffer::UniformBuffer(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

UniformBuffer::~UniformBuffer()
{
	graphicsDevice_->Unregister(this);
	Effekseer::SafeRelease(graphicsDevice_);
}

bool UniformBuffer::Init(int32_t size, const void* initialData)
{
	buffer_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateBuffer(LLGI::BufferUsageType::Constant, size));

	return buffer_ != nullptr;
}

void UniformBuffer::UpdateData(const void* src, int32_t size, int32_t offset)
{
	void* dst = buffer_->Lock(offset, size);
	memcpy(dst, src, size);
	buffer_->Unlock();
}

ComputeBuffer::ComputeBuffer(GraphicsDevice* graphicsDevice)
	: graphicsDevice_(graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

ComputeBuffer::~ComputeBuffer()
{
	graphicsDevice_->Unregister(this);
	Effekseer::SafeRelease(graphicsDevice_);
}

bool ComputeBuffer::Init(int32_t stride, int32_t size, const void* initialData)
{
	stride_ = stride;
	buffer_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreateBuffer(LLGI::BufferUsageType::Compute , size));

	return buffer_ != nullptr;
}

void ComputeBuffer::UpdateData(const void* src, int32_t size, int32_t offset)
{
	void* dst = buffer_->Lock(offset, size);
	memcpy(dst, src, size);
	buffer_->Unlock();
}

PipelineState::PipelineState(GraphicsDevice* graphicsDevice)
{
	ES_SAFE_ADDREF(graphicsDevice_);
	graphicsDevice_->Register(this);
}

PipelineState::~PipelineState()
{
	graphicsDevice_->Unregister(this);
	Effekseer::SafeRelease(graphicsDevice_);
}

bool PipelineState::Init(const Effekseer::Backend::PipelineStateParameter& param)
{
	param_ = param;

	pip_ = LLGI::CreateSharedPtr(graphicsDevice_->GetGraphics()->CreatePiplineState());
	if (pip_ == nullptr)
	{
		return false;
	}

	auto shader = param.ShaderPtr.DownCast<Backend::Shader>();
	if (auto vertexShader = shader->GetVertexShader())
	{
		pip_->SetShader(LLGI::ShaderStageType::Vertex, vertexShader);
	}
	if (auto pixelShader = shader->GetPixelShader())
	{
		pip_->SetShader(LLGI::ShaderStageType::Pixel, pixelShader);
	}
	if (auto computeShader = shader->GetComputeShader())
	{
		pip_->SetShader(LLGI::ShaderStageType::Compute, computeShader);
	}

	pip_->Culling = static_cast<LLGI::CullingMode>(param.Culling);
	pip_->Topology = static_cast<LLGI::TopologyType>(param.Topology);
	
	pip_->IsBlendEnabled = param.IsBlendEnabled;
	pip_->BlendSrcFunc = static_cast<LLGI::BlendFuncType>(param.BlendSrcFunc);
	pip_->BlendDstFunc = static_cast<LLGI::BlendFuncType>(param.BlendDstFunc);
	pip_->BlendSrcFuncAlpha = static_cast<LLGI::BlendFuncType>(param.BlendSrcFuncAlpha);
	pip_->BlendDstFuncAlpha = static_cast<LLGI::BlendFuncType>(param.BlendDstFuncAlpha);
	pip_->BlendEquationRGB = static_cast<LLGI::BlendEquationType>(param.BlendEquationRGB);
	pip_->BlendEquationAlpha = static_cast<LLGI::BlendEquationType>(param.BlendEquationAlpha);

	pip_->IsDepthTestEnabled = param.IsDepthTestEnabled;
	pip_->IsDepthWriteEnabled = param.IsDepthWriteEnabled;
	pip_->DepthFunc = static_cast<LLGI::DepthFuncType>(param.DepthFunc);
	
	if (auto vertexLayout = param.VertexLayoutPtr.DownCast<Backend::VertexLayout>())
	{
		auto elements = vertexLayout->GetElements();
		pip_->VertexLayoutCount = (int32_t)elements.size();
		for (size_t i = 0; i < elements.size(); i++)
		{
			pip_->VertexLayouts[i] = elements[i].Format;
			pip_->VertexLayoutNames[i] = elements[i].Name;
			pip_->VertexLayoutSemantics[i] = elements[i].Semantic;
		}
	}

	return true;
}

GraphicsDevice::GraphicsDevice(LLGI::Graphics* graphics)
	: graphics_(graphics)
{
	ES_SAFE_ADDREF(graphics_);
}

GraphicsDevice::~GraphicsDevice()
{
	ES_SAFE_RELEASE(graphics_);
}

void GraphicsDevice::LostDevice()
{
	for (auto& o : objects_)
	{
		o->OnLostDevice();
	}
}

void GraphicsDevice::ResetDevice()
{
	for (auto& o : objects_)
	{
		o->OnResetDevice();
	}
}

LLGI::Graphics* GraphicsDevice::GetGraphics()
{
	return graphics_;
}

void GraphicsDevice::Register(DeviceObject* deviceObject)
{
	objects_.insert(deviceObject);
}

void GraphicsDevice::Unregister(DeviceObject* deviceObject)
{
	objects_.erase(deviceObject);
}

Effekseer::Backend::VertexBufferRef GraphicsDevice::CreateVertexBuffer(int32_t size, const void* initialData, bool isDynamic)
{
	auto ret = Effekseer::MakeRefPtr<VertexBuffer>(this);

	if (!ret->Init(size, isDynamic))
	{
		return nullptr;
	}

	if (initialData != nullptr)
	{
		ret->UpdateData(initialData, size, 0);
	}

	return ret;
}

Effekseer::Backend::IndexBufferRef GraphicsDevice::CreateIndexBuffer(int32_t elementCount, const void* initialData, Effekseer::Backend::IndexBufferStrideType stride)
{
	auto ret = Effekseer::MakeRefPtr<IndexBuffer>(this);

	if (!ret->Init(elementCount, stride == Effekseer::Backend::IndexBufferStrideType::Stride4 ? 4 : 2))
	{
		return nullptr;
	}

	if (initialData != nullptr)
	{
		ret->UpdateData(initialData, elementCount * (stride == Effekseer::Backend::IndexBufferStrideType::Stride4 ? 4 : 2), 0);
	}

	return ret;
}

Effekseer::Backend::TextureRef GraphicsDevice::CreateTexture(const Effekseer::Backend::TextureParameter& param, const Effekseer::CustomVector<uint8_t>& initialData)
{
	auto ret = Effekseer::MakeRefPtr<Texture>(this);

	if (!ret->Init(param, initialData))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::TextureRef GraphicsDevice::CreateTexture(uint64_t id, const std::function<void()>& onDisposed)
{
	auto ret = Effekseer::MakeRefPtr<Texture>(this);

	if (!ret->Init(id, onDisposed))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::TextureRef GraphicsDevice::CreateTexture(LLGI::Texture* texture)
{
	auto ret = Effekseer::MakeRefPtr<Texture>(this);

	if (!ret->Init(texture))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::VertexLayoutRef GraphicsDevice::CreateVertexLayout(const Effekseer::Backend::VertexLayoutElement* elements, int32_t elementCount)
{
	auto ret = Effekseer::MakeRefPtr<VertexLayout>();

	if (!ret->Init(elements, elementCount))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::ShaderRef GraphicsDevice::CreateShaderFromBinary(const void* vsData, int32_t vsDataSize, const void* psData, int32_t psDataSize)
{
	auto ret = Effekseer::MakeRefPtr<Shader>(this);

	if (!ret->Init(vsData, vsDataSize, psData, psDataSize))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::ShaderRef GraphicsDevice::CreateComputeShader(const void* csData, int32_t csDataSize)
{
	auto ret = Effekseer::MakeRefPtr<Shader>(this);

	if (!ret->InitAsCompute(csData, csDataSize))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::UniformBufferRef GraphicsDevice::CreateUniformBuffer(int32_t size, const void* initialData)
{
	auto ret = Effekseer::MakeRefPtr<UniformBuffer>(this);

	if (!ret->Init(size, initialData))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::ComputeBufferRef GraphicsDevice::CreateComputeBuffer(int32_t elementCount, int32_t elementSize, const void* initialData)
{
	auto ret = Effekseer::MakeRefPtr<ComputeBuffer>(this);

	if (!ret->Init(elementSize, elementCount * elementSize, initialData))
	{
		return nullptr;
	}

	return ret;
}

Effekseer::Backend::RenderPassRef GraphicsDevice::CreateRenderPass(Effekseer::FixedSizeVector<Effekseer::Backend::TextureRef, Effekseer::Backend::RenderTargetMax>& textures, Effekseer::Backend::TextureRef& depthTexture)
{
	auto ret = Effekseer::MakeRefPtr<RenderPass>(this);

	if (!ret->Init(textures, depthTexture))
	{
		return nullptr;
	}

	return ret;
}

void GraphicsDevice::SetCommandList(LLGI::CommandList* commandList)
{
	commandList_ = commandList;
}

void GraphicsDevice::Draw(const Effekseer::Backend::DrawParameter& drawParam)
{
}

void GraphicsDevice::BeginRenderPass(Effekseer::Backend::RenderPassRef& renderPass, bool isColorCleared, bool isDepthCleared, Effekseer::Color clearColor)
{
	if (renderPass == nullptr)
	{
		return;
	}

	auto llgiRenderPass = renderPass.DownCast<Backend::RenderPass>()->GetRenderPass();
	llgiRenderPass->SetIsColorCleared(isColorCleared);
	llgiRenderPass->SetClearColor(LLGI::Color8(clearColor.R, clearColor.G, clearColor.B, clearColor.A));
	llgiRenderPass->SetIsDepthCleared(isDepthCleared);

	commandList_->BeginRenderPass(llgiRenderPass);
}

void GraphicsDevice::EndRenderPass()
{
	commandList_->EndRenderPass();
}

void GraphicsDevice::Dispatch(const Effekseer::Backend::DispatchParameter& dispatchParam)
{
	auto pipeline = dispatchParam.PipelineStatePtr.DownCast<PipelineState>();
	if (pipeline == nullptr)
	{
		return;
	}
	commandList_->SetPipelineState(pipeline->GetPipelineState());

	for (int32_t slot = 0; slot < dispatchParam.BufferSlotCount; slot++)
	{
		if (auto computeBuffer = dispatchParam.ROComputeBufferPtrs[slot].DownCast<ComputeBuffer>())
		{
			commandList_->SetComputeBuffer(computeBuffer->GetBuffer(), computeBuffer->GetStride(), slot, LLGI::ShaderStageType::Compute);
		}
		else
		{
			commandList_->SetComputeBuffer(nullptr, 0, slot, LLGI::ShaderStageType::Compute);
		}
	}
	for (int32_t slot = 0; slot < dispatchParam.BufferSlotCount; slot++)
	{
		if (auto computeBuffer = dispatchParam.RWComputeBufferPtrs[slot].DownCast<ComputeBuffer>())
		{
			commandList_->SetComputeBuffer(computeBuffer->GetBuffer(), computeBuffer->GetStride(), 4 + slot, LLGI::ShaderStageType::Compute);
		}
		else
		{
			commandList_->SetComputeBuffer(nullptr, 0, 4 + slot, LLGI::ShaderStageType::Compute);
		}
	}

	for (int32_t slot = 0; slot < 1; slot++)
	{
		if (auto uniformBuffer = dispatchParam.UniformBufferPtrs[slot].DownCast<UniformBuffer>())
		{
			commandList_->SetConstantBuffer(uniformBuffer->GetBuffer(), LLGI::ShaderStageType::Compute);
		}
		else
		{
			commandList_->SetConstantBuffer(nullptr, LLGI::ShaderStageType::Compute);
		}
	}

	for (int32_t slot = 0; slot < dispatchParam.TextureSlotCount; slot++)
	{
		LLGI::TextureMinMagFilter filter = (dispatchParam.TextureSamplingTypes[slot] == Effekseer::Backend::TextureSamplingType::Nearest) ?
			LLGI::TextureMinMagFilter::Nearest : LLGI::TextureMinMagFilter::Linear;
		LLGI::TextureWrapMode wrap = (dispatchParam.TextureWrapTypes[slot] == Effekseer::Backend::TextureWrapType::Clamp) ?
			LLGI::TextureWrapMode::Clamp : LLGI::TextureWrapMode::Repeat;
		
		if (auto texture = dispatchParam.TexturePtrs[slot].DownCast<Texture>())
		{
			commandList_->SetTexture(texture->GetTexture().get(), wrap, filter, slot, LLGI::ShaderStageType::Compute);
		}
		else
		{
			commandList_->SetTexture(nullptr, wrap, filter, slot, LLGI::ShaderStageType::Compute);
		}
	}

	auto gc = dispatchParam.GroupCount;
	auto tc = dispatchParam.ThreadCount;
	commandList_->Dispatch(gc[0], gc[1], gc[2], tc[0], tc[1], tc[2]);
}

void GraphicsDevice::BeginComputePass()
{
	commandList_->BeginComputePass();
}

void GraphicsDevice::EndComputePass()
{
	commandList_->EndComputePass();
}

bool GraphicsDevice::UpdateUniformBuffer(Effekseer::Backend::UniformBufferRef& buffer, int32_t size, int32_t offset, const void* data)
{
	if (buffer == nullptr)
	{
		return false;
	}

	auto b = buffer.DownCast<Backend::UniformBuffer>();

	b->UpdateData(data, size, offset);

	return true;
}

bool GraphicsDevice::UpdateComputeBuffer(Effekseer::Backend::ComputeBufferRef& buffer, int32_t size, int32_t offset, const void* data)
{
	if (buffer == nullptr)
	{
		return false;
	}

	auto b = buffer.DownCast<Backend::ComputeBuffer>();

	b->UpdateData(data, size, offset);

	return true;
}

} // namespace Backend
} // namespace EffekseerRendererLLGI