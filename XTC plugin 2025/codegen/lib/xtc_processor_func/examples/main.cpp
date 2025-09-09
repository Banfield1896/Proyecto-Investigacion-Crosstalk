//
// File: main.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 07-Sep-2025 14:36:14
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "xtc_processor_func.h"
#include "main.h"
#include "xtc_processor_func_terminate.h"
#include "xtc_processor_func_emxAPI.h"
#include "xtc_processor_func_initialize.h"

// Function Declarations
static emxArray_real_T *argInit_Unboundedx2_real_T();
static double argInit_real_T();
static struct0_T argInit_struct0_T();
static void main_xtc_processor_func();

// Function Definitions

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_Unboundedx2_real_T()
{
  emxArray_real_T *result;
  static int iv1[2] = { 2, 2 };

  int idx0;
  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreateND_real_T(2, *(int (*)[2])&iv1[0]);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : struct0_T
//
static struct0_T argInit_struct0_T()
{
  struct0_T result;

  // Set the value of each structure field.
  // Change this value to the value that the application requires.
  result.D = argInit_real_T();
  result.dp = argInit_real_T();
  result.b_do = argInit_real_T();
  result.beta = argInit_real_T();
  result.SampleRate = argInit_real_T();
  return result;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_xtc_processor_func()
{
  emxArray_real_T *out;
  emxArray_real_T *in;
  struct0_T r2;
  emxInitArray_real_T(&out, 2);

  // Initialize function 'xtc_processor_func' input arguments.
  // Initialize function input argument 'in'.
  in = argInit_Unboundedx2_real_T();

  // Initialize function input argument 'params'.
  // Call the entry-point 'xtc_processor_func'.
  r2 = argInit_struct0_T();
  xtc_processor_func(in, &r2, out);
  emxDestroyArray_real_T(out);
  emxDestroyArray_real_T(in);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  xtc_processor_func_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_xtc_processor_func();

  // Terminate the application.
  // You do not need to do this more than one time.
  xtc_processor_func_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
