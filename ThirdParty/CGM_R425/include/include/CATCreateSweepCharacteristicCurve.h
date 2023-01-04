#ifndef CATCreateSweepCharacteristicCurve_H
#define CATCreateSweepCharacteristicCurve_H

#include "Y300IINT.h"

#include "CATSkillValue.h"
class CATReflectCurve;
class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATMathVector;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

/**
 * Creates an operator for the computation of the sweep characteristic curves of a 
 * body transforming under uniform euclidean motion.
 * <br>The characteristic curves are the set of points of a surface such that the  
 * surface normal at these points is orthogonal to the velocity vector at these 
 * points.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to software configuration.
 * @param iSurface
 * The pointer to the surface on which the curves are computed.
 * @param iLinVelocity
 * The linear velocity component of the velocity field.
 * @param iAngVelocity
 * The angular velocity component of the velocity field.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation (only available).
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation (not implemented yet).</dl>
 * @return
 * The pointer to the created operator. Use Remove() to remove the operator.
 */
ExportedByY300IINT CATReflectCurve * 
CATCreateSweepCharacteristicCurve(
						CATGeoFactory * iFactory,
						CATSoftwareConfiguration *iConfig,
		                CATSurface *iSurface,
		                const CATMathVector& iLinVelocity,
		                const CATMathVector& iAngVelocity,
		                CATSkillValue iMode = BASIC
						);


ExportedByY300IINT CATReflectCurve * 
CATCreateSweepCharacteristicCurve(
						CATGeoFactory * iFactory,
						CATSoftwareConfiguration *iConfig,
		                CATSurface * iSurface,
		                const CATMathVector& iLinVelocity,
		                const CATMathVector& iAngVelocity,
                        CATMathSetOfPointsND const& SeedPts,
		                CATSkillValue iMode = BASIC
						);

#endif
