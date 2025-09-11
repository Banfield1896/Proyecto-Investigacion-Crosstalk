//
// AsyncBuffer.h
//
// Code generation for function 'AsyncBuffer'
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void read(int numRows, ::coder::array<double, 1U> &out);
  void write(const ::coder::array<double, 1U> &in);
  boolean_T matlabCodegenIsDeleted;
  internal::AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
// End of code generation (AsyncBuffer.h)
