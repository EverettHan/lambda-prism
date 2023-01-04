// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVPlaneIntersector.h
//
//===================================================================
//
// April 2009  Creation: NDO
//===================================================================
#ifndef CATPolyBVPlaneIntersector_H
#define CATPolyBVPlaneIntersector_H

#include "PolyMathBV.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBVConstVisitor.h"

class CATPolyBoundingVolume;
class CATMathTransformation;
class CATMathPlane;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingCylinder;


/**
 * This operator checks if there exists an intersection between a bounding volume and a plane.
 * If the distance between the bounding volume and the plane is below the allowed clearance
 * (0 by default), then the two entities are said to be intersecting.
 *
 */
class ExportedByPolyMathBV CATPolyBVPlaneIntersector : private CATPolyBVConstVisitor
{

public:

  /* 
   * Returns TRUE if a bounding volume intersects a plane and FALSE otherwise.
   * Two optional arguments are the clearance and the transformation to be applied to the bounding volume.
   */
  CATPolyBVPlaneIntersector (const CATPolyBoundingVolume& iBV, const CATMathPlane& iPlane,
                             double iClearance = 0, const CATMathTransformation* iBVPosition = 0);

  ~CATPolyBVPlaneIntersector () {}

public:

  /* 
   * Returns TRUE if a bounding volume intersects a plane and FALSE otherwise.
   * Two optional arguments are the clearance and the transformation to be applied to the bounding volume.
   */
  inline CATBoolean Intersect () const;

private:

  const CATPolyBoundingVolume& _BV;
  const CATMathPlane& _Plane;
  double _Clearance;
  const CATMathTransformation* _BVPosition;

  CATBoolean _Intersect;

private:

  HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingPlane& iBV);
  HRESULT VisitConcrete (const CATPolyAABB& iBV);
  HRESULT VisitConcrete (const CATPolyOBB& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV);

};

inline CATBoolean CATPolyBVPlaneIntersector::Intersect () const
{
  return _Intersect;
}

#endif // !CATPolyBVPlaneIntersector_H
