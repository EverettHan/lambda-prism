// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPGMBodyTessCache.h
//
//===================================================================
//
// Dec 2011  Creation: ZFI
//===================================================================

#ifndef CATPGMBodyTessCache_H
#define CATPGMBodyTessCache_H

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATPGMBodyTessCache;
#else
extern "C" const IID IID_CATPGMBodyTessCache ;
#endif

class ExportedByCATGMModelInterfaces CATPGMBodyTessCache: public CATBaseUnknown
{
CATDeclareInterface;

public:
  //Update tess cache
	virtual HRESULT Update() = 0;

  //Flag tess cache as persistent
  //To be done during an execute before save process
  virtual HRESULT SetPersistent() = 0;

public:
  //Check
  //return S_OK if a cache is available for the body
  //return S_FALSE if no cache is available for the body
  virtual HRESULT Check()=0;
};

//-----------------------------------------------------------------------
CATDeclareHandler( CATPGMBodyTessCache, CATBaseUnknown );

//Activation
ExportedByCATGMModelInterfaces int IsCGMTessellationCacheActivated();

//Persistence
ExportedByCATGMModelInterfaces int IsCGMTessellationCachePersistent();

#endif
