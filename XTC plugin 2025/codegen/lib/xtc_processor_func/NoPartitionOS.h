//
// File: NoPartitionOS.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef NOPARTITIONOS_H
#define NOPARTITIONOS_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"

// Function Declarations
extern void NoPartitionOS_computeOutput(const emxArray_real_T *input, double
  numFrames, const creal_T pH[16384], double prevsec[8191], emxArray_real_T *o);

#endif

//
// File trailer for NoPartitionOS.h
//
// [EOF]
//
