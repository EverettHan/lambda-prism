//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATPolyMeshCheckerObserver
//
//=============================================================================
// 2014-06-27 JXO: New.
//=============================================================================
#ifndef CATPolyMeshCheckerObserver_H
#define CATPolyMeshCheckerObserver_H

#include "PolyBodyTools.h"

// Poly
#include "CATPolyObserver.h"
#include "CATPolyBodyDiagnosis.h"
class CATIPolyMesh;

// System
#include "CATBoolean.h"
#include "CATErrorDef.h"



/**
 * This class performs several consistency checks of the macro-topology and micro-topology of a CATPolyBody.
 */
class ExportedByPolyBodyTools CATPolyMeshCheckerObserver : public CATPolyObserver<CATPolyMeshCheckerObserver>
{

public:

  CATPolyMeshCheckerObserver();
  ~CATPolyMeshCheckerObserver();

public:

  // Error eBadFace_NonManifoldSurface
  virtual void AddNonManifoldBar(const CATIPolyMesh * pmesh, int vertex0, int vertex1) = 0;
  // Error eBadFace_UnreferencedVertices
  virtual void AddUnreferencedVertex(const CATIPolyMesh * pmesh, int unrefvertex) = 0;
  // Error eBadFace_DuplicateTriangles
  virtual void AddDuplicateTriangle(const CATIPolyMesh * pmesh, int triangle, int duplicatetriangle) = 0;
  // Error eBadFace_BadTriangles
  virtual void AddBadTriangle(const CATIPolyMesh * pmesh, int badtriangle) = 0;
  // Error eBadFace_DegenerateTriangles
  virtual void AddDegenerateTriangle(const CATIPolyMesh * pmesh, int badtriangle) = 0;

};


#endif // !CATPolyMeshCheckerObserver_H
