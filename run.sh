#!/usr/bin/env sh



# normal
mkdir _build
cd _build
cmake .. -DOPT0:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# normal
mkdir _build
cd _build
cmake .. -DOPT1:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# normal
mkdir _build
cd _build
cmake .. -DOPT2:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# normal
mkdir _build
cd _build
cmake .. -DOPT3:BOOL=ON
cmake --build . && ./run
cd ..
rm -R _build

# release
#cmake .. -DCMAKE_BUILD_TYPE=Release
#cmake --build . && ./run