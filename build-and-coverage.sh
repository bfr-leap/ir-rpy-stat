#!/bin/bash

#./build.sh

cmake -B build -DCOVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build

ctest -C Debug --test-dir build
cmake --build build --target coverage