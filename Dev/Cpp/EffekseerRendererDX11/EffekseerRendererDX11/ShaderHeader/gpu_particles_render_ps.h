#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_5_0 /Emain /Fh ShaderHeader/gpu_particles_render_ps.h
//    Shader/gpu_particles_render_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer cb0
// {
//
//   struct DrawConstants
//   {
//       
//       float4x4 ProjMat;              // Offset:    0
//       float4x4 CameraMat;            // Offset:   64
//       float4x3 BillboardMat;         // Offset:  128
//       float4x3 YAxisFixedMat;        // Offset:  176
//       float3 CameraPos;              // Offset:  224
//       float Reserved0;               // Offset:  236
//       float3 CameraFront;            // Offset:  240
//       float Reserved1;               // Offset:  252
//       float3 LightDir;               // Offset:  256
//       float Reserved2;               // Offset:  268
//       float4 LightColor;             // Offset:  272
//       float4 LightAmbient;           // Offset:  288
//
//   } constants;                       // Offset:    0 Size:   304
//
// }
//
// cbuffer cb1
// {
//
//   struct ParameterSet
//   {
//       
//       int EmitCount;                 // Offset:    0
//       int EmitPerFrame;              // Offset:    4
//       float EmitOffset;              // Offset:    8
//       uint Padding0;                 // Offset:   12
//       float2 LifeTime;               // Offset:   16
//       uint EmitShapeType;            // Offset:   24
//       uint Padding1;                 // Offset:   28
//       float4 EmitShapeData[2];       // Offset:   32
//       float3 Direction;              // Offset:   64
//       float Spread;                  // Offset:   76
//       float2 InitialSpeed;           // Offset:   80
//       float2 Damping;                // Offset:   88
//       float4 InitialAngle[2];        // Offset:   96
//       float4 TargetAngle[2];         // Offset:  128
//       float4 InitialScale[2];        // Offset:  160
//       float4 TargetScale[2];         // Offset:  192
//       float3 Gravity;                // Offset:  224
//       uint Padding2;                 // Offset:  236
//       float3 VortexCenter;           // Offset:  240
//       float VortexRotation;          // Offset:  252
//       float3 VortexAxis;             // Offset:  256
//       float VortexAttraction;        // Offset:  268
//       float TurbulencePower;         // Offset:  272
//       uint TurbulenceSeed;           // Offset:  276
//       float TurbulenceScale;         // Offset:  280
//       float TurbulenceOctave;        // Offset:  284
//       uint RenderState;              // Offset:  288
//       uint ShapeType;                // Offset:  292
//       uint ShapeData;                // Offset:  296
//       float ShapeSize;               // Offset:  300
//       float Emissive;                // Offset:  304
//       float FadeIn;                  // Offset:  308
//       float FadeOut;                 // Offset:  312
//       uint Padding4;                 // Offset:  316
//       uint4 ColorData;               // Offset:  320
//       float3 ColorEasing;            // Offset:  336
//       uint ColorFlags;               // Offset:  348
//       uint MaterialType;             // Offset:  352
//       uint Padding5;                 // Offset:  356
//       uint Padding6;                 // Offset:  360
//       uint Padding7;                 // Offset:  364
//
//   } paramSet;                        // Offset:    0 Size:   368
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// ColorSamp                         sampler      NA          NA    2        1
// NormalSamp                        sampler      NA          NA    3        1
// ColorTex                          texture  float4          2d    2        1
// NormalTex                         texture  float4          2d    3        1
// cb0                               cbuffer      NA          NA    0        1
// cb1                               cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// TEXCOORD                 0   xy          1     NONE  float   xy  
// COLOR                    0   xyzw        2     NONE  float   xyzw
// TEXCOORD                 1   xyz         3     NONE  float   xyz 
// TEXCOORD                 2   xyz         4     NONE  float   xyz 
// TEXCOORD                 3   xyz         5     NONE  float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[19], immediateIndexed
dcl_constantbuffer cb1[23], immediateIndexed
dcl_sampler s2, mode_default
dcl_sampler s3, mode_default
dcl_resource_texture2d (float,float,float,float) t2
dcl_resource_texture2d (float,float,float,float) t3
dcl_input_ps linear v1.xy
dcl_input_ps linear v2.xyzw
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xyz
dcl_input_ps linear v5.xyz
dcl_output o0.xyzw
dcl_temps 3
sample_indexable(texture2d)(float,float,float,float) r0.xyzw, v1.xyxx, t2.xyzw, s2
mul r0.xyzw, r0.xyzw, v2.xyzw
ieq r1.x, cb1[22].x, l(1)
if_nz r1.x
  sample_indexable(texture2d)(float,float,float,float) r1.xyz, v1.xyxx, t3.xyzw, s3
  mad r1.xyz, r1.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), l(-1.000000, -1.000000, -1.000000, 0.000000)
  mul r2.xyz, r1.yyyy, v4.xyzx
  mad r1.xyw, r1.xxxx, v5.xyxz, r2.xyxz
  mad r1.xyz, r1.zzzz, v3.xyzx, r1.xywx
  dp3 r1.w, r1.xyzx, r1.xyzx
  rsq r1.w, r1.w
  mul r1.xyz, r1.wwww, r1.xyzx
  dp3 r1.x, cb0[16].xyzx, r1.xyzx
  max r1.x, r1.x, l(0.000000)
  mad r1.xyz, cb0[17].xyzx, r1.xxxx, cb0[18].xyzx
  mul r0.xyz, r0.xyzx, r1.xyzx
