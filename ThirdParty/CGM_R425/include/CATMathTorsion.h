#ifndef CATMATHTORSION_H
#define CATMATHTORSION_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h" //HRESULT

#include "CATIAV5Level.h"

// Returns E_FAIL if an error occurs
ExportedByYN000ANL HRESULT Torsion ( const CATMathVector & FirstDeriv,
				    const CATMathVector & SecondDeriv,
				    const CATMathVector & ThirdDeriv, double & oValue) ;

// deprecated 
// Throws an error if an error occurs
ExportedByYN000ANL double Torsion ( const CATMathVector & FirstDeriv,
				    const CATMathVector & SecondDeriv,
				    const CATMathVector & ThirdDeriv ) ;

#endif

