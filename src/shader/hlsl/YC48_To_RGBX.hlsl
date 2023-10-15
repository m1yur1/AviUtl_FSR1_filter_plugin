/*
fxc /T cs_5_0 /E YC48_to_RGBX_CompatibleConvert /O3 /Gis /Fh YC48_To_RGBX_Compatible.h /Qstrip_reflect YC48_To_RGBX.hlsl
fxc /T cs_5_0 /E YC48_to_RGBX_NoCompatibleConvert /O3 /Gis /Fh YC48_To_RGBX_NoCompatible.h /Qstrip_reflect YC48_To_RGBX.hlsl
*/

cbuffer kGlobal: register(b0)
{
	uint kUIntStride;
	uint2 kPictureSize;
};

Buffer<uint> Input: register(t0);
RWTexture2D<float4> Output: register(u0);

// (Y, Cb, Cr) to (R, G, B)
float3 Convert_YC48_to_RGB(in int3 yc48);
float3 Convert_YC48_to_RGB_NoCompatible(in int3 yc48);


[numthreads(16, 16, 1)]
void YC48_to_RGBX_CompatibleConvert(uint3 GroupID: SV_GroupID, uint2 GroupThreadID: SV_GroupThreadID)
{
	uint2 output_coord;
	uint input_idx;
	uint2 input_data;
	int3 input_color;

	output_coord.x = (16 * GroupID.x) + GroupThreadID.x;
	output_coord.y = (16 * GroupID.y) + GroupThreadID.y;

	if ((kPictureSize.x <= output_coord.x) || (kPictureSize.y <= output_coord.y))
		return;

	input_idx = (output_coord.y * kUIntStride) + ((output_coord.x * 6) / 4);
	input_data.x = Input[input_idx];
	input_data.y = Input[input_idx + 1];

	if (output_coord.x & 1)
	{
		input_color.r = asint(input_data.x) >> 16;
		input_color.g = asint(input_data.y << 16) >> 16;
		input_color.b = asint(input_data.y) >> 16;
	}
	else
	{
		input_color.r = asint(input_data.x << 16) >> 16;
		input_color.g = asint(input_data.x) >> 16;
		input_color.b = asint(input_data.y << 16) >> 16;
	}

	Output[output_coord] = float4(Convert_YC48_to_RGB(input_color), 1.f);
}

[numthreads(16, 16, 1)]
void YC48_to_RGBX_NoCompatibleConvert(uint3 GroupID: SV_GroupID, uint2 GroupThreadID: SV_GroupThreadID)
{
	uint2 output_coord;
	uint input_idx;
	uint2 input_data;
	int3 input_color;

	output_coord.x = (16 * GroupID.x) + GroupThreadID.x;
	output_coord.y = (16 * GroupID.y) + GroupThreadID.y;

	if ((kPictureSize.x <= output_coord.x) || (kPictureSize.y <= output_coord.y))
		return;

	input_idx = (output_coord.y * kUIntStride) + ((output_coord.x * 6) / 4);
	input_data.x = Input[input_idx];
	input_data.y = Input[input_idx + 1];

	if (output_coord.x & 1)
	{
		input_color.r = asint(input_data.x) >> 16;
		input_color.g = asint(input_data.y << 16) >> 16;
		input_color.b = asint(input_data.y) >> 16;
	}
	else
	{
		input_color.r = asint(input_data.x << 16) >> 16;
		input_color.g = asint(input_data.x) >> 16;
		input_color.b = asint(input_data.y << 16) >> 16;
	}

	Output[output_coord] = float4(Convert_YC48_to_RGB_NoCompatible(input_color), 1.f);
}

float3 Convert_YC48_to_RGB(in int3 yc48)
{
	float3 result;

	result.r = float(( ((yc48.r*16320) >> 16) + 3                          + ((yc48.b* 22881) >> 16) ) >> 2) / 255.f;
	result.g = float(( ((yc48.r*16320) >> 16) + 3 + ((yc48.g*-5616) >> 16) + ((yc48.b*-11655) >> 16) ) >> 2) / 255.f;
	result.b = float(( ((yc48.r*16320) >> 16) + 3 + ((yc48.g*28919) >> 16)                           ) >> 2) / 255.f;

	return saturate(result);
}

float3 Convert_YC48_to_RGB_NoCompatible(in int3 yc48)
{
	float3 result;

	float y = float(yc48.r) / 4096;
	float cb = float(yc48.g) / 4096;
	float cr = float(yc48.b) / 4096;

	result.r = y + cr * 1.402;
	result.g = y - cr * (0.419198 / 0.587) - cb * (0.202008 / 0.587);
	result.b = y + cb * 1.772;

	return saturate(result);
}
