//=============================================================================
// COPYRIGHT Dassault Systemes 2010
//=============================================================================
//
// CATPolyMeshCopier.cpp
//
//=============================================================================
// 2010-06-20   ZFI: New.
// 2019-05-02   JXO: CopyDataLayers
//=============================================================================
#ifndef CATPolyMeshCopier_H
#define CATPolyMeshCopier_H

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "PolyMeshImpl.h"

class CATMapOfIntToInt;
class CATIPolyMesh;
class CATIPolySurface;
class CATIPolySurfaceVertexLine;
class CATIPolyCurve;
class CATPolyLine;
class CATIPolyPoint;
class CATPolyPoint;
class CATPolyLayerCopier;

class CATMathTransformation;


/**
 * Operator making a copy of the mesh into another mesh.
 */
class ExportedByPolyMeshImpl CATPolyMeshCopier
{

public:

  CATPolyMeshCopier () {}
  ~CATPolyMeshCopier () {}

public:

  /**
   * Copies a mesh into another mesh.
   * @param iSrcMesh
   *   The input CATIPolyMesh.
   * @param ioDstMesh
   *   The CATIPolyMesh whose layers are populated with the input mesh data.
   * @param ioSrcVertexToDstVertexMap
   *   An optional vertex map.  If an empty map is passed as an argument, then, it is filled
   *   by this method.
   * @param ioSrcTriangleToDstTriangleMap
   *   An optional triangle map.  If an empty map is passed as an argument, then, it is filled
   *   by this method.
   * @param iAddVertexIfInTheMap
   *   If true, will add vertex if already found in the provided map, otherwise add a new vertex.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  static HRESULT Copy (const CATIPolyMesh& iSrcMesh,
    CATIPolyMesh& ioDstMesh,
    CATMapOfIntToInt* ioSrcVertexToDstVertexMap = 0,
    CATMapOfIntToInt* ioSrcTriangleToDstTriangleMap = 0,
    bool iAddVertexIfInTheMap = true);

  /**
   * Copies a mesh into another mesh.
   * @param iSrcMesh
   *   The input CATIPolyMesh.
   * @param iPosMatrix
   *   An optional position matrix that will be applied to the input mesh during the copy.
   *   If determinant of this matrix is negative, then the triangles will be flipped.
   * @param ioDstMesh
   *   The CATIPolyMesh whose layers are populated with the input mesh data.
   * @param ioSrcVertexToDstVertexMap
   *   An optional vertex map.  If an empty map is passed as an argument, then, it is filled
   *   by this method.
   * @param ioSrcTriangleToDstTriangleMap
   *   An optional triangle map.  If an empty map is passed as an argument, then, it is filled
   *   by this method.
   * @param iAddVertexIfInTheMap
   *   If true, will add vertex if already found in the provided map, otherwise add a new vertex.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  static HRESULT Copy (const CATIPolyMesh& iSrcMesh, const CATMathTransformation* iPosMatrix,
    CATIPolyMesh& ioDstMesh,
    CATMapOfIntToInt* ioSrcVertexToDstVertexMap = 0,
    CATMapOfIntToInt* ioSrcTriangleToDstTriangleMap = 0,
    bool iAddVertexIfInTheMap = true);

public:

  /**
   * Copies a surface vertex line.
   */
  inline static HRESULT Copy (const CATIPolySurfaceVertexLine& iSrcVertexLine,
    CATIPolySurfaceVertexLine& ioDstVertexLine,
    const CATMapOfIntToInt& ioSrcVertexToDstVertexMap);

  /**
   * Copies a surface vertex line.
   * @param ioSrcVertexToDstVertexMap
   *    An optional map of the surface-vertex indices.  
   *    (Null means an identity map.)
   */
  static HRESULT Copy (const CATIPolySurfaceVertexLine& iSrcVertexLine,
    CATIPolySurfaceVertexLine& ioDstVertexLine,
    const CATMapOfIntToInt* ioSrcVertexToDstVertexMap = 0);

  /**
   * Copies a CATIPolyCurve into a CATPolyLine.
   */
  static HRESULT Copy (const CATIPolyCurve& iSrcVertexCurve,
    CATPolyLine& ioDstVertexLine,
    CATMapOfIntToInt* ioSrcVertexToDstVertexMap = 0);

  /**
   * Copies a mesh vertex.
   */
  static HRESULT Copy (const CATIPolyMesh& iSrcMesh,
    CATIPolyMesh& ioDstMesh,
    const int iSrcMeshVertex,
    int& oDstMeshVertex);

  /**
   * Copies a CATIPolyPoint.
   */
  static HRESULT Copy (const CATIPolyPoint& iSrcPoint,
    CATPolyPoint& ioDstPoint);

public:

  /**
   * Copies the mesh triangle.
   * (Used by CATPolyBodyMultiLayerBuilder.)
   * DO NOT USE OTHERWISE.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  static HRESULT CopyMeshTriangles (const CATIPolyMesh& iSrcMesh, CATIPolyMesh& ioDstMesh,
    const CATMapOfIntToInt& ioSrcVertexToDstVertexMap,
    CATMapOfIntToInt* ioSrcTriangleToDstTriangleMap = 0,
    const CATBoolean iSwapOrientation = FALSE);

  /**
   * Copies the polyhedral objects layers.
   * Call it explicitely to copy the native layers to the destination mesh.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  static HRESULT CopyLayers (CATPolyLayerCopier& copier, const CATIPolySurface& iSrcMesh, const CATMathTransformation* iPosMatrix,
    CATIPolySurface& ioDstMesh,
    CATMapOfIntToInt& iSrcVertexToDstVertexMap);

  // Forget about me.  See CopyLayers () above.
  // To get rid of.
  static HRESULT CopyDataLayers (const CATIPolySurface& iSrcMesh, const CATMathTransformation* iPosMatrix,
    CATIPolySurface& ioDstMesh,
    CATMapOfIntToInt& iSrcVertexToDstVertexMap);

};

inline HRESULT CATPolyMeshCopier::Copy (const CATIPolySurfaceVertexLine& iSrcVertexLine,
  CATIPolySurfaceVertexLine& ioDstVertexLine,
  const CATMapOfIntToInt& ioSrcVertexToDstVertexMap)
{
  return Copy (iSrcVertexLine, ioDstVertexLine, &ioSrcVertexToDstVertexMap);
}

#endif // !CATPolyMeshCopier_H
