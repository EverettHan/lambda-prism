//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Polyhedral triangle/quad mesh interface
//
//=============================================================================
// 2007-06-14   BPG: Inherit from CATIPolySurface
// 2007-02-08   BPG: New
//=============================================================================
#ifndef CATIPolyTriQuadMesh_H
#define CATIPolyTriQuadMesh_H

#include "PolyhedralModel.h"
#include "CATIPolySurface.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATMathPoint;


/**
* Interface to a polyhedral triangle-quad mesh.
*
* A CATIPolyTriQuadMesh is a polyhedral surface whose facets are either triangles or quads.
* This interface provides additional iterators and methods to access and
* edit the triangles and the quads.
*/
class ExportedByPolyhedralModel CATIPolyTriQuadMesh : public CATIPolySurface
{

public:

/** @name Downcasters
    @{ */

  inline static const CATIPolyTriQuadMesh* Cast (const CATIPolySurface&);

  inline static CATIPolyTriQuadMesh* Cast (CATIPolySurface&);

  inline static const CATIPolyTriQuadMesh* Cast (const CATIPolySurface*);

  inline static CATIPolyTriQuadMesh* Cast (CATIPolySurface*);

  inline static const CATIPolyTriQuadMesh* Cast (const CATIPolyObject&);

  inline static CATIPolyTriQuadMesh* Cast (CATIPolyObject&);

  inline static const CATIPolyTriQuadMesh* Cast (const CATIPolyObject*);

  inline static CATIPolyTriQuadMesh* Cast (CATIPolyObject*);

/** @} */

public:

/** @name Vertex Management
   @{ */

  /** 
   * Adds a vertex and return its index.
   * @param P The position of the vertex.
   * @param v The index of the added vertex.
   * @return S_OK if the vertex is added successfully, E_FAIL otherwise.
   */
  virtual HRESULT AddVertex (const CATMathPoint &P, int &v) = 0;

  /**
   * Removes the vertex.
   * @return S_OK if the vertex is removed and E_FAIL otherwise.
   */
  virtual HRESULT RemoveVertex (const int v) = 0;

  /**
   * Returns the number of vertices in the mesh.
   */
  virtual int GetNbVertices() const = 0;

/** @} */


public:

/** @name Triangle Management
    @{ */

  /**
   * Returns the total number of triangles in the mesh.
   */
  virtual int GetNbTriangles () const = 0;

  /**
   * Adds a triangle and returns its index.
   * @return
   *   S_OK if the triangle is added successfully, E_FAIL otherwise.
   */
  virtual HRESULT AddTriangle (const int v0, const int v1, const int v2,
                               int &t) = 0;

  /**
   * Returns the vertices of a triangle given its index.
   */
  virtual HRESULT GetTriangle (const int t,
                               int &v0, int &v1, int &v2) const = 0;

  /**
   * Removes the triangle.
   */
  virtual HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE) = 0;

/** @} */


public:

/** @name Quad Management
    @{ */

  /**
   * Returns the total number of quads in the mesh.
   */
  virtual int GetNbQuads () const = 0;

  /**
   * Adds a quad and returns its index.
   * @return
   *   S_OK if the quad is added successfully, E_FAIL otherwise.
   */
  virtual HRESULT AddQuad (const int v0, const int v1, const int v2, const int v3,
                           int &q) = 0;

  /**
   * Returns the vertices of a quad given its index.
   */
  virtual HRESULT GetQuad (const int q,
                           int &v0, int &v1, int &v2, int &v3) const = 0;

  /**
   * Removes the quad.
   */
  virtual HRESULT RemoveQuad (const int q, const CATBoolean iRemoveUnreferencedVertices = FALSE) = 0;

/** @} */


public:

/** @name Facet Management
    @{ */

  /**
   * Removes a triangle or a quad given its index.
   * Returns S_OK if the facet is removed successfully.
   */
  virtual HRESULT RemoveFacet (const int f) = 0;

/** @} */


public:

/** @name Topological Services
    @{ */

  /**
   * See CATIPolySurface::MergeVertices
   */
  virtual HRESULT MergeVertices (const int v0, const int v1) = 0;

  /**
   * See CATIPolySurface::SplitBar
   */
  virtual HRESULT SplitBar (const int v0, const int v1, int &n) = 0;

  /**
  * Merges two adjacent triangles into a quad and returns its index.
  */
  virtual HRESULT MergeTrianglesIntoQuad (const int t0, const int t1,
                                         int &q) = 0;

  /**
  * Splits a quad into two triangles and returns their indices.
  */
  virtual HRESULT SplitQuadIntoTriangles (const int q,
                                          int &t0, int &t1, CATBoolean MakeEvenDiagonal = TRUE) = 0;

/** @} */

public:  // Should be protected.

  virtual ~CATIPolyTriQuadMesh () {}

public:

  const CATIPolyTriQuadMesh* CastToTriQuadMesh () const { return this; }
  CATIPolyTriQuadMesh* CastToTriQuadMesh () { return this; }

private:

#include "CATIPolyTriQuadMeshObsoleteMethods.h"

};

inline CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (CATIPolySurface& S)
{
  return S.CastToTriQuadMesh ();
}

inline const CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (const CATIPolySurface& S)
{
  return S.CastToTriQuadMesh ();
}

inline CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (CATIPolySurface* S)
{
  return S ? Cast (*S) : 0;
}

inline const CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (const CATIPolySurface* S)
{
  return S ? Cast (*S) : 0;
}

inline const CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (const CATIPolyObject& iObject)
{
  return Cast (iObject.CastToPolySurface ());
}

inline CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (CATIPolyObject& iObject)
{
  return Cast (iObject.CastToPolySurface ());
}

inline const CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (const CATIPolyObject* iObject)
{
  return iObject ? Cast (iObject->CastToPolySurface ()) : 0;
}

inline CATIPolyTriQuadMesh* CATIPolyTriQuadMesh::Cast (CATIPolyObject* iObject)
{
  return iObject ? Cast (iObject->CastToPolySurface ()) : 0;
}

#endif // !CATIPolyTriQuadMesh_H
