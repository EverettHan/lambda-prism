#ifndef CATIncompatibilityType_h
#define CATIncompatibilityType_h

/**
 * Defines the compatibility between two constraint
 * @param G0andG0Incompatible
 * At the intersection point of the projection of the constraints i and j
 * the 3D point on the constraint i is not identical to the 3D point
 * on the constraint j.
 * @param G0andG1Incompatible
 * At the intersection point of the projection of the constraints i and j 
 * the tangent of the constraint i is not in the tangent plane defined by 
 * the constraints j.
 * @param G1andG1Incompatible
 * At the intersection point of the projection of the constraints i and j 
 * the tangent plane defined by the constraint i is not identical to 
 * the tangent plane defined by the constraints j.	.
 * @param G2Incompatible
 * At the intersection point of the projection of the constraints i and j 
 * the curvature defined by the constraint i is not identical to 
 * the curvature defined by the constraint j.	.
 *  
 */
enum FillingIncompatibilityType{G0andG0Incompatible,G0andG1Incompatible,G1andG1Incompatible,
                                G0andG2Incompatible,G2Incompatible};
#endif
