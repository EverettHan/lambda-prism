#ifndef CATICGMCreateConfusionPtOnCrvPtOnCrv_h_
#define CATICGMCreateConfusionPtOnCrvPtOnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATICGMConfusionPtOnCrvPtOnCrv;
class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;

/**
* Creates an operator for testing the overlap of two CATPointOnCurves.
*<br>The two points belong to the same CATCurve.
* @param iFactory
* The pointer to the factory of the points.
* @param iPoint1
* The pointer to the first point.
* @param iPoint2
* The pointer to the second point.
* @param iTol
* The distance for deciding the overlap.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMConfusionPtOnCrvPtOnCrv *CATCGMCreateConfusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnCurve *iPoint1,
  const CATPointOnCurve *iPoint2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCreateConfusionPtOnCrvPtOnCrv_h_ */
