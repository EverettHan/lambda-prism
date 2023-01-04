#ifndef CATREFLECTCURVESIGN_H
#define CATREFLECTCURVESIGN_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/** @CAA2Required */

#include "CATMathDef.h"
/** @nodoc */
#define CATReflectCurveSignTol (0.00001) //@NumValidated

/** @nodoc */
typedef enum
{ 
   CATReflectCurveSignNegative = -1,
   CATReflectCurveSignUnset, 
   CATReflectCurveSignPositive,
   CATReflectCurveSignSameDirection,
   CATReflectCurveSignOppositeDirection,
   CATReflectCurveSignUnknown
} 
CATReflectCurveSign;

#endif
