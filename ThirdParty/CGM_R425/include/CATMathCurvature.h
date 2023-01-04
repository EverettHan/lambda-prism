#ifndef CATMathCurvature_H
#define CATMathCurvature_H
 
// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATMathVector2D.h"
#include "CATErrorDef.h" //HRESULT

#include "CATIAV5Level.h"

// Returns E_FAIL  if the FirstDeriv.Norm() is null
ExportedByYN000ANL HRESULT Curvature (const CATMathVector & FirstDeriv, 
				     const CATMathVector & SecondDeriv, double & oValue) ;

// Returns E_FAIL  if the  xy1.SquareNorm() is null
ExportedByYN000ANL HRESULT Curvature (const CATMathVector2D & xy1, 
				     const CATMathVector2D & xy2, double & oValue ) ;

// Deprecated 
// Throws an error if the FirstDeriv.Norm() is null
ExportedByYN000ANL double Curvature (const CATMathVector & FirstDeriv, 
				     const CATMathVector & SecondDeriv) ;

// Deprecated 
// Throws an error if the xy1.SquareNorm() is null
ExportedByYN000ANL double Curvature (const CATMathVector2D & xy1, 
				     const CATMathVector2D & xy2 ) ;
#endif

