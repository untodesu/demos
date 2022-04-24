# SPDX-License-Identifier: BSD-2-Clause
# Created: Sun Apr 24 2022 18:28:48
TOPDIR := $(realpath ..)
PHONY_TARGETS :=
export TOPDIR

PHONY_TARGETS += all
all:
	$(MAKE) all -C limine-deploy

PHONY_TARGETS += clean
clean:
	$(MAKE) clean -C limine-deploy

# Set up phony targets
.phony: $(PHONY_TARGETS)
