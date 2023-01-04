// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyMeshDisabler.h
//
//===================================================================
// October 2018  Creation: NDO
//===================================================================
#ifndef CATIPolyMeshDisabler_H
#define CATIPolyMeshDisabler_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceDisabler.h"


/**
* Class to disable editing events for CATIPolyMesh.
* By default, all editing events are enabled;
* all methods return false.
*/
class ExportedByPolyhedralModel CATIPolyMeshDisabler : public CATIPolySurfaceDisabler
{

public:

  virtual ~CATIPolyMeshDisabler () {}

public:

/** @name Casting Methods
    @{ */

  /**
   * Casts the event disabler as a CATIPolyMeshDisabler.
   */
  virtual CATIPolyMeshDisabler* CastAsMeshDisabler ();

  /**
   * Casts the event disabler as a const CATIPolyMeshDisabler.
   */
  virtual const CATIPolyMeshDisabler* CastAsMeshDisabler () const;

  /** @} */

public:

/** @name Disable CATIPolyMesh Events
    @{ */

  /** 
   * Disables adding a triangle.
   * @param v0 
   *   First vertex of the triangle to add.
   * @param v1 
   *   Second vertex of the triangle to add.
   * @param v2 
   *   Third vertex of the triangle to add.
   */
  virtual bool DisableAddTriangle (int v0, int v1, int v2) const;

  /** 
   * Disables removing a triangle.
   * @param t 
   *   Index of the triangle to remove. 
   */
  virtual bool DisableRemoveTriangle (int t) const;

public:

  /** 
   * Disables flipping a bar.
   * @param v0 
   *   First vertex of the bar.
   * @param v1 
   *   Second vertex of the bar.
   */
  virtual bool DisableFlipBar (int v0, int v1) const;

public:

  /** 
   * Disables compacting a mesh.
   */
  virtual bool DisableCompact () const;

/** @} */

};

#endif // !CATIPolyMeshDisabler_H
