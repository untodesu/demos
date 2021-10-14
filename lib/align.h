#ifndef __LIB_ALIGN_H__
#define __LIB_ALIGN_H__ 1
#define ALIGN_CEIL(x, align) (((x) + (align) - 1) & ~((align) - 1))
#define ALIGN_FLOOR(x, align) ((x) & ~((align) - 1))
#endif
