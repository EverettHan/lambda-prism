// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPGMBodyTessDeltaCache.h
//
//===================================================================
//
// Feb 2016  Creation: TPG
//===================================================================

#ifndef CATPGMBodyTessDeltaCache_H
#define CATPGMBodyTessDeltaCache_H

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

class CATTessSettings;
class CATListPtrCATCell;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATPGMBodyTessDeltaCache;
#else
extern "C" const IID IID_CATPGMBodyTessDeltaCache ;
#endif

class ExportedByCATGMModelInterfaces CATPGMBodyTessDeltaCache: public CATBaseUnknown
{
CATDeclareInterface;

public:
  //Update tess cache
  //return S_OK if all cells have cache
  //return S_FALSE if some cells don't have cache
	//oListPtrCATCell : list of CATCell actually having cache
	virtual HRESULT Update(CATTessSettings * iTessSettings, CATListPtrCATCell * oListPtrCATCell=0) = 0;

  //Flag tess cache as persistent
  //To be done during an execute before save process
  //return S_OK if all cells have cache
  //return S_FALSE if some cells don't have cache
	//oListPtrCATCell : list of CATCell actually having cache
  virtual HRESULT SetPersistent(CATTessSettings * iTessSettings, CATListPtrCATCell * oListPtrCATCell=0) = 0;

public:
  //Check
  //return S_OK if all cells have cache
  //return S_FALSE if some cells don't have cache
	//oListPtrCATCell : list of CATCell actually having cache
  virtual HRESULT Check(CATTessSettings * iTessSettings, CATListPtrCATCell * oListPtrCATCell=0)=0;
};

//-----------------------------------------------------------------------
CATDeclareHandler( CATPGMBodyTessDeltaCache, CATBaseUnknown );

//Activation
ExportedByCATGMModelInterfaces int IsCGMStaticTessDeltaCacheActivated();

//Persistence
ExportedByCATGMModelInterfaces int IsCGMStaticTessDeltaCachePersistent();

#endif
