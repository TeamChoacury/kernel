cmake_minimum_required(VERSION 3.10)
project(Choacury C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -O2 -mno-red-zone -fno-pie")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")

set(CMAKE_C_LINK_EXECUTABLE "ld -n -T ${CMAKE_SOURCE_DIR}/src/linker.ld -o <TARGET> <OBJECTS>")

add_executable(kernel.bin
    src/boot.s
    src/kernel.c
)

set_target_properties(kernel.bin PROPERTIES LINK_FLAGS "")

add_custom_command(TARGET kernel.bin POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Build complete"
)

add_custom_target(iso ALL
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp kernel.bin isodir/boot/kernel.bin
    COMMAND echo 'set timeout=0' > isodir/boot/grub/grub.cfg
    COMMAND echo 'set default=0' >> isodir/boot/grub/grub.cfg
    COMMAND echo '' >> isodir/boot/grub/grub.cfg
    COMMAND echo 'menuentry "Choacury OS" {' >> isodir/boot/grub/grub.cfg
    COMMAND echo '    multiboot2 /boot/kernel.bin' >> isodir/boot/grub/grub.cfg
    COMMAND echo '    boot' >> isodir/boot/grub/grub.cfg
    COMMAND echo '}' >> isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o choacury-os.iso isodir
    DEPENDS kernel.bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Creating ISO"
)

# Configuration
include(cmake/config.cmake)
# Doxygen config
include(cmake/docs.cmake)