#include "DllEntry.h"

D3D11FSR1 fsr1;

EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable()
{
	static const TCHAR *track_names[] = {TEXT("W"), TEXT("H"), TEXT("#")};
	static int track_defaults[] = {1920, 1080, 80};
	static int track_mins[] = {32, 32, 0};
	static int track_maxs[] = {1920, 1088, 100};

	static const TCHAR *check_names[] = {TEXT("Compatible Convert")};
	static int check_defaults[] = {1};

	static FILTER_DLL filter_table =
	{
		FILTER_FLAG_EX_INFORMATION,
		0, 0,
		const_cast<TCHAR *>(TEXT("AMD FSR 1.0 like filter")),

		3,
		const_cast<TCHAR **>(track_names),
		track_defaults,
		track_mins,
		track_maxs,

		1,
		const_cast<TCHAR **>(check_names),
		check_defaults,

		Filter_proc,
		nullptr,
		nullptr,
		Filter_update,
		Filter_WndProc,

		nullptr,
		nullptr,
		nullptr, 0,

		const_cast<TCHAR *>(TEXT("version 0 by miyuri")),
	};

	return &filter_table;
}

EXTERN_C BOOL Filter_proc(FILTER *fp, FILTER_PROC_INFO *fpip)
{
	if (!fsr1.IsAllocatedResources())
		return FALSE;

	UINT output_width = fp->track[0];
	UINT output_height = fp->track[1];
	UINT input_width = fpip->w;
	UINT input_height = fpip->h;
	UINT stride = fpip->line_size;
	float sharpness = fp->track[2] / 100.f;
	HRESULT result = fsr1.ApplyFilter(
		fpip->ycp_temp,
		output_width,
		output_height,
		stride,
		sharpness,
		fpip->ycp_edit,
		input_width,
		input_height,
		stride);

	if (SUCCEEDED(result))
	{
		std::swap(fpip->ycp_temp, fpip->ycp_edit);
		fpip->w = output_width;
		fpip->h = output_height;
	}

	return TRUE;
}

EXTERN_C BOOL Filter_update(FILTER *fp, int status)
{
	if (!fsr1.IsAllocatedResources())
		return TRUE;

	bool compatible_convert = fp->check[0];
	bool use_float_fomat = !compatible_convert;

	if (fsr1.UseFloatFormat() != use_float_fomat)
	{
		UINT width = fp->track_e[0];
		UINT height = fp->track_e[1];

		fsr1.ReleaseResources();

		if (FAILED(fsr1.AllocateResources(nullptr, width, height, use_float_fomat)))
			MessageBox(fp->hwnd, TEXT("Filter_update:\nAllocateResources"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
	}

	return TRUE;
}

EXTERN_C BOOL Filter_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp)
{
	SYS_INFO sys_info;

	switch (message)
	{
	case WM_FILTER_INIT:
		if (fp->exfunc->get_sys_info(editp, &sys_info))
		{
			fp->track_s[0] = sys_info.min_w;
			fp->track_e[0] = sys_info.max_w;
			fp->track_s[1] = sys_info.min_h;
			fp->track_e[1] = sys_info.max_h;

			fp->track[0] = std::clamp(fp->track[0], sys_info.min_w, sys_info.max_w);
			fp->track[1] = std::clamp(fp->track[1], sys_info.min_h, sys_info.max_h);

			fp->exfunc->filter_window_update(fp);
		}
		else
			MessageBox(hwnd, TEXT("WM_FILTER_INIT:\nget_sys_info"), TEXT("ERROR"), MB_OK | MB_ICONERROR);

		return TRUE;

	case WM_FILTER_EXIT:
		fsr1.ReleaseResources();

		break;

	case WM_FILTER_CHANGE_ACTIVE:
		if (fp->exfunc->is_filter_active(fp))
		{
			UINT max_width = fp->track_e[0];
			UINT max_height = fp->track_e[1];
			bool compatible_convert = fp->check[0];
			bool use_float_fomat = !compatible_convert;
			HRESULT result = fsr1.AllocateResources(nullptr, max_width, max_height, use_float_fomat);

			if (FAILED(result))
				MessageBox(hwnd, TEXT("WM_FILTER_CHANGE_ACTIVE:\nAllocateResources"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		}
		else
			fsr1.ReleaseResources();

		return TRUE;
	}

	return FALSE;
}
