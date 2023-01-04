#ifndef CATMovingFrameType_H
#define CATMovingFrameType_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The type of definition of the moving frame.
 * <br>The moving frame is an orthonormal axes system (<tt>X, Y, Z</tt>) moving along a curve (the dominant guide
 * or spine): at every point on the curve, the moving frame defines a local coordinate system. The moving frame
 * is defined by a strong condition (one direction is given) and by a weak condition (another direction
 * indicating the preliminary second axis). The third axis is set to be orthonormal to these two axes.
 * Afterwards, the second axis is changed to be orthonormal to the first and third axis.
 * <br>
 * By default for the <tt>PARALLEL_TO_PLANE_MF</tt>, <tt>ORTHO_MF</tt>, <tt>PSEUDO_ORTHO_MF</tt> cases, the
 * moving frame is chosen as follows: the viewing direction is the normal to the best approximating plane 
 * of the spine.
 * @param PARALLEL_TO_PLANE_MF
 * Parallel to a plane: the directions of all the three axes are constant.
 * <br>Strong condition: the direction of the <tt>Z</tt> axis is given. 
 * <br>Weak condition: the viewing direction <tt>V</tt>: then, <tt>X=V^Z</tt> and <tt>Y=Z^Y</tt>.
 * @param ORTHO_MF
 * Perpendicular to the spine.
 * <br>Strong condition: the direction of the <tt>Z</tt> axis is the current tangent of the spine. 
 * <br>Weak condition: the viewing direction <tt>V</tt>: then, <tt>X=V^Z</tt> and <tt>Y=Z^Y</tt>.
 * @param PSEUDO_ORTHO_MF
 * Pseudo-perpendicular to the spine.
 * <br>Strong condition:  <tt>Y</tt> is parallel to the viewing direction. 
 * <br>Weak condition: the tangent <tt>T</tt> to the spine: then, <tt>X=Y^T</tt> and <tt>Z=X^Y</tt>.
 * @param ORTHO_CRV_CRV_MF
 * Two guiding curves and perpendicular to the spine.
 * <br>Strong condition:  <tt>X</tt> is parallel to the difference vector of corresponding points of
 * two guiding curves. 
 * <br>Weak condition: the tangent <tt>T</tt> to the spine: then, <tt>Y=T^X</tt> and <tt>Z=X^Y</tt>.
 * @param PSEUDO_ORTHO_CRV_CRV_MF
 * Two guiding curves and pseudo-perpendicular to the spine.
 * <br>Strong condition:  <tt>X</tt> is parallel to the difference vector of corresponding points of
 * two guiding curves. 
 * <br>Weak condition: the viewing direction <tt>V</tt>: then, <tt>Y=V^X</tt> and <tt>Z=X^Y</tt>.
 */
typedef enum
{
  PARALLEL_TO_PLANE_MF             = 1,
  ORTHO_MF                         = 2,
  PSEUDO_ORTHO_MF                  = 3,
  ORTHO_CRV_CRV_MF                 = 4,
  PSEUDO_ORTHO_CRV_CRV_MF          = 5,
  MEAN_TANGENT_MF                  = 7
} CATMovingFrameType;
#endif




