//
// AsyncBuffercgHelper.cpp
//
// Code generation for function 'AsyncBuffercgHelper'
//

// Include files
#include "AsyncBuffercgHelper.h"

// Function Definitions
namespace coder {
namespace dsp {
namespace internal {
AsyncBuffercgHelper::AsyncBuffercgHelper()
{
  matlabCodegenIsDeleted = true;
}

AsyncBuffercgHelper::~AsyncBuffercgHelper()
{
  matlabCodegenDestructor();
}

void AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    if (isInitialized == 1) {
      isInitialized = 2;
      if (isSetupComplete) {
        ReadPointer = 1;
        WritePointer = 2;
        CumulativeOverrun = 0;
        CumulativeUnderrun = 0;
        AsyncBuffercgHelper_isInitialized = false;
        NumChannels = -1;
      }
    }
  }
}

} // namespace internal
} // namespace dsp
} // namespace coder

// End of code generation (AsyncBuffercgHelper.cpp)
