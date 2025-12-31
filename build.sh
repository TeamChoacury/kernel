#!/usr/bin/env bash
set -e

BUILD_DIR=build

mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"

# Configure and compile
cmake ..
cmake --build .

# Run
qemu-system-x86_64 -cdrom choacury-os.iso

cd ..