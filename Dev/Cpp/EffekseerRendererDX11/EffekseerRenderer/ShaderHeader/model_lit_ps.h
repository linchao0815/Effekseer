#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0 /Emain /D __INST__=40 /Fh ShaderHeader/model_lit_ps.h
//    Shader/model_lit_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer PS_ConstantBuffer
// {
//
//   float4 fLightDirection;            // Offset:    0 Size:    16
//   float4 fLightColor;                // Offset:   16 Size:    16
//   float4 fLightAmbient;              // Offset:   32 Size:    16
//   float4 fFlipbookParameter;         // Offset:   48 Size:    16 [unused]
//   float4 fUVDistortionParameter;     // Offset:   64 Size:    16 [unused]
//   float4 fBlendTextureParameter;     // Offset:   80 Size:    16 [unused]
//   float4 fCameraFrontDirection;      // Offset:   96 Size:    16 [unused]
//   float4 fFalloffParameter;          // Offset:  112 Size:    16 [unused]
//   float4 fFalloffBeginColor;         // Offset:  128 Size:    16 [unused]
//   float4 fFalloffEndColor;           // Offset:  144 Size:    16 [unused]
//   float4 fEmissiveScaling;           // Offset:  160 Size:    16
//   float4 fEdgeColor;                 // Offset:  176 Size:    16 [unused]
//   float4 fEdgeParameter;             // Offset:  192 Size:    16 [unused]
//   float4 softParticleParam;          // Offset:  208 Size:    16
//   float4 reconstructionParam1;       // Offset:  224 Size:    16
//   float4 reconstructionParam2;       // Offset:  240 Size:    16
//   float4 mUVInversedBack;            // Offset:  256 Size:    16
//   float4 miscFlags;                  // Offset:  272 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// sampler_colorTex                  sampler      NA          NA    0        1
// sampler_normalTex                 sampler      NA          NA    1        1
// sampler_depthTex                  sampler      NA          NA    2        1
// _colorTex                         texture  float4          2d    0        1
// _normalTex                        texture  float4          2d    1        1
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
// COLOR                    0   xyzw        1     NONE  float   xyzw
// TEXCOORD                 0   xy          2     NONE  float   xy  
// TEXCOORD                 1   xyz         3     NONE  float   xyz 
// TEXCOORD                 2   xyz         4     NONE  float   xyz 
// TEXCOORD                 3   xyz         5     NONE  float   xyz 
// TEXCOORD                 4   xyzw        6     NONE  float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
ps_4_0
dcl_constantbuffer cb1[18], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_sampler s2, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear centroid v1.xyzw
dcl_input_ps linear centroid v2.xy
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xyz
dcl_input_ps linear v5.xyz
dcl_input_ps linear v6.xyzw
dcl_output o0.xyzw
dcl_temps 4
ne r0.x, cb1[17].x, l(0.000000)
sample r1.xyzw, v2.xyxx, t0.xyzw, s0
max r0.yzw, |r1.xxyz|, l(0.000000, 0.000000, 0.000000, 0.000000)
log r0.yzw, r0.yyzw
mul r0.yzw, r0.yyzw, l(0.000000, 0.416667, 0.416667, 0.416667)
exp r0.yzw, r0.yyzw
mad r0.yzw, r0.yyzw, l(0.000000, 1.055000, 1.055000, 1.055000), l(0.000000, -0.055000, -0.055000, -0.055000)
max r0.yzw, r0.yyzw, l(0.000000, 0.000000, 0.000000, 0.000000)
movc r1.xyz, r0.xxxx, r0.yzwy, r1.xyzx
mul r1.xyzw, r1.xyzw, v1.xyzw
ne r0.y, cb1[13].w, l(0.000000)
if_nz r0.y
  div r2.yzw, v6.xxyz, v6.wwww
  add r0.yz, r2.yyzy, l(0.000000, 1.000000, 1.000000, 0.000000)
  mul r3.x, r0.y, l(0.500000)
  mad r0.y, -r0.z, l(0.500000), l(1.000000)
  mad r3.z, cb1[16].y, r0.y, cb1[16].x
  sample r3.xyzw, r3.xzxx, t2.xyzw, s2
  mad r2.x, r3.x, cb1[14].x, cb1[14].y
  mad r0.yz, r2.xxwx, cb1[15].wwww, -cb1[15].yyyy
  mad r2.xy, -r2.xwxx, cb1[15].zzzz, cb1[15].xxxx
  div r0.yz, r0.yyzy, r2.xxyx
  lt r0.w, l(0.000000), r0.y
  lt r2.x, r0.y, l(0.000000)
  iadd r0.w, r2.x, -r0.w
  itof r0.w, r0.w
  mul r2.x, r0.w, r0.z
  mad r0.y, r0.y, r0.w, -r2.x
  mad r0.z, r0.z, r0.w, -cb1[13].z
  div r0.yz, r0.yyzy, cb1[13].xxyx
  min_sat r0.y, r0.z, r0.y
  mul r1.w, r0.y, r1.w
