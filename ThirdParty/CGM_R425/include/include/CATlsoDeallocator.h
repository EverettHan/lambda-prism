//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022 - ALL RIGHTS RESERVED.
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Desalloc tools for 
//                       CATLSOHashTable, CATLSOHashMap, CATlsoList 
//===================================================================

#ifndef CATlsoDeallocator_H
#define CATlsoDeallocator_H

#include "CATSysErrorDef.h" // HRESULT

// ---------------------------------------------------------------------------------
// Dealloc utilities
//
// To be used with method  HRESULT DeleteAll(T * iElement),
//   in CATLSOHashTable, CATLSOHashMap, CATlsoList ...
// ---------------------------------------------------------------------------------
namespace LSO
{

#if !defined _AIX_SOURCE
/**
  * The Deallocator is a function pointer.
  * This Deallocator is called to deallocate the data passed in argument.
  * You may want to use the "delete[]" C++ keyword, or use your own deallocator,
  * or you can do nothing if the data does not need to be deallocated.
  */
  template <class T>
  using DesallocFunc = HRESULT (*) (T * iElement);

#endif

  template <class T>
  HRESULT DeleteDesalloc(T * iElem)
  {
    HRESULT hr = S_OK;
    if (iElem)    
      delete iElem;      
    
    return hr;
  }

  template <class T>
  HRESULT ReleaseDesalloc(T * iElem)
  {
    HRESULT hr = S_OK;
    if (iElem)    
      iElem->Release();     

    return hr;
  }
  
}

#endif /*CATlsoDeallocator_H*/
