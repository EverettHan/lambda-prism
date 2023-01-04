#ifndef CreateLayDownCrvSur_H
#define CreateLayDownCrvSur_H

// COPYRIGHT DASSAULT SYSTEMES  2000


#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATListOfCATCurves.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"

class CATLayDownCrvSur;
class CATMultiSurface;
class CATGeoFactory;
class CATSurface;
class CATCurve;
/**
* @deprecated V5R13 CATCreateLayDownCrvSur
*/
ExportedByY300IINT CATLayDownCrvSur * CreateLayDownCrvSur(CATGeoFactory * iWhere,
                                                          CATLISTP(CATCurve) * iCurveList, 
                                                          CATMultiSurface * iMultiSurface,
                                                          CATSkillValue iMode=BASIC);
/**
* @deprecated V5R13 CATCreateLayDownCrvSur
*/
ExportedByY300IINT CATLayDownCrvSur * CreateLayDownCrvSur(CATGeoFactory * iFactory, 
                                                          CATCurve * iCurve,
                                                          CATCrvLimits & iCrvLimits,
                                                          CATSurface * iSurface,
                                                          CATSurLimits & iSurLimits,
                                                          CATSkillValue iMode=BASIC);



/**
 * @nodoc
 * Removes a CATLayDownCrvSur operator from memory.
 */
ExportedByY300IINT void Remove(CATLayDownCrvSur * &iOperatorToRemove);


#endif
