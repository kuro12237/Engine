@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"


call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"


MSBuild "GameEngine\Engine.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Release;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../Generated\output\gameEngine\Release\ ^
 /m


IF EXIST "Generated\output\Release\Engine\Engine.lib" (
    mkdir "Externals\Engine\lib\Release" >nul 2>&1
    copy /Y "Generated\output\Release\Engine\Engine.lib" "Externals\Engine\lib\Release\"
) ELSE (
    echo Engine.lib not found. Build may have failed.
    pause
)

set "INCLUDE_DIR=Externals\Engine\include"
mkdir "%INCLUDE_DIR%" >nul 2>&1

robocopy "GameEngine" "Externals\Engine\include" *.h /S /XO

