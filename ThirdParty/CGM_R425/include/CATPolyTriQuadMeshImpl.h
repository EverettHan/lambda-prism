//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyTriQuadMeshImpl
//
// Polyhedral triangle/quad mesh (aka CATIPolyTriQuadMesh) reference
// implementation
//
//=============================================================================
// 2007-02-05   BPG: New
//=============================================================================
#ifndef CATPolyTriQuadMeshImpl_H
#define CATPolyTriQuadMeshImpl_H

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATPolyBuckets_T.h"

#include "CATPolyTriQuadMeshBase.h"
#include "PolyMeshImpl.h"

class CATIPolyVertexFloatPositionConstLayer;


class ExportedByPolyMeshImpl CATPolyTriQuadMeshImpl : public CATPolyTriQuadMeshBase
{

public:

/** @name Life Cycle
    @{ */

  /**
   * Construction of an instance of CATPolyTriQuadMeshImpl.
   */
  static CATPolyTriQuadMeshImpl *New ();

/** @} */


public:

/** @name Vertex Management
    @{ */

  virtual int GetNbVertices() const;

  virtual HRESULT AddVertex(int &v);

  virtual HRESULT AddVertex(const CATMathPoint &P, int &v);

  virtual HRESULT RemoveVertex(const int v);

  virtual HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const;

/** @} */

public:

/** @name Triangle Management
    @{ */

  virtual int GetNbTriangles () const;

  virtual HRESULT AddTriangle (const int v0, const int v1, const int v2,
                               int &t);

  virtual HRESULT GetTriangle (const int t,
                               int &v0, int &v1, int &v2) const;

  virtual HRESULT GetTriangle (const int t,
                               int oVertices[3], int oNeighbors[3]) const;

  virtual HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

public:

/** @name Quad Management
    @{ */

  virtual int GetNbQuads () const;

  virtual HRESULT AddQuad (const int v0, const int v1, const int v2, const int v3,
                           int &q);

  virtual HRESULT GetQuad (const int q,
                           int &v0, int &v1, int &v2, int &v3) const;

  virtual HRESULT GetQuad (const int q,
                           int oVertices[4], int oNeighbors[4]) const;

  virtual HRESULT RemoveQuad (const int q, const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

public:

/** @name Facet Management
    @{ */

  virtual int GetNbFacets () const;

  virtual HRESULT GetFacet (const int f, CATListOfInt &oVertices) const;

  virtual HRESULT RemoveFacet (const int f);

/** @} */

public:

/** @name Iterators
    @{ */

  virtual HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

/** @} */

public:

/** @name Neighborhoods
    @{ */

  /**
   * Neighborhood needs to be implemented.
   */
  virtual HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

/** @} */

public:

/** @name Data Layers
    @{ */

  /**
    * @param oLayer [out, IUnknown#Release]
    */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer*& oLayer) const;

  /**
    * @param oLayer [out, IUnknown#Release]
    */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer*& oLayer);

  /**
    * @param oLayer [out, IUnknown#Release]
    */
  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer*& oLayer) const;

  HRESULT SetSupport (CATIPolySurfaceSupport* iSupport);

  /**
    * @param oSupport [out, IUnknown#Release]
    */
  HRESULT GetSupport (CATIPolySurfaceSupport*& oSupport) const;

/** @} */

public:

/** @name Visitors
    @{ */

  virtual HRESULT Accept (const CATIPolySurface &iM, CATPolySurfaceConstVisitor &iV) const;

  virtual HRESULT Accept (CATIPolySurface &iM, CATPolySurfaceVisitor &iV);

  virtual CATIPolySurfaceConstTools* GetConstTools () const;
  virtual CATIPolySurfaceTools* GetTools ();

/** @} */


public:

/** @name Topological Services
    @{ */

  virtual HRESULT MergeVertices (const int v0, const int v1);
  virtual HRESULT SplitBar (const int v0, const int v1, int &n);

  // (Orientation of t0 is reproduced in q)
  virtual HRESULT MergeTrianglesIntoQuad (const int t0, const int t1, int &q);

  // (Orientation of q is reproduced in t0 and t1)
  virtual HRESULT SplitQuadIntoTriangles (const int q, int &t0, int &t1, CATBoolean MakeEvenDiagonal = TRUE);

/** @} */


