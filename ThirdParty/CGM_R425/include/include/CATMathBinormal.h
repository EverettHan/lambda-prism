#ifndef CATMathBinormal_H
#define CATMathBinormal_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h" //HRESULT

#include "CATIAV5Level.h"

// Returns E_FAIL if the (FirstDeriv ^ SecondDeriv).Norm() is null
ExportedByYN000ANL HRESULT Binormal (const CATMathVector &FirstDeriv, 
					   const CATMathVector &SecondDeriv, CATMathVector & oVector) ;

// Deprecated 
// Throws an error if the (FirstDeriv ^ SecondDeriv).Norm() is null
ExportedByYN000ANL CATMathVector Binormal (const CATMathVector &FirstDeriv, 
					   const CATMathVector &SecondDeriv) ;

#endif

