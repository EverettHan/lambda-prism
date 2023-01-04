#ifndef CATCreateDistanceMinPtCrv_H
#define CATCreateDistanceMinPtCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATCurve;
class CATDistanceMinPtCrv;
class CATPoint;
class CATMathPoint;
class CATMathNurbsMultiForm;
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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATDistanceMinPtCrv * CATCreateDistanceMin(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
							   CATPoint * iPt,
							   CATCurve * iCrv,
							   CATSkillValue iMode=BASIC);

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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATDistanceMinPtCrv * CATCreateDistanceMin(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
							   const CATMathPoint & iPt,
							   CATCurve * iCrv,
							   CATSkillValue iMode=BASIC);

/**
 * @nodoc
 * Internal use only. Use the other signatures.
 * Creates an operator for computing the minimum distance between a CATMathPoint
 * and a CATMathNurbsMultiForm (!!! with only one form !!!)
 * @param iMode
 * <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt> otherwise (not yet implemented)</dl>
 */
ExportedByY300IINT CATDistanceMinPtCrv * CATCreateDistanceMin(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
							   const CATMathPoint & iPt,
							   CATMathNurbsMultiForm * iCrv,
							   CATSkillValue iMode=BASIC);


#endif
