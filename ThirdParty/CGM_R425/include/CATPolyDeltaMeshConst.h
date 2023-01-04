// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDeltaMeshConst.h
//
//===================================================================
// Feb 2021 F1Z : Creation
//===================================================================

#pragma once

// System&co
#include "CATMutex.h"

// PolyhedralMathematics
#include "Poly/Vector.h"
#include "Poly/Array.h"
#include "CATMapOfIntToInt.h"

// PolyhedralInterfaces
#include "Poly/Iterator.h"

#include "CATIPolyObject.h"
#include "CATIPolyMeshTriangleIterator.h"
#include "CATIPolySurfaceVertexIterator.h"

// PolyhedralObjects
#include "PolyMeshImpl.h"
#include "CATPolyMeshBaseConst.h"

// std
#include <algorithm>
#include <utility>

class CATIPolyMeshTriangleVertexIterator;
class CATIPolyMeshTriangleIterator;
class CATIPolySurfaceFacetIterator;
class CATPolyLayerContainer;
class CATPolyDeltaMeshBase;
class CATPolyEditableMesh;
class CATPolyDeltaMeshKeep;
class CATPolyDeltaMeshRemove;

/**
* Implementation of a triangular mesh that is the delta of another mesh (base mesh)
* An instance of a CATPolyDeltaMeshConst is not editable and has compact indices.
*
* @see CATPolyEditableMesh for the editable version.
*/
class ExportedByPolyMeshImpl CATPolyDeltaMeshConst : public CATPolyMeshBaseConst
{
public:
  template<typename>
  class PositionLayer;
  template<typename>
  class NormalLayer;
  class UVLayer;

  typedef CATPolyDeltaMeshKeep DeltaKeep;
  typedef CATPolyDeltaMeshRemove DeltaRemove;
public:
  /** @name Life Cycle
  @{ */

  /**
  * Creates an instance of a delta mesh const with delta information.
  * @iDelta
  *  The delta information. The parent mesh must be not editable in order to create a CATPolyDeltaMeshConst.
  * @oMapSvToNSv
  *  The mapping between the id of iDelta mesh and this mesh
  * @oMapIdTToNIdT
  *  The mapping between the id of iDelta mesh and this mesh
  */
  static CATPolyDeltaMeshConst* New(CATPolyDeltaMeshBase & iDelta,
                                    CATMapOfIntToInt * oMapSvToNSv = NULL,
                                    CATMapOfIntToInt * oMapIdTToNIdT = NULL);

  /**
  * Creates an instance of a delta mesh const with delta information.
  * @param iToExtract
  *  The editable mesh where the delta information needs to be extracted.
  *  The parent (or origin parent) mesh must be not editable in order to create a CATPolyDeltaMeshConst.
  * @param iExtractToOriginParent
  *  Retrieve the origin mesh that is not a delta kind of mesh.
  * @param iFlip
  *  Extract the flipped content of the editable mesh
  */
  static CATPolyDeltaMeshConst* New(const CATPolyEditableMesh & iToExtract,
                                    bool iExtractToOriginParent,
                                    CATMapOfIntToInt & oMapSvToNSv,
                                    CATMapOfIntToInt * oMapIdToNIdT = NULL,
                                    bool iFlip=false);

  /**
  * Creates an empty instance of a delta mesh.
  * Use @Absorb or @Extract method to initialize the delta mesh const
  */
  static CATPolyDeltaMeshConst* New(const CATIPolyMesh & iParentMesh);

  /**
   * Return E_FAIL if the mesh parent isn't the same.
   * Return E_FAIL if the mesh was already initialized (one call to absorb/extract possible, only from New without delta)
   * @oMapSvToNSv
   *  The mapping between the id of iDelta mesh and this mesh
   * @oMapIdTToNIdT
   *  The mapping between the id of iDelta mesh and this mesh
   */
  HRESULT Absorb(CATPolyDeltaMeshBase & iDelta,
                 CATMapOfIntToInt & oMapSvToNSv,
                 CATMapOfIntToInt * oMapIdTToNIdT=NULL);

  /**
  * @param iFlip
  *  Extract the flipped content of the editable mesh
  * @oMapSvToNSv
  *  The mapping between the id of iDelta mesh and this mesh
  * @oMapIdTToNIdT
  *  The mapping between the id of iDelta mesh and this mesh
  */
  HRESULT Extract(const CATPolyEditableMesh & iToExtract,
                  bool iExtractToOriginParent,
                  CATMapOfIntToInt & oMapSvToNSv,
                  CATMapOfIntToInt * oMapIdToNIdT = NULL,
                  bool iFlip=false);


  ~CATPolyDeltaMeshConst();

  /** @} */

public:

  /** @name Vertices Management
  @{ */

  int GetNbVertices() const;

  /** @} */

public:

  /** @name Triangles Management
  @{ */

