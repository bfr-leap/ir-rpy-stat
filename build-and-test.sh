#!/bin/bash

./build.sh


if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    echo "Testing on Windows..."

    ./build/Release/test-ir-rpy-stat.tsk

else
    echo "Testing on Linux..."

    ./build/test-ir-rpy-stat.tsk
fi