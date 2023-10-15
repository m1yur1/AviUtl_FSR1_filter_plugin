#include "D3D11FSR1.h"

D3D11FSR1::D3D11FSR1():
	resource_allocated_(false),
	float_format_(false),
	texture_width_(0),
	texture_height_(0)
{
}

D3D11FSR1::~D3D11FSR1()
{
	ReleaseResources();
}

bool D3D11FSR1::IsAllocatedResources()
{
	return resource_allocated_;
}

bool D3D11FSR1::UseFloatFormat()
{
	return float_format_;
}

HRESULT D3D11FSR1::AllocateResources
(
	IDXGIAdapter *adapter,
	UINT width,
	UINT height,
	bool use_float_fomat
)
{
	UINT buffer_stride = CalculateStride(width);
	UINT buffer_uints_stride = buffer_stride / sizeof (uint32_t);
	DXGI_FORMAT texture_format;

	texture_format = use_float_fomat? DXGI_FORMAT_R32G32B32A32_FLOAT: DXGI_FORMAT_R10G10B10A2_UNORM;

	// create device and device_context
	wil::com_ptr<ID3D11Device> device;
	wil::com_ptr<ID3D11DeviceContext> device_context;
	{
		D3D_DRIVER_TYPE driver_type = adapter? D3D_DRIVER_TYPE_UNKNOWN: D3D_DRIVER_TYPE_HARDWARE;
		UINT create_device_flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
		std::array<D3D_FEATURE_LEVEL, 1> feature_levels = {D3D_FEATURE_LEVEL_11_0};

		RETURN_IF_FAILED(D3D11CreateDevice(adapter, driver_type, nullptr, create_device_flags, feature_levels.data(), feature_levels.size(), D3D11_SDK_VERSION, &device, nullptr, &device_context));
	}

	// create buffers
	wil::com_ptr<ID3D11Buffer> dynamic_buffer;
	wil::com_ptr<ID3D11Buffer> default_buffer;
	wil::com_ptr<ID3D11Buffer> staging_buffer;
	wil::com_ptr<ID3D11Buffer> constant_buffer;
	{
		D3D11_BUFFER_DESC desc {};

		desc.ByteWidth = buffer_stride * height;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		RETURN_IF_FAILED(device->CreateBuffer(&desc, nullptr, &dynamic_buffer));

		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
		desc.CPUAccessFlags = 0;
		RETURN_IF_FAILED(device->CreateBuffer(&desc, nullptr, &default_buffer));

		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		RETURN_IF_FAILED(device->CreateBuffer(&desc, nullptr, &staging_buffer));

		desc.ByteWidth = kConstantBufferSize;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		RETURN_IF_FAILED(device->CreateBuffer(&desc, nullptr, &constant_buffer));
	}

	// create textures
	wil::com_ptr<ID3D11Texture2D> texture_0;
	wil::com_ptr<ID3D11Texture2D> texture_1;
	{
		D3D11_TEXTURE2D_DESC desc {};

		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = texture_format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		RETURN_IF_FAILED(device->CreateTexture2D(&desc, nullptr, &texture_0));
		RETURN_IF_FAILED(device->CreateTexture2D(&desc, nullptr, &texture_1));
	}

	// create shaders
	wil::com_ptr<ID3D11ComputeShader> yc48_to_rgbx_shader;
	wil::com_ptr<ID3D11ComputeShader> easu_shader;
	wil::com_ptr<ID3D11ComputeShader> rcas_shader;
	wil::com_ptr<ID3D11ComputeShader> rgbx_to_yc48_shader;
	{
		if (use_float_fomat)
		{
			RETURN_IF_FAILED(device->CreateComputeShader(g_YC48_to_RGBX_NoCompatibleConvert, sizeof (g_YC48_to_RGBX_NoCompatibleConvert), nullptr, &yc48_to_rgbx_shader));
			RETURN_IF_FAILED(device->CreateComputeShader(g_RGBX_to_YC48_NoCompatibleConvert, sizeof (g_RGBX_to_YC48_NoCompatibleConvert), nullptr, &rgbx_to_yc48_shader));
		}
		else
		{
			RETURN_IF_FAILED(device->CreateComputeShader(g_YC48_to_RGBX_CompatibleConvert, sizeof (g_YC48_to_RGBX_CompatibleConvert), nullptr, &yc48_to_rgbx_shader));
			RETURN_IF_FAILED(device->CreateComputeShader(g_RGBX_to_YC48_CompatibleConvert, sizeof (g_RGBX_to_YC48_CompatibleConvert), nullptr, &rgbx_to_yc48_shader));
		}

		RETURN_IF_FAILED(device->CreateComputeShader(g_FSR1_EASU, sizeof (g_FSR1_EASU), nullptr, &easu_shader));
		RETURN_IF_FAILED(device->CreateComputeShader(g_FSR1_RCAS, sizeof (g_FSR1_RCAS), nullptr, &rcas_shader));
	}

	// sampler
	wil::com_ptr<ID3D11SamplerState> liner_clamp_sampler;
	{
		D3D11_SAMPLER_DESC desc {};

		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.MipLODBias = 0.f;
		desc.MaxAnisotropy = 1;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.BorderColor[0] = 0.f;
		desc.BorderColor[1] = 0.f;
		desc.BorderColor[2] = 0.f;
		desc.BorderColor[3] = 0.f;
		desc.MinLOD = 0.f;
		desc.MaxLOD = 0.f;
		RETURN_IF_FAILED(device->CreateSamplerState(&desc, &liner_clamp_sampler));
	}

	// create srvs
	wil::com_ptr<ID3D11ShaderResourceView> dynamic_buffer_srv;
	wil::com_ptr<ID3D11ShaderResourceView> texture_0_srv;
	wil::com_ptr<ID3D11ShaderResourceView> texture_1_srv;
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc {};

		desc.Format = DXGI_FORMAT_R32_UINT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		desc.Buffer.FirstElement = 0;
		desc.Buffer.NumElements = buffer_uints_stride * height;
		RETURN_IF_FAILED(device->CreateShaderResourceView(dynamic_buffer.get(), &desc, &dynamic_buffer_srv));

		desc.Format = texture_format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MostDetailedMip = 0;
		desc.Texture2D.MipLevels = 1;
		RETURN_IF_FAILED(device->CreateShaderResourceView(texture_0.get(), &desc, &texture_0_srv));
		RETURN_IF_FAILED(device->CreateShaderResourceView(texture_1.get(), &desc, &texture_1_srv));
	}

	// create uavs
	wil::com_ptr<ID3D11UnorderedAccessView> texture_0_uav;
	wil::com_ptr<ID3D11UnorderedAccessView> texture_1_uav;
	wil::com_ptr<ID3D11UnorderedAccessView> default_buffer_uav;
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC desc {};

		desc.Format = texture_format;
		desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;
		RETURN_IF_FAILED(device->CreateUnorderedAccessView(texture_0.get(), &desc, &texture_0_uav));
		RETURN_IF_FAILED(device->CreateUnorderedAccessView(texture_1.get(), &desc, &texture_1_uav));

		desc.Format = DXGI_FORMAT_R32_UINT;
		desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		desc.Buffer.FirstElement = 0;
		desc.Buffer.NumElements = buffer_uints_stride * height;
		desc.Buffer.Flags = 0;
		RETURN_IF_FAILED(device->CreateUnorderedAccessView(default_buffer.get(), &desc, &default_buffer_uav));
	}

	device_ = device;
	device_context_ = device_context;

	dynamic_buffer_ = dynamic_buffer;
	default_buffer_ = default_buffer;
	staging_buffer_ = staging_buffer;
	constant_buffer_ = constant_buffer;

	texture_0_ = texture_0;
	texture_1_ = texture_1;

	yc48_to_rgbx_shader_ = yc48_to_rgbx_shader;
	rgbx_to_yc48_shader_ = rgbx_to_yc48_shader;
	easu_shader_ = easu_shader;
	rcas_shader_ = rcas_shader;

	liner_clamp_sampler_ = liner_clamp_sampler;

	dynamic_buffer_srv_ = dynamic_buffer_srv;
	texture_0_srv_ = texture_0_srv;
	texture_1_srv_ = texture_1_srv;

	texture_0_uav_ = texture_0_uav;
	texture_1_uav_ = texture_1_uav;
	default_buffer_uav_ = default_buffer_uav;

	texture_width_ = width;
	texture_height_ = height;

	resource_allocated_ = true;
	float_format_ = use_float_fomat;

	return NOERROR;
}

