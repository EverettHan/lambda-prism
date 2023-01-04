//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyRawBuffersMesh
//
//=============================================================================
// 2008-10-16   ZFI: add tangents, binormals, scale
// 2008-05-12   BPG: New.
//=============================================================================
#ifndef CATPolyRawBuffersMesh_H
#define CATPolyRawBuffersMesh_H

#include "CATErrorDef.h"
#include "CATBoolean.h"

//#include "CATIPolyMesh.h"
#include "CATPolyMeshBaseConst.h"

// ----------------------------------------------------------------------------
#include "PolyMeshImpl.h"


class ExportedByPolyMeshImpl CATPolyRawBuffersMesh : public CATPolyMeshBaseConst
{

 public:
  CATPolyRawBuffersMesh(const float *VertexPositionBuffer, int VertexPositionBufferSize,
                        const float *VertexNormalBuffer, int VertexNormalBufferSize,
                        const float *VertexUVBuffer, int VertexUVBufferSize,
                        const float *VertexTextureCoords, int TexDimension,
                        const float *VertexTangent, const float *VertexBinormal,
                        const int *IsolatedTriangleBuffer, int NbIsolatedTriangles,
                        const int *StripVertexBuffer, int NbStrips, const int *NbStripVertices,
                        const int *FanVertexBuffer, int NbFans, const int *NbFanVertices,
                        CATBoolean IsPlanar);

  ~CATPolyRawBuffersMesh();

 public:
  virtual const CATIPolyMesh *CastToTriMesh() const;
  virtual CATIPolyMesh *CastToTriMesh();

  virtual const CATIPolyTriQuadMesh *CastToTriQuadMesh() const;
  virtual CATIPolyTriQuadMesh *CastToTriQuadMesh();

  // Vertices
 public:
  virtual int GetMinVertexIndex() const;
  virtual int GetMaxVertexIndex() const;

 public:

  virtual HRESULT GetVertexPositionLayer(CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;

  // Should not be implemented in this class.  See CATPolyMeshBaseConst.
  virtual HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalLayer *&oLayer);
  virtual HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVLayer *&oLayer);
  virtual HRESULT GetVertexTextureCoordLayer(CATIPolySurfaceVertexTextureCoordLayer *&oLayer);

  HRESULT GetTools (CATIPolySurfaceTools*& oSurfaceTools) const;

  // Triangles
 public:
  virtual int GetNbFacets() const;
  virtual int GetMaxFacetSize() const;

 public:
  virtual int GetNbTriangles() const;

 public:
  virtual HRESULT GetFacetIterator(CATIPolySurfaceFacetIterator *&oIterator) const;
  virtual HRESULT GetFacet(const int iFacet, CATListOfInt &oVertices) const;

  virtual HRESULT GetTriangleIterator(CATIPolyMeshTriangleIterator*& oIterator) const;
  virtual HRESULT GetTriangleIterator(CATIPolyMeshTriangleVertexIterator*& oIterator) const;

  virtual HRESULT GetTriangle(const int iTriangle, int oVertices[3]) const;

  // Specific accessors
 public:
  int GetMaxNbVertices() const;

 public:
  inline int GetNbIsolatedTriangles() const { return _NbIsolatedTriangles; }

  inline int MakeIsolatedTriangleIndex(int t) const { return t; }

 public:
  inline int GetNbStrips() const { return _NbStrips; }
  inline int GetNbStripTriangles(int s) const { return 2 < _NbStripVertices[s] ? _NbStripVertices[s] - 2 : 0; }
  
  inline int MakeStripTriangleIndex(int s, int st) const { return GetStripTriangleBase() + s * GetStripTriangleStride() + st; }

 public:
  inline int GetNbFans() const { return _NbFans; }
  inline int GetNbFanTriangles(int f) const { return 2 < _NbFanVertices[f] ? _NbFanVertices[f] - 2 : 0; }

  inline int MakeFanTriangleIndex(int f, int ft) const { return GetFanTriangleBase() + f * GetFanTriangleStride() + ft; }

 protected:
  inline int GetMinIsolatedTriangleIndex() const { return 1; }
  inline int GetMaxIsolatedTriangleIndex() const { return _NbIsolatedTriangles; }
  inline CATBoolean IsAnIsolatedTriangle(int t) const
  { return GetMinIsolatedTriangleIndex() <= t && t <= GetMaxIsolatedTriangleIndex(); }

  inline int GetStripTriangleBase() const { return GetNbIsolatedTriangles(); }
  inline int GetStripTriangleStride() const { return _StripTriangleStride; }

  inline int GetMinStripTriangleIndex() const { return GetStripTriangleBase() + 1; }
  inline int GetMaxStripTriangleIndex() const { return GetStripTriangleBase() + GetNbStrips() * GetStripTriangleStride(); }
  inline CATBoolean IsAStripTriangle(int t) const
  { return GetMinStripTriangleIndex() <= t && t <= GetMaxStripTriangleIndex(); }

  inline int GetFanTriangleBase() const { return GetMaxStripTriangleIndex(); }
  inline int GetFanTriangleStride() const { return _FanTriangleStride; }

  inline int GetMinFanTriangleIndex() const { return GetFanTriangleBase() + 1; }
  inline int GetMaxFanTriangleIndex() const { return GetFanTriangleBase() + GetNbFans() * GetFanTriangleStride(); }
  inline CATBoolean IsAFanTriangle(int t) const
  { return GetMinFanTriangleIndex() <= t && t <= GetMaxFanTriangleIndex(); }

 protected:
  const float *_VertexPositionBuffer;
  int _VertexPositionBufferSize;
  friend class CATPolyRawBuffersMeshVertexPositionConstLayer;

  const float *_VertexNormalBuffer;
  int _VertexNormalBufferSize;

  friend class CATPolyRawBuffersMeshVertexNormalConstLayer;

  const float *_VertexUVBuffer;
  int _VertexUVBufferSize;
  friend class CATPolyRawBuffersMeshVertexUVLayer;

  const float *_VertexTextureCoords;
  int _TexDimension;
  const float *_VertexTangent;
  const float *_VertexBinormal;
  friend class CATPolyRawBuffersMeshVertexTexCoordLayer;

 protected:
  int _MinVertexIndex;
  int _MaxVertexIndex;

 protected:
  int _NbTriangles;

  const int *_IsolatedTriangleBuffer;
  int _NbIsolatedTriangles;

  const int *_StripVertexBuffer;
  int _NbStrips;
  const int *_NbStripVertices;
  int _StripTriangleStride;
  int *_StripFirstVertex;

  const int *_FanVertexBuffer;
  int _NbFans;
  const int *_NbFanVertices;
  int _FanTriangleStride;
  int *_FanFirstVertex;

  CATBoolean _IsPlanar;


  // ----------------------------------------------------------------------------
  // Unsupported methods

  // Vertices
 private:
  virtual HRESULT AddVertex(const CATMathPoint &iPoint, int &oIdxVertex);
  virtual HRESULT AddVertex(int &oIdxVertex);

  virtual HRESULT RemoveVertex(const int iIdxVertex);

 private:
  virtual CATBoolean IsVertexDefined(const int iIdxVertex) const;

  virtual int GetNbVertices() const;

  virtual HRESULT GetVertexIterator(CATIPolySurfaceVertexIterator *&oIterator) const;

 private:
  virtual HRESULT GetVertexFacetNeighborhood(CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  // Triangles
 private:
  virtual HRESULT AddTriangle(const int  iIdxVertices[3], int &oIdxTriangle);
  virtual HRESULT RemoveTriangle(const int iIdxTriangle, const CATBoolean iRemoveUnreferencedVertices = FALSE);

  virtual int GetMinTriangleIndex() const;
  virtual int GetMaxTriangleIndex() const;

  virtual CATBoolean IsTriangleDefined(const int iIdxTriangle) const;

 private:
  virtual HRESULT RegisterObserver(CATIPolyMeshObserver &iObserver);
  virtual HRESULT UnregisterObserver(CATIPolyMeshObserver &iObserver);

  //
 private:
  virtual HRESULT GetOrientedBarTangentLayer(CATIPolySurfaceOrientedBarTangentLayer *&oLayer);

  // Geometrical services
 private:
  virtual HRESULT GetVertexPosition(const int iIdxVertex, CATMathPoint &oPoint) const;
  virtual HRESULT SetVertexPosition(const int iIdxVertex, const CATMathPoint &iPoint);
  virtual HRESULT GetTrianglePoints(const int iIdxTriangle,
                                    CATMathPoint& oPoint1, CATMathPoint& oPoint2, CATMathPoint& oPoint3) const;
  virtual HRESULT GetBoundingBox(CATMathBox &oBBox) const;

  // Topological services
 private:
  virtual CATBoolean IsVertexReferenced(const int iIdxVertex) const;
  virtual HRESULT GetVertexNeighborsOfVertex(const int     iIdxVertex,
                                             CATListOfInt &ioIdxVertices) const;
  virtual HRESULT GetTriangleNeighborsOfVertex(const int     iIdxVertex,
                                               CATListOfInt &ioIdxTriangles) const;
  virtual HRESULT GetTriangle(const int iIdxTriangle,
                              int       oIdxVertices[3],
                              int       oIdxTriangles[3]) const;
  virtual HRESULT GetTriangleNeighborsOfTriangle(const int iIdxTriangle,
                                                 int       oIdxNeighborTriangles[3]) const;
  virtual HRESULT GetTriangleNeighborsOfBar(const int  iIdxVertex1,
                                            const int  iIdxVertex2,
                                            int       &oIdxTriangle1,
                                            int       &oIdxTriangle2) const;
  virtual HRESULT GetTriangleNeighborsOfBar(const int     iIdxVertex1,
                                            const int     iIdxVertex2,
                                            CATListOfInt &ioIdxTriangles) const;
  virtual CATBoolean IsBarValid(const int iIdxVertex1,
                                const int iIdxVertex2) const;
  virtual HRESULT GetBar(const int iIdxTriangle0,
                         const int iIdxTriangle1,
                         int & oIdxVertex0,
                         int & oIdxVertex1,
                         int & oNbBars) const;
  virtual CATBoolean IsVertexManifold(const int iIdxVertex) const;
  virtual CATBoolean IsBarManifold(const int iIdxVertex0, const int iIdxVertex1) const;
  virtual CATBoolean IsHoleVertex(const int iIdxVertex) const;
  virtual CATBoolean IsHoleBar(const int iIdxVertex0, const int iIdxVertex1) const;

  // Modifiers
 private:
  virtual HRESULT UpdateTriangle(const int iIdxTriangle,
                                 const int iIdxVertices[3]);
  virtual HRESULT FlipBar(const int iIdxVertex1,
                          const int iIdxVertex2);
  virtual HRESULT SplitBar(const int v0, const int v1, int &n);
  virtual HRESULT MergeVertices(const int v0, const int v1);

  // Storage services
 private:
  virtual HRESULT Compact();
  virtual HRESULT Compact(int* &ioIdxVertices,
                          int* &ioIdxTriangles);
  virtual HRESULT Reserve(int iNbVertices, int iNbTriangles);

  // Visitors
 private:
  virtual HRESULT Accept(const CATIPolySurface&iM, CATPolySurfaceConstVisitor &iV) const;
  virtual HRESULT Accept(CATIPolySurface &iM, CATPolySurfaceVisitor &iV);

  // Deprecated methods
 private:
  virtual HRESULT AddTriangle(const int  iIdxVertices[3],
                              int       &oIdxTriangle,
                              const int  iIdxFace);
  virtual HRESULT GetFaceFromTriangle(const int  iIdxTriangle,
                                      int       &oIdxFace) const;
  virtual HRESULT GetTrianglesFromFace(const int     iIdxFace,
                                       CATListOfInt &oIdxTriangles) const;
  virtual HRESULT EndModification();
  virtual HRESULT AddVertices(const int     iNbVertices,
                              const float*  iPoints,
                              int          &oFirstIndex);
  virtual HRESULT GetVertices(CATListOfInt &oIdxVertices) const;
  virtual HRESULT RemoveVertices(const CATListOfInt &iIdxVertices);

  virtual HRESULT AddTriangles(const int     iNbVertices,
                               const double* iCoords,
                               const int     iNbTriangles,
                               const int*    iIdxVertices,
                               const int     iIdxFace);
  virtual HRESULT AddTriangles(const int           iNbVertices,
                               const CATMathPoint* iPoints,
                               const int           iNbTriangles,
                               const int*          iIdxVertices,
                               const int           iIdxFace);
  virtual HRESULT GetTriangles(CATListOfInt &oIdxTriangles) const;
  virtual HRESULT GetTriangles(int     &oNbVertices,
                               double* &ioCoords,
                               int     &oNbTriangles,
                               int*    &ioIdxVertices) const;
  virtual HRESULT GetTriangles(int           &oNbVertices,
                               CATMathPoint* &ioPoints,
                               int           &oNbTriangles,
                               int*          &ioIdxVertices) const;
  virtual HRESULT RemoveTriangles(const CATListOfInt &iIdxTriangles,
                                  const CATBoolean iRemoveUnreferencedVertices = FALSE);
  virtual HRESULT PropagateOrientation(const int iIdxTriangle,
                                       const CATIPolyMesh::Orientation iOrientation = O_Direct,
                                       const CATBoolean iInvert = FALSE);
  virtual HRESULT InvertTriangle(const int iIdxTriangle);
  virtual HRESULT RegisterVertexAttribute(CATPolyAttribute* iAttribute);
  virtual CATPolyAttribute* GetVertexAttribute(const CATPolyAttributeID id) const;
};

#endif // !CATPolyRawBuffersMesh_H
