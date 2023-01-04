#ifndef CATINTERSECTIONPCRVPCRVSIGN_H
#define CATINTERSECTIONPCRVPCRVSIGN_H

/** @CAA2Required */

// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATIntersectionPCrvPCrvSign :
// enum type used to describe the orientation between two objects.
//
//=============================================================================
// Usage notes:
//
// Output information of the intersection operator for PCurves and
// Surfaces.
//
//=============================================================================
// 24/05/07 NLD XScale CATInclusionPtPCrvSignatureCloseTol via GetToleranceObject()
#include "CATMathDef.h"
//BigScale Mod. #SKA
#include "CATTolerance.h"

#define CATIntersectionPCrvPCrvSignTol (0.01)//@NumValidated

typedef enum
{ 
   CATIntersectionPCrvPCrvSignPositive = 1,
   CATIntersectionPCrvPCrvSignNegative,
   CATIntersectionPCrvPCrvSignSameDirection,
   CATIntersectionPCrvPCrvSignOppositeDirection,
   CATIntersectionPCrvPCrvSignUnknown,
   CATIntersectionPCrvPCrvSignUnset
} 
CATIntersectionPCrvPCrvSign;

typedef enum
{ 
  CATPointPositionOnCurveBegin = 1,
  CATPointPositionOnCurveEnd,
  CATPointPositionOnCurveInterior,
  CATPointPositionOnCurveUnknown,
  CATPointPositionOnCurveUnset
} 
CATPointPositionOnCurve;

typedef enum
{ 
  CATIntersectionPCrvPCrvCrossingTrue = 1,
  CATIntersectionPCrvPCrvCrossingFalsePositive,
  CATIntersectionPCrvPCrvCrossingFalseNegative,
  CATIntersectionPCrvPCrvCrossingFalse,
  CATIntersectionPCrvPCrvCrossingUnknown,
  CATIntersectionPCrvPCrvCrossingUnset
} 
CATIntersectionPCrvPCrvCrossing;

// distance under which we decide that a point is on a curve
//#define CATInclusionPtPCrvSignatureCloseTol CATEpsg
//NLD240507#define CATInclusionPtPCrvSignatureCloseTol CATGetDefaultTolerance().EpsgForLengthTest()//Epsg should be scaled
#define CATInclusionPtPCrvSignatureCloseTol GetToleranceObject().EpsgForLengthTest()//Epsg should be scaled
// value under which we decide that signature is unknown
#define CATInclusionPtPCrvSignatureTol (1.e-3)//@NumValidated(for sinus test)

typedef enum
{ 
  CATPtPCrvSignaturePositive = 1,
  CATPtPCrvSignatureNegative,
  CATPtPCrvSignatureClose,
  CATPtPCrvSignatureUnknown,
  CATPtPCrvSignatureUnset
} 
CATPtPCrvSignature;



#endif
