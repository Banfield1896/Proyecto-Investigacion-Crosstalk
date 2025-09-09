//
// File: FrequencyDomainFIRFilter.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "FrequencyDomainFIRFilter.h"

// Function Definitions

//
// Arguments    : dsp_FrequencyDomainFIRFilter *obj
//                const double value[8192]
// Return Type  : void
//
void c_FrequencyDomainFIRFilter_set_(dsp_FrequencyDomainFIRFilter *obj, const
  double value[8192])
{
  int i3;
  for (i3 = 0; i3 < 8192; i3++) {
    obj->Numerator[i3] = value[i3];
  }
}

//
// File trailer for FrequencyDomainFIRFilter.cpp
//
// [EOF]
//
