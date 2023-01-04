// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathHermiteQuintic:
//  This is a global function used to build the coefficients of the degree 5
// hermite polynomial which interpolates points, tangents and second derivatives.
//
//=============================================================================


#ifndef CATMathHermiteQuintic_h
#define CATMathHermiteQuintic_h

#include "YN000FUN.h"

class CATMathNxNFullSymMatrix;

// Fill the array coef[] such that the polynomial p(x) = sum_{i=0}^5 coef[i] x^i verify
// p(0) = x0, p'(0) = dx0, p"(0) = d2x0,
// p(DeltaParam) = x1, p'(DeltaParam) = dx1, p"(DeltaParam) = d2x1
 
ExportedByYN000FUN void CATMathHermiteQuintic(const double x0, const double dx0, const double d2x0,
			   const double x1, const double dx1, const double d2x1,
			   const double DeltaParam,
			   double * coef);

// Fill the array coef[] such that the polynomial p(x) = sum_{i=0}^5 coef[i] x^i verify
// p(-DeltaParam/2) = x0, p'(-DeltaParam/2) = dx0, p"(-DeltaParam/2) = d2x0,
// p(DeltaParam/2) = x1, p'(DeltaParam/2) = dx1, p"(DeltaParam/2) = d2x1
 
ExportedByYN000FUN void CATMathHermiteShiftedQuintic(const double x0, const double dx0, const double d2x0,
			   const double x1, const double dx1, const double d2x1,
			   const double DeltaParam,
			   double * coef);

// Evaluation at a given parameter of a polynomial  p(x) = sum_{i=0}^5 coef[i] x^i verifying
// p(0) = x0, p'(0) = dx0, p"(0) = d2x0,
// p(1) = x1, p'(1) = dx1, p"(1) = d2x1
 
ExportedByYN000FUN double CATMathEvalHermiteQuintic(const double x0, const double dx0, const double d2x0,
			   const double x1, const double dx1, const double d2x1,
			   const double Param );


ExportedByYN000FUN void CATMathHermiteQuinticL2Matrices(double iDeltaParam, int iNbMatrices, 
                                                        CATMathNxNFullSymMatrix ** ioMatrices, int * iLevels);
#endif
