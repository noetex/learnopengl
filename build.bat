@echo off

if not exist "build" mkdir "build"
pushd "build"
set CompilerFlags=/nologo /W3 /Z7 /Fe:"main.exe"
set LinkerFlags=/incremental:no /opt:icf /opt:ref /subsystem:windows
cl %CompilerFlags% ../main.c /link %LinkerFlags%
popd