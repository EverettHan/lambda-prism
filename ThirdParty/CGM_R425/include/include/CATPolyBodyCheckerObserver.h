//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATPolyBodyCheckerObserver
//
// Check topological consistency of a macro polyhedral body
//
//=============================================================================
// 2014-06-25 JXO: New.
//=============================================================================
#ifndef CATPolyBodyCheckerObserver_H
#define CATPolyBodyCheckerObserver_H

#include "PolyBodyTools.h"

// Poly
#include "CATPolyObserver.h"
#include "CATPolyBodyDiagnosis.h"
class CATPolyVertex;
class CATPolyEdge;
class CATIPolyCurve;
class CATPolyFace;
class CATIPolyMesh;

// System
#include "CATBoolean.h"
#include "CATErrorDef.h"



/**
 * This class logs several consistency checks of the macro-topology and micro-topology of a CATPolyBody.
 */
class ExportedByPolyBodyTools CATPolyBodyCheckerObserver : public CATPolyObserver<CATPolyBodyCheckerObserver>
{

public:

  CATPolyBodyCheckerObserver();
  ~CATPolyBodyCheckerObserver();

public:
  // Errors eBadVertex_OnEdge and eBadEdge_OnVertex
  virtual void AddBadVertexOnEdge(CATPolyEdge * edge, int vertexonedge, CATPolyVertex * vertex) = 0;
  // Error eBadEdge_NonMatchingGeometry
  virtual void AddNonMatchingGeometryVertex(CATPolyEdge * edge, const CATIPolyCurve * pcurve, int vertexonedge) = 0;
  // Error eBadEdge_NoVertexPosition
  virtual void AddNoVertexPositionVertex(CATPolyEdge * edge, const CATIPolyCurve * pcurve, int vertexonedge) = 0;
  // Error eBadEdge_InvalidSurfaceVertex
  virtual void AddInvalidSurfaceVertex(CATPolyEdge * edge, const CATIPolyCurve * pcurve, int vertexonedge) = 0;
  // Error eBadEdge_SelfIntersecting
  virtual void AddSelfIntersectingVertex(CATPolyEdge * edge, int vertexonedge) = 0;

  // Error eBadFace_NonManifoldSurface
  virtual void AddNonManifoldBar(CATPolyFace * face, const CATIPolyMesh * pmesh, int vertex0, int vertex1) = 0;
  // Error eBadFace_BadTriangles
  virtual void AddBadTriangle(CATPolyFace * face, const CATIPolyMesh * pmesh, int badtriangle) = 0;
  // Error eBadFace_UnreferencedVertices
  virtual void AddUnreferencedVertex(CATPolyFace * face, const CATIPolyMesh * pmesh, int unrefvertex) = 0;
  // Error eBadFace_DuplicateTriangles
  virtual void AddDuplicateTriangle(CATPolyFace * face, const CATIPolyMesh * pmesh, int triangle, int duplicatetriangle) = 0;

};


#endif // !CATPolyBodyCheckerObserver_H
