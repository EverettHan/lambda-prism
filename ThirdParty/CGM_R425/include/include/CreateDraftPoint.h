#ifdef _Coverage_GOO
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateDraftPoint:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Dec. 99	   Creation                                       J. Saloux
//=============================================================================

#ifndef CreateDraftPoint_h
#define CreateDraftPoint_h

#include "CATListOfCATCrvParams.h"

#include "CATSkillValue.h"
#include "Connect.h"

class CATDraftPoint;
class CATGeoFactory;
class CATCurve;
class CATMathDirection;
class CATCrvLimits;

ExportedByConnect CATDraftPoint * CreateDraftPoint(CATGeoFactory *iFactoryPtr,
							   const CATMathDirection & direction,
							   const CATAngle & angle1	,const CATAngle & angle2,
							   CATCurve * profile1		,CATCurve *Profile2,
							   CATCrvParam * limits1	,CATCrvParam * limits2 ,
							   double * iLength1		,double * iLength2,
							   int Sens,
							   const CATSkillValue skill = BASIC);

ExportedByConnect void Remove(CATDraftPoint * oper);

#endif
#endif

