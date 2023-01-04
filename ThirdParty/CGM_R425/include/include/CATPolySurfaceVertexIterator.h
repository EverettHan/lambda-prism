//=============================================================================
// COPYRIGHT Dassault Systemes 2021
//=============================================================================
//
// CATPolySurfaceVertexIterator it(*mesh);
// for(; !it.End(); ++it)
//  int v = *it;
//
//=============================================================================
// Feb 2021 : F1Z : New
//=============================================================================

#pragma once 

#include "CATSysErrorDef.h"
#include "PolyhedralModel.h"
#include "CATIPolyIndexIterator.h"
#include "CATBoolean.h"

#include "CATIPolySurfaceVertexIterator.h"

class CATIPolySurface;

/**
 * For interface encapsulation
 */
class ExportedByPolyhedralModel CATPolySurfaceVertexIterator
{
public:
  typedef int value_type;

public:
  CATPolySurfaceVertexIterator(const CATIPolySurface & iSurface);

  CATPolySurfaceVertexIterator(const CATPolySurfaceVertexIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
  }

  inline ~CATPolySurfaceVertexIterator()
  {
    if (_ite)
      _ite->Release();
    _ite = 0;
  }

  inline CATPolySurfaceVertexIterator operator=(CATPolySurfaceVertexIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
    return *this;
  }

  inline HRESULT GetStatus() const { return _hr; };

  inline CATPolySurfaceVertexIterator & Begin()
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

  inline CATPolySurfaceVertexIterator &operator++()
  {
    ++(*_ite); /// no ptr check, call should check with End() before calling it
    return *this;
  }

private:
  HRESULT _hr;
  CATIPolySurfaceVertexIterator * _ite;
};
