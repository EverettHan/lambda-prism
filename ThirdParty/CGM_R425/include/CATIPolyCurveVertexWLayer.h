//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of per-curve-vertex W parameter interface
//
//=============================================================================
// 2007-07-04   BPG: New.
//=============================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyCurveVertexWConstLayer.h"


class ExportedByPolyhedralAttributes CATIPolyCurveVertexWLayer : public CATIPolyCurveVertexWConstLayer
{

public:

  //virtual HRESULT Set (int v, const double* a) { return Set (v, *a); }
  virtual HRESULT Set (int v, const double* a);
  virtual HRESULT Set (int iVertex, double w) = 0;

protected:

  CATIPolyCurveVertexWLayer () {}
  virtual ~CATIPolyCurveVertexWLayer () {}

};
