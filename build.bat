@echo off
setlocal

if not exist "build" (
	mkdir "build"
)
pushd "build"
set CompilerFlags=/nologo /W3 /Z7 /Fe:"main.exe"
set LinkerFlags=/incremental:no /opt:icf /opt:ref /subsystem:windows /WX
set LibsToLink=kernel32.lib user32.lib gdi32.lib opengl32.lib libucrt.lib
call cl %CompilerFlags% ../main.c /link %LinkerFlags% %LibsToLink%
popd