//
// AsyncBuffer.cpp
//
// Code generation for function 'AsyncBuffer'
//

// Include files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "xtc_processor_func_internal_types.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
namespace dsp {
void AsyncBuffer::read(int numRows, ::coder::array<double, 1U> &out)
{
  array<double, 1U> b_out;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int y_data[8194];
  int b_qY;
  int b_wPtr;
  int c;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  b_wPtr = pBuffer.WritePointer;
  qY = 0;
  if (rPtr > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr++;
  }
  if (rPtr > 8194) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (numRows < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (numRows > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + numRows;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  c = b_qY;
  if (b_qY > 8194) {
    int k;
    c = b_qY - 8194;
    n = 8195 - rPtr;
    y_data[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    y.set_size(1, b_qY - 8194);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    readIdx.set_size(1, (y.size(1) - rPtr) + 8195);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y_data[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[(yk - rPtr) + 8195] = y[yk];
    }
    if (rPtr <= b_wPtr) {
      if (b_wPtr < -2147475453) {
        qY = MAX_int32_T;
      } else {
        qY = 8194 - b_wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 8194 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 8194 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 8194;
      }
    } else if (b_wPtr <= b_qY - 8194) {
      if (b_wPtr < b_qY + 2147475455) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - b_wPtr) - 8194;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
    }
    if (n > 0) {
      y_data[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    readIdx.set_size(1, n);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y_data[yk];
    }
    if ((rPtr <= b_wPtr) && (b_wPtr <= b_qY)) {
      if ((b_qY >= 0) && (b_wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (b_wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= b_wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    b_out[yk] = pBuffer.Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if ((numRows >= 0) && (qY < numRows - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRows < 0) && (qY > numRows - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRows - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > numRows) {
      b_qY = 1;
    }
    for (yk = 0; yk < qY; yk++) {
      b_out[(b_qY + yk) - 1] = 0.0;
    }
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (yk = 0; yk < n; yk++) {
    out[yk] = b_out[yk];
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  pBuffer.CumulativeUnderrun = b_qY;
  if (wPtr < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY = wPtr - 1;
  }
  if (qY != 0) {
    pBuffer.ReadPointer = b_qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

void AsyncBuffer::write(const ::coder::array<double, 1U> &in)
{
  internal::AsyncBuffercgHelper *obj;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<short, 1U> r;
  cell_wrap_2 varSizes;
  int y_data[8194];
  unsigned int inSize[8];
  int b_qY;
  int c;
  int i;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    pBuffer.isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(in.size(0));
    varSizes.f1[1] = 1U;
    for (yk = 0; yk < 6; yk++) {
      varSizes.f1[yk + 2] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 8194; i++) {
      pBuffer.Cache[i] = 0.0;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      pBuffer.Cache[i] = 0.0;
    }
  }
  inSize[0] = static_cast<unsigned int>(in.size(0));
  inSize[1] = 1U;
  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (obj->inputVarSize[0].f1[k] != inSize[k]) {
      for (yk = 0; yk < 8; yk++) {
        obj->inputVarSize[0].f1[yk] = inSize[yk];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 0) && (in.size(0) < MIN_int32_T - wPtr)) {
    b_qY = MIN_int32_T;
  } else if ((wPtr > 0) && (in.size(0) > MAX_int32_T - wPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + in.size(0);
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  c = b_qY;
  if (b_qY > 8194) {
    c = b_qY - 8194;
    i = 8195 - wPtr;
    y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= i; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    y.set_size(1, b_qY - 8194);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    bc.set_size(1, (y.size(1) - wPtr) + 8195);
    for (yk = 0; yk < i; yk++) {
      bc[yk] = y_data[yk];
    }
    i = y.size(1);
    for (yk = 0; yk < i; yk++) {
      bc[(yk - wPtr) + 8195] = y[yk];
    }
    if (wPtr <= rPtr) {
      if (rPtr < -2147475453) {
        qY = MAX_int32_T;
      } else {
        qY = 8194 - rPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 8194 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 8194 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 8194;
      }
    } else if (rPtr <= b_qY - 8194) {
      if (rPtr < b_qY + 2147475455) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 8194;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY < wPtr) {
      i = 0;
    } else {
      i = (b_qY - wPtr) + 1;
    }
    if (i > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= i; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    bc.set_size(1, i);
    for (yk = 0; yk < i; yk++) {
      bc[yk] = y_data[yk];
    }
    if ((wPtr <= rPtr) && (rPtr <= b_qY)) {
      if ((b_qY >= 0) && (rPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (rPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= rPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (yk = 0; yk < i; yk++) {
    r[yk] = static_cast<short>(static_cast<short>(bc[yk]) - 1);
  }
  i = in.size(0);
  for (yk = 0; yk < i; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 8194) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  i = pBuffer.CumulativeOverrun;
  if ((i < 0) && (qY < MIN_int32_T - i)) {
    b_qY = MIN_int32_T;
  } else if ((i > 0) && (qY > MAX_int32_T - i)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = i + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

} // namespace dsp
} // namespace coder

// End of code generation (AsyncBuffer.cpp)
