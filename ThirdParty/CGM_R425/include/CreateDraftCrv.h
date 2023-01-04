//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateDraftCrv:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Dec. 97     Creation                                       S. Royer
//=============================================================================

#ifndef CreateDraftCrv_h
#define CreateDraftCrv_h

#include "CATListOfCATCrvParams.h"

#include "CATSkillValue.h"
#include "Connect.h"
#include "CATMathDef.h"

class CATDraftCrv;
class CATGeoFactory;
class CATCurve;
class CATMathDirection;
class CATCrvLimits;
class CATLaw;
class CATEdgeCurve;
class CATPCurve;

ExportedByConnect
void Remove(CATDraftCrv *& oper);

#endif
