//=============================================================================
// COPYRIGHT Dassault Systemes 2021
//=============================================================================
//
// CATPolySurfaceFacetIterator it(*mesh);
// for(; !it.End(); ++it)
//  int t = *it;
//
//=============================================================================
// Feb 2021 : F1Z : New
//=============================================================================

#pragma once
#include "CATSysErrorDef.h"
#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"

#include "CATIPolySurfaceFacetIterator.h"

class CATIPolySurface;

/**
* For interface encapsulation
*/
class ExportedByPolyhedralModel CATPolySurfaceFacetIterator
{
public:
  typedef int value_type;
public:
  CATPolySurfaceFacetIterator(const CATIPolySurface & iSurface);

  CATPolySurfaceFacetIterator(const CATPolySurfaceFacetIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
  }

  inline ~CATPolySurfaceFacetIterator()
  {
    if (_ite)
      _ite->Release();
    _ite = 0;
  }

  inline CATPolySurfaceFacetIterator operator=(CATPolySurfaceFacetIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
    return *this;
  }

  inline HRESULT GetStatus() const { return _hr; };

  inline CATPolySurfaceFacetIterator & Begin()
  {
    if (_ite)
      _ite->Begin();
    return *this;
  }

  inline bool End() const
  {
    return !_ite || _ite->End();
  }


  inline int operator*() const
  {
    return _ite->Get(); /// no ptr check, call should check with End() before calling it
  }

  inline CATPolySurfaceFacetIterator &operator++()
  {
    ++(*_ite); /// no ptr check, call should check with End() before calling it
    return *this;
  }

private:
  HRESULT _hr;
  CATIPolySurfaceFacetIterator * _ite;
};
