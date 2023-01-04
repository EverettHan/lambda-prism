#ifndef CATCGM_OMX_MLK_TRACKER_Internal_h
#define CATCGM_OMX_MLK_TRACKER_Internal_h

#include "ExportedByGeometricObjects.h"
#include "CATBaseUnknown.h"

class ExportedByGeometricObjects CATCGM_OMX_MLK_TRACKER_Internal
{
public:
  CATCGM_OMX_MLK_TRACKER_Internal();
  virtual ~CATCGM_OMX_MLK_TRACKER_Internal();

  virtual void Create(CATBaseUnknown *iObject, CATMetaClass *iMetaObject, const char *iFwName) = 0;
  virtual void AddRef(CATBaseUnknown *iObject, LONG im_cRef) = 0;
  virtual void Release(CATBaseUnknown *iObject, LONG im_cRef) = 0;
  virtual void Destroy(CATBaseUnknown *iObject) = 0;

private:
  CATCGM_OMX_MLK_TRACKER_Internal(const CATCGM_OMX_MLK_TRACKER_Internal &iObject); // Prohibited
  CATCGM_OMX_MLK_TRACKER_Internal &operator=(const CATCGM_OMX_MLK_TRACKER_Internal &iObject); // Prohibited
};

#endif /* CATCGM_OMX_MLK_TRACKER_Internal_h */
