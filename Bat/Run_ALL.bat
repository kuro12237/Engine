@echo off
setlocal

echo Run Start
echo directory: %cd%


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
