//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
#ifndef CATIPolyCurve_H
#define CATIPolyCurve_H

#include "PolyhedralModel.h"
#include "CATIPolyObject.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

// Subclasses.
class CATIPolySurfaceVertexLine;
class CATIPolyMeshCurve;

// Iterator.
class CATIPolyCurveVertexIterator;

// Layers, Supports.
class CATIPolyCurveVertexPositionConstLayer;
class CATIPolyCurveVertexPositionLayer;
class CATIPolyCurveVertexTangentConstLayer;
class CATIPolyCurveVertexTangentLayer;
class CATIPolyCurveVertexWConstLayer;
class CATIPolyCurveVertexWLayer;
class CATIPolySupport;
class CATIPolyLayer;
class CATIPolyLayerIterator;

// Tools
class CATIPolyCurveConstTools;
class CATIPolyCurveTools;

// Extensions: Observer, Visitors.
class CATIPolyCurveObserver;
class CATPolyCurveConstVisitor;
class CATPolyCurveVisitor;

class CATIPolySurface;
class CATMathPoint;


/**
* Interface to a polyhedral curve.
*
* A polyhedral curve is a curve represented by vertices, layers and support.  
* It consists of:
*   o Iterators to cycle through the vertices.
*   o Layers that store some properties about the vertices of the curve.
*   o A support that provide additional information about the geometry of the curve.
* 
* The vertices are referenced by integer indices.
* 
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolyCurve : public CATIPolyObject
{

public:

/** @name Downcasters
    @{ */

  inline static const CATIPolyCurve* Cast (const CATIPolyObject&);

  inline static CATIPolyCurve* Cast (CATIPolyObject&);

  inline static const CATIPolyCurve* Cast (const CATIPolyObject*);

  inline static CATIPolyCurve* Cast (CATIPolyObject*);

/** @} */

public:

/** @name Cross Services with Polyhedral Surfaces
    @{ */

  /**
   * Checks if the curve lies on a polyhedral surface.
   * @param s
   *   The input polyhedral surface.
   * @return
   *   <tt>TRUE</tt> if the curve lies on the polyhedral surface and <tt>FALSE</tt> otherwise.
   */
  virtual CATBoolean IsLyingOn (const CATIPolySurface &s) const = 0;

/** @} */

public:

/** @name Vertices Management
    @{ */

  /**
   * Appends a vertex at the end of the curve.
   * @param v
   *   The index of the appended vertex.
   * @return 
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT AppendVertex (int &v) = 0;

  /** 
   * Returns the number of vertices of the polyhedral curve.
   * @return 
   *   The number of vertices of the discrete curve.
   */
  virtual int GetNbVertices () const = 0;

  /**
   * Returns the start vertex of the curve.
   * @return
   *   The start vertex if any or 0 otherwise.
   */
  virtual int GetStartVertex () const = 0;

  /**
   * Returns the end vertex of the curve.
   * @return
   *   The end vertex if any or 0 otherwise.
   */
  virtual int GetEndVertex () const = 0;

  /**
   * Given a vertex of the curve, returns the next vertex along the curve.
   * @return
   *   The vertex if any or 0 otherwise.
   */
  virtual int GetNextVertex (int v) const = 0;

  /**
   * Given a vertex of the curve, returns the previous vertex along the curve.
   * @return
   *   The vertex if any or 0 otherwise.
   */
  virtual int GetPrevVertex (int v) const = 0;

/** @} */

public:

/** @name Vertex Iterator
    @{ */

  /**
   * Returns a vertex iterator (explicit).
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   * @return
   *   <tt>S_OK</tt> on success and <tt>E_FAIL</tt> or another error otherwise.
   */
  virtual HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const = 0;

/** @} */

public:

/** @name Vertex Layers
    @{ */

  /**
   * Returns the vertex position layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const = 0;

  /**
   * @nodoc
   * Returns the vertex position layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer) = 0;

  /**
   * @nodoc
   * Returns the vertex tangent layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const = 0;

  /**
   * @nodoc
   * Returns the vertex tangent layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer) = 0;

  /**
   * @nodoc
   * Returns the vertex W layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const = 0;

  /**
   * @nodoc
   * Returns the vertex W layer if any. 
   * @param oLayer
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  virtual HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer) = 0;

/** @} */

public:

  /** @name Data Layers
      @{ */

  /**
    * Adds a layer to the object.
    * @param iLayer
    *   The layer to be added to the object.
    * @param obs
    *   An optional observer for update of the layer during editing events of the CATIPolyCurve.  
    *   This layer is registered (and unregistered) automatically when the layer is added to (removed from) the curve.
    */
  virtual HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0) = 0;

  /**
   * Removes a layer from the object.  It will also unregister its associated observer.
   */
  virtual HRESULT RemoveLayer (CATIPolyLayer& iLayer) = 0;

  /**
   * Gets a specific layer given its class id.
   * If several layers of identical class ids are associated to the object,
   * then the method returns the most recent layer added to the object.
   */
  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const = 0;

  /**
   * Returns true if a layer of given id is associated to the curve.
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

/** @name Curve Support
    @{ */

  /**
   * @nodoc
   * Returns the underlying curve support, if any.
   * @param oSupport
   *   The curve support.  The returned support must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a support is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a support is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const = 0;

  /**
   * @nodoc
   * Sets the underlying curve support.
   * The curve support may be a surface or a curve.
   * @param iSupport
   *   A pointer to the curve support.  The method does and AddRef () on the support.
   *   Any previous support owned by the object will be released.
   * @return 
   *   S_OK if a support is successfully set.
   *   E_FAIL otherwise.
   */
  virtual HRESULT SetSupport (CATIPolySupport* iSupport) = 0;

/** @} */

