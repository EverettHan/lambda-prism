// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshBase.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATPolyMeshBase_H
#define CATPolyMeshBase_H

#include "PolyhedralModel.h"
#include "CATIPolyMesh.h"


/**
Class providing a default implementation to an editable CATIPolyMesh.
All (editable) CATIPolyMesh implementations can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
@see CATPolyMeshBaseConst
*/
class ExportedByPolyhedralModel CATPolyMeshBase : public CATIPolyMesh
{

public:

  CATPolyMeshBase () {}
  virtual ~CATPolyMeshBase ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbVertices () const;

  virtual HRESULT AddVertex (int &oIdxVertex);
  virtual HRESULT AddVertex (const CATMathPoint &iPoint, int &oIdxVertex);
  virtual HRESULT RemoveVertex (const int iIdxVertex);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbFacets () const;
  virtual int GetNbTriangles () const;

  virtual HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3]) const;

  virtual HRESULT AddTriangle (const int  iIdxVertices[3], int &oIdxTriangle);
  virtual HRESULT RemoveTriangle (const int iIdxTriangle, const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const;

  virtual HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

  virtual HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator*& oIterator) const;
  virtual HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator*& oIterator) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  virtual HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  virtual HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  virtual HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;
  virtual HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  virtual bool HasLayer (const CLSID& id) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
  virtual HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
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

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT SetSupport (CATIPolySurfaceSupport* iSupport);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT FlipBar (const int v0, const int v1);
  virtual HRESULT SplitBar (const int v0, const int v1, int &n);
  virtual HRESULT MergeVertices (const int v0, const int v1);
  
/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT Compact ();
  virtual HRESULT Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap);
  virtual HRESULT Reserve (int iNbVertices, int iNbTriangles);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT RegisterObserver (CATIPolySurfaceObserver &iObserver);
  virtual HRESULT UnregisterObserver (CATIPolySurfaceObserver &iObserver);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;
  virtual HRESULT Accept (CATIPolySurface &iS, CATPolySurfaceVisitor& iV);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual CATIPolySurfaceConstTools* GetConstTools () const;
  virtual CATIPolySurfaceTools* GetTools ();

/** @} */

public:

/** @name Methods implemented in this class. There is no need to override these methods.
    @{ */

  int GetMaxFacetSize () const;
  CATBoolean IsEditable () const;

/** @} */

protected:

  // No AddRef () on returned object.
  CATIPolySurfaceSupport* GetASupport () const;

};

#endif // !CATPolyMeshBase_H
