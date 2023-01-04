#ifndef CATIPGMCreateDistanceMinPtCrv_h_
#define CATIPGMCreateDistanceMinPtCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATCurve;
class CATIPGMDistanceMinPtCrv;
class CATGeoFactory;
class CATMathNurbsMultiForm;
class CATMathPoint;
class CATPoint;
class CATSoftwareConfiguration;

/**
 * Creates an operator for computing the minimum distance between a CATPoint and a CATCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iCrv
 * The pointer to the curve.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  CATPoint *iPt,
  CATCurve *iCrv,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for computing the minimum distance between a CATMathPoint and a CATCurve.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The point.
 * @param iCrv
 * The pointer to the curve.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATMathPoint &iPt,
  CATCurve *iCrv,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * Internal use only. Use the other signatures.
 * Creates an operator for computing the minimum distance between a CATMathPoint
 * and a CATMathNurbsMultiForm (!!! with only one form !!!)
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise (not yet implemented)</dl>
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATMathPoint &iPt,
  CATMathNurbsMultiForm *iCrv,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMCreateDistanceMinPtCrv_h_ */
