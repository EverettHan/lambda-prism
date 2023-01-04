//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyBVProperties.h
//
//=============================================================================
// 2009-03-01   JXO
//      * New
//=============================================================================
#ifndef CATPolyBVProperties_H
#define CATPolyBVProperties_H

#include "PolyMathBV.h"

#include "CATBoolean.h"

class CATPolyBoundingVolume;
class CATMathPoint;
class CATMathDirection;

  /**
 * This is the operator for Bounding Volume computations
 */
class ExportedByPolyMathBV CATPolyBVProperties
{
public:
  CATPolyBVProperties(){}
  virtual ~CATPolyBVProperties() {}

public:

  /**
   * Returns if a this Bounding Volume is empty or not
   */
static CATBoolean IsEmpty(const CATPolyBoundingVolume * ipBV);
  /**
   * Returns the volume of this Bounding Volume
   */
static double GetVolume(const CATPolyBoundingVolume * ipBV);
  /**
   * Returns a "center point" for this BV.
   */
static CATMathPoint GetCenter(const CATPolyBoundingVolume * ipBV);

  /**
   * Returns the radius for this BV.
   */
static double GetRadius(const CATPolyBoundingVolume * ipBV);

/**
 * @return TRUE if the ray intersect the bounding volume, FALSE otherwise.
 */
static CATBoolean IsRayIntersectingBV(const CATPolyBoundingVolume & iBV,
                                      const CATMathPoint & rayOrigin,
                                      const CATMathDirection & rayDirection);

/**
 * @return TRUE if the point is inside the bounding volume, FALSE otherwise.
 */
static CATBoolean IsPointInsideBV(const CATPolyBoundingVolume & iBV,
                                  const CATMathPoint & point);

};

#endif // !CATPolyBVProperties_H
