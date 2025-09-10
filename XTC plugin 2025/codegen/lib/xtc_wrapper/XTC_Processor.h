//
// XTC_Processor.h
//
// Code generation for function 'XTC_Processor'
//

#ifndef XTC_PROCESSOR_H
#define XTC_PROCESSOR_H

// Include files
#include "FrequencyDomainFIRFilter.h"
#include "rtwtypes.h"
#include "xtc_wrapper_types.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class XTC_Processor {
public:
  void recalculateFilters(double params_D, double params_dp, double params_do,
                          double params_beta, double params_SampleRate);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  coder::dsp::FrequencyDomainFIRFilter pFilter_LL;
  coder::dsp::FrequencyDomainFIRFilter pFilter_RL;
  coder::dsp::FrequencyDomainFIRFilter pFilter_LR;
  coder::dsp::FrequencyDomainFIRFilter pFilter_RR;
  struct0_T pLastParams;
};

#endif
// End of code generation (XTC_Processor.h)
