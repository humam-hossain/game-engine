REM Build script for engine
@echo off
SetLocal EnableDelayedExpansion

REM Get a list of all .c files.
SET cFilenmaes=
For /R . %%F in (*.c) Do (
    SET cFilenmaes=!cFilenmaes! "%%F"
)

REM echo "Files:" %cFilenmaes%
SET assembly=engine
SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
REM -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%\Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%\Lib
SET defines=-D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%"
clang %cFilenmaes% %compilerFlags% -o ../bin/%assembly%.dll %includeFlags% %linkerFlags% %defines%
