//=============================================================================
// COPYRIGHT Dassault Systemes 2004
//=============================================================================
//
// Polyhedral triangular mesh interface
//
//=============================================================================
// Usage:
//=============================================================================
// 2008-09-04   NDO: Clean interface.
// 2007-06-14   BPG: Inherit from CATIPolySurface.
// 2004-06-07   NDO: New.
//=============================================================================
#ifndef CATIPolyMesh_H
#define CATIPolyMesh_H

#include "PolyhedralModel.h"
#include "CATIPolySurface.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATIPolyMeshObsoleteMethods.h"

/** @nodoc */  // DO NOT USE
typedef int CATPolyAttributeID;

/** @nodoc */  // DO NOT USE
enum PolyVertexAttributeIDs
{
  ePolyVertexNormal = 1      // Vertex normal.
};

class CATPolyAttribute;  // DO NOT USE
class CATIPolyBody;      // DO NOT USE

// Iterators
class CATIPolyMeshTriangleIterator;
class CATIPolyMeshTriangleVertexIterator;

// Behavioral extensions
class CATIPolyMeshObserver;

class CATMathBox;
class CATMathPoint;
class CATMapOfIntToInt;

/**
* Interface to a polyhedral triangular mesh.
*
* A CATIPolyMesh is a polyhedral surface whose facets are triangular.
* This interface provides additional iterators and methods to access and
* edit the triangles.
*
*/
class ExportedByPolyhedralModel CATIPolyMesh : public CATIPolySurface
{

public:

  /** @name Downcasters
      @{ */

  inline static const CATIPolyMesh* Cast (const CATIPolySurface&);

  inline static CATIPolyMesh* Cast (CATIPolySurface&);

  inline static const CATIPolyMesh* Cast (const CATIPolySurface*);

  inline static CATIPolyMesh* Cast (CATIPolySurface*);

  inline static const CATIPolyMesh* Cast (const CATIPolyObject&);

  inline static CATIPolyMesh* Cast (CATIPolyObject&);

  inline static const CATIPolyMesh* Cast (const CATIPolyObject*);

  inline static CATIPolyMesh* Cast (CATIPolyObject*);

  /** @} */

public:

/** @name Vertex Management
    @{ */

  /**
    * Adds a vertex and returns its index.
    * @param iPoint
    *   The position of the vertex.
    * @param oIdxVertex
    *   The index of the added vertex.
    * @return
    *   S_OK on success or E_FAIL or another error otherwise.
    */
  virtual HRESULT AddVertex (const CATMathPoint &iPoint, int &oIdxVertex) = 0;

  /**
   * Adds a vertex to the surface.
   * @param v
   *   The index of the added vertex.
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT AddVertex (int &oIdxVertex) = 0;

  /**
   * Removes a vertex.
   * @param iIdxVertex
   *   The index of the vertex to be removed.
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT RemoveVertex (const int iIdxVertex) = 0;

/** @} */


public:

/** @name Triangle Management
    @{ */

  /**
   * Returns the total number of triangles in the mesh.
   * @return
   *   The number of triangles.
   */
  virtual int GetNbTriangles () const = 0;

  /**
   * Adds a triangle and returns its index.
   * @param iIdxVertices
   * The indices of the three vertices.
   * @param oIdxTriangle
   * The index of the added triangle.
   * @return
   *   S_OK if the triangle is added successfully, E_FAIL otherwise.
   */
  virtual HRESULT AddTriangle (const int iIdxVertices[3], int &oIdxTriangle) = 0;

  /**
   * Returns the vertices of a triangle given its index.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param oIdxVertices
   * The indices of the triangle vertices.
   * @return
   *   S_OK if the a triangle is successfully returned and E_FAIL otherwise.
   */
  virtual HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3]) const = 0;

  /**
   * Removes the triangle.
   * @param idxTriangle
   *   The index of the triangle to remove.
   * @param iRemoveUnreferencedVertices
   *   A flag indicating whether to remove vertices that are no longer referenced by any triangle.
   *   The default value is set to FALSE.  Vertices will not be implicitly removed.
   * @return
   *   S_OK if the triangle is removed and E_FAIL otherwise.
   */
  virtual HRESULT RemoveTriangle (const int iIdxTriangle, const CATBoolean iRemoveUnreferencedVertices = FALSE) = 0;

public:

  /**
   * Returns a triangle iterator for the whole mesh (explicit).
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator*& oIterator) const = 0;

  /**
   * @nodoc
   * Returns a triangle iterator for the whole mesh (explicit).
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator*& oIterator) const = 0;

/** @} */


public:

