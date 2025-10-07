@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "DirectXTex\DirectXTex\DirectXTex_Desktop_2022_Win10.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Release;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../../generated\output\Release\DirectXTex\ ^
 /m


IF EXIST "generated\output\Release\DirectXTex\DirectXTex.lib" (
    mkdir "Externals\DirectXTex\lib\Release" >nul 2>&1
    copy /Y "generated\output\Release\DirectXTex\DirectXTex.lib" "Externals\DirectXTex\lib\Release\"
) ELSE (
    echo DirectXTex.lib not found. Build may have failed.
  
)