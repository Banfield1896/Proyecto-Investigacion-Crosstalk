//
// NoPartitionOS.cpp
//
// Code generation for function 'NoPartitionOS'
//

// Include files
#include "NoPartitionOS.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "FFTImplementationCallback.h"
#include "xtc_wrapper_internal_types.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Variable Definitions
static const short iv[8]{8193, 1, 1, 1, 1, 1, 1, 1};

// Function Definitions
namespace coder {
namespace dsp {
namespace internal {
void NoPartitionOS::computeOutput(const ::coder::array<double, 1U> &input,
                                  double numFrames, const creal_T pH[16384],
                                  double prevsec[8191],
                                  ::coder::array<double, 1U> &o)
{
  static creal_T Z[16384];
  static creal_T y[16384];
  static double costab[8193];
  static double sintab[8193];
  array<double, 1U> z;
  double costab1q[4097];
  int i;
  int iy;
  iy = static_cast<int>(8193.0 * numFrames);
  o.set_size(iy);
  for (i = 0; i < iy; i++) {
    o[i] = 0.0;
  }
  i = static_cast<int>(numFrames);
  for (int b_index{0}; b_index < i; b_index++) {
    double d;
    double d1;
    double sintab_tmp;
    double temp_im;
    double temp_re;
    double twid_re;
    int b_i;
    int iheight;
    int ju;
    int k;
    d = ((static_cast<double>(b_index) + 1.0) - 1.0) * 8193.0 + 1.0;
    d1 = (static_cast<double>(b_index) + 1.0) * 8193.0;
    if (d > d1) {
      ju = 0;
      iheight = 0;
    } else {
      ju = static_cast<int>(d) - 1;
      iheight = static_cast<int>(d1);
    }
    iy = iheight - ju;
    z.set_size(iy + 8191);
    for (iheight = 0; iheight < 8191; iheight++) {
      z[iheight] = prevsec[iheight];
    }
    for (iheight = 0; iheight < iy; iheight++) {
      z[iheight + 8191] = input[ju + iheight];
    }
    for (ju = 0; ju < 8191; ju++) {
      prevsec[ju] = z[ju + 8193];
    }
    ::coder::internal::FFTImplementationCallback::generate_twiddle_tables(
        costab, sintab);
    if (16384 > z.size(0)) {
      std::memset(&y[0], 0, 16384U * sizeof(creal_T));
    }
    ::coder::internal::FFTImplementationCallback::doHalfLengthRadix2(
        z, y, costab, sintab);
    for (k = 0; k < 16384; k++) {
      temp_im = y[k].re;
      sintab_tmp = pH[k].im;
      temp_re = y[k].im;
      twid_re = pH[k].re;
      Z[k].re = temp_im * twid_re - temp_re * sintab_tmp;
      Z[k].im = temp_im * sintab_tmp + temp_re * twid_re;
    }
    costab1q[0] = 1.0;
    for (k = 0; k < 2048; k++) {
      costab1q[k + 1] =
          std::cos(0.00038349519697141029 * (static_cast<double>(k) + 1.0));
    }
    for (k = 0; k < 2047; k++) {
      costab1q[k + 2049] =
          std::sin(0.00038349519697141029 *
                   (4096.0 - (static_cast<double>(k) + 2049.0)));
    }
    costab1q[4096] = 0.0;
    costab[0] = 1.0;
    sintab[0] = 0.0;
    for (k = 0; k < 4096; k++) {
      temp_im = costab1q[k + 1];
      costab[k + 1] = temp_im;
      sintab_tmp = costab1q[4095 - k];
      sintab[k + 1] = sintab_tmp;
      costab[k + 4097] = -sintab_tmp;
      sintab[k + 4097] = temp_im;
    }
    iy = 0;
    ju = 0;
    for (b_i = 0; b_i < 16383; b_i++) {
      boolean_T tst;
      y[iy] = Z[b_i];
      iy = 16384;
      tst = true;
      while (tst) {
        iy >>= 1;
        ju ^= iy;
        tst = ((ju & iy) == 0);
      }
      iy = ju;
    }
    y[iy] = Z[16383];
    for (b_i = 0; b_i <= 16382; b_i += 2) {
      temp_im = y[b_i + 1].re;
      sintab_tmp = y[b_i + 1].im;
      temp_re = y[b_i].re;
      twid_re = y[b_i].im;
      y[b_i + 1].re = temp_re - temp_im;
      y[b_i + 1].im = twid_re - sintab_tmp;
      y[b_i].re = temp_re + temp_im;
      y[b_i].im = twid_re + sintab_tmp;
    }
    iy = 2;
    ju = 4;
    k = 4096;
    iheight = 16381;
    while (k > 0) {
      int istart;
      int temp_re_tmp;
      for (b_i = 0; b_i < iheight; b_i += ju) {
        temp_re_tmp = b_i + iy;
        temp_re = y[temp_re_tmp].re;
        temp_im = y[temp_re_tmp].im;
        y[temp_re_tmp].re = y[b_i].re - temp_re;
        y[temp_re_tmp].im = y[b_i].im - temp_im;
        y[b_i].re += temp_re;
        y[b_i].im += temp_im;
      }
      istart = 1;
      for (int j{k}; j < 8192; j += k) {
        double twid_im;
        int ihi;
        twid_re = costab[j];
        twid_im = sintab[j];
        b_i = istart;
        ihi = istart + iheight;
        while (b_i < ihi) {
          temp_re_tmp = b_i + iy;
          temp_im = y[temp_re_tmp].im;
          sintab_tmp = y[temp_re_tmp].re;
          temp_re = twid_re * sintab_tmp - twid_im * temp_im;
          temp_im = twid_re * temp_im + twid_im * sintab_tmp;
          y[temp_re_tmp].re = y[b_i].re - temp_re;
          y[temp_re_tmp].im = y[b_i].im - temp_im;
          y[b_i].re += temp_re;
          y[b_i].im += temp_im;
          b_i += ju;
        }
        istart++;
      }
      k /= 2;
      iy = ju;
      ju += ju;
      iheight -= iy;
    }
    for (ju = 0; ju < 16384; ju++) {
      y[ju].re *= 6.103515625E-5;
      y[ju].im *= 6.103515625E-5;
    }
    if (d > d1) {
      ju = 0;
      iheight = 0;
    } else {
      ju = static_cast<int>(d) - 1;
      iheight = static_cast<int>(d1);
    }
    for (iy = 0; iy < 8193; iy++) {
      costab[iy] = y[iy + 8191].re;
    }
    iy = iheight - ju;
    for (iheight = 0; iheight < iy; iheight++) {
      o[ju + iheight] = costab[iheight];
    }
  }
}

void NoPartitionOS::resetImpl()
{
  AsyncBuffer *obj;
  AsyncBuffercgHelper *b_obj;
  array<int, 2U> bc;
  array<int, 2U> y;
  cell_wrap_3 varSizes;
  int y_data[8194];
  int c;
  int i;
  int k;
  int overrun;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  short tmp_data[16386];
  boolean_T exitg1;
  for (i = 0; i < 8191; i++) {
    pLastSection[i] = 0.0;
  }
  if (pinBuff.pBuffer.isInitialized == 1) {
    pinBuff.pBuffer.ReadPointer = 1;
    pinBuff.pBuffer.WritePointer = 2;
    pinBuff.pBuffer.CumulativeOverrun = 0;
    pinBuff.pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      pinBuff.pBuffer.Cache[i] = 0.0;
    }
  }
  if (poutBuff.pBuffer.isInitialized == 1) {
    poutBuff.pBuffer.ReadPointer = 1;
    poutBuff.pBuffer.WritePointer = 2;
    poutBuff.pBuffer.CumulativeOverrun = 0;
    poutBuff.pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      poutBuff.pBuffer.Cache[i] = 0.0;
    }
  }
  obj = &poutBuff;
  b_obj = &poutBuff.pBuffer;
  if (obj->pBuffer.isInitialized != 1) {
    obj->pBuffer.isSetupComplete = false;
    obj->pBuffer.isInitialized = 1;
    for (k = 0; k < 8; k++) {
      varSizes.f1[k] = static_cast<unsigned int>(iv[k]);
    }
    obj->pBuffer.inputVarSize[0] = varSizes;
    obj->pBuffer.NumChannels = 1;
    obj->pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 8194; i++) {
      obj->pBuffer.Cache[i] = 0.0;
    }
    obj->pBuffer.isSetupComplete = true;
    obj->pBuffer.ReadPointer = 1;
    obj->pBuffer.WritePointer = 2;
    obj->pBuffer.CumulativeOverrun = 0;
    obj->pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 8194; i++) {
      obj->pBuffer.Cache[i] = 0.0;
    }
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (b_obj->inputVarSize[0].f1[k] != static_cast<unsigned int>(iv[k])) {
      for (k = 0; k < 8; k++) {
        b_obj->inputVarSize[0].f1[k] = static_cast<unsigned int>(iv[k]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  wPtr = obj->pBuffer.WritePointer;
  rPtr = obj->pBuffer.ReadPointer;
  overrun = 0;
  if (wPtr > 2147475454) {
    qY = MAX_int32_T;
  } else {
    qY = wPtr + 8193;
  }
  c = qY - 1;
  if (qY - 1 > 8194) {
    c = qY - 8195;
    i = 8195 - wPtr;
    y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= i; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    y.set_size(1, qY - 8195);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    bc.set_size(1, (y.size(1) - wPtr) + 8195);
    for (k = 0; k < i; k++) {
      bc[k] = y_data[k];
    }
    yk = y.size(1);
    for (k = 0; k < yk; k++) {
      bc[(k - wPtr) + 8195] = y[k];
    }
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
      if ((i < 0) && (qY - 8195 < MIN_int32_T - i)) {
        overrun = MIN_int32_T;
      } else if ((i > 0) && (qY - 8195 > MAX_int32_T - i)) {
        overrun = MAX_int32_T;
      } else {
        overrun = (i + qY) - 8195;
      }
    } else if (rPtr <= qY - 8195) {
      if (rPtr < qY + 2147475454) {
        qY = MAX_int32_T;
      } else {
        qY = (qY - rPtr) - 8195;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  } else {
    if (qY - 1 < wPtr) {
      i = 0;
    } else {
      i = qY - wPtr;
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
    for (k = 0; k < i; k++) {
      bc[k] = y_data[k];
    }
    if ((wPtr <= rPtr) && (rPtr <= qY - 1)) {
      if ((qY - 1 >= 0) && (rPtr < qY + MIN_int32_T)) {
        qY = MAX_int32_T;
      } else if ((qY - 1 < 0) && (rPtr > qY + MAX_int32_T)) {
        qY = MIN_int32_T;
      } else {
        qY = (qY - rPtr) - 1;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  }
  i = bc.size(1);
  yk = bc.size(1);
  for (k = 0; k < yk; k++) {
    tmp_data[k] = static_cast<short>(static_cast<short>(bc[k]) - 1);
  }
  for (k = 0; k < i; k++) {
    obj->pBuffer.Cache[tmp_data[k]] = 0.0;
  }
  if (c + 1 > 8194) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  i = obj->pBuffer.CumulativeOverrun;
  if ((i < 0) && (overrun < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (overrun > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + overrun;
  }
  obj->pBuffer.CumulativeOverrun = qY;
  obj->pBuffer.WritePointer = wPtr;
  obj->pBuffer.ReadPointer = rPtr;
}

void NoPartitionOS::setup()
{
  static double costab[8193];
  static double sintab[8193];
  cell_wrap_3 varSizes;
  double x[8192];
  int i;
  isSetupComplete = false;
  isInitialized = 1;
  for (i = 0; i < 8192; i++) {
    x[i] = Numerator[i];
  }
  ::coder::internal::FFTImplementationCallback::generate_twiddle_tables(costab,
                                                                        sintab);
  ::coder::internal::FFTImplementationCallback::doHalfLengthRadix2(x, costab,
                                                                   sintab, H);
  pinBuff.pBuffer.NumChannels = -1;
  pinBuff.pBuffer.CumulativeUnderrun = 0;
  pinBuff.pBuffer.ReadPointer = 1;
  pinBuff.pBuffer.WritePointer = 2;
  pinBuff.pBuffer.isInitialized = 0;
  pinBuff.pBuffer.matlabCodegenIsDeleted = false;
  pinBuff.matlabCodegenIsDeleted = false;
  pinBuff.pBuffer.isSetupComplete = false;
  pinBuff.pBuffer.isInitialized = 1;
  for (i = 0; i < 8; i++) {
    varSizes.f1[i] = static_cast<unsigned int>(iv[i]);
  }
  pinBuff.pBuffer.inputVarSize[0] = varSizes;
  pinBuff.pBuffer.NumChannels = 1;
  pinBuff.pBuffer.AsyncBuffercgHelper_isInitialized = true;
  for (i = 0; i < 8194; i++) {
    pinBuff.pBuffer.Cache[i] = 0.0;
  }
  pinBuff.pBuffer.isSetupComplete = true;
  poutBuff.pBuffer.NumChannels = -1;
  poutBuff.pBuffer.CumulativeUnderrun = 0;
  poutBuff.pBuffer.ReadPointer = 1;
  poutBuff.pBuffer.WritePointer = 2;
  poutBuff.pBuffer.isInitialized = 0;
  poutBuff.pBuffer.matlabCodegenIsDeleted = false;
  poutBuff.matlabCodegenIsDeleted = false;
  poutBuff.pBuffer.isSetupComplete = false;
  poutBuff.pBuffer.isInitialized = 1;
  for (i = 0; i < 8; i++) {
    varSizes.f1[i] = static_cast<unsigned int>(iv[i]);
  }
  poutBuff.pBuffer.inputVarSize[0] = varSizes;
  poutBuff.pBuffer.NumChannels = 1;
  poutBuff.pBuffer.AsyncBuffercgHelper_isInitialized = true;
  for (i = 0; i < 8194; i++) {
    poutBuff.pBuffer.Cache[i] = 0.0;
  }
  poutBuff.pBuffer.isSetupComplete = true;
  for (i = 0; i < 8191; i++) {
    pLastSection[i] = 0.0;
  }
  isSetupComplete = true;
  TunablePropsChanged = false;
}

} // namespace internal
} // namespace dsp
} // namespace coder

// End of code generation (NoPartitionOS.cpp)
