#ifndef CATCGMItfProtectedServices_h
#define CATCGMItfProtectedServices_h

#include "CATMathematics.h"
#include "IUnknown.h"
#include "CATCGMItfDestrBehavior.h"

class CATCGMVirtualItf;
class CATCGMVirtual;

/**
 * Services for CGM interfaces.
 * <b>Role:</b>
 */
class ExportedByCATMathematics CATCGMItfProtectedServices
{
public:
  /**
   * Returns the object that is exposed by the interface.
   * @param ipInterface
   *   The interface.
   * @return
   *   The component. Pay attention: you must not delete it.
   */
  static CATCGMVirtual *GetHandledObject(const CATCGMVirtualItf *ipInterface);

  /**
   * Makes or creates an interface of the specified object.
   * @param ipHandledObject
   *   The object that is to be handled by the interface.
   * @param iIID
   *   The interface Id.
   * @param iItfDestrBehavior
   *   <tt>TRUE</tt> if the handled object must be deleted with the current data.<br>
   *   If the object is already interfaced, this argument is ignored: the previous interface
   *   manages the object's lifecycle.
   * @return [out, IUnknown#Release]
   *   The interface.
   */
  static CATCGMVirtualItf *QueryInterface(CATCGMVirtual *ipHandledObject, const IID &iIID, CATCGMItfDestrBehavior iItfDestrBehavior);
};

#endif
