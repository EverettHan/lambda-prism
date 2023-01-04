//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// Observer of surface modification events.
//
//=============================================================================
// 2011-05-19   NDO: Creation
//=============================================================================
#ifndef CATIPolySurfaceObserver_H
#define CATIPolySurfaceObserver_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"

class CATIPolyMeshObserver;
class CATPolyFaceSurface;
class CATMathPoint;


/**
* Observer class for CATIPolySurface.
*/
class ExportedByPolyhedralModel CATIPolySurfaceObserver : public CATPolyRefCounted
{

protected:

  virtual ~CATIPolySurfaceObserver () {}

public:

/** @name CATIPolySurface Events
    @{ */

  /** 
   * Call made just after a vertex is added.
   * @param v 
   *   The index of the vertex that has been added to the CATIPolySurface. 
   */
  virtual HRESULT ReactToAddVertex (int v);

  /** 
   * Call made just before a vertex is removed.
   * @param v 
   *   The index of the vertex that is being removed from the CATIPolySurface. 
   */
  virtual HRESULT PrepareToRemoveVertex (int v);

  /** 
   * Call made just after a bar between two vertices has been split.
   * @param v0
   *   The first input vertex.
   * @param v1
   *   The second input vertex.
   * @param n
   *   The index of the new vertex created by the split.
   */
  virtual HRESULT ReactToSplitBar (int v0, int v1, int n);

  /** 
   * Call made before the merge of two vertices.
   * The second vertex is merged with the first.
   * @param v0
   *  The index of the first vertex.
   * @param v1
   *  The index of the second vertex.  
   */
  virtual HRESULT PrepareToMergeVertices (int v0, int v1);

  /**
   * Call made just after the merge of two vertices.
   * The second vertex is merged with the first.
   * However, the second vertex is not removed from the CATIPolySurface.
   * The second vertex is no longer referenced by any facet.
   * @param v0
   *  The index of the first vertex.
   * @param v1
   *  The index of the second vertex.
   */
  virtual HRESULT ReactToMergeVertices (int v0, int v1);

  /** @} */

public:

/** @name CATIPolySurfaceVertexPositionLayer Events
    @{ */

  /** 
   * Call made after the position of a vertex is modified.
   * See CATIPolySurfaceVertexPositionLayer.
   * @param v 
   *   The index of the vertex whose position is modified.
   * @param iPoint
   *   The new position of the vertex.
   */
  virtual HRESULT ReactToSetVertexPosition (int v, const CATMathPoint& iPoint);

/** @} */

public:

/** @name Casting Methods
    @{ */

  /**
   * Casts the observer as a CATIPolyMeshObserver.
   */
  virtual CATIPolyMeshObserver* CastAsPolyMeshObserver ();

  /**
   * Casts the observer as a CATPolyFaceSurface.
   * Reserved.
   */
  virtual CATPolyFaceSurface* CastAsPolyFaceSurface ();

/** @} */

};

#endif // !CATIPolySurfaceObserver_H
