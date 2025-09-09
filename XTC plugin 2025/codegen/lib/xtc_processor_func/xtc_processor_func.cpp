//
// File: xtc_processor_func.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "xtc_processor_func_emxutil.h"
#include "SystemCore.h"
#include "FrequencyDomainFIRFilter.h"
#include "transaural_ir3.h"

// Variable Definitions
static dsp_FrequencyDomainFIRFilter pFilter_LL;
static dsp_FrequencyDomainFIRFilter pFilter_RL;
static dsp_FrequencyDomainFIRFilter pFilter_LR;
static dsp_FrequencyDomainFIRFilter pFilter_RR;
static boolean_T isInitialized_not_empty;

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void isInitialized_not_empty_init()
{
  isInitialized_not_empty = false;
}

//
// xtc_processor_func - DSP core for the Crosstalk plugin.
//  This version uses a functional approach with persistent variables,
//  making it compatible with older versions of MATLAB Coder like R2017b.
// Arguments    : const emxArray_real_T *in
//                const struct0_T *params
//                emxArray_real_T *out
// Return Type  : void
//
void xtc_processor_func(const emxArray_real_T *in, const struct0_T *params,
  emxArray_real_T *out)
{
  static double cLL[8192];
  static double cLR[8192];
  boolean_T flag;
  emxArray_real_T *left_in;
  int loop_ub;
  int i0;
  emxArray_real_T *right_in;
  emxArray_real_T *y_LL;
  emxArray_real_T *y_RL;
  emxArray_real_T *y_LR;

  //  %% CAMBIO CLAVE: Declarar los filtros como variables persistentes.
  //  Estas variables se crearán una sola vez y mantendrán su estado
  //  entre las llamadas a esta función.
  //  On the very first run, or if the sample rate changes, initialize.
  if (!isInitialized_not_empty) {
    //  Crear los objetos de filtro por primera vez
    pFilter_LL.NumChannels = -1;
    pFilter_LL.isInitialized = 0;
    pFilter_RL.NumChannels = -1;
    pFilter_RL.isInitialized = 0;
    pFilter_LR.NumChannels = -1;
    pFilter_LR.isInitialized = 0;
    pFilter_RR.NumChannels = -1;
    pFilter_RR.isInitialized = 0;

    //  Calcular la IR inicial con los parámetros por defecto
    transaural_ir3(params->D, params->dp, params->b_do, params->beta,
                   params->SampleRate, cLL, cLR);

    //  Asignar los numeradores a los filtros
    flag = (pFilter_LL.isInitialized == 1);
    if (flag) {
      pFilter_LL.TunablePropsChanged = true;
    }

    c_FrequencyDomainFIRFilter_set_(&pFilter_LL, cLL);
    flag = (pFilter_RL.isInitialized == 1);
    if (flag) {
      pFilter_RL.TunablePropsChanged = true;
    }

    c_FrequencyDomainFIRFilter_set_(&pFilter_RL, cLR);
    flag = (pFilter_LR.isInitialized == 1);
    if (flag) {
      pFilter_LR.TunablePropsChanged = true;
    }

    c_FrequencyDomainFIRFilter_set_(&pFilter_LR, cLR);
    flag = (pFilter_RR.isInitialized == 1);
    if (flag) {
      pFilter_RR.TunablePropsChanged = true;
    }

    c_FrequencyDomainFIRFilter_set_(&pFilter_RR, cLL);
    isInitialized_not_empty = true;
  }

  //  --- Actualización de Parámetros (si es necesario) ---
  //  En un plugin real, esto se llamaría solo cuando un parámetro cambia.
  //  Aquí, para la generación de código, asumimos que 'params' puede cambiar
  //  en cada llamada, así que recalculamos.
  transaural_ir3(params->D, params->dp, params->b_do, params->beta,
                 params->SampleRate, cLL, cLR);
  flag = (pFilter_LL.isInitialized == 1);
  if (flag) {
    pFilter_LL.TunablePropsChanged = true;
  }

  c_FrequencyDomainFIRFilter_set_(&pFilter_LL, cLL);
  flag = (pFilter_RL.isInitialized == 1);
  if (flag) {
    pFilter_RL.TunablePropsChanged = true;
  }

  c_FrequencyDomainFIRFilter_set_(&pFilter_RL, cLR);
  flag = (pFilter_LR.isInitialized == 1);
  if (flag) {
    pFilter_LR.TunablePropsChanged = true;
  }

  c_FrequencyDomainFIRFilter_set_(&pFilter_LR, cLR);
  flag = (pFilter_RR.isInitialized == 1);
  if (flag) {
    pFilter_RR.TunablePropsChanged = true;
  }

  emxInit_real_T(&left_in, 1);
  c_FrequencyDomainFIRFilter_set_(&pFilter_RR, cLL);

  //  --- Procesamiento de Audio ---
  loop_ub = in->size[0];
  i0 = left_in->size[0];
  left_in->size[0] = loop_ub;
  emxEnsureCapacity_real_T(left_in, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    left_in->data[i0] = in->data[i0];
  }

  emxInit_real_T(&right_in, 1);
  loop_ub = in->size[0];
  i0 = right_in->size[0];
  right_in->size[0] = loop_ub;
  emxEnsureCapacity_real_T(right_in, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    right_in->data[i0] = in->data[i0 + in->size[0]];
  }

  emxInit_real_T(&y_LL, 1);
  emxInit_real_T(&y_RL, 1);
  emxInit_real_T(&y_LR, 1);

  //  Usar 'step' en los objetos de filtro persistentes
  SystemCore_step(&pFilter_LL, left_in, y_LL);
  SystemCore_step(&pFilter_RL, right_in, y_RL);
  SystemCore_step(&pFilter_LR, left_in, y_LR);
  SystemCore_step(&pFilter_RR, right_in, left_in);

  //  Combinar las salidas
  i0 = out->size[0] * out->size[1];
  out->size[0] = y_LL->size[0];
  out->size[1] = 2;
  emxEnsureCapacity_real_T1(out, i0);
  loop_ub = y_LL->size[0];
  emxFree_real_T(&right_in);
  for (i0 = 0; i0 < loop_ub; i0++) {
    out->data[i0] = y_LL->data[i0] + y_RL->data[i0];
  }

  emxFree_real_T(&y_RL);
  emxFree_real_T(&y_LL);
  loop_ub = y_LR->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    out->data[i0 + out->size[0]] = y_LR->data[i0] + left_in->data[i0];
  }

  emxFree_real_T(&y_LR);
  emxFree_real_T(&left_in);
}

//
// File trailer for xtc_processor_func.cpp
//
// [EOF]
//
