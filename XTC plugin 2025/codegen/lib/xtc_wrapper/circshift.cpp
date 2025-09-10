//
// circshift.cpp
//
// Code generation for function 'circshift'
//

// Include files
#include "circshift.h"
#include <algorithm>
#include <cstring>

// Function Definitions
namespace coder {
void circshift(double a[8192], double p)
{
  double a__1[4096];
  int ns;
  boolean_T shiftright;
  if (p < 0.0) {
    ns = static_cast<int>(-p);
    shiftright = false;
  } else {
    ns = static_cast<int>(p);
    shiftright = true;
  }
  if (ns > 8192) {
    ns -= (ns / 8192) << 13;
  }
  if (ns > 4096) {
    ns = 8192 - ns;
    shiftright = !shiftright;
  }
  std::memset(&a__1[0], 0, 4096U * sizeof(double));
  if (ns > 0) {
    if (shiftright) {
      int i;
      int k;
      for (k = 0; k < ns; k++) {
        a__1[k] = a[(k - ns) + 8192];
      }
      i = ns + 1;
      for (k = 8192; k >= i; k--) {
        a[k - 1] = a[(k - ns) - 1];
      }
      if (0 <= ns - 1) {
        std::copy(&a__1[0], &a__1[ns], &a[0]);
      }
    } else {
      int i;
      int k;
      if (0 <= ns - 1) {
        std::copy(&a[0], &a[ns], &a__1[0]);
      }
      i = 8191 - ns;
      for (k = 0; k <= i; k++) {
        a[k] = a[k + ns];
      }
      for (k = 0; k < ns; k++) {
        a[(k - ns) + 8192] = a__1[k];
      }
    }
  }
}

} // namespace coder

// End of code generation (circshift.cpp)
