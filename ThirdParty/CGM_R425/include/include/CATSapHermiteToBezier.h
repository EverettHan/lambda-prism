//====================================================================
// Copyright Dassault Systemes Provence 2004, all rights reserved 
//====================================================================
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
//  08 Janvier : ANR : Creation                          
//=============================================================================

#ifndef CATSapHermiteToBezier_H 
#define CATSapHermiteToBezier_H 

#include "CATSapApprox.h"

class CATMathVector ;
class CATMathPoint ;


//==========================================================================
ExportedByCATSapApprox
void CubicHermiteToBezier (CATMathPoint  *iS,   // tableau de 4 (0,0), (1,0), (0,1) et (1,1)
                           CATMathVector *iDSU,
                           CATMathVector *iDSV,
                           CATMathVector *iDSUV,
                           CATMathPoint  *oCtrPts) ; // tableau de 16 points de controles : points de Bezier



//==========================================================================
ExportedByCATSapApprox
void QuinticHermiteToBezier (CATMathPoint  *iS,   // tableau de 4 (0,0), (1,0), (0,1) et (1,1)
                             CATMathVector *iDSU,
                             CATMathVector *iDSV,
                             CATMathVector *iDSUV,
                             CATMathVector *iDSU2,
                             CATMathVector *iDSV2,
                             CATMathVector *iDSU2V,
                             CATMathVector *iDSUV2,
                             CATMathVector *iDSU2V2,
                             CATMathPoint  *oCtrPts) ; // tableau de 36 points de controles : points de Bezier


#endif


