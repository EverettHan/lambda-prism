// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshBaseConst.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATPolyMeshBaseConst_H
#define CATPolyMeshBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolyMesh.h"


/**
Class providing a default implementation to a non-editable CATIPolyMesh.
All CATIPolyMesh adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolyMeshBaseConst : public CATIPolyMesh
{

public:

  CATPolyMeshBaseConst () {}
  virtual ~CATPolyMeshBaseConst ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbVertices () const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbFacets () const;
  virtual int GetNbTriangles () const;

  virtual HRESULT GetTriangle (const int iIdxTriangle, int oIdxVertices[3]) const;

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

  virtual HRESULT AddLayer (CATIPolyLayer& oLayer, CATIPolySurfaceObserver* obs = 0);
  virtual HRESULT RemoveLayer (CATIPolyLayer& oLayer);

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

  virtual HRESULT Accept (const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;
  virtual HRESULT Accept (CATIPolySurface &iS, CATPolySurfaceVisitor& iV);  // Needs to be virtual (for CATPolyFace visitor.)

/** @} */

public:

/** @name Virtual methods that may be overriden in a derived class for customization of the tools.
    @{ */

  virtual CATIPolySurfaceConstTools* GetConstTools () const;
  virtual CATIPolySurfaceTools* GetTools ();

/** @} */

public:

/** @name Methods implemented in this class.
    No need to override these methods.
    @{ */

  int GetMaxFacetSize () const;
  CATBoolean IsEditable () const;

/** @} */

public:

/** @name Methods returning E_FAIL if called.
    Do not override these methods.
    @{ */

  HRESULT AddVertex (int &oIdxVertex);
  HRESULT AddVertex (const CATMathPoint &iPoint, int &oIdxVertex);
  HRESULT RemoveVertex (const int iIdxVertex);

  HRESULT AddTriangle (const int  iIdxVertices[3], int &oIdxTriangle);
  HRESULT RemoveTriangle (const int iIdxTriangle, const CATBoolean iRemoveUnreferencedVertices = FALSE);

  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer *&oLayer);
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer *&oLayer);
  HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVLayer *&oLayer);
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordLayer *&oLayer);
  HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentLayer *&oLayer);
  
  HRESULT SetSupport (CATIPolySurfaceSupport* iSupport);

  HRESULT FlipBar (const int v0, const int v1);
  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);
  
  HRESULT Compact ();
  HRESULT Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap);
  HRESULT Reserve (int iNbVertices, int iNbTriangles);

/** @} */

public:

/** @name Methods returning S_FALSE if called.
    Do not override these methods.
    @{ */

  virtual HRESULT RegisterObserver (CATIPolySurfaceObserver &iObserver);
  virtual HRESULT UnregisterObserver (CATIPolySurfaceObserver &iObserver);

/** @} */

protected:

  // No AddRef () on returned object.
  CATIPolySurfaceSupport* GetASupport () const;

};

#endif // !CATPolyMeshBaseConst_H
