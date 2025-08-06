@echo off
setlocal

rem 
for %%f in (*.bat) do (
    if /I not "%%~nxf"=="%~nx0" (
        echo Run: %%f
        call "%%f"
    )
)

endlocal
echo Run_Complite
pause
