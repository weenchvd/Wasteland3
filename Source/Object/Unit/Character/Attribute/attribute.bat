@ECHO OFF
set batchDir=%~dp0
set flatcDir=..\..\..\..\..\.out\build\x64-Debug\_deps\flatbuffers-build\

pushd %batchDir%

pushd %flatcDir%
set flatcDir=%cd%
popd

echo Errors:
echo.

%flatcDir%\flatc.exe --cpp %~n0.fbs

popd

echo.
echo Done!

pause
