#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tvs_4_0 /Emain /D __INST__=40 /Fh
//    EffekseerRenderer\ShaderHeader\ad_model_unlit_vs.h
//    EffekseerRenderer\Shader\ad_model_unlit_vs.fx
//
//
// Buffer Definitions: 
//
// cbuffer VS_ConstantBuffer
// {
//
//   float4x4 _372_mCameraProj;         // Offset:    0 Size:    64
//   float4x4 _372_mModel_Inst[40];     // Offset:   64 Size:  2560
//   float4 _372_fUV[40];               // Offset: 2624 Size:   640
//   float4 _372_fAlphaUV[40];          // Offset: 3264 Size:   640
//   float4 _372_fUVDistortionUV[40];   // Offset: 3904 Size:   640
//   float4 _372_fBlendUV[40];          // Offset: 4544 Size:   640
//   float4 _372_fBlendAlphaUV[40];     // Offset: 5184 Size:   640
//   float4 _372_fBlendUVDistortionUV[40];// Offset: 5824 Size:   640
//   float4 _372_flipbookParameter1;    // Offset: 6464 Size:    16
//   float4 _372_flipbookParameter2;    // Offset: 6480 Size:    16
//   float4 _372_fFlipbookIndexAndNextRate[40];// Offset: 6496 Size:   640
//   float4 _372_fModelAlphaThreshold[40];// Offset: 7136 Size:   640
//   float4 _372_fModelColor[40];       // Offset: 7776 Size:   640
//   float4 _372_fLightDirection;       // Offset: 8416 Size:    16 [unused]
//   float4 _372_fLightColor;           // Offset: 8432 Size:    16 [unused]
//   float4 _372_fLightAmbient;         // Offset: 8448 Size:    16 [unused]
//   float4 _372_mUVInversed;           // Offset: 8464 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// VS_ConstantBuffer                 cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xyz         0     NONE  float   xyz 
// TEXCOORD                 1   xyz         1     NONE  float   xyz 
// TEXCOORD                 2   xyz         2     NONE  float       
// TEXCOORD                 3   xyz         3     NONE  float       
// TEXCOORD                 4   xy          4     NONE  float   xy  
// TEXCOORD                 5   xyzw        5     NONE  float   xyzw
// SV_InstanceID            0   x           6   INSTID   uint   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xyzw        0     NONE  float   xyzw
// TEXCOORD                 1   xyzw        1     NONE  float   xyzw
// TEXCOORD                 2   xyz         2     NONE  float   xyz 
// TEXCOORD                 3   xyzw        3     NONE  float   xyzw
// TEXCOORD                 4   xyzw        4     NONE  float   xyzw
// TEXCOORD                 5   xyzw        5     NONE  float   xyzw
// TEXCOORD                 6   xyzw        6     NONE  float   xyzw
// SV_Position              0   xyzw        7      POS  float   xyzw
//
vs_4_0
dcl_constantbuffer cb0[530], dynamicIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v4.xy
dcl_input v5.xyzw
dcl_input_sgv v6.x, instance_id
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_output o2.xyz
dcl_output o3.xyzw
dcl_output o4.xyzw
dcl_output o5.xyzw
dcl_output o6.xyzw
dcl_output_siv o7.xyzw, position
dcl_temps 8
ishl r0.x, v6.x, l(2)
mov r0.y, v6.x
mul o0.xyzw, v5.xyzw, cb0[r0.y + 486].xyzw
mul r1.xyzw, v0.yyyy, cb0[r0.x + 5].xyzw
mad r1.xyzw, cb0[r0.x + 4].xyzw, v0.xxxx, r1.xyzw
mad r1.xyzw, cb0[r0.x + 6].xyzw, v0.zzzz, r1.xyzw
add r1.xyzw, r1.xyzw, cb0[r0.x + 7].xyzw
mul r2.xyzw, r1.yyyy, cb0[1].xyzw
mad r2.xyzw, cb0[0].xyzw, r1.xxxx, r2.xyzw
mad r2.xyzw, cb0[2].xyzw, r1.zzzz, r2.xyzw
mad r1.xyzw, cb0[3].xyzw, r1.wwww, r2.xyzw
mad r2.xz, v4.yyxy, cb0[r0.y + 164].wwzw, cb0[r0.y + 164].yyxy
mad r2.x, cb0[529].y, r2.x, cb0[529].x
mul r3.xyzw, v1.yyyy, cb0[r0.x + 5].xyzw
mad r3.xyzw, cb0[r0.x + 4].xyzw, v1.xxxx, r3.xyzw
mad r3.xyzw, cb0[r0.x + 6].xyzw, v1.zzzz, r3.xyzw
dp4 r0.x, r3.xyzw, r3.xyzw
rsq r0.x, r0.x
mul o2.xyz, r0.xxxx, r3.xyzx
mad o3.x, v4.x, cb0[r0.y + 204].z, cb0[r0.y + 204].x
mad r0.x, v4.y, cb0[r0.y + 204].w, cb0[r0.y + 204].y
mad o3.z, v4.x, cb0[r0.y + 244].z, cb0[r0.y + 244].x
mad r0.z, v4.y, cb0[r0.y + 244].w, cb0[r0.y + 244].y
mad o5.x, v4.x, cb0[r0.y + 284].z, cb0[r0.y + 284].x
mad r0.w, v4.y, cb0[r0.y + 284].w, cb0[r0.y + 284].y
mad o4.x, v4.x, cb0[r0.y + 324].z, cb0[r0.y + 324].x
mad r3.x, v4.y, cb0[r0.y + 324].w, cb0[r0.y + 324].y
mad o4.z, v4.x, cb0[r0.y + 364].z, cb0[r0.y + 364].x
mad r3.y, v4.y, cb0[r0.y + 364].w, cb0[r0.y + 364].y
lt r3.z, l(0.000000), cb0[404].x
if_nz r3.z
  frc r3.z, cb0[r0.y + 406].x
  round_ni r4.x, cb0[r0.y + 406].x
  add r3.w, r4.x, l(1.000000)
  mul r4.w, cb0[404].w, cb0[404].z
  eq r5.x, cb0[404].y, l(0.000000)
  if_nz r5.x
    ge r5.x, r3.w, r4.w
    mad r5.y, cb0[404].z, cb0[404].w, l(-1.000000)
    add r4.y, r4.x, l(1.000000)
    movc r5.xy, r5.xxxx, r5.yyyy, r4.xyxx
  else 
    div r4.y, r4.x, r4.w
    round_ni r4.y, r4.y
    mad r6.x, -r4.w, r4.y, r4.x
    div r5.z, r3.w, r4.w
    round_ni r5.z, r5.z
    mad r6.y, -r4.w, r5.z, r3.w
    eq r6.zw, cb0[404].yyyy, l(0.000000, 0.000000, 1.000000, 2.000000)
    mul r3.w, r4.y, l(0.500000)
    round_ni r3.w, r3.w
    mad r3.w, -r3.w, l(2.000000), r4.y
    eq r3.w, r3.w, l(1.000000)
    mad r4.y, cb0[404].z, cb0[404].w, l(-1.000000)
    round_ni r7.xy, r6.xyxx
    add r4.yw, r4.yyyy, -r7.xxxy
    movc r7.x, r3.w, r4.y, r6.x
    mul r3.w, r5.z, l(0.500000)
    round_ni r3.w, r3.w
    mad r3.w, -r3.w, l(2.000000), r5.z
    eq r3.w, r3.w, l(1.000000)
    movc r7.y, r3.w, r4.w, r6.y
    add r4.z, r4.x, l(1.000000)
    movc r4.xy, r6.wwww, r7.xyxx, r4.xzxx
    movc r5.xy, r6.zzzz, r6.xyxx, r4.xyxx
  endif 
  mad r2.y, cb0[529].y, r2.x, cb0[529].x
  ftoi r4.xy, r5.xyxx
  ftoi r3.w, cb0[404].z
  and r4.zw, r4.xxxy, l(0, 0, 0x80000000, 0x80000000)
  imax r5.xy, r4.xyxx, -r4.xyxx
  imax r5.z, r3.w, -r3.w
  udiv r5.x, r6.x, r5.x, r5.z
  ineg r5.w, r6.x
  movc r4.z, r4.z, r5.w, r6.x
  itof r6.x, r4.z
  xor r4.xy, r3.wwww, r4.xyxx
  ineg r3.w, r5.x
  and r4.xy, r4.xyxx, l(0x80000000, 0x80000000, 0, 0)
  movc r3.w, r4.x, r3.w, r5.x
  itof r6.y, r3.w
  mad r4.xz, r6.xxyx, cb0[405].xxyx, cb0[405].zzwz
  add r4.xz, r2.zzyz, -r4.xxzx
  udiv r5.x, r6.x, r5.y, r5.z
  ineg r3.w, r6.x
  movc r3.w, r4.w, r3.w, r6.x
  itof r6.x, r3.w
  ineg r3.w, r5.x
  movc r3.w, r4.y, r3.w, r5.x
  itof r6.y, r3.w
  mad r4.xy, r6.xyxx, cb0[405].xyxx, r4.xzxx
  add r4.xy, r4.xyxx, cb0[405].zwzz
  mad r4.z, cb0[529].y, r4.y, cb0[529].x
  mov o5.zw, r4.xxxz
  mov r2.y, r3.z
