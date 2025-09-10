//
// xtc_wrapper.cpp
//
// Code generation for function 'xtc_wrapper'
//

// Include files
#include "xtc_wrapper.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "FrequencyDomainFIRFilter.h"
#include "NoPartitionOS.h"
#include "XTC_Processor.h"
#include "cat.h"
#include "xtc_wrapper_data.h"
#include "xtc_wrapper_initialize.h"
#include "xtc_wrapper_types.h"
#include "coder_array.h"

// Variable Definitions
static XTC_Processor processor;

static boolean_T processor_not_empty;

// Function Definitions
void xtc_wrapper(const coder::array<double, 2U> &in, const struct0_T *params,
                 coder::array<double, 2U> &out)
{
  coder::array<double, 1U> b_in;
  coder::array<double, 1U> y_LL;
  coder::array<double, 1U> y_LR;
  coder::array<double, 1U> y_RL;
  coder::array<double, 1U> y_RR;
  double varargin_1_D;
  double varargin_1_SampleRate;
  double varargin_1_beta;
  double varargin_1_do;
  double varargin_1_dp;
  int i;
  int loop_ub;
  if (!isInitialized_xtc_wrapper) {
    xtc_wrapper_initialize();
  }
  // xtc_wrapper Entry-point function for MATLAB Coder.
  //    This function creates and manages a persistent instance of the
  //    XTC_Processor class.
  //  Declare 'processor' as persistent so it retains its state
  //  between calls.
  //  On the very first call, create and initialize the processor object.
  if (!processor_not_empty) {
    //  --- CONSTRUCTOR ---
    processor.isInitialized = 0;
    //  The constructor pre-initializes the filter properties.
    //  This tells MATLAB Coder the exact class of each property upfront,
    //  preventing type-mismatch errors during code generation.
    processor.pFilter_LL.NumChannels = -1;
    processor.pFilter_LL.isInitialized = 0;
    processor.pFilter_LL.matlabCodegenIsDeleted = false;
    processor.pFilter_RL.NumChannels = -1;
    processor.pFilter_RL.isInitialized = 0;
    processor.pFilter_RL.matlabCodegenIsDeleted = false;
    processor.pFilter_LR.NumChannels = -1;
    processor.pFilter_LR.isInitialized = 0;
    processor.pFilter_LR.matlabCodegenIsDeleted = false;
    processor.pFilter_RR.NumChannels = -1;
    processor.pFilter_RR.isInitialized = 0;
    processor.pFilter_RR.matlabCodegenIsDeleted = false;
    processor.pLastParams.D = 0.0;
    processor.pLastParams.dp = 0.0;
    processor.pLastParams.b_do = 0.0;
    processor.pLastParams.beta = 0.0;
    processor.pLastParams.SampleRate = 0.0;
    processor.matlabCodegenIsDeleted = false;
    processor_not_empty = true;
    //  The setup method will be called automatically by Coder before the
    //  first call to 'step'.
  }
  //  Call the step method of the processor object.
  //  The XTC_Processor class itself will handle checking if parameters
  //  have changed and recalculating the filters if necessary.
  if (processor.isInitialized != 1) {
    processor.isSetupComplete = false;
    processor.isInitialized = 1;
    //  --- SETUP ---
    //  Called once at the beginning. We do an initial calculation here.
    processor.recalculateFilters(params->D, params->dp, params->b_do,
                                 params->beta, params->SampleRate);
    processor.isSetupComplete = true;
  }
  //  --- PROCESS ---
  //  Called for each block of audio.
  //  --- Parameter Update Check ---
  //  This is the standard way to handle tunable parameters.
  //  We only recalculate the filters if the params struct has changed.
  varargin_1_D = processor.pLastParams.D;
  varargin_1_dp = processor.pLastParams.dp;
  varargin_1_do = processor.pLastParams.b_do;
  varargin_1_beta = processor.pLastParams.beta;
  varargin_1_SampleRate = processor.pLastParams.SampleRate;
  if ((!(varargin_1_SampleRate == params->SampleRate)) ||
      (!(varargin_1_beta == params->beta)) ||
      (!(varargin_1_do == params->b_do)) || (!(varargin_1_dp == params->dp)) ||
      (!(varargin_1_D == params->D))) {
    processor.recalculateFilters(params->D, params->dp, params->b_do,
                                 params->beta, params->SampleRate);
    processor.pLastParams = *params;
  }
  //  --- Audio Processing ---
  //  Process each path through its dedicated filter
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i];
  }
  processor.pFilter_LL.step(b_in, y_LL);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i];
  }
  processor.pFilter_RL.step(b_in, y_RL);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i + in.size(0)];
  }
  processor.pFilter_LR.step(b_in, y_LR);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i + in.size(0)];
  }
  processor.pFilter_RR.step(b_in, y_RR);
  //  Combine the results
  if ((y_LL.size(0) == y_LR.size(0)) && (y_RL.size(0) == y_RR.size(0))) {
    out.set_size(y_LL.size(0), 2);
    loop_ub = y_LL.size(0);
    for (i = 0; i < loop_ub; i++) {
      out[i] = y_LL[i] + y_LR[i];
    }
    loop_ub = y_RL.size(0);
    for (i = 0; i < loop_ub; i++) {
      out[i + out.size(0)] = y_RL[i] + y_RR[i];
    }
  } else {
    binary_expand_op(out, y_LL, y_LR, y_RL, y_RR);
  }
}

