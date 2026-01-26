/// @file kernel_panic Kernel Panic implementation

#ifndef PANIC_H
#define PANIC_H

#define __panic_stringify_helper(s) #s
#define __panic_stringify(s) __panic_stringify_helper(s)

/// @brief Kernel panic
#define kpanic(message) kpanic_impl("Kernel Panic! Location: " __FILE__ ":" __panic_stringify(__LINE), message)

/// @brief Kernel panic implementation
/// @warning This should not be called directly, refer to `kpanic`
__attribute__((noreturn)) void kpanic_impl(const char* location_prefix, const char* message);

#endif