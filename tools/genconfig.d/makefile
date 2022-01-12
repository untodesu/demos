ROOT_PATH := ../..

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.host.mk

all: genconfig

clean:
	$(RM) genconfig

install: genconfig
	cp genconfig $(ROOT_PATH)/tools/genconfig

genconfig: genconfig.c
	$(CC) $(CFLAGS) -o $@ $^

.phony: all clean install
