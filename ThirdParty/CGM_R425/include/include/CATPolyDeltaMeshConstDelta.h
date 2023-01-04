// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDeltaMesh.h
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
#include "Poly/Set.h"
#include "Poly/TemplateUtils.h"

// PolyhedralInterfaces
#include "Poly/Precision.h"
#include "Poly/LayerType.h"
#include "Poly/Iterator.h"

#include "CATIPolyMesh.h"
#include "CATIPolySurfaceVertexIterator.h"
#include "CATIPolyMesh.h"
#include "CATPolyMeshBase.h"

// PolyhedralObjects
#include "PolyMeshImpl.h"
#include "CATPolyDeltaMeshConst.h"

class CATIPolySurfaceVertexPositionLayer;
class CATIPolySurfaceVertexNormalLayer;
class CATIPolySurfaceVertexUVLayer;

// ==================================================================== //
//                         CATPolyDeltaMeshBase                         //
// ==================================================================== //
/**
* Common implementation for the detlaKeep/deltaRemove
* Inherit for CATIPolyMesh to make some initialization easier, but most of the behavior is not the same.
* and some operation cost a lost (as neighborhood layer)
* use a CATPolyEditableMesh for advanced mesh edition for CATPolyDeltaMeshConst initialisation.
*/
class ExportedByPolyMeshImpl CATPolyDeltaMeshBase : public CATPolyMeshBase
{
public:
  template<typename RealType>
  class PositionLayer;
  template<typename RealType>
  class NormalLayer;
  class UVLayer;

  // Constructor/Destructor
  // -------------------------------------------
protected:
  CATPolyDeltaMeshBase(const CATIPolyMesh & iParentMesh,
                       unsigned int iLayerType = Poly::LayerType::ePosition | Poly::LayerType::eNormal | Poly::LayerType::eUV,
                       int iParentInvertedInfo = 0, /// @see CATPolyDefualtMeshServices::Poly::ParentOrientation
                       PolyPrecision iRealTypePos = Poly::Precision::eDouble,
                       PolyPrecision iRealTypeNormal = Poly::Precision::eFloat);
public:
  virtual ~CATPolyDeltaMeshBase();

  // Parent
  // -------------------------------------------
  inline const CATIPolyMesh & GetParentMesh() const;
  bool IsParentTriangle(int iId, int * oIdParent=NULL) const;
  bool IsParentVertex(int iId, int * oIdParent=NULL) const;
  virtual int GetNewParentVertexIndice(int iParentVertexId) const = 0;
  virtual int GetNewParentTriangleIndice(int iParentTriangleId) const = 0;


  // Layers
  // -------------------------------------------
  CATIPolySurfaceVertexPositionLayer * GetVertexPositionLayer();
  CATIPolySurfaceVertexNormalLayer   * GetVertexNormalLayer();
  CATIPolySurfaceVertexUVLayer       * GetVertexUVLayer();

  CATIPolySurfaceVertexPositionConstLayer * GetVertexPositionLayer() const;
  CATIPolySurfaceVertexNormalConstLayer   * GetVertexNormalLayer() const;
  CATIPolySurfaceVertexUVConstLayer       * GetVertexUVLayer() const;

