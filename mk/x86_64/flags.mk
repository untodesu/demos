# SPDX-License-Identifier: BSD-2-Clause
# Created: Sat Apr 23 2022 21:13:45

ASFLAGS	:=
ASFLAGS += -fno-pic
ASFLAGS += -mcmodel=kernel
ASFLAGS += -mno-3dnow -mno-80387 -mno-mmx
ASFLAGS += -mno-red-zone -mno-sse -mno-sse2

CCFLAGS	:=
CCFLAGS += $(ASFLAGS)

CPFLAGS	:=
CPFLAGS += -D__X86_64__=1 -D__AMD64__=1
CPFLAGS += -D__x86_64__=1 -D__amd64__=1

LDFLAGS	:=
LDFLAGS += -fno-pie -Wl,-static,--no-dynamic-linker,-ztext
LDFLAGS += -z max-page-size=0x1000
