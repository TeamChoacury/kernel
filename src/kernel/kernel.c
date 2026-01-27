#include <stdint.h>
#include <stddef.h>

#include <memory/kmalloc.h>
#include <memory/pmm.h>

#include "multiboot2.h"
#include "mb2.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

void terminal_initialize(void) {
    volatile uint16_t* buffer = (volatile uint16_t*) VGA_MEMORY;
    
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            buffer[index] = (uint16_t) ' ' | (uint16_t) (15 | 0 << 4) << 8;
        }
    }
}

void terminal_writestring(const char* data, size_t row, size_t col) {
    volatile uint16_t* buffer = (volatile uint16_t*) VGA_MEMORY;
    size_t len = strlen(data);
    
    for (size_t i = 0; i < len; i++) {
        const size_t t = row * VGA_WIDTH + (col + i);
        if (t < VGA_WIDTH * VGA_HEIGHT) {
	        buffer[t] = (uint16_t) data[i] | (uint16_t) (15 | 0 << 4) << 8;
        }
    }
}

void kernel_main(u64 address, u32 magic) {
    kmalloc_init();
    // This won't work at all until multiboot data is sorted out
    //pmm_init(mbd);

    terminal_initialize();

    terminal_writestring("...",0,0);

    /// @bug Bootloader not providing multiboot information
    if(magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        terminal_writestring("Kernel Panic: Bootloader did not provide multiboot2 information", 0, 0);
        asm volatile("hlt");
    } else {
        terminal_writestring("Bootloader provided multiboot2 information", 1, 0);
    }

    int mb2_init_success = multiboot2_init(address, magic);
    if(mb2_init_success == 0) {
        terminal_writestring("MB2 init successful", 2, 0);
    } else {
        terminal_writestring("MB2 init failed", 2, 0);
    }
    
    while (1) {}
}