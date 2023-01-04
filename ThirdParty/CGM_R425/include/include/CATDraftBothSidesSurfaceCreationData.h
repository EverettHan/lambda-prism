//=============================================================================
// Apr. 03   Creation                                          PFV
//=============================================================================
#ifndef CATDraftBothSidesSurfaceCreationData_H
#define CATDraftBothSidesSurfaceCreationData_H

#include "CATDraftSurfaceCreationData.h"

#include "CATListOfCATCrvParams.h"
#include "CATSurLimits.h"
#include "CATMathDirection.h"
class CATSurface;
class CATPCurve;



class ExportedByYP00IMPL CATDraftBothSidesSurfaceCreationData : public CATDraftSurfaceCreationData
{
public:

  CATDraftBothSidesSurfaceCreationData();
  ~CATDraftBothSidesSurfaceCreationData();
   virtual int IsEqualTo(CATDraftSurfaceCreationData * DataToCompare, double LengthTol=0, double AngleTol=0) const;
   virtual CATDraftSurfaceCreationData::DraftDataType GetDataType() const;

   void GetSupport(const CATLONG32 iSupportID, CATGeometry *& oSupport,
                         CATLONG32 & oOrientation) const;
   void GetContact(const CATLONG32 iSupportID, CATGeometry *& oSupport) const;

   CATSurface *     _Surfaces[3];
   CATSurLimits     _SurLimits[3];
   CATPCurve  *     _PCurves[3];
   CATLONG32             _Orientation[2];
   short            _MixingFunctionType; // 1-> DrivingDriven, 2-> Fitted
   CATMathDirection direction2;
   double           angle2;
   double           _SmoothParameter;
   CATLONG32             _ConstraintType;
   short            _DraftSide;  // 0 si la surface s'appuie sur le support 0, 1 si la surface s'appuie sur le support 1
};

#endif

