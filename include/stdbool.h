#ifndef STDBOOL_H
#define STDBOOL_H 1

#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
typedef int bool;
#define false 0
#define true 1
#endif

#endif
