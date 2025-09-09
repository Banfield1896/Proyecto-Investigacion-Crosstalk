//
// File: xtc_processor_func_emxAPI.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef XTC_PROCESSOR_FUNC_EMXAPI_H
#define XTC_PROCESSOR_FUNC_EMXAPI_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"

// Function Declarations
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for xtc_processor_func_emxAPI.h
//
// [EOF]
//
