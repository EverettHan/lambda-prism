/* -*-C++-*- */

#ifndef CATIS_H
#define CATIS_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : List of Macros to simplify the use of CATCompare(a,b,tol) from CATMathFP.h
               You have to combine 2 Macros.
               CATIS(a)GT(b,tol)
               EQ : Equal To
               LT : Less Than
               GT : Greater Than
               LE : Less than or Equal to
               GE : Greater than or Equal to
=============================================================================

Samples of code
----------------

#include "CATIS.h" // To simplify the use of CATCompare(a,b,tol)

// if (a>b)
if (CATIS(a)GT(b,tol))

// if (a<=b)
if (CATIS(a)LE(b,tol))

/**/

#include "CATMathFP.h"

#define CATIS(iA)      (CATCompare(iA,
#define EQ(iB,iTol)    iB,iTol) ==  0 )    // EQ : Equal To
#define LT(iB,iTol)    iB,iTol) == -1 )    // LT : Less Than
#define GT(iB,iTol)    iB,iTol) ==  1 )    // GT : Greater Than
#define LE(iB,iTol)    iB,iTol) <=  0 )    // LE : Less than or Equal to
#define GE(iB,iTol)    iB,iTol) >=  0 )    // GE : Greater than or Equal to

#endif
