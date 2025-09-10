//
// FFTImplementationCallback.cpp
//
// Code generation for function 'FFTImplementationCallback'
//

// Include files
#include "FFTImplementationCallback.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
namespace internal {
void FFTImplementationCallback::get_bitrevIndex(int bitrevIndex[8192])
{
  int iy;
  int ju;
  ju = 0;
  iy = 1;
  for (int b_j1{0}; b_j1 < 8191; b_j1++) {
    boolean_T tst;
    bitrevIndex[b_j1] = iy;
    iy = 8192;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex[8191] = iy;
}

void FFTImplementationCallback::getback_radix2_fft(
    creal_T y[16384], const creal_T reconVar1[8192],
    const creal_T reconVar2[8192], const int wrapIndex[8192])
{
  double b_y_re_tmp;
  double c_y_re_tmp;
  double d_y_re_tmp;
  double temp1_im_tmp;
  double temp1_re_tmp;
  double y_re_tmp;
  temp1_re_tmp = y[0].re;
  temp1_im_tmp = y[0].im;
  y_re_tmp = temp1_re_tmp * reconVar2[0].re;
  b_y_re_tmp = temp1_re_tmp * reconVar1[0].re;
  y[0].re = 0.5 * ((b_y_re_tmp - temp1_im_tmp * reconVar1[0].im) +
                   (y_re_tmp - -temp1_im_tmp * reconVar2[0].im));
  c_y_re_tmp = temp1_re_tmp * reconVar2[0].im;
  d_y_re_tmp = temp1_re_tmp * reconVar1[0].im;
  y[0].im = 0.5 * ((d_y_re_tmp + temp1_im_tmp * reconVar1[0].re) +
                   (c_y_re_tmp + -temp1_im_tmp * reconVar2[0].re));
  y[8192].re = 0.5 * ((y_re_tmp - temp1_im_tmp * reconVar2[0].im) +
                      (b_y_re_tmp - -temp1_im_tmp * reconVar1[0].im));
  y[8192].im = 0.5 * ((c_y_re_tmp + temp1_im_tmp * reconVar2[0].re) +
                      (d_y_re_tmp + -temp1_im_tmp * reconVar1[0].re));
  for (int i{0}; i < 4095; i++) {
    double temp2_im_tmp;
    double temp2_re_tmp;
    int temp2_re_tmp_tmp;
    temp1_re_tmp = y[i + 1].re;
    temp1_im_tmp = y[i + 1].im;
    temp2_re_tmp_tmp = wrapIndex[i + 1];
    temp2_re_tmp = y[temp2_re_tmp_tmp - 1].re;
    temp2_im_tmp = y[temp2_re_tmp_tmp - 1].im;
    d_y_re_tmp = reconVar1[i + 1].im;
    y_re_tmp = reconVar1[i + 1].re;
    b_y_re_tmp = reconVar2[i + 1].im;
    c_y_re_tmp = reconVar2[i + 1].re;
    y[i + 1].re =
        0.5 * ((temp1_re_tmp * y_re_tmp - temp1_im_tmp * d_y_re_tmp) +
               (temp2_re_tmp * c_y_re_tmp - -temp2_im_tmp * b_y_re_tmp));
    y[i + 1].im =
        0.5 * ((temp1_re_tmp * d_y_re_tmp + temp1_im_tmp * y_re_tmp) +
               (temp2_re_tmp * b_y_re_tmp + -temp2_im_tmp * c_y_re_tmp));
    y[i + 8193].re =
        0.5 * ((temp1_re_tmp * c_y_re_tmp - temp1_im_tmp * b_y_re_tmp) +
               (temp2_re_tmp * y_re_tmp - -temp2_im_tmp * d_y_re_tmp));
    y[i + 8193].im =
        0.5 * ((temp1_re_tmp * b_y_re_tmp + temp1_im_tmp * c_y_re_tmp) +
               (temp2_re_tmp * d_y_re_tmp + -temp2_im_tmp * y_re_tmp));
    d_y_re_tmp = reconVar1[temp2_re_tmp_tmp - 1].im;
    y_re_tmp = reconVar1[temp2_re_tmp_tmp - 1].re;
    b_y_re_tmp = reconVar2[temp2_re_tmp_tmp - 1].im;
    c_y_re_tmp = reconVar2[temp2_re_tmp_tmp - 1].re;
    y[temp2_re_tmp_tmp - 1].re =
        0.5 * ((temp2_re_tmp * y_re_tmp - temp2_im_tmp * d_y_re_tmp) +
               (temp1_re_tmp * c_y_re_tmp - -temp1_im_tmp * b_y_re_tmp));
    y[temp2_re_tmp_tmp - 1].im =
        0.5 * ((temp2_re_tmp * d_y_re_tmp + temp2_im_tmp * y_re_tmp) +
               (temp1_re_tmp * b_y_re_tmp + -temp1_im_tmp * c_y_re_tmp));
    y[temp2_re_tmp_tmp + 8191].re =
        0.5 * ((temp2_re_tmp * c_y_re_tmp - temp2_im_tmp * b_y_re_tmp) +
               (temp1_re_tmp * y_re_tmp - -temp1_im_tmp * d_y_re_tmp));
    y[temp2_re_tmp_tmp + 8191].im =
        0.5 * ((temp2_re_tmp * b_y_re_tmp + temp2_im_tmp * c_y_re_tmp) +
               (temp1_re_tmp * d_y_re_tmp + -temp1_im_tmp * y_re_tmp));
  }
  temp1_re_tmp = y[4096].re;
  temp1_im_tmp = y[4096].im;
  y_re_tmp = temp1_re_tmp * reconVar2[4096].re;
  b_y_re_tmp = temp1_re_tmp * reconVar1[4096].re;
  y[4096].re = 0.5 * ((b_y_re_tmp - temp1_im_tmp * reconVar1[4096].im) +
                      (y_re_tmp - -temp1_im_tmp * reconVar2[4096].im));
  c_y_re_tmp = temp1_re_tmp * reconVar2[4096].im;
  d_y_re_tmp = temp1_re_tmp * reconVar1[4096].im;
  y[4096].im = 0.5 * ((d_y_re_tmp + temp1_im_tmp * reconVar1[4096].re) +
                      (c_y_re_tmp + -temp1_im_tmp * reconVar2[4096].re));
  y[12288].re = 0.5 * ((y_re_tmp - temp1_im_tmp * reconVar2[4096].im) +
                       (b_y_re_tmp - -temp1_im_tmp * reconVar1[4096].im));
  y[12288].im = 0.5 * ((c_y_re_tmp + temp1_im_tmp * reconVar2[4096].re) +
                       (d_y_re_tmp + -temp1_im_tmp * reconVar1[4096].re));
}

void FFTImplementationCallback::doHalfLengthRadix2(const double x[8192],
                                                   const double costab[8193],
                                                   const double sintab[8193],
                                                   creal_T y[16384])
{
  static creal_T reconVar1[8192];
  static creal_T reconVar2[8192];
  double hcostab[4096];
  double hsintab[4096];
  double re_tmp;
  double temp_im;
  double temp_re_tmp;
  double twid_re;
  int bitrevIndex[8192];
  int wrapIndex[8192];
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int k;
  std::memset(&y[0], 0, 16384U * sizeof(creal_T));
  for (i = 0; i < 4096; i++) {
    iDelta = ((i + 1) << 1) - 2;
    hcostab[i] = costab[iDelta];
    hsintab[i] = sintab[iDelta];
  }
  for (i = 0; i < 8192; i++) {
    temp_im = sintab[i];
    reconVar1[i].re = temp_im + 1.0;
    re_tmp = costab[i];
    reconVar1[i].im = -re_tmp;
    reconVar2[i].re = 1.0 - temp_im;
    reconVar2[i].im = re_tmp;
    if (i + 1 != 1) {
      wrapIndex[i] = 8193 - i;
    } else {
      wrapIndex[0] = 1;
    }
  }
  FFTImplementationCallback::get_bitrevIndex(bitrevIndex);
  for (i = 0; i < 4096; i++) {
    iDelta = i << 1;
    iDelta2 = bitrevIndex[i];
    y[iDelta2 - 1].re = x[iDelta];
    y[iDelta2 - 1].im = x[iDelta + 1];
  }
  for (i = 0; i <= 8190; i += 2) {
    temp_re_tmp = y[i + 1].re;
    temp_im = y[i + 1].im;
    re_tmp = y[i].re;
    twid_re = y[i].im;
    y[i + 1].re = re_tmp - temp_re_tmp;
    y[i + 1].im = twid_re - temp_im;
    y[i].re = re_tmp + temp_re_tmp;
    y[i].im = twid_re + temp_im;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 2048;
  iheight = 8189;
  while (k > 0) {
    double temp_re;
    int b_temp_re_tmp;
    int istart;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iDelta;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (int j{k}; j < 4096; j += k) {
      double twid_im;
      int ihi;
      twid_re = hcostab[j];
      twid_im = hsintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iDelta;
        temp_re_tmp = y[b_temp_re_tmp].im;
        re_tmp = y[b_temp_re_tmp].re;
        temp_re = twid_re * re_tmp - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * re_tmp;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  FFTImplementationCallback::getback_radix2_fft(y, reconVar1, reconVar2,
                                                wrapIndex);
}

void FFTImplementationCallback::doHalfLengthRadix2(
    const ::coder::array<double, 1U> &x, creal_T y[16384],
    const double costab[8193], const double sintab[8193])
{
  static creal_T reconVar1[8192];
  static creal_T reconVar2[8192];
  double hcostab[4096];
  double hsintab[4096];
  double temp_im;
  double temp_im_tmp_tmp;
  int bitrevIndex[8192];
  int wrapIndex[8192];
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int k;
  boolean_T nxeven;
  for (i = 0; i < 4096; i++) {
    iDelta = ((i + 1) << 1) - 2;
    hcostab[i] = costab[iDelta];
    hsintab[i] = sintab[iDelta];
  }
  for (i = 0; i < 8192; i++) {
    temp_im_tmp_tmp = sintab[i];
    reconVar1[i].re = temp_im_tmp_tmp + 1.0;
    temp_im = costab[i];
    reconVar1[i].im = -temp_im;
    reconVar2[i].re = 1.0 - temp_im_tmp_tmp;
    reconVar2[i].im = temp_im;
    if (i + 1 != 1) {
      wrapIndex[i] = 8193 - i;
    } else {
      wrapIndex[0] = 1;
    }
  }
  FFTImplementationCallback::get_bitrevIndex(bitrevIndex);
  if ((x.size(0) & 1) == 0) {
    nxeven = true;
    iDelta = x.size(0);
  } else if (x.size(0) >= 16384) {
    nxeven = true;
    iDelta = 16384;
  } else {
    nxeven = false;
    iDelta = x.size(0) - 1;
  }
  if (iDelta > 16384) {
    iDelta = 16384;
  }
  temp_im_tmp_tmp = static_cast<double>(iDelta) / 2.0;
  iDelta = static_cast<int>(temp_im_tmp_tmp);
  for (i = 0; i < iDelta; i++) {
    iDelta2 = i << 1;
    k = bitrevIndex[i];
    y[k - 1].re = x[iDelta2];
    y[k - 1].im = x[iDelta2 + 1];
  }
  if (!nxeven) {
    iDelta = bitrevIndex[static_cast<int>(temp_im_tmp_tmp)] - 1;
    y[iDelta].re = x[static_cast<int>(temp_im_tmp_tmp) << 1];
    y[iDelta].im = 0.0;
  }
  for (i = 0; i <= 8190; i += 2) {
    temp_im = y[i + 1].re;
    temp_im_tmp_tmp = y[i + 1].im;
    y[i + 1].re = y[i].re - temp_im;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_im;
    y[i].im += temp_im_tmp_tmp;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 2048;
  iheight = 8189;
  while (k > 0) {
    double temp_re;
    int istart;
    int temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      temp_re_tmp = i + iDelta;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - temp_re;
      y[temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (int j{k}; j < 4096; j += k) {
      double twid_im;
      double twid_re;
      int ihi;
      twid_re = hcostab[j];
      twid_im = hsintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iDelta;
        temp_im = y[temp_re_tmp].im;
        temp_im_tmp_tmp = y[temp_re_tmp].re;
        temp_re = twid_re * temp_im_tmp_tmp - twid_im * temp_im;
        temp_im = twid_re * temp_im + twid_im * temp_im_tmp_tmp;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  FFTImplementationCallback::getback_radix2_fft(y, reconVar1, reconVar2,
                                                wrapIndex);
}

void FFTImplementationCallback::generate_twiddle_tables(double costab[8193],
                                                        double sintab[8193])
{
  double costab1q[4097];
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] =
        std::cos(0.00038349519697141029 * (static_cast<double>(k) + 1.0));
  }
  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] = std::sin(0.00038349519697141029 *
                                  (4096.0 - (static_cast<double>(k) + 2049.0)));
  }
  costab1q[4096] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    double costab_tmp;
    double sintab_tmp;
    costab_tmp = costab1q[k + 1];
    costab[k + 1] = costab_tmp;
    sintab_tmp = -costab1q[4095 - k];
    sintab[k + 1] = sintab_tmp;
    costab[k + 4097] = sintab_tmp;
    sintab[k + 4097] = -costab_tmp;
  }
}

} // namespace internal
} // namespace coder

// End of code generation (FFTImplementationCallback.cpp)
