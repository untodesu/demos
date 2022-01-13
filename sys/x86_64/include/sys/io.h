/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_IO_H_
#define _SYS_IO_H_ 1
#include <stdint.h>

/* TODO list:
 * [x]  remake the legacy io  in a better way
 *      so we don't use actual instruction names:
 *      outb -> io_write8 with throttled counterparts.
 * [ ]  more io_throttle compatibility. not sure if
 *      it's really needed but linux seems to cover
 *      more cases where hardware misbehaves: the port 0x80
 *      may be taken on some IBM PC clones because there
 *      WAS and IS not a single standard about io throttling.
 * [ ]  memory-mapped io along with acpi table parsing.
 */

#define IO_LEGACY_IN8   "inb"
#define IO_LEGACY_IN16  "inw"
#define IO_LEGACY_IN32  "inl"
#define IO_LEGACY_OUT8  "outb"
#define IO_LEGACY_OUT16 "outw"
#define IO_LEGACY_OUT32 "outl"

typedef uint16_t    io_addr_t;
typedef uint8_t     io_uint8_t;
typedef uint16_t    io_uint16_t;
typedef uint32_t    io_uint32_t;

static inline void io_throttle(void)
{
    asm volatile("outb %0, $0x80"::"a"((io_uint8_t)0));
}

/* build legacy x86 io read functions */
#define _io_build_legacy_read(bits) \
    static inline io_uint##bits##_t io_read##bits(io_addr_t addr) \
    {io_uint##bits##_t val;asm volatile(IO_LEGACY_IN##bits" %1,%0":"=a"(val):"Nd"(addr));return val;} \
    static inline io_uint##bits##_t io_read##bits##_throttle(io_addr_t addr) \
    {io_uint##bits##_t val=io_read##bits(addr);io_throttle();return val;}

/* build legacy x86 io write functions */
#define _io_build_legacy_write(bits) \
    static inline void io_write##bits(io_addr_t addr, io_uint##bits##_t val) \
    {asm volatile(IO_LEGACY_OUT##bits" %0,%1"::"a"(val),"Nd"(addr));} \
    static inline void io_write##bits##_throttle(io_addr_t addr, io_uint##bits##_t val) \
    {io_write##bits(addr, val);io_throttle();}

_io_build_legacy_read(8)
_io_build_legacy_read(16)
_io_build_legacy_read(32)

_io_build_legacy_write(8)
_io_build_legacy_write(16)
_io_build_legacy_write(32)

#endif
