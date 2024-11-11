#!/bin/bash

# Check if the script is running on Windows (Git Bash or similar) or Linux
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    echo "Building on Windows..."

    # Check if the build directory exists
    if [ ! -d "build" ]; then
        # If it doesn't exist, create it and configure CMake for Windows
        cmake -S . -B build/
    fi

    # Build both Debug and Release configurations on Windows
    cmake --build build --config Debug
    cmake --build build --config Release

else
    echo "Building on Linux..."

    # Configure and build with Debug and Coverage enabled on Linux
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCOVERAGE=ON
    cmake --build build
fi
