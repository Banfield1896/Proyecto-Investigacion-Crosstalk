//
// File: squeeze.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "squeeze.h"

// Function Definitions

//
// Arguments    : const creal_T a[4095]
//                creal_T b[4095]
// Return Type  : void
//
void b_squeeze(const creal_T a[4095], creal_T b[4095])
{
  memcpy(&b[0], &a[0], 4095U * sizeof(creal_T));
}

//
// Arguments    : const creal_T a[4096]
//                creal_T b[4096]
// Return Type  : void
//
void squeeze(const creal_T a[4096], creal_T b[4096])
{
  memcpy(&b[0], &a[0], sizeof(creal_T) << 12);
}

//
// File trailer for squeeze.cpp
//
// [EOF]
//
