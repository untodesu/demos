ROOT_PATH := ../..

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.host.mk

CFLAGS := -O2 -pipe -Wall -Wextra

all: limine-install

clean:
	$(RM) limine-install

install: limine-install
	cp limine-install $(ROOT_PATH)/tools/limine-install

limine-install: inc.S limine-hdd.bin limine-install.c
	$(CC) $(CFLAGS) -std=c11 limine-install.c inc.S -o $@

.phony: all clean install
