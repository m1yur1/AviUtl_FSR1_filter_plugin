fxc.exe /nologo /T cs_5_0 /E YC48_to_RGBX_CompatibleConvert /O3 /Gis /Fh ..\YC48_To_RGBX_Compatible.h /Qstrip_reflect YC48_To_RGBX.hlsl
fxc.exe /nologo /T cs_5_0 /E YC48_to_RGBX_NoCompatibleConvert /O3 /Gis /Fh ..\YC48_To_RGBX_NoCompatible.h /Qstrip_reflect YC48_To_RGBX.hlsl
fxc.exe /nologo /T cs_5_0 /E FSR1_EASU /O3 /Gis /Fh ..\FSR1_EASU.h /Qstrip_reflect FSR1.hlsl
fxc.exe /nologo /T cs_5_0 /E FSR1_RCAS /O3 /Gis /Fh ..\FSR1_RCAS.h /Qstrip_reflect FSR1.hlsl
fxc.exe /nologo /T cs_5_0 /E RGBX_to_YC48_CompatibleConvert /O3 /Gis /Fh ..\RGBX_to_YC48_Compatible.h /Qstrip_reflect RGBX_To_YC48.hlsl
fxc.exe /nologo /T cs_5_0 /E RGBX_to_YC48_NoCompatibleConvert /O3 /Gis /Fh ..\RGBX_to_YC48_NoCompatible.h /Qstrip_reflect RGBX_To_YC48.hlsl
