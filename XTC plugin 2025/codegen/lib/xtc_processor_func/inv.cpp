//
// File: inv.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "inv.h"

// Function Definitions

//
// Arguments    : const creal_T x[4]
//                creal_T y[4]
// Return Type  : void
//
void inv(const creal_T x[4], creal_T y[4])
{
  double brm;
  double r_re;
  double bim;
  double r_im;
  double d;
  double bi;
  double t_re;
  double t_im;
  if (std::abs(x[1].re) + std::abs(x[1].im) > std::abs(x[0].re) + std::abs(x[0].
       im)) {
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
    } else {
      brm = std::abs(x[1].re);
      bim = std::abs(x[1].im);
      if (brm > bim) {
        bim = x[1].im / x[1].re;
        d = x[1].re + bim * x[1].im;
        r_re = (x[0].re + bim * x[0].im) / d;
        r_im = (x[0].im - bim * x[0].re) / d;
      } else if (bim == brm) {
        if (x[1].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[1].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        r_re = (x[0].re * bim + x[0].im * d) / brm;
        r_im = (x[0].im * bim - x[0].re * d) / brm;
      } else {
        bim = x[1].re / x[1].im;
        d = x[1].im + bim * x[1].re;
        r_re = (bim * x[0].re + x[0].im) / d;
        r_im = (bim * x[0].im - x[0].re) / d;
      }
    }

    d = (r_re * x[3].re - r_im * x[3].im) - x[2].re;
    bi = (r_re * x[3].im + r_im * x[3].re) - x[2].im;
    if (bi == 0.0) {
      t_re = 1.0 / d;
      t_im = 0.0;
    } else if (d == 0.0) {
      t_re = 0.0;
      t_im = -(1.0 / bi);
    } else {
      brm = std::abs(d);
      bim = std::abs(bi);
      if (brm > bim) {
        bim = bi / d;
        d += bim * bi;
        t_re = (1.0 + bim * 0.0) / d;
        t_im = (0.0 - bim) / d;
      } else if (bim == brm) {
        if (d > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (bi > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        t_re = (bim + 0.0 * d) / brm;
        t_im = (0.0 * bim - d) / brm;
      } else {
        bim = d / bi;
        d = bi + bim * d;
        t_re = bim / d;
        t_im = (bim * 0.0 - 1.0) / d;
      }
    }

    if (x[1].im == 0.0) {
      if (x[3].im == 0.0) {
        bi = x[3].re / x[1].re;
        d = 0.0;
      } else if (x[3].re == 0.0) {
        bi = 0.0;
        d = x[3].im / x[1].re;
      } else {
        bi = x[3].re / x[1].re;
        d = x[3].im / x[1].re;
      }
    } else if (x[1].re == 0.0) {
      if (x[3].re == 0.0) {
        bi = x[3].im / x[1].im;
        d = 0.0;
      } else if (x[3].im == 0.0) {
        bi = 0.0;
        d = -(x[3].re / x[1].im);
      } else {
        bi = x[3].im / x[1].im;
        d = -(x[3].re / x[1].im);
      }
    } else {
      brm = std::abs(x[1].re);
      bim = std::abs(x[1].im);
      if (brm > bim) {
        bim = x[1].im / x[1].re;
        d = x[1].re + bim * x[1].im;
        bi = (x[3].re + bim * x[3].im) / d;
        d = (x[3].im - bim * x[3].re) / d;
      } else if (bim == brm) {
        if (x[1].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[1].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        bi = (x[3].re * bim + x[3].im * d) / brm;
        d = (x[3].im * bim - x[3].re * d) / brm;
      } else {
        bim = x[1].re / x[1].im;
        d = x[1].im + bim * x[1].re;
        bi = (bim * x[3].re + x[3].im) / d;
        d = (bim * x[3].im - x[3].re) / d;
      }
    }

    y[0].re = bi * t_re - d * t_im;
    y[0].im = bi * t_im + d * t_re;
    y[1].re = -t_re;
    y[1].im = -t_im;
    if (x[1].im == 0.0) {
      if (-x[2].im == 0.0) {
        bi = -x[2].re / x[1].re;
        d = 0.0;
      } else if (-x[2].re == 0.0) {
        bi = 0.0;
        d = -x[2].im / x[1].re;
      } else {
        bi = -x[2].re / x[1].re;
        d = -x[2].im / x[1].re;
      }
    } else if (x[1].re == 0.0) {
      if (-x[2].re == 0.0) {
        bi = -x[2].im / x[1].im;
        d = 0.0;
      } else if (-x[2].im == 0.0) {
        bi = 0.0;
        d = -(-x[2].re / x[1].im);
      } else {
        bi = -x[2].im / x[1].im;
        d = -(-x[2].re / x[1].im);
      }
    } else {
      brm = std::abs(x[1].re);
      bim = std::abs(x[1].im);
      if (brm > bim) {
        bim = x[1].im / x[1].re;
        d = x[1].re + bim * x[1].im;
        bi = (-x[2].re + bim * -x[2].im) / d;
        d = (-x[2].im - bim * -x[2].re) / d;
      } else if (bim == brm) {
        if (x[1].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[1].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        bi = (-x[2].re * bim + -x[2].im * d) / brm;
        d = (-x[2].im * bim - -x[2].re * d) / brm;
      } else {
        bim = x[1].re / x[1].im;
        d = x[1].im + bim * x[1].re;
        bi = (bim * -x[2].re + -x[2].im) / d;
        d = (bim * -x[2].im - (-x[2].re)) / d;
      }
    }

    y[2].re = bi * t_re - d * t_im;
    y[2].im = bi * t_im + d * t_re;
    y[3].re = r_re * t_re - r_im * t_im;
    y[3].im = r_re * t_im + r_im * t_re;
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
    } else {
      brm = std::abs(x[0].re);
      bim = std::abs(x[0].im);
      if (brm > bim) {
        bim = x[0].im / x[0].re;
        d = x[0].re + bim * x[0].im;
        r_re = (x[1].re + bim * x[1].im) / d;
        r_im = (x[1].im - bim * x[1].re) / d;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[0].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        r_re = (x[1].re * bim + x[1].im * d) / brm;
        r_im = (x[1].im * bim - x[1].re * d) / brm;
      } else {
        bim = x[0].re / x[0].im;
        d = x[0].im + bim * x[0].re;
        r_re = (bim * x[1].re + x[1].im) / d;
        r_im = (bim * x[1].im - x[1].re) / d;
      }
    }

    d = x[3].re - (r_re * x[2].re - r_im * x[2].im);
    bi = x[3].im - (r_re * x[2].im + r_im * x[2].re);
    if (bi == 0.0) {
      t_re = 1.0 / d;
      t_im = 0.0;
    } else if (d == 0.0) {
      t_re = 0.0;
      t_im = -(1.0 / bi);
    } else {
      brm = std::abs(d);
      bim = std::abs(bi);
      if (brm > bim) {
        bim = bi / d;
        d += bim * bi;
        t_re = (1.0 + bim * 0.0) / d;
        t_im = (0.0 - bim) / d;
      } else if (bim == brm) {
        if (d > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (bi > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        t_re = (bim + 0.0 * d) / brm;
        t_im = (0.0 * bim - d) / brm;
      } else {
        bim = d / bi;
        d = bi + bim * d;
        t_re = bim / d;
        t_im = (bim * 0.0 - 1.0) / d;
      }
    }

    if (x[0].im == 0.0) {
      if (x[3].im == 0.0) {
        bi = x[3].re / x[0].re;
        d = 0.0;
      } else if (x[3].re == 0.0) {
        bi = 0.0;
        d = x[3].im / x[0].re;
      } else {
        bi = x[3].re / x[0].re;
        d = x[3].im / x[0].re;
      }
    } else if (x[0].re == 0.0) {
      if (x[3].re == 0.0) {
        bi = x[3].im / x[0].im;
        d = 0.0;
      } else if (x[3].im == 0.0) {
        bi = 0.0;
        d = -(x[3].re / x[0].im);
      } else {
        bi = x[3].im / x[0].im;
        d = -(x[3].re / x[0].im);
      }
    } else {
      brm = std::abs(x[0].re);
      bim = std::abs(x[0].im);
      if (brm > bim) {
        bim = x[0].im / x[0].re;
        d = x[0].re + bim * x[0].im;
        bi = (x[3].re + bim * x[3].im) / d;
        d = (x[3].im - bim * x[3].re) / d;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[0].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        bi = (x[3].re * bim + x[3].im * d) / brm;
        d = (x[3].im * bim - x[3].re * d) / brm;
      } else {
        bim = x[0].re / x[0].im;
        d = x[0].im + bim * x[0].re;
        bi = (bim * x[3].re + x[3].im) / d;
        d = (bim * x[3].im - x[3].re) / d;
      }
    }

    y[0].re = bi * t_re - d * t_im;
    y[0].im = bi * t_im + d * t_re;
    y[1].re = -r_re * t_re - -r_im * t_im;
    y[1].im = -r_re * t_im + -r_im * t_re;
    if (x[0].im == 0.0) {
      if (-x[2].im == 0.0) {
        bi = -x[2].re / x[0].re;
        d = 0.0;
      } else if (-x[2].re == 0.0) {
        bi = 0.0;
        d = -x[2].im / x[0].re;
      } else {
        bi = -x[2].re / x[0].re;
        d = -x[2].im / x[0].re;
      }
    } else if (x[0].re == 0.0) {
      if (-x[2].re == 0.0) {
        bi = -x[2].im / x[0].im;
        d = 0.0;
      } else if (-x[2].im == 0.0) {
        bi = 0.0;
        d = -(-x[2].re / x[0].im);
      } else {
        bi = -x[2].im / x[0].im;
        d = -(-x[2].re / x[0].im);
      }
    } else {
      brm = std::abs(x[0].re);
      bim = std::abs(x[0].im);
      if (brm > bim) {
        bim = x[0].im / x[0].re;
        d = x[0].re + bim * x[0].im;
        bi = (-x[2].re + bim * -x[2].im) / d;
        d = (-x[2].im - bim * -x[2].re) / d;
      } else if (bim == brm) {
        if (x[0].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (x[0].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        bi = (-x[2].re * bim + -x[2].im * d) / brm;
        d = (-x[2].im * bim - -x[2].re * d) / brm;
      } else {
        bim = x[0].re / x[0].im;
        d = x[0].im + bim * x[0].re;
        bi = (bim * -x[2].re + -x[2].im) / d;
        d = (bim * -x[2].im - (-x[2].re)) / d;
      }
    }

    y[2].re = bi * t_re - d * t_im;
    y[2].im = bi * t_im + d * t_re;
    y[3].re = t_re;
    y[3].im = t_im;
  }
}

//
// File trailer for inv.cpp
//
// [EOF]
//
