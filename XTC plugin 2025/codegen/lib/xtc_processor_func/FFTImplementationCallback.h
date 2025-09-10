//
// FFTImplementationCallback.h
//
// Code generation for function 'FFTImplementationCallback'
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class FFTImplementationCallback {
public:
  static void generate_twiddle_tables(double costab[8193], double sintab[8193]);
  static void doHalfLengthRadix2(const double x[8192],
                                 const double costab[8193],
                                 const double sintab[8193], creal_T y[16384]);
  static void doHalfLengthRadix2(const ::coder::array<double, 1U> &x,
                                 creal_T y[16384], const double costab[8193],
                                 const double sintab[8193]);

protected:
  static void get_bitrevIndex(int bitrevIndex[8192]);
  static void getback_radix2_fft(creal_T y[16384],
                                 const creal_T reconVar1[8192],
                                 const creal_T reconVar2[8192],
                                 const int wrapIndex[8192]);
};

} // namespace internal
} // namespace coder

#endif
// End of code generation (FFTImplementationCallback.h)
