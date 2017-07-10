#!/usr/bin/env sh

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . 

./benchmark_insert 100000 1000
./benchmark_scan 10000000 20
./benchmark_update 100000 100
./benchmark_thread 1000000 100 8
