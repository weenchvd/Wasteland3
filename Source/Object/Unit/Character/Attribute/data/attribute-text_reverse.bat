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

%flatcDir%\flatc.exe --json --strict-json --defaults-json --natural-utf8 -o %batchDir%\reverse %fbsDir%\attribute-text.fbs -- attribute-text.bundle
%flatcDir%\flatc.exe --jsonschema --strict-json --defaults-json --natural-utf8 -o %batchDir%\reverse %fbsDir%\attribute-text.fbs -- attribute-text.bundle

popd

echo.
echo Done!

pause
