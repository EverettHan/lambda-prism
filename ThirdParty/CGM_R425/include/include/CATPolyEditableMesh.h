// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyEditableMesh.h
//
//===================================================================
// September 2013  Creation NDO
//===================================================================
#ifndef CATPolyEditableMesh_H
#define CATPolyEditableMesh_H

#include "PolyMeshImpl.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATPolyMeshBase.h"

#include "CATPolyLayerObserverContainer.h"
#include "CATSetOfInt.h"
#include "CATMapOfIntToInt.h"
#include "CATMutex.h"


class CATPolyEditableMeshVertexPositionLayer;
class CATPolyEditableMeshVertexNormalLayer;
class CATPolyEditableMeshVertexFacetNeighborhood;
class CATPolyFace;


/**
 * Class representing an editable mesh constructed from a constant mesh.
 * An updated mesh consists of a (non-editable) reference mesh and editable fields recording the changes made to the reference mesh.
 * An updated mesh provides an editable view of the reference mesh.
 */
class ExportedByPolyMeshImpl CATPolyEditableMesh : public CATPolyMeshBase
{

public:

/** @name Life Cycle
    @{ */

  /**
   * Constructor of an updated mesh from an existing constant CATIPolyMesh.
   * @param iMesh
   *   The reference mesh.  It is not edited by the methods of this class (const mesh.)
   */
  static CATPolyEditableMesh* New (const CATIPolyMesh& iMesh,
                                   const bool iFlipParentTriangleAndNormal=false);

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
  * Casts a const CATIPolySurface as a const CATPolyEditableMesh.
  */
  static const CATPolyEditableMesh* Cast (const CATIPolySurface* iSurface);

  /**
  * Casts a CATIPolySurface as a CATPolyEditableMesh.
  */
  static CATPolyEditableMesh* Cast (CATIPolySurface* iSurface);

/** @} */

public:

/** @name Vertices Management
    @{ */

  int GetNbVertices () const;

  HRESULT AddVertex (int& v);
  HRESULT AddVertex (const CATMathPoint& iPoint, int& v);
  HRESULT RemoveVertex (const int v);

/** @} */

public:

/** @name Triangles Management
    @{ */

  int GetNbFacets () const;
  int GetNbTriangles () const;

  HRESULT GetTriangle (const int t, int oVertices[]) const;

  HRESULT AddTriangle (const int iVertices[], int& t);
  HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

public:

/** @name Iterators.
    @{ */

  HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator*& oIterator) const; 

  HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator*& oIterator) const;

  HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator*& oIterator) const ;
  HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator*& oIterator) const ;

/** @} */

public:

/** @name Neighborhood
    @{ */

  /**
   * @param oNeighborhood [out, IUnknown#Release] 
   */
  HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood*& oNeighborhood) const;

/** @} */

public:

/** @name Layers
    @{ */

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer*& oLayer);

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer*& oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer*& oLayer);

  /**
   * @param oLayer [out, IUnknown#Release] 
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer*& oLayer) const;

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

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator, bool excludeNonAddedLayers) const;

  /** @} */

public:

/** @name Mesh Topology Events
    @{ */

  //HRESULT FlipBar (const int v0, const int v1);

  HRESULT SplitBar (const int v0, const int v1, int &n);

  HRESULT MergeVertices (const int v0, const int v1);
  
/** @} */

public:

/** @name Bounding box.
    @{ */

  HRESULT GetBoundingBox (CATMathBox& oBBox) const;

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

/** @name Method specific to this mesh implementation. 
    @{ */

  /**
   * Returns the (non-editable) parent mesh.
   */
  inline const CATIPolyMesh& GetParentMesh () const;

  /**
   * Returns true if the vertex is a parent vertex. 
   * A parent vertex may have its position or normal edited.
   */
  inline bool IsParentVertex (const int v) const;

  /**
   * Returns true if the triangle is a parent triangle. 
   * A parent triangle may be flipped in the editable mesh 
   * in which case its index does not change.
   * (It has the same but transposed vertex indices compared to those from the parent triangle.)
   * This method returns true in case of a flipped parent triangle.
   */
  inline bool IsParentTriangle (const int t) const;

  /**
   * Associates to a new triangle a parent triangle (usually a triangle from the reference mesh.)
   * The method returns <tt>S_FALSE</tt> if <tt>t</tt> is from the reference mesh.
   */
  HRESULT SetParentTriangle (const int t, const int iParentTriangle);

  /**
   * Returns the parent triangle associated to a triangle.
   * The method returns the input index if the triangle is from the reference mesh.
   * (Any new triangle in an editable mesh cannot have the same index as a triangle from the reference mesh.)
   */
  int GetParentTriangle (const int t) const;

  /**
   * Returns true if the triangles from the parent mesh have been flipped. 
   * The indices from the parent triangles does not change when a flip occurs.
   */
  inline bool AreParentTrianglesFlipped () const;

  /** 
   * This method returns true if the mesh has been edited:
   * addition or removal of vertices or triangles.
   * Note that the method returns false, if the only change
   * to the mesh is a flip of the parent triangles.
   */
  inline bool IsEdited () const;

