//
// FrequencyDomainFIRFilter.h
//
// Code generation for function 'FrequencyDomainFIRFilter'
//

#ifndef FREQUENCYDOMAINFIRFILTER_H
#define FREQUENCYDOMAINFIRFILTER_H

// Include files
#include "NoPartitionOS.h"
#include "rtwtypes.h"
#include "xtc_processor_func_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class FrequencyDomainFIRFilter {
public:
  void step(const ::coder::array<double, 1U> &varargin_1,
            ::coder::array<double, 1U> &varargout_1);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  double Numerator[8192];
  internal::NoPartitionOS pFilter;
  int NumChannels;

private:
  cell_wrap_2 inputVarSize[1];
};

} // namespace dsp
} // namespace coder

#endif
// End of code generation (FrequencyDomainFIRFilter.h)
