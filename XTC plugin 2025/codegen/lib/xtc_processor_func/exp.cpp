//
// File: exp.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "exp.h"

// Function Definitions

//
// Arguments    : creal_T *x
// Return Type  : void
//
void b_exp(creal_T *x)
{
  double r;
  double x_im;
  if (x->im == 0.0) {
    x->re = std::exp(x->re);
    x->im = 0.0;
  } else if (rtIsInf(x->im) && rtIsInf(x->re) && (x->re < 0.0)) {
    x->re = 0.0;
    x->im = 0.0;
  } else {
    r = std::exp(x->re / 2.0);
    x_im = x->im;
    x->re = r * (r * std::cos(x->im));
    x->im = r * (r * std::sin(x_im));
  }
}

//
// File trailer for exp.cpp
//
// [EOF]
//
