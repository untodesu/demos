ROOT_PATH ?= ..

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.host.mk

all:
	$(MAKE) all -C genconfig.d
	$(MAKE) all -C limine-deploy.d

clean:
	$(MAKE) clean -C genconfig.d
	$(MAKE) clean -C limine-deploy.d

install:
	$(MAKE) install -C genconfig.d
	$(MAKE) install -C limine-deploy.d

.phony: all clean install
