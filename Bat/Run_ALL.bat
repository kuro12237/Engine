@echo off
setlocal

echo Run Start
echo directory: %cd%

rem バッチ自身のあるディレクトリに移動
cd /d %~dp0
set "CURDIR=%cd%"

rem カレントディレクトリの .bat ファイルをループ
for %%f in ("%CURDIR%\*.bat") do (
    if /I not "%%~nxf"=="%~nx0" (
        echo Run: %%~nxf
        call "%%f"
    )
)

endlocal

echo Run_Complite
pause
