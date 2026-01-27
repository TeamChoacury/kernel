#include <kernel/mb2.h>

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