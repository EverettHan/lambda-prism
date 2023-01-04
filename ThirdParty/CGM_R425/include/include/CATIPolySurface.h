//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Polyhedral surface interface
//
//=============================================================================
// 2007-06-14   BPG: New
// 2008-09-04   ZFI: Texture Coords Layer
// 2009-11-02   NDO: Replace CATBaseUnknown by CATPolyRefCounted.
//=============================================================================
#ifndef CATIPolySurface_H
#define CATIPolySurface_H

#include "PolyhedralModel.h"
#include "CATIPolyObject.h"
#include "CATListOfInt.h"
#include "CATErrorDef.h"
#include "CATPolyDeprecated.h"

// Subclasses.
class CATIPolyMesh;
class CATIPolyTriQuadMesh;

// Iterators.
class CATIPolySurfaceVertexIterator;
class CATIPolySurfaceFacetIterator;

// Layers, Neighborhoods, Supports.
class CATIPolySurfaceVertexFacetNeighborhood;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolySurfaceVertexPositionLayer;
class CATIPolySurfaceVertexNormalConstLayer;
class CATIPolySurfaceVertexNormalLayer;
class CATIPolySurfaceVertexUVConstLayer;
class CATIPolySurfaceVertexUVLayer;
class CATIPolySurfaceVertexTextureCoordConstLayer;
class CATIPolySurfaceVertexTextureCoordLayer;
class CATIPolySurfaceVertexCellConstLayer;
class CATIPolySurfaceVertexCellLayer;
class CATIPolySurfaceOrientedBarTangentConstLayer;
class CATIPolySurfaceOrientedBarTangentLayer;
class CATIPolySurfaceSupport;
class CATIPolyLayer;
class CATIPolyLayerIterator;

// Tools.
class CATIPolySurfaceConstTools;
class CATIPolySurfaceTools;

// Observer.
class CATIPolySurfaceObserver;

// Extensions.
class CATPolySurfaceConstVisitor;
class CATPolySurfaceVisitor;


/**
* Interface to a polyhedral surface.
*
* A polyhedral surface is a surface represented by vertices, facets, layers and support.
* It consists of:
*   - Iterators to cycle through the vertices and facets.
*   - Layers that store some properties about the vertices, facets or the surface.
*   - Neighborhoods that provide the links between the vertices and the facets.
*   - A surface support that provide additional information about the geometry of the surface.
*
* The discrete data (vertices and facets) are referenced by integer indices.
*
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolySurface : public CATIPolyObject
{

public:

/** @name Downcasters
    @{ */

  inline static const CATIPolySurface* Cast (const CATIPolyObject&);

  inline static CATIPolySurface* Cast (CATIPolyObject&);

  inline static const CATIPolySurface* Cast (const CATIPolyObject*);

  inline static CATIPolySurface* Cast (CATIPolyObject*);

/** @} */

public:

/** @name Vertex Services and Iterators
    @{ */

  /**
    * Returns the number of vertices of the polyhedral surface.
    * @return
    *   The number of vertices of the discrete surface.
    */
  virtual int GetNbVertices () const = 0;

  /**
   * Returns a vertex iterator (explicit).
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const = 0;

/** @} */

public:

/** @name Vertex and Facet Neighborhoods
    @{ */

  /**
    * Returns the vertex facet neighborhood.
    * The neighborhood layer associates to each vertex the facets that refer to it.
    * @param oNeighborhood
    *   The neighborhood layer.
    * @return
    *   S_OK if a neighborhood is available.
    *   S_FALSE if no neighborhood is available.
    *   E_FAIL or another error otherwise.
    */
  virtual HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const = 0;

/** @} */

public:

/** @name Vertex Events
    @{ */

  /**
    * Adds a vertex to the surface.
    * @param v
    *   The index of the added vertex.
    * @return
    *   <ul>
    *     <li> <code> S_OK </code> on success.
    *     <li> <code> E_FAIL </code> otherwise.
    *   </ul>
    */
  virtual HRESULT AddVertex (int &v) = 0;

  /**
   * Removes a vertex from the surface.
   * @param v
   *   The index of the vertex to remove.
   * @return
   *   <ul>
   *     <li> <code> S_OK </code> on success.
   *     <li> <code> E_FAIL </code> otherwise.
   *   </ul>
   */
  virtual HRESULT RemoveVertex (const int v) = 0;

  /**
   * Splits the bar connecting two vertices by a new vertex.
   * <br>
   *
   * <pre>
   *
   *   Before:   v0----------v1
   *
   *   After:    v0----n-----v1
   *
   * </pre>
   *
   * @param v0
   *   The input index of the first vertex.
   * @param v1
   *   The input index of the second vertex.
   * @param n
   *   The output index of the new vertex.
   * @return
   *   <ul>
   *     <li> <code> S_OK </code> on success.
   *     <li> <code> E_FAIL </code> otherwise.
   *   </ul>
   */
  virtual HRESULT SplitBar (const int v0, const int v1, int &n) = 0;

  /**
   * Merges the vertices by collapsing the bar between them
   * and replaces the second vertex v1 by the first vertex v0.
   * The second vertex, v1 is not removed from the surface.
   * <br>
   *
   * <pre>
   *
   *   Before:  v2------v0-------v1------v3
   *
   *   After:   v2------v0---------------v3
   *
   * </pre>
   *
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> otherwise.
   * </ul>
   */
  virtual HRESULT MergeVertices (const int v0, const int v1) = 0;

