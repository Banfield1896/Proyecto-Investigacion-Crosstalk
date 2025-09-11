//
// XTC_Processor.cpp
//
// Code generation for function 'XTC_Processor'
//

// Include files
#include "XTC_Processor.h"
#include "FrequencyDomainFIRFilter.h"
#include "circshift.h"
#include "ifft.h"
#include <algorithm>
#include <cmath>

// Function Definitions
void XTC_Processor::recalculateFilters(double params_D, double params_dp,
                                       double params_do, double params_beta,
                                       double params_SampleRate)
{
  static creal_T b_C[16384];
  static creal_T C[8192];
  static const signed char b[4]{1, 0, 0, 1};
  creal_T dcv[8192];
  creal_T Haux0[4];
  creal_T b_a[4];
  creal_T x[4];
  double a;
  double dLL;
  double dLR;
  double ntdelay;
  double r;
  double tLL;
  double tLR;
  int Haux0_re_tmp;
  int i;
  //  --- PRIVATE HELPER METHOD ---
  //  This private method contains the logic to update filter coefficients.
  //  Recalculate the impulse responses with the new parameters
  //  Versión corregida y optimizada para la generación de código C++.
  //  - Pre-asigna memoria para todas las matrices.
  //  - Devuelve únicamente las dos IRs necesarias (cLL y cLR).
  //  --- Pre-asignación de memoria ---
  //  Esto le dice a MATLAB Coder el tamaño exacto de las matrices de antemano.
  //  H no es necesario si no se devuelve H2.
  //  C2 y H2 tampoco son necesarios si no se devuelven.
  a = params_dp / 2.0 - params_do / 2.0;
  r = params_D * params_D;
  dLL = std::sqrt(r + a * a);
  a = params_dp / 2.0 + params_do / 2.0;
  dLR = std::sqrt(r + a * a);
  tLL = dLL / 345.0;
  tLR = dLR / 345.0;
  //  Cálculo de la matriz de transferencia en frecuencia
  //  Reconstrucción del espectro completo con simetría Hermitiana
  //  Obtener la respuesta al impulso (real)
  //  Aplicar un pequeño retardo para hacer la respuesta causal
  //  10 ms delay
  ntdelay = std::round(0.01 * params_SampleRate);
  for (int naux{0}; naux < 4096; naux++) {
    double b_Haux0_re_tmp;
    double b_bim;
    double b_brm;
    double bim;
    double brm;
    double im;
    double r_im;
    double r_re;
    double re;
    double t_im;
    double t_re;
    a = 6.2831853071795862 *
        (0.0001220703125 * static_cast<double>(naux) * params_SampleRate);
    r_re = a * 0.0;
    t_re = tLL * r_re;
    t_im = tLL * -a;
    if (t_im == 0.0) {
      t_re = std::exp(t_re);
      t_im = 0.0;
    } else {
      r = std::exp(t_re / 2.0);
      t_re = r * (r * std::cos(t_im));
      t_im = r * (r * std::sin(t_im));
    }
    r_re *= tLR;
    r_im = tLR * -a;
    if (r_im == 0.0) {
      r_re = std::exp(r_re);
      r_im = 0.0;
    } else {
      r = std::exp(r_re / 2.0);
      r_re = r * (r * std::cos(r_im));
      r_im = r * (r * std::sin(r_im));
    }
    if (r_im == 0.0) {
      re = r_re / dLR;
      im = 0.0;
    } else if (r_re == 0.0) {
      re = 0.0;
      im = r_im / dLR;
    } else {
      re = r_re / dLR;
      im = r_im / dLR;
    }
    if (t_im == 0.0) {
      Haux0[0].re = t_re / dLL;
      Haux0[0].im = 0.0;
    } else if (t_re == 0.0) {
      Haux0[0].re = 0.0;
      Haux0[0].im = t_im / dLL;
    } else {
      Haux0[0].re = t_re / dLL;
      Haux0[0].im = t_im / dLL;
    }
    Haux0[2].re = re;
    Haux0[2].im = im;
    Haux0[1].re = re;
    Haux0[1].im = im;
    if (t_im == 0.0) {
      Haux0[3].re = t_re / dLL;
      Haux0[3].im = 0.0;
    } else if (t_re == 0.0) {
      Haux0[3].re = 0.0;
      Haux0[3].im = t_im / dLL;
    } else {
      Haux0[3].re = t_re / dLL;
      Haux0[3].im = t_im / dLL;
    }
    for (i = 0; i < 2; i++) {
      Haux0_re_tmp = i << 1;
      a = Haux0[Haux0_re_tmp].re;
      r = -Haux0[Haux0_re_tmp].im;
      b_Haux0_re_tmp = Haux0[Haux0_re_tmp + 1].re;
      t_im = -Haux0[Haux0_re_tmp + 1].im;
      x[i].re = ((a * Haux0[0].re - r * Haux0[0].im) +
                 (b_Haux0_re_tmp * re - t_im * im)) +
                params_beta * static_cast<double>(b[i]);
      x[i].im = (a * Haux0[0].im + r * Haux0[0].re) +
                (b_Haux0_re_tmp * im + t_im * re);
      x[i + 2].re = ((a * re - r * im) +
                     (b_Haux0_re_tmp * Haux0[3].re - t_im * Haux0[3].im)) +
                    params_beta * static_cast<double>(b[i + 2]);
      x[i + 2].im = (a * im + r * re) +
                    (b_Haux0_re_tmp * Haux0[3].im + t_im * Haux0[3].re);
    }
    brm = std::abs(x[0].re);
    b_brm = std::abs(x[1].re);
    bim = std::abs(x[0].im);
    b_bim = std::abs(x[1].im);
    if (b_brm + b_bim > brm + bim) {
      if (x[1].im == 0.0) {
        if (x[0].im == 0.0) {
          r_re = x[0].re / x[1].re;
          r_im = 0.0;
        } else if (x[0].re == 0.0) {
          r_re = 0.0;
          r_im = x[0].im / x[1].re;
        } else {
          r_re = x[0].re / x[1].re;
          r_im = x[0].im / x[1].re;
        }
      } else if (x[1].re == 0.0) {
        if (x[0].re == 0.0) {
          r_re = x[0].im / x[1].im;
          r_im = 0.0;
        } else if (x[0].im == 0.0) {
          r_re = 0.0;
          r_im = -(x[0].re / x[1].im);
        } else {
          r_re = x[0].im / x[1].im;
          r_im = -(x[0].re / x[1].im);
        }
      } else if (b_brm > b_bim) {
        b_Haux0_re_tmp = x[1].im / x[1].re;
        a = x[1].re + b_Haux0_re_tmp * x[1].im;
        r_re = (x[0].re + b_Haux0_re_tmp * x[0].im) / a;
        r_im = (x[0].im - b_Haux0_re_tmp * x[0].re) / a;
      } else if (b_bim == b_brm) {
        if (x[1].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[1].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r_re = (x[0].re * b_Haux0_re_tmp + x[0].im * a) / b_brm;
        r_im = (x[0].im * b_Haux0_re_tmp - x[0].re * a) / b_brm;
      } else {
        b_Haux0_re_tmp = x[1].re / x[1].im;
        a = x[1].im + b_Haux0_re_tmp * x[1].re;
        r_re = (b_Haux0_re_tmp * x[0].re + x[0].im) / a;
        r_im = (b_Haux0_re_tmp * x[0].im - x[0].re) / a;
      }
      a = (r_re * x[3].re - r_im * x[3].im) - x[2].re;
      r = (r_re * x[3].im + r_im * x[3].re) - x[2].im;
      if (r == 0.0) {
        t_re = 1.0 / a;
        t_im = 0.0;
      } else if (a == 0.0) {
        t_re = 0.0;
        t_im = -(1.0 / r);
      } else {
        brm = std::abs(a);
        bim = std::abs(r);
        if (brm > bim) {
          b_Haux0_re_tmp = r / a;
          a += b_Haux0_re_tmp * r;
          t_re = (b_Haux0_re_tmp * 0.0 + 1.0) / a;
          t_im = (0.0 - b_Haux0_re_tmp) / a;
        } else if (bim == brm) {
          if (a > 0.0) {
            b_Haux0_re_tmp = 0.5;
          } else {
            b_Haux0_re_tmp = -0.5;
          }
          if (r > 0.0) {
            a = 0.5;
          } else {
            a = -0.5;
          }
          t_re = (b_Haux0_re_tmp + 0.0 * a) / brm;
          t_im = (0.0 * b_Haux0_re_tmp - a) / brm;
        } else {
          b_Haux0_re_tmp = a / r;
          a = r + b_Haux0_re_tmp * a;
          t_re = b_Haux0_re_tmp / a;
          t_im = (b_Haux0_re_tmp * 0.0 - 1.0) / a;
        }
      }
      if (x[1].im == 0.0) {
        if (x[3].im == 0.0) {
          r = x[3].re / x[1].re;
          a = 0.0;
        } else if (x[3].re == 0.0) {
          r = 0.0;
          a = x[3].im / x[1].re;
        } else {
          r = x[3].re / x[1].re;
          a = x[3].im / x[1].re;
        }
      } else if (x[1].re == 0.0) {
        if (x[3].re == 0.0) {
          r = x[3].im / x[1].im;
          a = 0.0;
        } else if (x[3].im == 0.0) {
          r = 0.0;
          a = -(x[3].re / x[1].im);
        } else {
          r = x[3].im / x[1].im;
          a = -(x[3].re / x[1].im);
        }
      } else if (b_brm > b_bim) {
        b_Haux0_re_tmp = x[1].im / x[1].re;
        a = x[1].re + b_Haux0_re_tmp * x[1].im;
        r = (x[3].re + b_Haux0_re_tmp * x[3].im) / a;
        a = (x[3].im - b_Haux0_re_tmp * x[3].re) / a;
      } else if (b_bim == b_brm) {
        if (x[1].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[1].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r = (x[3].re * b_Haux0_re_tmp + x[3].im * a) / b_brm;
        a = (x[3].im * b_Haux0_re_tmp - x[3].re * a) / b_brm;
      } else {
        b_Haux0_re_tmp = x[1].re / x[1].im;
        a = x[1].im + b_Haux0_re_tmp * x[1].re;
        r = (b_Haux0_re_tmp * x[3].re + x[3].im) / a;
        a = (b_Haux0_re_tmp * x[3].im - x[3].re) / a;
      }
      b_a[0].re = r * t_re - a * t_im;
      b_a[0].im = r * t_im + a * t_re;
      b_a[1].re = -t_re;
      b_a[1].im = -t_im;
      if (x[1].im == 0.0) {
        if (-x[2].im == 0.0) {
          r = -x[2].re / x[1].re;
          a = 0.0;
        } else if (-x[2].re == 0.0) {
          r = 0.0;
          a = -x[2].im / x[1].re;
        } else {
          r = -x[2].re / x[1].re;
          a = -x[2].im / x[1].re;
        }
      } else if (x[1].re == 0.0) {
        if (-x[2].re == 0.0) {
          r = -x[2].im / x[1].im;
          a = 0.0;
        } else if (-x[2].im == 0.0) {
          r = 0.0;
          a = -(-x[2].re / x[1].im);
        } else {
          r = -x[2].im / x[1].im;
          a = -(-x[2].re / x[1].im);
        }
      } else if (b_brm > b_bim) {
        b_Haux0_re_tmp = x[1].im / x[1].re;
        a = x[1].re + b_Haux0_re_tmp * x[1].im;
        r = (-x[2].re + b_Haux0_re_tmp * -x[2].im) / a;
        a = (-x[2].im - b_Haux0_re_tmp * -x[2].re) / a;
      } else if (b_bim == b_brm) {
        if (x[1].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[1].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r = (-x[2].re * b_Haux0_re_tmp + -x[2].im * a) / b_brm;
        a = (-x[2].im * b_Haux0_re_tmp - -x[2].re * a) / b_brm;
      } else {
        b_Haux0_re_tmp = x[1].re / x[1].im;
        a = x[1].im + b_Haux0_re_tmp * x[1].re;
        r = (b_Haux0_re_tmp * -x[2].re + -x[2].im) / a;
        a = (b_Haux0_re_tmp * -x[2].im - (-x[2].re)) / a;
      }
      b_a[2].re = r * t_re - a * t_im;
      b_a[2].im = r * t_im + a * t_re;
      b_a[3].re = r_re * t_re - r_im * t_im;
      b_a[3].im = r_re * t_im + r_im * t_re;
    } else {
      if (x[0].im == 0.0) {
        if (x[1].im == 0.0) {
          r_re = x[1].re / x[0].re;
          r_im = 0.0;
        } else if (x[1].re == 0.0) {
          r_re = 0.0;
          r_im = x[1].im / x[0].re;
        } else {
          r_re = x[1].re / x[0].re;
          r_im = x[1].im / x[0].re;
        }
      } else if (x[0].re == 0.0) {
        if (x[1].re == 0.0) {
          r_re = x[1].im / x[0].im;
          r_im = 0.0;
        } else if (x[1].im == 0.0) {
          r_re = 0.0;
          r_im = -(x[1].re / x[0].im);
        } else {
          r_re = x[1].im / x[0].im;
          r_im = -(x[1].re / x[0].im);
        }
      } else if (brm > bim) {
        b_Haux0_re_tmp = x[0].im / x[0].re;
        a = x[0].re + b_Haux0_re_tmp * x[0].im;
        r_re = (x[1].re + b_Haux0_re_tmp * x[1].im) / a;
        r_im = (x[1].im - b_Haux0_re_tmp * x[1].re) / a;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[0].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r_re = (x[1].re * b_Haux0_re_tmp + x[1].im * a) / brm;
        r_im = (x[1].im * b_Haux0_re_tmp - x[1].re * a) / brm;
      } else {
        b_Haux0_re_tmp = x[0].re / x[0].im;
        a = x[0].im + b_Haux0_re_tmp * x[0].re;
        r_re = (b_Haux0_re_tmp * x[1].re + x[1].im) / a;
        r_im = (b_Haux0_re_tmp * x[1].im - x[1].re) / a;
      }
      a = x[3].re - (r_re * x[2].re - r_im * x[2].im);
      r = x[3].im - (r_re * x[2].im + r_im * x[2].re);
      if (r == 0.0) {
        t_re = 1.0 / a;
        t_im = 0.0;
      } else if (a == 0.0) {
        t_re = 0.0;
        t_im = -(1.0 / r);
      } else {
        b_brm = std::abs(a);
        b_bim = std::abs(r);
        if (b_brm > b_bim) {
          b_Haux0_re_tmp = r / a;
          a += b_Haux0_re_tmp * r;
          t_re = (b_Haux0_re_tmp * 0.0 + 1.0) / a;
          t_im = (0.0 - b_Haux0_re_tmp) / a;
        } else if (b_bim == b_brm) {
          if (a > 0.0) {
            b_Haux0_re_tmp = 0.5;
          } else {
            b_Haux0_re_tmp = -0.5;
          }
          if (r > 0.0) {
            a = 0.5;
          } else {
            a = -0.5;
          }
          t_re = (b_Haux0_re_tmp + 0.0 * a) / b_brm;
          t_im = (0.0 * b_Haux0_re_tmp - a) / b_brm;
        } else {
          b_Haux0_re_tmp = a / r;
          a = r + b_Haux0_re_tmp * a;
          t_re = b_Haux0_re_tmp / a;
          t_im = (b_Haux0_re_tmp * 0.0 - 1.0) / a;
        }
      }
      if (x[0].im == 0.0) {
        if (x[3].im == 0.0) {
          r = x[3].re / x[0].re;
          a = 0.0;
        } else if (x[3].re == 0.0) {
          r = 0.0;
          a = x[3].im / x[0].re;
        } else {
          r = x[3].re / x[0].re;
          a = x[3].im / x[0].re;
        }
      } else if (x[0].re == 0.0) {
        if (x[3].re == 0.0) {
          r = x[3].im / x[0].im;
          a = 0.0;
        } else if (x[3].im == 0.0) {
          r = 0.0;
          a = -(x[3].re / x[0].im);
        } else {
          r = x[3].im / x[0].im;
          a = -(x[3].re / x[0].im);
        }
      } else if (brm > bim) {
        b_Haux0_re_tmp = x[0].im / x[0].re;
        a = x[0].re + b_Haux0_re_tmp * x[0].im;
        r = (x[3].re + b_Haux0_re_tmp * x[3].im) / a;
        a = (x[3].im - b_Haux0_re_tmp * x[3].re) / a;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[0].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r = (x[3].re * b_Haux0_re_tmp + x[3].im * a) / brm;
        a = (x[3].im * b_Haux0_re_tmp - x[3].re * a) / brm;
      } else {
        b_Haux0_re_tmp = x[0].re / x[0].im;
        a = x[0].im + b_Haux0_re_tmp * x[0].re;
        r = (b_Haux0_re_tmp * x[3].re + x[3].im) / a;
        a = (b_Haux0_re_tmp * x[3].im - x[3].re) / a;
      }
      b_a[0].re = r * t_re - a * t_im;
      b_a[0].im = r * t_im + a * t_re;
      b_a[1].re = -r_re * t_re - -r_im * t_im;
      b_a[1].im = -r_re * t_im + -r_im * t_re;
      if (x[0].im == 0.0) {
        if (-x[2].im == 0.0) {
          r = -x[2].re / x[0].re;
          a = 0.0;
        } else if (-x[2].re == 0.0) {
          r = 0.0;
          a = -x[2].im / x[0].re;
        } else {
          r = -x[2].re / x[0].re;
          a = -x[2].im / x[0].re;
        }
      } else if (x[0].re == 0.0) {
        if (-x[2].re == 0.0) {
          r = -x[2].im / x[0].im;
          a = 0.0;
        } else if (-x[2].im == 0.0) {
          r = 0.0;
          a = -(-x[2].re / x[0].im);
        } else {
          r = -x[2].im / x[0].im;
          a = -(-x[2].re / x[0].im);
        }
      } else if (brm > bim) {
        b_Haux0_re_tmp = x[0].im / x[0].re;
        a = x[0].re + b_Haux0_re_tmp * x[0].im;
        r = (-x[2].re + b_Haux0_re_tmp * -x[2].im) / a;
        a = (-x[2].im - b_Haux0_re_tmp * -x[2].re) / a;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          b_Haux0_re_tmp = 0.5;
        } else {
          b_Haux0_re_tmp = -0.5;
        }
        if (x[0].im > 0.0) {
          a = 0.5;
        } else {
          a = -0.5;
        }
        r = (-x[2].re * b_Haux0_re_tmp + -x[2].im * a) / brm;
        a = (-x[2].im * b_Haux0_re_tmp - -x[2].re * a) / brm;
      } else {
        b_Haux0_re_tmp = x[0].re / x[0].im;
        a = x[0].im + b_Haux0_re_tmp * x[0].re;
        r = (b_Haux0_re_tmp * -x[2].re + -x[2].im) / a;
        a = (b_Haux0_re_tmp * -x[2].im - (-x[2].re)) / a;
      }
      b_a[2].re = r * t_re - a * t_im;
      b_a[2].im = r * t_im + a * t_re;
      b_a[3].re = t_re;
      b_a[3].im = t_im;
    }
    a = Haux0[0].re;
    r = Haux0[0].im;
    b_Haux0_re_tmp = Haux0[3].re;
    t_im = Haux0[3].im;
    for (i = 0; i < 2; i++) {
      brm = b_a[i].re;
      b_brm = b_a[i].im;
      bim = b_a[i + 2].re;
      b_bim = b_a[i + 2].im;
      Haux0_re_tmp = i + (naux << 2);
      b_C[Haux0_re_tmp].re = (brm * a - b_brm * -r) + (bim * re - b_bim * -im);
      b_C[Haux0_re_tmp].im = (brm * -r + b_brm * a) + (bim * -im + b_bim * re);
      b_C[Haux0_re_tmp + 2].re =
          (brm * re - b_brm * -im) + (bim * b_Haux0_re_tmp - b_bim * -t_im);
      b_C[Haux0_re_tmp + 2].im =
          (brm * -im + b_brm * re) + (bim * -t_im + b_bim * b_Haux0_re_tmp);
    }
    C[naux] = b_C[naux << 2];
  }
  C[4096].re = 0.0;
  C[4096].im = 0.0;
  for (i = 0; i < 4095; i++) {
    Haux0_re_tmp = (4095 - i) << 2;
    C[i + 4097].re = b_C[Haux0_re_tmp].re;
    C[i + 4097].im = -b_C[Haux0_re_tmp].im;
  }
  coder::ifft(C, dcv);
  for (i = 0; i < 8192; i++) {
    pFilter_LL.Numerator[i] = dcv[i].re;
  }
  coder::circshift(pFilter_LL.Numerator, ntdelay);
  for (i = 0; i < 4096; i++) {
    C[i] = b_C[(i << 2) + 1];
  }
  C[4096].re = 0.0;
  C[4096].im = 0.0;
  for (i = 0; i < 4095; i++) {
    Haux0_re_tmp = ((4095 - i) << 2) + 1;
    C[i + 4097].re = b_C[Haux0_re_tmp].re;
    C[i + 4097].im = -b_C[Haux0_re_tmp].im;
  }
  coder::ifft(C, dcv);
  for (i = 0; i < 8192; i++) {
    pFilter_RL.Numerator[i] = dcv[i].re;
  }
  coder::circshift(pFilter_RL.Numerator, ntdelay);
  //  Update the Numerator of the existing filter objects
  if (pFilter_LL.isInitialized == 1) {
    pFilter_LL.TunablePropsChanged = true;
  }
  if (pFilter_RL.isInitialized == 1) {
    pFilter_RL.TunablePropsChanged = true;
  }
  if (pFilter_LR.isInitialized == 1) {
    pFilter_LR.TunablePropsChanged = true;
  }
  std::copy(&pFilter_RL.Numerator[0], &pFilter_RL.Numerator[8192],
            &pFilter_LR.Numerator[0]);
  if (pFilter_RR.isInitialized == 1) {
    pFilter_RR.TunablePropsChanged = true;
  }
  std::copy(&pFilter_LL.Numerator[0], &pFilter_LL.Numerator[8192],
            &pFilter_RR.Numerator[0]);
}

// End of code generation (XTC_Processor.cpp)
