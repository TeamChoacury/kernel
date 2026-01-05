#ifndef KMALLOC_H
#define KMALLOC_H

/// @brief Initialise heap
void kmalloc_init();
/// @brief Allocate memory
/// @param size The size to allocate
/// @return The pointer to the allocated memory
void* kmalloc(size_t size);
/// @brief Free allocated memory
/// @param The pointer to the allocated memory
void kfree(void* ptr);

#endif