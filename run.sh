#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="build"

mkdir -p "$BUILD_DIR"
cmake -S . -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"

[ 0 -ne $? ] && exit

# run
./build/rayTracing > ./build/image.ppm
display build/image.ppm
