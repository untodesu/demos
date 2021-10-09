CCFLAGS +=			\
	-fno-pie -fPIC	\
	-mno-80387		\
	-mno-mmx		\
	-mno-3dnow		\
	-mno-sse -mno-sse2

CPFLAGS += -DX86_64

LDFLAGS +=									\
	-fno-pie -fPIC							\
	-Wl,-static,--no-dynamic-linker,-ztext	\
	-z max-page-size=0x1000

subdirs_y += boot
