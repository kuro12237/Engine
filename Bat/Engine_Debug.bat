@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "GameEngine\Engine.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Debug;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../Generated\output\gameEngine\Debug\ ^
 /m


IF EXIST "Generated\output\Engine\Debug\Engine.lib" (
    mkdir "Externals\Engine\lib\Debug" >nul 2>&1
    copy /Y "generated\output\Engine\Debug\Engine.lib" "Externals\Engine\lib\Debug\"
) ELSE (
    echo Engine.lib not found. Build may have failed.
    pause
)

set "INCLUDE_DIR=Externals\Engine\include"
mkdir "%INCLUDE_DIR%" >nul 2>&1

for /R "GameEngine\" %%f in (*.h) do (
    copy /Y "%%f" "%INCLUDE_DIR%\"
)