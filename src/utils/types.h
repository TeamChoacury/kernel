/// @todo Could probably do with implementing these locally
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

/* Instead of using 'chars' to allocate non-character bytes,
 * we will use these new type with no semantic meaning */
/// @brief Unsigned 64-bit integer
typedef uint64_t u64;
/// @brief Signed 64-bit integer
typedef int64_t  s64;
/// @brief Unsigned 32-bit integer
typedef uint32_t u32;
/// @brief Signed 32-bit integer
typedef int32_t  s32;
/// @brief Unsigned 16-bit integer
typedef uint16_t u16;
/// @brief Signed 16-bit integer
typedef int16_t  s16;
/// @brief Unsigned 8-bit integer
typedef uint8_t  u8;
/// @brief Signed 8-bit integer
typedef int8_t   s8;

/// @brief Unsigned integer pointer
typedef uintptr_t uptr;

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif