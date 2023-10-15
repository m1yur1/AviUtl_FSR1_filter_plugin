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
dcl_resource_buffer (uint,uint,uint,uint) t0
dcl_uav_typed_texture2d (float,float,float,float) u0
dcl_input vThreadGroupID.xy
dcl_input vThreadIDInGroup.xy
dcl_temps 4
dcl_thread_group 16, 16, 1
imad [precise] r0.xyzw, vThreadGroupID.xyyy, l(16, 16, 16, 16), vThreadIDInGroup.xyyy
uge [precise(xy)] r1.xy, r0.xwxx, cb0[0].yzyy
or [precise(x)] r1.x, r1.y, r1.x
if_nz r1.x
  ret 
endif 
imul [precise(x)] null, r1.x, r0.x, l(6)
ushr [precise(x)] r1.x, r1.x, l(2)
imad [precise(x)] r1.x, r0.w, cb0[0].x, r1.x
ld_indexable [precise(y)](buffer)(uint,uint,uint,uint) r1.y, r1.xxxx, t0.yxzw
iadd [precise(x)] r1.x, r1.x, l(1)
ld_indexable [precise(x)](buffer)(uint,uint,uint,uint) r1.x, r1.xxxx, t0.xyzw
and [precise(z)] r1.z, r0.x, l(1)
ishr [precise(yw)] r2.yw, r1.yyyx, l(0, 16, 0, 16)
ibfe [precise(xz)] r2.xz, l(16, 0, 16, 0), l(0, 0, 0, 0), r1.yyxy
movc [precise(xyz)] r1.xyz, r1.zzzz, r2.yzwy, r2.xyzx
itof [precise(xyz)] r1.xyz, r1.xyzx
div [precise(xyz)] r1.xyz, r1.xyzx, l(4096.000000, 4096.000000, 4096.000000, 0.000000)
mul [precise] r2.xyzw, r1.zzyy, l(1.402000, 0.714136, 0.344136, 1.772000)
add [precise(y)] r1.y, r1.x, -r2.y
add_sat [precise(y)] r3.y, -r2.z, r1.y
add_sat [precise(xz)] r3.xz, r1.xxxx, r2.xxwx
mov r3.w, l(1.000000)
store_uav_typed u0.xyzw, r0.xyzw, r3.xyzw
ret 
// Approximately 0 instruction slots used
#endif

const BYTE g_YC48_to_RGBX_NoCompatibleConvert[] =
{
     68,  88,  66,  67, 147,  63, 
     32, 250, 101, 173,  44, 229, 
    183, 152, 130, 193, 230,  44, 
     11, 185,   1,   0,   0,   0, 
    144,   3,   0,   0,   3,   0, 
      0,   0,  44,   0,   0,   0, 
     60,   0,   0,   0,  76,   0, 
      0,   0,  73,  83,  71,  78, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     79,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  83,  72, 
     69,  88,  60,   3,   0,   0, 
     80,   0,   5,   0, 207,   0, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  88,   8, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  68,  68, 
      0,   0, 156,  24,   0,   4, 
      0, 224,  17,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
     95,   0,   0,   2,  50,  16, 
      2,   0,  95,   0,   0,   2, 
     50,  32,   2,   0, 104,   0, 
      0,   2,   4,   0,   0,   0, 
    155,   0,   0,   4,  16,   0, 
      0,   0,  16,   0,   0,   0, 
      1,   0,   0,   0,  35,   0, 
    120,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  21, 
      2,   0,   2,  64,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,  16,   0,   0,   0, 
     16,   0,   0,   0,  70,  37, 
      2,   0,  80,   0,  24,   8, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 198,   0,  16,   0, 
      0,   0,   0,   0, 150, 133, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  60,   0, 
      8,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  31,   0,   4,   3, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     21,   0,   0,   1,  38,   0, 
      8,   8,   0, 208,   0,   0, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   6,   0,   0,   0, 
     85,   0,   8,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      2,   0,   0,   0,  35,   0, 
      8,  10,  18,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  45,   0,  16, 137, 
     66,   0,   0, 128,   3,  17, 
     17,   0,  34,   0,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   1,   0,   0,   0, 
     22, 126,  16,   0,   0,   0, 
      0,   0,  30,   0,   8,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   1,   0,   0,   0, 
     45,   0,   8, 137,  66,   0, 
      0, 128,   3,  17,  17,   0, 
     18,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      1,   0,  32,   7,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      1,   0,   0,   0,  42,   0, 
     80,  10, 162,   0,  16,   0, 
      2,   0,   0,   0,  86,   1, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0, 139,   0,  40,  15, 
     82,   0,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     86,   4,  16,   0,   1,   0, 
      0,   0,  55,   0,  56,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0, 150,   7, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  43,   0,  56,   5, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  14,   0, 
     56,  10, 114,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  69,   0,   0, 128,  69, 
      0,   0, 128,  69,   0,   0, 
      0,   0,  56,   0, 120,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 166,   5,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0, 188, 116, 179,  63, 
    163, 209,  54,  63, 162,  50, 
    176,  62, 229, 208, 226,  63, 
      0,   0,  16,   8,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,   0,  32,  16,   8, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,   0,  32, 
     40,   7,  82,   0,  16,   0, 
      3,   0,   0,   0,   6,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   3,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63, 164,   0, 
      0,   7, 242, 224,  17,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  62,   0,   0,   1
};
