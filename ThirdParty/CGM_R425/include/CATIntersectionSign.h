#ifndef CATINTERSECTIONSIGN_H
#define CATINTERSECTIONSIGN_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathDef.h"
/**
 * @nodoc
 */
#define CATIntersectionSignTol (0.00001) //@NumValidated

/**
 * Defines the position of the intersection with regards to the the initial geometry.
 * <br>Do not use the values that are not documented here.
 * @param CATIntersectionSignNegative
 * The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is negative. 
 * @param CATIntersectionSignPositive
 * The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is positive. 
 */
typedef enum
{ 
   CATIntersectionSignNegativeSingular = -2,
   CATIntersectionSignNegative = -1,
   CATIntersectionSignUnset, 
   CATIntersectionSignPositive,
   CATIntersectionSignPositiveSingular,
   CATIntersectionSignSameDirection,
   CATIntersectionSignOppositeDirection,
   /* Used by fillet */
   CATIntersectionSignUnknown,               
   CATIntersectionSignNegativeDeformation,
   CATIntersectionSignNegativeDeformationSingular,
   CATIntersectionSignPositiveDeformation,
   CATIntersectionSignPositiveDeformationSingular,
   CATIntersectionSignUnknownDeformation,
   CATIntersectionSignUnknownDeformationSingular,
   /* Used by shell */
   CATIntersectionSignBoth,                   
   CATIntersectionSignExit,
   CATIntersectionSignTangent,
   CATIntersectionSignTangentBoth
} 
CATIntersectionSign;
/** @nodoc */
typedef enum
{ 
  CATIntersectionCrossingTrue = 1,
  CATIntersectionCrossingFalsePositive,
  CATIntersectionCrossingFalseNegative,
  CATIntersectionCrossingFalse,
  CATIntersectionCrossingUnknown,
  CATIntersectionCrossingUnset
} 
CATIntersectionCrossing;

#endif
