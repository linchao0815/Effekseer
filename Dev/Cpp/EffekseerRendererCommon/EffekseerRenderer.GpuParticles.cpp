#include "EffekseerRenderer.GpuParticles.h"
#include "EffekseerRenderer.CommonUtils.h"
#include "EffekseerRenderer.Renderer_Impl.h"
#include "../Effekseer/Effekseer/Noise/CurlNoise.h"

namespace EffekseerRenderer
{

namespace
{

inline constexpr uint32_t RoundUp(uint32_t x, uint32_t unit)
{
	return (x + unit - 1) / unit * unit;
}

const Effekseer::Vector3D VEC_UP = {0.0f, 1.0f, 0.0f};
const Effekseer::Vector3D VEC_RIGHT = {1.0f, 0.0f, 0.0f};
const Effekseer::Vector3D VEC_FRONT = {0.0f, 0.0f, 1.0f};
const Effekseer::Color COLOR_WHITE = {255, 255, 255, 255};

Effekseer::ModelRef CreateSpriteModel()
{
	Effekseer::CustomVector<Effekseer::Model::Vertex> vertexes = {
		{ { -0.5f,  0.5f, 0.0f }, VEC_FRONT, VEC_UP, VEC_RIGHT, {0.0f, 0.0f}, COLOR_WHITE },
		{ { -0.5f, -0.5f, 0.0f }, VEC_FRONT, VEC_UP, VEC_RIGHT, {0.0f, 1.0f}, COLOR_WHITE },
		{ {  0.5f,  0.5f, 0.0f }, VEC_FRONT, VEC_UP, VEC_RIGHT, {1.0f, 0.0f}, COLOR_WHITE },
		{ {  0.5f, -0.5f, 0.0f }, VEC_FRONT, VEC_UP, VEC_RIGHT, {1.0f, 1.0f}, COLOR_WHITE },
	};
	Effekseer::CustomVector<Effekseer::Model::Face> faces = {
		{ {0, 2, 1} }, { {1, 2, 3} }
	};
	return Effekseer::MakeRefPtr<Effekseer::Model>(vertexes, faces);
}

Effekseer::ModelRef CreateTrailModel()
{
	const size_t TrailJoints = 256;
	Effekseer::CustomVector<Effekseer::Model::Vertex> vertexes;

	vertexes.resize(TrailJoints * 2);
	for (size_t i = 0; i < TrailJoints * 2; i++) {
		Effekseer::Model::Vertex v{};
		v.Position.X = (i % 2 == 0) ? -0.5f : 0.5f;
		v.Position.Y = 0.0f;
		v.Position.Z = 0.0f;
		v.Binormal = VEC_FRONT;
		v.Normal = VEC_UP;
		v.Tangent = VEC_RIGHT;
		v.UV.X = (i % 2 == 0) ? 0.0f : 1.0f;
		v.UV.Y = (float)(i / 2) / (float)(TrailJoints - 1);
		v.VColor = COLOR_WHITE;
		vertexes[i] = v;
	}

	Effekseer::CustomVector<Effekseer::Model::Face> faces;
	faces.resize((TrailJoints - 1) * 2);
	for (size_t i = 0; i < TrailJoints - 1; i++) {
		int32_t ofs = (int32_t)(2 * i);
		faces[i * 2 + 0] = Effekseer::Model::Face{ { ofs + 0, ofs + 2, ofs + 1 } };
		faces[i * 2 + 1] = Effekseer::Model::Face{ { ofs + 1, ofs + 2, ofs + 3 } };
	}
	return Effekseer::MakeRefPtr<Effekseer::Model>(vertexes, faces);
}

std::vector<Effekseer::Model::Vertex> GeneratePointCache(Effekseer::ModelRef model, uint32_t pointCount, uint32_t seed)
{
	std::vector<std::vector<float>> modelFaceAreas;
	float totalArea = 0.0f;

	int32_t frameCount = model->GetFrameCount();
	modelFaceAreas.resize((size_t)frameCount);

	for (int32_t frameIndex = 0; frameIndex < frameCount; frameIndex++)
	{
		auto vertexes = model->GetVertexes(frameIndex);
		int32_t vertexCount = model->GetVertexCount(frameIndex);
		auto faces = model->GetFaces(frameIndex);
		int32_t faceCount = model->GetFaceCount(frameIndex);

		auto& faceAreas = modelFaceAreas[frameIndex];
		faceAreas.resize((size_t)faceCount);

		for (int32_t faceIndex = 0; faceIndex < faceCount; faceIndex++)
		{
			auto& v0 = vertexes[faces[faceIndex].Indexes[0]];
			auto& v1 = vertexes[faces[faceIndex].Indexes[1]];
			auto& v2 = vertexes[faces[faceIndex].Indexes[2]];
			float r0 = Effekseer::Vector3D::Length(v0.Position - v1.Position);
			float r1 = Effekseer::Vector3D::Length(v1.Position - v2.Position);
			float r2 = Effekseer::Vector3D::Length(v2.Position - v0.Position);
			float s = (r0 + r1 + r2) / 2.0f;
			float area = sqrt(s * (s - r0) * (s - r1) * (s - r2));
			totalArea += area;
			faceAreas[faceIndex] = area;
		}
	}

	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> random(0.0f, 1.0f);

	auto lerpVec3 = [](Effekseer::Vector3D a, Effekseer::Vector3D b, float t) {
		return a + (b - a) * t;
	};
	auto lerpVec2 = [](Effekseer::Vector2D a, Effekseer::Vector2D b, float t) {
		float x = a.X + (b.X - a.X) * t;
		float y = a.Y + (b.Y - a.Y) * t;
		return Effekseer::Vector2D{ x, y };
	};
	auto lerpColor = [](Effekseer::Color a, Effekseer::Color b, float t) {
		return Effekseer::Color::Lerp(a, b, t);
	};
	auto randomVector3 = [&](Effekseer::Vector3D a, Effekseer::Vector3D b, Effekseer::Vector3D c) {
		return lerpVec3(lerpVec3(a, b, random(engine)), lerpVec3(a, c, random(engine)), random(engine));
	};
	auto randomVector2 = [&](Effekseer::Vector2D a, Effekseer::Vector2D b, Effekseer::Vector2D c) {
		return lerpVec2(lerpVec2(a, b, random(engine)), lerpVec2(a, c, random(engine)), random(engine));
	};
	auto randomColor = [&](Effekseer::Color a, Effekseer::Color b, Effekseer::Color c) {
		return lerpColor(lerpColor(a, b, random(engine)), lerpColor(a, c, random(engine)), random(engine));
	};

	std::vector<Effekseer::Model::Vertex> points;
	points.resize(pointCount);

	uint32_t pointIndex = 0;
	float summedArea = 0.0f;
	for (int32_t frameIndex = 0; frameIndex < frameCount; frameIndex++)
	{
		auto vertexes = model->GetVertexes(frameIndex);
		int32_t vertexCount = model->GetVertexCount(frameIndex);
		auto faces = model->GetFaces(frameIndex);
		int32_t faceCount = model->GetFaceCount(frameIndex);

		auto& faceAreas = modelFaceAreas[frameIndex];

		for (int32_t faceIndex = 0; faceIndex < faceCount; faceIndex++)
		{
			auto& v0 = vertexes[faces[faceIndex].Indexes[0]];
			auto& v1 = vertexes[faces[faceIndex].Indexes[1]];
			auto& v2 = vertexes[faces[faceIndex].Indexes[2]];

			summedArea += faceAreas[faceIndex];

			uint32_t genCount = (uint32_t)(summedArea / totalArea * pointCount) - pointIndex;
			for (uint32_t i = 0; i < genCount; i++)
			{
				auto& point = points[(size_t)pointIndex + i];
				point.Position = randomVector3(v0.Position, v1.Position, v2.Position);
				point.Normal = randomVector3(v0.Normal, v1.Normal, v2.Normal);
				point.Tangent = randomVector3(v0.Tangent, v1.Tangent, v2.Tangent);
				point.Binormal = randomVector3(v0.Binormal, v1.Binormal, v2.Binormal);
				point.UV = randomVector2(v0.UV, v1.UV, v2.UV);
				point.VColor = randomColor(v0.VColor, v1.VColor, v2.VColor);
			}
			pointIndex += genCount;
		}
	}

	return points;
}

}

void GpuParticles::BlockAllocator::Init(uint32_t bufferSize, uint32_t blockSize)
{
	bufferBlocks.reserve(bufferSize / blockSize);
	bufferBlocks.push_back({0, bufferSize});
}

GpuParticles::Block GpuParticles::BlockAllocator::Allocate(uint32_t size)
{
	Block result{};
	for (size_t i = 0; i < bufferBlocks.size(); i++)
	{
		Block& block = bufferBlocks[i];
		if (block.size >= size)
		{
			if (block.size == size)
			{
				result = block;
				bufferBlocks.erase(bufferBlocks.begin() + i);
				break;
			}
			else
			{
				result = Block{block.offset, size};
				block.offset += size;
				break;
			}
		}
	}
	return result;
}

void GpuParticles::BlockAllocator::Deallocate(Block releasingBlock)
{
	if (releasingBlock.size == 0)
	{
		return;
	}

	Block newBlock = releasingBlock;
	uint32_t newTail = newBlock.offset + newBlock.size;
	for (size_t i = 0; i < bufferBlocks.size(); i++)
	{
		Block& block = bufferBlocks[i];
		if (block.offset + block.size == newBlock.offset)
		{
			block.size += newBlock.size;

			if (i + 1 < bufferBlocks.size() && block.offset + block.size == bufferBlocks[i + 1].offset)
			{
				block.size += bufferBlocks[i + 1].size;
				bufferBlocks.erase(bufferBlocks.begin() + i + 1);
			}
			break;
		}
		else if (newBlock.offset + newBlock.size == block.offset)
		{
			block.offset -= newBlock.size;
			break;
		}
		else if (newBlock.offset < block.offset)
		{
			bufferBlocks.insert(bufferBlocks.begin() + i, newBlock);
			break;
		}
	}
}

GpuParticles::GpuParticles(Renderer* renderer)
	: m_rendererBase(renderer)
{
}

GpuParticles::~GpuParticles()
{
}

bool GpuParticles::InitSystem(const Settings& settings)
{
	auto graphics = m_rendererBase->GetGraphicsDevice();

	m_settings = settings;
	m_paramSets.resize(settings.EmitterMaxCount);
	m_resources.resize(settings.EmitterMaxCount);
	m_emitters.resize(settings.EmitterMaxCount);

	for (uint32_t index = 0; index < settings.EmitterMaxCount; index++)
	{
		m_paramFreeList.push_back(index);
		m_emitterFreeList.push_back(index);
		m_ubufParamSets.push_back(graphics->CreateUniformBuffer(sizeof(ParameterSet), nullptr));
		m_ubufEmitters.push_back(graphics->CreateUniformBuffer(sizeof(Emitter), nullptr));
	}
	m_newParamSetIDs.reserve(settings.EmitterMaxCount);
	m_newEmitterIDs.reserve(settings.EmitterMaxCount);

	m_particleAllocator.Init(settings.ParticleMaxCount, ParticleUnitSize);
	m_trailAllocator.Init(settings.TrailMaxCount, ParticleUnitSize);

	Constants cdata{};
	m_ubufConstants = graphics->CreateUniformBuffer(sizeof(Constants), &cdata);
	m_cbufParticles = graphics->CreateComputeBuffer((int32_t)settings.ParticleMaxCount, (int32_t)sizeof(Particle), nullptr);
	m_cbufTrails = graphics->CreateComputeBuffer((int32_t)settings.TrailMaxCount, (int32_t)sizeof(Trail), nullptr);

	m_vertexLayout = EffekseerRenderer::GetModelRendererVertexLayout(graphics);

	m_modelSprite = CreateSpriteModel();
	m_modelSprite->StoreBufferToGPU(graphics.Get());

	m_modelTrail = CreateTrailModel();
	m_modelTrail->StoreBufferToGPU(graphics.Get());

	{
		Effekseer::Backend::TextureParameter texParam{};
		texParam.Format = Effekseer::Backend::TextureFormatType::R8G8B8A8_UNORM;
		texParam.Size = { 1, 1, 1 };
		texParam.Dimension = 3;
		m_dummyVectorField = graphics->CreateTexture(texParam, {0, 0, 0, 0});
	}
	{
		uint32_t dummyData[4] = {};
		m_dummyEmitPoints = graphics->CreateComputeBuffer(16, 16, dummyData);
	}

	m_dummyColorTexture = m_rendererBase->GetImpl()->GetProxyTexture(EffekseerRenderer::ProxyTextureType::White);
	m_dummyNormalTexture = m_rendererBase->GetImpl()->GetProxyTexture(EffekseerRenderer::ProxyTextureType::Normal);

	return true;
}

void GpuParticles::SetShaders(const Shaders& shaders)
{
	m_shaders = shaders;

	auto graphics = m_rendererBase->GetGraphicsDevice();

	{
		Effekseer::Backend::PipelineStateParameter params{};
		params.ShaderPtr = m_shaders.csParticleClear;
		m_pipelineParticleClear = graphics->CreatePipelineState(params);
	}
	{
		Effekseer::Backend::PipelineStateParameter params{};
		params.ShaderPtr = m_shaders.csParticleSpawn;
		m_pipelineParticleSpawn = graphics->CreatePipelineState(params);
	}
	{
		Effekseer::Backend::PipelineStateParameter params{};
		params.ShaderPtr = m_shaders.csParticleUpdate;
		m_pipelineParticleUpdate = graphics->CreatePipelineState(params);
	}
}

void GpuParticles::UpdateFrame(float deltaTime)
{
	auto renderer = m_rendererBase;
	auto graphics = renderer->GetGraphicsDevice();

	// Update constant buffer
	Constants cdata{};
	cdata.ProjMat = renderer->GetProjectionMatrix();
	cdata.CameraMat = renderer->GetCameraMatrix();

	Effekseer::Matrix44	inv{};
	Effekseer::Matrix44::Inverse(inv, cdata.CameraMat);
	cdata.BillboardMat = {
		float4{ inv.Values[0][0], inv.Values[1][0], inv.Values[2][0], 0.0f },
		float4{ inv.Values[0][1], inv.Values[1][1], inv.Values[2][1], 0.0f },
		float4{ inv.Values[0][2], inv.Values[1][2], inv.Values[2][2], 0.0f }
	};
	cdata.YAxisBillboardMat = {
		float4{ inv.Values[0][0], 0.0f, inv.Values[2][0], 0.0f },
		float4{ inv.Values[0][1], 1.0f, inv.Values[2][1], 0.0f },
		float4{ inv.Values[0][2], 0.0f, inv.Values[2][2], 0.0f }
	};
	cdata.CameraPos = renderer->GetCameraPosition();
	cdata.CameraFront = renderer->GetCameraFrontDirection();
	cdata.DeltaTime = deltaTime;
	graphics->UpdateUniformBuffer(m_ubufConstants, sizeof(Constants), 0, &cdata);

	for (auto paramID : m_newParamSetIDs)
	{
		// Initialize parameter data
		graphics->UpdateUniformBuffer(m_ubufParamSets[paramID], sizeof(ParameterSet), 0, &m_paramSets[paramID]);
	}
	m_newParamSetIDs.clear();

	for (auto emitterID : m_newEmitterIDs)
	{
		// Initialize particle data region
		auto& emitter = m_emitters[emitterID];
		graphics->UpdateUniformBuffer(m_ubufEmitters[emitterID], sizeof(Emitter), 0, &emitter);

		ComputeCommand command;
		command.PipelineStatePtr = m_pipelineParticleClear;

		command.UniformBufferPtrs[0] = m_ubufConstants;
		command.UniformBufferPtrs[1] = m_ubufParamSets[emitter.GetParamID()];
		command.UniformBufferPtrs[2] = m_ubufEmitters[emitterID];
		command.SetComputeBuffer(0, m_cbufParticles, false);

		command.GroupCount = { (int32_t)emitter.ParticleSize / 256, 1, 1 };
		command.ThreadCount = { 256, 1, 1 };
		graphics->Dispatch(command);
	}
	m_newEmitterIDs.clear();

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Spawn particles
	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& paramRes = m_resources[emitter.GetParamID()];

			emitter.TimeCount += deltaTime;

			emitter.TotalEmitCount += emitter.NextEmitCount;
			emitter.NextEmitCount = 0;

			if (emitter.TotalEmitCount >= paramSet.EmitCount)
			{
				emitter.SetEmitting(false);
				emitter.TimeStopped = emitter.TimeCount;
			}

			if (emitter.IsEmitting())
			{
				if (emitter.TimeCount >= paramSet.EmitOffset)
				{
					emitter.NextEmitCount = (uint32_t)(round(paramSet.EmitPerFrame * deltaTime));

					if (paramSet.EmitCount >= 0)
					{
						emitter.NextEmitCount = std::clamp((int32_t)emitter.NextEmitCount, 0, paramSet.EmitCount - (int32_t)emitter.TotalEmitCount);
					}
				}

				if (paramSet.EmitShapeType == EmitShape::Model)
				{
					if (!paramRes.EmitPoints)
					{
						if (auto model = paramRes.Effect->GetModel(paramSet.EmitShapeData.ModelIndex))
						{
							auto points = GeneratePointCache(model, 16 * 1024, 1);
							paramRes.EmitPointCount = (uint32_t)points.size();
							paramRes.EmitPoints = graphics->CreateComputeBuffer(
								(int32_t)points.size(), (int32_t)sizeof(Effekseer::Model::Vertex), points.data());
						}
					}
					emitter.EmitPointCount = paramRes.EmitPointCount;
				}

				graphics->UpdateUniformBuffer(m_ubufEmitters[emitterID], sizeof(Emitter), 0, &emitter);

				if (emitter.NextEmitCount > 0)
				{
					ComputeCommand command;
					command.PipelineStatePtr = m_pipelineParticleSpawn;

					command.UniformBufferPtrs[0] = m_ubufConstants;
					command.UniformBufferPtrs[1] = m_ubufParamSets[emitter.GetParamID()];
					command.UniformBufferPtrs[2] = m_ubufEmitters[emitterID];
					command.SetComputeBuffer(0, m_cbufParticles, false);
					command.SetComputeBuffer(1, (paramRes.EmitPoints) ? paramRes.EmitPoints : m_dummyEmitPoints, true);

					command.GroupCount = { (int32_t)emitter.NextEmitCount, 1, 1 };
					command.ThreadCount = { 1, 1, 1 };
					graphics->Dispatch(command);
				}
			}
			else
			{
				if (GetEmitterParticleCount(emitter, paramSet) == 0)
				{
					FreeEmitter(emitterID);
				}
			}
		}
	}

	// Update particles
	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& paramRes = m_resources[emitter.GetParamID()];

			ComputeCommand command;
			command.PipelineStatePtr = m_pipelineParticleUpdate;

			command.UniformBufferPtrs[0] = m_ubufConstants;
			command.UniformBufferPtrs[1] = m_ubufParamSets[emitter.GetParamID()];
			command.UniformBufferPtrs[2] = m_ubufEmitters[emitterID];
			command.SetComputeBuffer(0, m_cbufParticles, false);
			command.SetComputeBuffer(1, m_cbufTrails, false);

			command.SetTexture(2, (paramRes.NoiseVectorField) ? paramRes.NoiseVectorField : m_dummyVectorField,
				Effekseer::Backend::TextureWrapType::Repeat, Effekseer::Backend::TextureSamplingType::Linear);

			command.GroupCount = { (int32_t)emitter.ParticleSize / 256, 1, 1 };
			command.ThreadCount = { 256, 1, 1 };
			graphics->Dispatch(command);

			if (emitter.TrailSize > 0)
			{
				emitter.TrailPhase = (emitter.TrailPhase + 1) % paramSet.ShapeData;
			}
		}
	}
}

