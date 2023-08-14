#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0 /Emain /D __INST__=40 /Fh
//    ShaderHeader/model_distortion_ps.h Shader/model_distortion_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer PS_ConstantBuffer
// {
//
//   float4 g_scale;                    // Offset:    0 Size:    16
//   float4 mUVInversedBack;            // Offset:   16 Size:    16
//   float4 fFlipbookParameter;         // Offset:   32 Size:    16 [unused]
//   float4 fUVDistortionParameter;     // Offset:   48 Size:    16 [unused]
//   float4 fBlendTextureParameter;     // Offset:   64 Size:    16 [unused]
//   float4 softParticleParam;          // Offset:   80 Size:    16
//   float4 reconstructionParam1;       // Offset:   96 Size:    16
//   float4 reconstructionParam2;       // Offset:  112 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// sampler_colorTex                  sampler      NA          NA    0        1
// sampler_backTex                   sampler      NA          NA    1        1
// sampler_depthTex                  sampler      NA          NA    2        1
// _colorTex                         texture  float4          2d    0        1
// _backTex                          texture  float4          2d    1        1
// _depthTex                         texture  float4          2d    2        1
// PS_ConstantBuffer                 cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// TEXCOORD                 0   xy          1     NONE  float   xy  
// TEXCOORD                 1   xyzw        2     NONE  float   xy w
// TEXCOORD                 2   xyzw        3     NONE  float   xy w
// TEXCOORD                 3   xyzw        4     NONE  float   xyzw
// COLOR                    0   xyzw        5     NONE  float   xy w
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
ps_4_0
dcl_constantbuffer cb1[8], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_sampler s2, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear centroid v1.xy
dcl_input_ps linear v2.xyw
dcl_input_ps linear v3.xyw
dcl_input_ps linear v4.xyzw
dcl_input_ps linear centroid v5.xyw
dcl_output o0.xyzw
dcl_temps 4
sample r0.xyzw, v1.xyxx, t0.xyzw, s0
mul r1.x, r0.w, v5.w
ne r0.z, cb1[5].w, l(0.000000)
if_nz r0.z
  div r2.yzw, v4.xxyz, v4.wwww
  add r0.zw, r2.yyyz, l(0.000000, 0.000000, 1.000000, 1.000000)
  mul r3.x, r0.z, l(0.500000)
  mad r3.z, -r0.w, l(0.500000), l(1.000000)
  sample r3.xyzw, r3.xzxx, t2.xyzw, s2
  mad r2.x, r3.x, cb1[6].x, cb1[6].y
  mad r0.zw, r2.xxxw, cb1[7].wwww, -cb1[7].yyyy
  mad r2.xy, -r2.xwxx, cb1[7].zzzz, cb1[7].xxxx
  div r0.zw, r0.zzzw, r2.xxxy
  lt r2.x, l(0.000000), r0.z
  lt r2.y, r0.z, l(0.000000)
  iadd r2.x, r2.y, -r2.x
  itof r2.x, r2.x
  mul r2.y, r0.w, r2.x
  mad r0.z, r0.z, r2.x, -r2.y
  mad r0.w, r0.w, r2.x, -cb1[5].z
  div r0.zw, r0.zzzw, cb1[5].xxxy
  min_sat r0.z, r0.w, r0.z
  mul r1.x, r0.z, r1.x
