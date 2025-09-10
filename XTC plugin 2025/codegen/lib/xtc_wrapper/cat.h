//
// cat.h
//
// Code generation for function 'cat'
//

#ifndef CAT_H
#define CAT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void binary_expand_op(coder::array<double, 2U> &out,
                      const coder::array<double, 1U> &y_LL,
                      const coder::array<double, 1U> &y_LR,
                      const coder::array<double, 1U> &y_RL,
                      const coder::array<double, 1U> &y_RR);

#endif
// End of code generation (cat.h)
