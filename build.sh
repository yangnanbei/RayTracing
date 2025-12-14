#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="build"

mkdir -p "$BUILD_DIR"
cmake -S . -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"
