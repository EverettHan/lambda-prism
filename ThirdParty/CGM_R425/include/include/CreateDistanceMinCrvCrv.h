#ifndef CreateDistanceMinCrvCrv_H
#define CreateDistanceMinCrvCrv_H

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

/**
 * @deprecated V5R11 CATCreateDistanceMin
 */
ExportedByY300IINT CATDistanceMinCrvCrv * CreateDistanceMin(CATGeoFactory * iWhere, 
                                                            CATCurve * iCrv1,
                                                            CATCurve * iCrv2,
                                                            CATSkillValue iMode = BASIC);
/**
 *@nodoc
 * Removes a CATDistanceMinCrvCrv operator from memory.
 */
ExportedByY300IINT void Remove(CATDistanceMinCrvCrv *iOperatorToRemove);


#endif
