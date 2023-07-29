#pragma once

#include <random>
#include "EffekseerRendererDX11.DeviceObject.h"
#include "EffekseerRenderer.GpuParticles.h"

namespace EffekseerRendererDX11
{

class GpuParticles
	: public DeviceObject
	, public EffekseerRenderer::GpuParticles
{
public:
	GpuParticles(RendererImplemented* renderer, bool hasRefCount);

	virtual ~GpuParticles();

public: // GpuParticles
	virtual bool InitSystem(const Settings& settings) override;

public: // For device restore
	virtual void OnLostDevice();
	virtual void OnResetDevice();
};

}
