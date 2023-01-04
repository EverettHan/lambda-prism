#ifdef _Coverage_GOO
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATDraftPoint:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// March. 99     Creation                                       J. Saloux
//=============================================================================

#ifndef CATDraftPoint_h
#define CATDraftPoint_h

#include "CATMathDef.h"
#include "CATConnect.h"
#include "CATGeoOperator.h"

class CATGeoFactory;
class CATDraftSurface;
class CATCrvParam;
//class CATDraftPoint;
//
enum CATDraftPointResult {CATDraftPtNoSol, CATDraftPtIntersec,CATDraftPtGlobalConf,CATDraftPtLocalConf};

class ExportedByConnect CATDraftPoint : public CATGeoOperator
{    
 public:
	CATDraftPoint(CATGeoFactory* factory);

  virtual ~CATDraftPoint() =0;

  virtual int Run() =0;
  
  virtual CATDraftPointResult GetResult() =0;
  virtual void GetMaxConf(double &Hmin,double &Hmax) = 0;
  virtual void GetParams(CATCrvParam &P1,CATCrvParam &P2,CATLength &L1,CATLength &L2) =0;
  virtual void Intersection(CATSurface *Sur1, CATSurface *Sur2, CATCurve *&C1, CATCurve *&C2) =0;
};

#endif
#endif