  int GetNbFacets() const;
  int GetNbTriangles() const;

  HRESULT GetTriangle(const int t, int oVertices[]) const;

  /** @} */

public:
  /** @name Iterators.
  @{ */

  Poly::Iterator<int> GetVertexAddedIterator() const;
  Poly::Iterator<int> GetVertexKeptIterator(bool iGetNewId=false) const;
  HRESULT GetVertexIterator(CATIPolySurfaceVertexIterator*& oIterator) const;

  Poly::Iterator<int> GetTriangleAddedIterator() const;
  Poly::Iterator<int> GetTriangleKeptIterator(bool iGetNewId = false) const;
  HRESULT GetFacetIterator(CATIPolySurfaceFacetIterator*& oIterator) const;

  HRESULT GetTriangleIterator(CATIPolyMeshTriangleIterator*& oIterator) const;
  HRESULT GetTriangleIterator(CATIPolyMeshTriangleVertexIterator*& oIterator) const;

  /**
  * Returns true if the triangles (and normals) from the parent mesh have been flipped.
  * The indices from the parent triangles do not change when a flip occurs.
  */
  inline bool AreParentTrianglesInverted() const { return _parentTrianglesInverted; };
  bool AreParentNormalsInverted() const;

  /** @} */


public:
  /** @name Method specific to this mesh implementation.
  @{ */

  /**
   *  Return the parent mesh
   */
  inline const CATIPolyMesh & GetParentMesh() const { return _baseMesh; };

  /**
  * If compact, then return the number of parent element kept but with different id
  */
  unsigned int GetNbVerticesKeptIdChange() const;

  /**
* If compact, then return the number of parent element kept but with different id
*/
  unsigned int GetNbTrianglesKeptIdChange() const;

  /**
  * Return trie if the id belongs to the parent mesh and false if it is a new id
  * The id of the parent might be different
  */
  bool IsParentVertex(int iId, int * oParentId=NULL) const;

  /**
   * @param iParentVertexId
   *  The vertex indice of the delta mesh parent
   * @return
   *  The indice of the same vertex on the delta mesh. Return 0 if the vertex is not part of the delta mesh (was removed)
   */
  int GetNewParentVertexIndice(int iParentVertexId) const;

  /**
* Return trie if the id belongs to the parent mesh and false if it is a new id
* The id of the parent might be different
*/
  bool IsParentTriangle(int iId, int * oParentId=NULL) const;

  /**
 * @param iParentTriangleId
 *  The triangle indice of the delta mesh parent
 * @return
 *  The indice of the same triangle on the delta mesh. Return 0 if the triangle is not part of the delta mesh (was removed)
 */
  int GetNewParentTriangleIndice(int iParentTriangleId) const;


  /**
  * If the input argument is a new vertex, then it returns a value within
  * a compact range from GetNewVerticesOffset+1 to GetNbVertices () - 1.
  */
  unsigned int GetNewVerticesOffset() const;

  /**
  * If the input argument is a new triangle, then it returns a value within
  * a compact range from GetNewTrianglesOffset()+1 to GetNbTriangles () - 1.
  */
  unsigned int GetNewTrianglesOffset() const;

  /**
  * Get the number of vertices that are kept
  */
  unsigned int GetNbVerticesKept() const;

  /**
  * Get the number of triangles that are kept
  */
  unsigned int GetNbTrianglesKept() const;

  /**
 * Get the number of vertices that are removed
 */
  unsigned int GetNbVerticesRemoved() const;

  /**
 * Get the number of triangles that are removed
 */
  unsigned int GetNbTrianglesRemoved() const;

  /**
  * Get the number of vertices that are added
  */
  unsigned int GetNbVerticesAdded() const;

  /**
  * Get the number of triangles that are added
  */ 
  unsigned int GetNbTrianglesAdded() const;

 /**
  * Return True if it has a position layer
  * Useful to avoid taking care of the addref/release
  */
  bool HasPositionLayer() const;
  bool HasNormalLayer() const;
  bool HasUVLayer() const;

  /**
   * Return True if it has a delta at the position layer
   * If no delta position, return false, the position layer is the parent one
   * Useful for stream/unstream for instance for stream optimisation
   */
  bool HasDeltaPositionLayer() const;

  /**
  * Return True if it has a delta at the normal layer
  * If no delta normal, return false, the normal layer is the parent one
  * Useful for stream/unstream for instance for stream optimisation
  */
  bool HasDeltaNormalLayer() const;

  /**
  * Return True if it has a delta at the uv layer
  * If no delta uv, return false, the uv layer is the parent one
  * Useful for stream/unstream for instance for stream optimisation
  */
  bool HasDeltaUVLayer() const;

  /**
  * Return position layer directly
  */
  CATIPolySurfaceVertexPositionConstLayer * GetVertexPositionLayer() const;

