#ifndef CATCreateConicalReflectCurve_H
#define CATCreateConicalReflectCurve_H

#include "Y300IINT.h"

#include "CATSkillValue.h"
class CATReflectCurve;
class CATGeoFactory;
class CATSurface;
class CATPoint;
class CATSoftwareConfiguration;

/**
 * Creates an operator for the computation of the conical reflect curves.
 * <br>The reflect curves are the set of points of a surface such that the surface normal 
 * at these points and a vector joining given point & these points defines a constant angle.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to software configuration.
 * @param iSurface
 * The pointer to the surface on which the curves are computed.
 * @param iPoint
 * The pointer to user point
 * @param iAngle
 * The constant angle between the surface normal at a point (P) of the reflect curve 
 * and the direction PO ( from P to given Point) <tt>iPoint</tt>.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation (only available).
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation (not implemented yet).</dl>
 * @return
 * The pointer to the created operator. Use Remove() to remove the operator.
 */
ExportedByY300IINT CATReflectCurve * 
CATCreateReflectCurve(CATGeoFactory * iFactory,
                      CATSoftwareConfiguration *iConfig,
		                  CATSurface *iSurface,
		                  CATPoint *iPoint,
		                  CATAngle iAngle,
		                  CATSkillValue mode=BASIC);


#endif

