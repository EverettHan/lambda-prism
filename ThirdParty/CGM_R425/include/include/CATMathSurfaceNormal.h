#ifndef CATMathSurfaceNormal_H
#define CATMathSurfaceNormal_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h" //HRESULT

#include "CATIAV5Level.h"

// Returns E_FAIL  if the (FirstDeriv ^ SecondDeriv).Norm() is null
ExportedByYN000ANL HRESULT SurfaceNormal  ( const CATMathVector & FirstDeriv, 
						  const CATMathVector & SecondDeriv , CATMathVector & oVector) ;

// deprecated 
// Throws an error if the (FirstDeriv ^ SecondDeriv).Norm() is null
ExportedByYN000ANL CATMathVector SurfaceNormal  ( const CATMathVector & FirstDeriv, 
						  const CATMathVector & SecondDeriv ) ;

			

#endif
