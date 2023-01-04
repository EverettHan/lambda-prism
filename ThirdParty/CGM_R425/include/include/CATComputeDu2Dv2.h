//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CATComputeDU2DV2
// 
//
//===================================================================
// Usage notes : Evaluations of the fourth derivate Du2Dv2 of the X,Y,
// Z functions of a surface
//
//===================================================================

#ifndef CATComputeDu2Dv2_H
#define CATComputeDu2Dv2_H
#include "Y30UIUTI.h"

#include "CATSurface.h"
#include "CATSurParam.h"
#include "CATMathVector.h"
#include "CATMathPolynomXY.h"
#include "CATMathFractionXY.h"
#include "CATMathFunctionXY.h"

class CATSoftwareConfiguration;

// Pour des Nurbs ou des Nupbs les resultats sont tres bons.
// CoteU =+/- 1 donne la derivee resp. a droite ou a gauche en U : extremement instable a ne pas utiliser
// CoteV =+/- 1 donne la derivee resp. a droite ou a gauche en V : plutot stable, a environ 1.e-6 pres.
ExportedByY30UIUTI void CATComputeDu2Dv2(const CATSurface *, const CATSurParam *, CATMathVector &, CATLONG32 iCoteU = 0, CATLONG32 iCoteV = 0);
ExportedByY30UIUTI void CATComputeDu2Dv2(CATSoftwareConfiguration * iConfig,
                                         const CATSurface *, const CATSurParam *, CATMathVector &, CATLONG32 iCoteU = 0, CATLONG32 iCoteV = 0);


void CATComputePolDu2Dv2(CATSoftwareConfiguration * iConfig,const CATMathPolynomXY *, const double *, const double *, double &);
void CATComputeFracDu2Dv2(CATSoftwareConfiguration * iConfig,const CATMathFractionXY *, const double *, const double *, double &, const CATTolerance & iTolObject);
ExportedByY30UIUTI void CATComputeGenDu2Dv2(CATSoftwareConfiguration * iConfig,const CATMathFunctionXY *, const double *, const double *, double &, CATLONG32 iCoteU, CATLONG32 iCoteV, const CATTolerance & iTolObject);
void CATComputeGenDu2(CATSoftwareConfiguration * iConfig,const CATMathFunctionXY *, const double *, const double, double &, CATLONG32 iCoteU, const CATTolerance & iTolObject);

#endif
