#ifndef CATMathNormalCurvature_H
#define CATMathNormalCurvature_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathDef.h"
#include "CATMathVector.h"
#include "CATMathVector2D.h"

ExportedByYN000ANL CATBoolean NormalCurvature (const CATMathVector & DU, 
                                               const CATMathVector & DV,
                                               const CATMathVector & DU2,
                                               const CATMathVector & DUDV,
                                               const CATMathVector & DV2,
                                               const CATMathVector2D &Dir,
                                               double & oNormalCurvature) ;

		
#endif
