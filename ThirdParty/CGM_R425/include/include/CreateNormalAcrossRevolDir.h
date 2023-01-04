// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateNormalAcrossRevolDir : creation of an operator that computes along	a PCurve all the normal to the surface 
// which are perpendicular to local revol direction
//
//=============================================================================

#ifndef CreateNormalAcrossRevolDir_h 
#define CreateNormalAcrossRevolDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"

class CATExtractNormalAcrossRevolDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
/**
* @deprecated V5R13 CATCreateNormalAcrossRevolDir
*/
ExportedByY300IINT CATExtractNormalAcrossRevolDir * CreateNormalAcrossRevolDir ( CATGeoFactory    * Factory       ,
					                                                             CATPCurve        * PCurve        ,
                                                                                 CATMathPoint     & Origin        ,
					                                                             CATMathDirection & Direction     ,
					                                                             CATCrvParam      & StartCrvParam ,
					                                                             CATCrvParam      & EndCrvParam   ,
					                                                             CATSkillValue      iMode = BASIC );

ExportedByY300IINT void Remove (CATExtractNormalAcrossRevolDir *&iOperatorToRemove) ;

#endif


