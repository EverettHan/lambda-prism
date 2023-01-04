//#ifdef CATIAV5R14

#ifndef CATCreateConvertCurveToCanonic_H 
#define CATCreateConvertCurveToCanonic_H 

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
 * @level Protected
 * @usage U1
 */

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATSurface.h"

class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATCurve;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATCrvLimits;
class CATConvertCurveToCanonic;

/**
* Creates an operator that computes the most approaching canonical
* curve of a given edge curve.
* @param iFactory
* The pointer to the geometry factory needed for the creation of the result curve.
* @iConfig
* the CATSoftwareConfiguration = level of versionning
* @param iEdgeCurve
* The pointer to the edge curve to be analyzed.
* @param iStartPOEC
* The pointer to the first point on the edge curve, defining the beginning of the domain to analyze.
* @param iEndPOEC
* The pointer to the last point on the edge curve, defining the end of the domain to analyze.
* @param iSupport
* The pointer to the planar surface of one of the representant of the edge curve. It can be <tt>NULL</tt>.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>The operation is is performed with the <tt>Run</tt> method</dl> 
* @return
* The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByY300IINT
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATEdgeCurve * iEdgeCurve,
                                                       CATPointOnEdgeCurve * iStartPOEC,
                                                       CATPointOnEdgeCurve * iEndPOEC,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);

/**
* Creates an operator that computes the most approaching canonical
* curve of a given curve.
* @param iFactory
* The pointer to the geometry factory needed for the creation of the result curve.
* @iConfig
* the CATSoftwareConfiguration = level of versionning
* @param iCurve
* The pointer to the curve to be analyzed.
* @param iLimits
* The limits inside which the analyze is done.
* @param iSupport
* The pointer to the planar surface of one of the representant of the edge curve. It can be <tt>NULL</tt>.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>The operation is is performed with the <tt>Run</tt> method</dl> 
* @return
* The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByY300IINT
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATCurve * iCurve,
                                                       CATCrvLimits & iLimits,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);

/**
* Creates an operator that computes the most approaching canonical
* curve of a set of curves lying on the same plane.
* <br>The operator outputs one curve.
* @param iFactory
* The pointer to the geometry factory needed for the creation of the result curve.
* @iConfig
* the CATSoftwareConfiguration = level of versionning
* @param iNbCrv
* The number of curves to analyze.
* @param iTabCrv
* The array <tt>[iNbCrv]</tt> of pointers to the curves to analyze.
* @param iStartParam
* The array <tt>[iNbCrv]</tt> defining the first parameter on the curves, defining the beginning of the
* domain to analyze for each curve.
* @param iEndParam
* The array <tt>[iNbCrv]</tt> defining the last parameter on the curves, defining the end of the
* domain to analyze for each curve.
* @param iSupport
* The pointer to the planar surface common to all the input curves. It can be <tt>NULL</tt>.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>The operation is is performed with the <tt>Run</tt> method</dl> 
* @return
* The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByY300IINT
CATConvertCurveToCanonic * CATCreateConvertCurveToCanonic(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATLONG32 iNbCrv,
                                                       CATCurve ** iTabCrv,
                                                       CATCrvParam * iStartParam,
                                                       CATCrvParam * iEndParam,
                                                       CATSurface * iSupport=NULL,
                                                       CATSkillValue iMode = BASIC);




//#endif

#endif




