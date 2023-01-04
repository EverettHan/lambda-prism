// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshManifoldFaceIterator.h
// Header definition of CATPolyMeshManifoldFaceIterator
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// August 2008 Creation: ndo
//===================================================================
#ifndef CATPolyMeshManifoldFaceIterator_H
#define CATPolyMeshManifoldFaceIterator_H

#include "PolyMeshImpl.h"
#include "CATErrorDef.h"     // HRESULT definition (for compil under UNIX)
#include "CATPolyBitSet.h"
#include "CATIPolyMeshTriangleIterator.h"
#include "CATAssert.h"

class CATIPolyMesh;
class CATPolySurfaceFacetSupportLayer;

class PolyMeshManifoldFaceTriangleIteratorData;


/**
* Iterator of manifold faces from a CATIPolyMesh.
* The iterator cycles though a series of CATIPolyMeshTriangleIterator's which each represents a 
* two-manifold and connected subset of the CATIPolyMesh.  An optional support layer can be provided
* to segment further the connected subsets according to their support.
*/
class ExportedByPolyMeshImpl CATPolyMeshManifoldFaceIterator 
{

public:

  CATPolyMeshManifoldFaceIterator (const CATIPolyMesh& iMesh,
                                   const CATPolySurfaceFacetSupportLayer* iSupportLayer = 0);

  ~CATPolyMeshManifoldFaceIterator ();

public:

  inline CATBoolean End () const;
  CATPolyMeshManifoldFaceIterator& operator++ ();  // Increment the iterator to the next Manifold Face.

  // Return an iterator to cycle through all the triangles of a two-manifold subset of the mesh.
  CATIPolyMeshTriangleIterator* Get () const;

private:

  CATIPolyMeshTriangleIterator* _TriangleIterator;
  PolyMeshManifoldFaceTriangleIteratorData* _Data;

  CATPolyBitSet _TriangleVisited;

};

inline CATBoolean CATPolyMeshManifoldFaceIterator::End () const
{
  return _Data == 0 ? TRUE : FALSE;
}

#endif