public:

/** @name Topological Services
    @{ */

  /**
   * Splits the bar (v0, v1) with creation of a new vertex n. 
   * The coordinates of n are undefined and must be set with the use of the vertex position layer.
   * @param v0
   *   The first vertex of the bar.
   * @param v1
   *   The second vertex of the bar.
   * @param n
   *   The index of the new vertex.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> if the bar is split.
   *     <li> <tt>S_FALSE</tt> if the bar is not split (for instance if the two vertices are consecutive).
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  virtual HRESULT SplitBar (const int v0, const int v1, int &n) = 0;

  /**
   * Merges vertices v0 and v1 by collapse of the bar (v0, v1).
   * Topologically, Vertex v1 is replaced by Vertex v0.
   * The two vertices must be contiguous.
   * @param v0
   *   The first vertex of the bar.
   * @param v1
   *   The second vertex of the bar.
   * @return
   *   S_OK if the curve is successfully edited and E_FAIL otherwise.
   */
  virtual HRESULT MergeVertices (const int v0, const int v1) = 0;

public:

  /**
   * Check whether a curve is closed or not.
   * @return
   *   TRUE if the curve is closed, i.e. last vertex is linked to first, FALSE otherwise.
   */
  virtual CATBoolean IsClosed () const = 0;
  /** @} */

  /**
   * Define the curve as being closed.
   * @return 
   *   S_OK if the curve is successfully edited and E_FAIL otherwise.
   */
  virtual HRESULT Close () = 0;

  /**
   * Define the curve as being open.
   * @return 
   *   S_OK if the curve is successfully edited and E_FAIL otherwise.
   */
  virtual HRESULT Open () = 0;

/** @} */

public:

/** @name Event Listener. 
    Event listener are used to update user-defined attributes.
    @{ */

  /** 
   * @nodoc
   * Registers an observer (event listener) with the instance. 
   * @param iObserver
   *   The observer that is registered with the instance.
   * @return 
   *   S_OK if the observer is successfully registered with the curve.
   *   E_FAIL otherwise.
   */
  virtual HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver) = 0;

  /** 
   * @nodoc
   * Unregisters an observer (event listener) with the instance. 
   * @param iObserver
   *   The observer that is unregistered with the instance.
   * @return 
   *   S_OK if the observer is successfully unregistered with the curve.
   *   E_FAIL otherwise.
   */
  virtual HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver) = 0;

/** @} */

public:

/** @name Visitors.  
    Access to concrete types.
    @{ */

  /**
   * @nodoc
   * Accepts a const visitor for access to the concrete curve type.
   * @return
   *   The status of the application of the visitor.
   */
  virtual HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iV) const = 0;

  /**
   * @nodoc
   * Accepts a const visitor for access to the concrete curve type.
   * @return
   *   The status of the application of the visitor.
   */
  virtual HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iV) = 0;

/** @} */

public:

/** @name Other Services
    Tools provide access to various curve services. 
    Do not use in frameworks other than in PolyhedralInterfaces and PolyhedralObjects.
    @{ */

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolyCurveConstTools* GetConstTools () const = 0;

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolyCurveTools* GetTools () = 0;

/** @} */

public:

/** @name Deprecated Member Functions.
    Do not use any of these methods from this interface.
    @{ */

  /**
   * @nodoc
   * @see CATIPolyCurveVertexPositionLayer
   */
  virtual HRESULT AppendVertex (const CATMathPoint& P, int& v) = 0;

  /**
   * @nodoc
   * @see CATIPolyCurveVertexPositionConstLayer
   */
  virtual HRESULT GetVertexPosition (const int v, CATMathPoint& P) const = 0;

  /**
   * @nodoc
   * @see CATIPolyCurveVertexPositionLayer
   */
  virtual HRESULT SetVertexPosition (const int v, const CATMathPoint& P) = 0;

/** @} */

protected:

  virtual ~CATIPolyCurve() {}

  const CATIPolyCurve* CastToPolyCurve () const { return this; }
  CATIPolyCurve* CastToPolyCurve () { return this; }

public:

  /**
   * Casts a const CATIPolyCurve to a const CATIPolySurfaceVertexLine.
   * @return
   *   The cast as a const CATIPolySurfaceVertexLine.
   */
  virtual const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const { return 0; }

  /**
   * Casts a CATIPolyCurve to a CATIPolySurfaceVertexLine.
   * @return
   *   The cast as a const CATIPolySurfaceVertexLine.
   */
  virtual CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () { return 0; }

  /**
   * Casts a const CATIPolyCurve to a const CATIPolyMeshCurve.
   * @return
   *   The cast as a const CATIPolyMeshCurve.
   */
  virtual const CATIPolyMeshCurve* CastToMeshCurve () const { return 0; }

  /**
   * Casts a CATIPolyCurve to a CATIPolyMeshCurve.
   * @return
   *   The cast as a const CATIPolyMeshCurve.
   */
  virtual CATIPolyMeshCurve* CastToMeshCurve () { return 0; }

};

inline const CATIPolyCurve* CATIPolyCurve::Cast (const CATIPolyObject& iObject)
{
  return iObject.CastToPolyCurve ();
}

inline CATIPolyCurve* CATIPolyCurve::Cast (CATIPolyObject& iObject)
{
  return iObject.CastToPolyCurve ();
}

inline const CATIPolyCurve* CATIPolyCurve::Cast (const CATIPolyObject* iObject)
{
  return iObject ? CATIPolyCurve::Cast (*iObject) : 0;
}

inline CATIPolyCurve* CATIPolyCurve::Cast (CATIPolyObject* iObject)
{
  return iObject ? CATIPolyCurve::Cast (*iObject) : 0;
}

#endif // !CATIPolyCurve_H
