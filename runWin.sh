#!/usr/bin/env sh

rm -rf build
mkdir build
cd build
cmake ..
cmake --build . 
ctest -V #-V enables verbose output alternative: --output-on-failure only shows output when task fails