endif 
eq r0.z, r1.x, l(0.000000)
discard r0.z
div r0.zw, v4.xxxy, v4.wwww
div r2.xy, v3.xyxx, v3.wwww
div r2.zw, v2.xxxy, v2.wwww
mad r0.xy, r0.xyxx, l(2.000000, 2.000000, 0.000000, 0.000000), l(-1.000000, -1.000000, 0.000000, 0.000000)
mul r0.xy, r0.xyxx, v5.xyxx
mul r0.xy, r0.xyxx, cb1[0].xxxx
add r2.xy, -r0.zwzz, r2.xyxx
mad r2.xy, r2.xyxx, r0.xxxx, r0.zwzz
add r0.xz, -r0.zzwz, r2.zzwz
mad r0.xy, r0.xzxx, r0.yyyy, r2.xyxx
add r0.xy, r0.xyxx, l(1.000000, 1.000000, 0.000000, 0.000000)
mul r0.x, r0.x, l(0.500000)
mad r0.y, -r0.y, l(0.500000), l(1.000000)
mad r0.z, cb1[1].y, r0.y, cb1[1].x
sample r0.xyzw, r0.xzxx, t1.xyzw, s1
mov r1.yzw, r0.xxyz
mov o0.xyzw, r1.yzwx
ret 
// Approximately 44 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67, 245,  24, 
    249, 217, 189,  20, 134, 227, 
      4,  24, 100, 101, 179,  25, 
    115, 138,   1,   0,   0,   0, 
    216,  10,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     76,   3,   0,   0,   8,   4, 
      0,   0,  60,   4,   0,   0, 
     92,  10,   0,   0,  82,  68, 
     69,  70,  16,   3,   0,   0, 
      1,   0,   0,   0,  96,   1, 
      0,   0,   7,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    221,   2,   0,   0, 252,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   1,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  29,   1,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  46,   1, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     56,   1,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   1,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  65,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  75,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    115,  97, 109, 112, 108, 101, 
    114,  95,  99, 111, 108, 111, 
    114,  84, 101, 120,   0, 115, 
     97, 109, 112, 108, 101, 114, 
     95,  98,  97,  99, 107,  84, 
    101, 120,   0, 115,  97, 109, 
    112, 108, 101, 114,  95, 100, 
    101, 112, 116, 104,  84, 101, 
    120,   0,  95,  99, 111, 108, 
    111, 114,  84, 101, 120,   0, 
     95,  98,  97,  99, 107,  84, 
    101, 120,   0,  95, 100, 101, 
    112, 116, 104,  84, 101, 120, 
      0,  80,  83,  95,  67, 111, 
    110, 115, 116,  97, 110, 116, 
     66, 117, 102, 102, 101, 114, 
      0, 171, 171, 171,  75,   1, 
      0,   0,   8,   0,   0,   0, 
    120,   1,   0,   0, 128,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  56,   2, 
      0,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0,  80,   2, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0,  96,   2, 
      0,   0,  32,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 115,   2, 
      0,   0,  48,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 138,   2, 
      0,   0,  64,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 161,   2, 
      0,   0,  80,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 179,   2, 
      0,   0,  96,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 200,   2, 
      0,   0, 112,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  64,   2,   0,   0, 
      0,   0,   0,   0, 103,  95, 
    115,  99,  97, 108, 101,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 109,  85, 
     86,  73, 110, 118, 101, 114, 
    115, 101, 100,  66,  97,  99, 
    107,   0, 102,  70, 108, 105, 
    112,  98, 111, 111, 107,  80, 
     97, 114,  97, 109, 101, 116, 
    101, 114,   0, 102,  85,  86, 
     68, 105, 115, 116, 111, 114, 
    116, 105, 111, 110,  80,  97, 
    114,  97, 109, 101, 116, 101, 
    114,   0, 102,  66, 108, 101, 
    110, 100,  84, 101, 120, 116, 
    117, 114, 101,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
      0, 115, 111, 102, 116,  80, 
     97, 114, 116, 105,  99, 108, 
    101,  80,  97, 114,  97, 109, 
      0, 114, 101,  99, 111, 110, 
    115, 116, 114, 117,  99, 116, 
    105, 111, 110,  80,  97, 114, 
     97, 109,  49,   0, 114, 101, 
     99, 111, 110, 115, 116, 114, 
    117,  99, 116, 105, 111, 110, 
     80,  97, 114,  97, 109,  50, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     57,  46,  50,  57,  46,  57, 
     53,  50,  46,  51,  49,  49, 
     49,   0, 171, 171,  73,  83, 
     71,  78, 180,   0,   0,   0, 
      6,   0,   0,   0,   8,   0, 
      0,   0, 152,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 164,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   3,   3, 
      0,   0, 164,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  15,  11, 
      0,   0, 164,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,  15,  11, 
      0,   0, 164,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,  15, 
      0,   0, 173,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,  15,  11, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  67, 
     79,  76,  79,  82,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     68,  82,  24,   6,   0,   0, 
     64,   0,   0,   0, 134,   1, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   1,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      1,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   2,   0, 
      0,   0,  85,  85,   0,   0, 
     98,  24,   0,   3,  50,  16, 
     16,   0,   1,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   2,   0,   0,   0, 
     98,  16,   0,   3, 178,  16, 
     16,   0,   3,   0,   0,   0, 
     98,  16,   0,   3, 242,  16, 
     16,   0,   4,   0,   0,   0, 
     98,  24,   0,   3, 178,  16, 
     16,   0,   5,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   4,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  58,  16, 
     16,   0,   5,   0,   0,   0, 
     57,   0,   0,   8,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     58, 128,  32,   0,   1,   0, 
      0,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  31,   0,   4,   3, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  14,   0,   0,   7, 
    226,   0,  16,   0,   2,   0, 
      0,   0,   6,  25,  16,   0, 
      4,   0,   0,   0, 246,  31, 
     16,   0,   4,   0,   0,   0, 
      0,   0,   0,  10, 194,   0, 
     16,   0,   0,   0,   0,   0, 
     86,   9,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,  56,   0, 
      0,   7,  18,   0,  16,   0, 
      3,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,  50,   0,   0,  10, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   3,   0,   0,   0, 
    134,   0,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      2,   0,   0,   0,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  11,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   3,   0, 
      0,   0,  10, 128,  32,   0, 
      1,   0,   0,   0,   6,   0, 
      0,   0,  26, 128,  32,   0, 
      1,   0,   0,   0,   6,   0, 
      0,   0,  50,   0,   0,  12, 
    194,   0,  16,   0,   0,   0, 
      0,   0,   6,  12,  16,   0, 
      2,   0,   0,   0, 246, 143, 
     32,   0,   1,   0,   0,   0, 
      7,   0,   0,   0,  86, 133, 
     32, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,   7,   0, 
      0,   0,  50,   0,   0,  12, 
     50,   0,  16,   0,   2,   0, 
      0,   0, 198,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0, 166, 138,  32,   0, 
      1,   0,   0,   0,   7,   0, 
      0,   0,   6, 128,  32,   0, 
      1,   0,   0,   0,   7,   0, 
      0,   0,  14,   0,   0,   7, 
    194,   0,  16,   0,   0,   0, 
      0,   0, 166,  14,  16,   0, 
      0,   0,   0,   0,   6,   4, 
     16,   0,   2,   0,   0,   0, 
     49,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  49,   0, 
      0,   7,  34,   0,  16,   0, 
      2,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  30,   0,   0,   8, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16, 128,  65,   0,   0,   0, 
      2,   0,   0,   0,  43,   0, 
      0,   5,  18,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7,  34,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10,  66,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,  50,   0,   0,  11, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     42, 128,  32, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
      5,   0,   0,   0,  14,   0, 
      0,   8, 194,   0,  16,   0, 
      0,   0,   0,   0, 166,  14, 
     16,   0,   0,   0,   0,   0, 
      6, 132,  32,   0,   1,   0, 
      0,   0,   5,   0,   0,   0, 
     51,  32,   0,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  21,   0,   0,   1, 
     24,   0,   0,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  42,   0,  16,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   7, 194,   0,  16,   0, 
      0,   0,   0,   0,   6,  20, 
     16,   0,   4,   0,   0,   0, 
    246,  31,  16,   0,   4,   0, 
      0,   0,  14,   0,   0,   7, 
     50,   0,  16,   0,   2,   0, 
      0,   0,  70,  16,  16,   0, 
      3,   0,   0,   0, 246,  31, 
     16,   0,   3,   0,   0,   0, 
     14,   0,   0,   7, 194,   0, 
     16,   0,   2,   0,   0,   0, 
      6,  20,  16,   0,   2,   0, 
      0,   0, 246,  31,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  15,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,  64,   0,   0,   0,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 128, 191,   0,   0, 
    128, 191,   0,   0,   0,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  16,  16,   0,   5,   0, 
      0,   0,  56,   0,   0,   8, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,   6, 128, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      2,   0,   0,   0, 230,  10, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9,  50,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   0,  16,   0,   2,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0, 230,  10, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   8,  82,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  11,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
    166,  11,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,   9, 
     50,   0,  16,   0,   0,   0, 
      0,   0, 134,   0,  16,   0, 
      0,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,  10, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  50,   0, 
      0,  10,  34,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,  11, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0, 134,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,   0,  96,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 226,   0,  16,   0, 
      1,   0,   0,   0,   6,   9, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    150,   3,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  44,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     22,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
