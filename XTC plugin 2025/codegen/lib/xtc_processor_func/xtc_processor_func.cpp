//
// xtc_processor_func.cpp
//
// Code generation for function 'xtc_processor_func'
//

// Include files
#include "xtc_processor_func.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "FrequencyDomainFIRFilter.h"
#include "NoPartitionOS.h"
#include "cat.h"
#include "transaural_ir3.h"
#include "xtc_processor_func_data.h"
#include "xtc_processor_func_initialize.h"
#include "xtc_processor_func_types.h"
#include "coder_array.h"
#include <algorithm>

// Variable Definitions
static coder::dsp::FrequencyDomainFIRFilter pFilter_LL;

static coder::dsp::FrequencyDomainFIRFilter pFilter_RL;

static coder::dsp::FrequencyDomainFIRFilter pFilter_LR;

static coder::dsp::FrequencyDomainFIRFilter pFilter_RR;

static boolean_T isInitialized_not_empty;

// Function Definitions
void isInitialized_not_empty_init()
{
  isInitialized_not_empty = false;
}

void xtc_processor_func(const coder::array<double, 2U> &in,
                        const struct0_T *params, coder::array<double, 2U> &out)
{
  coder::array<double, 1U> b_in;
  coder::array<double, 1U> y_LL;
  coder::array<double, 1U> y_LR;
  coder::array<double, 1U> y_RL;
  coder::array<double, 1U> y_RR;
  int i;
  int loop_ub;
  boolean_T flag;
  if (!isInitialized_xtc_processor_func) {
    xtc_processor_func_initialize();
  }
  //  xtc_processor_func - DSP core for the Crosstalk plugin.
  //  This version uses a functional approach with persistent variables,
  //  making it compatible with older versions of MATLAB Coder like R2017b.
  //  %% CAMBIO CLAVE: Declarar los filtros como variables persistentes.
  //  Estas variables se crearán una sola vez y mantendrán su estado
  //  entre las llamadas a esta función.
  //  On the very first run, or if the sample rate changes, initialize.
  if (!isInitialized_not_empty) {
    //  Crear los objetos de filtro por primera vez
    pFilter_LL.NumChannels = -1;
    pFilter_LL.isInitialized = 0;
    pFilter_LL.matlabCodegenIsDeleted = false;
    pFilter_RL.NumChannels = -1;
    pFilter_RL.isInitialized = 0;
    pFilter_RL.matlabCodegenIsDeleted = false;
    pFilter_LR.NumChannels = -1;
    pFilter_LR.isInitialized = 0;
    pFilter_LR.matlabCodegenIsDeleted = false;
    pFilter_RR.NumChannels = -1;
    pFilter_RR.isInitialized = 0;
    pFilter_RR.matlabCodegenIsDeleted = false;
    //  Calcular la IR inicial con los parámetros por defecto
    transaural_ir3(params->D, params->dp, params->b_do, params->beta,
                   params->SampleRate, pFilter_LL.Numerator,
                   pFilter_RL.Numerator);
    //  Asignar los numeradores a los filtros
    flag = (pFilter_LL.isInitialized == 1);
    if (flag) {
      pFilter_LL.TunablePropsChanged = true;
    }
    flag = (pFilter_RL.isInitialized == 1);
    if (flag) {
      pFilter_RL.TunablePropsChanged = true;
    }
    flag = (pFilter_LR.isInitialized == 1);
    if (flag) {
      pFilter_LR.TunablePropsChanged = true;
    }
    std::copy(&pFilter_RL.Numerator[0], &pFilter_RL.Numerator[8192],
              &pFilter_LR.Numerator[0]);
    flag = (pFilter_RR.isInitialized == 1);
    if (flag) {
      pFilter_RR.TunablePropsChanged = true;
    }
    std::copy(&pFilter_LL.Numerator[0], &pFilter_LL.Numerator[8192],
              &pFilter_RR.Numerator[0]);
    isInitialized_not_empty = true;
  }
  //  --- Actualización de Parámetros (si es necesario) ---
  //  En un plugin real, esto se llamaría solo cuando un parámetro cambia.
  //  Aquí, para la generación de código, asumimos que 'params' puede cambiar
  //  en cada llamada, así que recalculamos.
  transaural_ir3(params->D, params->dp, params->b_do, params->beta,
                 params->SampleRate, pFilter_LL.Numerator,
                 pFilter_RL.Numerator);
  flag = (pFilter_LL.isInitialized == 1);
  if (flag) {
    pFilter_LL.TunablePropsChanged = true;
  }
  flag = (pFilter_RL.isInitialized == 1);
  if (flag) {
    pFilter_RL.TunablePropsChanged = true;
  }
  flag = (pFilter_LR.isInitialized == 1);
  if (flag) {
    pFilter_LR.TunablePropsChanged = true;
  }
  std::copy(&pFilter_RL.Numerator[0], &pFilter_RL.Numerator[8192],
            &pFilter_LR.Numerator[0]);
  flag = (pFilter_RR.isInitialized == 1);
  if (flag) {
    pFilter_RR.TunablePropsChanged = true;
  }
  std::copy(&pFilter_LL.Numerator[0], &pFilter_LL.Numerator[8192],
            &pFilter_RR.Numerator[0]);
  //  --- Procesamiento de Audio ---
  //  Usar 'step' en los objetos de filtro persistentes
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i];
  }
  pFilter_LL.step(b_in, y_LL);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i + in.size(0)];
  }
  pFilter_RL.step(b_in, y_RL);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i];
  }
  pFilter_LR.step(b_in, y_LR);
  loop_ub = in.size(0);
  b_in.set_size(in.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_in[i] = in[i + in.size(0)];
  }
  pFilter_RR.step(b_in, y_RR);
  //  Combinar las salidas
  if ((y_LL.size(0) == y_RL.size(0)) && (y_LR.size(0) == y_RR.size(0))) {
    out.set_size(y_LL.size(0), 2);
    loop_ub = y_LL.size(0);
    for (i = 0; i < loop_ub; i++) {
      out[i] = y_LL[i] + y_RL[i];
    }
    loop_ub = y_LR.size(0);
    for (i = 0; i < loop_ub; i++) {
      out[i + out.size(0)] = y_LR[i] + y_RR[i];
    }
  } else {
    binary_expand_op(out, y_LL, y_RL, y_LR, y_RR);
  }
}

