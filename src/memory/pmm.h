#ifndef PMM_H
#define PMM_H

#include <kernel/multiboot2.h>
#include <utils/types.h>

extern u64 g_total_pmm_bytes;

/// @brief Initialises the Phyiscal Memory Manager
/// @param multiboot_info The multiboot information
void pmm_init(const struct multiboot_info* multiboot_info);

#endif