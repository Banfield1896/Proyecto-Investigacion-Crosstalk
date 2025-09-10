//
// _coder_xtc_wrapper_api.h
//
// Code generation for function 'xtc_wrapper'
//

#ifndef _CODER_XTC_WRAPPER_API_H
#define _CODER_XTC_WRAPPER_API_H

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
void xtc_wrapper(coder::array<real_T, 2U> *in, struct0_T *params,
                 coder::array<real_T, 2U> *out);

void xtc_wrapper_api(const mxArray *const prhs[2], const mxArray **plhs);

void xtc_wrapper_atexit();

void xtc_wrapper_initialize();

void xtc_wrapper_terminate();

void xtc_wrapper_xil_shutdown();

void xtc_wrapper_xil_terminate();

#endif
// End of code generation (_coder_xtc_wrapper_api.h)