public:

  // Do not use via CATIPolyTriMeshInterface.  Use vertex iterator.
  virtual CATBoolean IsVertexDefined(const int v) const;
  virtual int GetMinVertexIndex() const;
  virtual int GetMaxVertexIndex() const;

  // Do not use via CATIPolyTriMeshInterface. Use vertex position layer (fix me.)
  virtual HRESULT GetVertexPosition(const int v, CATMathPoint &P) const;
  virtual HRESULT SetVertexPosition(const int v, const CATMathPoint &P);

  // Do not use via CATIPolyTriMeshInterface.  Use neighborhoods (fix me.)
  virtual HRESULT GetVertexNeighborsOfVertex(const int v, CATListOfInt &oNeighbors) const;
  virtual HRESULT GetFacetNeighborsOfVertex(const int v, CATListOfInt &oNeighbors) const;
  virtual HRESULT GetFacetNeighborsOfFacet (const int f, CATListOfInt &oNeighbors) const;
  virtual HRESULT GetFacetNeighborsOfBar (const int v0, const int v1, CATListOfInt &oNeighbors) const;

  // Do not use via CATIPolyTriMeshInterface.  Use triangle iterator (fix me.)
  virtual CATBoolean IsTriangleDefined (const int f) const;
  virtual int GetMinTriangleIndex () const;
  virtual int GetMaxTriangleIndex () const;

  // Do not use via CATIPolyTriMeshInterface.  Use quad iterator (fix me.)
  virtual CATBoolean IsQuadDefined (const int f) const;
  virtual int GetMinQuadIndex() const;
  virtual int GetMaxQuadIndex() const;

  // Do not use via CATIPolyTriMeshInterface.
  virtual CATBoolean IsFacetDefined (const int f) const;
  virtual int GetMinFacetIndex () const;
  virtual int GetMaxFacetIndex () const;

  // Do not use via CATIPolyTriMeshInterface.
  virtual HRESULT RemoveBar (const int v0, const int v1);

/** @} */

private:

// --------------------------------------------------------------------------
// Internals
//
// In facet neighborhood, quad and triangles are encoded as follows:
//
// 0 <= c : c is a quad, q = c its index
// q == 0 : invalid quad, free edge
//
// c < 0 : c is a triangle, t = (~c) is its index
// t == 0: invalid triangle, non-manifold edge
//

  class Vertex
  {
  public:
    inline Vertex();
    inline Vertex(float x, float y, float z);
    inline ~Vertex();

    // WARNING: Buckets use default assignment operator

    // Recycling
  public:
    inline void Clear();
    inline void Recycle(float x, float y, float z);

    // Facet iterator
  public:
    inline int GetNbFacets() const;
    inline int GetFacet(int e) const;

  public:
    HRESULT PushBackFacet(int f); // May return E_NOMEM
    CATBoolean EraseFacet(int f); // Return found-predicate

    //
  public:
    float _Coords[3];
  public:
    unsigned int _Defined      :  1;
    // (Let the compiler pad)
  public:
    unsigned int _NbFacets     : 15;
    unsigned int _FacetListSize: 15;
    union
    {
      int _F;
      int* _List;
    } _Facet;
  };
  class Specialize_CATPolyBuckets_T(VertexBuckets, Vertex);
  
  //
private:
  class Quad
  {
  public:
    inline Quad();
    inline Quad(int v0, int v1, int v2, int v3);

    enum { Size = 4 };

  public:
    inline void Recycle(int v0, int v1, int v2, int v3);

  public:
    inline int FindBar(int v0, int v1) const; // Return -1 on failure
    inline int GetFirstAdjacentFacet(int v0, int v1) const; // Return 0 on free edge, -1 on non-existing edge (SHOULD NOT)

    inline int NextAdjacentVertex(int v) const;
    inline int PrevAdjacentVertex(int v) const;

  public:
    int _Vertices[4];
    int _Neighbors[4];
  public:
    unsigned int _Defined :  1;
  };
  class Specialize_CATPolyBuckets_T(QuadBuckets, CATPolyTriQuadMeshImpl::Quad);

  //
private:
  class Triangle
  {
  public:
    inline Triangle();
    inline Triangle(int v0, int v1, int v2);

    enum { Size = 3 };

  public:
    inline void Recycle(int v0, int v1, int v2);

  public:
    inline int FindBar(int v0, int v1) const; // Return -1 on failure
    inline int GetFirstAdjacentFacet(int v0, int v1) const; // Return 0 on free edge, -1 on non-existing edge (SHOULD NOT)

    inline int GetOppositeVertex(int v0, int v1) const;

    inline int NextAdjacentVertex(int v) const;
    inline int PrevAdjacentVertex(int v) const;

  public:
    int _Vertices[3];
    int _Neighbors[3];
  public:
    unsigned int _Defined: 1;
  };
  class Specialize_CATPolyBuckets_T(TriangleBuckets, CATPolyTriQuadMeshImpl::Triangle);

  // Fast accessors
