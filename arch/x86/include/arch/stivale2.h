/*
 * Copyright (c) 2019, 2020, 2021, mintsuki and contributors.
 * Copyright (c) 2021, Kirill GPRB.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef STIVALE2_H
#define STIVALE2_H 1
#include <arch/stddef.h>
#include <arch/stdint.h>
#include <demos/cdefs.h>

/* Anchor for non ELF kernels */
struct stivale2_anchor {
    uint8_t anchor[15];
    uint8_t bits;
    uint64_t phys_load_addr;
    uint64_t phys_bss_start;
    uint64_t phys_bss_end;
    uint64_t phys_stivale2hdr;
} __packed;

struct stivale2_tag {
    uint64_t identifier;
    uint64_t next;
} __packed;

struct stivale2_header {
    uint64_t entry_point;
    uint64_t stack;
    uint64_t flags;
    uint64_t tags;
} __packed;

#define STIVALE2_HEADER_TAG_ANY_VIDEO_ID    (0xc75c9fa92a44c4db)
#define STIVALE2_HEADER_TAG_FRAMEBUFFER_ID  (0x3ecc1bc43d0f7971)
#define STIVALE2_HEADER_TAG_FB_MTRR_ID      (0x4c7bb07731282e00)
#define STIVALE2_HEADER_TAG_TERMINAL_ID     (0xa85d499b1823be72)
#define STIVALE2_HEADER_TAG_SMP_ID          (0x1ab015085f3273df)
#define STIVALE2_HEADER_TAG_5LV_PAGING_ID   (0x932f477032007e8f)
#define STIVALE2_HEADER_TAG_UNMAP_NULL_ID   (0x92919432b16fe7e7)

struct stivale2_header_tag_any_video {
    struct stivale2_tag tag;
    uint64_t preference;
} __packed;

struct stivale2_header_tag_framebuffer {
    struct stivale2_tag tag;
    uint16_t framebuffer_width;
    uint16_t framebuffer_height;
    uint16_t framebuffer_bpp;
} __packed;

struct stivale2_header_tag_terminal {
    struct stivale2_tag tag;
    uint64_t flags;
} __packed;

struct stivale2_header_tag_smp {
    struct stivale2_tag tag;
    uint64_t flags;
} __packed;


#define STIVALE2_BOOTLOADER_BRAND_SIZE 64
#define STIVALE2_BOOTLOADER_VERSION_SIZE 64

struct stivale2_struct {
    char bootloader_brand[STIVALE2_BOOTLOADER_BRAND_SIZE];
    char bootloader_version[STIVALE2_BOOTLOADER_VERSION_SIZE];
    uint64_t tags;
} __packed;

#define STIVALE2_STRUCT_TAG_CMDLINE_ID          (0xe5e76a1b4597a781)
#define STIVALE2_STRUCT_TAG_MEMMAP_ID           (0x2187f79e8612de07)
#define STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID      (0x506461d2950408fa)
#define STIVALE2_STRUCT_TAG_EDID_ID             (0x968609d7af96b845)
#define STIVALE2_STRUCT_TAG_TEXTMODE_ID         (0x38d74c23e0dca893)
#define STIVALE2_STRUCT_TAG_FB_MTRR_ID          (0x6bc1a78ebe871172)
#define STIVALE2_STRUCT_TAG_TERMINAL_ID         (0xc2b3f4c3233b0974)
#define STIVALE2_STRUCT_TAG_MODULES_ID          (0x4b6fe466aade04ce)
#define STIVALE2_STRUCT_TAG_RSDP_ID             (0x9e1786930a375e78)
#define STIVALE2_STRUCT_TAG_EPOCH_ID            (0x566a7bed888e1407)
#define STIVALE2_STRUCT_TAG_FIRMWARE_ID         (0x359d837855e3858c)
#define STIVALE2_STRUCT_TAG_EFI_SYSTEM_TABLE_ID (0x4bc5ec15845b558e)
#define STIVALE2_STRUCT_TAG_KERNEL_FILE_ID      (0xe599d90c2975584a)
#define STIVALE2_STRUCT_TAG_KERNEL_SLIDE_ID     (0xee80847d01506c57)
#define STIVALE2_STRUCT_TAG_SMBIOS_ID           (0x274bd246c62bf7d1)
#define STIVALE2_STRUCT_TAG_SMP_ID              (0x34d1d96339647025)
#define STIVALE2_STRUCT_TAG_PXE_SERVER_INFO     (0x29d1e96239247032)
#define STIVALE2_STRUCT_TAG_MMIO32_UART         (0xb813f9b8dbc78797)
#define STIVALE2_STRUCT_TAG_DTB                 (0xabb29bd49a2833fa)
#define STIVALE2_STRUCT_TAG_VMAP                (0xb0ed257db18cb58f)

