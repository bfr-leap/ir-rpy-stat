#!/bin/bash

./build.sh

if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    echo "Running on Windows..."

    ./build/Release/ir-rpy-stat.tsk

else
    echo "Running on Linux..."

    ./build/ir-rpy-stat.tsk
fi
