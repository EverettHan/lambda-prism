//=============================================================================
// Apr. 03   Creation                                          PFV
//=============================================================================
#ifndef CATSimpleDraftSurfaceCreationData_H
#define CATSimpleDraftSurfaceCreationData_H

#include "YP00IMPL.h"
#include "CATCurve.h"
#include "CATCrvLimits.h"
#include "CATCGMVirtual.h"

#include "CATDraftSurfaceCreationData.h"

class CATEdgeCurve;
class CATLaw;
class CATPCurve;

class ExportedByYP00IMPL CATSimpleDraftSurfaceCreationData : public CATDraftSurfaceCreationData
{
public:

  CATSimpleDraftSurfaceCreationData();
  ~CATSimpleDraftSurfaceCreationData();
  virtual int IsEqualTo(CATDraftSurfaceCreationData * DataToCompare, double LengthTol=0, double AngleTol=0) const;
  virtual CATDraftSurfaceCreationData::DraftDataType GetDataType() const;

  CATCurve * NeutralCurve;
  
  double StartLength;
  double EndLength;
  CATCrvLimits limits;
  
  //New Data 27/11/00
  CATEdgeCurve * EdgeCurve;

  //Only For Variable Draft. If PNeutral != NULL => Variable Draft.
  //If AngleLaw==MappingLaw==NULL => Constant Variable Draft = angle.
  CATPCurve * PNeutral;
  CATLaw    * AngleLaw;
  CATLaw    * MappingLaw;
  CATBoolean OrnSupp;
  
};
#endif