#define STIVALE2_MMAP_USABLE                    (0x0001)
#define STIVALE2_MMAP_RESERVED                  (0x0002)
#define STIVALE2_MMAP_ACPI_RECLAIMABLE          (0x0003)
#define STIVALE2_MMAP_ACPI_NVS                  (0x0004)
#define STIVALE2_MMAP_BAD_MEMORY                (0x0005)
#define STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE    (0x1000)
#define STIVALE2_MMAP_KERNEL_AND_MODULES        (0x1001)
#define STIVALE2_MMAP_FRAMEBUFFER               (0x1002)

struct stivale2_struct_tag_cmdline {
    struct stivale2_tag tag;
    uint64_t cmdline;
} __packed;

struct stivale2_mmap_entry {
    uint64_t base;
    uint64_t length;
    uint32_t type;
    uint32_t unused;
} __packed;

struct stivale2_struct_tag_memmap {
    struct stivale2_tag tag;
    uint64_t entries;
    struct stivale2_mmap_entry memmap[];
} __packed;

#define STIVALE2_FBUF_MMODEL_RGB 1
struct stivale2_struct_tag_framebuffer {
    struct stivale2_tag tag;
    uint64_t framebuffer_addr;
    uint16_t framebuffer_width;
    uint16_t framebuffer_height;
    uint16_t framebuffer_pitch;
    uint16_t framebuffer_bpp;
    uint8_t  memory_model;
    uint8_t  red_mask_size;
    uint8_t  red_mask_shift;
    uint8_t  green_mask_size;
    uint8_t  green_mask_shift;
    uint8_t  blue_mask_size;
    uint8_t  blue_mask_shift;
} __packed;

struct stivale2_struct_tag_edid {
    struct stivale2_tag tag;
    uint64_t edid_size;
    uint8_t  edid_information[];
} __packed;

struct stivale2_struct_tag_textmode {
    struct stivale2_tag tag;
    uint64_t address;
    uint16_t unused;
    uint16_t rows;
    uint16_t cols;
    uint16_t bytes_per_char;
} __packed;

struct stivale2_struct_tag_terminal {
    struct stivale2_tag tag;
    uint32_t flags;
    uint16_t cols;
    uint16_t rows;
    uint64_t term_write;
    uint64_t max_length;
} __packed;

#define STIVALE2_MODULE_STRING_SIZE 128
struct stivale2_module {
    uint64_t begin;
    uint64_t end;
    char string[STIVALE2_MODULE_STRING_SIZE];
} __packed;

struct stivale2_struct_tag_modules {
    struct stivale2_tag tag;
    uint64_t module_count;
    struct stivale2_module modules[];
} __packed;

struct stivale2_struct_tag_rsdp {
    struct stivale2_tag tag;
    uint64_t rsdp;
} __packed;

struct stivale2_struct_tag_epoch {
    struct stivale2_tag tag;
    uint64_t epoch;
} __packed;

#define STIVALE2_FIRMWARE_BIOS (1 << 0)
struct stivale2_struct_tag_firmware {
    struct stivale2_tag tag;
    uint64_t flags;
} __packed;

struct stivale2_struct_tag_efi_system_table {
    struct stivale2_tag tag;
    uint64_t system_table;
} __packed;

struct stivale2_struct_tag_kernel_file {
    struct stivale2_tag tag;
    uint64_t kernel_file;
} __packed;

struct stivale2_struct_tag_kernel_slide {
    struct stivale2_tag tag;
    uint64_t kernel_slide;
} __packed;

struct stivale2_struct_tag_smbios {
    struct stivale2_tag tag;
    uint64_t flags;
    uint64_t smbios_entry_32;
    uint64_t smbios_entry_64;
} __packed;

struct stivale2_smp_info {
    uint32_t processor_id;
    uint32_t lapic_id;
    uint64_t target_stack;
    uint64_t goto_address;
    uint64_t extra_argument;
} __packed;

struct stivale2_struct_tag_smp {
    struct stivale2_tag tag;
    uint64_t flags;
    uint32_t bsp_lapic_id;
    uint32_t unused;
    uint64_t cpu_count;
    struct stivale2_smp_info smp_info[];
} __packed;

struct stivale2_struct_tag_pxe_server_info {
    struct stivale2_tag tag;
    uint32_t server_ip;
} __packed;

struct stivale2_struct_tag_mmio32_uart {
    struct stivale2_tag tag;
    uint64_t addr;
} __packed;

struct stivale2_struct_tag_dtb {
    struct stivale2_tag tag;
    uint64_t addr;
    uint64_t size;
} __packed;

struct stivale2_struct_vmap {
    struct stivale2_tag tag;
    uint64_t addr;
} __packed;

#endif
