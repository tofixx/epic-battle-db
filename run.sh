#!/usr/bin/env sh

# normal
mkdir _build
cd _build
cmake ..
cmake --build . && ./run
cd ..
rm -R _build

# O-flag -O0
mkdir _build
cd _build
cmake .. -DOPT0:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# O-flag -O1
mkdir _build
cd _build
cmake .. -DOPT1:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# O-flag -O2
mkdir _build
cd _build
cmake .. -DOPT2:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# O-flag -O3
mkdir _build
cd _build
cmake .. -DOPT3:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# O-flag -O4
mkdir _build
cd _build
cmake .. -DOPT4:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# release
mkdir _build
cd _build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . && ./run
cd ..
rm -R _build
