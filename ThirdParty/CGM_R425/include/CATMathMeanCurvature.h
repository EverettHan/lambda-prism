#ifndef CATMathMeanCurvature_H
#define CATMathMeanCurvature_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"
#include "CATErrorDef.h"

#include "CATIAV5Level.h"

ExportedByYN000ANL HRESULT MeanCurvature(const CATMathVector & DU, 
                                         const CATMathVector & DV,
                                         const CATMathVector & DU2,
                                         const CATMathVector & DUDV,
                                         const CATMathVector & DV2,
                                         double & oValue);

// deprecated
ExportedByYN000ANL double MeanCurvature(const CATMathVector & DU, 
                                        const CATMathVector & DV,
                                        const CATMathVector & DU2,
                                        const CATMathVector & DUDV,
                                        const CATMathVector & DV2);

    
#endif
