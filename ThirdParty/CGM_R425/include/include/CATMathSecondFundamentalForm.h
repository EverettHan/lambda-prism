#ifndef CATMathSecondFundamentalForm_H
#define CATMathSecondFundamentalForm_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h" //HRESULT


// Returns E_FAIL if an error occurs
ExportedByYN000ANL HRESULT SecondFundamentalForm(const CATMathVector & DU, 
                                                 const CATMathVector & DV,
                                                 const CATMathVector & DU2,
                                                 const CATMathVector & DUDV,
                                                 const CATMathVector & DV2,
                                                 double  & L, double & M, double & N);

#endif