void xtc_wrapper_free()
{
  coder::dsp::AsyncBuffer *c_obj;
  coder::dsp::FrequencyDomainFIRFilter *obj;
  coder::dsp::internal::NoPartitionOS *b_obj;
  if (!processor.matlabCodegenIsDeleted) {
    processor.matlabCodegenIsDeleted = true;
    if (processor.isInitialized == 1) {
      processor.isInitialized = 2;
    }
  }
  obj = &processor.pFilter_LL;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        if (obj->pFilter.isInitialized == 1) {
          obj->pFilter.isInitialized = 2;
        }
        obj->NumChannels = -1;
      }
    }
  }
  obj = &processor.pFilter_RL;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        if (obj->pFilter.isInitialized == 1) {
          obj->pFilter.isInitialized = 2;
        }
        obj->NumChannels = -1;
      }
    }
  }
  obj = &processor.pFilter_LR;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        if (obj->pFilter.isInitialized == 1) {
          obj->pFilter.isInitialized = 2;
        }
        obj->NumChannels = -1;
      }
    }
  }
  obj = &processor.pFilter_RR;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        if (obj->pFilter.isInitialized == 1) {
          obj->pFilter.isInitialized = 2;
        }
        obj->NumChannels = -1;
      }
    }
  }
  b_obj = &processor.pFilter_LL.pFilter;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
    }
  }
  b_obj = &processor.pFilter_RL.pFilter;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
    }
  }
  b_obj = &processor.pFilter_LR.pFilter;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
    }
  }
  b_obj = &processor.pFilter_RR.pFilter;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
    }
  }
  c_obj = &processor.pFilter_LL.pFilter.pinBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_LL.pFilter.poutBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_RL.pFilter.pinBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_RL.pFilter.poutBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_LR.pFilter.pinBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_LR.pFilter.poutBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_RR.pFilter.pinBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  c_obj = &processor.pFilter_RR.pFilter.poutBuff;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
  }
  processor.pFilter_LL.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_LL.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_RL.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_RL.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_LR.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_LR.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_RR.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  processor.pFilter_RR.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
}

void xtc_wrapper_init()
{
  processor_not_empty = false;
  processor.pFilter_RR.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_RR.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  processor.pFilter_RR.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_RR.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  processor.pFilter_RR.pFilter.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.pFilter.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.pFilter.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.pFilter.matlabCodegenIsDeleted = true;
  processor.pFilter_RR.matlabCodegenIsDeleted = true;
  processor.pFilter_LR.matlabCodegenIsDeleted = true;
  processor.pFilter_RL.matlabCodegenIsDeleted = true;
  processor.pFilter_LL.matlabCodegenIsDeleted = true;
  processor.matlabCodegenIsDeleted = true;
}

// End of code generation (xtc_wrapper.cpp)
