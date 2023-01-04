//=============================================================================
// Nov. 05   Creation                                          SOU
//=============================================================================
#ifndef CATDraftBothSidesNeutralNeutralSurfaceCreationData_H
#define CATDraftBothSidesNeutralNeutralSurfaceCreationData_H

#include "CATDraftSurfaceCreationData.h"

#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CATMathDirection.h"

class CATCurve;
class CATSurface;
class CATPCurve;

class ExportedByYP00IMPL CATDraftBothSidesNeutralNeutralSurfaceCreationData : public CATDraftSurfaceCreationData
{
public:

  CATDraftBothSidesNeutralNeutralSurfaceCreationData();
  ~CATDraftBothSidesNeutralNeutralSurfaceCreationData();
   virtual int IsEqualTo(CATDraftSurfaceCreationData* DataToCompare, double LengthTol=0, double AngleTol=0) const;
   virtual CATDraftSurfaceCreationData::DraftDataType GetDataType() const;

   void GetSupport(const CATLONG32 iSupportID, CATGeometry* &oSupport,
                         CATLONG32 &oOrientation) const;
   void GetContact(const CATLONG32 iSupportID, CATGeometry* &oSupport) const;

   CATCurve*    _Curves[2]; //neutral curves
   CATCrvLimits     _CrvLimits[2];
   CATSurface*      _Surface;//parting surface
   CATSurLimits     _SurLimit;
   CATPCurve*       _PCurves[3];
   CATLONG32        _Orientation[2]; //we need this to : decide on which side of support curve is the draft surface present
   short            _MixingFunctionType; // 1-> DrivingDriven, 2-> Fitted
   CATMathDirection direction2;
   double           angle2;
   double           _SmoothParameter;
   CATLONG32        _ConstraintType; //do we need this?
   short            _DraftSide;  // 0 is surface for support 0, 1 is surface for support 1
};

#endif

