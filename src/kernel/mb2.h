#include <drivers/utils/types.h>
#include "multiboot2.h"

/*
    This file pretty much gives a way of loading multiboot2 information.
*/

#define HIGH_HALF           0xffff800000000000
#define VIRTUAL(addr)       (void*)((u64)(addr) | HIGH_HALF)
#define ALIGN(addr, nbytes) (void*)(((u64)(addr) + (nbytes) - 1) & ~((nbytes) -1))

/// @brief Multiboot2 union struct
/// @details This struct provides a union for multiboot2 information
struct multiboot2_tag_all {
    union {
        /// For more information on the following structures, please
        /// refer to multiboot2 docs, or the multiboot2.h header file

        struct multiboot_tag tag;

        struct multiboot_tag_string string;

        struct multiboot_tag_module module;

        struct multiboot_tag_basic_meminfo basic_meminfo;

        struct multiboot_tag_bootdev bootdev;

        struct multiboot_tag_mmap mmap;

        struct multiboot_tag_vbe vbe;

        struct multiboot_tag_framebuffer framebuffer;

        struct multiboot_tag_framebuffer_common framebuffer_common;

        struct multiboot_tag_elf_sections elf_sections;

        struct multiboot_tag_apm apm;

        struct multiboot_tag_efi32 efi32;

        struct multiboot_tag_efi64 efi64;

        struct multiboot_tag_smbios smbios;

        struct multiboot_tag_old_acpi old_acpi;

        struct multiboot_tag_new_acpi new_acpi;

        struct multiboot_tag_network network;
    };
};

/// @brief Multiboot2 tag names
static char* multiboot2_tag_names[16] = {
    "cmdline",  "boot_loader_name", "module",      "basic_meminfo",
    "mmap",     "vbe",              "framebuffer", "elf_sections",
    "apm",      "efi32",            "efi64",       "smbios",
    "acpi_old", "acpi_new",         "network"
};

/// @brief Initialises multiboot2
/// @param address The address from multiboot2
/// @param magic The magic from multiboot2
/// @return 0 on success, -1 on error
int multiboot2_init(u64 address, u32 magic) {
    int i;

    struct multiboot2_tag_all* tag = (struct multiboot2_tag_all*)(address + 8);

    if(magic != MULTIBOOT2_BOOTLOADER_MAGIC)
        return -1;

    u32 total_size = *(u32*)(address);
    u64 end = address + total_size;

    while((u64)tag < end && tag->tag.type != MULTIBOOT_TAG_TYPE_END) {

        //tag = (struct multiboot2_tag_all*)ALIGN((u64)tag + tag->tag.size, MULTIBOOT_TAG_ALIGN);
    }

    return 0;
}