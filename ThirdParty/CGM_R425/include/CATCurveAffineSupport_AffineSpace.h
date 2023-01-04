#ifndef CATCurveAffineSupport_AffineSpace_h_
#define CATCurveAffineSupport_AffineSpace_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @level Protected
* @usage U1
*/

/**
 * Type of affine support. It is returned by CATIPGMCurveAffineSupport::GetAffineSpace method.
 * @param CATCurveAffineSupport_POINT
 * The affine support is a POINT.
 * @param CATCurveAffineSupport_LINE
 * The affine support is a LINE.
 * @param CATCurveAffineSupport_SPACE
 * The affine support is a SPACE.
 */
enum CATCurveAffineSupport_AffineSpace { CATCurveAffineSupport_POINT, CATCurveAffineSupport_LINE, CATCurveAffineSupport_PLANE, CATCurveAffineSupport_SPACE };

#endif /* CATCurveAffineSupport_AffineSpace_h_ */
