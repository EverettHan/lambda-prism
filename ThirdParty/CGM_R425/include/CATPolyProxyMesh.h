//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATPolyProxyMesh.h
//
//=============================================================================
// 2008-10-22   JXO: New, from CATPolySubMesh
//=============================================================================
#ifndef CATPolyProxyMesh_H
#define CATPolyProxyMesh_H

#include "PolyMeshImpl.h"
#include "CATPolyMeshBaseConst.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATPolyLayerContainer;


/**
 * Class representing a mesh with a (possible) different orientation.
 * A proxy-mesh refers to a parent CATIPolyMesh and an orientation flag.
 * Note that currently, edition of the proxy-mesh geometry results in changes of the parent mesh.
 * Default orientation is same as the parent mesh.
 */
class ExportedByPolyMeshImpl CATPolyProxyMesh : public CATPolyMeshBaseConst
{

public:

  /**
   * Construction of proxy-mesh from a parent mesh.
   */
  static CATPolyProxyMesh* New (CATIPolyMesh& iBaseMesh);

  /**
   * Construction of proxy-mesh from a parent mesh.
   */
  static CATPolyProxyMesh* New (CATIPolyMesh* iBaseMesh);

  ~CATPolyProxyMesh ();

public:

/** @name Methods specific to proxy-meshes.
    @{ */

  /**
   * Returns the parent mesh.
   */
  inline const CATIPolyMesh& GetParentMesh () const;

  /** 
   * Set the orientation of the proxy-mesh with regard to the parent mesh.
   * @param iSameAsParentMesh
   *         TRUE same orientation as the parent mesh. Basically the meshes are identical.
   *         FALSE the proxy mesh has an orientation opposite to the parent mesh. Triangles are flipped.
   * @param iAlsoFlipVertexNormals
   *         TRUE if triangles are flipped, then vertices normals are also inverted.
   *         FALSE normals are not changed.
   */
  inline void SetOrientation(CATBoolean iSameAsParentMesh, CATBoolean iAlsoFlipVertexNormals = TRUE);

  /** 
   * Get the orientation of the proxy-mesh with regard to the parent mesh.
   * @return
   *         TRUE same orientation as the parent mesh. Basically the meshes are identical.
   *         FALSE the proxy mesh has an orientation opposite to the parent mesh. Triangles are flipped. Default is to also invert the vertices normals.
   */
  inline CATBoolean GetOrientation() const;

  /** 
   * Get the orientation of the normals
   */
  inline CATBoolean AreNormalsAlsoInverted() const;

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolySurface as a const CATPolyProxyMesh.
   */
  static const CATPolyProxyMesh* Cast (const CATIPolySurface* iSurface);

  /**
   * Casts a CATIPolySurface as a CATPolyProxyMesh.
   */
  static CATPolyProxyMesh* Cast (CATIPolySurface* iSurface);

/** @} */

private:

  CATIPolyMesh& m_BaseMesh;
  bool m_Orientation;
  bool m_AlsoFlipVertexNormals;
  bool m_IncludeBaseMeshLayers;

  CATPolyLayerContainer* _Layers;  // Layers associated to the proxy-mesh.

public:

/** @name Virtual methods from base classes.
    @{ */

  int GetNbVertices () const;

/** @} */

public:

  int GetNbFacets () const;
  int GetNbTriangles () const;

  HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3]) const ;

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
  HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  HRESULT GetVertexTextureCoordLayer(CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;
  HRESULT GetOrientedBarTangentLayer(CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const;
  /**
   * @param oNeighborhood [out, IUnknown#Release] 
   */
  HRESULT GetVertexFacetNeighborhood(CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  HRESULT GetSupport (CATIPolySurfaceSupport*& oSupport) const;

  CATIPolySurfaceConstTools* GetConstTools () const;

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
  * Exclusive layers are the layers that were added to the proxy-mesh.
  * Otherwise the layers may include parents layers.
  */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator, bool exclusiveLayers) const;

/** @} */

public:

  // Visitors.
  HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;

public:

  // Don't use these methods. Use instead layers, iterators, neighborhoods and tools.

  HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const ;

  int GetMinVertexIndex () const;  // Deprecated.
  int GetMaxVertexIndex () const;  // Deprecated.
  int GetMinTriangleIndex () const;  // Deprecated.
  int GetMaxTriangleIndex () const;  // Deprecated.

private: 

  // Private constructor.
  CATPolyProxyMesh (CATIPolyMesh& iBaseMesh, bool includeBaseMeshLayers = true);

};


inline const CATIPolyMesh& CATPolyProxyMesh::GetParentMesh () const
{
  return m_BaseMesh;
}

inline void CATPolyProxyMesh::SetOrientation(CATBoolean iSameAsParentMesh, CATBoolean iAlsoFlipVertexNormals)
{
  m_Orientation = iSameAsParentMesh;
  m_AlsoFlipVertexNormals = iAlsoFlipVertexNormals;
}

inline CATBoolean CATPolyProxyMesh::GetOrientation() const
{
  return m_Orientation ? TRUE : FALSE;
}

inline CATBoolean CATPolyProxyMesh::AreNormalsAlsoInverted() const
{
  return m_AlsoFlipVertexNormals ? TRUE : FALSE;
}

#endif // !CATPolyProxyMesh_H
