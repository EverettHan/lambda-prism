#include "CATIPGMOperatorImplDefine.h"
#include "CATIPGMSurTo2DMapping.h"
#include "CATCGMItfProtectedServices.h"

// ---------- CATSurTo2DGlobalMapping

/* Already defined in a parent class
CATSoftwareConfiguration *CATCGM_ITF_IMPL_CLASS::GetSoftwareConfiguration() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSoftwareConfiguration();
}
*/

CATIPGMSurTo2DMapping *CATCGM_ITF_IMPL_CLASS::CreateLocalMapping(
    CATSurface *iLocalReference,
    const double &iRefOrientation,
    const CATSurLimits &iRefLimits) const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  CATSurTo2DMapping *pObject = HandledObject.CreateLocalMapping(
    iLocalReference,
    iRefOrientation,
    iRefLimits);
  CATIPGMSurTo2DMapping *pInterface = (CATIPGMSurTo2DMapping *)CATCGMItfProtectedServices::QueryInterface(pObject, IID_CATIPGMSurTo2DMapping, CATCGMDeleteObjWithItf); // The object will be deleted by its interface
  return pInterface;
}

void CATCGM_ITF_IMPL_CLASS::RemoveLocalMapping(CATIPGMSurTo2DMapping *iLocalMapping)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  CATSurTo2DMapping *pMapping = (CATSurTo2DMapping *)CATCGMItfProtectedServices::GetHandledObject(iLocalMapping);
  HandledObject.RemoveLocalMapping(pMapping);
}

void CATCGM_ITF_IMPL_CLASS::Stream(CATCGMStream &Str, const char *iLabelReserved) const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.Stream(Str, iLabelReserved);
}

/* Already defined in a parent class
void CATCGM_ITF_IMPL_CLASS::Stream(CATCGMStream &Str, const char const *iLabelReserved) const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.Stream(Str, iLabelReserved);
}
*/
