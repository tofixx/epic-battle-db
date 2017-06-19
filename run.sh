#!/usr/bin/env sh


mkdir _build
cd _build
cmake ..
cmake --build . 
ctest -V #-V enables verbose output alternative: --output-on-failure only shows output when task fails
