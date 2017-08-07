#! /bin/bash
set -e

# Ensure that build directory exists
mkdir -p build

# Launch CMake
cd build

cmake ..
make