  HRESULT GetVertexPositionLayer(CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexNormalLayer(CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  HRESULT GetVertexUVLayer(CATIPolySurfaceVertexUVConstLayer *&oLayer) const;

  bool HasDeltaPositionLayer() const;
  bool HasDeltaNormalLayer() const;
  bool HasDeltaUVLayer() const;

  // Neighb
  // -------------------------------------------
  HRESULT GetVertexFacetNeighborhood(CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

  // Add Triangle/Vertex
  // -------------------------------------------
  HRESULT AddTriangle(const int Vertices[3], int& t);
  HRESULT AddVertex(int &v);
  void ReserveNbAddedTriangles(unsigned int iReserveSize);

  inline bool AreParentTrianglesInverted() const { return _parentTrianglesInverted; };
  bool AreParentNormalsInverted() const;
  HRESULT GetTriangle(const int iIdxTriangle, int oIdxVertices[3]) const;

  unsigned int GetNbTrianglesAdded() const;
  unsigned int GetNbVerticesAdded() const;

  // Keep/Remove itf
  // -------------------------------------------
  virtual unsigned int GetNbVerticesKept() const = 0;
  virtual unsigned int GetNbTrianglesKept() const = 0;
  virtual unsigned int GetNbVerticesRemoved() const = 0;
  virtual unsigned int GetNbTrianglesRemoved() const = 0;

  // Iterator Itf
  // -------------------------------------------
  HRESULT GetVertexIterator(CATIPolySurfaceVertexIterator*& oIterator) const;
  HRESULT GetFacetIterator(CATIPolySurfaceFacetIterator*& oIterator) const;
  HRESULT GetTriangleIterator(CATIPolyMeshTriangleIterator*& oIterator) const;
  HRESULT GetTriangleIterator(CATIPolyMeshTriangleVertexIterator*& oIterator) const;

  // General
  inline bool IsCompact() const { return false; };
  inline int GetNbVertices() const { return GetNbVerticesAdded() + GetNbVerticesKept(); };
  inline int GetNbTriangles() const { return GetNbTrianglesAdded() + GetNbTrianglesKept(); };
  inline unsigned int GetNewVerticesOffset() const { return _newVerticesOffset; };
  inline unsigned int GetNewTrianglesOffset() const { return _newTrianglesOffset; };

  Poly::Iterator<int> GetVertexAddedIterator() const;
  virtual Poly::Iterator<int> GetVertexKeptIterator() const = 0;

  Poly::Iterator<int> GetTriangleAddedIterator() const;
  virtual Poly::Iterator<int> GetTriangleKeptIterator() const = 0;

protected:
  const CATIPolyMesh & _parentMesh;
  CATMutex _mutex;

  HRESULT GetTriangleAdded(const int iIdxTriangle, int oIdxVertices[3]) const;

private:
  template<typename>
  friend class PositionLayer;
  template<typename>
  friend class NormalLayer;
  friend class UVLayer;

  friend class CATPolyDeltaMeshConst;

  // Method private
  // -------------------------------------------
  void UpateLayerNewVertices(int iNewID);
  void InitLayers(int iLayerType,
                  bool iNormalInverted,
                  PolyPrecision iRealTypePos = Poly::Precision::eDouble,
                  PolyPrecision iRealTypeNormal = Poly::Precision::eDouble);
  unsigned int GetLayersInfo() const;
  void ComputeOffset();

  // Att private
  // -------------------------------------------
  unsigned int _newTrianglesOffset;
  unsigned int _newVerticesOffset;

  PolyVector<Poly::Array<int,3> > _tAdded;
  unsigned int _nbVerticesAdded;

  CATIPolySurfaceVertexPositionLayer * _pPosLayer;
  CATIPolySurfaceVertexNormalLayer * _pNormalLayer;
  CATIPolySurfaceVertexUVLayer * _puvLayer;

  bool _parentTrianglesInverted;
};

// ==================================================================== //
//                              DeltaKeep                               //
// ==================================================================== //
/**
* Delta base on kept information.
* All the parent element are supposed to be removed
* The delta will be used for the construction of a CATPolyDeltaMeshConst.
* Its interfaces is a bit similar to a CATIPolyMesh, but not its behavior.
*/
class ExportedByPolyMeshImpl CATPolyDeltaMeshKeep : public CATPolyDeltaMeshBase
{
  // Constructor/Destructor
  // -------------------------------------------
public:
  /**
  *@param iFlipTriangle
    *   Flips all the triangles from the mesh.
    *   (CCW triangles become CW and CW triangles become CCW.)
    */
  CATPolyDeltaMeshKeep(const CATIPolyMesh & iParentMesh,
                       int iParentInvertedInfo = 0,  /// @see CATPolyDefualtMeshServices::Poly::ParentOrientation
                       unsigned int iLayerType = Poly::LayerType::ePosition | Poly::LayerType::eNormal | Poly::LayerType::eUV);

  CATPolyDeltaMeshKeep(const CATIPolyMesh & iParentMesh,
                       int iParentInvertedInfo,  /// @see CATPolyDefualtMeshServices::Poly::ParentOrientation
                       PolyPrecision iRealTypePos,
                       PolyPrecision iRealTypeNormal,
                       unsigned int iLayerType = Poly::LayerType::ePosition | Poly::LayerType::eNormal | Poly::LayerType::eUV);

  ~CATPolyDeltaMeshKeep();

  // ElementKept
  // -------------------------------------------
  /**
  * Set iIdT parent id as triangle to keep
  * @param iSetVerticesToKeep
  *   true if the method also has to add the triangle vertices as kept.
  *   false otherwise for performance optimisation if the vertices were already set as kept.
  */
  void SetParentTriangleToKeep(int iIdT, bool iSetVerticesToKeep=true);
  void SetParentVertexToKeep(int iIdV);
  void ReserveNbTrianglesToKeep(unsigned int iReserveSize);
  void ReserveNbVerticesToKeep(unsigned int iReserveSize);

  int GetNewParentVertexIndice(int iParentVertexId) const;
  int GetNewParentTriangleIndice(int iParentTriangleId) const;

  // Iterators
  // -------------------------------------------
  inline const Poly::Set<int> & GetTrianglesKept() const { return _tKeep; };
  inline const Poly::Set<int> & GetVerticesKept() const { return _vKeep; };

  inline unsigned int GetNbVerticesKept() const { return (unsigned int)_vKeep.Size(); };
  inline unsigned int GetNbTrianglesKept() const { return (unsigned int)_tKeep.Size(); };
  inline unsigned int GetNbVerticesRemoved() const { return (unsigned int)(_parentMesh.GetNbVertices()-_vKeep.Size()); };
  inline unsigned int GetNbTrianglesRemoved() const { return (unsigned int)(_parentMesh.GetNbTriangles() - _tKeep.Size()); };

  Poly::Iterator<int> GetVertexKeptIterator() const;
  Poly::Iterator<int> GetTriangleKeptIterator() const;

  // Visitor
  // -------------------------------------------
  HRESULT Accept(const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;

  // Private
  // -------------------------------------------
private:
  friend class CATPolyDeltaMeshConst;
  Poly::Set<int> _tKeep; /// We use a set for fast serach
  Poly::Set<int> _vKeep; /// We use a set for fast search
};

// ==================================================================== //
//                              DeltaRemove                             //
// ==================================================================== //
/**
* Delta base on remove information.
* All the parent elements are supposed to be kept.
* The delta will be used for the construction of a CATPolyDeltaMeshConst.
* Its interface is a bit similar to a CATIPolyMesh, but not its behavior.
*/
class ExportedByPolyMeshImpl CATPolyDeltaMeshRemove : public CATPolyDeltaMeshBase
{
  // Constructor/Destructor
  // -------------------------------------------
public:
  /**
*@param iFlipTriangle
  *   Flips all the triangles from the mesh.
  *   (CCW triangles become CW and CW triangles become CCW.)
  */
  CATPolyDeltaMeshRemove(const CATIPolyMesh & iParentMesh,
                         int iParentInvertedInfo = 0, /// @see CATPolyDefualtMeshServices::Poly::ParentOrientation
                         unsigned int iLayerType = Poly::LayerType::ePosition | Poly::LayerType::eNormal | Poly::LayerType::eUV);

  CATPolyDeltaMeshRemove(const CATIPolyMesh & iParentMesh,
                         int iParentInvertedInfo,
                         PolyPrecision iRealTypePos,
                         PolyPrecision iRealTypeNormal,
                         unsigned int iLayerType = Poly::LayerType::ePosition | Poly::LayerType::eNormal | Poly::LayerType::eUV);

  ~CATPolyDeltaMeshRemove();

  // ElementRemoved
  // -------------------------------------------
  void RemoveParentTriangle(int iIdT);
  void RemoveParentVertex(int iIdV);

  inline unsigned int GetNbVerticesKept() const { return (unsigned int)(_parentMesh.GetNbVertices() - _vRemove.Size()); };
  inline unsigned int GetNbTrianglesKept() const { return (unsigned int)(_parentMesh.GetNbTriangles() - _tRemove.Size());};
  inline unsigned int GetNbVerticesRemoved() const { return (unsigned int)_vRemove.Size(); };
  inline unsigned int GetNbTrianglesRemoved() const { return (unsigned int)_tRemove.Size(); };

  int GetNewParentVertexIndice(int iParentVertexId) const;
  int GetNewParentTriangleIndice(int iParentTriangleId) const;

  // Find
  // -------------------------------------------
  inline bool IsRemovedTriangle(int iIdT) const { return _tRemove.Find(iIdT)!=0; };
  inline bool IsRemovedVertex(int iIdV) const { return _vRemove.Find(iIdV)!=0; };

  // Iterator
  // -------------------------------------------
  Poly::Iterator<int> GetVertexKeptIterator() const;
  Poly::Iterator<int> GetTriangleKeptIterator() const;

  // Visitor
  // -------------------------------------------
  HRESULT Accept(const CATIPolySurface& iS, CATPolySurfaceConstVisitor& iV) const;

  // Private
  // -------------------------------------------
private:
  friend class CATPolyDeltaMeshConst;

  Poly::Set<int> _tRemove;
  Poly::Set<int> _vRemove;
};


const CATIPolyMesh & CATPolyDeltaMeshBase::GetParentMesh() const
{
  return _parentMesh;
}
