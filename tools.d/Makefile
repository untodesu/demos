# SPDX-License-Identifier: BSD-2-Clause
# Created: Sun Apr 24 2022 18:28:48
TOPDIR := $(realpath ..)
PHONY_TARGETS :=
export TOPDIR

PHONY_TARGETS += all clean

all:
	@$(MAKE) -C limine-deploy all
clean:
	@$(MAKE) -C limine-deploy clean

# Set up phony targets
.phony: $(PHONY_TARGETS)
