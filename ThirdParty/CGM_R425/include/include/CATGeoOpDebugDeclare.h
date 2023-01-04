// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// CATGeoOpDebugDefine:
//  - active CATGeoOpDebug define geometric operators
//  - to include in header files when we don't want the full CATGeoOpDebug class
//=============================================================================
//=============================================================================
// Usage notes:
//=============================================================================
// 15/01/20 Q48  Creation
//=============================================================================
#ifndef CATGeoOpDebugDeclare_H
#define CATGeoOpDebugDeclare_H

#include "CATGeoOpDebugSwitch.h"

// JSX == > USE NOW GEODEBUGSWITCH in file CATGeoOpDebugSwitch to activate traces
// Define GEOPDEBUG here to enable debug trace in the Geometric Operators code.

#ifdef GEOPDEBUG_SWITCH
#define GEOPDEBUG 
#else
#undef  GEOPDEBUG 
#endif

// Some macros for declare functions
#ifdef GEOPDEBUG
#define GEOPDEBUG_CMD(Cmd) Cmd;
#else
#define GEOPDEBUG_CMD(Cmd)
#endif

#endif // CATGeoOpDebugDeclare_H
