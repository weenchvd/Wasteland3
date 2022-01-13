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

%flatcDir%\flatc.exe --json --strict-json --defaults-json --natural-utf8 -o %batchDir%\reverse %fbsDir%\attribute.fbs -- attribute.bundle
%flatcDir%\flatc.exe --jsonschema --strict-json --defaults-json --natural-utf8 -o %batchDir%\reverse %fbsDir%\attribute.fbs -- attribute.bundle
rem D:\_Code\Wasteland3\.out\build\x64-Debug\_deps\flatbuffers-build\flatc.exe --json --strict-json --defaults-json --natural-utf8 --raw-binary ..\attribute.fbs -- attribute.bundle

popd

echo.
echo Done!

pause
