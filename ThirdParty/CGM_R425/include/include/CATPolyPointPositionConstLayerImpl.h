// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointPositionConstLayerImpl.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyPointPositionConstLayerImpl_H
#define CATPolyPointPositionConstLayerImpl_H

#include "CATIPolyPointPositionConstLayer.h"
#include "CATIPolyPoint.h"
#include "CATMathPoint.h"


/**
 * Implementation class of a CATIPolyPointPositionConstLayer.
 */
class CATPolyPointPositionConstLayerImpl : public CATIPolyPointPositionConstLayer
{

public:

  CATPolyPointPositionConstLayerImpl (const CATIPolyPoint& iPoint) : _Point (iPoint) {}

public:

  HRESULT Get (double &x, double &y, double &z) const
  {
    CATMathPoint P;
    HRESULT hr = _Point.GetPosition (P);
    x = P.GetX (); y = P.GetY (); z = P.GetZ ();
    return hr;
  }

public:

  HRESULT Get (int v, double &x, double &y, double &z) const
  {
    CATMathPoint P;
    HRESULT hr = _Point.GetPosition (P);
    x = P.GetX (); y = P.GetY (); z = P.GetZ ();
    return hr;
  }

  HRESULT Get (int v, CATMathPoint &oPosition) const
  {
    return _Point.GetPosition (oPosition);
  }

protected:

  const CATIPolyPoint& _Point;
};

#endif // !CATPolyPointPositionConstLayerImpl_H
