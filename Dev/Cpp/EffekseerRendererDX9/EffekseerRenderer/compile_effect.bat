"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_VS.h Shader/standard_renderer_VS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_PS.h Shader/standard_renderer_PS.fx

"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_Distortion_VS.h Shader/standard_renderer_distortion_VS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_Distortion_PS.h Shader/standard_renderer_distortion_PS.fx

"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_Lighting_VS.h Shader/standard_renderer_lighting_VS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.Standard_Lighting_PS.h Shader/standard_renderer_lighting_PS.fx

"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderTexture_VS.h Shader/model_renderer_texture_VS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderLightingTextureNormal_VS.h Shader/model_renderer_lighting_texture_normal_VS.fx

"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderTexture_PS.h Shader/model_renderer_texture_PS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderLightingTextureNormal_PS.h Shader/model_renderer_lighting_texture_normal_PS.fx

"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tvs_3_0 /EVS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderDistortion_VS.h Shader/model_renderer_distortion_VS.fx
"%DXSDK_DIR%Utilities\\bin\x86\fxc" /Zpc /Tps_3_0 /EPS /D __EFFEKSEER_BUILD_VERSION16__=1 /Fh Shader/EffekseerRenderer.ModelRenderer.ShaderDistortionTexture_PS.h Shader/model_renderer_distortion_texture_PS.fx


pause