/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_ACPI_TABLE_H_
#define _SYS_ACPI_TABLE_H_ 1
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

/* 5.2.6 - System Description Table Header */
#define ACPI_SDT_SIGNATURE_SIZE 4
struct acpi_sdt {
    char signature[ACPI_SDT_SIGNATURE_SIZE];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __packed;

/* 5.2.7 - Root System Description Table (RSDT) */
#define ACPI_RSDT_SIGNATURE "RSDT"
struct acpi_rsdt {
    struct acpi_sdt header;
    uint32_t entries[];
} __packed;

/* 5.2.8 - Extended System Description Table (XSDT) */
#define ACPI_XSDT_SIGNATURE "XSDT"
struct acpi_xsdt {
    struct acpi_sdt header;
    uint64_t entries[];
} __packed;

/* 5.2.12 - Multiple APIC Description Table (MADT) */
#define ACPI_MADT_SIGNATURE "APIC"
struct acpi_madt {
    struct acpi_sdt header;
    uint32_t lapic_addr;
    uint32_t flags;
    uint8_t ics[];
} __packed;

#endif