public:

  /**
   * Reserves memory before addition of new vertices and triangles.
   * @param nbNewVertices
   *   An estimated number of new vertices that will be added to the mesh.
   * @param nbNewTriangles
   *   An estimated number of new triangles that will be added to the mesh.
   * @return
   *   <tt>S_OK</tt> if the allocation is successful.
   */
  HRESULT Reserve (unsigned int nbNewVertices, unsigned int nNewTriangles);

  /**
   * Returned the number of new vertices.
   */
  unsigned int GetNbNewVertices () const;

  /**
   * Returned the number of new triangles.
   */
  inline unsigned int GetNbNewTriangles () const;

  /**
 * Returned the maximum number of new triangles.
 */
  inline unsigned int GetNbNewTrianglesToAllocate() const { return _NbAllocatedTriangles; };

  /**
   * Applies the offset to the vertex.
   * If the input argument is a new vertex, then it returns a value within
   * a compact range from 0 to GetNbVertices () - 1.
   * If the input argument is an existing vertex, then it returns a value
   * strictly negative.
   * The method can be applied also to recover a vertex value (involution).
   */
  inline int ApplyVertexOffset (const int v) const;

  /**
   * Applies the offset to the triangle.
   * If the input argument is a new triangle, then it returns a value within
   * a compact range from 0 to GetNbTriangles () - 1.
   * If the input argument is an existing triangle, then it returns a value
   * strictly negative.
   * The method can be applied also to recover a triangle value (involution).
   */
  inline int ApplyTriangleOffset (const int t) const;

/** @} */

private:

  const CATIPolyMesh& _Mesh;
  CATIPolyMeshTriangleIterator* _TriangleIterator;  // Help with performance for some implementations (hold the triangles in cache.)

  CATMapOfIntToInt _Vertices;  // Maps a vertex to an index (reserved for layer and neighborhood data.)
  CATSetOfInt _Triangles;

  CATPolyLayerObserverContainer _LayersObservers;  // List of (layer, observer) pairs.

  int* _TriangleData;     // Array of quadruplets of integers: 3 vertices and a reference to a triangle from the parent mesh.

  CATPolyEditableMeshVertexPositionLayer* _PositionLayer;
  CATPolyEditableMeshVertexNormalLayer* _NormalLayer;
  CATPolyEditableMeshVertexFacetNeighborhood* _Neighborhood;

  unsigned int _NbNewTriangles;  // The number of new triangles that have been used in the mesh.
  unsigned int _NbAllocatedTriangles;  // The number of allocated new triangles.
  unsigned int _IncrementTriangles;  // The number of new triangles added during an allocation.
  int _LastUndefinedTriangle;  // For recycling (always negative.)

  int _OffsetVertex;    // Maximum index of a new vertex (always negative).
  int _OffsetTriangle;  // Maximum index of a new triangle (always negative.)

  unsigned int _Flags;  // Various flags.
  static CATMutex _Mutex;

private:

  /**
   * Masks for various flags.
   */
  enum Masks
  {
    /** Bit 0 for edited objects. */                    MaskEdited        = 0x0001,
    /** Bit 1 for flipping triangles. */                MaskFlipTriangles = 0x0002
  };

private:

  // Private constructor (see New ()).
  CATPolyEditableMesh (const CATIPolyMesh& iMesh,
                       const bool iFlipParentTriangleAndNormal);

  // Final class.
  ~CATPolyEditableMesh ();

  void Populate ();
  HRESULT ReallocateTriangleData (const int iNbTrianglesToAllocate);

  void PushUndefinedTriangle (unsigned int ta);
  unsigned int PopUndefinedTriangle ();

  CATIPolySurfaceVertexFacetNeighborhood* MakeVertexFacetNeighborhood ();
  CATIPolySurfaceVertexPositionLayer* MakeVertexPositionLayer ();
  CATIPolySurfaceVertexNormalLayer* MakeVertexNormalLayer ();

  HRESULT FinalAddVertex (int& v);
  HRESULT FinalAddTriangle (const int v[3], int& t);
  HRESULT FinalRemoveTriangle (const int t);

  inline void SetEdited ();

private:

  friend class CATPolyEditableMeshVertexPositionLayer;
  friend class CATPolyEditableMeshVertexNormalLayer;
  friend class CATPolyEditableMeshVertexFacetNeighborhood;
  friend class CATPolyEditableMeshVertexCellLayer;

  /**
   * Reserved for vertex-facet neighborhood.
   * Given a vertex, returns an index as set.
   */
  inline bool GetVertexIndex (const int v, int& i) const;

  // Returns the number of allocated vertices.
  unsigned int GetNbNewVerticesToAllocate () const;

};

inline const CATIPolyMesh& CATPolyEditableMesh::GetParentMesh () const
{
  return _Mesh;
}

inline unsigned int CATPolyEditableMesh::GetNbNewTriangles () const
{
  return _NbNewTriangles;
}

inline int CATPolyEditableMesh::ApplyVertexOffset (const int v) const
{
  return _OffsetVertex - v;
}

inline int CATPolyEditableMesh::ApplyTriangleOffset (const int t) const
{
  return _OffsetTriangle - t;
}

inline bool CATPolyEditableMesh::IsParentVertex (const int v) const
{
  return v > _OffsetVertex;
}

inline bool CATPolyEditableMesh::IsParentTriangle (const int t) const
{
  return t > _OffsetTriangle;
}

inline bool CATPolyEditableMesh::GetVertexIndex (const int v, int& i) const
{
  CATMapOfIntToInt::Handle h = _Vertices.Find (v);
  if (!h)
    return false;
  else
  {
    i = _Vertices.GetData (h);
    return true;
  }
}

inline bool CATPolyEditableMesh::AreParentTrianglesFlipped () const
{
  return _Flags & MaskFlipTriangles ? true : false;
}

inline void CATPolyEditableMesh::SetEdited ()
{
  _Flags |= MaskEdited;
}

inline bool CATPolyEditableMesh::IsEdited () const
{
  return _Flags & MaskEdited ? true : false;
}

#endif
