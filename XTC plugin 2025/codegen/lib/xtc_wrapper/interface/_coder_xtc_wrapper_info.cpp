//
// _coder_xtc_wrapper_info.cpp
//
// Code generation for function 'xtc_wrapper'
//

// Include files
#include "_coder_xtc_wrapper_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

// Function Declarations
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

// Function Definitions
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char_T *data[8]{
      "789ced58bd6e1341101ea38042410814d4863e28101210a240b24962a2382676a20046ce"
      "b1dec497ecfd70b767ec9e8a86374079001e005a24fa94143c009450"
      "d12098dbbbf5cf91b3ad9c7306e7563acfceceec7cfb33de4fbb90caada600600abc7278"
      "cd93177c7dda9767a0bb04ed295f9e0de8d06a9fe8ea27ed6f7c490c",
      "9dd306f7145dd168ab67d5d0545dd179a96952b0a86db03aad0acb8eca6849d568b153c9"
      "bb9ab6d8616a29aec9ad676a94ec171d0dac9add1e21eb545aeb7190"
      "3a7abe1303aec7db90f5b8e4cb7bbee1293c80679081bb50860db001a78abf655805056b"
      "1c54d0f153f0d7c0d6359414b26851a18eb532dc821b3003056c3180",
      "608b8dbe1a5a297a726c4b4315eb6911f9d76f0598f029fb3d9aa8912ebf1cf6ab0b1f17"
      "7b17a3119406b6a671946e1f5bd8dc48fb47c499e91161e6c8085b50"
      "c2f63498a83be8af0aac9b308bdf3cda1be84ba0022fb1af825ea658a3eb38cbcefd3243"
      "f663d0fd0ae62704fca47dab94a9142c8350db36ac0efced63e2074b",
      "18be2cc3cacf83103c999ff75bf99949f2b3677e7af64ad71c6dac7939da2f3f2e0eb85f"
      "41d9f69f14f2c7d52fc21417ded4bbdaa738f16419155e2324dea0ff"
      "b72b2178d3017b96efacdf79d85c9e9fcd6fdece93c7eb9b0bf35b4bed7114fae0f41b07"
      "84e871c5df0ee97f52e764545e38df074fda6dca1d33a7996cc8f851",
      "79e973449ef810822f79c26af1c45ac214919822d5c35e16b3e618d5c4516902c12ba7e5"
      "fc1d77bcb8f865e3497e7361a998ddcb2fbfd8d8db6d1694b90249f8"
      "e5af3228bf44ddb7cb7df0a4dda24461c4610aa77895e5d4b2bbc7316a9ef91a91673e86"
      "e04b9e7995f04c2c3c638971b948046333ac716c59440c266aee5a03",
      "9c9e7379dcf112de194efce43de6ff38fde2e64b6e29baad3896c22aea30de0b25deb950"
      "7ccf52359ce78c8e223f93f7ecdef9c9c53bb62e66e6883ac36c5563"
      "7e2ffc16f37be1f7d7cb3fe3c49365dc79b59623e612595971b2b9627eae5eb45866e1d1"
      "18f1ea7648ff93bacf1d174fc69f0ce86d3ccf62732a9e09ff957bdb",
      "61445e781f822f79c14cee6d31bd0fbab7b3f6ebe0693967c71d2fb99f458bff0789207f"
      "f0",
      ""};
  nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&data[0], 8936U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties()
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *epFieldName[6]{
      "Name",           "NumberOfInputs", "NumberOfOutputs",
      "ConstantInputs", "FullPath",       "TimeStamp"};
  const char_T *propFieldName[5]{"Version", "ResolvedFunctions", "EntryPoints",
                                 "CoverageInfo", "IsPolymorphic"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, (const char_T *)"Name",
                emlrtMxCreateString((const char_T *)"xtc_wrapper"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfInputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, (const char_T *)"FullPath",
      emlrtMxCreateString(
          (const char_T *)"C:\\Users\\Martiniano\\OneDrive\\41-Procesamiento "
                          "de señales\\Proyecto de Investigacion "
                          "Crosstalk\\Proyecto-Investigacion-Crosstalk\\XT"
                          "C plugin 2025\\xtc_wrapper.m"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"TimeStamp",
                emlrtMxCreateDoubleScalar(739869.93575231486));
  xResult =
      emlrtCreateStructMatrix(1, 1, 5, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, (const char_T *)"Version",
                emlrtMxCreateString((const char_T *)"9.11.0.1769968 (R2021b)"));
  emlrtSetField(xResult, 0, (const char_T *)"ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, (const char_T *)"EntryPoints", xEntryPoints);
  return xResult;
}

// End of code generation (_coder_xtc_wrapper_info.cpp)
