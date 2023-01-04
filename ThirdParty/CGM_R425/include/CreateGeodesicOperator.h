// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateGeodesic :
// Declaration of global functions used to create and destroy
// an instance of the Geodesic operator
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// October. 97  Creation                          GDR
//=============================================================================
#ifndef CreateGeodesicOperator_H 
#define CreateGeodesicOperator_H 
//
#include "FrFGeodesic.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"
#include <stdlib.h>
//
class CATGeoFactory;
class CATSurface;
class CATSurParam;
class CATPCurve;
class CATMathVector;
class CATGeodesicOperator;

//
ExportedByFrFGeodesic
CATGeodesicOperator * CreateGeodesicCircle  (CATGeoFactory     * iFactory,
					     CATSurface        * iSurface,
					     CATSurParam       * iParam,
					     CATPositiveLength   iRadius,
					     CATMathVector     * iDirection = NULL,
					     CATAngle            iMinAngle = 0.,
					     CATAngle            iMaxAngle = CAT2PI,
					     CATSkillValue       iMode = BASIC);
//
ExportedByFrFGeodesic
CATGeodesicOperator * CreateGeodesicParallel (CATGeoFactory    * iFactory,
					      CATPCurve        * iPCurve,
					      CATLength          iOffset,
					      CATSkillValue      iMode = BASIC);
//
ExportedByFrFGeodesic
void Remove( CATGeodesicOperator *&iGeodesic );
//
#endif


