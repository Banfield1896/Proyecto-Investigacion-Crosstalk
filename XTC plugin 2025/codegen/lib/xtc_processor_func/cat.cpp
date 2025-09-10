//
// cat.cpp
//
// Code generation for function 'cat'
//

// Include files
#include "cat.h"
#include "coder_array.h"

// Function Definitions
void binary_expand_op(coder::array<double, 2U> &out,
                      const coder::array<double, 1U> &y_LL,
                      const coder::array<double, 1U> &y_RL,
                      const coder::array<double, 1U> &y_LR,
                      const coder::array<double, 1U> &y_RR)
{
  coder::array<double, 1U> b_y_LL;
  coder::array<double, 1U> b_y_LR;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (y_RL.size(0) == 1) {
    i = y_LL.size(0);
  } else {
    i = y_RL.size(0);
  }
  b_y_LL.set_size(i);
  stride_0_0 = (y_LL.size(0) != 1);
  stride_1_0 = (y_RL.size(0) != 1);
  if (y_RL.size(0) == 1) {
    loop_ub = y_LL.size(0);
  } else {
    loop_ub = y_RL.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_y_LL[i] = y_LL[i * stride_0_0] + y_RL[i * stride_1_0];
  }
  if (y_RR.size(0) == 1) {
    i = y_LR.size(0);
  } else {
    i = y_RR.size(0);
  }
  b_y_LR.set_size(i);
  stride_0_0 = (y_LR.size(0) != 1);
  stride_1_0 = (y_RR.size(0) != 1);
  if (y_RR.size(0) == 1) {
    loop_ub = y_LR.size(0);
  } else {
    loop_ub = y_RR.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_y_LR[i] = y_LR[i * stride_0_0] + y_RR[i * stride_1_0];
  }
  out.set_size(b_y_LL.size(0), 2);
  loop_ub = b_y_LL.size(0);
  for (i = 0; i < loop_ub; i++) {
    out[i] = b_y_LL[i];
  }
  loop_ub = b_y_LR.size(0);
  for (i = 0; i < loop_ub; i++) {
    out[i + out.size(0)] = b_y_LR[i];
  }
}

// End of code generation (cat.cpp)
