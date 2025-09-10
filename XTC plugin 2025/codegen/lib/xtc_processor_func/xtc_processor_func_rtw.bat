@echo off

set skipSetupArg=%2
if "%skipSetupArg%" NEQ "skip_setup_msvc" (
call "setup_msvc.bat"
)


call  "\\Martiniano-1\D$\Archivos de programa\MATLAB\R2021b\bin\win64\checkMATLABRootForDriveMap.exe" "\\Martiniano-1\D$\Archivos de programa\MATLAB\R2021b"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
cd .

chcp 1252

if "%1"=="" (nmake MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f xtc_processor_func_rtw.mk all) else (nmake MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f xtc_processor_func_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1