//
// _coder_xtc_processor_func_mex.cpp
//
// Code generation for function 'xtc_processor_func'
//

// Include files
#include "_coder_xtc_processor_func_mex.h"
#include "_coder_xtc_processor_func_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&xtc_processor_func_atexit);
  // Module initialization.
  xtc_processor_func_initialize();
  try {
    emlrtShouldCleanupOnError((emlrtCTX *)emlrtRootTLSGlobal, false);
    // Dispatch the entry-point.
    unsafe_xtc_processor_func_mexFunction(nlhs, plhs, nrhs, prhs);
    // Module termination.
    xtc_processor_func_terminate();
  } catch (...) {
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2021a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr);
  return emlrtRootTLSGlobal;
}

void unsafe_xtc_processor_func_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                           int32_T nrhs, const mxArray *prhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        18, "xtc_processor_func");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "xtc_processor_func");
  }
  // Call the function.
  xtc_processor_func_api(prhs, &outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

// End of code generation (_coder_xtc_processor_func_mex.cpp)
