#pragma once

#include <Windows.h>
#include <tchar.h>
#include <dxgi.h>
#include <d3d11.h>

#include <algorithm>
#include <array>
#include <cmath>

#include <wil/com.h>

#ifndef FILTER_FLAG_ACTIVE
#include <filter.h>
#endif

#define A_CPU
#include <ffx_a.h>
#include <ffx_fsr1.h>

#include "shader/YC48_To_RGBX_Compatible.h"
#include "shader/YC48_To_RGBX_NoCompatible.h"
#include "shader/FSR1_EASU.h"
#include "shader/FSR1_RCAS.h"
#include "shader/RGBX_to_YC48_Compatible.h"
#include "shader/RGBX_to_YC48_NoCompatible.h"

class D3D11FSR1
{
private:
	static const UINT kConstantBufferSize = 16 * 4;

	bool resource_allocated_;
	bool float_format_;
	UINT texture_width_;
	UINT texture_height_;

	wil::com_ptr<ID3D11Device> device_;
	wil::com_ptr<ID3D11DeviceContext> device_context_;

	wil::com_ptr<ID3D11Buffer> dynamic_buffer_;
	wil::com_ptr<ID3D11Buffer> default_buffer_;
	wil::com_ptr<ID3D11Buffer> staging_buffer_;
	wil::com_ptr<ID3D11Buffer> constant_buffer_;

	wil::com_ptr<ID3D11Texture2D> texture_0_;
	wil::com_ptr<ID3D11Texture2D> texture_1_;

	wil::com_ptr<ID3D11ComputeShader> yc48_to_rgbx_shader_;
	wil::com_ptr<ID3D11ComputeShader> easu_shader_;
	wil::com_ptr<ID3D11ComputeShader> rcas_shader_;
	wil::com_ptr<ID3D11ComputeShader> rgbx_to_yc48_shader_;

	wil::com_ptr<ID3D11SamplerState> liner_clamp_sampler_;

	wil::com_ptr<ID3D11ShaderResourceView> dynamic_buffer_srv_;
	wil::com_ptr<ID3D11ShaderResourceView> texture_0_srv_;
	wil::com_ptr<ID3D11ShaderResourceView> texture_1_srv_;

	wil::com_ptr<ID3D11UnorderedAccessView> texture_0_uav_;
	wil::com_ptr<ID3D11UnorderedAccessView> texture_1_uav_;
	wil::com_ptr<ID3D11UnorderedAccessView> default_buffer_uav_;

public:
	D3D11FSR1();
	~D3D11FSR1();

	bool IsAllocatedResources();
	bool UseFloatFormat();

	HRESULT AllocateResources
	(
		IDXGIAdapter *adapter,
		UINT width,
		UINT height,
		bool use_float_fomat
	);
	void ReleaseResources();
	HRESULT ApplyFilter
	(
		PIXEL_YC *output_data,
		UINT output_width,
		UINT output_height,
		UINT output_stride,
		float sharpness,
		const PIXEL_YC *input_data,
		UINT input_width,
		UINT input_height,
		UINT input_stride
	);

private:
	HRESULT CopyInputDataToDynamicBuffer
	(
		const PIXEL_YC *input_data,
		UINT input_width,
		UINT input_height,
		UINT input_stride
	);
	HRESULT ConvertYC48ToRGBX(UINT width, UINT height);
	HRESULT EASU
	(
		UINT output_width,
		UINT output_height,
		UINT input_width,
		UINT input_height
	);
	HRESULT RCAS
	(
		UINT width,
		UINT height,
		float sharpness
	);
	HRESULT ConvertRGBXToYC48
	(
		UINT width,
		UINT height
	);
	HRESULT CopyStagingBufferToOutputData
	(
		PIXEL_YC *output_data,
		UINT output_width,
		UINT output_height,
		UINT output_stride
	);
	UINT CalculateStride(UINT width);
};
