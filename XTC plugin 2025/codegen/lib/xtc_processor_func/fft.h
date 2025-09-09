//
// File: fft.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef FFT_H
#define FFT_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"

// Function Declarations
extern void b_generate_twiddle_tables(double costab[8193], double sintab[8193]);
extern void generate_twiddle_tables(double costab[8193], double sintab[8193]);

#endif

//
// File trailer for fft.h
//
// [EOF]
//
