// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTriTangentPCrv :
// creation of an operator of TriTangent between 3 PCurves on a plan
// These PCurves must have the same support
// The iSide argument is to indicate the side regarding the PCurve where
// the center of the PCircle should be found
//
//=============================================================================

#ifndef CreateTriTangentPCrv_h 
#define CreateTriTangentPCrv_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATTriTangentPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATSoftwareConfiguration ;

/**
* @deprecated V5R13 CATCreateTriTangentPCrv
*/
/*
ExportedByY300IINT CATTriTangentPCrv *
                   CreateTriTangentPCrv (CATGeoFactory *Factory,
					 CATPCurve     *PCurve1, CATLONG32 iSide1,  
					 CATPCurve     *PCurve2, CATLONG32 iSide2, 
					 CATPCurve     *PCurve3, CATLONG32 iSide3, 
					 CATSkillValue iMode=BASIC);
*/

/**
* @deprecated V5R13 CATCreateTriTangentPCrv 
*/
/*
ExportedByY300IINT CATTriTangentPCrv *
                   CreateTriTangentPCrv (CATGeoFactory *Factory,
           CATSoftwareConfiguration * iConfig,
					 CATPCurve     *PCurve1, CATLONG32 iSide1,  
					 CATPCurve     *PCurve2, CATLONG32 iSide2, 
					 CATPCurve     *PCurve3, CATLONG32 iSide3, 
					 CATSkillValue iMode=BASIC);
*/

ExportedByY300IINT void Remove (CATTriTangentPCrv *iOperatorToRemove) ;

#endif


