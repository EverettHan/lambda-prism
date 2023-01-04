#include "CATIPGMOperatorImplDeclare.h"

  // ---------- CATSurTo2DGlobalMapping

/* Already defined in a parent class
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const;
*/

  virtual CATIPGMSurTo2DMapping *CreateLocalMapping(
    CATSurface *iLocalReference,
    const double &iRefOrientation,
    const CATSurLimits &iRefLimits) const;

  virtual void RemoveLocalMapping(CATIPGMSurTo2DMapping *iLocalMapping);

  virtual void Stream(CATCGMStream &Str, const char *iLabelReserved) const;
