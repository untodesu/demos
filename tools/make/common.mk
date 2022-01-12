ASFLAGS		+= -Wall -Wextra -Werror -pedantic
CFLAGS		+= -Wall -Wextra -Werror -pedantic -std=gnu99
CPPFLAGS	+=

%.c.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS.$*.c) $(CPPFLAGS) -c -o $@ $(realpath $<)

%.S.o: %.S
	$(AS) $(ASFLAGS) $(ASFLAGS.$*.S) $(CPPFLAGS) -c -o $@ $(realpath $<)

%.a:
	$(AR) rs $@ $^ 2> /dev/null