/** @} */

public:

/** @name Vertex Layers
    @{ */

  /**
    * Returns the vertex position layer if any.
    * @param oLayer
    *   The ouput layer.  The returned layer must be released (ref-counted.)
    * @return
    *   S_OK if a layer is successfully returned.
    *   S_FALSE if a layer is not available.
    *   E_FAIL if an error occurs.
    */
  virtual HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer *&oLayer) const = 0;

  /**
   * Returns the vertex position layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer *&oLayer) = 0;

  /**
   * Returns the vertex normal layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const = 0;

  /**
   * Returns the vertex normal layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer *&oLayer) = 0;

  /**
   * Returns the vertex UV layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const = 0;

  /**
   * Returns the vertex UV layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVLayer *&oLayer) = 0;

  /**
   * @nodoc
   * Returns the vertex texture coordinate layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const = 0;

  /**
   * @nodoc
   * Returns the vertex texture coordinate layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordLayer *&oLayer) = 0;

  /**
   * @nodoc
   * Returns the oriented bar tangent layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const = 0;

  /**
   * @nodoc
   * Returns the oriented bar tangent layer if any.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentLayer *&oLayer) = 0;

/** @} */

public:

/** @name Data Layers
    @{ */

  /**
   * Adds a layer to the object.
   * @param iLayer
   *  The layer to be added to the object.
   * @param obs
   *  An optional observer to register with the CATIPolySurface for update of the layer during 
   *  editing events.  When the observer is registered explicitely with the layer, it will be
   *  unregistered when the layer is removed from the object.
   */
  virtual HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolySurfaceObserver* obs = 0) = 0;

  /**
   * Removes a layer from the object.  It will also unregister the observer registered 
   * when the layer was added.
   */
  virtual HRESULT RemoveLayer (CATIPolyLayer& iLayer) = 0;

  /**
   * Gets a specific layer given its class id. 
   * If several layers of identical class ids are associated to the object, 
   * then the method returns the most recently added to the object.
   */
  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const = 0;

  /**
   * Returns true if a layer of given id is attached to the surface.
   */
  virtual bool HasLayer (const CLSID& id) const = 0;

  /**
   * Returns an iterator through all the layers of type CATIPolyLayer
   * matching a specific class id.
   */
  virtual HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const = 0;

  /**
   * Returns an iterator through all the layers of type CATIPolyLayer.
   */
  virtual HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const = 0;

/** @} */

public:

/** @name Surface Support
    @{ */

  /**
    * Returns the underlying surface support, if any.
    * @param oSupport
    *   The surface support.  The returned support must be released (ref-counted.)
    * <ul>
    *   <li> <tt>S_OK</tt> if a support is successfully returned.
    *   <li> <tt>S_FALSE</tt> if a support is not available.
    *   <li> <tt>E_FAIL</tt> if an error occurs.
    * </ul>
    */
  virtual HRESULT GetSupport (CATIPolySurfaceSupport*& oSupport) const = 0;

  /**
   * Sets the underlying surface support.
   * @param iSupport
   *   A pointer to the surface support.  The method calls AddRef on the support.
   *   Any previous support owned by the object will be released.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a support is successfully set.
   *   <li> <tt>S_FALSE</tt> if a support cannot be set.
   *   <li> <tt>E_FAIL</tt> otherwise.
   * </ul>
   */
  virtual HRESULT SetSupport (CATIPolySurfaceSupport* iSupport) = 0;

/** @} */

public:

/** @name Facet Services and Iterators
    @{ */

  /**
    * Returns the number of facets.
    */
  virtual int GetNbFacets () const = 0;

  /**
   * Returns the maximal number of vertices a facet can have in this surface.
   * @return
   *   The maximum number of vertices per facet allowed.
   */
  virtual int GetMaxFacetSize () const = 0;

  /**
   * Returns a facet iterator.
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   */
  virtual HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const = 0;

