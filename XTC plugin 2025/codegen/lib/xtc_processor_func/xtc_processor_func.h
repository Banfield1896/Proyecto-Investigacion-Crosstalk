//
// xtc_processor_func.h
//
// Code generation for function 'xtc_processor_func'
//

#ifndef XTC_PROCESSOR_FUNC_H
#define XTC_PROCESSOR_FUNC_H

// Include files
#include "rtwtypes.h"
#include "xtc_processor_func_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void isInitialized_not_empty_init();

extern void xtc_processor_func(const coder::array<double, 2U> &in,
                               const struct0_T *params,
                               coder::array<double, 2U> &out);

void xtc_processor_func_free();

void xtc_processor_func_init();

#endif
// End of code generation (xtc_processor_func.h)
