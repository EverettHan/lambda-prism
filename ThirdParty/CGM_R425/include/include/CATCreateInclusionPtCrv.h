#ifndef CATCreateInclusionPtCrv_H
#define CATCreateInclusionPtCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CreateInclusionPtCrv.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATPoint;
class CATMathPoint;
class CATEdgeCurve;
class CATCurve;
class CATCrvLimits;
class CATInclusionPtCrv;
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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATInclusionPtCrv * CATCreateInclusion(CATGeoFactory * iWhere,
                                                          CATSoftwareConfiguration *Config,
                                                          const CATPoint * iPoint,
                                                          const CATCurve * iCrv, 
                                                          const double iTol,
                                                          CATSkillValue iMode=BASIC);

/**
* @nodoc
* Creates an operator for testing the inclusion of a CATMathPoint in a CATEdgeCurve.
* @param iWhere
* The pointer to the factory of the geometry. 
* @param iPt
* The point.
* @param iECrv
* The pointer to the edge curve.
* @param iCrv
* The pointer to a curve of the edge curve used to test the inclusion.
* @param iTol
* The tolerance used to decide the inclusion.
* @param iMode
* The mode of use.
* <br><b>Legal values</b>:
* <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
*     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
* @return
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATInclusionPtCrv * CATCreateInclusion(CATGeoFactory * iWhere,
                                                          CATSoftwareConfiguration *Config,
                                                          const CATMathPoint & iPoint,
                                                          const CATEdgeCurve * iECrv,
                                                          const CATCurve * iCrv, 
                                                          const double iTol,
                                                          CATSkillValue iMode=BASIC);


/**
* @nodoc
* Creates an operator for testing the inclusion of a CATMathPoint in a CATCurve.
* @param iWhere
* The pointer to the factory of the geometry. 
* @param iM
* The point.
* @param iCrv
* The pointer to a curve of the edge curve used to test the inclusion.
* @param iTol
* The tolerance used to decide the inclusion.
* @param iMode
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATInclusionPtCrv * CATCreateInclusion(CATGeoFactory * iFactory,
                                                             CATSoftwareConfiguration * iConfig,
                                                             const CATMathPoint & iM,
                                                             const CATCurve * iCrv,
                                                             const double iTol);
/**
* @nodoc
* Creates an operator for testing the inclusion of a CATMathPoint in a CATCurve.
* @param iWhere
* The pointer to the factory of the geometry. 
* @param iM
* The point.
* @param iCrv
* The pointer to a curve of the edge curve used to test the inclusion.
* @param iTol
* The tolerance used to decide the inclusion.
* @param iMode
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
* @param iLim
* The limits of the curve.
*/
ExportedByY300IINT 	CATInclusionPtCrv * CATCreateInclusion(CATGeoFactory * iFactory,
                                                              CATSoftwareConfiguration * iConfig,
                                                              const CATMathPoint & iM,
                                                              const CATCurve *iCrv,
                                                              const double iTol,
                                                              const CATCrvLimits & iLim);
#endif
