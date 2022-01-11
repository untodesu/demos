ROOT_PATH ?= ..

include $(ROOT_PATH)/tools/scripts/make/common.mk
include $(ROOT_PATH)/tools/scripts/make/tools.host.mk

all:
	$(MAKE) all -C genconfig.d
	$(MAKE) all -C limine-install.d

clean:
	$(MAKE) clean -C genconfig.d
	$(MAKE) clean -C limine-install.d

install:
	$(MAKE) install -C genconfig.d
	$(MAKE) install -C limine-install.d

.phony: all clean install
