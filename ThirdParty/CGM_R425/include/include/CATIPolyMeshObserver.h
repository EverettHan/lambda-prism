//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Observer of mesh events.
//
//=============================================================================
// 2007-07-06   BPG: Remove dependancy on CATBaseUnknown.
// 2007-01-26   BPG     * New.
//=============================================================================
#ifndef CATIPolyMeshObserver_H
#define CATIPolyMeshObserver_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceObserver.h"
#include "CATErrorDef.h"

class CATMathPoint;
class CATMapOfIntToInt;


/**
* Observer class for CATIPolyMesh.
*/
class ExportedByPolyhedralModel CATIPolyMeshObserver : public CATIPolySurfaceObserver
{

protected:

  virtual ~CATIPolyMeshObserver();

public:

  /**
   * Casts the observer as a CATIPolyMeshObserver.
   */
  virtual CATIPolyMeshObserver* CastAsPolyMeshObserver ();

public:

  /** 
   * Call made just after a triangle is added.
   * @param v0 
   *   First vertex of the new triangle.
   * @param v1 
   *   Second vertex of the new triangle.
   * @param v2 
   *   Third vertex of the new triangle.
   * @param t
   *   Index of the new triangle.
   */
  virtual HRESULT ReactToAddTriangle (int v0, int v1, int v2, int t);

  /** 
   * Call made just before a triangle is removed.
   * @param t 
   *   Index of the triangle being removed. 
   */
  virtual HRESULT PrepareToRemoveTriangle (int t);

public:

  /** 
   * Call made just after a bar has been flipped.
   * @param v0 
   *   First vertex of the bar resulting from the flip.
   * @param v1 
   *   Second vertex of the bar resulting from the flip.
   */
  virtual HRESULT ReactToFlipBar (int v0, int v1);

  /**
   * Call made during the split a bar.
   * @see CATIPolySurface::SplitBar
   *
   * When a bar of a triangle is splitted, the triangles adjacent to the bar are 
   * divided in two.  This method is called just after the split of each adjacent triangle.
   *
   * @param t 
   *   Index of the triangle that was split. 
   * @param t0
   *   Index of the first triangle resulting from the split of t.
   * @param t1
   *   Index of the second triangle resulting from the split of t.
   */
  virtual HRESULT ReactToSplitTriangle (int t, int t0, int t1);

  /**
   * Call made during the merge of vertices.
   * @see CATIPolySurface::MergeVertices
   *
   * When two vertices v0 and v1 are merged, the triangles adjacent to the second vertex v1 are
   * updated.  This method is called for each triangle whose vertex v1 is replaced by
   * the first vertex v0.
   * @param t0
   *   Index of the triangle before the update (refers to v1).
   * @param t1
   *   Index of the triangle after the update (refers to v0).
   *   The index t1 may be equal to t0.
   * @param v0
   *   Target vertex in Triangle t1.
   * @param v1
   *   Source vertex in Triangle t0.
   */
  virtual HRESULT ReactToUpdateTriangle (int t0, int t1, int v0, int v1);

public:

  /** 
   * Call made just after a compact of the mesh vertex and triangle indices.
   * @param iVertexMap
   *   Maps an old vertex index to a new vertex index.
   * @param iTriangleMap
   *   Maps an old triangle index to a new triangle index.
   * @see CATIPolyMesh::Compact
   */
  virtual HRESULT ReactToCompact (const CATMapOfIntToInt& iVertexMap, const CATMapOfIntToInt& iTriangleMap);

};

#endif // !CATIPolyMeshObserver_H