endif 
eq r0.y, r1.w, l(0.000000)
discard r0.y
sample r2.xyzw, v2.xyxx, t1.xyzw, s1
add r0.yzw, r2.xxyz, l(0.000000, -0.500000, -0.500000, -0.500000)
add r0.yzw, r0.yyzw, r0.yyzw
mul r2.xyz, r0.zzzz, v4.xyzx
mad r2.xyz, r0.yyyy, v5.xyzx, r2.xyzx
mad r0.yzw, r0.wwww, v3.xxyz, r2.xxyz
dp3 r2.x, r0.yzwy, r0.yzwy
rsq r2.x, r2.x
mul r0.yzw, r0.yyzw, r2.xxxx
dp3 r0.y, cb1[0].xyzx, r0.yzwy
max r0.y, r0.y, l(0.000000)
mad r0.yzw, cb1[1].xxyz, r0.yyyy, cb1[2].xxyz
mul r0.yzw, r0.yyzw, r1.xxyz
mul r0.yzw, r0.yyzw, cb1[10].xxxx
mad r2.xyz, r0.yzwy, l(0.305306, 0.305306, 0.305306, 0.000000), l(0.682171, 0.682171, 0.682171, 0.000000)
mad r2.xyz, r0.yzwy, r2.xyzx, l(0.012523, 0.012523, 0.012523, 0.000000)
mul r2.xyz, r0.yzwy, r2.xyzx
min r2.xyz, r0.yzwy, r2.xyzx
movc r1.xyz, r0.xxxx, r2.xyzx, r0.yzwy
mov o0.xyzw, r1.xyzw
ret 
// Approximately 56 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67,  83, 242, 
     87, 207, 141, 138, 196, 114, 
    252, 116, 166,  17, 182,  85, 
     51, 216,   1,   0,   0,   0, 
     68,  14,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    228,   4,   0,   0, 184,   5, 
      0,   0, 236,   5,   0,   0, 
    200,  13,   0,   0,  82,  68, 
     69,  70, 168,   4,   0,   0, 
      1,   0,   0,   0, 100,   1, 
      0,   0,   7,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    116,   4,   0,   0, 252,   0, 
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
      0,   0,  31,   1,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  48,   1, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     58,   1,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   1,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  69,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   2,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  79,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    115,  97, 109, 112, 108, 101, 
    114,  95,  99, 111, 108, 111, 
    114,  84, 101, 120,   0, 115, 
     97, 109, 112, 108, 101, 114, 
     95, 110, 111, 114, 109,  97, 
    108,  84, 101, 120,   0, 115, 
     97, 109, 112, 108, 101, 114, 
     95, 100, 101, 112, 116, 104, 
     84, 101, 120,   0,  95,  99, 
    111, 108, 111, 114,  84, 101, 
    120,   0,  95, 110, 111, 114, 
    109,  97, 108,  84, 101, 120, 
      0,  95, 100, 101, 112, 116, 
    104,  84, 101, 120,   0,  80, 
     83,  95,  67, 111, 110, 115, 
    116,  97, 110, 116,  66, 117, 
    102, 102, 101, 114,   0, 171, 
    171, 171,  79,   1,   0,   0, 
     18,   0,   0,   0, 124,   1, 
      0,   0,  32,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  44,   3,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  76,   3,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  88,   3,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 102,   3,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 121,   3,   0,   0, 
     64,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 144,   3,   0,   0, 
     80,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 167,   3,   0,   0, 
     96,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 189,   3,   0,   0, 
    112,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 207,   3,   0,   0, 
    128,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 226,   3,   0,   0, 
    144,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 243,   3,   0,   0, 
    160,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,   4,   4,   0,   0, 
    176,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  15,   4,   0,   0, 
    192,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  30,   4,   0,   0, 
    208,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  48,   4,   0,   0, 
    224,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  69,   4,   0,   0, 
    240,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0,  90,   4,   0,   0, 
      0,   1,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 106,   4,   0,   0, 
     16,   1,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     60,   3,   0,   0,   0,   0, 
      0,   0, 102,  76, 105, 103, 
    104, 116,  68, 105, 114, 101, 
     99, 116, 105, 111, 110,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 102,  76, 
    105, 103, 104, 116,  67, 111, 
    108, 111, 114,   0, 102,  76, 
    105, 103, 104, 116,  65, 109, 
     98, 105, 101, 110, 116,   0, 
    102,  70, 108, 105, 112,  98, 
    111, 111, 107,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
      0, 102,  85,  86,  68, 105, 
    115, 116, 111, 114, 116, 105, 
    111, 110,  80,  97, 114,  97, 
    109, 101, 116, 101, 114,   0, 
    102,  66, 108, 101, 110, 100, 
     84, 101, 120, 116, 117, 114, 
    101,  80,  97, 114,  97, 109, 
    101, 116, 101, 114,   0, 102, 
     67,  97, 109, 101, 114,  97, 
     70, 114, 111, 110, 116,  68, 
    105, 114, 101,  99, 116, 105, 
    111, 110,   0, 102,  70,  97, 
    108, 108, 111, 102, 102,  80, 
     97, 114,  97, 109, 101, 116, 
    101, 114,   0, 102,  70,  97, 
    108, 108, 111, 102, 102,  66, 
    101, 103, 105, 110,  67, 111, 
    108, 111, 114,   0, 102,  70, 
     97, 108, 108, 111, 102, 102, 
     69, 110, 100,  67, 111, 108, 
    111, 114,   0, 102,  69, 109, 
    105, 115, 115, 105, 118, 101, 
     83,  99,  97, 108, 105, 110, 
    103,   0, 102,  69, 100, 103, 
    101,  67, 111, 108, 111, 114, 
      0, 102,  69, 100, 103, 101, 
     80,  97, 114,  97, 109, 101, 
    116, 101, 114,   0, 115, 111, 
    102, 116,  80,  97, 114, 116, 
    105,  99, 108, 101,  80,  97, 
    114,  97, 109,   0, 114, 101, 
     99, 111, 110, 115, 116, 114, 
    117,  99, 116, 105, 111, 110, 
     80,  97, 114,  97, 109,  49, 
      0, 114, 101,  99, 111, 110, 
    115, 116, 114, 117,  99, 116, 
    105, 111, 110,  80,  97, 114, 
     97, 109,  50,   0, 109,  85, 
     86,  73, 110, 118, 101, 114, 
    115, 101, 100,  66,  97,  99, 
    107,   0, 109, 105, 115,  99, 
     70, 108,  97, 103, 115,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171, 171, 171,  73,  83, 
     71,  78, 204,   0,   0,   0, 
      7,   0,   0,   0,   8,   0, 
      0,   0, 176,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 188,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,  15, 
      0,   0, 194,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   3,   3, 
      0,   0, 194,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   7, 
      0,   0, 194,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   7,   7, 
      0,   0, 194,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,   7,   7, 
      0,   0, 194,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      6,   0,   0,   0,  15,  15, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  67,  79,  76,  79, 
     82,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     68,  82, 212,   7,   0,   0, 
     64,   0,   0,   0, 245,   1, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,  18,   0,   0,   0, 
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
     98,  24,   0,   3, 242,  16, 
     16,   0,   1,   0,   0,   0, 
     98,  24,   0,   3,  50,  16, 
     16,   0,   2,   0,   0,   0, 
     98,  16,   0,   3, 114,  16, 
     16,   0,   3,   0,   0,   0, 
     98,  16,   0,   3, 114,  16, 
     16,   0,   4,   0,   0,   0, 
     98,  16,   0,   3, 114,  16, 
     16,   0,   5,   0,   0,   0, 
     98,  16,   0,   3, 242,  16, 
     16,   0,   6,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   4,   0, 
      0,   0,  57,   0,   0,   8, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   0, 
      1,   0,   0,   0,  17,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  52,   0, 
      0,  11, 226,   0,  16,   0, 
      0,   0,   0,   0,   6,   9, 
     16, 128, 129,   0,   0,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,  52,   0,   0, 
      0,  52,   0,   0,   0,  52, 
     47,   0,   0,   5, 226,   0, 
     16,   0,   0,   0,   0,   0, 
     86,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,  10, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
     85,  85, 213,  62,  85,  85, 
    213,  62,  85,  85, 213,  62, 
     25,   0,   0,   5, 226,   0, 
     16,   0,   0,   0,   0,   0, 
     86,  14,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  15, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
     61,  10, 135,  63,  61,  10, 
    135,  63,  61,  10, 135,  63, 
      2,  64,   0,   0,   0,   0, 
      0,   0, 174,  71,  97, 189, 
    174,  71,  97, 189, 174,  71, 
     97, 189,  52,   0,   0,  10, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70,  30,  16,   0, 
      1,   0,   0,   0,  57,   0, 
      0,   8,  34,   0,  16,   0, 
      0,   0,   0,   0,  58, 128, 
     32,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   4,   3,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     14,   0,   0,   7, 226,   0, 
     16,   0,   2,   0,   0,   0, 
      6,  25,  16,   0,   6,   0, 
      0,   0, 246,  31,  16,   0, 
      6,   0,   0,   0,   0,   0, 
      0,  10,  98,   0,  16,   0, 
      0,   0,   0,   0,  86,   6, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     18,   0,  16,   0,   3,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     50,   0,   0,  10,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,  11,  66,   0,  16,   0, 
      3,   0,   0,   0,  26, 128, 
     32,   0,   1,   0,   0,   0, 
     16,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   1,   0, 
      0,   0,  16,   0,   0,   0, 
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
      1,   0,   0,   0,  14,   0, 
      0,   0,  26, 128,  32,   0, 
      1,   0,   0,   0,  14,   0, 
      0,   0,  50,   0,   0,  12, 
     98,   0,  16,   0,   0,   0, 
      0,   0,   6,   3,  16,   0, 
      2,   0,   0,   0, 246, 143, 
     32,   0,   1,   0,   0,   0, 
     15,   0,   0,   0,  86, 133, 
     32, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0,  50,   0,   0,  12, 
     50,   0,  16,   0,   2,   0, 
      0,   0, 198,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0, 166, 138,  32,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0,   6, 128,  32,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0,  14,   0,   0,   7, 
     98,   0,  16,   0,   0,   0, 
      0,   0,  86,   6,  16,   0, 
      0,   0,   0,   0,   6,   1, 
     16,   0,   2,   0,   0,   0, 
     49,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  49,   0, 
      0,   7,  18,   0,  16,   0, 
      2,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  30,   0,   0,   8, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  43,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10,  34,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,  50,   0,   0,  11, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     42, 128,  32, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  14,   0, 
      0,   8,  98,   0,  16,   0, 
      0,   0,   0,   0,  86,   6, 
     16,   0,   0,   0,   0,   0, 
      6, 129,  32,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     51,  32,   0,   7,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  21,   0,   0,   1, 
     24,   0,   0,   7,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  26,   0,  16,   0, 
      0,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,   0,  96,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,  10, 226,   0,  16,   0, 
      0,   0,   0,   0,   6,   9, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0, 191, 
      0,   0,   0, 191,   0,   0, 
      0, 191,   0,   0,   0,   7, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,  86,  14, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      4,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      2,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,   9, 226,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
      6,  25,  16,   0,   3,   0, 
      0,   0,   6,   9,  16,   0, 
      2,   0,   0,   0,  16,   0, 
      0,   7,  18,   0,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
    150,   7,  16,   0,   0,   0, 
      0,   0,  68,   0,   0,   5, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      0,   0,   0,   0,  86,  14, 
     16,   0,   0,   0,   0,   0, 
      6,   0,  16,   0,   2,   0, 
      0,   0,  16,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      0,   0,   0,   0,  52,   0, 
      0,   7,  34,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  50,   0,   0,  11, 
    226,   0,  16,   0,   0,   0, 
      0,   0,   6, 137,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,   6, 137, 
     32,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      0,   0,   0,   0,  86,  14, 
     16,   0,   0,   0,   0,   0, 
      6,   9,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   8, 
    226,   0,  16,   0,   0,   0, 
      0,   0,  86,  14,  16,   0, 
      0,   0,   0,   0,   6, 128, 
     32,   0,   1,   0,   0,   0, 
     10,   0,   0,   0,  50,   0, 
      0,  15, 114,   0,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,  18,  81, 
    156,  62,  18,  81, 156,  62, 
     18,  81, 156,  62,   0,   0, 
      0,   0,   2,  64,   0,   0, 
    196, 162,  46,  63, 196, 162, 
     46,  63, 196, 162,  46,  63, 
      0,   0,   0,   0,  50,   0, 
      0,  12, 114,   0,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
    194,  44,  77,  60, 194,  44, 
     77,  60, 194,  44,  77,  60, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  51,   0,   0,   7, 
    114,   0,  16,   0,   2,   0, 
      0,   0, 150,   7,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     55,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  56,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
     31,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