else 
  mov o5.zw, l(0,0,0,0)
  mov r2.y, l(0)
endif 
mad o3.y, cb0[529].y, r0.x, cb0[529].x
mad o3.w, cb0[529].y, r0.z, cb0[529].x
mad o5.y, cb0[529].y, r0.w, cb0[529].x
mad o4.y, cb0[529].y, r3.x, cb0[529].x
mad o4.w, cb0[529].y, r3.y, cb0[529].x
mov r2.w, cb0[r0.y + 446].x
mov o1.xyzw, r2.zxyw
mov o6.xyzw, r1.xyzw
mov o7.xyzw, r1.xyzw
ret 
// Approximately 109 instruction slots used
#endif

const uint8_t dx12_ad_model_unlit_vs[] =
{
     68,  88,  66,  67, 102, 250, 
    185,   5,  89,  96,  65,  46, 
     97,  53,  20, 160, 196,   0, 
    179, 132,   1,   0,   0,   0, 
    220,  21,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    148,   4,   0,   0, 100,   5, 
      0,   0,  76,   6,   0,   0, 
     96,  21,   0,   0,  82,  68, 
     69,  70,  88,   4,   0,   0, 
      1,   0,   0,   0,  80,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,  16,   1,   0,   0, 
     38,   4,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     86,  83,  95,  67, 111, 110, 
    115, 116,  97, 110, 116,  66, 
    117, 102, 102, 101, 114,   0, 
    171, 171,  60,   0,   0,   0, 
     17,   0,   0,   0, 104,   0, 
      0,   0,  32,  33,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   2,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
     20,   2,   0,   0,   0,   0, 
      0,   0,  36,   2,   0,   0, 
     64,   0,   0,   0,   0,  10, 
      0,   0,   2,   0,   0,   0, 
     56,   2,   0,   0,   0,   0, 
      0,   0,  72,   2,   0,   0, 
     64,  10,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
     84,   2,   0,   0,   0,   0, 
      0,   0, 100,   2,   0,   0, 
    192,  12,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    116,   2,   0,   0,   0,   0, 
      0,   0, 132,   2,   0,   0, 
     64,  15,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    156,   2,   0,   0,   0,   0, 
      0,   0, 172,   2,   0,   0, 
    192,  17,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    188,   2,   0,   0,   0,   0, 
      0,   0, 204,   2,   0,   0, 
     64,  20,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    224,   2,   0,   0,   0,   0, 
      0,   0, 240,   2,   0,   0, 
    192,  22,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
     12,   3,   0,   0,   0,   0, 
      0,   0,  28,   3,   0,   0, 
     64,  25,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0,  68,   3,   0,   0, 
     80,  25,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0,  92,   3,   0,   0, 
     96,  25,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    124,   3,   0,   0,   0,   0, 
      0,   0, 140,   3,   0,   0, 
    224,  27,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    168,   3,   0,   0,   0,   0, 
      0,   0, 184,   3,   0,   0, 
     96,  30,   0,   0, 128,   2, 
      0,   0,   2,   0,   0,   0, 
    204,   3,   0,   0,   0,   0, 
      0,   0, 220,   3,   0,   0, 
    224,  32,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0, 241,   3,   0,   0, 
    240,  32,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0,   2,   4,   0,   0, 
      0,  33,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0,  21,   4,   0,   0, 
     16,  33,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     52,   3,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 109,  67,  97, 109, 101, 
    114,  97,  80, 114, 111, 106, 
      0, 171, 171, 171,   3,   0, 
      3,   0,   4,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 109,  77, 111, 100, 101, 
    108,  95,  73, 110, 115, 116, 
      0, 171, 171, 171,   3,   0, 
      3,   0,   4,   0,   4,   0, 
     40,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102,  85,  86,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,  40,   0, 
      0,   0,   0,   0,   0,   0, 
     95,  51,  55,  50,  95, 102, 
     65, 108, 112, 104,  97,  85, 
     86,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
     40,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102,  85,  86,  68, 105, 
    115, 116, 111, 114, 116, 105, 
    111, 110,  85,  86,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,  40,   0, 
      0,   0,   0,   0,   0,   0, 
     95,  51,  55,  50,  95, 102, 
     66, 108, 101, 110, 100,  85, 
     86,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
     40,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102,  66, 108, 101, 110, 
    100,  65, 108, 112, 104,  97, 
     85,  86,   0, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
     40,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102,  66, 108, 101, 110, 
    100,  85,  86,  68, 105, 115, 
    116, 111, 114, 116, 105, 111, 
    110,  85,  86,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,  40,   0,   0,   0, 
      0,   0,   0,   0,  95,  51, 
     55,  50,  95, 102, 108, 105, 
    112,  98, 111, 111, 107,  80, 
     97, 114,  97, 109, 101, 116, 
    101, 114,  49,   0,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102, 108, 105, 112,  98, 
    111, 111, 107,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
     50,   0,  95,  51,  55,  50, 
     95, 102,  70, 108, 105, 112, 
     98, 111, 111, 107,  73, 110, 
    100, 101, 120,  65, 110, 100, 
     78, 101, 120, 116,  82,  97, 
    116, 101,   0, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
     40,   0,   0,   0,   0,   0, 
      0,   0,  95,  51,  55,  50, 
     95, 102,  77, 111, 100, 101, 
    108,  65, 108, 112, 104,  97, 
     84, 104, 114, 101, 115, 104, 
    111, 108, 100,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,  40,   0,   0,   0, 
      0,   0,   0,   0,  95,  51, 
     55,  50,  95, 102,  77, 111, 
    100, 101, 108,  67, 111, 108, 
    111, 114,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,  40,   0,   0,   0, 
      0,   0,   0,   0,  95,  51, 
     55,  50,  95, 102,  76, 105, 
    103, 104, 116,  68, 105, 114, 
    101,  99, 116, 105, 111, 110, 
      0,  95,  51,  55,  50,  95, 
    102,  76, 105, 103, 104, 116, 
     67, 111, 108, 111, 114,   0, 
     95,  51,  55,  50,  95, 102, 
     76, 105, 103, 104, 116,  65, 
    109,  98, 105, 101, 110, 116, 
      0,  95,  51,  55,  50,  95, 
    109,  85,  86,  73, 110, 118, 
    101, 114, 115, 101, 100,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171,  73,  83,  71,  78, 
    200,   0,   0,   0,   7,   0, 
      0,   0,   8,   0,   0,   0, 
    176,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   7,   7,   0,   0, 
    176,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   7,   0,   0, 
    176,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   7,   0,   0,   0, 
    176,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   0,   0,   0, 
    176,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,   3,   3,   0,   0, 
    176,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   5,   0, 
      0,   0,  15,  15,   0,   0, 
    185,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
      1,   0,   0,   0,   6,   0, 
      0,   0,   1,   1,   0,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  83,  86,  95, 
     73, 110, 115, 116,  97, 110, 
     99, 101,  73,  68,   0, 171, 
     79,  83,  71,  78, 224,   0, 
      0,   0,   8,   0,   0,   0, 
      8,   0,   0,   0, 200,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 200,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   0,   0,   0, 200,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      7,   8,   0,   0, 200,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,   0,   0,   0, 200,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
     15,   0,   0,   0, 200,   0, 
      0,   0,   5,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,   0,   0,   0, 200,   0, 
      0,   0,   6,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,   0,   0,   0, 209,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   7,   0,   0,   0, 
     15,   0,   0,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  83,  86,  95,  80, 111, 
    115, 105, 116, 105, 111, 110, 
      0, 171, 171, 171,  83,  72, 
     68,  82,  12,  15,   0,   0, 
     64,   0,   1,   0, 195,   3, 
      0,   0,  89,   8,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  18,   2,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     95,   0,   0,   3,  50,  16, 
     16,   0,   4,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   5,   0,   0,   0, 
     96,   0,   0,   4,  18,  16, 
     16,   0,   6,   0,   0,   0, 
      8,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      3,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      4,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      5,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      6,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      7,   0,   0,   0,   1,   0, 
      0,   0, 104,   0,   0,   2, 
      8,   0,   0,   0,  41,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,  16, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  10,  16,  16,   0, 
      6,   0,   0,   0,  56,   0, 
      0,  10, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  30, 
     16,   0,   5,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0, 230,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,  21,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
      5,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  12, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   6,  16,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  12, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0, 166,  26,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,   7,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      2,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 166,  10, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  15,  82,   0, 
     16,   0,   2,   0,   0,   0, 
     86,  20,  16,   0,   4,   0, 
      0,   0, 246, 142,  32,   6, 
      0,   0,   0,   0, 164,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  86, 132, 
     32,   6,   0,   0,   0,   0, 
    164,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  11,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     26, 128,  32,   0,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,  17,   2, 
      0,   0,  56,   0,   0,  10, 
    242,   0,  16,   0,   3,   0, 
      0,   0,  86,  21,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
      5,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  12, 242,   0, 
     16,   0,   3,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   6,  16,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  12, 242,   0, 
     16,   0,   3,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0, 166,  26,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     17,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  68,   0, 
      0,   5,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,  32, 
     16,   0,   2,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  15,  18,  32,  16,   0, 
      3,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   6,   0,   0, 
      0,   0, 204,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0, 204,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  18,   0,  16,   0, 
      0,   0,   0,   0,  26,  16, 
     16,   0,   4,   0,   0,   0, 
     58, 128,  32,   6,   0,   0, 
      0,   0, 204,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   6, 
      0,   0,   0,   0, 204,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  66,  32,  16,   0, 
      3,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   6,   0,   0, 
      0,   0, 244,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0, 244,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  66,   0,  16,   0, 
      0,   0,   0,   0,  26,  16, 
     16,   0,   4,   0,   0,   0, 
     58, 128,  32,   6,   0,   0, 
      0,   0, 244,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   6, 
      0,   0,   0,   0, 244,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  18,  32,  16,   0, 
      5,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   6,   0,   0, 
      0,   0,  28,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0,  28,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15, 130,   0,  16,   0, 
      0,   0,   0,   0,  26,  16, 
     16,   0,   4,   0,   0,   0, 
     58, 128,  32,   6,   0,   0, 
      0,   0,  28,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   6, 
      0,   0,   0,   0,  28,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  18,  32,  16,   0, 
      4,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   6,   0,   0, 
      0,   0,  68,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0,  68,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  18,   0,  16,   0, 
      3,   0,   0,   0,  26,  16, 
     16,   0,   4,   0,   0,   0, 
     58, 128,  32,   6,   0,   0, 
      0,   0,  68,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   6, 
      0,   0,   0,   0,  68,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  66,  32,  16,   0, 
      4,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   6,   0,   0, 
      0,   0, 108,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0, 108,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  15,  34,   0,  16,   0, 
      3,   0,   0,   0,  26,  16, 
     16,   0,   4,   0,   0,   0, 
     58, 128,  32,   6,   0,   0, 
      0,   0, 108,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26, 128,  32,   6, 
      0,   0,   0,   0, 108,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  49,   0, 
      0,   8,  66,   0,  16,   0, 
      3,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0, 148,   1,   0,   0, 
     31,   0,   4,   3,  42,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,   0,   8,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     10, 128,  32,   6,   0,   0, 
      0,   0, 150,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  65,   0,   0,   8, 
     18,   0,  16,   0,   4,   0, 
      0,   0,  10, 128,  32,   6, 
      0,   0,   0,   0, 150,   1, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  56,   0,   0,   9, 
    130,   0,  16,   0,   4,   0, 
      0,   0,  58, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,  24,   0,   0,   8, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  10,   0,  16,   0, 
      5,   0,   0,   0,  29,   0, 
      0,   7,  18,   0,  16,   0, 
      5,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16,   0,   4,   0, 
      0,   0,  50,   0,   0,  11, 
     34,   0,  16,   0,   5,   0, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,  58, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128, 191,   0,   0, 
      0,   7,  34,   0,  16,   0, 
      4,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  55,   0,   0,   9, 
     50,   0,  16,   0,   5,   0, 
      0,   0,   6,   0,  16,   0, 
      5,   0,   0,   0,  86,   5, 
     16,   0,   5,   0,   0,   0, 
     70,   0,  16,   0,   4,   0, 
      0,   0,  18,   0,   0,   1, 
     14,   0,   0,   7,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   4,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,  65,   0, 
      0,   5,  34,   0,  16,   0, 
      4,   0,   0,   0,  26,   0, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,  10,  18,   0, 
     16,   0,   6,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  14,   0, 
      0,   7,  66,   0,  16,   0, 
      5,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16,   0,   4,   0, 
      0,   0,  65,   0,   0,   5, 
     66,   0,  16,   0,   5,   0, 
      0,   0,  42,   0,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  10,  34,   0,  16,   0, 
      6,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      4,   0,   0,   0,  42,   0, 
     16,   0,   5,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  24,   0,   0,  11, 
    194,   0,  16,   0,   6,   0, 
      0,   0,  86, 133,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0,   0,  64,  56,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  26,   0, 
     16,   0,   4,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,  65,   0,   0,   5, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  10, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      3,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  64, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  24,   0,   0,   7, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     50,   0,   0,  11,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     42, 128,  32,   0,   0,   0, 
      0,   0, 148,   1,   0,   0, 
     58, 128,  32,   0,   0,   0, 
      0,   0, 148,   1,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128, 191,  65,   0,   0,   5, 
     50,   0,  16,   0,   7,   0, 
      0,   0,  70,   0,  16,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   8, 162,   0,  16,   0, 
      4,   0,   0,   0,  86,   5, 
     16,   0,   4,   0,   0,   0, 
      6,   4,  16, 128,  65,   0, 
      0,   0,   7,   0,   0,   0, 
     55,   0,   0,   9,  18,   0, 
     16,   0,   7,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   5,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  65,   0, 
      0,   5, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  64,  42,   0,  16,   0, 
      5,   0,   0,   0,  24,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  55,   0,   0,   9, 
     34,   0,  16,   0,   7,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   4,   0,   0,   0, 
     26,   0,  16,   0,   6,   0, 
      0,   0,   0,   0,   0,   7, 
     66,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     55,   0,   0,   9,  50,   0, 
     16,   0,   4,   0,   0,   0, 
    246,  15,  16,   0,   6,   0, 
      0,   0,  70,   0,  16,   0, 
      7,   0,   0,   0, 134,   0, 
     16,   0,   4,   0,   0,   0, 
     55,   0,   0,   9,  50,   0, 
     16,   0,   5,   0,   0,   0, 
    166,  10,  16,   0,   6,   0, 
      0,   0,  70,   0,  16,   0, 
      6,   0,   0,   0,  70,   0, 
     16,   0,   4,   0,   0,   0, 
     21,   0,   0,   1,  50,   0, 
      0,  11,  34,   0,  16,   0, 
      2,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     27,   0,   0,   5,  50,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   0,  16,   0,   5,   0, 
      0,   0,  27,   0,   0,   6, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0, 148,   1, 
      0,   0,   1,   0,   0,  10, 
    194,   0,  16,   0,   4,   0, 
      0,   0,   6,   4,  16,   0, 
      4,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0, 128,   0,   0,   0, 128, 
     36,   0,   0,   8,  50,   0, 
     16,   0,   5,   0,   0,   0, 
     70,   0,  16,   0,   4,   0, 
      0,   0,  70,   0,  16, 128, 
     65,   0,   0,   0,   4,   0, 
      0,   0,  36,   0,   0,   8, 
     66,   0,  16,   0,   5,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      3,   0,   0,   0,  78,   0, 
      0,   9,  18,   0,  16,   0, 
      5,   0,   0,   0,  18,   0, 
     16,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  42,   0,  16,   0, 
      5,   0,   0,   0,  40,   0, 
      0,   5, 130,   0,  16,   0, 
      5,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
     55,   0,   0,   9,  66,   0, 
     16,   0,   4,   0,   0,   0, 
     42,   0,  16,   0,   4,   0, 
      0,   0,  58,   0,  16,   0, 
      5,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
     43,   0,   0,   5,  18,   0, 
     16,   0,   6,   0,   0,   0, 
     42,   0,  16,   0,   4,   0, 
      0,   0,  87,   0,   0,   7, 
     50,   0,  16,   0,   4,   0, 
      0,   0, 246,  15,  16,   0, 
      3,   0,   0,   0,  70,   0, 
     16,   0,   4,   0,   0,   0, 
     40,   0,   0,   5, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,   1,   0,   0,  10, 
     50,   0,  16,   0,   4,   0, 
      0,   0,  70,   0,  16,   0, 
      4,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0, 128, 
      0,   0,   0, 128,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     55,   0,   0,   9, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   4,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     43,   0,   0,   5,  34,   0, 
     16,   0,   6,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  11, 
     82,   0,  16,   0,   4,   0, 
      0,   0,   6,   1,  16,   0, 
      6,   0,   0,   0,   6, 129, 
     32,   0,   0,   0,   0,   0, 
    149,   1,   0,   0, 166, 139, 
     32,   0,   0,   0,   0,   0, 
    149,   1,   0,   0,   0,   0, 
      0,   8,  82,   0,  16,   0, 
      4,   0,   0,   0, 166,   9, 
     16,   0,   2,   0,   0,   0, 
      6,   2,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     78,   0,   0,   9,  18,   0, 
     16,   0,   5,   0,   0,   0, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  26,   0,  16,   0, 
      5,   0,   0,   0,  42,   0, 
     16,   0,   5,   0,   0,   0, 
     40,   0,   0,   5, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,  55,   0,   0,   9, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,  43,   0,   0,   5, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  40,   0, 
      0,   5, 130,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     55,   0,   0,   9, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     43,   0,   0,   5,  34,   0, 
     16,   0,   6,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  10, 
     50,   0,  16,   0,   4,   0, 
      0,   0,  70,   0,  16,   0, 
      6,   0,   0,   0,  70, 128, 
     32,   0,   0,   0,   0,   0, 
    149,   1,   0,   0, 134,   0, 
     16,   0,   4,   0,   0,   0, 
      0,   0,   0,   8,  50,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   0,  16,   0,   4,   0, 
      0,   0, 230, 138,  32,   0, 
      0,   0,   0,   0, 149,   1, 
      0,   0,  50,   0,   0,  11, 
     66,   0,  16,   0,   4,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,  17,   2, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  54,   0, 
      0,   5, 194,  32,  16,   0, 
      5,   0,   0,   0,   6,   8, 
     16,   0,   4,   0,   0,   0, 
     54,   0,   0,   5,  34,   0, 
     16,   0,   2,   0,   0,   0, 
     42,   0,  16,   0,   3,   0, 
      0,   0,  18,   0,   0,   1, 
     54,   0,   0,   8, 194,  32, 
     16,   0,   5,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   2,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  21,   0, 
      0,   1,  50,   0,   0,  11, 
     34,  32,  16,   0,   3,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,  17,   2, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  50,   0, 
      0,  11, 130,  32,  16,   0, 
      3,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     50,   0,   0,  11,  34,  32, 
     16,   0,   5,   0,   0,   0, 
     26, 128,  32,   0,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,  17,   2, 
      0,   0,  50,   0,   0,  11, 
     34,  32,  16,   0,   4,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,  17,   2, 
      0,   0,  10,   0,  16,   0, 
      3,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  50,   0, 
      0,  11, 130,  32,  16,   0, 
      4,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
     17,   2,   0,   0,  26,   0, 
     16,   0,   3,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  17,   2,   0,   0, 
     54,   0,   0,   8, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     10, 128,  32,   6,   0,   0, 
      0,   0, 190,   1,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
    242,  32,  16,   0,   1,   0, 
      0,   0,  38,  13,  16,   0, 
      2,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      6,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   7,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0, 109,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0,  13,   0,   0,   0, 
     32,   0,   0,   0,   7,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,   9,   0, 
      0,   0,  13,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
