// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateCurveAffineSupport :
// creation of a CATCurveAffineSupport operator
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Jan.  99 Creation                                     X. Gourdon
//=============================================================================

#ifndef CATCreateCurveAffineSupport_H
#define CATCreateCurveAffineSupport_H

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATGeoFactory;
class CATPoint;
class CATCurve;
class CATCrvLimits;
class CATCurveAffineSupport;
class CATSoftwareConfiguration;

/**
* @deprecated V5R20 CATCreateCurveAffineSupport
* Use creation with limits, instead.
*/
/**
 * Creates an operator for computing a CATCurveAffineSupport operator for a family
 * of curves.
 * @param iWhere
 * The container of geometric objects.
 * @param Config
 * The software configuration.
 * @param iCurve
 * The curve whose affine support is to be computed.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise. The ADVANCED mode is to be used whenever the <tt>Setxxx</tt> methods
 *         are called.
 *  </dl>
 */
ExportedByY300IINT CATCurveAffineSupport * CATCreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATSoftwareConfiguration *Config,
                                                                    CATCurve * iCurve, 
                                                                    CATSkillValue iMode = BASIC);

/**
* @deprecated V5R20 CATCreateCurveAffineSupport
* Use creation with limits, instead.
*/
/**
 * Creates an operator for computing a CATCurveAffineSupport operator.
 * @param iWhere
 * The container of geometric objects.
 * @param Config
 * The software configuration.
 * @param iCurves
 * The array of curves.
 * @param iNbCurves
 * The number of curves.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise. The ADVANCED mode is to be used whenever the <tt>Setxxx</tt> methods
 *         are called.
 *  </dl>
 */
ExportedByY300IINT CATCurveAffineSupport * CATCreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATSoftwareConfiguration *Config,
                                                                    CATCurve ** iCurves,
                                                                    const CATLONG32 iNbCurves,
                                                                    CATSkillValue iMode = BASIC);

/**
 * Creates an operator for computing a CATCurveAffineSupport operator for a family
 * of curves.
 * @param iWhere
 * The container of geometric objects.
 * @param Config
 * The software configuration.
 * @param iCurve
 * The curve whose affine support is to be computed.
 * @param iCrvLim
 * The limits of the curves.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise. The ADVANCED mode is to be used whenever the <tt>Setxxx</tt> methods
 *         are called.
 *  </dl>
 */
ExportedByY300IINT CATCurveAffineSupport * CATCreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATSoftwareConfiguration *Config,
                                                                    CATCurve * iCurve, CATCrvLimits & iCrvLim,
                                                                    CATSkillValue iMode = BASIC);

/**
 * Creates an operator for computing a CATCurveAffineSupport operator.
 * @param iWhere
 * The container of geometric objects.
 * @param Config
 * The software configuration.
 * @param iCurves
 * The array of curves.
 * @param iCrvLims
 * The array of Crv Limits.
 * @param iNbCurves
 * The number of curves.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise. The ADVANCED mode is to be used whenever the <tt>Setxxx</tt> methods
 *         are called.
 *  </dl>
 */
ExportedByY300IINT CATCurveAffineSupport * CATCreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATSoftwareConfiguration *Config,
                                                                    CATCurve ** iCurves, CATCrvLimits* iCrvLims,
                                                                    const CATLONG32 iNbCurves,
                                                                    CATSkillValue iMode = BASIC);

#endif
