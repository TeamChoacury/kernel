#ifndef PMM_H
#define PMM_H

#include <multiboot.h>
#include <drivers/utils/types.h>

extern u64 g_total_pmm_bytes;

/// @brief Initialises the Phyiscal Memory Manager
/// @param multiboot_info The multiboot information
void pmm_init(const multiboot_info_t* multiboot_info);

#endif