#ifndef CATIPolyMeshObsoleteMethods_H
#define CATIPolyMeshObsoleteMethods_H

/** @cond PRIVATE */

/** @name Deprecated Member Functions
Do not use any of these methods.  They are not supported.
@{ */

// These methods are all deprecated.
#define CATIPolyMeshObsoleteMethods                                                         \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsVertexDefined (const int iIdxVertex) const;                          \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsVertexReferenced (const int iIdxVertex) const;                       \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsVertexManifold (const int iIdxVertex) const;                         \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsHoleVertex (const int iIdxVertex) const;                             \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual int GetMinVertexIndex () const;                                                   \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual int GetMaxVertexIndex () const;                                                   \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsBarValid (const int iIdxVertex1, const int iIdxVertex2) const;       \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsBarManifold (const int iIdxVertex0, const int iIdxVertex1) const;    \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsHoleBar (const int iIdxVertex0, const int iIdxVertex1) const;        \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetBar (const int iIdxTriangle0, const int iIdxTriangle1, int & oIdxVertex0, int & oIdxVertex1, int & oNbBars) const; \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATBoolean IsTriangleDefined (const int iIdxTriangle) const;                      \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual int GetMinTriangleIndex () const;                                                 \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual int GetMaxTriangleIndex () const;                                                 \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetVertexNeighborsOfVertex (const int iIdxVertex, CATListOfInt &ioIdxVertices) const; \
                                                                                            \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3], int oIdxTriangles[3]) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTriangleNeighborsOfVertex (const int iIdxVertex, CATListOfInt &ioIdxTriangles) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTriangleNeighborsOfBar (const int iIdxVertex1, const int iIdxVertex2, int &oIdxTriangle1, int &oIdxTriangle2) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTriangleNeighborsOfBar (const int iIdxVertex1, const int iIdxVertex2, CATListOfInt &ioIdxTriangles) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTriangleNeighborsOfTriangle (const int iIdxTriangle, int oIdxNeighborTriangles[3]) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT AddTriangle (const int iIdxVertices[3], int &oIdxTriangle, const int iIdxFace); \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetFaceFromTriangle (const int iIdxTriangle, int &oIdxFace) const;        \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTrianglesFromFace (const int iIdxFace, CATListOfInt &oIdxTriangles) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT UpdateTriangle (const int iIdxTriangle, const int iIdxVertices[3]);       \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT InvertTriangle (const int iIdxTriangle);                                  \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const;     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT SetVertexPosition (const int iIdxVertex, const CATMathPoint &iPoint);     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetTrianglePoints (const int iIdxTriangle,                                \
                                     CATMathPoint& oPoint1, CATMathPoint& oPoint2, CATMathPoint& oPoint3) const; \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use AddVertices.  Replace instead by calls to AddVertex.",       \
  virtual HRESULT AddVertices (const int iNbVertices, const float* iPoints, int &oFirstIndex)); \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use RemoveVertices.  Replace instead by use of vertex iterator and calls to RemoveVertex.", \
  virtual HRESULT RemoveVertices (const CATListOfInt &iIdxVertices));                       \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use GetVertices.  Replace instead by use of vertex iterator and calls to GetVertex.", \
  virtual HRESULT GetVertices (CATListOfInt &oIdxVertices) const);                          \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use AddTriangles.  Replace instead by CATPolyDefaultAddTriangles from CATPolyDefaultMeshServices.", \
  virtual HRESULT AddTriangles (const int     iNbVertices,                                  \
                                const double* iCoords,                                      \
                                const int     iNbTriangles,                                 \
                                const int*    iIdxVertices,                                 \
                                const int     iIdxFace = 0));                               \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use AddTriangles.  Replace instead by CATPolyDefaultAddTriangles from CATPolyDefaultMeshServices.", \
  virtual HRESULT AddTriangles (const int           iNbVertices,                            \
                                const CATMathPoint* iPoints,                                \
                                const int           iNbTriangles,                           \
                                const int*          iIdxVertices,                           \
                                const int           iIdxFace = 0));                         \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use GetTriangles.  See instead triangle iterators.",             \
  virtual HRESULT GetTriangles (CATListOfInt &oIdxTriangles) const);                        \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use GetTriangles.  See instead triangle iterators.",             \
  virtual HRESULT GetTriangles (int     &oNbVertices,                                       \
                                double* &ioCoords,                                          \
                                int     &oNbTriangles,                                      \
                                int*    &ioIdxVertices) const);                             \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use GetTriangles.  See instead triangle iterators.",             \
  virtual HRESULT GetTriangles (int           &oNbVertices,                                 \
                                CATMathPoint* &ioPoints,                                    \
                                int           &oNbTriangles,                                \
                                int*          &ioIdxVertices) const);                       \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  POLY_DEPRECATED ("Do not use RemoveTriangles.  See instead triangle iterators and RemoveTriangle.", \
  virtual HRESULT RemoveTriangles (const CATListOfInt &iIdxTriangles,                       \
                                  const CATBoolean iRemoveUnreferencedVertices = FALSE));   \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT Compact (int* &ioIdxVertices, int* &ioIdxTriangles);                      \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  enum Orientation {                                                                        \
    O_Unset = 0,                                                                            \
    O_Right = 1, O_Outside = 1, O_Indirect = 1,                                             \
    O_Left = 2, O_Inside = 2, O_Direct = 2,                                                 \
    O_Undecided = 3                                                                         \
  };                                                                                        \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT PropagateOrientation (const int iIdxTriangle = 0,                         \
                                        const CATIPolyMesh::Orientation iOrientation = O_Direct, \
                                        const CATBoolean iInvert = FALSE);                  \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT RegisterVertexAttribute (CATPolyAttribute* iAttribute);                   \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual CATPolyAttribute* GetVertexAttribute (const CATPolyAttributeID id) const;         \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT EndModification ();                                                       \
                                                                                            \
public:                                                                                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  */                                                                                        \
  virtual HRESULT GetFacet (const int f, CATListOfInt &oVertices) const;                    \
                                                                                            \
protected:                                                                                  \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyAddVertices (const int iNbVertices, const float* iPoints, int &oFirstIndex); \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyRemoveVertices (const CATListOfInt &iIdxVertices);                   \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyGetVertices (CATListOfInt &oIdxVertices) const;                      \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyAddTriangles (const int     iNbVertices,                             \
                                     const double* iCoords,                                 \
                                     const int     iNbTriangles,                            \
                                     const int*    iIdxVertices,                            \
                                     const int     iIdxFace = 0);                           \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyAddTriangles (const int           iNbVertices,                       \
                                     const CATMathPoint* iPoints,                           \
                                     const int           iNbTriangles,                      \
                                     const int*          iIdxVertices,                      \
                                     const int           iIdxFace = 0);                     \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyGetTriangles (CATListOfInt &oIdxTriangles) const;                    \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyGetTriangles (int     &oNbVertices,                                  \
                                     double* &ioCoords,                                     \
                                     int     &oNbTriangles,                                 \
                                     int*    &ioIdxVertices) const;                         \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyGetTriangles (int           &oNbVertices,                            \
                                     CATMathPoint* &ioPoints,                               \
                                     int           &oNbTriangles,                           \
                                     int*          &ioIdxVertices) const;                   \
                                                                                            \
  /**                                                                                       \
  * @nodoc                                                                                  \
  * Temporary method until complete removal of AddVertices.                                 \
  */                                                                                        \
  virtual HRESULT DummyRemoveTriangles (const CATListOfInt &iIdxTriangles,                  \
                                        const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

/** @endcond */

#endif // !CATIPolyMeshObsoleteMethods_H
