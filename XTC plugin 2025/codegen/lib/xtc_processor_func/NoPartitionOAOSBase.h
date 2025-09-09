//
// File: NoPartitionOAOSBase.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef NOPARTITIONOAOSBASE_H
#define NOPARTITIONOAOSBASE_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"

// Function Declarations
extern void NoPartitionOAOSBase_resetImpl(dsp_private_NoPartitionOS *obj);
extern void NoPartitionOAOSBase_stepImpl(dsp_private_NoPartitionOS *obj, const
  emxArray_real_T *u, emxArray_real_T *y);

#endif

//
// File trailer for NoPartitionOAOSBase.h
//
// [EOF]
//
