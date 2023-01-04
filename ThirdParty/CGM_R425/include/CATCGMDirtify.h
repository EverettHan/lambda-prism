/* -*-c++-*- */
#ifndef CATCGMDirtify_H_
#define CATCGMDirtify_H_
// COPYRIGHT DASSAULT SYSTEMES  2009
//=============================================================================
//  Dedicated to Object Dirtification FOR INTERNAL CGM USE
//  To signal that object are dirty used in context f the incrmentalStream
//=============================================================================
// Nov. 09  Creation                                                      VUC
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATICGMObject.h"
#include "IUnknown.h"
#include "CATCGMDebug.h"


//-------------------------------------------------------------------------
// CATCGMDirtify
//-------------------------------------------------------------------------
class ExportedByGeometricObjects CATCGMDirtify
{
public:
  /**
  * Mark an object as Dirty : modified but not saved
  * @param iObject 
  *  The input interface on the object to mark.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt>S_OK</dt><dd>when marking was done correctly.
  * <dt>E_FAIL</dt><dd>otherwise
  *</dl>
  */
  INLINE static HRESULT SetWasModified(CATICGMObject* iObject)
  {
    return CATCGMDebug::SetWasModified(iObject);
  }
};

#endif
