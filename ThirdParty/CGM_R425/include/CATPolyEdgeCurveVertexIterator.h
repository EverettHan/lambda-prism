// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdgeCurveVertexIterator
//
//=============================================================================
// Sept 2021 : F1Z : Creation
//=============================================================================

#pragma once

#include "CATPolyEdgeCurveIterator.h"
#include "CATPolyCurveVertexIterator.h"

class CATPolyEdgeCurveVertexIterator
{
public:
  inline CATPolyEdgeCurveVertexIterator(CATPolyEdge* iEdge = 0);
  inline ~CATPolyEdgeCurveVertexIterator();

public:
  inline CATPolyEdgeCurveVertexIterator& Begin(CATPolyEdge* iEdge);
  inline CATPolyEdgeCurveVertexIterator& Begin(CATPolyEdge& iEdge);
  inline bool End() const;
  inline CATPolyEdgeCurveVertexIterator& operator++ ();
  inline int operator*() const;

private:
  CATPolyEdge * _edge;
  CATPolyCurveVertexIterator _iteV;
};

CATPolyEdgeCurveVertexIterator::CATPolyEdgeCurveVertexIterator(CATPolyEdge* iEdge) :
  _edge(iEdge)
{
  Begin(_edge);
}

CATPolyEdgeCurveVertexIterator::~CATPolyEdgeCurveVertexIterator()
{
  _edge = nullptr;
}

CATPolyEdgeCurveVertexIterator& CATPolyEdgeCurveVertexIterator::Begin(CATPolyEdge* iEdge)
{
  if (iEdge)
    Begin(*iEdge);
  else
    _iteV.Begin(NULL);

  return *this;
}

CATPolyEdgeCurveVertexIterator& CATPolyEdgeCurveVertexIterator::Begin(CATPolyEdge& iEdge)
{
  CATIPolyCurve* curve = NULL;
  CATPolyEdgeCurveIterator iteCurve(&iEdge);
  for (; !iteCurve.End() && (curve = iteCurve.GetCurve()) && !curve; ++iteCurve);

  _iteV.Begin(curve);

  return *this;
}

bool CATPolyEdgeCurveVertexIterator::End() const
{
  return !_iteV.End();
}

CATPolyEdgeCurveVertexIterator& CATPolyEdgeCurveVertexIterator::operator++ ()
{
  ++_iteV;
  return *this;
}

int CATPolyEdgeCurveVertexIterator::operator*() const
{
  return *_iteV;
}
