#ifndef CATICGMCreateInclusionPtCrv_h_
#define CATICGMCreateInclusionPtCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATICGMInclusionPtCrv;
class CATMathPoint;
class CATPoint;
class CATSoftwareConfiguration;

/**
 * Creates an operator for testing the inclusion of a CATPoint in a CATCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iCrv
 * The pointer to the curve.
 * @param iTol
 * The tolerance used to decide the inclusion.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMInclusionPtCrv *CATCGMCreateInclusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATPoint *iPoint,
  const CATCurve *iCrv,
  const double iTol,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCreateInclusionPtCrv_h_ */
