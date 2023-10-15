#pragma once

#include <Windows.h>
#include <tchar.h>

#include <algorithm>
#include <utility>

#ifndef FILTER_FLAG_ACTIVE
#include <filter.h>
#endif

#include "D3D11FSR1.h"

EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable();
EXTERN_C BOOL Filter_proc(FILTER *fp, FILTER_PROC_INFO *fpip);
EXTERN_C BOOL Filter_update(FILTER *fp, int status);
EXTERN_C BOOL Filter_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp);
