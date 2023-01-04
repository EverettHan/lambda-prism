// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveVertexPositionLayer.h
//
//===================================================================
// 2010-01-20 NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyCurveVertexPositionConstLayer.h"


class ExportedByPolyhedralAttributes CATIPolyCurveVertexPositionLayer : public CATIPolyCurveVertexPositionConstLayer
{

public:

  virtual HRESULT Set (int v, const double* a);

  /**
   * Update the vertex coordinates.
   * @param v
   *   The index of the vertex.
   * @param x, y, z
   *   The new position of the vertex.
   * @return
   *   S_OK if the coordinates are successfully updated and E_FAIL otherwise.
   */
  virtual HRESULT Set (int v, double x, double y, double z) = 0;

protected:

  CATIPolyCurveVertexPositionLayer () {}
  virtual ~CATIPolyCurveVertexPositionLayer () {}

};
