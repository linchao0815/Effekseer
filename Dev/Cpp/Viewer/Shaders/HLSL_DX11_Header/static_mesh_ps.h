#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0 /Emain /Fh HLSL_DX11_Header/static_mesh_ps.h
//    HLSL_DX11/static_mesh_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer PS_ConstantBuffer
// {
//
//   float4 isLit;                      // Offset:    0 Size:    16
//   float4 directionalLightDirection;  // Offset:   16 Size:    16
//   float4 directionalLightColor;      // Offset:   32 Size:    16
//   float4 ambientLightColor;          // Offset:   48 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_sampler                         sampler      NA          NA    0        1
// g_texture                         texture  float4          2d    0        1
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
// NORMAL                   0   xyzw        2     NONE  float   xyzw
// NORMAL                   1   xyz         3     NONE  float   xyz 
// NORMAL                   2   xyzw        4     NONE  float     zw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_TARGET                0   xyzw        0   TARGET  float   xyzw
// SV_TARGET                1   xyzw        1   TARGET  float   xyzw
//
ps_4_0
dcl_constantbuffer cb1[4], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v1.xy
dcl_input_ps linear v2.xyzw
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.zw
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_temps 2
dp3 r0.x, cb1[1].xyzx, v3.xyzx
max r0.x, r0.x, l(0.000000)
mad r0.xyz, cb1[2].xyzx, r0.xxxx, cb1[3].xyzx
sample r1.xyzw, v1.xyxx, t0.xyzw, s0
mul r1.xyzw, r1.xyzw, v2.xyzw
mul r0.xyz, r0.xyzx, r1.xyzx
lt r0.w, l(0.000000), cb1[0].x
movc o0.xyz, r0.wwww, r0.xyzx, r1.xyzx
mov o0.w, r1.w
div o1.x, v4.z, v4.w
mov o1.yzw, l(0,1.000000,1.000000,1.000000)
ret 
// Approximately 12 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67,  29,  61, 
    162,  98, 200, 235, 195,  11, 
    172, 218,  93, 142, 182,  50, 
    239, 139,   1,   0,   0,   0, 
     56,   5,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    228,   1,   0,   0, 136,   2, 
      0,   0, 212,   2,   0,   0, 
    188,   4,   0,   0,  82,  68, 
     69,  70, 168,   1,   0,   0, 
      1,   0,   0,   0, 164,   0, 
      0,   0,   3,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    118,   1,   0,   0, 124,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    134,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 144,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 103,  95, 
    115,  97, 109, 112, 108, 101, 
    114,   0, 103,  95, 116, 101, 
    120, 116, 117, 114, 101,   0, 
     80,  83,  95,  67, 111, 110, 
    115, 116,  97, 110, 116,  66, 
    117, 102, 102, 101, 114,   0, 
    171, 171, 144,   0,   0,   0, 
      4,   0,   0,   0, 188,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  28,   1,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,  52,   1,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,  78,   1,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0, 100,   1,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0, 105, 115,  76, 105, 
    116,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 100, 105, 114, 101, 
     99, 116, 105, 111, 110,  97, 
    108,  76, 105, 103, 104, 116, 
     68, 105, 114, 101,  99, 116, 
    105, 111, 110,   0, 100, 105, 
    114, 101,  99, 116, 105, 111, 
    110,  97, 108,  76, 105, 103, 
    104, 116,  67, 111, 108, 111, 
    114,   0,  97, 109,  98, 105, 
    101, 110, 116,  76, 105, 103, 
    104, 116,  67, 111, 108, 111, 
    114,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171,  73,  83, 
     71,  78, 156,   0,   0,   0, 
      5,   0,   0,   0,   8,   0, 
      0,   0, 128,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 140,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   3,   3, 
      0,   0, 149,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  15,  15, 
      0,   0, 149,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   7, 
      0,   0, 149,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,  12, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  78, 
     79,  82,  77,  65,  76,   0, 
     79,  83,  71,  78,  68,   0, 
      0,   0,   2,   0,   0,   0, 
      8,   0,   0,   0,  56,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  56,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  65,  82,  71,  69, 
     84,   0, 171, 171,  83,  72, 
     68,  82, 224,   1,   0,   0, 
     64,   0,   0,   0, 120,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   4,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0,  98,  16, 
      0,   3, 242,  16,  16,   0, 
      2,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      3,   0,   0,   0,  98,  16, 
      0,   3, 194,  16,  16,   0, 
      4,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,   2,   0,   0,   0, 
     16,   0,   0,   8,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     70,  18,  16,   0,   3,   0, 
      0,   0,  52,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  11, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  49,   0, 
      0,   8, 130,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     55,   0,   0,   9, 114,  32, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  14,   0,   0,   7, 
     18,  32,  16,   0,   1,   0, 
      0,   0,  42,  16,  16,   0, 
      4,   0,   0,   0,  58,  16, 
     16,   0,   4,   0,   0,   0, 
     54,   0,   0,   8, 226,  32, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  12,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
