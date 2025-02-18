#ifndef MLIB_MOP_H

#define MLIB_MOP_H

#include "errlib/err.h"

#define MOP_SUC 0 // success
#define MOP_EDZ 1 // divide by zero
#define MOP_EOF 2 // overflow
#define MOP_EUF 3 // underflow

#define MOP_SUC_MSG "Success"
#define MOP_EDZ_MSG "Divide by zero"
#define MOP_EOF_MSG "Overflow"
#define MOP_EUF_MSG "Underflow"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

Err max_int(int a, int b, int* res);

Err min_int(int a, int b, int* res);

Err safe_add_int(int a, int b, int* res);

Err safe_sub_int(int a, int b, int* res);

Err safe_mul_int(int a, int b, int* res);

Err safe_div_int(int a, int b, int* res);

Err safe_math_mod_int(int a, int b, int* res);

Err safe_mod_int(int a, int b, int* res);

#endif // MLIB_MOP_H