/** @name Split, Merge and Flip Events
    @{ */

  /**
    * Flips the bar between two triangles.<br>
    * The method can only flip a bar between two triangles.
    * It will fail otherwise.
    * Let T1 (n1, n2, n3) and T2 (n4, n2, n1) be two triangles.
    * They will be replaced by the triangles T'1 (n1, n4, n3) and T'2 (n4, n2, n3)
    * after a successful call to this method.
    * The index of the two triangles may change.
    * <pre>
    *   n4-----n2     n4-----n2
    *   |     /|      |\     |
    *   | T2 / |      | \ T2'|
    *   |   /  |      |  \   |
    *   |  /   | ==>  |   \  |
    *   | / T1 |      |T1' \ |
    *   |/     |      |     \|
    *   n1-----n3     n1-----n3
    * </pre>
    * @param iIdxVertex1
    * The index of the first vertex.
    * @param iIdxVertex2
    * The index of the second vertex.
    * @return
    * <ul>
    *   <li> <code> S_OK </code> on success.
    *   <li> <code> E_FAIL </code> otherwise.
    * </ul>
    */
  virtual HRESULT FlipBar (const int iIdxVertex1, const int iIdxVertex2) = 0;

  /**
   * Splits the bar connecting two vertices, refining the adjacent triangles A
   * new vertex is created whose position is undetermined. <br/>
   *
   * <pre>
   *   v2------v1      v2------v1
   *   |      /|       |\ t2  /|
   *   | t0  / |       | \   / |
   *   |    /  |       |  \ /  |
   *   |   /   |  ==>  |t0 n t3|
   *   |  /    |       |  / \  |
   *   | /  t1 |       | /   \ |
   *   |/      |       |/ t1  \|
   *   v0------v3      v0------v3
   * </pre>
   *
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> otherwise.
   * </ul>
   */
  virtual HRESULT SplitBar (const int v0, const int v1, int &n) = 0;

  /**
   * Merges two vertices.  If there is a bar between the two vertices, it collapses
   * the bar and removes the triangles referring to these two vertices.
   * The method replaces v1 by v0 in the mesh.
   * Topologically, the method:
   * <ul>
   *   <li> Removes the triangles connected to v0 and v1; and, </li>
   *   <li> Replaces v1 by v0 in the remaining triangles referring to v1. </li>
   * <ul>
   * The second vertex, v1, is topologically disconnected but it is NOT removed from the mesh.
   * To remove the vertex v1, the method RemoveVertex () must be called explicitely.
   * <br/>
   *
   * <pre>
   *   v0------v2      v0------v2
   *   |\  t2 /|       |      /|
   *   | \   / |       | t0  / |
   *   |  \ /  |       |    /  |
   *   |t0 v1 t3  ==>  |   /   |
   *   |  / \  |       |  /    |
   *   | /   \ |       | /  t1 |
   *   |/  t1 \|       |/      |
   *   v4------v3      v4------v3
   * </pre>
   *
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> otherwise.
   */
  virtual HRESULT MergeVertices (const int v0, const int v1) = 0;

/** @} */


public:

/** @name Storage Services
    @{ */

  /**
    * Compacts the arrays containing the mesh data.<br>
    * The indices are not stable during a compact operation since reference to deleted vertices and
    * triangles are removed.
    */
  virtual HRESULT Compact () = 0;

  /**
   * Compacts the arrays containing the mesh data.<br>
   * The vertex and triangle indices are not stable during compact and
   * the input maps are used to store the mapping of old to new indices.
   * @param ioVertexMap
   *   The map from an old vertex index to a new vertex index.
   * @param ioTriangleMap
   *   The map from an old triangle index to a new triangle index.
   */
  virtual HRESULT Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap) = 0;

  /**
   * Reserves additional storage for vertices and triangles.
   * @param iNbVertices
   *   The number of vertices applied to increase vertex storage.
   * @param iNbTriangles
   *   The number of triangles applied to increase triangle storage.
   */
  virtual HRESULT Reserve (int iNbVertices, int iNbTriangles) = 0;

/** @} */


public:

/** @name Geometrical Services
@{ */

  /**
   * Returns the bounding box of the whole mesh.
   * @param oBBox
   *   The returned bounding box.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the bounding box is set.
   *   <li> <code> S_FALSE </code> if the bounding box is not set.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT GetBoundingBox (CATMathBox &oBBox) const = 0;

/** @} */

public:  // Should be protected.

  virtual ~CATIPolyMesh () {}

public:

  const CATIPolyMesh* CastToTriMesh () const { return this; }
  CATIPolyMesh* CastToTriMesh () { return this; }

private:

  CATIPolyMeshObsoleteMethods

};

inline CATIPolyMesh* CATIPolyMesh::Cast (CATIPolySurface& S)
{
  return S.CastToTriMesh ();
}

inline const CATIPolyMesh* CATIPolyMesh::Cast (const CATIPolySurface& S)
{
  return S.CastToTriMesh ();
}

inline CATIPolyMesh* CATIPolyMesh::Cast (CATIPolySurface* S)
{
  return S ? Cast (*S) : 0;
}

inline const CATIPolyMesh* CATIPolyMesh::Cast (const CATIPolySurface* S)
{
  return S ? Cast (*S) : 0;
}

inline const CATIPolyMesh* CATIPolyMesh::Cast (const CATIPolyObject& iObject)
{
  return Cast (iObject.CastToPolySurface ());
}

inline CATIPolyMesh* CATIPolyMesh::Cast(CATIPolyObject& iObject)
{
  return Cast (iObject.CastToPolySurface ());
}

inline const CATIPolyMesh* CATIPolyMesh::Cast(const CATIPolyObject* iObject)
{
  return iObject ? Cast (iObject->CastToPolySurface ()) : 0;
}

inline CATIPolyMesh* CATIPolyMesh::Cast (CATIPolyObject* iObject)
{
  return iObject ? Cast (iObject->CastToPolySurface ()) : 0;
}

#endif // !CATIPolyMesh_H
