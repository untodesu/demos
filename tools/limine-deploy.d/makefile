ROOT_PATH := ../..

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.host.mk

CFLAGS := -O2 -pipe -Wall -Wextra

all: limine-deploy

clean:
	$(RM) limine-deploy

install: limine-deploy
	cp limine-deploy $(ROOT_PATH)/tools/limine-deploy

limine-deploy: limine-deploy.c limine-hdd.h
	$(CC) $(CFLAGS) -std=c11 limine-deploy.c -o $@

.phony: all clean install
