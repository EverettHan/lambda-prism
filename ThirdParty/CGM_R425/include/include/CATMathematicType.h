#ifndef CATMathematicType_H
#define CATMathematicType_H

// COPYRIGHT DASSAULT SYSTEMES  2004

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * Mathematic object type.
 * @param CATMathematicType
 * The generic type.
 * @param CATMathCurveType
 * The Curve type.
 * @param CATMathLineType
 * The MathLine type.
 * @param CATMathCircleType
 * The MathCircle type.

 */
#define CATMathematicType        unsigned int

#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"


/** @nodoc   ---------- Mathematic -------------   */
#define CATMathType                         0x00000001

/** @nodoc */
#define CATMathCurveType                    0x03000002

/** @nodoc   -------------- Curve ----------------   */
/** @nodoc */
#define CATMathLineType                     0x03500003	
/** @nodoc */
#define CATMathCircleType                   0x03310004	


/** @nodoc */
#define CATUnknownMathematicType            0x00000000

#endif