void GpuParticles::RenderFrame()
{
	auto renderer = m_rendererBase;
	auto graphics = renderer->GetGraphicsDevice();

	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive())
		{
			auto& paramSet = m_paramSets[emitter.GetParamID()];
			auto& paramRes = m_resources[emitter.GetParamID()];

			Effekseer::Backend::DrawParameter drawParams;
			drawParams.PipelineStatePtr = paramRes.PiplineState;

			drawParams.VertexUniformBufferPtrs[0] = m_ubufConstants;
			drawParams.VertexUniformBufferPtrs[1] = m_ubufParamSets[emitter.GetParamID()];
			drawParams.VertexUniformBufferPtrs[2] = m_ubufEmitters[emitterID];

			drawParams.SetComputeBuffer(0, m_cbufParticles);
			drawParams.SetComputeBuffer(1, m_cbufTrails);

			Effekseer::Backend::TextureRef colorTex = m_dummyColorTexture;
			if (auto tex = paramRes.Effect->GetColorImage(paramSet.ColorTexIndex))
			{
				colorTex = tex->GetBackend();
			}
			drawParams.SetTexture(2, colorTex, 
				static_cast<Effekseer::Backend::TextureWrapType>(paramSet.ColorTexWrap), 
				static_cast<Effekseer::Backend::TextureSamplingType>(paramSet.ColorTexFilter));

			Effekseer::Backend::TextureRef normalTex = m_dummyNormalTexture;
			if (auto tex = paramRes.Effect->GetColorImage(paramSet.NormalTexIndex))
			{
				normalTex = tex->GetBackend();
			}
			drawParams.SetTexture(3, colorTex, 
				static_cast<Effekseer::Backend::TextureWrapType>(paramSet.NormalTexWrap), 
				static_cast<Effekseer::Backend::TextureSamplingType>(paramSet.NormalTexFilter));

			Effekseer::ModelRef model;
			switch (paramSet.ShapeType)
			{
				case 0: model = m_modelSprite; break;
				case 1: model = paramRes.Effect->GetModel(paramSet.ShapeData); break;
				case 2: model = m_modelTrail; break;
			}

			if (model)
			{
				if (!model->GetIsBufferStoredOnGPU())
				{
					model->StoreBufferToGPU(graphics.Get());
				}

				int32_t modelFrameCount = model->GetFrameCount();
				for (int32_t i = 0; i < modelFrameCount; i++)
				{
					drawParams.VertexBufferPtr = model->GetVertexBuffer(i);
					drawParams.VertexStride = sizeof(Effekseer::Model::Vertex);
					drawParams.IndexBufferPtr = model->GetIndexBuffer(i);

					if (emitter.TrailSize > 0)
					{
						drawParams.PrimitiveCount = (paramSet.ShapeData - 1) * 2;
					}
					else
					{
						drawParams.PrimitiveCount = model->GetFaceCount(i);
					}
					drawParams.InstanceCount = emitter.ParticleSize;
					
					graphics->Draw(drawParams);
				}
			}
		}
	}
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

	auto graphics = m_rendererBase->GetGraphicsDevice();

	ParameterRes paramRes;
	paramRes.Effect = effect;
	paramRes.PiplineState = CreatePiplineState(paramSet);

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

		paramRes.NoiseVectorField = graphics->CreateTexture(texParam, initialData);
	}
	m_resources[paramID] = std::move(paramRes);

	return paramID;
}

