#include "CATIPGMDistanceToolImplDeclare.h"

  // ---------- CATEnhancedDistanceTool

  virtual CATLONG32 ValidateInitSide(
    CATCurve *iCurve,
    CATCrvParam &iCrvParam,
    CATSurface *iSurface,
    CATSurParam &iSurParam,
    double iRadiusValue,
    double *iTangent3D,
    double *oProduct);

  virtual CATLONG32 ProjectOnOriginalSurface(
    CATCurve *iCurve,
    CATCrvParam &iParam,
    CATSurface *&oOriginalSurface,
    CATPCurve *&oOriginalPCurve,
    CATCrvParam &oParam,
    CATSurParam &oCorrespondingParam);

  virtual CATEdgeCurve *GetMaps2DCurve(CATCurve *iCurve, CATCrvParam &iCrvParam);

  virtual void GetNewSmoothing(CATLONG32 &oSmooth);

