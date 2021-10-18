#ifndef _ALIGN_H_
#define _ALIGN_H_ 1
#define ALIGN_CEIL(x, align) (((x) + (align) - 1) & ~((align) - 1))
#define ALIGN_FLOOR(x, align) ((x) & ~((align) - 1))
#endif
