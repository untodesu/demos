#ifndef __SYS_EXCEPTIONS_H__
#define __SYS_EXCEPTIONS_H__ 1
#include <lib/inttypes.h>

typedef void(*exception_handler_t)(uint64_t code);
void init_exceptions(void);
void set_exception_handler(unsigned int vector, exception_handler_t handler);

#endif
