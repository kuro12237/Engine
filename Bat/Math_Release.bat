@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "Math\Math.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Release;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../Generated\output\Release\Math ^
 /m

IF EXIST "Generated\output\Release\Math\Math.lib" (
    mkdir "Externals\Math\lib\Release" >nul 2>&1
    copy /Y "generated\output\Release\Math\Math.lib" "Externals\Math\lib\Release\"
) ELSE (
    echo Math.lib not found. Build may have failed.
    pause
)

set "INCLUDE_DIR=Externals\Math\include"
mkdir "%INCLUDE_DIR%" >nul 2>&1

for /R "Math\" %%f in (*.h) do (
    copy /Y "%%f" "%INCLUDE_DIR%\"
)
