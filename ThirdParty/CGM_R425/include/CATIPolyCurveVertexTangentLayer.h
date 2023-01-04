//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of per-curve-vertex tangent interface
//
//=============================================================================
// 2007-07-04   BPG: New.
//=============================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyCurveVertexTangentConstLayer.h"

class CATMathVector;


class ExportedByPolyhedralAttributes CATIPolyCurveVertexTangentLayer : public CATIPolyCurveVertexTangentConstLayer
{

public:

  virtual HRESULT Set (int v, const double* a);

  virtual HRESULT Set (int iVertex, const CATMathVector& iTangent) = 0;

protected:

  CATIPolyCurveVertexTangentLayer () {}
  virtual ~CATIPolyCurveVertexTangentLayer () {}

};
