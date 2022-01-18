@ECHO OFF
set batchDir=%~dp0
set flatcDir=..\..\..\..\..\..\.out\build\x64-Debug\_deps\flatbuffers-build\
set fbsDir=..\

pushd %batchDir%

pushd %flatcDir%
set flatcDir=%cd%
popd

pushd %fbsDir%
set fbsDir=%cd%
popd

echo Errors:
echo.

%flatcDir%\flatc.exe --binary %fbsDir%\%~n0.fbs %~n0.json
rem %flatcDir%\flatc.exe --binary %fbsDir%\attribute.fbs attribute.json

popd

echo.
echo Done!

pause
