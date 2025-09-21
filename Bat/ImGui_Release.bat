@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "ImGui\ImGui.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Release;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../Generated\output\Release\ImGui ^
 /m

IF EXIST "Generated\output\Release\ImGui\ImGui.lib" (
    mkdir "Externals\ImGui\lib\Release" >nul 2>&1
    copy /Y "generated\output\Release\ImGui\ImGui.lib" "Externals\ImGui\lib\Release\"
) ELSE (
    echo ImGui.lib not found. Build may have failed.
    pause
)

set "INCLUDE_DIR=Externals\ImGui\include"
mkdir "%INCLUDE_DIR%" >nul 2>&1

for /R "ImGui\" %%f in (*.h) do (
    copy /Y "%%f" "%INCLUDE_DIR%\"
)
