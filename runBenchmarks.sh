#!/usr/bin/env sh

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . 

./benchmark_insert 1000000 100
./benchmark_scan 10000000 100
./benchmark_update 1000000 100
./benchmark_updateLess 1000000 100
./benchmark_updateRandom 1000000 100
./benchmark_thread 1000000 100 8
./benchmark_thread 1000000 100 4
