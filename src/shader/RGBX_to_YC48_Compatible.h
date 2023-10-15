#if 0
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Input
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Output
cs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[1], immediateIndexed
dcl_resource_texture2d (float,float,float,float) t0
dcl_uav_typed_buffer (uint,uint,uint,uint) u0
dcl_input vThreadIDInGroupFlattened
dcl_input vThreadGroupID.xy
dcl_temps 5
dcl_thread_group 256, 1, 1
ishl [precise(x)] r0.x, cb0[0].x, l(8)
ishl [precise(y)] r0.y, vThreadGroupID.x, l(8)
imad [precise(x)] r0.x, r0.x, vThreadGroupID.y, r0.y
iadd [precise(x)] r0.x, r0.x, vThreadIDInGroupFlattened.x
uge [precise(y)] r0.y, r0.x, cb0[0].z
if_nz r0.y
  ret 
endif 
udiv [precise(x)] r1.x, r2.x, r0.x, cb0[0].y
udiv [precise(x)] r2.x, r3.x, r2.x, l(3)
ishl [precise(x)] r2.x, r2.x, l(1)
switch r3.x
  case l(0)
  mov [precise(y)] r2.y, r1.x
  mov [precise(z)] r2.z, l(0)
  ld_indexable [precise](texture2d)(float,float,float,float) r1.yzw, r2.xyzz, t0.wxyz
  mul [precise] r3.xyzw, r1.wzyw, l(255.000000, 255.000000, 255.000000, 255.000000)
  ftoi [precise] r3.xyzw, r3.xyzw
  imax [precise] r3.xyzw, r3.xyzw, l(0, 0, 0, 0)
  imin [precise] r3.xyzw, r3.xyzw, l(255, 255, 255, 255)
  imad [precise] r4.xyzw, r3.xyzw, l(0x0001d4c0, 0x00096dc0, 0x0004cd80, 0x00080800), l(0x000083d6, 0x0002a6de, 0x000159cc, 0x00024240)
  ishr [precise] r4.xyzw, r4.xyzw, l(16, 16, 16, 16)
  iadd [precise(z)] r0.z, r4.y, r4.x
  iadd [precise(z)] r0.z, r4.z, r0.z
  imad [precise(yz)] r1.yz, r3.yyzy, l(0, 0xfffaadc0, 0xfffd4a40, 0), l(0, 0xfffe80de, 0xffff3ce2, 0)
  ishr [precise(yz)] r1.yz, r1.yyzy, l(0, 16, 16, 0)
  iadd [precise(w)] r0.w, r1.y, r4.w
  iadd [precise(w)] r0.w, r1.z, r0.w
  ishl [precise(w)] r0.w, r0.w, l(16)
  iadd [precise(zw)] r0.zw, r0.zzzw, l(0, 0, -3, 0x00010000)
  bfi [precise(y)] r0.y, l(16), l(0), r0.z, r0.w
  break 
  case l(1)
  mov [precise(y)] r2.y, r1.x
  mov [precise(zw)] r2.zw, l(0,0,0,0)
  ld_indexable [precise](texture2d)(float,float,float,float) r1.yzw, r2.xyzw, t0.wxyz
  mul [precise(yzw)] r1.yzw, r1.wwzy, l(0.000000, 255.000000, 255.000000, 255.000000)
  ftoi [precise(yzw)] r1.yzw, r1.yyzw
  imax [precise(yzw)] r1.yzw, r1.yyzw, l(0, 0, 0, 0)
  imin [precise(yzw)] r1.yzw, r1.yyzw, l(0, 255, 255, 255)
  imad [precise(yzw)] r1.yzw, r1.yyzw, l(0, 0xfffeb1c0, 0xfff94640, 0x00080800), l(0, 0xffffa1fe, 0xfffe1bc2, 0x00024240)
  ishr [precise(yzw)] r1.yzw, r1.yyzw, l(0, 16, 16, 16)
  iadd [precise(z)] r0.z, r1.z, r1.y
  iadd [precise(z)] r0.z, r1.w, r0.z
  iadd [precise(xy)] r3.xy, r2.xyxx, l(1, 0, 0, 0)
  mov [precise(zw)] r3.zw, l(0,0,0,0)
  ld_indexable [precise](texture2d)(float,float,float,float) r1.yzw, r3.xyzw, t0.wxyz
  mul [precise(yzw)] r1.yzw, r1.wwzy, l(0.000000, 255.000000, 255.000000, 255.000000)
  ftoi [precise(yzw)] r1.yzw, r1.yyzw
  imax [precise(yzw)] r1.yzw, r1.yyzw, l(0, 0, 0, 0)
  imin [precise(yzw)] r1.yzw, r1.yyzw, l(0, 255, 255, 255)
  imad [precise(yzw)] r1.yzw, r1.yyzw, l(0, 0x0001d4c0, 0x00096dc0, 0x0004cd80), l(0, 0x000083d6, 0x0002a6de, 0x000159cc)
  ishr [precise(yzw)] r1.yzw, r1.yyzw, l(0, 16, 16, 16)
  iadd [precise(w)] r0.w, r1.z, r1.y
  iadd [precise(w)] r0.w, r1.w, r0.w
  ishl [precise(w)] r0.w, r0.w, l(16)
  iadd [precise(zw)] r0.zw, r0.zzzw, l(0, 0, 1, 0xfffd0000)
  bfi [precise(y)] r0.y, l(16), l(0), r0.z, r0.w
  break 
  default 
  mov [precise(w)] r2.w, r1.x
  iadd [precise(xy)] r1.xy, r2.xwxx, l(1, 0, 0, 0)
  mov [precise(zw)] r1.zw, l(0,0,0,0)
  ld_indexable [precise](texture2d)(float,float,float,float) r1.xyz, r1.xyzw, t0.xyzw
  mul [precise] r1.xyzw, r1.zyxz, l(255.000000, 255.000000, 255.000000, 255.000000)
  ftoi [precise] r1.xyzw, r1.xyzw
  imax [precise] r1.xyzw, r1.xyzw, l(0, 0, 0, 0)
  imin [precise] r1.xyzw, r1.xyzw, l(255, 255, 255, 255)
  imad [precise] r2.xyzw, r1.xyzw, l(0x00080800, 0xfffaadc0, 0xfffd4a40, 0xfffeb1c0), l(0x00024240, 0xfffe80de, 0xffff3ce2, 0xffffa1fe)
  ishr [precise] r2.xyzw, r2.xyzw, l(16, 16, 16, 16)
  iadd [precise(z)] r0.z, r2.y, r2.x
  iadd [precise(z)] r0.z, r2.z, r0.z
  imad [precise(xy)] r1.xy, r1.yzyy, l(0xfff94640, 0x00080800, 0, 0), l(0xfffe1bc2, 0x00024240, 0, 0)
  ishr [precise(xy)] r1.xy, r1.xyxx, l(16, 16, 0, 0)
  iadd [precise(w)] r0.w, r1.x, r2.w
  iadd [precise(w)] r0.w, r1.y, r0.w
  ishl [precise(w)] r0.w, r0.w, l(16)
  iadd [precise(zw)] r0.zw, r0.zzzw, l(0, 0, 1, 0x00010000)
  bfi [precise(y)] r0.y, l(16), l(0), r0.z, r0.w
  break 
