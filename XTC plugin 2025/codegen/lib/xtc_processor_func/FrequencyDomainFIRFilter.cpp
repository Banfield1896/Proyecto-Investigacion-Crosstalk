//
// FrequencyDomainFIRFilter.cpp
//
// Code generation for function 'FrequencyDomainFIRFilter'
//

// Include files
#include "FrequencyDomainFIRFilter.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "FFTImplementationCallback.h"
#include "NoPartitionOS.h"
#include "xtc_processor_func_internal_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace dsp {
void FrequencyDomainFIRFilter::step(
    const ::coder::array<double, 1U> &varargin_1,
    ::coder::array<double, 1U> &varargout_1)
{
  static creal_T pH[16384];
  static double costab[8193];
  static double sintab[8193];
  static double num[8192];
  static double prevsec[8191];
  internal::NoPartitionOS *obj;
  array<double, 1U> b_varargin_1;
  array<double, 1U> input;
  array<double, 1U> r;
  cell_wrap_2 varSizes;
  double inpStart;
  double remSamples;
  double remSamples_tmp;
  unsigned int inSize[8];
  int b_i;
  int i;
  int k;
  unsigned int ns;
  int numFrames;
  int samplesToFill;
  int unreadSamples;
  boolean_T exitg1;
  boolean_T flag;
  if (isInitialized != 1) {
    isSetupComplete = false;
    isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(varargin_1.size(0));
    varSizes.f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes.f1[i + 2] = 1U;
    }
    inputVarSize[0] = varSizes;
    NumChannels = 1;
    for (i = 0; i < 8192; i++) {
      num[i] = Numerator[i];
    }
    pFilter.isInitialized = 0;
    pFilter.isInitialized = 0;
    flag = (pFilter.isInitialized == 1);
    if (flag) {
      pFilter.TunablePropsChanged = true;
    }
    for (i = 0; i < 8192; i++) {
      pFilter.Numerator[i] = num[i];
    }
    pFilter.matlabCodegenIsDeleted = false;
    pFilter.setup();
    isSetupComplete = true;
    TunablePropsChanged = false;
    if (pFilter.isInitialized == 1) {
      pFilter.resetImpl();
    }
  }
  if (TunablePropsChanged) {
    TunablePropsChanged = false;
    flag = (pFilter.isInitialized == 1);
    if (flag) {
      pFilter.TunablePropsChanged = true;
    }
    for (i = 0; i < 8192; i++) {
      pFilter.Numerator[i] = Numerator[i];
    }
  }
  inSize[0] = static_cast<unsigned int>(varargin_1.size(0));
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (inputVarSize[0].f1[k] != inSize[k]) {
      for (i = 0; i < 8; i++) {
        inputVarSize[0].f1[i] = inSize[i];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  obj = &pFilter;
  if (pFilter.isInitialized != 1) {
    pFilter.setup();
    pFilter.resetImpl();
  }
  if (pFilter.TunablePropsChanged) {
    pFilter.TunablePropsChanged = false;
    for (i = 0; i < 8192; i++) {
      num[i] = pFilter.Numerator[i];
    }
    ::coder::internal::FFTImplementationCallback::generate_twiddle_tables(
        costab, sintab);
    ::coder::internal::FFTImplementationCallback::doHalfLengthRadix2(
        num, costab, sintab, pFilter.H);
  }
  k = pFilter.poutBuff.pBuffer.WritePointer;
  numFrames = pFilter.poutBuff.pBuffer.ReadPointer;
  if ((k >= 0) && (numFrames < k - MAX_int32_T)) {
    k = MAX_int32_T;
  } else if ((k < 0) && (numFrames > k - MIN_int32_T)) {
    k = MIN_int32_T;
  } else {
    k -= numFrames;
  }
  if (k < -2147483647) {
    k = MIN_int32_T;
  } else {
    k--;
  }
  numFrames = pFilter.poutBuff.pBuffer.ReadPointer;
  if (numFrames < -2147475454) {
    b_i = MAX_int32_T;
  } else {
    b_i = 8193 - numFrames;
  }
  numFrames = pFilter.poutBuff.pBuffer.WritePointer;
  if ((b_i < 0) && (numFrames < MIN_int32_T - b_i)) {
    b_i = MIN_int32_T;
  } else if ((b_i > 0) && (numFrames > MAX_int32_T - b_i)) {
    b_i = MAX_int32_T;
  } else {
    b_i += numFrames;
  }
  if (pFilter.poutBuff.pBuffer.ReadPointer <
      pFilter.poutBuff.pBuffer.WritePointer) {
    unreadSamples = k;
  } else if (pFilter.poutBuff.pBuffer.ReadPointer ==
             pFilter.poutBuff.pBuffer.WritePointer) {
    unreadSamples = 8193;
  } else {
    unreadSamples = b_i;
  }
  k = pFilter.pinBuff.pBuffer.WritePointer;
  numFrames = pFilter.pinBuff.pBuffer.ReadPointer;
  if ((k >= 0) && (numFrames < k - MAX_int32_T)) {
    k = MAX_int32_T;
  } else if ((k < 0) && (numFrames > k - MIN_int32_T)) {
    k = MIN_int32_T;
  } else {
    k -= numFrames;
  }
  if (k < -2147483647) {
    k = MIN_int32_T;
  } else {
    k--;
  }
  numFrames = pFilter.pinBuff.pBuffer.ReadPointer;
  if (numFrames < -2147475454) {
    b_i = MAX_int32_T;
  } else {
    b_i = 8193 - numFrames;
  }
  numFrames = pFilter.pinBuff.pBuffer.WritePointer;
  if ((b_i < 0) && (numFrames < MIN_int32_T - b_i)) {
    b_i = MIN_int32_T;
  } else if ((b_i > 0) && (numFrames > MAX_int32_T - b_i)) {
    b_i = MAX_int32_T;
  } else {
    b_i += numFrames;
  }
  if (pFilter.pinBuff.pBuffer.ReadPointer >=
      pFilter.pinBuff.pBuffer.WritePointer) {
    if (pFilter.pinBuff.pBuffer.ReadPointer ==
        pFilter.pinBuff.pBuffer.WritePointer) {
      k = 8193;
    } else {
      k = b_i;
    }
  }
  for (b_i = 0; b_i < 8191; b_i++) {
    prevsec[b_i] = pFilter.pLastSection[b_i];
  }
  for (b_i = 0; b_i < 16384; b_i++) {
    pH[b_i] = pFilter.H[b_i];
  }
  numFrames =
      static_cast<int>(std::floor((std::fmin(static_cast<double>(k), 8193.0) +
                                   static_cast<double>(varargin_1.size(0))) /
                                  8193.0));
  input.set_size(8193 * numFrames);
  b_i = 8193 * numFrames;
  for (i = 0; i < b_i; i++) {
    input[i] = 0.0;
  }
  inpStart = 1.0;
  remSamples_tmp = 8193.0 * static_cast<double>(numFrames);
  remSamples = remSamples_tmp;
  if (k > 0) {
    double val;
    val = std::fmin(remSamples_tmp, static_cast<double>(k));
    if (numFrames > 0) {
      if (val >= -2.147483648E+9) {
        i = static_cast<int>(val);
      } else {
        i = MIN_int32_T;
      }
      obj->pinBuff.read(i, r);
      b_i = r.size(0);
      for (i = 0; i < b_i; i++) {
        input[i] = r[i];
      }
      inpStart = val + 1.0;
      remSamples = remSamples_tmp - val;
    }
  }
  if (remSamples > 0.0) {
    if (inpStart > (inpStart + remSamples) - 1.0) {
      i = 1;
    } else {
      i = static_cast<int>(inpStart);
    }
    b_i = static_cast<int>(remSamples);
    for (k = 0; k < b_i; k++) {
      input[(i + k) - 1] = varargin_1[k];
    }
  }
  if (static_cast<unsigned int>(varargin_1.size(0)) > remSamples) {
    if (remSamples + 1.0 > varargin_1.size(0)) {
      i = 0;
      k = 0;
    } else {
      i = static_cast<int>(remSamples + 1.0) - 1;
      k = varargin_1.size(0);
    }
    b_i = k - i;
    b_varargin_1.set_size(b_i);
    for (k = 0; k < b_i; k++) {
      b_varargin_1[k] = varargin_1[i + k];
    }
    obj->pinBuff.write(b_varargin_1);
  }
  varargout_1.set_size(varargin_1.size(0));
  b_i = varargin_1.size(0);
  for (i = 0; i < b_i; i++) {
    varargout_1[i] = 0.0;
  }
  samplesToFill = varargin_1.size(0);
  ns = 1U;
  if (unreadSamples > 0) {
    ns = static_cast<unsigned int>(std::fmin(
        static_cast<double>(static_cast<unsigned int>(varargin_1.size(0))),
        static_cast<double>(unreadSamples)));
    pFilter.poutBuff.read(static_cast<int>(ns), r);
    b_i = r.size(0);
    for (i = 0; i < b_i; i++) {
      varargout_1[i] = r[i];
    }
    samplesToFill = varargin_1.size(0) - static_cast<int>(ns);
    ns++;
  }
  if (numFrames > 0) {
    internal::NoPartitionOS::computeOutput(
        input, static_cast<double>(numFrames), pH, prevsec, b_varargin_1);
    if (1 > samplesToFill) {
      b_i = 0;
    } else {
      b_i = samplesToFill;
    }
    if (ns > static_cast<unsigned int>(varargout_1.size(0))) {
      i = 1;
    } else {
      i = static_cast<int>(ns);
    }
    for (k = 0; k < b_i; k++) {
      varargout_1[(i + k) - 1] = b_varargin_1[k];
    }
    if (samplesToFill < remSamples_tmp) {
      if (static_cast<double>(samplesToFill) + 1.0 > b_varargin_1.size(0)) {
        samplesToFill = 0;
        i = 0;
      } else {
        i = b_varargin_1.size(0);
      }
      k = i - samplesToFill;
      for (i = 0; i < k; i++) {
        b_varargin_1[i] = b_varargin_1[samplesToFill + i];
      }
      b_varargin_1.set_size(k);
      pFilter.poutBuff.write(b_varargin_1);
    }
  }
  for (b_i = 0; b_i < 8191; b_i++) {
    pFilter.pLastSection[b_i] = prevsec[b_i];
  }
}

} // namespace dsp
} // namespace coder

// End of code generation (FrequencyDomainFIRFilter.cpp)
