#ifndef CATIPolyTriQuadMeshObsoleteMethods_H
#define CATIPolyTriQuadMeshObsoleteMethods_H

/** @cond PRIVATE */

/** @name Deprecated Member Functions
Do not use any of these methods.  They are not supported.
@{ */

public:

  /**
  * @nodoc
  */
  virtual CATBoolean IsVertexDefined (const int v) const;

  /**
  * @nodoc
  */
  virtual int GetMinVertexIndex () const;

  /**
  * @nodoc
  */
  virtual int GetMaxVertexIndex () const;

  /**
  * @nodoc
  */
  virtual HRESULT GetVertexPosition (const int v, CATMathPoint &P) const;

  /**
  * @nodoc
  */
  virtual HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

  /**
  * @nodoc
  */
  virtual HRESULT GetVertexNeighborsOfVertex (const int v, CATListOfInt &oNeighbors) const;

  /**
  * @nodoc
  */
  virtual HRESULT GetFacetNeighborsOfVertex (const int v, CATListOfInt &oNeighbors) const;

  /**
  * @nodoc
  */
  virtual HRESULT GetFacetNeighborsOfBar (const int v0, const int v1, CATListOfInt &oNeighbors) const;

  /**
  * @nodoc
  */
  virtual HRESULT GetFacetNeighborsOfFacet (const int f, CATListOfInt &oNeighbors) const;

  /**
  * @nodoc
  * oNeighbors is filled with adjacent facet indices; by convention `0'
  * is used for indicating free edges, `-1' for non-2-manifold edges.
  * @return E_FAIL if q is not defined, S_OK otherwise
  */
  virtual HRESULT GetTriangle (const int t,
                               int oVertices[3], int oNeighbors[3]) const;

  /**
  * @nodoc
  * oNeighbors is filled with adjacent facet indices; by convention `0'
  * is used for indicating free edges, `-1' for non-2-manifold edges.
  * @return E_FAIL if q is not defined, S_OK otherwise
  */
  virtual HRESULT GetQuad (const int q,
                           int oVertices[4], int oNeighbors[4]) const;

  /**
  * @nodoc
  */
  virtual CATBoolean IsTriangleDefined (const int t) const;

  /**
  * @nodoc
  */
  virtual int GetMinTriangleIndex () const;

  /**
  * @nodoc
  */
  virtual int GetMaxTriangleIndex () const;

  /**
  * @nodoc
  */
  virtual CATBoolean IsQuadDefined (const int q) const;

  /**
  * @nodoc
  */
  virtual int GetMinQuadIndex () const;

  /**
  * @nodoc
  */
  virtual int GetMaxQuadIndex () const;

  /**
  * @nodoc
  */
  virtual CATBoolean IsFacetDefined (const int f) const;

  /**
  * @nodoc
  */
  virtual int GetMinFacetIndex () const;

  /**
  * @nodoc
  */
  virtual int GetMaxFacetIndex () const;

  /**
  * @nodoc
  */
  virtual HRESULT RemoveBar (const int v0, const int v1);

/** @} */

/** @endcond */

#endif // !CATIPolyTriQuadMeshObsoleteMethods_H
