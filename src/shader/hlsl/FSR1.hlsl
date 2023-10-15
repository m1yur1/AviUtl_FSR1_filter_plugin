/*
fxc /T cs_5_0 /E FSR1_EASU /O3 /Gis /Fh FSR1_EASU.h /Qstrip_reflect FSR1.hlsl
fxc /T cs_5_0 /E FSR1_RCAS /O3 /Gis /Fh FSR1_RCAS.h /Qstrip_reflect FSR1.hlsl
*/

SamplerState liner_clamp_sampler: register(s0);
cbuffer kGlobal: register(b0)
{
	uint4 Const0;
	uint4 Const1;
	uint4 Const2;
	uint4 Const3;
};
Texture2D Input: register(t0);
RWTexture2D<float4> Output: register(u0);


#define A_GPU 1
#define A_HLSL 1

#include "ffx_a.h"

#define FSR_EASU_F

AF4 FsrEasuRF(AF2 coord)
{
	return Input.GatherRed(liner_clamp_sampler, coord, int2(0, 0));
}

AF4 FsrEasuGF(AF2 coord)
{
	return Input.GatherGreen(liner_clamp_sampler, coord, int2(0, 0));

}

AF4 FsrEasuBF(AF2 coord)
{
	return Input.GatherBlue(liner_clamp_sampler, coord, int2(0, 0));
}


#define FSR_RCAS_F

AF4 FsrRcasLoadF(ASU2 coord)
{
	return Input.Load(int3(ASU2(coord), 0));
}

void FsrRcasInputF(inout AF1 r, inout AF1 g, inout AF1 b)
{
}


#include "ffx_fsr1.h"

void EASU_Filter(int2 coord)
{
	AF3 color;

	FsrEasuF(color, coord, Const0, Const1, Const2, Const3);
	Output[coord] = float4(color, 1);
}

void RCAS_Filter(int2 coord)
{
	AF1 r, g, b;

	FsrRcasF(r, g, b, coord, Const0);
	Output[coord] = float4(r, g, b, 1);
}

[numthreads(64, 1, 1)]
void FSR1_EASU(uint3 GroupThreadID: SV_GroupThreadID, uint3 GroupID: SV_GroupID)
{
	AU2 coord = ARmp8x8(GroupThreadID.x) + AU2(GroupID.x << 4u, GroupID.y << 4u);

	EASU_Filter(coord);

	coord.x += 8u;
	EASU_Filter(coord);

	coord.y += 8u;
	EASU_Filter(coord);

	coord.x -= 8u;
	EASU_Filter(coord);
}

[numthreads(64, 1, 1)]
void FSR1_RCAS(uint3 GroupThreadID: SV_GroupThreadID, uint3 GroupID: SV_GroupID)
{
	AU2 coord = ARmp8x8(GroupThreadID.x) + AU2(GroupID.x << 4u, GroupID.y << 4u);

	RCAS_Filter(coord);

	coord.x += 8u;
	RCAS_Filter(coord);

	coord.y += 8u;
	RCAS_Filter(coord);

	coord.x -= 8u;
	RCAS_Filter(coord);
}
