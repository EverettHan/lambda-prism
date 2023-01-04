// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVZRayIntersector.h
//
//===================================================================
// June 2014 Creation: ndo
//===================================================================
#ifndef CATPolyBVZRayIntersector_H
#define CATPolyBVZRayIntersector_H

#include "PolyMathBV.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBVConstVisitor.h"

class CATPolyBoundingVolume;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingCylinder;
class CATMathPoint;


/**
 * This operator intersects a bounding volume with a semi-infinite ray starting at a given point 
 * and parallel to the z-axis. 
 */
class ExportedByPolyMathBV CATPolyBVZRayIntersector : private CATPolyBVConstVisitor
{

public:

  /* 
   * Returns <tt>TRUE</tt> if a bounding volume intersects the semi-infinite ray and <tt>FALSE</tt> otherwise.
   * @param iBV
   *   Input bounding volume.
   * @param iStart
   *   The starting point of the ray.
   * @param iDir
   *   The direction of the ray: +1 if the ray goes up (+z direction); and -1 of the ray goes down (-z direction).
   * @param iClearance
   *   An optional clearance applied to the bounding volume for the intersection test.
   */
  CATPolyBVZRayIntersector (const CATPolyBoundingVolume& iBV, const CATMathPoint& iStart, int iDir, const double iClearance = 0);

  ~CATPolyBVZRayIntersector () {}

public:

  /* 
   * Returns <tt>TRUE</tt> if the bounding volume intersects the ray and <tt>FALSE</tt> otherwise.
   */
  inline CATBoolean Intersect () const;

private:

  const CATPolyBoundingVolume& _BV;
  const CATMathPoint& _Start;
  int _Dir;
  double _Clearance;

  CATBoolean _Intersect;

private:

  HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingPlane& iBV);
  HRESULT VisitConcrete (const CATPolyAABB& iBV);
  HRESULT VisitConcrete (const CATPolyOBB& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV);

};

inline CATBoolean CATPolyBVZRayIntersector::Intersect () const
{
  return _Intersect;
}

#endif // !CATPolyBVZRayIntersector_H