endswitch 
store_uav_typed u0.xyzw, r0.xxxx, r0.yyyy
ret 
// Approximately 0 instruction slots used
#endif

const BYTE g_RGBX_to_YC48_CompatibleConvert[] =
{
     68,  88,  66,  67, 142, 201, 
    240, 206,  28, 138, 204, 109, 
     27,  57, 155,  62, 230,  52, 
    160, 221,   1,   0,   0,   0, 
    212,  10,   0,   0,   3,   0, 
      0,   0,  44,   0,   0,   0, 
     60,   0,   0,   0,  76,   0, 
      0,   0,  73,  83,  71,  78, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     79,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  83,  72, 
     69,  88, 128,  10,   0,   0, 
     80,   0,   5,   0, 160,   2, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0, 156,   8,   0,   4, 
      0, 224,  17,   0,   0,   0, 
      0,   0,  68,  68,   0,   0, 
     95,   0,   0,   2,   0,  64, 
      2,   0,  95,   0,   0,   2, 
     50,  16,   2,   0, 104,   0, 
      0,   2,   5,   0,   0,   0, 
    155,   0,   0,   4,   0,   1, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  41,   0, 
      8,   8,  18,   0,  16,   0, 
      0,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   8,   0,   0,   0, 
     41,   0,  16,   6,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     10,  16,   2,   0,   1,  64, 
      0,   0,   8,   0,   0,   0, 
     35,   0,   8,   8,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  26,  16,   2,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  30,   0,   8,   6, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10,  64, 
      2,   0,  80,   0,  16,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  26,   0,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  21,   0,   0,   1, 
     78,   0,   8,  10,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  78,   0, 
      8,   9,  18,   0,  16,   0, 
      2,   0,   0,   0,  18,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,   1,  64,   0,   0, 
      3,   0,   0,   0,  41,   0, 
      8,   7,  18,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,  76,   0,   0,   3, 
     10,   0,  16,   0,   3,   0, 
      0,   0,   6,   0,   0,   3, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  54,   0,  16,   5, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  54,   0, 
     32,   5,  66,   0,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     45,   0, 120, 137, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  70,  10,  16,   0, 
      2,   0,   0,   0,  54, 121, 
     16,   0,   0,   0,   0,   0, 
     56,   0, 120,  10, 242,   0, 
     16,   0,   3,   0,   0,   0, 
    182,  13,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 127,  67,   0,   0, 
    127,  67,   0,   0, 127,  67, 
      0,   0, 127,  67,  27,   0, 
    120,   5, 242,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     36,   0, 120,  10, 242,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  37,   0, 
    120,  10, 242,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0, 255,   0, 
      0,   0, 255,   0,   0,   0, 
    255,   0,   0,   0, 255,   0, 
      0,   0,  35,   0, 120,  15, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,   2,  64, 
      0,   0, 192, 212,   1,   0, 
    192, 109,   9,   0, 128, 205, 
      4,   0,   0,   8,   8,   0, 
      2,  64,   0,   0, 214, 131, 
      0,   0, 222, 166,   2,   0, 
    204,  89,   1,   0,  64,  66, 
      2,   0,  42,   0, 120,  10, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,   2,  64, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,  16,   0,   0,   0, 
     30,   0,  32,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  30,   0, 
     32,   7,  66,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   4,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  35,   0,  48,  15, 
     98,   0,  16,   0,   1,   0, 
      0,   0,  86,   6,  16,   0, 
      3,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
    192, 173, 250, 255,  64,  74, 
    253, 255,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0, 222, 128, 254, 255, 
    226,  60, 255, 255,   0,   0, 
      0,   0,  42,   0,  48,  10, 
     98,   0,  16,   0,   1,   0, 
      0,   0,  86,   6,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     30,   0,  64,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,  30,   0, 
     64,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  41,   0,  64,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,  16,   0,   0,   0, 
     30,   0,  96,  10, 194,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  14,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 253, 255, 255, 255, 
      0,   0,   1,   0, 140,   0, 
     16,  11,  34,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,  16,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      2,   0,   0,   1,   6,   0, 
      0,   3,   1,  64,   0,   0, 
      1,   0,   0,   0,  54,   0, 
     16,   5,  34,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     54,   0,  96,   8, 194,   0, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  45,   0, 120, 137, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 226,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     54, 121,  16,   0,   0,   0, 
      0,   0,  56,   0, 112,  10, 
    226,   0,  16,   0,   1,   0, 
      0,   0, 246,   6,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 127,  67,   0,   0, 
    127,  67,   0,   0, 127,  67, 
     27,   0, 112,   5, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  14,  16,   0,   1,   0, 
      0,   0,  36,   0, 112,  10, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     37,   0, 112,  10, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  14,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0, 255,   0, 
      0,   0, 255,   0,   0,   0, 
    255,   0,   0,   0,  35,   0, 
    112,  15, 226,   0,  16,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0, 192, 177, 254, 255, 
     64,  70, 249, 255,   0,   8, 
      8,   0,   2,  64,   0,   0, 
      0,   0,   0,   0, 254, 161, 
    255, 255, 194,  27, 254, 255, 
     64,  66,   2,   0,  42,   0, 
    112,  10, 226,   0,  16,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,  30,   0,  32,   7, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     30,   0,  32,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  30,   0, 
     24,  10,  50,   0,  16,   0, 
      3,   0,   0,   0,  70,   0, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  54,   0,  96,   8, 
    194,   0,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  45,   0, 
    120, 137, 194,   0,   0, 128, 
     67,  85,  21,   0, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  54, 121,  16,   0, 
      0,   0,   0,   0,  56,   0, 
    112,  10, 226,   0,  16,   0, 
      1,   0,   0,   0, 246,   6, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0, 127,  67, 
      0,   0, 127,  67,   0,   0, 
    127,  67,  27,   0, 112,   5, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      1,   0,   0,   0,  36,   0, 
    112,  10, 226,   0,  16,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  37,   0, 112,  10, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
    255,   0,   0,   0, 255,   0, 
      0,   0, 255,   0,   0,   0, 
     35,   0, 112,  15, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  14,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0, 192, 212, 
      1,   0, 192, 109,   9,   0, 
    128, 205,   4,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
    214, 131,   0,   0, 222, 166, 
      2,   0, 204,  89,   1,   0, 
     42,   0, 112,  10, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  14,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,  30,   0, 
     64,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,  64,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     41,   0,  64,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
     16,   0,   0,   0,  30,   0, 
     96,  10, 194,   0,  16,   0, 
      0,   0,   0,   0, 166,  14, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
    253, 255, 140,   0,  16,  11, 
     34,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
     16,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   1,  10,   0,   0,   1, 
     54,   0,  64,   5, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,  24,  10, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 198,   0,  16,   0, 
      2,   0,   0,   0,   2,  64, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     54,   0,  96,   8, 194,   0, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  45,   0, 120, 137, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 114,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,  56,   0, 120,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 102,   8,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 127,  67, 
      0,   0, 127,  67,   0,   0, 
    127,  67,   0,   0, 127,  67, 
     27,   0, 120,   5, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  36,   0, 120,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     37,   0, 120,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
    255,   0,   0,   0, 255,   0, 
      0,   0, 255,   0,   0,   0, 
    255,   0,   0,   0,  35,   0, 
    120,  15, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   8, 
      8,   0, 192, 173, 250, 255, 
     64,  74, 253, 255, 192, 177, 
    254, 255,   2,  64,   0,   0, 
     64,  66,   2,   0, 222, 128, 
    254, 255, 226,  60, 255, 255, 
    254, 161, 255, 255,  42,   0, 
    120,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,  16,   0, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,  30,   0,  32,   7, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     30,   0,  32,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   2,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  35,   0, 
     24,  15,  50,   0,  16,   0, 
      1,   0,   0,   0, 150,   5, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,  64,  70, 
    249, 255,   0,   8,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
    194,  27, 254, 255,  64,  66, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  42,   0, 
     24,  10,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,  16,   0, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  30,   0,  64,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     30,   0,  64,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  41,   0, 
     64,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,  16,   0, 
      0,   0,  30,   0,  96,  10, 
    194,   0,  16,   0,   0,   0, 
      0,   0, 166,  14,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   1,   0, 
    140,   0,  16,  11,  34,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,  16,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   2,   0,   0,   1, 
     23,   0,   0,   1, 164,   0, 
      0,   7, 242, 224,  17,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1
};