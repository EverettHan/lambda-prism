#ifndef CATCreateConfusionPtOnCrvPtOnCrv_H
#define CATCreateConfusionPtOnCrvPtOnCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @level Protected
* @usage U1
*/ 

#include "Y300IINT.h"
#include "CATSkillValue.h"
class CATConfusionPtOnCrvPtOnCrv;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATCrvParam;
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
* @return
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv * 
CATCreateConfusion(CATGeoFactory * iWhere,
                   CATSoftwareConfiguration *iConfig,
                   const CATPointOnCurve * iPoint1,
                   const CATPointOnCurve * iPoint2, 
                   const double & iTol,
                   CATSkillValue iMode=BASIC);

                   
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
* @return
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv* 
CATCreateConfusion(CATGeoFactory * iFactory,
                   CATSoftwareConfiguration *iConfig,
                   const CATPointOnEdgeCurve * iPECrv1,
                   const CATPointOnEdgeCurve * iPECrv2,
                   const CATCurve * iCrv,
                   double iTol,
                   CATSkillValue iMode=BASIC);

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
* @return
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv * 
CATCreateConfusion(CATGeoFactory * iFactory,
                   CATSoftwareConfiguration *iConfig,
                   const CATCrvParam & iParam1,
                   const CATCrvParam & iParam2,
                   const CATCurve * iCrv,		
                   const double & tol,
                   CATSkillValue iMode=BASIC);


#endif