void xtc_processor_func_free()
{
  coder::dsp::AsyncBuffer *b_obj;
  coder::dsp::internal::NoPartitionOS *obj;
  if (!pFilter_LL.matlabCodegenIsDeleted) {
    pFilter_LL.matlabCodegenIsDeleted = true;
    if (pFilter_LL.isInitialized == 1) {
      pFilter_LL.isInitialized = 2;
      if (pFilter_LL.isSetupComplete) {
        if (pFilter_LL.pFilter.isInitialized == 1) {
          pFilter_LL.pFilter.isInitialized = 2;
        }
        pFilter_LL.NumChannels = -1;
      }
    }
  }
  if (!pFilter_RL.matlabCodegenIsDeleted) {
    pFilter_RL.matlabCodegenIsDeleted = true;
    if (pFilter_RL.isInitialized == 1) {
      pFilter_RL.isInitialized = 2;
      if (pFilter_RL.isSetupComplete) {
        if (pFilter_RL.pFilter.isInitialized == 1) {
          pFilter_RL.pFilter.isInitialized = 2;
        }
        pFilter_RL.NumChannels = -1;
      }
    }
  }
  if (!pFilter_LR.matlabCodegenIsDeleted) {
    pFilter_LR.matlabCodegenIsDeleted = true;
    if (pFilter_LR.isInitialized == 1) {
      pFilter_LR.isInitialized = 2;
      if (pFilter_LR.isSetupComplete) {
        if (pFilter_LR.pFilter.isInitialized == 1) {
          pFilter_LR.pFilter.isInitialized = 2;
        }
        pFilter_LR.NumChannels = -1;
      }
    }
  }
  if (!pFilter_RR.matlabCodegenIsDeleted) {
    pFilter_RR.matlabCodegenIsDeleted = true;
    if (pFilter_RR.isInitialized == 1) {
      pFilter_RR.isInitialized = 2;
      if (pFilter_RR.isSetupComplete) {
        if (pFilter_RR.pFilter.isInitialized == 1) {
          pFilter_RR.pFilter.isInitialized = 2;
        }
        pFilter_RR.NumChannels = -1;
      }
    }
  }
  obj = &pFilter_LL.pFilter;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }
  obj = &pFilter_RL.pFilter;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }
  obj = &pFilter_LR.pFilter;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }
  obj = &pFilter_RR.pFilter;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }
  b_obj = &pFilter_LL.pFilter.pinBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_LL.pFilter.poutBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_RL.pFilter.pinBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_RL.pFilter.poutBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_LR.pFilter.pinBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_LR.pFilter.poutBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_RR.pFilter.pinBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  b_obj = &pFilter_RR.pFilter.poutBuff;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
  }
  pFilter_LL.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  pFilter_LL.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  pFilter_RL.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  pFilter_RL.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  pFilter_LR.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  pFilter_LR.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
  pFilter_RR.pFilter.pinBuff.pBuffer.matlabCodegenDestructor();
  pFilter_RR.pFilter.poutBuff.pBuffer.matlabCodegenDestructor();
}

void xtc_processor_func_init()
{
  pFilter_RR.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_RR.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_LR.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_LR.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_RL.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_RL.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_LL.pFilter.poutBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_LL.pFilter.pinBuff.pBuffer.matlabCodegenIsDeleted = true;
  pFilter_RR.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  pFilter_RR.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  pFilter_LR.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  pFilter_LR.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  pFilter_RL.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  pFilter_RL.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  pFilter_LL.pFilter.poutBuff.matlabCodegenIsDeleted = true;
  pFilter_LL.pFilter.pinBuff.matlabCodegenIsDeleted = true;
  pFilter_RR.pFilter.matlabCodegenIsDeleted = true;
  pFilter_LR.pFilter.matlabCodegenIsDeleted = true;
  pFilter_RL.pFilter.matlabCodegenIsDeleted = true;
  pFilter_LL.pFilter.matlabCodegenIsDeleted = true;
  pFilter_RR.matlabCodegenIsDeleted = true;
  pFilter_LR.matlabCodegenIsDeleted = true;
  pFilter_RL.matlabCodegenIsDeleted = true;
  pFilter_LL.matlabCodegenIsDeleted = true;
}

// End of code generation (xtc_processor_func.cpp)
