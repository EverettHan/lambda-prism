#ifndef CATDynBooleanType_h_
#define CATDynBooleanType_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATIACGMLevel.h"
#include "CATDynExtrapolationToolsDef.h"

/**
 * Defines the Boolean operation types.
 * @param CATBoolNone
 * Undefined operation.
 * @param CATBoolUnion
 * The union.
 * @param CATBoolIntersection
 * The intersection.
 * @param CATBoolRemoval
 * The difference.
 */
enum CATDynBooleanType
{ CATBoolNone, CATBoolUnion, CATBoolIntersection, CATBoolRemoval };

/**
 * Defines the sides to keep in a split operation.
 * @param CATSplitBothSides
 * The both sides are kept.
 * @param CATSplitPositiveSideOnly
 * The portion of the body on the positive side of the cutting object is kept.
 * @param CATSplitNegativeSideOnly
 * The portion of the body on the negtive side of the cutting object is kept.
 */
enum CATDynSplitType
{ CATSplitBothSides, CATSplitPositiveSideOnly, CATSplitNegativeSideOnly};

/**
* Selection mode for split operator.
* @param CATDynPositionVsPlaneMode 
* The use of CATDynPositionVsPlaneMode has 2 consequences:
* - If the splitting element is a one-face body with a planar surface as support,
*   the split is done using the planar surface instead of the body.
* - If a volume is not cut by the plane, it is positioned towards the plane to decide
*   if it should be kept or not in the result.
* @param CATDynKeepMode
* Volumes that are not cut by the splitting element will be in the result.
* @param CATDynRemoveMode
* Volumes that are not cut by the splitting element will not be in the result.
*/
enum CATDynSelectionMode
{ CATDynKeepMode, CATDynRemoveMode, CATDynPositionVsPlaneMode};

/** @nodoc */
enum CATDynLimitType 
{ CATLimOffsetFromProfile, CATLimUntil, CATLimNextAlongAxis, CATLimLastAlongAxis };

/** @nodoc */
enum CATDynLimit 
{ CATLimStart, CATLimEnd };

/** @nodoc */
enum CATDynPropagationType
{ CATPropagSingle, CATPropagExtrapolated, CATPropagClosing};

#endif /* CATDynBooleanType_h_ */
