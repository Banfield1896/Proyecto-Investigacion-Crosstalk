//
// NoPartitionOS.h
//
// Code generation for function 'NoPartitionOS'
//

#ifndef NOPARTITIONOS_H
#define NOPARTITIONOS_H

// Include files
#include "AsyncBuffer.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
namespace internal {
class NoPartitionOS {
public:
  void setup();
  void resetImpl();
  static void computeOutput(const ::coder::array<double, 1U> &input,
                            double numFrames, const creal_T pH[16384],
                            double prevsec[8191],
                            ::coder::array<double, 1U> &o);
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T TunablePropsChanged;
  double Numerator[8192];
  double pLastSection[8191];
  creal_T H[16384];
  AsyncBuffer pinBuff;
  AsyncBuffer poutBuff;

private:
  boolean_T isSetupComplete;
};

} // namespace internal
} // namespace dsp
} // namespace coder

#endif
// End of code generation (NoPartitionOS.h)
