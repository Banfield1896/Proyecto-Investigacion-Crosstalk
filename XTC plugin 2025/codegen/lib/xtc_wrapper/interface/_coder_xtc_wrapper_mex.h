//
// _coder_xtc_wrapper_mex.h
//
// Code generation for function 'xtc_wrapper'
//

#ifndef _CODER_XTC_WRAPPER_MEX_H
#define _CODER_XTC_WRAPPER_MEX_H

// Include files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_xtc_wrapper_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                    int32_T nrhs, const mxArray *prhs[2]);

#endif
// End of code generation (_coder_xtc_wrapper_mex.h)
