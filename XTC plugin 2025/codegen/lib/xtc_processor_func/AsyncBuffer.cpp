//
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "AsyncBuffer.h"
#include "xtc_processor_func_emxutil.h"

// Function Definitions

//
// Arguments    : dsp_AsyncBuffer *obj
//                int numRows
//                emxArray_real_T *out
// Return Type  : void
//
void AsyncBuffer_read(dsp_AsyncBuffer *obj, int numRows, emxArray_real_T *out)
{
  int rPtr;
  int wPtr;
  int underrun;
  int yk;
  int c;
  emxArray_int32_T *readIdx;
  int n;
  int y_data[8194];
  int k;
  emxArray_int32_T *y;
  rPtr = obj->ReadPointer;
  wPtr = obj->WritePointer;
  underrun = 0;
  if (rPtr > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr++;
  }

  if (rPtr > 8194) {
    rPtr = 1;
  }

  if ((rPtr < 0) && (numRows < MIN_int32_T - rPtr)) {
    yk = MIN_int32_T;
  } else if ((rPtr > 0) && (numRows > MAX_int32_T - rPtr)) {
    yk = MAX_int32_T;
  } else {
    yk = rPtr + numRows;
  }

  if (yk < -2147483647) {
    c = MIN_int32_T;
  } else {
    c = yk - 1;
  }

  emxInit_int32_T(&readIdx, 2);
  if (c > 8194) {
    c -= 8194;
    y_data[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= 8195 - rPtr; k++) {
      yk++;
      y_data[k - 1] = yk;
    }

    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = c;
    emxEnsureCapacity_int32_T(y, k);
    y->data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y->data[k - 1] = yk;
    }

    k = readIdx->size[0] * readIdx->size[1];
    readIdx->size[0] = 1;
    readIdx->size[1] = (y->size[1] - rPtr) + 8195;
    emxEnsureCapacity_int32_T(readIdx, k);
    yk = 8195 - rPtr;
    for (k = 0; k < yk; k++) {
      readIdx->data[readIdx->size[0] * k] = y_data[k];
    }

    yk = y->size[1];
    for (k = 0; k < yk; k++) {
      readIdx->data[readIdx->size[0] * ((k - rPtr) + 8195)] = y->data[y->size[0]
        * k];
    }

    emxFree_int32_T(&y);
    if (rPtr <= wPtr) {
      if (wPtr < -2147475453) {
        yk = MAX_int32_T;
      } else {
        yk = 8194 - wPtr;
      }

      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }

      if ((yk < 0) && (c < MIN_int32_T - yk)) {
        underrun = MIN_int32_T;
      } else if ((yk > 0) && (c > MAX_int32_T - yk)) {
        underrun = MAX_int32_T;
      } else {
        underrun = yk + c;
      }
    } else {
      if (wPtr <= c) {
        if (wPtr < c - MAX_int32_T) {
          yk = MAX_int32_T;
        } else {
          yk = c - wPtr;
        }

        if (yk > 2147483646) {
          underrun = MAX_int32_T;
        } else {
          underrun = yk + 1;
        }
      }
    }
  } else {
    if (c < rPtr) {
      n = 0;
    } else {
      n = (c - rPtr) + 1;
    }

    if (n > 0) {
      y_data[0] = rPtr;
      yk = rPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }

    k = readIdx->size[0] * readIdx->size[1];
    readIdx->size[0] = 1;
    readIdx->size[1] = n;
    emxEnsureCapacity_int32_T(readIdx, k);
    for (k = 0; k < n; k++) {
      readIdx->data[k] = y_data[k];
    }

    if ((rPtr <= wPtr) && (wPtr <= c)) {
      if ((c >= 0) && (wPtr < c - MAX_int32_T)) {
        yk = MAX_int32_T;
      } else if ((c < 0) && (wPtr > c - MIN_int32_T)) {
        yk = MIN_int32_T;
      } else {
        yk = c - wPtr;
      }

      if (yk > 2147483646) {
        underrun = MAX_int32_T;
      } else {
        underrun = yk + 1;
      }
    }
  }

  k = out->size[0];
  out->size[0] = readIdx->size[1];
  emxEnsureCapacity_real_T(out, k);
  yk = readIdx->size[1];
  for (k = 0; k < yk; k++) {
    out->data[k] = obj->Cache[readIdx->data[readIdx->size[0] * k] - 1];
  }

  emxFree_int32_T(&readIdx);
  if (underrun != 0) {
    if ((numRows >= 0) && (underrun < numRows - MAX_int32_T)) {
      yk = MAX_int32_T;
    } else if ((numRows < 0) && (underrun > numRows - MIN_int32_T)) {
      yk = MIN_int32_T;
    } else {
      yk = numRows - underrun;
    }

    if (yk > 2147483646) {
      yk = MAX_int32_T;
    } else {
      yk++;
    }

    if (yk > numRows) {
      k = 0;
    } else {
      k = yk - 1;
    }

    for (yk = 0; yk < underrun; yk++) {
      out->data[k + yk] = 0.0;
    }

    if (wPtr < -2147483647) {
      rPtr = MIN_int32_T;
    } else {
      rPtr = wPtr - 1;
    }
  } else {
    rPtr = c;
  }

  yk = obj->CumulativeUnderrun;
  if ((yk < 0) && (underrun < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (underrun > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += underrun;
  }

  obj->CumulativeUnderrun = yk;
  obj->ReadPointer = rPtr;
}

//
// Arguments    : dsp_AsyncBuffer *obj
//                const double in[8193]
// Return Type  : void
//
void AsyncBuffer_stepImpl(dsp_AsyncBuffer *obj, const double in[8193])
{
  int wPtr;
  int rPtr;
  int overrun;
  int yk;
  int c;
  emxArray_int32_T *bc;
  int n;
  int y_data[8194];
  int k;
  int i4;
  emxArray_int32_T *y;
  short tmp_data[16386];
  wPtr = obj->WritePointer;
  rPtr = obj->ReadPointer;
  overrun = 0;
  if (wPtr > 2147475454) {
    yk = MAX_int32_T;
  } else {
    yk = wPtr + 8193;
  }

  c = yk - 1;
  emxInit_int32_T(&bc, 2);
  if (c > 8194) {
    c -= 8194;
    y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= 8195 - wPtr; k++) {
      yk++;
      y_data[k - 1] = yk;
    }

    emxInit_int32_T(&y, 2);
    i4 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = c;
    emxEnsureCapacity_int32_T(y, i4);
    y->data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y->data[k - 1] = yk;
    }

    i4 = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = (y->size[1] - wPtr) + 8195;
    emxEnsureCapacity_int32_T(bc, i4);
    k = 8195 - wPtr;
    for (i4 = 0; i4 < k; i4++) {
      bc->data[bc->size[0] * i4] = y_data[i4];
    }

    k = y->size[1];
    for (i4 = 0; i4 < k; i4++) {
      bc->data[bc->size[0] * ((i4 - wPtr) + 8195)] = y->data[y->size[0] * i4];
    }

    emxFree_int32_T(&y);
    if (wPtr <= rPtr) {
      if (rPtr < -2147475453) {
        yk = MAX_int32_T;
      } else {
        yk = 8194 - rPtr;
      }

      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }

      if ((yk < 0) && (c < MIN_int32_T - yk)) {
        overrun = MIN_int32_T;
      } else if ((yk > 0) && (c > MAX_int32_T - yk)) {
        overrun = MAX_int32_T;
      } else {
        overrun = yk + c;
      }
    } else {
      if (rPtr <= c) {
        if (rPtr < c - MAX_int32_T) {
          yk = MAX_int32_T;
        } else {
          yk = c - rPtr;
        }

        if (yk > 2147483646) {
          overrun = MAX_int32_T;
        } else {
          overrun = yk + 1;
        }
      }
    }
  } else {
    if (c < wPtr) {
      n = 0;
    } else {
      n = (c - wPtr) + 1;
    }

    if (n > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }

    i4 = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = n;
    emxEnsureCapacity_int32_T(bc, i4);
    for (i4 = 0; i4 < n; i4++) {
      bc->data[i4] = y_data[i4];
    }

    if ((wPtr <= rPtr) && (rPtr <= c)) {
      if ((c >= 0) && (rPtr < c - MAX_int32_T)) {
        yk = MAX_int32_T;
      } else if ((c < 0) && (rPtr > c - MIN_int32_T)) {
        yk = MIN_int32_T;
      } else {
        yk = c - rPtr;
      }

      if (yk > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = yk + 1;
      }
    }
  }

  yk = bc->size[1];
  k = bc->size[1];
  for (i4 = 0; i4 < k; i4++) {
    tmp_data[i4] = (short)((short)bc->data[bc->size[0] * i4] - 1);
  }

  emxFree_int32_T(&bc);
  for (i4 = 0; i4 < yk; i4++) {
    obj->Cache[tmp_data[i4]] = in[i4];
  }

  if (c + 1 > 8194) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }

  if (overrun != 0) {
    rPtr = wPtr;
  }

  yk = obj->CumulativeOverrun;
  if ((yk < 0) && (overrun < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (overrun > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += overrun;
  }

  obj->CumulativeOverrun = yk;
  obj->WritePointer = wPtr;
  obj->ReadPointer = rPtr;
}

//
// Arguments    : dsp_AsyncBuffer *obj
//                const emxArray_real_T *in
// Return Type  : void
//
void AsyncBuffer_write(dsp_AsyncBuffer *obj, const emxArray_real_T *in)
{
  unsigned int b_in[2];
  int yk;
  unsigned int inSize[8];
  cell_wrap_2 varSizes[1];
  int i;
  boolean_T exitg1;
  int wPtr;
  int rPtr;
  int qY;
  int c;
  emxArray_int32_T *bc;
  int n;
  int y_data[8194];
  emxArray_int32_T *y;
  emxArray_int16_T *r1;
  if (obj->isInitialized != 1) {
    obj->isInitialized = 1;
    b_in[0] = (unsigned int)in->size[0];
    b_in[1] = 1U;
    for (yk = 0; yk < 2; yk++) {
      varSizes[0].f1[yk] = b_in[yk];
    }

    for (yk = 0; yk < 6; yk++) {
      varSizes[0].f1[yk + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    obj->NumChannels = 1;
    obj->AsyncBuffer_isInitialized = true;
    for (i = 0; i < 8194; i++) {
      obj->Cache[i] = 0.0;
    }

    obj->ReadPointer = 1;
    obj->WritePointer = 2;
    obj->CumulativeOverrun = 0;
    obj->CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      obj->Cache[i] = 0.0;
    }
  }

  b_in[0] = (unsigned int)in->size[0];
  b_in[1] = 1U;
  for (yk = 0; yk < 2; yk++) {
    inSize[yk] = b_in[yk];
  }

  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (yk = 0; yk < 8; yk++) {
        obj->inputVarSize[0].f1[yk] = inSize[yk];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  wPtr = obj->WritePointer;
  rPtr = obj->ReadPointer;
  qY = 0;
  i = in->size[0];
  if ((wPtr < 0) && (i < MIN_int32_T - wPtr)) {
    i = MIN_int32_T;
  } else if ((wPtr > 0) && (i > MAX_int32_T - wPtr)) {
    i = MAX_int32_T;
  } else {
    i += wPtr;
  }

  if (i < -2147483647) {
    c = MIN_int32_T;
  } else {
    c = i - 1;
  }

  emxInit_int32_T(&bc, 2);
  if (c > 8194) {
    c -= 8194;
    y_data[0] = wPtr;
    yk = wPtr;
    for (i = 2; i <= 8195 - wPtr; i++) {
      yk++;
      y_data[i - 1] = yk;
    }

    emxInit_int32_T(&y, 2);
    yk = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = c;
    emxEnsureCapacity_int32_T(y, yk);
    y->data[0] = 1;
    yk = 1;
    for (i = 2; i <= c; i++) {
      yk++;
      y->data[i - 1] = yk;
    }

    yk = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = (y->size[1] - wPtr) + 8195;
    emxEnsureCapacity_int32_T(bc, yk);
    i = 8195 - wPtr;
    for (yk = 0; yk < i; yk++) {
      bc->data[bc->size[0] * yk] = y_data[yk];
    }

    i = y->size[1];
    for (yk = 0; yk < i; yk++) {
      bc->data[bc->size[0] * ((yk - wPtr) + 8195)] = y->data[y->size[0] * yk];
    }

    emxFree_int32_T(&y);
    if (wPtr <= rPtr) {
      if (rPtr < -2147475453) {
        i = MAX_int32_T;
      } else {
        i = 8194 - rPtr;
      }

      if (i > 2147483646) {
        i = MAX_int32_T;
      } else {
        i++;
      }

      if ((i < 0) && (c < MIN_int32_T - i)) {
        qY = MIN_int32_T;
      } else if ((i > 0) && (c > MAX_int32_T - i)) {
        qY = MAX_int32_T;
      } else {
        qY = i + c;
      }
    } else {
      if (rPtr <= c) {
        if (rPtr < c - MAX_int32_T) {
          i = MAX_int32_T;
        } else {
          i = c - rPtr;
        }

        if (i > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = i + 1;
        }
      }
    }
  } else {
    if (c < wPtr) {
      n = 0;
    } else {
      n = (c - wPtr) + 1;
    }

    if (n > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (i = 2; i <= n; i++) {
        yk++;
        y_data[i - 1] = yk;
      }
    }

    yk = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = n;
    emxEnsureCapacity_int32_T(bc, yk);
    for (yk = 0; yk < n; yk++) {
      bc->data[yk] = y_data[yk];
    }

    if ((wPtr <= rPtr) && (rPtr <= c)) {
      if ((c >= 0) && (rPtr < c - MAX_int32_T)) {
        i = MAX_int32_T;
      } else if ((c < 0) && (rPtr > c - MIN_int32_T)) {
        i = MIN_int32_T;
      } else {
        i = c - rPtr;
      }

      if (i > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = i + 1;
      }
    }
  }

  emxInit_int16_T(&r1, 1);
  yk = r1->size[0];
  r1->size[0] = bc->size[1];
  emxEnsureCapacity_int16_T(r1, yk);
  i = bc->size[1];
  for (yk = 0; yk < i; yk++) {
    r1->data[yk] = (short)((short)bc->data[bc->size[0] * yk] - 1);
  }

  emxFree_int32_T(&bc);
  i = in->size[0];
  for (yk = 0; yk < i; yk++) {
    obj->Cache[r1->data[yk]] = in->data[yk];
  }

  emxFree_int16_T(&r1);
  if (c + 1 > 8194) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }

  if (qY != 0) {
    rPtr = wPtr;
  }

  i = obj->CumulativeOverrun;
  if ((i < 0) && (qY < MIN_int32_T - i)) {
    i = MIN_int32_T;
  } else if ((i > 0) && (qY > MAX_int32_T - i)) {
    i = MAX_int32_T;
  } else {
    i += qY;
  }

  obj->CumulativeOverrun = i;
  obj->WritePointer = wPtr;
  obj->ReadPointer = rPtr;
}

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
