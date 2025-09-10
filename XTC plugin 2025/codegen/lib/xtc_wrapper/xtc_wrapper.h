//
// xtc_wrapper.h
//
// Code generation for function 'xtc_wrapper'
//

#ifndef XTC_WRAPPER_H
#define XTC_WRAPPER_H

// Include files
#include "rtwtypes.h"
#include "xtc_wrapper_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void xtc_wrapper(const coder::array<double, 2U> &in,
                        const struct0_T *params, coder::array<double, 2U> &out);

void xtc_wrapper_free();

void xtc_wrapper_init();

#endif
// End of code generation (xtc_wrapper.h)
