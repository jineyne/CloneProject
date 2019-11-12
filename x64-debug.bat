@echo off

echo.
echo ====================
echo =    x64 build     =
echo ====================
echo.

set PATH=d:\Program Files\LLVM\bin;%PATH%
set INCLUDE=D:\Program Files\LLVM\lib\clang\8.0.0\include;%INCLUDE%

cmake -H. -GNinja -Bbuild
cd build 
Ninja 
cd ..
