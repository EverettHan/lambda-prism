// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVPointIntersector.h
//
//===================================================================
//
// June 2009  Creation: NDO
//===================================================================
#ifndef CATPolyBVPointIntersector_H
#define CATPolyBVPointIntersector_H

#include "PolyMathBV.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBVConstVisitor.h"

class CATPolyBoundingVolume;
class CATMathTransformation;
class CATMathPoint;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingCylinder;


/**
 * This operator checks if a point is inside a bounding volume.
 * If the distance between the bounding volume and the point is below the allowed clearance
 * (0 by default), then the two entities are said to be intersecting.
 *
 */
class ExportedByPolyMathBV CATPolyBVPointIntersector : private CATPolyBVConstVisitor
{

public:

  /* 
   * Returns TRUE if a bounding volume intersects a plane and FALSE otherwise.
   * Two optional arguments are the clearance and the transformation to be applied to the bounding volume.
   */
  CATPolyBVPointIntersector (const CATPolyBoundingVolume& iBV, const CATMathPoint& iPoint,
                             double iClearance = 0, const CATMathTransformation* iBVPosition = 0);

  ~CATPolyBVPointIntersector () {}

public:

  /* 
   * Returns TRUE if a point is inside a bounding volume (up to a clearance) and FALSE otherwise.
   * Two optional arguments are the clearance and the transformation to be applied to the bounding volume.
   */
  inline CATBoolean Intersect () const;

private:

  const CATPolyBoundingVolume& _BV;
  const CATMathPoint& _Point;
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

inline CATBoolean CATPolyBVPointIntersector::Intersect () const
{
  return _Intersect;
}

#endif // !CATPolyBVPointIntersector_H