endif 
mov o0.xyzw, r0.xyzw
ret 
// Approximately 19 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67,  29, 240, 
     30, 198, 172, 113, 135,  13, 
    214,  74,  89, 213,  31, 127, 
    172,  90,   1,   0,   0,   0, 
     24,  14,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    164,   9,   0,   0,  96,  10, 
      0,   0, 148,  10,   0,   0, 
    124,  13,   0,   0,  82,  68, 
     69,  70, 104,   9,   0,   0, 
      2,   0,   0,   0,  44,   1, 
      0,   0,   6,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,  16,   1,   0,   0, 
     52,   9,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    252,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   6,   1,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  17,   1, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     26,   1,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   3,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  36,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  40,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     67, 111, 108, 111, 114,  83, 
     97, 109, 112,   0,  78, 111, 
    114, 109,  97, 108,  83,  97, 
    109, 112,   0,  67, 111, 108, 
    111, 114,  84, 101, 120,   0, 
     78, 111, 114, 109,  97, 108, 
     84, 101, 120,   0,  99,  98, 
     48,   0,  99,  98,  49,   0, 
     36,   1,   0,   0,   1,   0, 
      0,   0,  92,   1,   0,   0, 
     48,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     40,   1,   0,   0,   1,   0, 
      0,   0, 180,   3,   0,   0, 
    112,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    132,   1,   0,   0,   0,   0, 
      0,   0,  48,   1,   0,   0, 
      2,   0,   0,   0, 144,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  99, 111, 
    110, 115, 116,  97, 110, 116, 
    115,   0,  68, 114,  97, 119, 
     67, 111, 110, 115, 116,  97, 
    110, 116, 115,   0,  80, 114, 
    111, 106,  77,  97, 116,   0, 
    102, 108, 111,  97, 116,  52, 
    120,  52,   0, 171, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 164,   1,   0,   0, 
     67,  97, 109, 101, 114,  97, 
     77,  97, 116,   0,  66, 105, 
    108, 108,  98, 111,  97, 114, 
    100,  77,  97, 116,   0, 102, 
    108, 111,  97, 116,  52, 120, 
     51,   0,   3,   0,   3,   0, 
      4,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 235,   1, 
      0,   0,  89,  65, 120, 105, 
    115,  70, 105, 120, 101, 100, 
     77,  97, 116,   0,  67,  97, 
    109, 101, 114,  97,  80, 111, 
    115,   0, 102, 108, 111,  97, 
    116,  51,   0, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     48,   2,   0,   0,  82, 101, 
    115, 101, 114, 118, 101, 100, 
     48,   0, 102, 108, 111,  97, 
    116,   0,   0,   0,   3,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 102,   2, 
      0,   0,  67,  97, 109, 101, 
    114,  97,  70, 114, 111, 110, 
    116,   0,  82, 101, 115, 101, 
    114, 118, 101, 100,  49,   0, 
     76, 105, 103, 104, 116,  68, 
    105, 114,   0,  82, 101, 115, 
    101, 114, 118, 101, 100,  50, 
      0,  76, 105, 103, 104, 116, 
     67, 111, 108, 111, 114,   0, 
    102, 108, 111,  97, 116,  52, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 196,   2, 
      0,   0,  76, 105, 103, 104, 
    116,  65, 109,  98, 105, 101, 
    110, 116,   0, 171, 171, 171, 
    156,   1,   0,   0, 176,   1, 
      0,   0,   0,   0,   0,   0, 
    212,   1,   0,   0, 176,   1, 
      0,   0,  64,   0,   0,   0, 
    222,   1,   0,   0, 244,   1, 
      0,   0, 128,   0,   0,   0, 
     24,   2,   0,   0, 244,   1, 
      0,   0, 176,   0,   0,   0, 
     38,   2,   0,   0,  56,   2, 
      0,   0, 224,   0,   0,   0, 
     92,   2,   0,   0, 108,   2, 
      0,   0, 236,   0,   0,   0, 
    144,   2,   0,   0,  56,   2, 
      0,   0, 240,   0,   0,   0, 
    156,   2,   0,   0, 108,   2, 
      0,   0, 252,   0,   0,   0, 
    166,   2,   0,   0,  56,   2, 
      0,   0,   0,   1,   0,   0, 
    175,   2,   0,   0, 108,   2, 
      0,   0,  12,   1,   0,   0, 
    185,   2,   0,   0, 204,   2, 
      0,   0,  16,   1,   0,   0, 
    240,   2,   0,   0, 204,   2, 
      0,   0,  32,   1,   0,   0, 
      5,   0,   0,   0,   1,   0, 
     76,   0,   0,   0,  12,   0, 
      0,   3,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 142,   1,   0,   0, 
    220,   3,   0,   0,   0,   0, 
      0,   0, 112,   1,   0,   0, 
      2,   0,   0,   0,  16,   9, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 112,  97, 
    114,  97, 109,  83, 101, 116, 
      0,  80,  97, 114,  97, 109, 
    101, 116, 101, 114,  83, 101, 
    116,   0,  69, 109, 105, 116, 
     67, 111, 117, 110, 116,   0, 
    105, 110, 116,   0,   0,   0, 
      2,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    252,   3,   0,   0,  69, 109, 
    105, 116,  80, 101, 114,  70, 
    114,  97, 109, 101,   0,  69, 
    109, 105, 116,  79, 102, 102, 
    115, 101, 116,   0,  80,  97, 
    100, 100, 105, 110, 103,  48, 
      0, 100, 119, 111, 114, 100, 
      0, 171,   0,   0,  19,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  69,   4, 
      0,   0,  76, 105, 102, 101, 
     84, 105, 109, 101,   0, 102, 
    108, 111,  97, 116,  50,   0, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 121,   4,   0,   0, 
     69, 109, 105, 116,  83, 104, 
     97, 112, 101,  84, 121, 112, 
    101,   0,  80,  97, 100, 100, 
    105, 110, 103,  49,   0,  69, 
    109, 105, 116,  83, 104,  97, 
    112, 101,  68,  97, 116,  97, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    196,   2,   0,   0,  68, 105, 
    114, 101,  99, 116, 105, 111, 
    110,   0,  83, 112, 114, 101, 
     97, 100,   0,  73, 110, 105, 
    116, 105,  97, 108,  83, 112, 
    101, 101, 100,   0,  68,  97, 
    109, 112, 105, 110, 103,   0, 
     73, 110, 105, 116, 105,  97, 
    108,  65, 110, 103, 108, 101, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 196,   2, 
      0,   0,  84,  97, 114, 103, 
    101, 116,  65, 110, 103, 108, 
    101,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 196,   2, 
      0,   0,  73, 110, 105, 116, 
    105,  97, 108,  83,  99,  97, 
    108, 101,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 196,   2,   0,   0, 
     84,  97, 114, 103, 101, 116, 
     83,  99,  97, 108, 101,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 196,   2,   0,   0, 
     71, 114,  97, 118, 105, 116, 
    121,   0,  80,  97, 100, 100, 
    105, 110, 103,  50,   0,  86, 
    111, 114, 116, 101, 120,  67, 
    101, 110, 116, 101, 114,   0, 
     86, 111, 114, 116, 101, 120, 
     82, 111, 116,  97, 116, 105, 
    111, 110,   0,  86, 111, 114, 
    116, 101, 120,  65, 120, 105, 
    115,   0,  86, 111, 114, 116, 
    101, 120,  65, 116, 116, 114, 
     97,  99, 116, 105, 111, 110, 
      0,  84, 117, 114,  98, 117, 
    108, 101, 110,  99, 101,  80, 
    111, 119, 101, 114,   0,  84, 
    117, 114,  98, 117, 108, 101, 
    110,  99, 101,  83, 101, 101, 
    100,   0,  84, 117, 114,  98, 
    117, 108, 101, 110,  99, 101, 
     83,  99,  97, 108, 101,   0, 
     84, 117, 114,  98, 117, 108, 
    101, 110,  99, 101,  79,  99, 
    116,  97, 118, 101,   0,  82, 
    101, 110, 100, 101, 114,  83, 
    116,  97, 116, 101,   0,  83, 
    104,  97, 112, 101,  84, 121, 
    112, 101,   0,  83, 104,  97, 
    112, 101,  68,  97, 116,  97, 
      0,  83, 104,  97, 112, 101, 
     83, 105, 122, 101,   0,  69, 
    109, 105, 115, 115, 105, 118, 
    101,   0,  70,  97, 100, 101, 
     73, 110,   0,  70,  97, 100, 
    101,  79, 117, 116,   0,  80, 
     97, 100, 100, 105, 110, 103, 
     52,   0,  67, 111, 108, 111, 
    114,  68,  97, 116,  97,   0, 
    117, 105, 110, 116,  52,   0, 
      1,   0,  19,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 186,   6,   0,   0, 
     67, 111, 108, 111, 114,  69, 
     97, 115, 105, 110, 103,   0, 
     67, 111, 108, 111, 114,  70, 
    108,  97, 103, 115,   0,  77, 
     97, 116, 101, 114, 105,  97, 
    108,  84, 121, 112, 101,   0, 
     80,  97, 100, 100, 105, 110, 
    103,  53,   0,  80,  97, 100, 
    100, 105, 110, 103,  54,   0, 
     80,  97, 100, 100, 105, 110, 
    103,  55,   0, 171, 242,   3, 
      0,   0,   0,   4,   0,   0, 
      0,   0,   0,   0,  36,   4, 
      0,   0,   0,   4,   0,   0, 
      4,   0,   0,   0,  49,   4, 
      0,   0, 108,   2,   0,   0, 
      8,   0,   0,   0,  60,   4, 
      0,   0,  76,   4,   0,   0, 
     12,   0,   0,   0, 112,   4, 
      0,   0, 128,   4,   0,   0, 
     16,   0,   0,   0, 164,   4, 
      0,   0,  76,   4,   0,   0, 
     24,   0,   0,   0, 178,   4, 
      0,   0,  76,   4,   0,   0, 
     28,   0,   0,   0, 187,   4, 
      0,   0, 204,   4,   0,   0, 
     32,   0,   0,   0, 240,   4, 
      0,   0,  56,   2,   0,   0, 
     64,   0,   0,   0, 250,   4, 
      0,   0, 108,   2,   0,   0, 
     76,   0,   0,   0,   1,   5, 
      0,   0, 128,   4,   0,   0, 
     80,   0,   0,   0,  14,   5, 
      0,   0, 128,   4,   0,   0, 
     88,   0,   0,   0,  22,   5, 
      0,   0,  36,   5,   0,   0, 
     96,   0,   0,   0,  72,   5, 
      0,   0,  84,   5,   0,   0, 
    128,   0,   0,   0, 120,   5, 
      0,   0, 136,   5,   0,   0, 
    160,   0,   0,   0, 172,   5, 
      0,   0, 184,   5,   0,   0, 
    192,   0,   0,   0, 220,   5, 
      0,   0,  56,   2,   0,   0, 
    224,   0,   0,   0, 228,   5, 
      0,   0,  76,   4,   0,   0, 
    236,   0,   0,   0, 237,   5, 
      0,   0,  56,   2,   0,   0, 
    240,   0,   0,   0, 250,   5, 
      0,   0, 108,   2,   0,   0, 
    252,   0,   0,   0,   9,   6, 
      0,   0,  56,   2,   0,   0, 
      0,   1,   0,   0,  20,   6, 
      0,   0, 108,   2,   0,   0, 
     12,   1,   0,   0,  37,   6, 
      0,   0, 108,   2,   0,   0, 
     16,   1,   0,   0,  53,   6, 
      0,   0,  76,   4,   0,   0, 
     20,   1,   0,   0,  68,   6, 
      0,   0, 108,   2,   0,   0, 
     24,   1,   0,   0,  84,   6, 
      0,   0, 108,   2,   0,   0, 
     28,   1,   0,   0, 101,   6, 
      0,   0,  76,   4,   0,   0, 
     32,   1,   0,   0, 113,   6, 
      0,   0,  76,   4,   0,   0, 
     36,   1,   0,   0, 123,   6, 
      0,   0,  76,   4,   0,   0, 
     40,   1,   0,   0, 133,   6, 
      0,   0, 108,   2,   0,   0, 
     44,   1,   0,   0, 143,   6, 
      0,   0, 108,   2,   0,   0, 
     48,   1,   0,   0, 152,   6, 
      0,   0, 108,   2,   0,   0, 
     52,   1,   0,   0, 159,   6, 
      0,   0, 108,   2,   0,   0, 
     56,   1,   0,   0, 167,   6, 
      0,   0,  76,   4,   0,   0, 
     60,   1,   0,   0, 176,   6, 
      0,   0, 192,   6,   0,   0, 
     64,   1,   0,   0, 228,   6, 
      0,   0,  56,   2,   0,   0, 
     80,   1,   0,   0, 240,   6, 
      0,   0,  76,   4,   0,   0, 
     92,   1,   0,   0, 251,   6, 
      0,   0,  76,   4,   0,   0, 
     96,   1,   0,   0,   8,   7, 
      0,   0,  76,   4,   0,   0, 
    100,   1,   0,   0,  17,   7, 
      0,   0,  76,   4,   0,   0, 
    104,   1,   0,   0,  26,   7, 
      0,   0,  76,   4,   0,   0, 
    108,   1,   0,   0,   5,   0, 
      0,   0,   1,   0,  92,   0, 
      0,   0,  41,   0,  36,   7, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    229,   3,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  57,  46,  50, 
     57,  46,  57,  53,  50,  46, 
     51,  49,  49,  49,   0, 171, 
    171, 171,  73,  83,  71,  78, 
    180,   0,   0,   0,   6,   0, 
      0,   0,   8,   0,   0,   0, 
    152,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
    164,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   3,   3,   0,   0, 
    173,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  15,  15,   0,   0, 
    164,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   7,   0,   0, 
    164,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,   7,   7,   0,   0, 
    164,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   5,   0, 
      0,   0,   7,   7,   0,   0, 
     83,  86,  95,  80,  79,  83, 
     73,  84,  73,  79,  78,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  67,  79,  76, 
     79,  82,   0, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     97, 114, 103, 101, 116,   0, 
    171, 171,  83,  72,  69,  88, 
    224,   2,   0,   0,  80,   0, 
      0,   0, 184,   0,   0,   0, 
    106,   8,   0,   1,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,  19,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,  23,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   3,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   2,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      3,   0,   0,   0,  85,  85, 
      0,   0,  98,  16,   0,   3, 
     50,  16,  16,   0,   1,   0, 
      0,   0,  98,  16,   0,   3, 
    242,  16,  16,   0,   2,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   3,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   4,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   5,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      3,   0,   0,   0,  69,   0, 
      0, 139, 194,   0,   0, 128, 
     67,  85,  21,   0, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  16,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      2,   0,   0,   0,   0,  96, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70,  30,  16,   0, 
      2,   0,   0,   0,  32,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
     22,   0,   0,   0,   1,  64, 
      0,   0,   1,   0,   0,   0, 
     31,   0,   4,   3,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0, 139, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   3,   0,   0,   0, 
      0,  96,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  15, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,  64, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128, 191,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  86,   5,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,   9, 178,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0,  70,  24,  16,   0, 
      5,   0,   0,   0,  70,   8, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    166,  10,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      3,   0,   0,   0,  70,   3, 
     16,   0,   1,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  68,   0, 
      0,   5, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     52,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  11, 114,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
     17,   0,   0,   0,   6,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   0,   0,   0, 
      0,   0,  18,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  21,   0, 
      0,   1,  54,   0,   0,   5, 
    242,  32,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  19,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0,   8,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};
