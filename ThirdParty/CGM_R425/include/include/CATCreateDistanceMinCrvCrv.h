#ifndef CATCreateDistanceMinCrvCrv_H
#define CATCreateDistanceMinCrvCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATPointOnCurve.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATCurve;
class CATDistanceMinCrvCrv;
class CATSoftwareConfiguration;

/**
 * Creates an operator for computing the minimum distance between two curves.
 * @param iWhere
 * The pointer to the factory of the curves. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCrv1
 * The pointer to the first curve.
 * @param iCrv2
 * The pointer to the second curve.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATDistanceMinCrvCrv * CATCreateDistanceMin(CATGeoFactory * iWhere, 
                                                               CATSoftwareConfiguration * iConfig,
                                                               CATCurve * iCrv1,
                                                               CATCurve * iCrv2,
                                                               CATSkillValue iMode = BASIC);

#endif
