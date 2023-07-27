#define NOMINMAX
#include "EffekseerRendererDX11.GpuParticles.h"
#include "EffekseerRendererDX11.Shader.h"
#include "EffekseerRendererDX11.RenderState.h"
#include "../Effekseer/Effekseer/Noise/CurlNoise.h"

namespace EffekseerRendererDX11
{

namespace
{
#define ShaderData(shaderName) shaderName::g_main
#define ShaderSize(shaderName) sizeof(shaderName::g_main)

namespace CS_ParticleClear
{
#include "ShaderHeader/gpu_particles_clear_cs.h"
}

namespace CS_ParticleSpawn
{
#include "ShaderHeader/gpu_particles_spawn_cs.h"
}

namespace CS_ParticleUpdate
{
#include "ShaderHeader/gpu_particles_update_cs.h"
}

namespace VS_ParticleRender
{
#include "ShaderHeader/gpu_particles_render_vs.h"
}

namespace PS_ParticleRender
{
#include "ShaderHeader/gpu_particles_render_ps.h"
}

}

GpuParticles::GpuParticles(RendererImplemented* renderer, bool hasRefCount)
	: DeviceObject(renderer, hasRefCount)
	, EffekseerRenderer::GpuParticles(renderer)
{
}

GpuParticles::~GpuParticles()
{
}

void GpuParticles::OnLostDevice()
{
}

void GpuParticles::OnResetDevice()
{
}

void GpuParticles::InitShaders()
{
	auto graphics = GetRenderer()->GetGraphicsDevice();

	m_csParticleClear = graphics->CreateComputeShader(ShaderData(CS_ParticleClear), ShaderSize(CS_ParticleClear));
	m_csParticleSpawn = graphics->CreateComputeShader(ShaderData(CS_ParticleSpawn), ShaderSize(CS_ParticleSpawn));
	m_csParticleUpdate = graphics->CreateComputeShader(ShaderData(CS_ParticleUpdate), ShaderSize(CS_ParticleUpdate));

	m_renderShader = graphics->CreateShaderFromBinary(
		ShaderData(VS_ParticleRender), ShaderSize(VS_ParticleRender),
		ShaderData(PS_ParticleRender), ShaderSize(PS_ParticleRender));
}

}
