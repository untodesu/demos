#ifndef UAPI_ARCH_STDARG_H
#define UAPI_ARCH_STDARG_H 1

// The older version was obviously shitting itself
// because GCC was not an optimal generic cross-compiler
// and was using linux-specific va_list as a built-in
// solution. Now that I have a working cross-compiler
// this problem is gone and this code will work without
// any workarounds like 
typedef __builtin_va_list __demos_va_list;
#define __demos_va_start(va, x) __builtin_va_start(va, x)
#define __demos_va_copy(va, dv) __builtin_va_copy(va, dv)
#define __demos_va_arg(va, t)   __builtin_va_arg(va, t)
#define __demos_va_end(va)      __builtin_va_end(va)

#endif
