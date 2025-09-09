//
// File: xtc_processor_func_types.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//
#ifndef XTC_PROCESSOR_FUNC_TYPES_H
#define XTC_PROCESSOR_FUNC_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
typedef struct {
  unsigned int f1[8];
} cell_wrap_2;

typedef struct {
  int isInitialized;
  cell_wrap_2 inputVarSize[1];
  double Cache[8194];
  int NumChannels;
  int ReadPointer;
  int WritePointer;
  int CumulativeOverrun;
  int CumulativeUnderrun;
  boolean_T AsyncBuffer_isInitialized;
} dsp_AsyncBuffer;

typedef struct {
  int isInitialized;
  boolean_T TunablePropsChanged;
  double Numerator[8192];
  double pLastSection[8191];
  creal_T H[16384];
  dsp_AsyncBuffer pinBuff;
  dsp_AsyncBuffer poutBuff;
} dsp_private_NoPartitionOS;

typedef struct {
  int isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_2 inputVarSize[1];
  double Numerator[8192];
  dsp_private_NoPartitionOS pFilter;
  int NumChannels;
} dsp_FrequencyDomainFIRFilter;

#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T

struct emxArray_int16_T
{
  short *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int16_T

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int32_T

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_real_T

typedef struct {
  double D;
  double dp;
  double b_do;
  double beta;
  double SampleRate;
} struct0_T;

#endif

//
// File trailer for xtc_processor_func_types.h
//
// [EOF]
//
