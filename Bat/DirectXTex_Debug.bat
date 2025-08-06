@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "DirectXTex\DirectXTex\DirectXTex_Desktop_2022_Win10.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Debug;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../../Generated\output\DirectXTex\Debug\ ^
 /m


IF EXIST "Generated\output\DirectXTex\Debug\DirectXTex.lib" (
    mkdir "Externals\DirectXTex\lib\Debug" >nul 2>&1
    copy /Y "generated\output\DirectXTex\Debug\DirectXTex.lib" "Externals\DirectXTex\lib\Debug\"
) ELSE (
    echo DirectXTex.lib not found. Build may have failed.
    pause
)

set "INCLUDE_DIR=Externals\DirectXTex\include"
mkdir "%INCLUDE_DIR%" >nul 2>&1

for /R "DirectXTex\" %%f in (*.h) do (
    copy /Y "%%f" "%INCLUDE_DIR%\"
)