public:

  /**
   * @nodoc
   */
  virtual HRESULT GetFacet (const int f, CATListOfInt &oVertices) const = 0;

/** @} */

public:

/** @name Observers
    Observers are event listeners used to update attributes (user-defined layers.)
    @{ */

  /**
    * Registers an observer (event listener) with the instance.
    * @param iObserver
    *   The observer that is registered with the instance.
    * @return
    * <ul>
    *   <li> <tt>S_OK</tt> if the observer is successfully registered with the surface.
    * </ul>
    */
  virtual HRESULT RegisterObserver (CATIPolySurfaceObserver& iObserver) = 0;

  /**
   * Unregisters an observer (event listener) with the instance.
   * @param iObserver
   *   The observer that is unregistered with the instance.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the observer is successfully unregistered with the surface.
   * </ul>
   */
  virtual HRESULT UnregisterObserver (CATIPolySurfaceObserver& iObserver) = 0;

/** @} */

public:

/** @name Visitors
    Access to concrete types.
    @{ */

  /**
   * Accepts a const visitor for access to the concrete surface type.
   * @return
   *   The status of the application of the visitor.
   */
  virtual HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const = 0;

  /**
   * Accepts a visitor for access to the concrete surface type.
   * @return
   *   The status of the application of the visitor.
   */
  virtual HRESULT Accept (CATIPolySurface &iS, CATPolySurfaceVisitor& iV) = 0;

/** @} */

public:

/** @name Reserved Services
    Do not use in frameworks other than in PolyhedralInterfaces and PolyhedralObjects.
    @{ */

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolySurfaceConstTools* GetConstTools () const = 0;

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolySurfaceTools* GetTools () = 0;

/** @} */

public:

  /**
   * @nodoc
   * @deprecated
  */
  POLY_DEPRECATED ("Do not call GetVertexCellLayer.  Call instead CATPolyFace::GetSurfaceVertexCellLayer.",
  virtual HRESULT GetVertexCellLayer (CATIPolySurfaceVertexCellConstLayer *&oLayer) const);

  /**
   * @nodoc
   * @deprecated
   */
  POLY_DEPRECATED ("Do not call GetVertexCellLayer.  Call instead CATPolyFace::GetSurfaceVertexCellLayer.",
  virtual HRESULT GetVertexCellLayer (CATIPolySurfaceVertexCellLayer *&oLayer));

protected:

  /**
   * @nodoc
   * Temporary method until complete removal of GetVertexCellLayer.
   */
  virtual HRESULT DummyGetVertexCellLayer (CATIPolySurfaceVertexCellConstLayer *&oLayer) const;

  /**
   * @nodoc
   * Temporary method until complete removal of GetVertexCellLayer.
   */
  virtual HRESULT DummyGetVertexCellLayer (CATIPolySurfaceVertexCellLayer *&oLayer);

public:

  virtual ~CATIPolySurface () {}

public:

  const CATIPolySurface* CastToPolySurface () const { return this; }
  CATIPolySurface* CastToPolySurface () { return this; }

public:

  /**
   * Casts a const CATIPolySurface as a const CATIPolyMesh.
   */
  virtual const CATIPolyMesh* CastToTriMesh () const { return 0; }

  /**
   * Casts a CATIPolySurface as a CATIPolyMesh.
   */
  virtual CATIPolyMesh* CastToTriMesh () { return 0; }

  /**
   * Casts a const CATIPolySurface as a const CATIPolyTriQuadMesh.
   */
  virtual const CATIPolyTriQuadMesh* CastToTriQuadMesh () const { return 0; }

  /**
   * Casts a CATIPolySurface as a CATIPolyTriQuadMesh.
   */
  virtual CATIPolyTriQuadMesh* CastToTriQuadMesh () { return 0; }

};

inline const CATIPolySurface* CATIPolySurface::Cast (const CATIPolyObject& iObject)
{
  return iObject.CastToPolySurface ();
}

inline CATIPolySurface* CATIPolySurface::Cast (CATIPolyObject& iObject)
{
  return iObject.CastToPolySurface ();
}

inline const CATIPolySurface* CATIPolySurface::Cast (const CATIPolyObject* iObject)
{
  return iObject ? CATIPolySurface::Cast (*iObject) : 0;
}

inline CATIPolySurface* CATIPolySurface::Cast (CATIPolyObject* iObject)
{
  return iObject ? CATIPolySurface::Cast (*iObject) : 0;
}

#endif // !CATIPolySurface_H
