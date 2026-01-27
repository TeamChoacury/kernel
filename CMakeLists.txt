cmake_minimum_required(VERSION 3.10)
project(Choacury C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -O2 -mno-red-zone -fno-pie -nostdlib")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")

set(CMAKE_C_LINK_EXECUTABLE "ld -n -T ${CMAKE_SOURCE_DIR}/src/linker.ld -o <TARGET> <OBJECTS>")

# Configuration
include(cmake/config.cmake)

set(
    KERNEL_SOURCES
    src/boot.s
    src/kernel/kernel.c
    src/kernel/mb2.c
    src/memory/kmalloc.c
    src/memory/pmm.c
    src/utils/utils.c
    src/panic.c
)

if(KERNEL_BUILD)
add_executable(kernel.bin
    ${KERNEL_SOURCES}
)

# Add src headers, so you should be able to include using #include <>
target_include_directories(kernel.bin PRIVATE src)

set_target_properties(kernel.bin PROPERTIES LINK_FLAGS "")

add_custom_command(TARGET kernel.bin POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Build complete"
)

add_executable(kernel.elf ${KERNEL_SOURCES})
target_include_directories(kernel.elf PRIVATE src)
set_target_properties(kernel.elf PROPERTIES LINK_FLAGS "-nostdlib max-page-size=0x1000")

add_custom_target(iso ALL
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp kernel.elf isodir/boot/kernel.elf
    COMMAND echo 'set timeout=0' > isodir/boot/grub/grub.cfg
    COMMAND echo 'set default=0' >> isodir/boot/grub/grub.cfg
    COMMAND echo '' >> isodir/boot/grub/grub.cfg
    COMMAND echo 'menuentry "Choacury OS" {' >> isodir/boot/grub/grub.cfg
    COMMAND echo '    multiboot2 /boot/kernel.elf' >> isodir/boot/grub/grub.cfg
    COMMAND echo '    boot' >> isodir/boot/grub/grub.cfg
    COMMAND echo '}' >> isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o choacury-os.iso isodir
    DEPENDS kernel.elf
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Creating ISO"
)
endif()

# Doxygen config
include(cmake/docs.cmake)