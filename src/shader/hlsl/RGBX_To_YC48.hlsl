/*
fxc /T cs_5_0 /E RGBX_to_YC48_CompatibleConvert /O3 /Gis /Fh RGBX_to_YC48_Compatible.h /Qstrip_reflect RGBX_To_YC48.hlsl
fxc /T cs_5_0 /E RGBX_to_YC48_NoCompatibleConvert /O3 /Gis /Fh RGBX_to_YC48_NoCompatible.h /Qstrip_reflect RGBX_To_YC48.hlsl
*/

#ifndef NUMTHREADS_X
#define NUMTHREADS_X 256
#endif

cbuffer kGlobal: register(b0)
{
	uint kGroupSize;
	uint kUIntStride;
	uint kWriteUInts;
};

Texture2D<float4> Input: register(t0);
RWBuffer<uint> Output: register(u0);

// (R, G, B) to (Y, Cb, Cr)
int3 Convert_RGB_to_YC48(in float3 rgb);
int3 Convert_RGB_to_YC48_NoCompatible(in float3 rgb);
uint CombineInteger(in int lower, in int higher);


[numthreads(NUMTHREADS_X, 1, 1)]
void RGBX_to_YC48_CompatibleConvert(uint3 GroupID: SV_GroupID, uint GroupIndex: SV_GroupIndex)
{
	uint global_liner_id = (NUMTHREADS_X * kGroupSize.x * GroupID.y) + (NUMTHREADS_X * GroupID.x) + GroupIndex;
	uint store_data;
	uint store_coord;
	uint2 load_coord;
	int3 yc48_0;
	int3 yc48_1;

	if (kWriteUInts <= global_liner_id)
		return;

	store_coord.x = global_liner_id % kUIntStride;
	load_coord.x = (store_coord.x / 3) * 2;
	load_coord.y = global_liner_id / kUIntStride;

	switch (store_coord.x % 3)
	{
	case 0:
		// Y, Cb
		yc48_0 = Convert_RGB_to_YC48(Input[load_coord].rgb);
		store_data = CombineInteger(yc48_0.r, yc48_0.g);
		break;

	case 1:
		// Cr, Y
		yc48_0 = Convert_RGB_to_YC48(Input[load_coord].rgb);
		yc48_1 = Convert_RGB_to_YC48(Input[load_coord + uint2(1, 0)].rgb);
		store_data = CombineInteger(yc48_0.b, yc48_1.r);
		break;

	//case 2:
	default:
		// Cb, Cr
		yc48_1 = Convert_RGB_to_YC48(Input[load_coord + uint2(1, 0)].rgb);
		store_data = CombineInteger(yc48_1.g, yc48_1.b);
		break;
	}

	Output[global_liner_id] = store_data;
}

[numthreads(NUMTHREADS_X, 1, 1)]
void RGBX_to_YC48_NoCompatibleConvert(uint3 GroupID: SV_GroupID, uint GroupIndex: SV_GroupIndex)
{
	uint global_liner_id = (NUMTHREADS_X * kGroupSize.x * GroupID.y) + (NUMTHREADS_X * GroupID.x) + GroupIndex;
	uint store_data;
	uint store_coord;
	uint2 load_coord;
	int3 yc48_0;
	int3 yc48_1;

	if (kWriteUInts <= global_liner_id)
		return;

	store_coord.x = global_liner_id % kUIntStride;
	load_coord.x = (store_coord.x / 3) * 2;
	load_coord.y = global_liner_id / kUIntStride;

	switch (store_coord.x % 3)
	{
	case 0:
		// Y, Cb
		yc48_0 = Convert_RGB_to_YC48_NoCompatible(Input[load_coord].rgb);
		store_data = CombineInteger(yc48_0.r, yc48_0.g);
		break;

	case 1:
		// Cr, Y
		yc48_0 = Convert_RGB_to_YC48_NoCompatible(Input[load_coord].rgb);
		yc48_1 = Convert_RGB_to_YC48_NoCompatible(Input[load_coord + uint2(1, 0)].rgb);
		store_data = CombineInteger(yc48_0.b, yc48_1.r);
		break;

	//case 2:
	default:
		// Cb, Cr
		yc48_1 = Convert_RGB_to_YC48_NoCompatible(Input[load_coord + uint2(1, 0)].rgb);
		store_data = CombineInteger(yc48_1.g, yc48_1.b);
		break;
	}

	Output[global_liner_id] = store_data;
}

int3 Convert_RGB_to_YC48(in float3 rgb)
{
	int y, cb, cr;
	int r = clamp(int(rgb.r * 255.0), 0, 255);
	int g = clamp(int(rgb.g * 255.0), 0, 255);
	int b = clamp(int(rgb.b * 255.0), 0, 255);

	y	= ((((b << 6) + 18) *  1875) >> 16)
		+ ((((g << 6) + 18) *  9655) >> 16)
		+ ((((r << 6) + 18) *  4918) >> 16)
		- 3;
	cb	= ((((b << 6) + 18) *  8224) >> 16)
		+ ((((g << 6) + 18) * -5449) >> 16)
		+ ((((r << 6) + 18) * -2775) >> 16)
		+ 1;
	cr	= ((((b << 6) + 18) * -1337) >> 16)
		+ ((((g << 6) + 18) * -6887) >> 16)
		+ ((((r << 6) + 18) *  8224) >> 16)
		+ 1;

	return int3(y, cb, cr);
}

int3 Convert_RGB_to_YC48_NoCompatible(in float3 rgb)
{
	int3 result;
	float y =  dot(rgb, float3(       0.299,           0.587,           0.114));
	float cb = dot(rgb, float3(-0.299/1.772,    -0.587/1.772,             0.5));
	float cr = dot(rgb, float3(         0.5,    -0.587/1.402,    -0.114/1.402));

	result.r = int(y * 4096);
	result.g = int(cb * 4096);
	result.b = int(cr * 4096);

	return result;
}

uint CombineInteger(in int lower, in int higher)
{
	return (lower & 0xffff)| (higher << 16);
}
