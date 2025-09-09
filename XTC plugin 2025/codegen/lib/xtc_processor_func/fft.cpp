//
// File: fft.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "fft.h"

// Function Definitions

//
// Arguments    : double costab[8193]
//                double sintab[8193]
// Return Type  : void
//
void b_generate_twiddle_tables(double costab[8193], double sintab[8193])
{
  double costab1q[4097];
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] = std::cos(0.00038349519697141029 * ((double)k + 1.0));
  }

  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] = std::sin(0.00038349519697141029 * (4096.0 - ((double)k
      + 2049.0)));
  }

  costab1q[4096] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = costab1q[4095 - k];
    costab[k + 4097] = -costab1q[4095 - k];
    sintab[k + 4097] = costab1q[k + 1];
  }
}

//
// Arguments    : double costab[8193]
//                double sintab[8193]
// Return Type  : void
//
void generate_twiddle_tables(double costab[8193], double sintab[8193])
{
  double costab1q[4097];
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] = std::cos(0.00038349519697141029 * ((double)k + 1.0));
  }

  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] = std::sin(0.00038349519697141029 * (4096.0 - ((double)k
      + 2049.0)));
  }

  costab1q[4096] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[4095 - k];
    costab[k + 4097] = -costab1q[4095 - k];
    sintab[k + 4097] = -costab1q[k + 1];
  }
}

//
// File trailer for fft.cpp
//
// [EOF]
//
