// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriQuadMeshBase.h
//
//===================================================================
// September 2018  Creation: NDO
//===================================================================
#ifndef CATPolyTriQuadMeshBase_H
#define CATPolyTriQuadMeshBase_H

#include "PolyhedralModel.h"
#include "CATIPolyTriQuadMesh.h"

class CATMathBox;

/**
Class providing a default implementation to an editable CATIPolyTriQuadMesh.
All (editable) CATIPolyTriQuadMesh implementations can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolyTriQuadMeshBase : public CATIPolyTriQuadMesh
{

public:

  CATPolyTriQuadMeshBase () {}
  virtual ~CATPolyTriQuadMeshBase ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbVertices () const;
  virtual HRESULT AddVertex (int &v);
  virtual HRESULT AddVertex (const CATMathPoint &P, int &v);
  virtual HRESULT RemoveVertex (const int v);

  virtual int GetNbTriangles () const;
  virtual HRESULT GetTriangle (const int t, int &v0, int &v1, int &v2) const;
  virtual HRESULT AddTriangle (const int v0, const int v1, const int v2, int &t);
  virtual HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

  virtual int GetNbQuads () const;
  virtual HRESULT GetQuad (const int q, int &v0, int &v1, int &v2, int &v3) const;
  virtual HRESULT AddQuad (const int v0, const int v1, const int v2, const int v3, int &q);
  virtual HRESULT RemoveQuad (const int q, const CATBoolean iRemoveUnreferencedVertices = FALSE);

  virtual int GetNbFacets () const;
  virtual HRESULT GetFacet (const int f, CATListOfInt &oVertices) const;
  virtual HRESULT RemoveFacet (const int f);

  virtual HRESULT MergeVertices (const int v0, const int v1);
  virtual HRESULT SplitBar (const int v0, const int v1, int &n);
  virtual HRESULT MergeTrianglesIntoQuad (const int t0, const int t1, int &q);
  virtual HRESULT SplitQuadIntoTriangles (const int q, int &t0, int &t1, CATBoolean MakeEvenDiagonal = TRUE);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const;
  virtual HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

  virtual HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  virtual HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;
  virtual HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const;

  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;
  virtual bool HasLayer (const CLSID& id) const;
  virtual HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;
  virtual HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

  virtual HRESULT GetSupport (CATIPolySurfaceSupport*& oSupport) const;

  virtual HRESULT GetBoundingBox (CATMathBox &oBBox) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer *&oLayer);
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer *&oLayer);
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVLayer *&oLayer);
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordLayer *&oLayer);
  virtual HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentLayer *&oLayer);
  
  virtual HRESULT AddLayer (CATIPolyLayer& oLayer, CATIPolySurfaceObserver* obs = 0);
  virtual HRESULT RemoveLayer (CATIPolyLayer& oLayer);

  virtual HRESULT SetSupport (CATIPolySurfaceSupport* iSupport);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT RegisterObserver (CATIPolySurfaceObserver &iObserver);
  virtual HRESULT UnregisterObserver (CATIPolySurfaceObserver &iObserver);

  virtual HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;
  virtual HRESULT Accept (CATIPolySurface &iS, CATPolySurfaceVisitor& iV);

  virtual CATIPolySurfaceConstTools* GetConstTools () const;
  virtual CATIPolySurfaceTools* GetTools ();

/** @} */

public:

/** @name Methods implemented in this class. There is no need to override these methods.
    @{ */

  int GetMaxFacetSize () const;
  CATBoolean IsEditable () const;

/** @} */

};

#endif // !CATPolyTriQuadMeshBase_H
