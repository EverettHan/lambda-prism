// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathPointsToCubic:
//  This is a global function used to build the cubic coefficients
// for degree 3 interpolation.
//
//=============================================================================
// Usage notes:
//
//=============================================================================

#ifndef CATMathPointsToCubic_h
#define CATMathPointsToCubic_h

#include "YN000FUN.h"

ExportedByYN000FUN void CATMathPointsToCubic(
		      const double x0, const double dx0,
		      const double x1, const double dx1,
		      const double deltaparam,
		      double * coef);

#endif
