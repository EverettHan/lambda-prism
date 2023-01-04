// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexNNormalsLayer.h
// Header definition of CATPolyMeshVertexNNormalsLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2005 Creation: ndo
//===================================================================
#ifndef CATPolyMeshVertexNNormalsLayer_H
#define CATPolyMeshVertexNNormalsLayer_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexNNormalsLayer.h"
#include "CATIPolyMesh.h"


/*
Implementation class for vertex normal attributes. 
This class defines a layer of normals that can be associated to each vertex of a mesh.
See CATPolySurfaceVertexNNormalsLayer.
*/
class ExportedByPolyMeshImpl CATPolyMeshVertexNNormalsLayer : public CATPolySurfaceVertexNNormalsLayer
{

public:

  /*
   * This method defines a new vertex normal layer on a CATIPolyMesh.
   * It will fails and return 0 if it cannot define a new vertex normal layer as for instance in the cases
   * of memory exhaustion or already defined vertex normal layer.
   * The returned layer must be release by the caller.
   */
  static CATPolySurfaceVertexNNormalsLayer* NewVertexNNormalsLayer (CATIPolyMesh& iMesh);

  /*
   * This method returns the vertex normal layer defined on a CATIPolyMesh.
   * If the method returns S_FALSE, this means that no vertex normal layer (N-normals layer) is defined on
   * the mesh.
   * The returned layer must be release by the caller.
   */
  static HRESULT GetVertexNNormalsLayer (const CATIPolyMesh& iMesh, CATPolySurfaceVertexNNormalsLayer*& oLayer);

public:

  inline CATPolyMeshVertexNNormalsLayer (const CATIPolyMesh& iMesh);

  ~CATPolyMeshVertexNNormalsLayer () {}

};


inline CATPolyMeshVertexNNormalsLayer::CATPolyMeshVertexNNormalsLayer (const CATIPolyMesh& iMesh) :
  CATPolySurfaceVertexNNormalsLayer (iMesh)
{
}

#endif
