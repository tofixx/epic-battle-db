#!/usr/bin/env sh

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . 

./benchmark_insert
./benchmark_scan
./benchmark_update
./benchmark_thread
