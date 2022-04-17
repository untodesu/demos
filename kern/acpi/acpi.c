/* SPDX-License-Identifier: BSD-2-Clause */
#include <limine.h>
#include <sys/acpi/acpi.h>
#include <sys/acpi/table.h>
#include <sys/debug.h>
#include <sys/printk.h>
#include <sys/pmem.h>
#include <sys/string.h>

/* 5.2.5.3 - Root System Description Pointer (RSDP) */
struct acpi_rsdp_rev1 {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_ptr;
} __packed;

/* 5.2.5.3 - Root System Description Pointer (RSDP) */
struct acpi_rsdp_rev2 {
    struct acpi_rsdp_rev1 rev1;
    uint32_t length;
    uint64_t xsdt_ptr;
    uint8_t checksum;
    uint8_t reserved[3];
} __packed;

static const struct acpi_rsdp_rev2 *rsdp = NULL;
static const struct acpi_rsdt *rsdt = NULL;
static const struct acpi_xsdt *xsdt = NULL;

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0,
    .response = NULL
};

static int sdt_signature_match(const struct acpi_sdt *sdt, const char *signature)
{
    size_t i;
    size_t length = strnlen(signature, ACPI_SDT_SIGNATURE_SIZE);
    for(i = 0; i < length; i++) {
        if(sdt->signature[i] == signature[i])
            continue;
        return 0;
    }

    return 1;
}

const void *acpi_lookup_sdt(const char *signature, size_t index)
{
    size_t i, count, num_sdts;
    struct acpi_sdt *sdt = NULL;

    if(xsdt) {
        count = 0;
        num_sdts = (xsdt->header.length - sizeof(struct acpi_sdt)) / sizeof(uint64_t);
        for(i = 0; i < num_sdts; i++) {
            sdt = pptr_to_vptr(xsdt->entries[i]);
            if(sdt_signature_match(sdt, signature)) {
                if(count++ != index)
                    continue;
                return sdt;
            }
        }
    }
    else if(rsdt) {
        count = 0;
        num_sdts = (rsdt->header.length - sizeof(struct acpi_sdt) / sizeof(uint32_t));
        for(i = 0; i < num_sdts; i++) {
            sdt = pptr_to_vptr(rsdt->entries[i]);
            if(sdt_signature_match(sdt, signature)) {
                if(count++ != index)
                    continue;
                return sdt;
            }
        }
    }

    return NULL;
}

static unsigned int get_checksum(const void *s, size_t n)
{
    const uint8_t *sb = s;
    unsigned int checksum = 0;
    while(n--)
        checksum += *sb++;
    return checksum & 0xFF;
}

static void init_acpi(void)
{
    unsigned int checksum;

    panic_unless_msg(rsdp_request.response, "acpi: no boot response for rsdp request");
    panic_unless_msg(rsdp_request.response->address, "acpi: rsdp address is not valid");
    rsdp = rsdp_request.response->address;

    if(rsdp->rev1.revision >= 2)
        checksum = get_checksum(rsdp, sizeof(struct acpi_rsdp_rev2));
    else
        checksum = get_checksum(&rsdp->rev1, sizeof(struct acpi_rsdp_rev1));
    panic_unless_msg(checksum == 0, "acpi: rsdp checksum is not valid");

    if(rsdp->rev1.revision >= 2 && rsdp->xsdt_ptr) {
        xsdt = pptr_to_vptr(rsdp->xsdt_ptr);
        pk_info("acpi: xsdt at %p", (const void *)xsdt);
    }
    else if(rsdp->rev1.rsdt_ptr) {
        rsdt = pptr_to_vptr(rsdp->rev1.rsdt_ptr);
        pk_info("acpi: rsdt at %p", (const void *)rsdt);
    }
    else {
        /* How did we get here? */
        panic("acpi: unsupported version");
    }

    pk_info("acpi: madt at %p", (const void *)acpi_lookup_sdt(ACPI_MADT_SIGNATURE, 0));
}

setup_initcall(acpi, init_acpi);
initcall_dependency(acpi, pmem);
