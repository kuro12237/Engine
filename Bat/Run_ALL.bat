@echo off
setlocal

echo Run Start
cd /d %~dp0
set "CURDIR=%cd%"

rem カレントディレクトリの .bat ファイルをループ
for %%f in ("%CURDIR%\*.bat") do (
    if /I not "%%~nxf"=="%~nx0" (
        echo Run: %%~nxf
        rem 新しいウィンドウで実行して、終わったら次へ
        start /wait "Running %%~nxf" cmd /c call "%%f"
        
        echo Complete: %%~nxf
    )
)

endlocal
echo Run_Complete
pause
