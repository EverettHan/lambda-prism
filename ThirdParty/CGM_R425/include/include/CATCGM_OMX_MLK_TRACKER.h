#ifndef CATCGM_OMX_MLK_TRACKER_h
#define CATCGM_OMX_MLK_TRACKER_h

#include "ExportedByGeometricObjects.h"
#include "CATCGM_OMX_MLK_TRACKER_Internal.h"

/**
 * Class for tracking memory leaks.<br>
 * It must be used as a global automatic instance in the cpp source of the class.
 */
class ExportedByGeometricObjects CATCGM_OMX_MLK_TRACKER
{
public:
  CATCGM_OMX_MLK_TRACKER();
  ~CATCGM_OMX_MLK_TRACKER();

  int  Create (const CATBaseUnknown *iObject, CATMetaClass *iMetaObject, const char *iFwName);
  void AddRef (const CATBaseUnknown *iObject, LONG im_cRef);
  void Release(const CATBaseUnknown *iObject, LONG im_cRef);
  void Destroy(const CATBaseUnknown *iObject);

private:
  CATCGM_OMX_MLK_TRACKER(const CATCGM_OMX_MLK_TRACKER &iObject); // Prohibited
  CATCGM_OMX_MLK_TRACKER &operator=(const CATCGM_OMX_MLK_TRACKER &iObject); // Prohibited

  CATCGM_OMX_MLK_TRACKER_Internal * CreateTracker();
// ------------------------------------------------------------------
  CATCGM_OMX_MLK_TRACKER_Internal *_pTracker;
  int                              _Status;
};
// ------------------------------------------------------------------

#endif /* CATCGM_OMX_MLK_TRACKER_h */
