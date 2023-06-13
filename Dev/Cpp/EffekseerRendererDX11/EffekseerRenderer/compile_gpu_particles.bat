@echo off

cd /d %~dp0

set COMPILER="%DXSDK_DIR%Utilities\\bin\x86\fxc"

%COMPILER% /Zpc /Tcs_5_0 /Emain /Fh ShaderHeader/gpupt_emitter_clear_cs.h Shader/gpupt_emitter_clear_cs.fx
%COMPILER% /Zpc /Tcs_5_0 /Emain /Fh ShaderHeader/gpupt_emitter_update_cs.h Shader/gpupt_emitter_update_cs.fx
%COMPILER% /Zpc /Tcs_5_0 /Emain /Fh ShaderHeader/gpupt_particle_clear_cs.h Shader/gpupt_particle_clear_cs.fx
%COMPILER% /Zpc /Tcs_5_0 /Emain /Fh ShaderHeader/gpupt_particle_update_cs.h Shader/gpupt_particle_update_cs.fx
%COMPILER% /Zpc /Tvs_5_0 /Emain /Fh ShaderHeader/gpupt_particle_render_vs.h Shader/gpupt_particle_render_vs.fx
%COMPILER% /Zpc /Tps_5_0 /Emain /Fh ShaderHeader/gpupt_particle_render_ps.h Shader/gpupt_particle_render_ps.fx

pause
