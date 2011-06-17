
@if not exist "..\..\..\Freya_MSVC10" goto error_not_found

@if exist "%ProgramFiles%\Microsoft Visual Studio 10.0\VC\VCVARSALL.BAT" call "%ProgramFiles%\Microsoft Visual Studio 10.0\VC\VCVARSALL.BAT"

@if exist "%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\VC\VCVARSALL.BAT" call "%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\VC\VCVARSALL.BAT"

@set CURRENTDIR=%CD%

@set PATH=%CURRENTDIR%"\..\..\..\Freya_MSVC10\bin";%PATH%
@set INCLUDE=%CURRENTDIR%"\..\..\..\Freya_MSVC10\include";%INCLUDE%
@set LIB=%CURRENTDIR%"\..\..\..\Freya_MSVC10\lib";%LIB%
@set LIBPATH=%CURRENTDIR%"\..\..\..\Freya_MSVC10\lib";%LIBPATH%

@if not exist Build mkdir Build
@cd ".\Build"

@if not exist "NMake" mkdir NMake
@cd "NMake"
@call cmake.exe -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..\.. 
@cd ..

@if not exist "MSVC10" mkdir MSVC10
@cd "MSVC10"
@call cmake.exe -G "Visual Studio 10" ..\.. 
@cd ..

@cd ..
@goto :end
:error_not_found
echo "Freya_MSVC10 directory is not found"
:end
