//
// File: transaural_ir3.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "transaural_ir3.h"
#include "circshift.h"
#include "ifft.h"
#include "squeeze.h"
#include "inv.h"
#include "exp.h"
#include "sqrt.h"

// Function Declarations
static double rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : double u
// Return Type  : double
//
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// Versión corregida y optimizada para la generación de código C++.
//  - Pre-asigna memoria para todas las matrices.
//  - Devuelve únicamente las dos IRs necesarias (cLL y cLR).
// Arguments    : double D
//                double dp
//                double b_do
//                double beta
//                double fs
//                double cLL[8192]
//                double cLR[8192]
// Return Type  : void
//
void transaural_ir3(double D, double dp, double b_do, double beta, double fs,
                    double cLL[8192], double cLR[8192])
{
  int i;
  double w;
  double f[4096];
  double dLL;
  double dLR;
  double tLL;
  double tLR;
  int naux;
  creal_T dc0;
  creal_T dc1;
  static creal_T C[4096];
  static creal_T dcv0[4096];
  static creal_T b_C[16384];
  creal_T dc2;
  creal_T c_C[4095];
  creal_T dcv1[4095];
  creal_T dc3;
  static creal_T dcv2[8192];
  creal_T Haux0[4];
  static creal_T dcv3[8192];
  creal_T b_Haux0[4];
  creal_T a[4];
  int i1;
  double im;
  int i2;
  static const signed char b[4] = { 1, 0, 0, 1 };

  double Haux0_re;
  double Haux0_im;

  //  --- Pre-asignación de memoria ---
  //  Esto le dice a MATLAB Coder el tamaño exacto de las matrices de antemano.
  //  H no es necesario si no se devuelve H2.
  //  C2 y H2 tampoco son necesarios si no se devuelven.
  for (i = 0; i < 4096; i++) {
    f[i] = 0.0001220703125 * (double)i * fs;
  }

  w = dp / 2.0 - b_do / 2.0;
  dLL = D * D + w * w;
  b_sqrt(&dLL);
  w = dp / 2.0 + b_do / 2.0;
  dLR = D * D + w * w;
  b_sqrt(&dLR);
  tLL = dLL / 345.0;
  tLR = dLR / 345.0;

  //  Cálculo de la matriz de transferencia en frecuencia
  for (naux = 0; naux < 4096; naux++) {
    w = 6.2831853071795862 * f[naux];
    dc0.re = tLL * (w * 0.0);
    dc0.im = tLL * -w;
    b_exp(&dc0);
    dc1.re = tLR * (w * 0.0);
    dc1.im = tLR * -w;
    b_exp(&dc1);
    dc2.re = tLR * (w * 0.0);
    dc2.im = tLR * -w;
    b_exp(&dc2);
    dc3.re = tLL * (w * 0.0);
    dc3.im = tLL * -w;
    b_exp(&dc3);
    if (dc0.im == 0.0) {
      Haux0[0].re = dc0.re / dLL;
      Haux0[0].im = 0.0;
    } else if (dc0.re == 0.0) {
      Haux0[0].re = 0.0;
      Haux0[0].im = dc0.im / dLL;
    } else {
      Haux0[0].re = dc0.re / dLL;
      Haux0[0].im = dc0.im / dLL;
    }

    if (dc1.im == 0.0) {
      Haux0[2].re = dc1.re / dLR;
      Haux0[2].im = 0.0;
    } else if (dc1.re == 0.0) {
      Haux0[2].re = 0.0;
      Haux0[2].im = dc1.im / dLR;
    } else {
      Haux0[2].re = dc1.re / dLR;
      Haux0[2].im = dc1.im / dLR;
    }

    if (dc2.im == 0.0) {
      Haux0[1].re = dc2.re / dLR;
      Haux0[1].im = 0.0;
    } else if (dc2.re == 0.0) {
      Haux0[1].re = 0.0;
      Haux0[1].im = dc2.im / dLR;
    } else {
      Haux0[1].re = dc2.re / dLR;
      Haux0[1].im = dc2.im / dLR;
    }

    if (dc3.im == 0.0) {
      Haux0[3].re = dc3.re / dLL;
      Haux0[3].im = 0.0;
    } else if (dc3.re == 0.0) {
      Haux0[3].re = 0.0;
      Haux0[3].im = dc3.im / dLL;
    } else {
      Haux0[3].re = dc3.re / dLL;
      Haux0[3].im = dc3.im / dLL;
    }

    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 2; i1++) {
        w = 0.0;
        im = 0.0;
        for (i2 = 0; i2 < 2; i2++) {
          Haux0_re = Haux0[i2 + (i << 1)].re;
          Haux0_im = -Haux0[i2 + (i << 1)].im;
          w += Haux0_re * Haux0[i2 + (i1 << 1)].re - Haux0_im * Haux0[i2 + (i1 <<
            1)].im;
          im += Haux0_re * Haux0[i2 + (i1 << 1)].im + Haux0_im * Haux0[i2 + (i1 <<
            1)].re;
        }

        b_Haux0[i + (i1 << 1)].re = w + beta * (double)b[i + (i1 << 1)];
        b_Haux0[i + (i1 << 1)].im = im;
        b_C[(i1 + (i << 1)) + (naux << 2)].re = 0.0;
        b_C[(i1 + (i << 1)) + (naux << 2)].im = 0.0;
      }
    }

    inv(b_Haux0, a);
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < 2; i1++) {
        b_C[(i + (i1 << 1)) + (naux << 2)].re = 0.0;
        b_C[(i + (i1 << 1)) + (naux << 2)].im = 0.0;
        for (i2 = 0; i2 < 2; i2++) {
          Haux0_re = Haux0[i1 + (i2 << 1)].re;
          Haux0_im = -Haux0[i1 + (i2 << 1)].im;
          b_C[(i + (i1 << 1)) + (naux << 2)].re += a[i + (i2 << 1)].re *
            Haux0_re - a[i + (i2 << 1)].im * Haux0_im;
          b_C[(i + (i1 << 1)) + (naux << 2)].im += a[i + (i2 << 1)].re *
            Haux0_im + a[i + (i2 << 1)].im * Haux0_re;
        }
      }
    }
  }

  //  Reconstrucción del espectro completo con simetría Hermitiana
  //  Obtener la respuesta al impulso (real)
  //  Aplicar un pequeño retardo para hacer la respuesta causal
  //  10 ms delay
  w = rt_roundd_snf(0.01 * fs);
  for (i = 0; i < 4096; i++) {
    C[i] = b_C[i << 2];
  }

  squeeze(C, dcv0);
  for (i = 0; i < 4095; i++) {
    c_C[i] = b_C[(4095 - i) << 2];
  }

  b_squeeze(c_C, dcv1);
  memcpy(&dcv2[0], &dcv0[0], sizeof(creal_T) << 12);
  dcv2[4096].re = 0.0;
  dcv2[4096].im = 0.0;
  for (i = 0; i < 4095; i++) {
    dcv2[i + 4097].re = dcv1[i].re;
    dcv2[i + 4097].im = -dcv1[i].im;
  }

  ifft(dcv2, dcv3);
  for (i = 0; i < 8192; i++) {
    cLL[i] = dcv3[i].re;
  }

  circshift(cLL, w);
  for (i = 0; i < 4096; i++) {
    C[i] = b_C[1 + (i << 2)];
  }

  squeeze(C, dcv0);
  for (i = 0; i < 4095; i++) {
    c_C[i] = b_C[1 + ((4095 - i) << 2)];
  }

  b_squeeze(c_C, dcv1);
  memcpy(&dcv2[0], &dcv0[0], sizeof(creal_T) << 12);
  dcv2[4096].re = 0.0;
  dcv2[4096].im = 0.0;
  for (i = 0; i < 4095; i++) {
    dcv2[i + 4097].re = dcv1[i].re;
    dcv2[i + 4097].im = -dcv1[i].im;
  }

  ifft(dcv2, dcv3);
  for (i = 0; i < 8192; i++) {
    cLR[i] = dcv3[i].re;
  }

  circshift(cLR, w);
}

//
// File trailer for transaural_ir3.cpp
//
// [EOF]
//