void D3D11FSR1::ReleaseResources()
{
	if (!resource_allocated_)
		return;

	resource_allocated_ = false;

	device_.reset();
	device_context_.reset();

	dynamic_buffer_.reset();
	default_buffer_.reset();
	staging_buffer_.reset();
	constant_buffer_.reset();

	texture_0_.reset();
	texture_1_.reset();

	yc48_to_rgbx_shader_.reset();
	easu_shader_.reset();
	rcas_shader_.reset();
	rgbx_to_yc48_shader_.reset();

	liner_clamp_sampler_.reset();

	dynamic_buffer_srv_.reset();
	texture_0_srv_.reset();
	texture_1_srv_.reset();

	texture_0_uav_.reset();
	texture_1_uav_.reset();
	default_buffer_uav_.reset();
}

HRESULT D3D11FSR1::ApplyFilter
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
)
{
	if (!resource_allocated_)
		return E_FAIL;

	if (!output_data || !input_data)
		return E_POINTER;

	if (texture_width_ < output_width || texture_width_ < input_width)
		return E_INVALIDARG;

	if (texture_height_ < output_height || texture_height_ < input_height)
		return E_INVALIDARG;

	if (sizeof (PIXEL_YC) * output_width > output_stride)
		return E_INVALIDARG;

	if (sizeof (PIXEL_YC) * input_width > input_stride)
		return E_INVALIDARG;

	float rcas_demand_sharpness = std::clamp(2.f - (sharpness * 2.f), 0.f, 2.f);

	RETURN_IF_FAILED(CopyInputDataToDynamicBuffer(input_data, input_width, input_height, input_stride));
	RETURN_IF_FAILED(ConvertYC48ToRGBX(input_width, input_height));
	RETURN_IF_FAILED(EASU(output_width, output_height, input_width, input_height));
	RETURN_IF_FAILED(RCAS(output_width, output_height, rcas_demand_sharpness));
	RETURN_IF_FAILED(ConvertRGBXToYC48(output_width, output_height));
	device_context_->CopyResource(staging_buffer_.get(), default_buffer_.get());
	RETURN_IF_FAILED(CopyStagingBufferToOutputData(output_data, output_width, output_height, output_stride));

	return NOERROR;
}

