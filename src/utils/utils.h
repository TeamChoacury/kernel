#include "types.h"

#ifndef UTILS_H
#define UTILS_H

/// @brief Copy memory from source to destination
/// @param dest The destination pointer
/// @param source The source pointer
/// @param nbytes The length of the source in bytes
/// @return The destination pointer
void* memcpy(void *dest, const void *source, size_t nbytes);
/// @brief Moves memory from source to destination
/// @param dest The destination pointer
/// @param source The source pointer
/// @param nbytes The length of the source in bytes
/// @return The destination pointer
void* memmove(void *dest, const void *source, size_t nbytes);
/// @brief Sets a value in memory
/// @param dest The destination pointer
/// @param val The value to set the memory to
/// @param len The length of the destination
/// @return The destination pointer
void* memset(void *dest, int val, size_t len);
/// @brief Compares 2 pointers in memory
/// @param a The first pointer
/// @param b The second pointer
/// @param len The length of the data
/// @return `a_u8[i] - b_u8[i]` or 0
/// @todo Add a better explanation for the return type
int memcmp(const void *a, const void *b, size_t len);

/// @brief Converts an integer to string?
/// @param n
/// @param str
/// @todo Write better docs for this function
void iota(int n, char str[]);

/// @brief The return structure of `atoi`
typedef struct {
    bool valid;
    int value;
} atoi_result_t;
/// @brief Attempts to convert a string to an integer
/// @param The string to attempt to convert
/// @return Returns an `atoi_result_t` object with a valid boolean, and an integer
atoi_result_t atoi(const char* str);

/// @brief Pi constant
#define M_PI 3.14159265358979323846

/// @brief Gets the absolute (positive) value of the integer
/// @param x The original number
/// @return The absolute (positive) number
int abs(int x);
//float fmod(float x, float y);
///float sin(float x);
//float cos(float x);

/// @brief Converts an unsigned 64-bit integer to a string
/// @param number The number
/// @param buffer The string pointer
void uint64_to_string(uint64_t number, char* buffer);
/// @brief Gets the length of the string
/// @param str The string
/// @return The length of the string
int strlen(const char *str);
/// @brief Compares 2 strings
/// @param str1 The first string pointer
/// @param str2 The second string poitner
/// @return `*str1 - *str2`
int strcmp(const char *str1, const char *str2);
/// @brief Copies a string from source to destination
/// @param dest The destination pointer
/// @param src The source pointer
/// @return The destination pointer
char* strcpy(char *dest, const char *src);
/// @brief Concatenates (adds to the end) a string
/// @param dest The destination pointer
/// @param src The source pointer (The string to add)
/// @return The destination pointer
char* strcat(char *dest, const char *src);

/// @brief Converts an upper character to a lower character
/// @param ch The upper character
/// @return The lower character (Or the original if it was already lower case)
int tolower(int ch);
/// @brief Converts a lower character to an upper character
/// @param ch The lower character
/// @return The higher character (Or the original if it was already higher case)
int toupper(int ch);

#endif