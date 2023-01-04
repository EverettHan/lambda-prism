#ifndef _CATContinuityQuery_HeaderFile
#define _CATContinuityQuery_HeaderFile
    
class CATCurve;
class CATPCurve;
class CATSurface;
class CATKnotVector;
class CATCrvLimits;
class CATSurLimits;

#include "CATIsoParameter.h"
#include "YP00IMPL.h"

class ExportedByYP00IMPL CATContinuityQuery
{
  public:

enum ContinuityLevel {
  ContinuityUnknown = -1000,
  ContinuityMinus1 = -1,
  Continuity0 = 0,
  Continuity1 = 1,
  Continuity2 = 2,
  Continuity3 = 3,
  Continuity4 = 4,
  Continuity5 = 5,
  Continuity6 = 6,
  Continuity7 = 7,
  Continuity8 = 8,
  Continuity9 = 9,
  Continuity10 = 10,
  Continuity11 = 11,
  Continuity12 = 12,
  Continuity13 = 13,
  Continuity14 = 14,
  Continuity15 = 15,
  Continuity16 = 16,
  Continuity17 = 17,
  Continuity18 = 18,
  Continuity19 = 19,
  Continuity20 = 20,
  ContinuityHigh = 100,
  ContinuityInfinite = 1000
};

static ContinuityLevel GetMinContinuity(const CATCurve * iCurve, const CATCrvLimits * iLimits);
static ContinuityLevel GetMinContinuity(const CATSurface * iSurface, CATIsoParameter iIsoParameter, const CATSurLimits * iLimits);

  private:
CATContinuityQuery();
CATContinuityQuery(const CATContinuityQuery &);
void operator = (const CATContinuityQuery &);

static ContinuityLevel GetMinContinuityUV(const CATPCurve * iPCurve, const CATCrvLimits * iLimits);
static ContinuityLevel GetKnotVectorContinuity(const CATKnotVector * iKnotVector, const double * iLimits);
static ContinuityLevel Min(ContinuityLevel iLevel0, ContinuityLevel iLevel1);
static ContinuityLevel GetContinuity(short iToConvert);
static ContinuityLevel MinusOne(ContinuityLevel iLevel);
};
#endif
