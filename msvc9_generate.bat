
@if not exist "..\Freya_MSVC9" goto error_not_found

@if exist "%ProgramFiles%\Microsoft Visual Studio 9.0\VC\VCVARSALL.BAT" call "%ProgramFiles%\Microsoft Visual Studio 9.0\VC\VCVARSALL.BAT"

@if exist "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\VCVARSALL.BAT" call "%ProgramFiles(x86)%\Microsoft Visual Studio 9.0\VC\VCVARSALL.BAT"

@set CURRENTDIR=%CD%

@set PATH=%CURRENTDIR%"\..\Freya_MSVC9\bin";%PATH%
@set INCLUDE=%CURRENTDIR%"\..\Freya_MSVC9\include";%INCLUDE%
@set LIB=%CURRENTDIR%"\..\Freya_MSVC9\lib";%LIB%
@set LIBPATH=%CURRENTDIR%"\..\Freya_MSVC9\lib";%LIBPATH%

@cd ".\Build"
@if not exist "MSVC9" mkdir MSVC9
@cd "MSVC9"
@call cmake.exe -G "Visual Studio 9 2008" ..\..

@cd ..
@if not exist "NMake" mkdir NMake
@cd "NMake"
@call cmake.exe -G "NMake Makefiles" ..\..

@cd ..
@cd ..
@goto :end
:error_not_found
echo "Freya_MSVC9 directory is not found"
:end
