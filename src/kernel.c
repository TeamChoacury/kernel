#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000


size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

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


void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("1234567890",0,0);

    
    while (1) {}
}
