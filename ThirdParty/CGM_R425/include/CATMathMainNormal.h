#ifndef CATMathMainNormal_H
#define CATMathMainNormal_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h" //HRESULT

#include "CATIAV5Level.h"

// Returns E_FAIL if the FirstDeriv.Norm() is null
ExportedByYN000ANL HRESULT MainNormal (const CATMathVector & FirstDeriv, 
					     const CATMathVector & SecondDeriv, CATMathVector & oVector) ;

// deprecated 
// Throws an error if the FirstDeriv.Norm() is null
ExportedByYN000ANL CATMathVector MainNormal (const CATMathVector & FirstDeriv, 
					     const CATMathVector & SecondDeriv) ;

#endif

