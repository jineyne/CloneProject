@echo off

echo.
echo ====================
echo =    x64 build     =
echo ====================
echo.

cmake -H. -G"Visual Studio 16 2019" -Bbuild -Ax64
cd build 
cd ..
