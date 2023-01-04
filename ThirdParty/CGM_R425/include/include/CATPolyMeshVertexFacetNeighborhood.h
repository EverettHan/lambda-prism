// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexFacetNeighborhood.h
//
//===================================================================
//
// February 2009  Creation: MNA
//===================================================================
#ifndef CATPolyMeshVertexFacetNeighborhood_H
#define CATPolyMeshVertexFacetNeighborhood_H

#include "PolyMeshImpl.h"
#include "CATIPolySurfaceVertexFacetNeighborhood.h"
#include "CATMapOfIntToInt.h"

class CATIPolyMesh;
class CATIPolySurfaceFacetIterator;


/*
* Computes the neighborhood of the vertices of a mesh (CATIPolyMesh) and provides the access
* the neighbor vertices and facets of a vertex.
* This class is used when the neighborhood of the vertices is not explicitly known.
* Note that there is currently no observers associated to the neighborhood.  Therefore, if the mesh
* is modified, the neighborhood is not updated; it must be recomputed (inefficient.)
*/
class ExportedByPolyMeshImpl CATPolyMeshVertexFacetNeighborhood : public CATIPolySurfaceVertexFacetNeighborhood
{

public: // Final class

  CATPolyMeshVertexFacetNeighborhood (const CATIPolyMesh& iPolyMesh);
  CATPolyMeshVertexFacetNeighborhood (const CATIPolyMesh& iPolyMesh, bool iKeepReferenceFacetIterator);
  
  virtual ~CATPolyMeshVertexFacetNeighborhood ();

public:

  HRESULT GetFacetNeighborsOfVertex (const int v, CATListOfInt& oFacets)  const;
  HRESULT GetFacetNeighborsOfFacet (const int f, CATListOfInt& oFacets)    const;
  HRESULT GetVertexNeighborsOfVertex (const int v, CATListOfInt& oVertices) const;

public:

  CATBoolean IsBar (const int v0, const int v1) const;
  CATBoolean IsVertexManifold (const int v) const;
  CATBoolean IsBarManifold (const int v0, const int v1) const;
  CATBoolean IsBoundaryVertex (const int v) const;
  CATBoolean IsBoundaryBar (const int v0, const int v1) const;

public:

  // Return the size in bytes of the vertex facet neighborhood layer.
  unsigned int SizeOf () const;

private:

  const CATIPolyMesh& _PolyMesh;
  CATIPolySurfaceFacetIterator* _FacetIterator;

  // Associate to each vertex a set of facets to which the vertex belongs.
  // This is a contiguous array of set of facets for all vertices.
  int* _Facets;

  // Associate to a vertex an offset into _Facets where the list of facets for that vertex begins.
  CATMapOfIntToInt _VertexToFacetOffet;

private:

  HRESULT Initialize (bool iKeepReferenceFacetIterator=true);
};


#endif // !CATPolyMeshVertexFacetNeighborhood_H