  /**
  * Return normal layer directly
  */
  CATIPolySurfaceVertexNormalConstLayer * GetVertexNormalLayer() const;

  /**
  * Return uv layer directly
  */
  CATIPolySurfaceVertexUVConstLayer * GetVertexUVLayer() const;

  /** @} */

public:
  /** @name Virtual methods to be overriden in a derived class.
  @{ */

  HRESULT GetVertexPositionLayer(CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;

  HRESULT GetBoundingBox(CATMathBox &oBBox) const;

  /** @} */

public:

  /** @name Neighborhood
  @{ */

  /**
  * @param oNeighborhood [out, CATPolyRefCounted#Release]
  */
  HRESULT GetVertexFacetNeighborhood(CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  /** @} */

public:

  /** @name Data Layers
  @{ */

  HRESULT AddLayer(CATIPolyLayer& iLayer, CATIPolySurfaceObserver* obs = 0);

  HRESULT RemoveLayer(CATIPolyLayer& iLayer);

  /**
  * @param oLayer [out, IUnknown#Release]
  */
  HRESULT GetLayer(const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer(const CLSID& id) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  */
  HRESULT GetLayerIterator(const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  */
  HRESULT GetLayerIterator(CATIPolyLayerIterator*& oLayerIterator) const;

  /** @} */

public:
  /** @name Casting Methods.
  @{ */

  /**
  * Casts a const CATIPolySurface as a const CATPolyDeltaMeshConst.
  */
  static const CATPolyDeltaMeshConst* Cast(const CATIPolySurface* iSurface);

  HRESULT Accept(const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;

  /** @} */


private:
  template<typename>
  friend class PositionLayer;
  template<typename>
  friend class NormalLayer;
  friend class UVLayer;
  friend class TriangleIterator;

private:
  CATMutex & GetMutex() const;

  class ParentToCompactId
  {
  public:
    ParentToCompactId();
    ~ParentToCompactId();

    void Initialisation(int iNbElementKept, int iNbElementsInMap, int iMaxIdParentKept, bool iIsParentCompact);
    HRESULT Insert(int iKey, int iData);
    int operator[](int iKey) const;
    int Size() const;

  private:
    CATMapOfIntToInt * _mapIdParentToIdKept;
    PolyVector<int> * _idParentToidKept;
    int _nbElementsKept;
  };

  const CATIPolyMesh & _baseMesh;

  PolyVector<int> _vKept;
  ParentToCompactId _idVParentToIdVKept;
  PolyVector<int> _tKept;
  ParentToCompactId _idTParentToIdTKept;

  int _newTrianglesOffset;
  int _newVerticesOffset;

  PolyVector<Poly::Array<int, 3> > _tAdded; /// Local indice is 1..NbTriAdded. Real mesh indice is _minNewTriangleId+idLocal
  unsigned int _nbVerticesAdded; /// Added vertices local id go from 1 to _nbVerticesAdded, no storage needed since the edition is frozen.
                                 /// Real mesh indice is _minNewVerticesId+idLocal

  /// Layers
  unsigned int _layerType; /// Still needed in case of delta with no new element, we can't logically deduce if we should get the parent layer or nothing.
  CATIPolySurfaceVertexPositionConstLayer * _pPosLayer;
  CATIPolySurfaceVertexNormalConstLayer * _pNormalLayer;
  UVLayer * _pUVLayer;
  CATPolyLayerContainer *_pDataLayers;
  mutable CATIPolySurfaceVertexFacetNeighborhood * _pNeighborhood;

  /// Mode
  bool _parentTrianglesInverted;

  /// Please, note we support any kind of delta, even a delta without element kept...

private:
  void AbsorbBase(CATPolyDeltaMeshBase & iDeltaBase, CATMapOfIntToInt & oMapSVToNSV, CATMapOfIntToInt * oMapTToNT);
  void AbsorbAndCompactDelta(CATPolyDeltaMeshBase & iDelta, CATMapOfIntToInt & oMapSVToNSV, CATMapOfIntToInt * oMapTToNT);
  void AbsorbNonCompact(CATPolyDeltaMeshBase & iDelta, CATMapOfIntToInt & oMapSVToNSV, CATMapOfIntToInt * oMapTToNT);

  CATPolyDeltaMeshConst(const CATIPolyMesh & iParentMesh);

  void ExtractDeltaVertex(const CATPolyEditableMesh & iToExtract,
                          bool iExtractToOriginParent,
                          CATMapOfIntToInt & oMapSVToNSV);
  void ExtractDeltaTriangle(const CATPolyEditableMesh & iToExtract,
                            bool iExtractToOriginParent,
                            const CATMapOfIntToInt & iMapSVToNSV,
                            CATMapOfIntToInt * oMapOfIdTToNIdT,
                            bool iFlip);
};
