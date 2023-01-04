//=============================================================================
// COPYRIGHT Dassault Systemes 2021
//=============================================================================
//
// CATPolyCurveVertexIterator it(*curve);
// for(; !it.End(); ++it)
//  int v = *it;
//
//=============================================================================
// Mar 2021 : F1Z : New
//=============================================================================

#pragma once 

#include "CATSysErrorDef.h"
#include "PolyhedralModel.h"
#include "CATIPolyIndexIterator.h"
#include "CATBoolean.h"

#include "CATIPolyCurveVertexIterator.h"

class CATIPolyCurve;

/**
 * For interface encapsulation
 */
class ExportedByPolyhedralModel CATPolyCurveVertexIterator
{
public:
  CATPolyCurveVertexIterator();
  CATPolyCurveVertexIterator(const CATIPolyCurve & iCurve);

  CATPolyCurveVertexIterator(const CATPolyCurveVertexIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
  }

  inline ~CATPolyCurveVertexIterator()
  {
    if (_ite)
      _ite->Release();
    _ite = 0;
  }

  CATPolyCurveVertexIterator & Begin(const CATIPolyCurve & iCurve);
  CATPolyCurveVertexIterator & Begin(const CATIPolyCurve * iCurve);

  inline CATPolyCurveVertexIterator operator=(CATPolyCurveVertexIterator & iToCopy)
  {
    _ite = iToCopy._ite;
    if (_ite)
      _ite->AddRef();
    return *this;
  }

  inline HRESULT GetStatus() const { return _hr; };

  inline CATPolyCurveVertexIterator & Begin()
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

  inline CATPolyCurveVertexIterator &operator++()
  {
    ++(*_ite); /// no ptr check, call should check with End() before calling it
    return *this;
  }

private:
  HRESULT _hr;
  CATIPolyCurveVertexIterator * _ite;
};