void GpuParticles::RemoveParamSet(ParamID paramID)
{
	assert(paramID >= 0 && paramID < m_paramSets.size());
	std::lock_guard<std::mutex> lock(m_mutex);
	m_paramFreeList.push_front(paramID);
}

const GpuParticles::ParameterSet* GpuParticles::GetParamSet(ParamID paramID) const
{
	assert(paramID >= 0 && paramID < m_paramSets.size());
	return &m_paramSets[paramID];
}

GpuParticles::EmitterID GpuParticles::NewEmitter(ParamID paramID, ParticleGroupID groupID)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_emitterFreeList.size() == 0)
	{
		return InvalidID;
	}

	EmitterID emitterID = m_emitterFreeList.front();

	auto& paramSet = m_paramSets[paramID];
	uint32_t particlesMaxCount = (uint32_t)(round((double)paramSet.LifeTime[0] * paramSet.EmitPerFrame));
	particlesMaxCount = std::min(particlesMaxCount, (uint32_t)paramSet.EmitCount);
	particlesMaxCount = RoundUp(particlesMaxCount, ParticleUnitSize);

	Emitter& emitter = m_emitters[emitterID];
	emitter.SetFlagBits(true, false, paramID);
	emitter.Seed = m_random();
	emitter.ParticleHead = 0;
	emitter.ParticleSize = 0;
	emitter.TrailHead = 0;
	emitter.TrailSize = 0;
	emitter.TrailPhase = 0;
	emitter.NextEmitCount = 0;
	emitter.TotalEmitCount = 0;
	emitter.EmitPointCount = 0;
	emitter.TimeCount = 0.0f;
	emitter.TimeStopped = 0.0f;
	emitter.GroupID = groupID;
	emitter.Color = Effekseer::Color(255, 255, 255, 255);
	emitter.Transform = {
		float4{ 1.0f, 0.0f, 0.0f, 0.0f },
		float4{ 0.0f, 1.0f, 0.0f, 0.0f },
		float4{ 0.0f, 0.0f, 1.0f, 0.0f }
	};

	Block particleBlock = m_particleAllocator.Allocate(particlesMaxCount);
	if (particleBlock.size == 0)
	{
		return InvalidID;
	}
	emitter.ParticleHead = particleBlock.offset;
	emitter.ParticleSize = particleBlock.size;

	if (paramSet.ShapeType == RenderShape::Trail)
	{
		Block trailBlock = m_trailAllocator.Allocate(particlesMaxCount * paramSet.ShapeData);
		if (trailBlock.size == 0)
		{
			m_particleAllocator.Deallocate(particleBlock);
			return InvalidID;
		}
		emitter.TrailHead = trailBlock.offset;
		emitter.TrailSize = trailBlock.size;
	}

	m_newEmitterIDs.push_back(emitterID);
	m_emitterFreeList.pop_front();

	return emitterID;
}

