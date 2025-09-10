//
// AsyncBuffercgHelper.h
//
// Code generation for function 'AsyncBuffercgHelper'
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include files
#include "rtwtypes.h"
#include "xtc_processor_func_internal_types.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
namespace internal {
class AsyncBuffercgHelper {
public:
  void matlabCodegenDestructor();
  ~AsyncBuffercgHelper();
  AsyncBuffercgHelper();
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  double Cache[8194];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

} // namespace internal
} // namespace dsp
} // namespace coder

#endif
// End of code generation (AsyncBuffercgHelper.h)
