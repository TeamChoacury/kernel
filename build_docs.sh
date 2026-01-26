#!/usr/bin/env bash
set -e

BUILD_DIR=build

mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"

# Configure and compile
cmake .. -DKERNEL_BUILD_DOCS=ON -DKERNEL_BUILD=OFF
cmake --build .

# grub-mkrescue -o choacury-os.iso isodir/

# Run
qemu-system-x86_64 -cdrom choacury-os.iso

cd ..