void GpuParticles::FreeEmitter(EmitterID emitterID)
{
	assert(emitterID >= 0 && emitterID < m_emitters.size());

	Emitter& emitter = m_emitters[emitterID];
	emitter.FlagBits = 0;
	emitter.GroupID = 0;

	m_particleAllocator.Deallocate({ emitter.ParticleHead, emitter.ParticleSize });
	m_trailAllocator.Deallocate({ emitter.TrailHead, emitter.TrailSize });
	m_emitterFreeList.push_front(emitterID);
}

void GpuParticles::StartEmit(EmitterID emitterID)
{
	assert(emitterID >= 0 && emitterID < m_emitters.size());
	Emitter& emitter = m_emitters[emitterID];
	emitter.SetEmitting(true);
	emitter.TimeCount = 0.0f;
}

void GpuParticles::StopEmit(EmitterID emitterID)
{
	assert(emitterID >= 0 && emitterID < m_emitters.size());
	Emitter& emitter = m_emitters[emitterID];
	emitter.SetEmitting(false);
	emitter.TimeStopped = emitter.TimeCount;
}

void GpuParticles::SetTransform(EmitterID emitterID, const Effekseer::Matrix43& transform)
{
	assert(emitterID >= 0 && emitterID < m_emitters.size());
	Emitter& emitter = m_emitters[emitterID];
	emitter.Transform = {
		float4{ transform.Value[0][0], transform.Value[0][1], transform.Value[0][2], transform.Value[3][0] },
		float4{ transform.Value[1][0], transform.Value[1][1], transform.Value[1][2], transform.Value[3][1] },
		float4{ transform.Value[2][0], transform.Value[2][1], transform.Value[2][2], transform.Value[3][2] }
	};
}

