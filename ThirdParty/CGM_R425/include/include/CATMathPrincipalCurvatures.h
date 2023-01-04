#ifndef CATMathPrincipalCurvatures_H
#define CATMathPrincipalCurvatures_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"

#include "CATMathVector.h"
#include "CATMathDirection2D.h"
#include "CATErrorDef.h" //HRESULT


#include "CATIAV5Level.h"

#ifndef NULL
#define NULL    0
#endif

ExportedByYN000ANL HRESULT ComputePrincipalCurvatures (const CATMathVector & iDU,
                                             const CATMathVector & iDV, 
                                             const CATMathVector & iD2U, 
                                             const CATMathVector & iDUDV, 
                                             const CATMathVector & iD2V, 
                                             double & oMaxPrinK,
                                             CATMathDirection2D & oMaxPrinDir,
                                             double & oMinPrinK,
                                             CATMathDirection2D & oMinPrinDir);

// deprecated
ExportedByYN000ANL void PrincipalCurvatures (const CATMathVector & iDU,
                                             const CATMathVector & iDV, 
                                             const CATMathVector & iD2U, 
                                             const CATMathVector & iDUDV, 
                                             const CATMathVector & iD2V, 
                                             double & oMaxPrinK,
                                             CATMathDirection2D & oMaxPrinDir,
                                             double & oMinPrinK,
                                             CATMathDirection2D & oMinPrinDir,
                                             int * diag = NULL);

#endif
