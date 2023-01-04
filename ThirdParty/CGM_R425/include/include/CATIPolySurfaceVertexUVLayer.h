//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of per-surface-vertex UV parameter interface
//
//=============================================================================
// 2007-05-29   BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexUVLayer_H
#define CATIPolySurfaceVertexUVLayer_H

#include "PolyhedralAttributes.h"

#include "CATErrorDef.h"
#include "CATIPolySurfaceVertexUVConstLayer.h"


//
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexUVLayer : public CATIPolySurfaceVertexUVConstLayer
{
protected:

  CATIPolySurfaceVertexUVLayer () {}
  virtual ~CATIPolySurfaceVertexUVLayer () {}

public:

  virtual HRESULT Set (int iVertex, double u, double v) = 0;

  virtual HRESULT Set (int v, const double* a);

public:

  /**
   * Casts as a non-const layer.
   */
  CATIPolySurfaceVertexUVLayer* NonConstCast ();

};

#endif // !CATIPolySurfaceVertexUVLayer_H