void GpuParticles::SetColor(EmitterID emitterID, Effekseer::Color color)
{
	assert(emitterID >= 0 && emitterID < m_emitters.size());
	Emitter& emitter = m_emitters[emitterID];
	emitter.Color = color;
}

void GpuParticles::KillParticles(ParticleGroupID groupID)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive() && emitter.GroupID == groupID)
		{
			FreeEmitter(emitterID);
		}
	}
}

int32_t GpuParticles::GetParticleCount(ParticleGroupID groupID)
{
	int32_t count = 0;

	for (EmitterID emitterID = 0; emitterID < (EmitterID)m_emitters.size(); emitterID++)
	{
		auto& emitter = m_emitters[emitterID];
		if (emitter.IsAlive() && emitter.GroupID == groupID)
		{
			count += GetEmitterParticleCount(emitter, m_paramSets[emitter.GetParamID()]);
		}
	}
	return count;
}


int32_t GpuParticles::GetEmitterParticleCount(const Emitter& emitter, const ParameterSet& paramSet)
{
	int32_t maxParticleCount = static_cast<int32_t>(paramSet.LifeTime[0] * paramSet.EmitPerFrame);
	float emitDuration = static_cast<float>(paramSet.EmitCount) / static_cast<float>(paramSet.EmitPerFrame);
	float timeCount = std::max(0.0f, emitter.TimeCount - paramSet.EmitOffset);

	if (!emitter.IsEmitting())
	{
		emitDuration = std::min(emitDuration, emitter.TimeStopped - paramSet.EmitOffset);
	}
	if (timeCount < paramSet.LifeTime[0])
	{
		return static_cast<int32_t>(paramSet.EmitPerFrame * timeCount);
	}
	else if (timeCount < emitDuration)
	{
		return maxParticleCount;
	}
	else
	{
		return std::max(0, maxParticleCount - static_cast<int32_t>(paramSet.EmitPerFrame * (timeCount - emitDuration)));
	}
}

