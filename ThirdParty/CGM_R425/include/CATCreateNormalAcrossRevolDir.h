// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateNormalAcrossRevolDir : creation of an operator that computes along	a PCurve all the normal to the surface 
// which are perpendicular to local revol direction
//
//=============================================================================

#ifndef CATCreateNormalAcrossRevolDir_h 
#define CATCreateNormalAcrossRevolDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"
#include "CreateNormalAcrossRevolDir.h"

class CATExtractNormalAcrossRevolDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
class CATSoftwareConfiguration;

ExportedByY300IINT CATExtractNormalAcrossRevolDir * CATCreateNormalAcrossRevolDir (CATGeoFactory    * Factory,
                                                                                   CATSoftwareConfiguration *Config,
                                                                                   CATPCurve        * PCurve,
                                                                                   CATMathPoint     & Origin,
                                                                                   CATMathDirection & Direction,
                                                                                   CATCrvParam      & StartCrvParam,
                                                                                   CATCrvParam      & EndCrvParam,
                                                                                   CATSkillValue      iMode = BASIC );



#endif


