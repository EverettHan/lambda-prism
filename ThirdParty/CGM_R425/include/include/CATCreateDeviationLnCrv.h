#ifndef CATCreateDeviationLnCrv_h
#define CATCreateDeviationLnCrv_h

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATMathLine;
class CATCrvParam;
class CATGeoFactory;
class CATCurve;
class CATSoftwareConfiguration;
class CATDeviationLnCrv;

ExportedByY300IINT
CATDeviationLnCrv * CATCreateDeviationLnCrv(CATGeoFactory  *iWhere,
                                            CATSoftwareConfiguration * iConfig,
																				    const CATMathLine & iLine,
																				    CATCurve * iCurve,
                                            CATSkillValue iMode = BASIC);
   

#endif