GpuParticles::PipelineStateRef GpuParticles::CreatePiplineState(const ParameterSet& paramSet)
{
	using namespace Effekseer::Backend;

	PipelineStateParameter pipParams;
	if ((Effekseer::AlphaBlendType)paramSet.BlendType == Effekseer::AlphaBlendType::Opacity)
	{
		pipParams.IsBlendEnabled = false;
	}
	else
	{
		pipParams.IsBlendEnabled = true;
		switch ((Effekseer::AlphaBlendType)paramSet.BlendType)
		{
		case Effekseer::AlphaBlendType::Blend:
			pipParams.BlendEquationRGB = BlendEquationType::Add;
			pipParams.BlendSrcFunc = BlendFuncType::SrcAlpha;
			pipParams.BlendDstFunc = BlendFuncType::OneMinusSrcAlpha;
			break;
		case Effekseer::AlphaBlendType::Add:
			pipParams.BlendEquationRGB = BlendEquationType::Add;
			pipParams.BlendSrcFunc = BlendFuncType::SrcAlpha;
			pipParams.BlendDstFunc = BlendFuncType::One;
			break;
		case Effekseer::AlphaBlendType::Sub:
			pipParams.BlendDstFunc = BlendFuncType::One;
			pipParams.BlendSrcFunc = BlendFuncType::SrcAlpha;
			pipParams.BlendEquationRGB = BlendEquationType::ReverseSub;
			pipParams.BlendSrcFuncAlpha = BlendFuncType::Zero;
			pipParams.BlendDstFuncAlpha = BlendFuncType::One;
			pipParams.BlendEquationAlpha = BlendEquationType::Add;
			break;
		case Effekseer::AlphaBlendType::Mul:
			pipParams.BlendDstFunc = BlendFuncType::SrcColor;
			pipParams.BlendSrcFunc = BlendFuncType::Zero;
			pipParams.BlendEquationRGB = BlendEquationType::Add;
			pipParams.BlendSrcFuncAlpha = BlendFuncType::Zero;
			pipParams.BlendDstFuncAlpha = BlendFuncType::One;
			pipParams.BlendEquationAlpha = BlendEquationType::Add;
			break;
		}
	}
	pipParams.IsDepthTestEnabled = paramSet.ZTest;
	pipParams.IsDepthWriteEnabled = paramSet.ZWrite;
	pipParams.Culling = CullingType::DoubleSide;
	pipParams.ShaderPtr = m_shaders.rsParticleRender;
	pipParams.VertexLayoutPtr = m_vertexLayout;

	return m_rendererBase->GetGraphicsDevice()->CreatePipelineState(pipParams);
}

}
