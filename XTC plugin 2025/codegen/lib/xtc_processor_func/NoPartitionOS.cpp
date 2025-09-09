//
// File: NoPartitionOS.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "NoPartitionOS.h"
#include "xtc_processor_func_emxutil.h"
#include "fft.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *input
//                double numFrames
//                const creal_T pH[16384]
//                double prevsec[8191]
//                emxArray_real_T *o
// Return Type  : void
//
void NoPartitionOS_computeOutput(const emxArray_real_T *input, double numFrames,
  const creal_T pH[16384], double prevsec[8191], emxArray_real_T *o)
{
  int k;
  int iy;
  int b_index;
  emxArray_real_T *z;
  emxArray_int32_T *r3;
  double temp_re;
  double temp_im;
  int iDelta2;
  double costab[8193];
  double sintab[8193];
  int i;
  int ix;
  int ju;
  static creal_T y[16384];
  boolean_T tst;
  static creal_T Z[16384];
  int j;
  double twid_re;
  double twid_im;
  int ihi;
  k = o->size[0];
  o->size[0] = (int)(8193.0 * numFrames);
  emxEnsureCapacity_real_T(o, k);
  iy = (int)(8193.0 * numFrames);
  for (k = 0; k < iy; k++) {
    o->data[k] = 0.0;
  }

  b_index = 0;
  emxInit_real_T(&z, 1);
  emxInit_int32_T1(&r3, 1);
  while (b_index <= (int)numFrames - 1) {
    temp_re = ((1.0 + (double)b_index) - 1.0) * 8193.0 + 1.0;
    temp_im = (1.0 + (double)b_index) * 8193.0;
    if (temp_re > temp_im) {
      k = 1;
      iDelta2 = 0;
    } else {
      k = (int)temp_re;
      iDelta2 = (int)temp_im;
    }

    iy = z->size[0];
    z->size[0] = (iDelta2 - k) + 8192;
    emxEnsureCapacity_real_T(z, iy);
    for (iy = 0; iy < 8191; iy++) {
      z->data[iy] = prevsec[iy];
    }

    iy = iDelta2 - k;
    for (iDelta2 = 0; iDelta2 <= iy; iDelta2++) {
      z->data[iDelta2 + 8191] = input->data[(k + iDelta2) - 1];
    }

    for (k = 0; k < 8191; k++) {
      prevsec[k] = z->data[8193 + k];
    }

    generate_twiddle_tables(costab, sintab);
    k = z->size[0];
    if (!(k < 16384)) {
      k = 16384;
    }

    if (16384 > z->size[0]) {
      for (i = 0; i < 16384; i++) {
        y[i].re = 0.0;
        y[i].im = 0.0;
      }
    }

    ix = 0;
    ju = 0;
    iy = 0;
    for (i = 1; i < k; i++) {
      y[iy].re = z->data[ix];
      y[iy].im = 0.0;
      iDelta2 = 16384;
      tst = true;
      while (tst) {
        iDelta2 >>= 1;
        ju ^= iDelta2;
        tst = ((ju & iDelta2) == 0);
      }

      iy = ju;
      ix++;
    }

    y[iy].re = z->data[ix];
    y[iy].im = 0.0;
    for (i = 0; i <= 16383; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    iy = 2;
    iDelta2 = 4;
    k = 4096;
    ix = 16381;
    while (k > 0) {
      for (i = 0; i < ix; i += iDelta2) {
        temp_re = y[i + iy].re;
        temp_im = y[i + iy].im;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
      }

      ju = 1;
      for (j = k; j < 8192; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = ju;
        ihi = ju + ix;
        while (i < ihi) {
          temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
          temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
          y[i + iy].re = y[i].re - temp_re;
          y[i + iy].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
          i += iDelta2;
        }

        ju++;
      }

      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      ix -= iy;
    }

    for (k = 0; k < 16384; k++) {
      Z[k].re = y[k].re * pH[k].re - y[k].im * pH[k].im;
      Z[k].im = y[k].re * pH[k].im + y[k].im * pH[k].re;
    }

    b_generate_twiddle_tables(costab, sintab);
    ix = 0;
    ju = 0;
    iy = 0;
    for (i = 0; i < 16383; i++) {
      y[iy] = Z[ix];
      iDelta2 = 16384;
      tst = true;
      while (tst) {
        iDelta2 >>= 1;
        ju ^= iDelta2;
        tst = ((ju & iDelta2) == 0);
      }

      iy = ju;
      ix++;
    }

    y[iy] = Z[ix];
    for (i = 0; i <= 16383; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    iy = 2;
    iDelta2 = 4;
    k = 4096;
    ix = 16381;
    while (k > 0) {
      for (i = 0; i < ix; i += iDelta2) {
        temp_re = y[i + iy].re;
        temp_im = y[i + iy].im;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
      }

      ju = 1;
      for (j = k; j < 8192; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = ju;
        ihi = ju + ix;
        while (i < ihi) {
          temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
          temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
          y[i + iy].re = y[i].re - temp_re;
          y[i + iy].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
          i += iDelta2;
        }

        ju++;
      }

      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      ix -= iy;
    }

    for (k = 0; k < 16384; k++) {
      y[k].re *= 6.103515625E-5;
      y[k].im *= 6.103515625E-5;
    }

    temp_re = ((1.0 + (double)b_index) - 1.0) * 8193.0 + 1.0;
    temp_im = 8193.0 * (1.0 + (double)b_index);
    if (temp_re > temp_im) {
      k = 0;
      iDelta2 = 0;
    } else {
      k = (int)temp_re - 1;
      iDelta2 = (int)temp_im;
    }

    iy = r3->size[0];
    r3->size[0] = iDelta2 - k;
    emxEnsureCapacity_int32_T1(r3, iy);
    iy = iDelta2 - k;
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      r3->data[iDelta2] = k + iDelta2;
    }

    for (k = 0; k < 8193; k++) {
      costab[k] = y[8191 + k].re;
    }

    iy = r3->size[0];
    for (k = 0; k < iy; k++) {
      o->data[r3->data[k]] = costab[k];
    }

    b_index++;
  }

  emxFree_int32_T(&r3);
  emxFree_real_T(&z);
}

//
// File trailer for NoPartitionOS.cpp
//
// [EOF]
//
