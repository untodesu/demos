/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_BOOT_H_
#define _SYS_BOOT_H_ 1
#include <stivale2.h>
#include <sys/cdefs.h>

extern struct stivale2_struct boot_struct;
const void *find_boot_tag(uint64_t tag_identifier);

/* Demos now boots as a Stivale2-compliant kernel.
 * That means it works for AMD64 and can be ported to ARM64.
 * However, it should be possible to port it to other arhitectures
 * that are not supported by the "official" Stivale2 specification
 * by emulating Stivale's structures and chain-calling this function. */
extern void boot_entry(const struct stivale2_struct *boot_struct_ptr) __noreturn;

#endif
