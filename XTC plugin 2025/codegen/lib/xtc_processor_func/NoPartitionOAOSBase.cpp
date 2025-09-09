//
// File: NoPartitionOAOSBase.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "NoPartitionOAOSBase.h"
#include "xtc_processor_func_emxutil.h"
#include "AsyncBuffer.h"
#include "NoPartitionOS.h"
#include "xtc_processor_func_data.h"

// Function Definitions

//
// Arguments    : dsp_private_NoPartitionOS *obj
// Return Type  : void
//
void NoPartitionOAOSBase_resetImpl(dsp_private_NoPartitionOS *obj)
{
  int i;
  dsp_AsyncBuffer *b_obj;
  boolean_T exitg1;
  cell_wrap_2 varSizes[1];
  double dv2[8193];
  for (i = 0; i < 8191; i++) {
    obj->pLastSection[i] = 0.0;
  }

  if (obj->pinBuff.isInitialized == 1) {
    obj->pinBuff.ReadPointer = 1;
    obj->pinBuff.WritePointer = 2;
    obj->pinBuff.CumulativeOverrun = 0;
    obj->pinBuff.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      obj->pinBuff.Cache[i] = 0.0;
    }
  }

  if (obj->poutBuff.isInitialized == 1) {
    obj->poutBuff.ReadPointer = 1;
    obj->poutBuff.WritePointer = 2;
    obj->poutBuff.CumulativeOverrun = 0;
    obj->poutBuff.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      obj->poutBuff.Cache[i] = 0.0;
    }
  }

  b_obj = &obj->poutBuff;
  if (obj->poutBuff.isInitialized != 1) {
    obj->poutBuff.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      varSizes[0].f1[i] = (unsigned int)iv0[i];
    }

    obj->poutBuff.inputVarSize[0] = varSizes[0];
    obj->poutBuff.NumChannels = 1;
    obj->poutBuff.AsyncBuffer_isInitialized = true;
    for (i = 0; i < 8194; i++) {
      obj->poutBuff.Cache[i] = 0.0;
    }

    obj->poutBuff.ReadPointer = 1;
    obj->poutBuff.WritePointer = 2;
    obj->poutBuff.CumulativeOverrun = 0;
    obj->poutBuff.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      obj->poutBuff.Cache[i] = 0.0;
    }
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (b_obj->inputVarSize[0].f1[i] != (unsigned int)iv0[i]) {
      for (i = 0; i < 8; i++) {
        b_obj->inputVarSize[0].f1[i] = (unsigned int)iv0[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  memset(&dv2[0], 0, 8193U * sizeof(double));
  AsyncBuffer_stepImpl(&obj->poutBuff, dv2);
}

//
// Arguments    : dsp_private_NoPartitionOS *obj
//                const emxArray_real_T *u
//                emxArray_real_T *y
// Return Type  : void
//
void NoPartitionOAOSBase_stepImpl(dsp_private_NoPartitionOS *obj, const
  emxArray_real_T *u, emxArray_real_T *y)
{
  unsigned int sz_idx_0;
  dsp_AsyncBuffer *poutbff;
  int i;
  int q1;
  int qY;
  int unreadSamples;
  static double prevsec[8191];
  emxArray_real_T *input;
  static creal_T pH[16384];
  int numFrames;
  int i5;
  double inpStart;
  double remSamples;
  emxArray_real_T *r0;
  double varargin_1;
  double val;
  emxArray_real_T *b_u;
  unsigned int ns;
  emxArray_real_T *o;
  sz_idx_0 = (unsigned int)u->size[0];
  poutbff = &obj->poutBuff;
  i = obj->poutBuff.WritePointer;
  q1 = obj->poutBuff.ReadPointer;
  if ((i >= 0) && (q1 < i - MAX_int32_T)) {
    i = MAX_int32_T;
  } else if ((i < 0) && (q1 > i - MIN_int32_T)) {
    i = MIN_int32_T;
  } else {
    i -= q1;
  }

  if (i < -2147483647) {
    i = MIN_int32_T;
  } else {
    i--;
  }

  q1 = obj->poutBuff.ReadPointer;
  if (q1 < -2147475454) {
    qY = MAX_int32_T;
  } else {
    qY = 8193 - q1;
  }

  q1 = obj->poutBuff.WritePointer;
  if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
    qY = MIN_int32_T;
  } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
    qY = MAX_int32_T;
  } else {
    qY += q1;
  }

  if (obj->poutBuff.ReadPointer < obj->poutBuff.WritePointer) {
    unreadSamples = i;
  } else if (obj->poutBuff.ReadPointer == obj->poutBuff.WritePointer) {
    unreadSamples = 8193;
  } else {
    unreadSamples = qY;
  }

  i = obj->pinBuff.WritePointer;
  q1 = obj->pinBuff.ReadPointer;
  if ((i >= 0) && (q1 < i - MAX_int32_T)) {
    i = MAX_int32_T;
  } else if ((i < 0) && (q1 > i - MIN_int32_T)) {
    i = MIN_int32_T;
  } else {
    i -= q1;
  }

  if (i < -2147483647) {
    i = MIN_int32_T;
  } else {
    i--;
  }

  q1 = obj->pinBuff.ReadPointer;
  if (q1 < -2147475454) {
    qY = MAX_int32_T;
  } else {
    qY = 8193 - q1;
  }

  q1 = obj->pinBuff.WritePointer;
  if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
    qY = MIN_int32_T;
  } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
    qY = MAX_int32_T;
  } else {
    qY += q1;
  }

  if (obj->pinBuff.ReadPointer < obj->pinBuff.WritePointer) {
    qY = i;
  } else {
    if (obj->pinBuff.ReadPointer == obj->pinBuff.WritePointer) {
      qY = 8193;
    }
  }

  for (i = 0; i < 8191; i++) {
    prevsec[i] = obj->pLastSection[i];
  }

  for (i = 0; i < 16384; i++) {
    pH[i] = obj->H[i];
  }

  emxInit_real_T(&input, 1);
  if (qY < 8193) {
    i = qY;
  } else {
    i = 8193;
  }

  numFrames = (int)std::floor(((double)i + (double)sz_idx_0) / 8193.0);
  i5 = input->size[0];
  input->size[0] = (int)(8193.0 * (double)numFrames);
  emxEnsureCapacity_real_T(input, i5);
  q1 = (int)(8193.0 * (double)numFrames);
  for (i5 = 0; i5 < q1; i5++) {
    input->data[i5] = 0.0;
  }

  inpStart = 1.0;
  remSamples = 8193.0 * (double)numFrames;
  emxInit_real_T(&r0, 1);
  if (qY > 0) {
    varargin_1 = 8193.0 * (double)numFrames;
    val = qY;
    if (varargin_1 < val) {
      val = varargin_1;
    }

    if (numFrames > 0) {
      if (val >= -2.147483648E+9) {
        i5 = (int)val;
      } else {
        i5 = MIN_int32_T;
      }

      AsyncBuffer_read(&obj->pinBuff, i5, r0);
      q1 = r0->size[0];
      for (i5 = 0; i5 < q1; i5++) {
        input->data[i5] = r0->data[i5];
      }

      inpStart = val + 1.0;
      remSamples -= val;
    }
  }

  if (remSamples > 0.0) {
    if (inpStart > (inpStart + remSamples) - 1.0) {
      i5 = 0;
    } else {
      i5 = (int)inpStart - 1;
    }

    q1 = (int)remSamples;
    for (qY = 0; qY < q1; qY++) {
      input->data[i5 + qY] = u->data[qY];
    }
  }

  emxInit_real_T(&b_u, 1);
  if (sz_idx_0 > remSamples) {
    if (remSamples + 1.0 > u->size[0]) {
      i5 = 0;
      qY = 0;
    } else {
      i5 = (int)(remSamples + 1.0) - 1;
      qY = u->size[0];
    }

    i = b_u->size[0];
    b_u->size[0] = qY - i5;
    emxEnsureCapacity_real_T(b_u, i);
    q1 = qY - i5;
    for (qY = 0; qY < q1; qY++) {
      b_u->data[qY] = u->data[i5 + qY];
    }

    AsyncBuffer_write(&obj->pinBuff, b_u);
  }

  i5 = y->size[0];
  y->size[0] = (int)sz_idx_0;
  emxEnsureCapacity_real_T(y, i5);
  q1 = (int)sz_idx_0;
  for (i5 = 0; i5 < q1; i5++) {
    y->data[i5] = 0.0;
  }

  i = (int)sz_idx_0;
  ns = 1U;
  if (unreadSamples > 0) {
    if ((int)sz_idx_0 < unreadSamples) {
      ns = sz_idx_0;
    } else {
      ns = (unsigned int)unreadSamples;
    }

    AsyncBuffer_read(poutbff, (int)ns, r0);
    q1 = r0->size[0];
    for (i5 = 0; i5 < q1; i5++) {
      y->data[i5] = r0->data[i5];
    }

    i = (int)sz_idx_0 - (int)ns;
    ns++;
  }

  emxFree_real_T(&r0);
  if (numFrames > 0) {
    emxInit_real_T(&o, 1);
    NoPartitionOS_computeOutput(input, (double)numFrames, pH, prevsec, o);
    if (1 > i) {
      q1 = -1;
    } else {
      q1 = i - 1;
    }

    if (ns > (unsigned int)y->size[0]) {
      i5 = 0;
    } else {
      i5 = (int)ns - 1;
    }

    for (qY = 0; qY <= q1; qY++) {
      y->data[i5 + qY] = o->data[qY];
    }

    if (i < 8193.0 * (double)numFrames) {
      if ((double)i + 1.0 > o->size[0]) {
        i5 = 1;
        qY = 0;
      } else {
        i5 = i + 1;
        qY = o->size[0];
      }

      i = b_u->size[0];
      b_u->size[0] = (qY - i5) + 1;
      emxEnsureCapacity_real_T(b_u, i);
      q1 = (qY - i5) + 1;
      for (qY = 0; qY < q1; qY++) {
        b_u->data[qY] = o->data[(i5 + qY) - 1];
      }

      AsyncBuffer_write(poutbff, b_u);
    }

    emxFree_real_T(&o);
  }

  emxFree_real_T(&b_u);
  emxFree_real_T(&input);
  for (i = 0; i < 8191; i++) {
    obj->pLastSection[i] = prevsec[i];
  }
}

//
// File trailer for NoPartitionOAOSBase.cpp
//
// [EOF]
//
