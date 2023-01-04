// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexNNormalsLayerMeshObserver.h
//
//===================================================================
// February 2008 Creation: ndo
//===================================================================
#ifndef CATPolyMeshVertexNNormalsLayerMeshObserver_H
#define CATPolyMeshVertexNNormalsLayerMeshObserver_H

#include "PolyMeshImpl.h"
#include "CATIPolyMeshObserver.h"
#include "CATErrorDef.h"     // HRESULT definition (for compil under UNIX)

class CATIPolyMesh;
class CATPolyMeshVertexNNormalsLayer;


/**
* Class observing mesh events to update a vertex normals layer. 
*/
class ExportedByPolyMeshImpl CATPolyMeshVertexNNormalsLayerMeshObserver : public CATIPolyMeshObserver
{

public:

  CATPolyMeshVertexNNormalsLayerMeshObserver (const CATIPolyMesh& iObservedMesh, 
                                              CATPolyMeshVertexNNormalsLayer& iNormalLayer);

  virtual ~CATPolyMeshVertexNNormalsLayerMeshObserver ();

public:

  HRESULT PrepareToMergeVertices (int v0, int v1);

private:

  const CATIPolyMesh& _Mesh;
  CATPolyMeshVertexNNormalsLayer& _NormalLayer;

};

#endif