HRESULT D3D11FSR1::CopyInputDataToDynamicBuffer
(
	const PIXEL_YC *input_data,
	UINT input_width,
	UINT input_height,
	UINT input_stride
)
{
	D3D11_MAPPED_SUBRESOURCE mapped {};

	RETURN_IF_FAILED(device_context_->Map(dynamic_buffer_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
	
	uint8_t *dst = reinterpret_cast<uint8_t *>(mapped.pData);
	const uint8_t *src = reinterpret_cast<const uint8_t *>(input_data);
	UINT stride = CalculateStride(input_width);

	while (input_height--)
	{
		CopyMemory(dst, src, sizeof (PIXEL_YC) * input_width);
		dst += stride;
		src += input_stride;
	}
	
	device_context_->Unmap(dynamic_buffer_.get(), 0);

	return NOERROR;
}

HRESULT D3D11FSR1::ConvertYC48ToRGBX(UINT width, UINT height)
{
	static const UINT kGroupWidth = 16;
	static const UINT kGroupHeight = 16;
	UINT dispatch_x = (width + (kGroupWidth-1)) / kGroupWidth;
	UINT dispatch_y = (height + (kGroupHeight-1)) / kGroupHeight;

	// write arguments
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		UINT uints_stride = CalculateStride(width) / sizeof (uint32_t);
		std::array<UINT, 3> args {uints_stride, width, height};

		RETURN_IF_FAILED(device_context_->Map(constant_buffer_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
		CopyMemory(mapped.pData, args.data(), sizeof (args));
		device_context_->Unmap(constant_buffer_.get(), 0);
	}

	// dispatch shader
	{
		std::array<ID3D11Buffer *, 1> cbvs {constant_buffer_.get()};
		std::array<ID3D11ShaderResourceView *, 1> srvs {dynamic_buffer_srv_.get()};
		std::array<ID3D11UnorderedAccessView *, 1> uavs {texture_0_uav_.get()};

		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(yc48_to_rgbx_shader_.get(), nullptr, 0);

		device_context_->Dispatch(dispatch_x, dispatch_y, 1);

		cbvs.at(0) = nullptr;
		srvs.at(0) = nullptr;
		uavs.at(0) = nullptr;
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(nullptr, nullptr, 0);
	}

	return NOERROR;
}

HRESULT D3D11FSR1::EASU
(
	UINT output_width,
	UINT output_height,
	UINT input_width,
	UINT input_height
)
{
	static const UINT kGroupWidth = 16;
	static const UINT kGroupHeight = 16;
	UINT dispatch_x = (output_width + (kGroupWidth-1)) / kGroupWidth;
	UINT dispatch_y = (output_height + (kGroupHeight-1)) / kGroupHeight;

	// write arguments
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		std::array<AU1, 16> args;

		FsrEasuCon(&args.at(0), &args.at(4), &args.at(8), &args.at(12),
			static_cast<AF1>(input_width), static_cast<AF1>(input_height),
			static_cast<AF1>(texture_width_), static_cast<AF1>(texture_height_),
			static_cast<AF1>(output_width), static_cast<AF1>(output_height));
		RETURN_IF_FAILED(device_context_->Map(constant_buffer_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
		CopyMemory(mapped.pData, args.data(), sizeof (args));
		device_context_->Unmap(constant_buffer_.get(), 0);
	}

	// dispatch shader
	{
		std::array<ID3D11SamplerState *, 1> samplers {liner_clamp_sampler_.get()};
		std::array<ID3D11Buffer *, 1> cbvs {constant_buffer_.get()};
		std::array<ID3D11ShaderResourceView *, 1> srvs {texture_0_srv_.get()};
		std::array<ID3D11UnorderedAccessView *, 1> uavs {texture_1_uav_.get()};

		device_context_->CSSetSamplers(0, 1, samplers.data());
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(easu_shader_.get(), nullptr, 0);

		device_context_->Dispatch(dispatch_x, dispatch_y, 1);

		samplers.at(0) = nullptr;
		cbvs.at(0) = nullptr;
		srvs.at(0) = nullptr;
		uavs.at(0) = nullptr;
		device_context_->CSSetSamplers(0, 1, samplers.data());
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(nullptr, nullptr, 0);
	}

	return NOERROR;
}

HRESULT D3D11FSR1::RCAS
(
	UINT width,
	UINT height,
	float sharpness
)
{
	static const UINT kGroupWidth = 16;
	static const UINT kGroupHeight = 16;
	UINT dispatch_x = (width + (kGroupWidth-1)) / kGroupWidth;
	UINT dispatch_y = (height + (kGroupHeight-1)) / kGroupHeight;

	// write arguments
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		std::array<AU1, 4> args;

		FsrRcasCon(args.data(), sharpness);
		RETURN_IF_FAILED(device_context_->Map(constant_buffer_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
		CopyMemory(mapped.pData, args.data(), sizeof (args));
		device_context_->Unmap(constant_buffer_.get(), 0);
	}

	// dispatch shader
	{
		std::array<ID3D11SamplerState *, 1> samplers {liner_clamp_sampler_.get()};
		std::array<ID3D11Buffer *, 1> cbvs {constant_buffer_.get()};
		std::array<ID3D11ShaderResourceView *, 1> srvs {texture_1_srv_.get()};
		std::array<ID3D11UnorderedAccessView *, 1> uavs {texture_0_uav_.get()};

		device_context_->CSSetSamplers(0, 1, samplers.data());
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(rcas_shader_.get(), nullptr, 0);

		device_context_->Dispatch(dispatch_x, dispatch_y, 1);

		samplers.at(0) = nullptr;
		cbvs.at(0) = nullptr;
		srvs.at(0) = nullptr;
		uavs.at(0) = nullptr;
		device_context_->CSSetSamplers(0, 1, samplers.data());
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(nullptr, nullptr, 0);
	}

	return NOERROR;
}

HRESULT D3D11FSR1::ConvertRGBXToYC48
(
	UINT width,
	UINT height
)
{
	static const UINT kGroupWidth = 256;
	UINT dispatch_x;
	UINT dispatch_y;

	// write arguments
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		std::array<AU1, 3> args;
		UINT bytes_stride = CalculateStride(width);
		UINT uints_stride = bytes_stride / sizeof (uint32_t);
		UINT uints = uints_stride * height;
		UINT groups = (uints + (kGroupWidth-1)) / kGroupWidth;

		if (D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION >= groups)
		{
			dispatch_x = groups;
			dispatch_y = 1;
		}
		else
		{
			dispatch_x = static_cast<UINT>(std::ceil(std::sqrt(groups)));
			if (groups <= dispatch_x * (dispatch_x-1))
				dispatch_y = dispatch_x - 1;
			else
				dispatch_y = dispatch_x;
		}

		args.at(0) = dispatch_x;
		args.at(1) = uints_stride;
		args.at(2) = uints;
		RETURN_IF_FAILED(device_context_->Map(constant_buffer_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
		CopyMemory(mapped.pData, args.data(), sizeof (args));
		device_context_->Unmap(constant_buffer_.get(), 0);
	}

	// dispatch shader
	{
		std::array<ID3D11Buffer *, 1> cbvs {constant_buffer_.get()};
		std::array<ID3D11ShaderResourceView *, 1> srvs {texture_0_srv_.get()};
		std::array<ID3D11UnorderedAccessView *, 1> uavs {default_buffer_uav_.get()};

		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(rgbx_to_yc48_shader_.get(), nullptr, 0);

		device_context_->Dispatch(dispatch_x, dispatch_y, 1);

		cbvs.at(0) = nullptr;
		srvs.at(0) = nullptr;
		uavs.at(0) = nullptr;
		device_context_->CSSetConstantBuffers(0, 1, cbvs.data());
		device_context_->CSSetShaderResources(0, 1, srvs.data());
		device_context_->CSSetUnorderedAccessViews(0, 1, uavs.data(), nullptr);
		device_context_->CSSetShader(nullptr, nullptr, 0);
	}

	return NOERROR;
}

HRESULT D3D11FSR1::CopyStagingBufferToOutputData
(
	PIXEL_YC *output_data,
	UINT output_width,
	UINT output_height,
	UINT output_stride
)
{
	D3D11_MAPPED_SUBRESOURCE mapped;

	RETURN_IF_FAILED(device_context_->Map(staging_buffer_.get(), 0, D3D11_MAP_READ, 0, &mapped));

	uint8_t *dst = reinterpret_cast<uint8_t *>(output_data);
	const uint8_t *src = reinterpret_cast<uint8_t *>(mapped.pData);
	UINT horizontal_bytes = sizeof (PIXEL_YC) * output_width;
	UINT buffer_stride = CalculateStride(output_width);

	while (output_height--)
	{
		CopyMemory(dst, src, horizontal_bytes);
		dst += output_stride;
		src += buffer_stride;
	}

	device_context_->Unmap(staging_buffer_.get(), 0);

	return NOERROR;
}

UINT D3D11FSR1::CalculateStride(UINT width)
{
	UINT horizontal_bytes = sizeof (PIXEL_YC) * width;

	if (horizontal_bytes % sizeof (uint32_t))
		return horizontal_bytes + (sizeof (uint32_t) - (horizontal_bytes % sizeof (uint32_t)));
	else
		return horizontal_bytes;
}
