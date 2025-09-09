//
// File: circshift.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "circshift.h"

// Function Definitions

//
// Arguments    : double a[8192]
//                double p
// Return Type  : void
//
void circshift(double a[8192], double p)
{
  int ns;
  boolean_T shiftright;
  double unusedU0[4096];
  int k;
  if (p < 0.0) {
    ns = (int)-p;
    shiftright = false;
  } else {
    ns = (int)p;
    shiftright = true;
  }

  if (ns > 8192) {
    ns -= (ns / 8192) << 13;
  }

  if (ns > 4096) {
    ns = 8192 - ns;
    shiftright = !shiftright;
  }

  memset(&unusedU0[0], 0, sizeof(double) << 12);
  if (ns > 0) {
    if (shiftright) {
      for (k = 1; k <= ns; k++) {
        unusedU0[k - 1] = a[(k - ns) + 8191];
      }

      for (k = 8191; k + 1 >= ns + 1; k--) {
        a[k] = a[k - ns];
      }

      for (k = 0; k + 1 <= ns; k++) {
        a[k] = unusedU0[k];
      }
    } else {
      for (k = 0; k + 1 <= ns; k++) {
        unusedU0[k] = a[k];
      }

      for (k = 0; k + 1 <= 8192 - ns; k++) {
        a[k] = a[k + ns];
      }

      for (k = 1; k <= ns; k++) {
        a[(k - ns) + 8191] = unusedU0[k - 1];
      }
    }
  }
}

//
// File trailer for circshift.cpp
//
// [EOF]
//
