// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathVectorUtilities: header providing global methods on MathVectors
//
//=============================================================================
//
// Usage notes:
//
//  This header should be used whenever needed generic services on Vectors.
//
//=============================================================================
// Oct. 97    Creation                           R. Rorato
//=============================================================================

#ifndef CATMathVectorUtilities_H
#define CATMathVectorUtilities_H

#include "YP00IMPL.h"

class CATMathVector;

//-----------------------------------------------------------------------------
// Computes derivative of a normed vector iV/|iV|.
// Returns 1/norm of iV (0 is iV is null).
//-----------------------------------------------------------------------------
double ExportedByYP00IMPL CATDerivNormedVector (const CATMathVector & iV, 
						                        const CATMathVector & iDV, 
						                        CATMathVector &oDVnormed  );


//-----------------------------------------------------------------
// Derivative of a normed vector dnv = d(v/|v|)/dt 
//-----------------------------------------------------------------
void ExportedByYP00IMPL CATDerivNormedVector (const double *v, 
                                              const double *dv, 
                                              double *dnv      );

//-----------------------------------------------------------------------------
// Computes second Derivative of a normed vector iV/|iV|
// Returns 1/norm of iV (0 is iV is null).
//-----------------------------------------------------------------------------
double ExportedByYP00IMPL CATSecondDerivNormedVector (const CATMathVector &iV, 
						                              const CATMathVector &iDV,
						                              const CATMathVector &iD2V,
						                              CATMathVector &oD2Vnormed);

//-----------------------------------------------------------------
// Second derivative of a normed vector dnv = d2(v/|v|)/dt2 
//-----------------------------------------------------------------
void ExportedByYP00IMPL CATSecondDerivNormedVector (const double *v, 
                                                    const double *dv, 
                                                    const double *d2v, 
                                                    double *d2nv);


//-----------------------------------------------------------------------------


#endif

