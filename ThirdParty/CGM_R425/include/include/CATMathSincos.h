#ifndef CATMathSincos_h
#define CATMathSincos_h
/** @CAA2Required */

// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathSincos
//
//===========================================================================
// Usage notes:
//    macros de sinus + cosinus simultanes sous Intel PENTIUM...
//
//    #include "CATMath.h"
//    double angle, sinus, cosinus;
//    CATSincos ( angle, sinus, cosinus )
//
//    #include <math.h>   deja dans CATMath.h
//
//
//===========================================================================
// 09/10/15 NLD Restructuration pour une seule implementation pour tous les cas C++,
//              indentation
//              et ajout de {} dans cette macro comme le veut le bon usage
//              (anciennement non present dans CATSincos) (tous appelants Catia verifies/corriges)
//===========================================================================


                                                          #ifdef _SUNOS_SOURCE
// ------------------------------------------------------
// SUN only
// ------------------------------------------------------
#include <sunmath.h>
#define CATSincos( iANGLE, oSINUS, oCOSINUS )        \
sincos (iANGLE, &oSINUS, &oCOSINUS);
                                                          #else
                                                             #ifdef _ASM_ALLOWED
                                                                #ifdef WIN32
                                                                   #ifdef _M_IX86

// ------------------------------------------------------
// INTEL 32 bits only
// 3 arguments imperativement doubles, sans operateur C++
// ------------------------------------------------------
#define CATSincos( iANGLE, oSINUS, oCOSINUS )        \
   __asm                                             \
     {                                               \
     __asm fld  iANGLE                               \
     __asm fsincos                                   \
     __asm fstp oCOSINUS                             \
     __asm fstp oSINUS                               \
     }
                                                                   #endif                    // _M_IX86
                                                                #endif                    // WIN32
                                                             #endif                    // _ASM_ALLOWED
                                                          #endif                    // _SUNOS_SOURCE

#ifndef CATSincos

// ------------------------------------------------------
// Sinon C++
// ------------------------------------------------------
#define CATSincos( iANGLE, oSINUS, oCOSINUS )        \
  {oSINUS   = sin ( iANGLE );                        \
   oCOSINUS = cos ( iANGLE );}
#endif

#endif                    // CATMathSincos_h
