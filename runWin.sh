#!/usr/bin/env sh

rm -rf _build
mkdir _build
cd _build
cmake ..
cmake --build . 
ctest
