#include "CATIPGMOperatorImplDeclare.h"

  // ---------- CATConnectTool

  virtual CATLONG32 GetType() const;

  virtual void SetOriginCurveSupport(CATSurface *iSupp, CATLONG32 iOrient);

  virtual void GetOriginCurveSupport(CATSurface *&oSupp, CATLONG32 &oOrient);

  virtual CATGeoODTScaleManager *GetScaleManager() const;

  virtual void SetScaleManager(CATGeoODTScaleManager *iScaleManager);

  virtual CATLONG32 GetSectionType() const;

