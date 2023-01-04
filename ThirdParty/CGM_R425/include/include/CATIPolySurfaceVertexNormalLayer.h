//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of per-vertex normal interface
//
//=============================================================================
// 2007-05-29   BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexNormalLayer_H
#define CATIPolySurfaceVertexNormalLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolySurfaceVertexNormalConstLayer.h"

class CATMathVector;


class ExportedByPolyhedralAttributes CATIPolySurfaceVertexNormalLayer : public CATIPolySurfaceVertexNormalConstLayer
{

public:

  virtual HRESULT Set (int v, const double* a);
  virtual HRESULT Set (int iVertex, const CATMathVector &iNormal) = 0;

public:

  /**
  * Casts as a non-const layer.
  */
  CATIPolySurfaceVertexNormalLayer* NonConstCast ();

protected:

  virtual ~CATIPolySurfaceVertexNormalLayer () {}

};

#endif // !CATIPolySurfaceVertexNormalLayer_H
