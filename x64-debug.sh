#!/bin/sh

cmake -H. -G"Unix Makefiles" -Bbuild
cd build 
make
cd ..
