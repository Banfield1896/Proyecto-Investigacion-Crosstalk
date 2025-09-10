//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "xtc_processor_func.h"
#include "xtc_processor_func_terminate.h"
#include "xtc_processor_func_types.h"
#include "coder_array.h"

// Function Declarations
static coder::array<double, 2U> argInit_Unboundedx2_real_T();

static double argInit_real_T();

static struct0_T argInit_struct0_T();

static void main_xtc_processor_func();

// Function Definitions
static coder::array<double, 2U> argInit_Unboundedx2_real_T()
{
  coder::array<double, 2U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(2, 2);
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < result.size(0); idx0++) {
    for (int idx1{0}; idx1 < 2; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + result.size(0) * idx1] = argInit_real_T();
    }
  }
  return result;
}

static double argInit_real_T()
{
  return 0.0;
}

static struct0_T argInit_struct0_T()
{
  struct0_T result;
  double result_tmp;
  // Set the value of each structure field.
  // Change this value to the value that the application requires.
  result_tmp = argInit_real_T();
  result.dp = result_tmp;
  result.b_do = result_tmp;
  result.beta = result_tmp;
  result.SampleRate = result_tmp;
  result.D = result_tmp;
  return result;
}

static void main_xtc_processor_func()
{
  coder::array<double, 2U> in;
  coder::array<double, 2U> out;
  struct0_T r;
  // Initialize function 'xtc_processor_func' input arguments.
  // Initialize function input argument 'in'.
  in = argInit_Unboundedx2_real_T();
  // Initialize function input argument 'params'.
  // Call the entry-point 'xtc_processor_func'.
  r = argInit_struct0_T();
  xtc_processor_func(in, &r, out);
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_xtc_processor_func();
  // Terminate the application.
  // You do not need to do this more than one time.
  xtc_processor_func_terminate();
  return 0;
}

// End of code generation (main.cpp)
