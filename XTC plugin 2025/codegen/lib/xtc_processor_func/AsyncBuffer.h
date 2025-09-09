//
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"

// Function Declarations
extern void AsyncBuffer_read(dsp_AsyncBuffer *obj, int numRows, emxArray_real_T *
  out);
extern void AsyncBuffer_stepImpl(dsp_AsyncBuffer *obj, const double in[8193]);
extern void AsyncBuffer_write(dsp_AsyncBuffer *obj, const emxArray_real_T *in);

#endif

//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
