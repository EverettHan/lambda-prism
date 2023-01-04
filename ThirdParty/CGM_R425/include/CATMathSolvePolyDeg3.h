// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathPolynomXDeg3
//  Function to solve the real roots of P(x) = 0 where P is the polynom :
//    P(x) = d + c x + b x^2 + a x^3
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 97    Creation                         S. Tremey
// Oct. 97    Modification                     S. Royer
//=============================================================================
#ifndef CATMathSolvePolyDeg3_h
#define CATMathSolvePolyDeg3_h

#include "YN000MAT.h"
#include "CATDataType.h"

//-----------------------------------------------------------------------------
//- Solve the polynom P(x) = d + c x + b x^2 + a x^3 = 0
//-----------------------------------------------------------------------------
void ExportedByYN000MAT Solver(double a, double b, double c, double d,
			       CATLONG32 & num, double X[3]);

#endif
