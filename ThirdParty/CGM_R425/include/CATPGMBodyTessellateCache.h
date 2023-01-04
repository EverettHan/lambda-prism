// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPGMBodyTessellateCache.h
//
//===================================================================
//
// Dec 2011  Creation: ZFI
//===================================================================

#ifndef CATPGMBodyTessellateCache_H
#define CATPGMBodyTessellateCache_H

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

class CATTessSettings;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATPGMBodyTessellateCache;
#else
extern "C" const IID IID_CATPGMBodyTessellateCache ;
#endif

class ExportedByCATGMModelInterfaces CATPGMBodyTessellateCache: public CATBaseUnknown
{
CATDeclareInterface;

public:
  //Update tess cache
	virtual HRESULT Update(CATTessSettings * iTessSettings) = 0;

  //Flag tess cache as persistent
  //To be done during an execute before save process
  virtual HRESULT SetPersistent(CATTessSettings * iTessSettings) = 0;

public:
  //Check
  //return S_OK if a cache is available for the body
  //return S_FALSE if no cache is available for the body
  virtual HRESULT Check(CATTessSettings * iTessSettings)=0;
};

//-----------------------------------------------------------------------
CATDeclareHandler( CATPGMBodyTessellateCache, CATBaseUnknown );

//Activation
ExportedByCATGMModelInterfaces int IsCGMStaticTessellationCacheActivated();

//Persistence
ExportedByCATGMModelInterfaces int IsCGMStaticTessellationCachePersistent();

#endif
