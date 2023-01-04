// COPYRIGHT DASSAULT SYSTEMES 1999
//==========================================================================================================
//
// CreateNormalAlongDir: creation of an operator that computes along a PCurve all the normal to the surface 
// which are perpendicular to a given direction
//
//==========================================================================================================

#ifndef CreateNormalAlongDir_h 
#define CreateNormalAlongDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"

class CATExtractNormalAlongDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;

/**
* @deprecated V5R13 CATCreateNormalAlongDir 
*/
ExportedByY300IINT CATExtractNormalAlongDir * CreateNormalAlongDir ( CATGeoFactory    * Factory       ,
					                                                 CATPCurve        * PCurve        ,
					                                                 CATMathDirection & Direction     ,
					                                                 CATCrvParam      & StartCrvParam ,
					                                                 CATCrvParam      & EndCrvParam   ,
					                                                 CATSkillValue      iMode=BASIC   );

ExportedByY300IINT void Remove (CATExtractNormalAlongDir *&iOperatorToRemove) ;

#endif


