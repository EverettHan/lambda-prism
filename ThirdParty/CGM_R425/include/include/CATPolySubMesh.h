//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySubMesh.h
//
//=============================================================================
// 2008-10-22   ZFI: New
// 2010-03-25   NDO: Revisit
// 2014-12-10   NDO: Revisit surface vertex cell layer, optimizations.
//=============================================================================
#ifndef CATPolySubMesh_H
#define CATPolySubMesh_H

#include "PolyMeshImpl.h"
#include "CATPolyMeshBase.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATSetOfInt.h"

class CATPolyLayerContainer;
class CATIPolySurfaceVertexFacetNeighborhood;


/**
Class representing a sub-mesh.
A sub-mesh refers to a subset of triangles from a parent CATIPolyMesh.
Vertices and triangles from a parent mesh can be added or removed from a sub-mesh.
Edition of the sub-mesh geometry results in changes of the parent mesh.
*/
class ExportedByPolyMeshImpl CATPolySubMesh : public CATPolyMeshBase
{

public:

  /**
   * Construction of sub-mesh from a parent mesh.
   */
  static CATPolySubMesh* New (CATIPolyMesh& iBaseMesh);

  /**
   * Construction of sub-mesh from a parent mesh.
   */
  static CATPolySubMesh* New (CATIPolyMesh* iBaseMesh);

  ~CATPolySubMesh ();

public:

/** @name Methods specific to sub-meshes.
    @{ */

  /**
   * Returns the parent mesh.
   */
  inline const CATIPolyMesh& GetParentMesh () const;

  /**
   * Adds a vertex from the parent-mesh to the sub-mesh.
   */
  //HRESULT AddParentVertex (const int iIdxVertex);

  /**
   * Adds a triangle from the parent-mesh to the sub-mesh.
   * When adding a triangle to a sub-mesh, the vertices of the triangle are automatially added to the sub-mesh.
   */
  HRESULT AddParentTriangle (const int iIdxTriangle);
  
  /**
   * Removes a vertex from the sub-mesh.
   */
  //HRESULT RemoveParentVertex (const int iIdxVertex);

  /**
   * Removes a triangle from the sub-mesh.
   */
  HRESULT RemoveParentTriangle (const int iIdxTriangle);
  
  /** 
   * Returns <tt>TRUE</tt> when a triangle from the parent mesh belongs to the sub-mesh.
   */
  CATBoolean IsParentTriangleIn (const int iIdxTriangle) const;

  /**
   * Removes all vertices and triangles from the sub-mesh.
   */
  HRESULT Empty ();

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolySurface as a const CATIPolySubMesh.
   */
  static const CATPolySubMesh* Cast (const CATIPolySurface* iSurface);

  /**
   * Casts a CATIPolySurface as a CATIPolySubMesh.
   */
  static CATPolySubMesh* Cast (CATIPolySurface* iSurface);

/** @} */

/**
* Returns <tt>TRUE</tt> when a vertex from the parent mesh belongs to the sub-mesh.  Warning: this is O(N) where N=number of triangles in the mesh.
*/
	CATBoolean IsParentVertexIn(const int iIdxVertex) const;

private:

  CATIPolyMesh& _BaseMesh;
  mutable CATSetOfInt _VertexSet;	// modified lazily.  This info is stale if the set is empty.
  CATSetOfInt _TriangleSet;

  // A flag set to true if the sub-mesh layers include all base-mesh layers. Default is true.
  // If set to false, then base-mesh layers are excluded;  
  // Sharing of layers between base-mesh and sub-mesh is possible by simple addition of the base-mesh layer
  // to the sub-mesh.
  bool _IncludeBaseMeshLayers;  

  CATPolyLayerContainer* _Layers;  // Layers associated to sub-mesh.
  CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;  // Cache.

  void EnsureVertexSetValid () const; // only modifies mutable data.
  void InvalidateVertexSet () const;

public:

/** @name Virtual methods from base classes.
    @{ */

  int GetNbVertices () const;

  HRESULT AddVertex (int &v);
  HRESULT AddVertex (const CATMathPoint &iPoint, int &oIdxVertex); // Not allowed on a sub-mesh.
  HRESULT RemoveVertex (const int iIdxVertex); // Not implemented.

/** @} */

public:

  int GetNbFacets () const;
  int GetNbTriangles () const;

  HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3]) const ;

  HRESULT AddTriangle (const int  iIdxVertices[3], int &oIdxTriangle); // Not allowed on a sub-mesh.
  HRESULT RemoveTriangle (const int iIdxTriangle, const CATBoolean iRemoveUnreferencedVertices = FALSE); // Not implemented.

public:

/** @name Virtual methods from base classes.  Iterators.
    @{ */

  HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator*& oIterator) const; 

  HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

  HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator*& oIterator) const ;
  HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator*& oIterator) const ;

/** @} */

public:

/** @name Virtual methods from base classes.  Data extensions.
    @{ */

  HRESULT GetVertexPositionLayer(CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexPositionLayer(CATIPolySurfaceVertexPositionLayer *&oLayer);
  HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalLayer *&oLayer);
  HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVLayer *&oLayer);
  HRESULT GetVertexTextureCoordLayer(CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;
  HRESULT GetVertexTextureCoordLayer(CATIPolySurfaceVertexTextureCoordLayer *&oLayer);
  HRESULT GetOrientedBarTangentLayer(CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const;
  HRESULT GetOrientedBarTangentLayer(CATIPolySurfaceOrientedBarTangentLayer *&oLayer);

  /**
   * @param oNeighborhood [out, IUnknown#Release] 
   */
  HRESULT GetVertexFacetNeighborhood(CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  /**
   * @param oSupport [out, IUnknown#Release]
   */
  HRESULT GetSupport (CATIPolySurfaceSupport*& oSupport) const;

  CATIPolySurfaceConstTools* GetConstTools () const;
  CATIPolySurfaceTools* GetTools ();

  HRESULT GetBoundingBox (CATMathBox &oBBox) const ;

/** @} */

public:

  /** @name Data Layers
  @{ */

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolySurfaceObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  /**
  * @param oLayer [out, IUnknown#Release]
  */
  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  */
  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  * Exclusive layers are the layers that were added to the sub-mesh.
  * Otherwise the layers may include parents layers.
  */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator, bool exclusiveLayers) const;

  /** @} */

public:

  // Event listener.

  //HRESULT RegisterObserver (CATIPolySurfaceObserver& iObserver);
  //HRESULT UnregisterObserver (CATIPolySurfaceObserver& iObserver);

public:

  // Visitors.

  HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;
  HRESULT Accept (CATIPolySurface& iS, CATPolySurfaceVisitor& iV);

public:

  // Overridden from CATPolyMeshBase.

  HRESULT FlipBar (const int iIdxVertex1, const int iIdxVertex2);
  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);

public:

  // Don't use these methods. Use instead layers, iterators, neighborhoods and tools.

  HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const ;

	// Warning this is potentially O(N) where N is the number of triangles in the submesh.  Don't use it.
  CATBoolean IsVertexDefined (const int iIdxVertex) const;
	// Warning this is potentially O(N) where N is the number of triangles in the submesh.  Don't use it.
	CATBoolean IsVertexReferenced (const int iIdxVertex) const ;
  int GetMinVertexIndex () const;
  int GetMaxVertexIndex () const;

  CATBoolean IsTriangleDefined(const int iIdxTriangle) const  ;
  int GetMinTriangleIndex() const ;
  int GetMaxTriangleIndex() const ;

  //CATBoolean IsHoleVertex (const int iIdxVertex) const;

  CATBoolean IsBarValid (const int iIdxVertex1,
                         const int iIdxVertex2) const ;
  //CATBoolean IsHoleBar (const int iIdxVertex0, const int iIdxVertex1) const;



  HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3], int oIdxTriangles[3]) const ;

	// Warning this is potentially O(N) where N is the number of triangles in the submesh.  Don't use it.
	HRESULT GetVertexNeighborsOfVertex(const int     iIdxVertex,
                                             CATListOfInt &ioIdxVertices) const ;
	// Warning this is potentially O(N) where N is the number of triangles in the submesh.  Don't use it.
  HRESULT GetTriangleNeighborsOfVertex(const int     iIdxVertex,
                                               CATListOfInt &ioIdxTriangles) const ;
	// Warning this is potentially O(N) where N is the number of triangles in the submesh.  Don't use it.
	HRESULT GetTriangleNeighborsOfBar(const int  iIdxVertex1,
                                            const int  iIdxVertex2,
                                            int       &oIdxTriangle1,
                                            int       &oIdxTriangle2) const ;
  HRESULT GetTriangleNeighborsOfBar(const int     iIdxVertex1,
                                            const int     iIdxVertex2,
                                            CATListOfInt &ioIdxTriangles) const ;
  HRESULT GetTriangleNeighborsOfTriangle(const int iIdxTriangle,
                                                 int       oIdxNeighborTriangles[3]) const ;

  HRESULT GetBar(const int iIdxTriangle0, const int iIdxTriangle1, int & oIdxVertex0, int & oIdxVertex1, int & oNbBars) const ;

  HRESULT GetFacet (const int f, CATListOfInt &oVertices) const;

  HRESULT GetTrianglePoints (const int iIdxTriangle,
                             CATMathPoint& oPoint1, 
                             CATMathPoint& oPoint2, 
                             CATMathPoint& oPoint3) const ;

private: 

  // Private constructor.
  CATPolySubMesh (CATIPolyMesh& iBaseMesh, bool includeBaseMeshLayers = true); 

};


inline const CATIPolyMesh& CATPolySubMesh::GetParentMesh () const
{
  return _BaseMesh;
}


#endif // !CATPolySubMesh_H
