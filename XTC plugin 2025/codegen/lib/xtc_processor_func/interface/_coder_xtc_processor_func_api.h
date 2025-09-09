/*
 * File: _coder_xtc_processor_func_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 07-Sep-2025 14:36:14
 */

#ifndef _CODER_XTC_PROCESSOR_FUNC_API_H
#define _CODER_XTC_PROCESSOR_FUNC_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_xtc_processor_func_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  real_T D;
  real_T dp;
  real_T b_do;
  real_T beta;
  real_T SampleRate;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void xtc_processor_func(emxArray_real_T *in, struct0_T *params,
  emxArray_real_T *out);
extern void xtc_processor_func_api(const mxArray * const prhs[2], const mxArray *
  plhs[1]);
extern void xtc_processor_func_atexit(void);
extern void xtc_processor_func_initialize(void);
extern void xtc_processor_func_terminate(void);
extern void xtc_processor_func_xil_terminate(void);

#endif

/*
 * File trailer for _coder_xtc_processor_func_api.h
 *
 * [EOF]
 */
