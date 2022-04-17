/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_ACPI_ACPI_H_
#define _SYS_ACPI_ACPI_H_ 1
#include <stddef.h>
#include <sys/initcall.h>

const void *acpi_lookup_sdt(const char *signature, size_t index);

initcall_extern(acpi);

#endif
