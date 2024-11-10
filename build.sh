#!/bin/bash

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCOVERAGE=ON
cmake --build build 