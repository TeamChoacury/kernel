.set MULTIBOOT2_MAGIC,              0xE85250D6
.set MULTIBOOT2_ARCHITECTURE,       0
.set MULTIBOOT2_HEADER_LENGTH,      (multiboot2_header_end - multiboot2_header)
.set MULTIBOOT2_CHECKSUM,           -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCHITECTURE + MULTIBOOT2_HEADER_LENGTH)

/* Multiboot2 header */
.section .multiboot, "a"
.align 8
multiboot2_header:
    .long MULTIBOOT2_MAGIC
    .long MULTIBOOT2_ARCHITECTURE
    .long MULTIBOOT2_HEADER_LENGTH
    .long MULTIBOOT2_CHECKSUM

    .align 8
    .short 0    /* type */
    .short 0    /* flags */
    .long 8     /* size */
multiboot2_header_end:

/* Stack */
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:
/* Multiboot information */
mb_magic:
    .quad 0
mb_info:
    .quad 0

/* Page tables */
.align 4096
pml4:
    .skip 4096
pdpt:
    .skip 4096
pd:
    .skip 4096

.section .rodata
.align 16
gdt64:
    .quad 0x0000000000000000    /* Null descriptor */
    .quad 0x00209A0000000000 /* .quad 0x002F9A000000FFFF */    /* Code descriptor */
    .quad 0x0000920000000000 /* .quad 0x00AF92000000FFFF */    /* Data descriptor */
gdt64_end:

gdt64_pointer:
    .word gdt64_end - gdt64 - 1
    .quad gdt64

.section .text
.code32
.global _start
.type _start, @function
_start:
    /* Move multiboot info */
    mov %eax, mb_magic
    mov %ebx, mb_info

    mov $stack_top, %esp
    
    /*Setup paging */
    call setup_page_tables
    
    /* Enable PAE */
    mov %cr4, %eax
    or $0x20, %eax
    mov %eax, %cr4
    
    /* Load PML4*/
    lea pml4, %eax
    mov %eax, %cr3

    mov $0xC0000080, %ecx
    rdmsr
    or $0x100, %eax
    wrmsr
    
    /* Enable paging */
    mov %cr0, %eax
    or $0x80000001, %eax
    mov %eax, %cr0
    
    lgdt gdt64_pointer
    
    ljmp $0x08, $long_mode


setup_page_tables:
    /* PML4[0] -> PDPT */
    lea pdpt, %eax
    or $0x03, %eax
    mov %eax, pml4
    
    /* PDPT[0] -> PD */
    lea pd, %eax
    or $0x03, %eax
    mov %eax, pdpt
    
    /* PD[0] -> 2MB page */
    mov $0x83, %eax
    mov %eax, pd
    
    ret

.code64
long_mode:
    lea stack_top(%rip), %rsp
    and $~0xF, %rsp

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    /* Move multiboot info */
    mov mb_info(%rip), %rdi
    mov mb_magic(%rip), %rsi
    
    /* Call kernel */
    call kernel_main
    
    cli
1:  hlt
    jmp 1b

.size _start, . - _start