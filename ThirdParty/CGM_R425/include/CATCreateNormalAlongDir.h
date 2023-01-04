// COPYRIGHT DASSAULT SYSTEMES 1999
//==========================================================================================================
//
// CreateNormalAlongDir: creation of an operator that computes along a PCurve all the normal to the surface 
// which are perpendicular to a given direction
//
//==========================================================================================================

#ifndef CATCreateNormalAlongDir_h 
#define CATCreateNormalAlongDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"
#include "CreateNormalAlongDir.h"

class CATExtractNormalAlongDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
class CATSoftwareConfiguration;

ExportedByY300IINT CATExtractNormalAlongDir * CreateNormalAlongDir ( CATGeoFactory    * Factory,
                                                                    CATSoftwareConfiguration *Config,
                                                                    CATPCurve        * PCurve,
                                                                    CATMathDirection & Direction ,
                                                                    CATCrvParam      & StartCrvParam,
                                                                    CATCrvParam      & EndCrvParam,
                                                                    CATSkillValue      iMode=BASIC);



#endif


