// ----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2014
// ---------------------------------------------------------------------------- 
// Environment variable to active CGM stream traces 
// ----------------------------------------------------------------------------

#ifndef CATActivateCGMStreamTraces_h
#define CATActivateCGMStreamTraces_h 

#include "CATLib.h"

// Debug trace
static int ActivateCGMStreamTraces = ::CATGetEnv("ActivateCGMStreamTraces")? 1 : 0;

static int ActiveIncrementalStreamTrace = CATGetEnv("ActiveIncrementalStreamTrace") ? 1 : 0;
static int ActiveCGMStreamPerfoTrace = CATGetEnv("ActiveCGMStreamPerfoTrace") ? 1 : 0;
static const char * CGMStreamDebugSavePath = CATGetEnv("CGMStreamDebugSavePath");
static const char * OpenSaveIncrementalStreamBuffer = CATGetEnv("OpenSaveIncrementalStreamBuffer");

// ODT Test
static int CGMIncrementalStreamFailureODTTest = CATGetEnv("CGMIncrementalStreamFailureODTTest") ? 1 : 0;

#endif

