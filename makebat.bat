@echo off
setlocal EnableDelayedExpansion

set CPPFILES=

for /f "delims=" %%a in ('dir /s/b *.cpp') do (
  set CPPFILES="%%a" !CPPFILES!
)

set COMPILE_COMMAND=g++ %CPPFILES% -o r.exe

echo %COMPILE_COMMAND%
%COMPILE_COMMAND%

endlocal