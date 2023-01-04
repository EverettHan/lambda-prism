#ifndef CATBlendValue_H
#define CATBlendValue_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathDef.h"

/**
 * The way of construction of the control points of the blend surface.
 * <br>In case of analytical mode and G1 or G2 continuity.
 * @param CATBlendCrossTgCont
 * The second rank of control points (parallel to the rank of the wire control points) is computed
 * as a ratio of the length between the first rank and the second rank of control points on the supporting
 * surface.
 * @param CATBlendProportionalTgCont
 * The second rank of control points (parallel to the rank of the wire control points) is computed as
 * a ratio of the distance between the two input wires.
 */
typedef enum
{ 
   CATBlendCrossTgCont,
   CATBlendProportionalTgCont
} 
CATBlendTgContMode;

#endif
