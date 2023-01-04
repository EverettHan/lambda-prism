//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Layer of per-vertex position interface
//
//=============================================================================
// 2008-01-21   BPG: New
//=============================================================================
#ifndef CATIPolySurfaceVertexPositionLayer_H
#define CATIPolySurfaceVertexPositionLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolySurfaceVertexPositionConstLayer.h"


class ExportedByPolyhedralAttributes CATIPolySurfaceVertexPositionLayer
  : public CATIPolySurfaceVertexPositionConstLayer
{
protected:

  CATIPolySurfaceVertexPositionLayer () {}
  virtual ~CATIPolySurfaceVertexPositionLayer () {}

public:

  /**
   * Update the vertex coordinates.
   * @param v
   * The index of the vertex.
   * @param x, y, z
   * The new position of the vertex.
   * @return
   *   S_OK if the coordinates are successfully updated and E_FAIL otherwise.
   */
  virtual HRESULT Set (int v, double x, double y, double z) = 0;

  virtual HRESULT Set (int v, const double* a) { return Set (v, a[0], a[1], a[2]); }

};

#endif // !CATIPolySurfaceVertexPositionLayer_H
