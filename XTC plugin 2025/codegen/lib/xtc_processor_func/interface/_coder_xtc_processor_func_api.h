//
// _coder_xtc_processor_func_api.h
//
// Code generation for function 'xtc_processor_func'
//

#ifndef _CODER_XTC_PROCESSOR_FUNC_API_H
#define _CODER_XTC_PROCESSOR_FUNC_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Type Definitions
typedef struct {
  real_T D;
  real_T dp;
  real_T b_do;
  real_T beta;
  real_T SampleRate;
} struct0_T;

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void xtc_processor_func(coder::array<real_T, 2U> *in, struct0_T *params,
                        coder::array<real_T, 2U> *out);

void xtc_processor_func_api(const mxArray *const prhs[2], const mxArray **plhs);

void xtc_processor_func_atexit();

void xtc_processor_func_initialize();

void xtc_processor_func_terminate();

void xtc_processor_func_xil_shutdown();

void xtc_processor_func_xil_terminate();

#endif
// End of code generation (_coder_xtc_processor_func_api.h)
