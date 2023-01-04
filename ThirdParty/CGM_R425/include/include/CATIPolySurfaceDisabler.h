// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceDisabler.h
//
//===================================================================
// October 2018  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceDisabler_H
#define CATIPolySurfaceDisabler_H

#include "PolyhedralModel.h"
//#include "CATPolyRefCounted.h"

class CATIPolyMeshDisabler;
class CATMathPoint;


/**
* Class to disable editing events for CATIPolySurface.
* By default, all editing events are enabled;
* all methods return false.
*/
class ExportedByPolyhedralModel CATIPolySurfaceDisabler
{

public:

  virtual ~CATIPolySurfaceDisabler () {}

public:

/** @name Casting Methods
    @{ */

  /**
   * Casts the observer as a CATIPolyMeshDisabler.
   */
  virtual CATIPolyMeshDisabler* CastAsMeshDisabler ();

  /**
   * Casts the observer as a const CATIPolyMeshDisabler.
   */
  virtual const CATIPolyMeshDisabler* CastAsMeshDisabler () const;

  /** @} */

public:

/** @name Disable CATIPolySurface Events
    @{ */

  /** 
   * Disables adding a vertex.
   */
  virtual bool DisableAddVertex () const;

  /**
   * Disables removing a vertex.
   * @param v
   *   Index of the vertex to remove.
   */
  virtual bool DisableRemoveVertex (int v) const;

  /**
   * Disables splitting a bar.
   * @param v0
   *   First vertex of the bar.
   * @param v1
   *   Second vertex of the bar.
   */
  virtual bool DisableSplitBar (int v0, int v1) const;

  /** 
   * Disables merging two vertices.
   * @param v0
   *  The index of the first vertex.
   * @param v1
   *  The index of the second vertex.  
   */
  virtual bool DisableMergeVertices (int v0, int v1) const;

/** @} */

public:

/** @name Disable CATIPolySurfaceVertexPositionLayer Events
    @{ */

  /** 
   * Disables setting a new position to a vertex.
   * See CATIPolySurfaceVertexPositionLayer.
   * @param v 
   *   The index of the vertex whose position is modified.
   * @param P
   *   The target position of the vertex.
   */
  virtual bool DisableSetVertexPosition (int v, const CATMathPoint& P) const;

/** @} */

};

#endif // !CATIPolySurfaceDisabler_H
