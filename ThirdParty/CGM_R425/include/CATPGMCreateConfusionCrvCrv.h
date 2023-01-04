#ifndef CATPGMCreateConfusionCrvCrv_h_
#define CATPGMCreateConfusionCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATIPGMConfusionCrvCrv;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;

/**
 * Creates an operator for testing the overlap of two CATCurves.
 *<br>The CATPointOnCurves precise the curves limitations to take into
 * account for this operator, but this does not change the current CATCurves 
 * limitations. The proposed limitations have to be included into the
 * current limitations.
 * @param iWhere
 * The pointer to the factory of the curves.
 * @param iStartPtOnCrv1
 * The pointer to the point defining the low limitation on the first curve.
 * @param iEndPtOnCrv1
 * The pointer to the point defining the high limitation on the first curve.
 * @param iStartPtOnCrv2
 * The pointer to the point defining the low limitation on the second curve.
 * @param iEndPtOnCrv2
 * The pointer to the point defining the high limitation on the second curve.
 * @param iTol
 * The maximum Haussdorf distance for deciding the overlap.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation (only available).
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation (not implemented yet).</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnCurve *iStartPtOnCrv1,
  const CATPointOnCurve *iEndPtOnCrv1,
  const CATPointOnCurve *iStartPtOnCrv2,
  const CATPointOnCurve *iEndPtOnCrv2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for testing the overlap of two CATCurves.
 *<br>The CATPointOnEdgeCurves precise the curves limitations to take into
 * account for this operator, but this does not change the current curve 
 * limitations. The proposed limitations have to be included into the
 * current limitations.
 * @param iWhere
 * The pointer to the factory of the curves.
 * @param iStartPtOnCrv1
 * The pointer to the point defining the low limitation on the first curve.
 * @param iEndPtOnCrv1
 * The pointer to the point defining the high limitation on the first curve. 
 * @param iCrv1
 * The pointer to the curve of the first edge curve ( implicitly defined by <tt>iStartPtOnCrv1</tt>)
 * to take into account.
 * @param iStartPtOnCrv2
 * The pointer to the point defining the low limitation on the second curve.
 * @param iEndPtOnCrv2
 * The pointer to the point defining the high limitation on the second curve.
 * @param iCrv2
 * The pointer to the curve of the second edge curve ( implicitly defined by <tt>iStartPtOnCrv2</tt>)
 * to take into account.
 * @param iTol
 * The maximum Haussdorf distance for deciding of the overlap.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation (only available)
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnEdgeCurve *iStartPtOnECrv1,
  const CATPointOnEdgeCurve *iEndPtOnECrv1,
  const CATCurve *iCrv1,
  const CATPointOnEdgeCurve *iStartPtOnECrv2,
  const CATPointOnEdgeCurve *iEndPtOnECrv2,
  const CATCurve *iCrv2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for testing the overlap of two CATCurves.
 *<br>The CATPointOnEdgeCurves precise the curves limitations to take into
 * account for this operator, but this does not change the current curve 
 * limitations. The proposed limitations have to be included into the
 * current limitations.
 * @param iFActory
 * The pointer to the factory of the curves.
 * @param iCrv1
 * The pointer to the first curve.
 * @param iCrv2
 * The pointer to the second curve. 
 * @param iTol
 * The maximum Haussdorf distance for deciding of the overlap.
 * @param iStartParam1
 * The param to the start point on the curve 1.
 * @param iEndParam1
 * The param to the end point on the curve 1.
 * @param iStartParam2
 * The param to the start point on the curve 2.
 * @param iEndParam2
 * The param to the end point on the curve 2.
 * @param iECrv1
 * The pointer to the edge curve containing the curve 1.
 * @param iECrv2
 * The pointer to the edge curve containing the curve 1.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCrv1,
  const CATCurve *iCrv2,
  const double iTol,
  const CATCrvParam &iStartParam1,
  const CATCrvParam &iEndParam1,
  const CATCrvParam &iStartParam2,
  const CATCrvParam &iEndParam2,
  const CATEdgeCurve *iECrv1 = 0,
  const CATEdgeCurve *iECrv2 = 0);

/**
* @deprecated V5R13 CATPGMCreateConfusion
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,

  const CATPointOnCurve *iStartPtOnCrv1,
  const CATPointOnCurve *iEndPtOnCrv1,
  const CATPointOnCurve *iStartPtOnCrv2,
  const CATPointOnCurve *iEndPtOnCrv2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateConfusion
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,

  const CATPointOnEdgeCurve *iStartPtOnECrv1,
  const CATPointOnEdgeCurve *iEndPtOnECrv1,
  const CATCurve *iCrv1,
  const CATPointOnEdgeCurve *iStartPtOnECrv2,
  const CATPointOnEdgeCurve *iEndPtOnECrv2,
  const CATCurve *iCrv2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateConfusionCrvCrv_h_ */
