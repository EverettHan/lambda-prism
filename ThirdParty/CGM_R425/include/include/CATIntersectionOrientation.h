#ifndef CATINTERSECTIONORIENTATION_H
#define CATINTERSECTIONORIENTATION_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * Defines the relative orientation of a curve and a loop.
 * @param CATIntersectionOrientationOpposite
 * The curve and the loop have opposite orientations.
 * @param CATIntersectionOrientationSame
 * The curve and the loop have the same orientation.
 */
typedef short CATIntersectionOrientation;
/** @nodoc */
#define CATIntersectionOrientationOpposite -1
/** @nodoc */
#define CATIntersectionOrientationUnset 0
/** @nodoc */
#define CATIntersectionOrientationSame 1

#endif
