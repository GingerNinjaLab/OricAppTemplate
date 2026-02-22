@echo OFF
echo ==Building and Running the Oric Program==
TASKKILL /F /IM oricutron.exe

CALL ./osdk_config.bat
CALL ./osdk_build.bat

IF %ERRORLEVEL% NEQ 0  GOTO End

echo CALL %OSDK%\bin\tap2wav.exe -11 BUILD\%OSDKNAME%.tap BUILD\%OSDKNAME%.wav

DEL %OSDK%\Oricutron\breakpoints.txt

if "%1"=="debug" COPY breakpoints.txt %OSDK%\Oricutron\breakpoints.txt

CALL ./osdk_execute.bat

:End

