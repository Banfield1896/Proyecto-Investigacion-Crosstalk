//
// xtc_wrapper_terminate.cpp
//
// Code generation for function 'xtc_wrapper_terminate'
//

// Include files
#include "xtc_wrapper_terminate.h"
#include "xtc_wrapper.h"
#include "xtc_wrapper_data.h"

// Function Definitions
void xtc_wrapper_terminate()
{
  xtc_wrapper_free();
  isInitialized_xtc_wrapper = false;
}

// End of code generation (xtc_wrapper_terminate.cpp)
