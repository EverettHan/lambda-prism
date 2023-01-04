#ifndef CATTopBooleanType_H
#define CATTopBooleanType_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


/**
 * The Boolean operation type associated with a topological operator.
 * @param  CatBoolNone
 * Undefined Boolean operation.
 * @param  CatBoolUnion
 * The Boolean union.
 * @param  CatBoolIntersection
 * The Boolean intersection.
 * @param  CatBoolRemoval
 * The Boolean subtraction.
 */
enum CATTopBooleanType
{ CatBoolNone, CatBoolUnion, CatBoolIntersection, CatBoolRemoval };

#endif
