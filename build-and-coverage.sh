#!/bin/bash

if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    echo "Coverage not supported on Windows..."

    ./build/Release/test-ir-rpy-stat.tsk

else
    echo "Coverage on Linux..."

    cmake -B build -DCOVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
    cmake --build build

    ctest -C Debug --test-dir build
    cmake --build build --target coverage
fi

