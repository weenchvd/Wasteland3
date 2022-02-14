@ECHO OFF

set FLATBUFFERS_COMPILER_FILE=$<SHELL_PATH:$<TARGET_FILE:flatc>>
set FLATBUFFERS_SCHEMA_FILES=$<SHELL_PATH:${VAR_SCHEMA_FILES}>
set INCLUDE_DIR=$<SHELL_PATH:${VAR_INCLUDE_DIR}>\
set OUTPUT_DIR=$<SHELL_PATH:${VAR_OUTPUT_DIR}>\

echo ~~ Start!
echo.

%FLATBUFFERS_COMPILER_FILE% --cpp -I %INCLUDE_DIR% -o %OUTPUT_DIR% %FLATBUFFERS_SCHEMA_FILES%

echo.
echo ~~ Done!

pause
