#!/usr/bin/env sh

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. # use optimization flags: -DOPT1:BOOL=ON
cmake --build . 
ctest -V #-V enables verbose output alternative: --output-on-failure only shows output when task fails
