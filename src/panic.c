#include "panic.h"

__attribute__((noreturn)) void kpanic_impl(const char* location_prefix, const char* message) {
    /// @todo Implement this once VBE/display driver has been added

    asm volatile("cli");
    for (;;) {
        asm volatile("hlt");
    }
}