public:
  inline int FinalGetMinVertexIndex() const { return 1; }
  inline int FinalGetMaxVertexIndex() const { return _MaxVertexIndex; }

  inline CATBoolean FinalIsVertexDefined(int v) const
  {
    if (v <= 0 || _Vertices.Size() < (unsigned int) v) return FALSE;
    return _Vertices[v]._Defined;
  }

  inline int FinalGetMinFacetIndex() const { return ~_MaxTriangleIndex; }
  inline int FinalGetMaxFacetIndex() const { return _MaxQuadIndex; }

  inline CATBoolean FinalIsFacetDefined(int f) const
  {
    if (0 <= f)
    {
      const unsigned int q = f;
      return (0 < q && q <= _Quads.Size()) ? _Quads[q]._Defined : FALSE;
    }
    else
    {
      const unsigned int t = ~f;
      return (0 < t && t <= _Triangles.Size()) ? _Triangles[t]._Defined : FALSE;
    }
  }

  inline CATBoolean FinalIsTriangleDefined(int f) const
  {
    const unsigned int t = ~f;
    if (t <= 0 || _Triangles.Size() < t) return FALSE;
    return _Triangles[t]._Defined;
  }

  inline CATBoolean FinalIsQuadDefined(int f) const
  {
    const unsigned int q = f;
    if (q <= 0 || _Quads.Size() < q) return FALSE;
    return _Quads[q]._Defined;
  }

public:
  inline int FinalGetMinTriangleIndex() const { return ~_MaxTriangleIndex; }
  inline int FinalGetMaxTriangleIndex() const { return -2; }

  inline int FinalGetMinQuadIndex() const { return 1; }
  inline int FinalGetMaxQuadIndex() const { return _MaxQuadIndex; }

  // Topology exploration
private:
  // (Delegate to concrete)
  inline int GetFacetFirstAdjacentFacet(int f, int v0, int v1) const; // Return 0 on free edge, -1 on non-existing edge (SHOULD NOT)
  // (Delegate to concrete)
  inline int FindFacetBar(int f, int v0, int v1) const; // Return -1 if none

  // Return TRUE if found (facet f, bar b), FALSE otherwise
  CATBoolean FindFirstAdjacentFacet(int v0, int v1,
                                    int &f, int &b) const;

  // f: facet
  // (v0, v1): bar
  // n: first neighbor of f by (v0, v1)
  HRESULT TurnAroundFacetBar(int f, int v0, int v1, int n,
                             CATListOfInt &ioNeighbors) const;

  // Topology update
private:
  void InsertFacetInBarNeighborhood(int f, int v0, int v1, int &FacetNeighbor);
  HRESULT RemoveFacetFromBarNeighborhood(int f, int v0, int v1, int iFacetNeighbor);

  // Recycling
private:
  void PushUndefinedVertex(unsigned int v);
  unsigned int PopUndefinedVertex();

  void PushUndefinedTriangle(unsigned int t);
  unsigned int PopUndefinedTriangle();

  void PushUndefinedQuad(unsigned int q);
  unsigned int PopUndefinedQuad();

  // Forbidden constructs
private:
  CATPolyTriQuadMeshImpl(const CATPolyTriQuadMeshImpl &iRHS);
  CATPolyTriQuadMeshImpl& operator=(const CATPolyTriQuadMeshImpl &iRHS);

private:
  unsigned int _NbVertices;
  unsigned int _MaxVertexIndex;
  VertexBuckets _Vertices;

  unsigned int _FirstUndefinedVertex;

private:
  unsigned int _NbTriangles;
  unsigned int _MaxTriangleIndex;
  TriangleBuckets _Triangles;

  unsigned int _FirstUndefinedTriangle;

private:
  unsigned int _NbQuads;
  unsigned int _MaxQuadIndex;
  QuadBuckets _Quads;

  unsigned int _FirstUndefinedQuad;

private:

  CATIPolySurfaceSupport* _Support;

  friend class PositionLayerImpl;
  friend class PositionLayerImplFloat;

private:

  // Private constructor.
  CATPolyTriQuadMeshImpl ();

  virtual ~CATPolyTriQuadMeshImpl ();

};

#endif // !CATPolyTriQuadMeshImpl_H
