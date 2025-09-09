//
// File: SystemCore.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "SystemCore.h"
#include "NoPartitionOAOSBase.h"
#include "fft1.h"
#include "xtc_processor_func_data.h"

// Function Declarations
static void SystemCore_setup(dsp_private_NoPartitionOS *obj);

// Function Definitions

//
// Arguments    : dsp_private_NoPartitionOS *obj
// Return Type  : void
//
static void SystemCore_setup(dsp_private_NoPartitionOS *obj)
{
  static creal_T dcv5[16384];
  int i;
  cell_wrap_2 varSizes[1];
  obj->isInitialized = 1;
  fft(obj->Numerator, dcv5);
  for (i = 0; i < 16384; i++) {
    obj->H[i] = dcv5[i];
  }

  obj->pinBuff.NumChannels = -1;
  obj->pinBuff.ReadPointer = 1;
  obj->pinBuff.WritePointer = 2;
  obj->pinBuff.CumulativeUnderrun = 0;
  obj->pinBuff.isInitialized = 0;
  obj->pinBuff.isInitialized = 1;
  for (i = 0; i < 8; i++) {
    varSizes[0].f1[i] = (unsigned int)iv0[i];
  }

  obj->pinBuff.inputVarSize[0] = varSizes[0];
  obj->pinBuff.NumChannels = 1;
  obj->pinBuff.AsyncBuffer_isInitialized = true;
  for (i = 0; i < 8194; i++) {
    obj->pinBuff.Cache[i] = 0.0;
  }

  obj->poutBuff.NumChannels = -1;
  obj->poutBuff.ReadPointer = 1;
  obj->poutBuff.WritePointer = 2;
  obj->poutBuff.CumulativeUnderrun = 0;
  obj->poutBuff.isInitialized = 0;
  for (i = 0; i < 8191; i++) {
    obj->pLastSection[i] = 0.0;
  }

  obj->TunablePropsChanged = false;
}

//
// Arguments    : dsp_FrequencyDomainFIRFilter *obj
//                const emxArray_real_T *varargin_1
//                emxArray_real_T *varargout_1
// Return Type  : void
//
void SystemCore_step(dsp_FrequencyDomainFIRFilter *obj, const emxArray_real_T
                     *varargin_1, emxArray_real_T *varargout_1)
{
  unsigned int b_varargin_1[2];
  boolean_T flag;
  int k;
  cell_wrap_2 varSizes[1];
  unsigned int inSize[8];
  boolean_T exitg1;
  static double varargin_2[8192];
  static creal_T dcv4[16384];
  if (obj->isInitialized != 1) {
    obj->isInitialized = 1;
    b_varargin_1[0] = (unsigned int)varargin_1->size[0];
    b_varargin_1[1] = 1U;
    for (k = 0; k < 2; k++) {
      varSizes[0].f1[k] = b_varargin_1[k];
    }

    for (k = 0; k < 6; k++) {
      varSizes[0].f1[k + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    obj->NumChannels = 1;
    for (k = 0; k < 8192; k++) {
      varargin_2[k] = obj->Numerator[k];
    }

    obj->pFilter.isInitialized = 0;
    flag = (obj->pFilter.isInitialized == 1);
    if (flag) {
      obj->pFilter.TunablePropsChanged = true;
    }

    for (k = 0; k < 8192; k++) {
      obj->pFilter.Numerator[k] = varargin_2[k];
    }

    SystemCore_setup(&obj->pFilter);
    obj->TunablePropsChanged = false;
    if (obj->pFilter.isInitialized == 1) {
      NoPartitionOAOSBase_resetImpl(&obj->pFilter);
    }
  }

  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    flag = (obj->pFilter.isInitialized == 1);
    if (flag) {
      obj->pFilter.TunablePropsChanged = true;
    }

    for (k = 0; k < 8192; k++) {
      obj->pFilter.Numerator[k] = obj->Numerator[k];
    }
  }

  b_varargin_1[0] = (unsigned int)varargin_1->size[0];
  b_varargin_1[1] = 1U;
  for (k = 0; k < 2; k++) {
    inSize[k] = b_varargin_1[k];
  }

  for (k = 0; k < 6; k++) {
    inSize[k + 2] = 1U;
  }

  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (obj->inputVarSize[0].f1[k] != inSize[k]) {
      for (k = 0; k < 8; k++) {
        obj->inputVarSize[0].f1[k] = inSize[k];
      }

      exitg1 = true;
    } else {
      k++;
    }
  }

  if (obj->pFilter.isInitialized != 1) {
    SystemCore_setup(&obj->pFilter);
    NoPartitionOAOSBase_resetImpl(&obj->pFilter);
  }

  if (obj->pFilter.TunablePropsChanged) {
    obj->pFilter.TunablePropsChanged = false;
    fft(obj->pFilter.Numerator, dcv4);
    for (k = 0; k < 16384; k++) {
      obj->pFilter.H[k] = dcv4[k];
    }
  }

  NoPartitionOAOSBase_stepImpl(&obj->pFilter, varargin_1, varargout_1);
}

//
// File trailer for SystemCore.cpp
//
// [EOF]
//
