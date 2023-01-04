#ifndef CATCGMVersionningDefVarGEO_h
#define CATCGMVersionningDefVarGEO_h

// ExportedBy macros 
#include "ExportedByCATMathStream.h"

// C++11
#include "CATMathCpp11.h"

// Manual flags (and importantly the manual versioning macro)
#include "CATMathLocalVersioning.h"

// ---------------------------------------------------------------------------------------------------------------
// Q48 (08/07/19): Some simple mechanism to allow newly defined variables to be activated in the environment
// ---------------------------------------------------------------------------------------------------------------
// The definition of the flags is now in CATCGMVersionningDefVarGEO_Flag.h
//     **** please keep this file tidy by removing variables once they have been offically declared ****
// ---------------------------------------------------------------------------------------------------------------

#ifdef MATH_CPP11
#define GEO_FLAG_OBJ(flag, level) extern ExportedByCATMathStream const ManualVersioningData_Flag* flag;
#else
#define GEO_FLAG_OBJ(flag, level) extern ExportedByCATMathStream const short flag;
#endif

#include "CATCGMVersionningDefVarGEO_Flag.h" // the list of flags

#endif // CATCGMVersionningDefVarGEO_h
