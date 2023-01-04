#ifndef CATPGMCreateInclusionPtPCrv_h_
#define CATPGMCreateInclusionPtPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATEdgeCurve;
class CATGeoFactory;
class CATIPGMInclusionPtPCrv;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurParam;

/**
 * Creates an operator for testing the inclusion of a point in a CATEdgeCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The parameter of the point.
 * @param iECrv
 * The pointer to the edge curve.
 * @param iPCrv
 * The pointer to a PCurve of the edge curve used to test the inclusion.
 * @param iTol
 * The tolerance used to decide the inclusion.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 */
ExportedByCATGMModelInterfaces CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iPt,
  const CATEdgeCurve *iECrv,
  const CATPCurve *iPCrv,
  const double iTol,
  CATSkillValue mode = BASIC);

/**
 * Creates an operator for testing the inclusion of a CATPoint in a CATPCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iPCrv
 * The pointer to the PCurve.
 * @param iTol
 * The tolerance used to decide the inclusion.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 */
ExportedByCATGMModelInterfaces CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iPt,
  const CATPCurve *iPCrv,
  const double iTol,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for testing the inclusion of a CATPoint in a CATPCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iPCrv
 * The pointer to the PCurve.
 * @param iTol
 * The tolerance used to decide the inclusion.
 * @paramiLim
 * The pointer to the PCurve Limits
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 */
ExportedByCATGMModelInterfaces CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iPt,
  const CATPCurve *iPCrv,
  const double &iTol,
  const CATCrvLimits &iLim,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateInclusionPtPCrv_h_ */
