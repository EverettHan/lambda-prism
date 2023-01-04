// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNonManifoldEdgeOptimizer.h
//
//===================================================================
//
// Usage notes:
// 
// Optimize the connection between manifold edges (alpha 2 link)
// from the vertex information.
//
//===================================================================
// 2022-04 F1Z : New
//===================================================================
#pragma once

// PolyhedralMathematics
#include "Poly/Set.h"

// PolyhedralObjects
#include "PolyBodyTools.h"
#include "CATPolyBody.h"
#include "CATPolyVertex.h"
#include "CATPolyPseudoManifoldVertex.h"
#include "CATCompareElements.h"

// std
#include <memory>
#include <set>

class ExportedByPolyBodyTools CATPolyBodyNonManifoldEdgeOptimizer
{
public:
  CATPolyBodyNonManifoldEdgeOptimizer();
  ~CATPolyBodyNonManifoldEdgeOptimizer();

  HRESULT Run(CATPolyBody & ioBody);

private:
  bool IsConnectingManifoldEdge(CATPolyVertex * iV);
  HRESULT ConnectManifoldEdges(CATPolyBody & ioBody,
                               CATPolyVertex * iV);
  HRESULT ConnectManifoldEdge(CATPolyBody & ioBody,
                              CATPolyPseudoManifoldVertex & iPMV);
private:
  class PriorityVertexComparator
  {
  public:
    PriorityVertexComparator() {};
    bool operator()(const CATPolyVertex * iV0, const CATPolyVertex * iV1) const;
  };
  std::set<CATPolyVertex *, PriorityVertexComparator> _vertices;
};
