#ifndef CATFreeFormDef_H
#define CATFreeFormDef_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATDataType.h"

/**
 * The type of continuity constraint.
 * @param CATFrFPointCont
 * The point continuity (G0).
 * @param CATFrFTangentCont
 * The tangency continuity (G1).
 * @param CATFrFCurvatureCont
 * The curvature continuity (G2).
 * @param CATFrFG3Cont
 * The G3 continuity (G3).
 */
typedef CATLONG32 CATFrFContinuity;
/** @nodoc */
#define CATFrFNoCont        -1
/** @nodoc */
#define CATFrFPointCont      0
/** @nodoc */
#define CATFrFTangentCont    1
/** @nodoc */
#define CATFrFCurvatureCont  2
/** @nodoc */
#define CATFrFG3Cont         3


/** @nodoc */
typedef CATLONG32 CATFrFTangentContinuity;
/** @nodoc */
#define CATFrFCrossTgtCont         0
/** @nodoc */
#define CATFrFProportionalTgtCont  1

/** @nodoc */
typedef CATLONG32  CATFrFTangentDirection;
/** @nodoc */
#define CATFrFFreeTgtDir       0
/** @nodoc */
#define CATFrFCollinearTgtDir  1

#endif
