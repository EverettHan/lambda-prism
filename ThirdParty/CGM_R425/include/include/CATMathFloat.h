//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// Define some float function independent of the system
// 
//=============================================================================
// INLINE Functions   : Yes
//=============================================================================

#ifndef CATMATHFLOAT_H
#define CATMATHFLOAT_H

#include <math.h>
#include "CATMathInline.h"

//
// Compilator on IRIX : the float function are defined
// To benefit of fast square root, you have to had the 
// option `SYS_LIBS = -lfastm` in your Imakefile.mk
// on IRIX only
#ifdef _IRIX_SOURCE

#define CATSqrtf  sqrtf
#define CATFabsf  fabsf

//
//  Other systems
//

#else

INLINE float CATSqrtf(float iEntry)
{
  return (float) sqrt(iEntry);
}

INLINE float CATFabsf(float iEntry)
{
  return (float) fabs(iEntry);
}


#endif

INLINE float CATInvSqrtf(float iEntry)
{
  return ( (float) 1. / CATSqrtf(iEntry) );
}

#endif
 
