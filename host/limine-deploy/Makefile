# SPDX-License-Identifier: BSD-2-Clause
# Created: Sun Apr 24 2022 18:21:18
CCFLAGS := -O2 -pipe -Wall -Wextra -std=c11
PHONY_TARGETS :=
include $(TOPDIR)/mk/compile.mk
include $(TOPDIR)/mk/flags.mk
include $(TOPDIR)/mk/tools.mk

PHONY_TARGETS += all
all: limine-deploy

PHONY_TARGETS += clean
clean:
	@$(RM) -v limine-deploy

limine-deploy: limine-deploy.c limine-hdd.h
	@$(ECHO) "linking/compiling $@"
	@$(CC) $(CCFLAGS) limine-deploy.c -o $@

# Set up phony targets
.phony: $(PHONY_TARGETS)
