// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessCacheChecker.h
//
//===================================================================
//
// JUL 2012  Creation: NHD
//===================================================================

#ifndef CATTessCacheChecker_H
#define CATTessCacheChecker_H

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATTessCacheChecker;
#else
extern "C" const IID IID_CATTessCacheChecker ;
#endif

class ExportedByCATGMModelInterfaces CATTessCacheChecker: public CATBaseUnknown
{
CATDeclareInterface;

public:
  //Update tess cache
	//virtual HRESULT Update() = 0;

  //Flag tess cache as persistent
  //To be done during an execute before save process
  //virtual HRESULT SetPersistent() = 0;

public:
  //CheckExistence
  //return S_OK if a cache is available for the body
  //return S_FALSE if no cache is available for the body
  virtual HRESULT CheckExistence()=0;

  //CheckValidity
  //return S_OK if a cache is valid for the body
  //return S_FALSE if cache is invalid for the body
  virtual HRESULT CheckValidity()=0;

  //CheckBuildRepStatic
  //return S_OK if a cache is valid for the body
  //return E_Fail if cache is not valid for the body
  virtual HRESULT CheckBuildRepStatic()=0;

};

//-----------------------------------------------------------------------
CATDeclareHandler( CATTessCacheChecker, CATBaseUnknown );

//Activation
//ExportedByCATGMModelInterfaces int IsCGMTessellationCacheActivated();

//Persistence
//ExportedByCATGMModelInterfaces int IsCGMTessellationCachePersistent();

#endif
