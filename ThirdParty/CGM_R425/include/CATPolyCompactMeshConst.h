// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCompactMeshConst.h
//
//===================================================================
// May 2016  Creation: NDO
//===================================================================
#ifndef CATPolyCompactMeshConst_H
#define CATPolyCompactMeshConst_H

#include "PolyMeshImpl.h"
#include "CATPolyMeshBaseConst.h"
#include "CATMathBox.h"
#include "CATBoolean.h"
#include "CATMutex.h"

class CATPolyCompactMesh;
class CATIPolyVertexFloatPositionConstLayer;
class CATIPolyVertexFloatNormalConstLayer;
class CATPolyLayerContainer;
class CATMathPoint;
class CATPolyCompactMeshVertexPositionLayerBase;
class CATPolyCompactMeshVertexNormalLayer;


/**
 * Implementation of a triangular mesh as simple contiguous arrays of vertices and triangles.
 * An instance of a CATPolyCompactMeshConst is not editable.
 * 
 * @see CATPolyCompactMesh
 */
class ExportedByPolyMeshImpl CATPolyCompactMeshConst : public CATPolyMeshBaseConst
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an empty instance.
   * The instance must be filled with the help of the methods Initialize () and Finalize ().
   */
  static CATPolyCompactMeshConst* New ();

  /** 
   * Initializes an instance of an editable mesh (CATPolyCompactMesh) that can be filled with the data.
   * After completion of the mesh, the method Finalize () must be called with the same mesh instance.
   * The call to Finalize completes the construction of the compact mesh which can no longer be edited.
   * The vertex position is in float or double precision.
   * The optional vertex-normal layer is in float precision.
   * The optional vertex-UV layer is in double precision.
   * @param iFloatOrDouble
   *   Precision of the vertex-position layer: CATIPolyObject::eFloat or CATIPolyObject::eDouble.
   * @param iNbVerticesToAllocate
   *  The number of vertices that will be initially allocated for the mesh.
   * @param iNbTrianglesToAllocate
   *  The number of triangles that will be initially allocated for the mesh.
   * @param iWithVertexNormalLayer
   *   Optional vertex-normal layer.
   * @param iWithVertexUVLayer
   *   Optional vertex-UV layer.
   * @return 
   *   A new CATIPolyMesh instance or 0 on memory allocation failure.
   *   This instance is to be filled with the data prior to the call to Finalize ().
   *   Do not release the instance returned.
   */
#ifndef _AIX_SOURCE
  CATPolyCompactMesh* Initialize (Poly::Precision iFloatOrDouble, int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#else
  CATPolyCompactMesh* Initialize (PrecisionVertexPosition iFloatOrDouble, int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#endif
  /** 
   * Completes the construction of a CATPolyCompactMeshConst.
   * @param iMesh
   *   The editable mesh that was returned by the method Initialize.
   *   The editable mesh becomes invalid and is released after this call.
   */
  HRESULT Finalize (CATPolyCompactMesh*& iMesh);

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolySurface as a const CATPolyCompactMeshConst.
   */
  static const CATPolyCompactMeshConst* Cast (const CATIPolySurface* iSurface);

  /**
   * Casts a CATIPolySurface as a CATPolyCompactMeshConst.
   */
  static CATPolyCompactMeshConst* Cast (CATIPolySurface* iSurface);

/** @} */

public:

/** @name Vertices 
    @{ */

  int GetNbVertices () const;

/** @} */

public:

/** @name Triangles 
    @{ */

  int GetNbFacets () const;
  int GetNbTriangles () const;

  HRESULT GetTriangle (const int t, int oVertices[3]) const;

/** @} */

public:

/** @name Iterators
    @{ */

  HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const;

  HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

  HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator *&oIterator) const;
  HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator *&oIterator) const;

/** @} */

public:

/** @name Neighborhood
    @{ */

 /**
  * @param oNeighborhood [out, CATPolyRefCounted#Release]
  */
  HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

/** @} */

public:

/** @name Const Layers
    @{ */

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;

  HRESULT GetBoundingBox (CATMathBox &oBBox) const;

  /**
   * Returns the native vertex position layer.
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer*& oLayer) const;

  /**
   * Returns the native vertex normal layer.
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolyVertexFloatNormalConstLayer*& oLayer) const;

/** @} */

public:

/** @name Data Layers
@{ */

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolySurfaceObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

/** @} */

public:

/** @name Visitors
    @{ */

  HRESULT Accept (const CATIPolySurface &iM, CATPolySurfaceConstVisitor &iV) const;

/** @} */

public:

/** @name Tools. 
    @{ */

  CATIPolySurfaceConstTools* GetConstTools () const;

/** @} */

public:

  /**
   * Returns the native surface support.  
   * Do not delete the support that is returned.
   */
  inline CATIPolySurfaceSupport* GetNativeSupport () const;

  /**
   * Returns the size of the instance in memory in bytes.
   */
  unsigned int SizeOf () const;

public:

  inline CATBoolean FinalIsVertexDefined (int v) const {return 0 < v && v <= CATPolyCompactMeshConst::GetNbVertices ();}

  inline int FinalGetNbVertices() const {return CATPolyCompactMeshConst::GetNbVertices ();}

  inline int FinalGetNbTriangles() const {return _NbTriangles; }

private:

  mutable CATMathBox _BoundingBox;

  mutable unsigned int _Flags;  // Bit flags: see CATPolyCompactMesh

  int _NbTriangles;
  int* _Triangles;

private:

  CATPolyCompactMeshVertexPositionLayerBase* _PositionLayer;
  float* _VerticesNormals;
  CATPolyLayerContainer* _DataLayers;
  union
  {
    CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;  // Cache.
    CATPolyCompactMesh* _InitMesh;  // Temporary mesh used for the initialization.
  };
  CATMutex & GetMutex() const;

private:

  friend class CATPolyCompactMeshVertexNormalLayer;

  friend class CompactMeshConstVertexNormalConstLayer;
  friend class CompactMeshConstVertexFloatNormalConstLayer;

private:

  // Protected constructor.
  // Use static New methods.
  CATPolyCompactMeshConst ();

  virtual ~CATPolyCompactMeshConst ();

  void AbsorbNormalLayer (CATPolyCompactMeshVertexNormalLayer& layer);

public:

  //
  // Obsolete.
  // Should not be using these methods. Use instead layers, iterators, neighborhoods and services.
  //

  HRESULT GetVertexPosition (const int v, CATMathPoint &P) const;

  CATBoolean IsVertexDefined (const int v) const;
  int GetMinVertexIndex () const;
  int GetMaxVertexIndex () const;

  CATBoolean IsTriangleDefined (const int t) const;
  int GetMinTriangleIndex () const;
  int GetMaxTriangleIndex () const;

  HRESULT GetFacet (const int f, CATListOfInt &oVertices) const;

  HRESULT GetTrianglePoints (const int t,
                             CATMathPoint &P1, CATMathPoint &P2, CATMathPoint &P3) const;

};

inline CATIPolySurfaceSupport* CATPolyCompactMeshConst::GetNativeSupport () const
{
  return GetASupport ();
}

#endif // #ifndef CATPolyCompactMeshConst_H
