#ifndef CATIPGMCreateConfusionPtOnCrvPtOnCrv_h_
#define CATIPGMCreateConfusionPtOnCrvPtOnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATIPGMConfusionPtOnCrvPtOnCrv;
class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;

/**
* @nodoc
* Creates an operator for testing the overlap of two CATPointEdgeCurves.
* @param iFactory
* The pointer to the factory of the points.
* @param iParam1
* The parameter of the first point.
* @param iParam2
* The parameter of the second point.
* @param iCrv
* The pointer to the curve on which the points are lying on.
* @param iTol
* The distance for deciding the overlap.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATCrvParam &iParam1,
  const CATCrvParam &iParam2,
  const CATCurve *iCrv,
  const double &tol,
  CATSkillValue iMode = BASIC);

/**
* @nodoc
* Creates an operator for testing the overlap of two CATPointEdgeCurves. 
* @param iFactory
* The pointer to the factory of the points.
* @param iPECrv1
* The pointer to the first point.
* @param iPECrv2
* The pointer to the second point.
* @param iCrv
* The pointer to the curve on which the points are lying on.
* @param iTol
* The distance for deciding the overlap.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnEdgeCurve *iPECrv1,
  const CATPointOnEdgeCurve *iPECrv2,
  const CATCurve *iCrv,
  double iTol,
  CATSkillValue iMode = BASIC);

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
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnCurve *iPoint1,
  const CATPointOnCurve *iPoint2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateConfusion
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iWhere,
  const CATPointOnCurve *iPoint1,
  const CATPointOnCurve *iPoint2,
  const double &iTol,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateConfusion
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iFactory,

  const CATPointOnEdgeCurve *iPECrv1,
  const CATPointOnEdgeCurve *iPECrv2,
  const CATCurve *iCrv,
  double iTol,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateConfusion
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
  CATGeoFactory *iFactory,
  const CATCrvParam &iParam1,
  const CATCrvParam &iParam2,
  const CATCurve *iCrv,
  const double &tol,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMCreateConfusionPtOnCrvPtOnCrv_h_ */
