//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyCompactMesh.h
//
//=============================================================================
// 2007-04-19   BPG: New.
// November 2011   Revisited: NDO
// October 2014   JXO: Observers
// August 2015  NDO: Renamed from CATPolyPreAllocatedMesh, 
//                   Compact mesh with vertex position layer in double precision.
// May 2019  JXO: CATUnicodeString identifier for textures
//=============================================================================
#ifndef CATPolyCompactMesh_H
#define CATPolyCompactMesh_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceObserverList.h"
#include "CATPolyMeshBase.h"
#include "CATMathBox.h"
#include "CATBoolean.h"
#include "CATMutex.h"


class CATIPolyVertexFloatPositionConstLayer;
class CATIPolyVertexFloatNormalConstLayer;
class CATPolyCompactMeshVertexPositionLayerBase;
class CATPolyLayerContainer;
class CATMathPoint;
#include "CATUnicodeString.h"


/**
 * Implementation of a triangular mesh as simple contiguous arrays of vertices and triangles.
 * Instances can resize themselves when adding vertices and triangles if the allocated arrays are too small.
 */
class ExportedByPolyMeshImpl CATPolyCompactMesh : public CATPolyMeshBase
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an instance of a CATPolyCompactMesh with the vertex-position layer in float or double precision.
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
   */
#ifndef _AIX_SOURCE
  static CATPolyCompactMesh* New (Poly::Precision iFloatOrDouble, int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#else
  static CATPolyCompactMesh* New (PrecisionVertexPosition iFloatOrDouble, int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#endif

  /** 
   * Creates an instance of CATPolyCompactMesh.
   * @param iMesh
   *   The input mesh data are copied into the new instance.
   * @return 
   *   A new CATIPolyMesh instance or 0 on memory allocation failure.
   */
  static CATPolyCompactMesh* New (const CATIPolyMesh& iMesh);

  /** 
   * @deprecated
   */
  static CATPolyCompactMesh* New (int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
                                  CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer,
                                  PolyPrecision iFloatOrDouble)
    {return New ((PrecisionVertexPosition) iFloatOrDouble, iNbVerticesToAllocate, iNbTrianglesToAllocate, iWithVertexNormalLayer, iWithVertexUVLayer);}

  /** 
   * @deprecated
   */
  static CATPolyCompactMesh* New (int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
                                  CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer)
    {return New ((PrecisionVertexPosition) Poly::Precision::eFloat, iNbVerticesToAllocate, iNbTrianglesToAllocate, iWithVertexNormalLayer, iWithVertexUVLayer);}

  /**
   * @see Poly::Precision
   */
  typedef PolyPrecision LayerPrecision;

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolySurface as a const CATPolyCompactMesh.
   */
  static const CATPolyCompactMesh* Cast (const CATIPolySurface* iSurface);

  /**
   * Casts a CATIPolySurface as a CATPolyCompactMesh.
   */
  static CATPolyCompactMesh* Cast (CATIPolySurface* iSurface);

/** @} */

public:

/** @name Vertices Management
    @{ */

  int GetNbVertices () const;

  HRESULT AddVertex (int &v);
  HRESULT AddVertex (const CATMathPoint &P, int &v);

  HRESULT RemoveVertex (const int v);

/** @} */

public:

/** @name Triangles Management
    @{ */

  int GetNbFacets () const;
  int GetNbTriangles () const;

  HRESULT GetTriangle (const int t, int oVertices[3]) const;

  HRESULT AddTriangle (const int iVertices[3], int &t);
  HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

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
  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer *&oLayer) const;

  /**
   * Returns the native vertex normal layer.
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolyVertexFloatNormalConstLayer *&oLayer) const;

/** @} */

public:

/** @name Layers
    @{ */

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer *&oLayer);

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer *&oLayer);

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVLayer *&oLayer);

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordLayer *&oLayer);

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

/** @name Adding Normal Layer
    @{ */

  /**
   * Returns TRUE if the mesh has a vertex normal layer.
   */
  inline CATBoolean HasVertexNormalLayer () const;

  /**
   * Adds a vertex normal layer if none is available.
   * This method does not initialize or compute the normals.
   * It is up to the caller to set the normals.
   * @param iUniqueNormal
   *   An argument stating that the normal layer consists of a unique normal if set to <tt>TRUE</tt>
   */
  HRESULT AddVertexNormalLayer (CATBoolean iUniqueNormal = FALSE);

/** @} */

public:

/** @name Adding Texture Layer
    @{ */

  /**
   * Returns TRUE if the mesh has a vertex texture coordinates layer.
   */
  CATBoolean HasVertexTextureCoordLayer () const;

  /**
   * Adds a vertex texture coordinates layer if none is available.
   * This method does not initialize the texture coordinates.
   * It is up to the caller to set the texture coordinates.
   */
  HRESULT AddVertexTextureCoordLayer (const int iDimension = 2, const CATUnicodeString & iTextureIdentifier = "DEFAULT_TC_SET");

/** @} */

public:

/** @name Storage
    @{ */

  HRESULT Compact ();
  HRESULT Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap);
  HRESULT Reserve (int iNbVertices, int iNbTriangles);

/** @} */

public:

/** @name Event Listener. 
    @{ */

  HRESULT RegisterObserver (CATIPolySurfaceObserver& iObserver);

  HRESULT UnregisterObserver (CATIPolySurfaceObserver& iObserver);

/** @} */

public:

/** @name Visitors
    @{ */

  HRESULT Accept (const CATIPolySurface &iM, CATPolySurfaceConstVisitor &iV) const;

  HRESULT Accept (CATIPolySurface &iM, CATPolySurfaceVisitor &iV);

/** @} */

public:

/** @name Tools. 
    @{ */

  CATIPolySurfaceConstTools* GetConstTools () const;
  CATIPolySurfaceTools* GetTools ();

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

  inline CATBoolean FinalIsVertexDefined (int v) const {return 0 < v && v <= CATPolyCompactMesh::GetNbVertices ();}

  int GetNbAllocatedVertices () const;

  inline int FinalGetNbVertices() const {return CATPolyCompactMesh::GetNbVertices ();}

  inline int FinalGetNbTriangles() const {return _NbTriangles; }

  inline int HasUniqueVertexNormal () const {return _Flags & MaskUniqueVertexNormal;}

protected:

  CATMathBox _BoundingBox;

  /**
   * Definition of various bit flags.
   */
  enum Masks
  {
    /** Bit 0: Bounding box ok. */                      MaskBoundingBoxOK      = 0x0001,
    /** Bit 1: Vertex position layer in float. */       MaskVertexFloat        = 0x0002,
    /** Bit 2: Vertex position layer in double. */      MaskVertexDouble       = 0x0004,
    /** Bit 3: Unique vertex normal. */                 MaskUniqueVertexNormal = 0x0008
  };

  unsigned int _Flags;  // Bit flags.

  int _NbTriangles;
  int _NbAllocatedTriangles;

  int* _Triangles;

protected:

  CATPolyCompactMeshVertexPositionLayerBase* _PositionLayer;
  float* _VerticesNormals;
  CATPolyLayerContainer* _DataLayers;

  // Observers.
  CATPolySurfaceObserverList _Observers;
  CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;  // Cache.
  CATMutex & GetMutex() const;

protected:

  friend class CATPolyCompactMeshConst;
  friend class CATPolySurfacePolyFaceConstVisitor;

  friend class CompactMeshVertexNormalLayer;
  friend class CompactMeshVertexNormalConstLayer;
  friend class CompactMeshVertexFloatNormalConstLayer;
  friend class CompactMeshConstVertexNormalConstLayer;
  friend class CompactMeshConstVertexFloatNormalConstLayer;

protected:

  // Protected constructor.
  // Use static New methods.
  CATPolyCompactMesh (PolyPrecision iFloatOrDouble);

  virtual ~CATPolyCompactMesh ();

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT DummyGetVertexCellLayer (CATIPolySurfaceVertexCellConstLayer *&oLayer) const;

private:

  // Memory management.

  HRESULT ReallocateVertexNormals ();
  HRESULT ReallocateDataLayers ();

  HRESULT ReallocateTriangles (const int iNbTrianglesToAllocate);

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

public:

  //
  // Obsolete.
  // Should not be using these methods. Use instead layers, iterators, neighborhoods and services.
  //

  // Do not use this method.
  HRESULT SetVertexPosition(const int v, const CATMathPoint &P);
  void ReactToSetVertexPosition (const int v, const CATMathPoint& P);  // Reserved.
  
  // Do not use this method.
  HRESULT UpdateTriangle(const int t, const int iVertices[3]);

};


inline CATBoolean CATPolyCompactMesh::HasVertexNormalLayer () const
{
  return _VerticesNormals ? TRUE : FALSE;
}


inline CATIPolySurfaceSupport* CATPolyCompactMesh::GetNativeSupport () const
{
  return GetASupport ();
}

#endif // #ifndef CATPolyCompactMesh_H
