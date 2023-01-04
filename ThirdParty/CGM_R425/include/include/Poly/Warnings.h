
#pragma once

#include "CATErrorDef.h"


#define ENABLE_WARNINGS
#define PRINT_WARNING_FUNCTION
#define PRINT_WARNING_LOCATION


#ifdef ENABLE_WARNINGS

#include "CATCGMOutput.h"
#include "CATLib.h"

static void PrintWarning(const char* error, const char* code, const char* function, const char* file, int line) {
#ifdef PRINT_WARNING_LOCATION
  char fileName[CATMaxPathSize + 1];
  char dirPath[CATMaxPathSize + 1];
  CATSplitPath(file, dirPath, fileName);
#endif
#ifdef PRINT_WARNING_ODT
  cgmodt
#else
  cgmout
#endif
    << "WARNING: " << error << " " << code
#ifdef PRINT_WARNING_FUNCTION
    << " in " << function
#endif
#ifdef PRINT_WARNING_LOCATION
    << " at " << fileName << ":" << line
#endif
    << cgmendl;
}

#define WARN_IF_FAIL(a) WarnIfFail(a, #a, __FUNCTION__, __FILE__, __LINE__)

static HRESULT WarnIfFail(HRESULT hr, const char* code, const char* function, const char* file, int line) {
  if (!SUCCEEDED(hr))
    PrintWarning("failure of", code, function, file, line);
  return hr;
}

#define WARN_IF_NULL(a) WarnIfNull(a, #a, __FUNCTION__, __FILE__, __LINE__)

static void* WarnIfNull(void* ptr, const char* code, const char* function, const char* file, int line) {
  if (!ptr)
    PrintWarning("nullptr returned by", code, function, file, line);
  return ptr;
}

#define WARN_IF_FALSE(a) WarnIfFalse(a, #a, __FUNCTION__, __FILE__, __LINE__)

static bool WarnIfFalse(bool condition, const char* code, const char* function, const char* file, int line) {
  if (!condition)
    PrintWarning("false returned by", code, function, file, line);
  return condition;
}

#define RETURN_IF_NULL(a) if (!a) { \
  PrintWarning("nullptr returned by", #a, __FUNCTION__, __FILE__, __LINE__); \
  return E_FAIL; \
}


#else

#define HR_WARN(a) a
#define NULL_WARN(a) a
#define FALSE_WARN(a) a

#define RETURN_IF_NULL(a) if (!a) \
  return E_FAIL;

#endif


#define RETURN_IF_FAIL(a) { \
  HRESULT hr = WARN_IF_FAIL(a); \
  if (FAILED(hr)) \
    return hr; \
}

#define RETURN_IF_FALSE(a) { \
  if (!(WARN_IF_FALSE(a))) \
    return E_FAIL; \
}

// RETURN_IF_NULL cannot be implemented the same way as RETURN_IF_FAIL and RETURN_IF_FALSE because mkmk needs a
// direct pointer check in order not to create a LCLVMCBU1 issue.


