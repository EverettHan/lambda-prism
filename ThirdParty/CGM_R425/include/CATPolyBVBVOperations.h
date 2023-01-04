//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyBVBVOperations.h
//
//=============================================================================
// 2009-03-01   JXO
//      * New
// 2013-08-22 JXO
//      * epsilon
//=============================================================================
#ifndef CATPolyBVBVOperations_H
#define CATPolyBVBVOperations_H

#include "PolyMathBV.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBoundingVolume;
class CATMathTransformation;
class CATMathVector;
#include "CATTolerance.h"

#ifndef NULL
#define NULL 0
#endif

/**
 * This is the operator for Bounding Volume / Bounding Volume
 * computations (such as union, overlap, etc...)
 */
class ExportedByPolyMathBV CATPolyBVBVOperations
{
 public:
  CATPolyBVBVOperations(){}
  ~CATPolyBVBVOperations() {}

 public:
  /**
   * Returns the volume that would have a new bounding volume union of the two input ones.
   * Type of this new one is the worst of the two input ones (sphere is worst than AABB, then OOBB, etc...)
   */
  static double GetVolumeOfUnion(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2);

  /**
   * Absorbs another bounding volume.
   * @param iAbsorbingBV
   *   The first bounding volume that absorbs the other.  This bounding volume is modified.
   * @param iBVToAbsorb
   *   The second bounding volume that is absorbed.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> The bounding volume has been updated to absorb the second volume.
   *   <li> <tt>S_FALSE</tt> The bounding volume already contains the second volume.
   *   <li> <tt>E_FAIL</tt> The bounding volume could not absorb the second volume.
   * </ul>
   */
  static HRESULT Absorb (CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2);

  /**
   * States whether two BVs overlap given a tolerance.
   * Note that if the intersection is just a point, or a line, or a surface, it will return TRUE.
   */
  static CATBoolean BVOverLap(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                              double iTol = 0.,
                              const CATMathTransformation * ipPosition1 = NULL, const CATMathTransformation * ipPosition2 = NULL);

  static double GetMinimumDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                   double iTol = 0.0,
                                   CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL);
  static double GetSquareMinimumDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                         double iTol = 0.0,
                                         CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL);
  static double GetMaximumDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                   double iTol = 0.0,
                                   CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL);
  static double GetSquareMaximumDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                         double iTol = 0.0,
                                         CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL);

  static CATBoolean BVOverLapOnePos(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                    double iTol = 0.,
                                    CATMathTransformation * ipPosition2 = NULL);

  static CATBoolean BVOverLapOnePos(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                    const CATMathVector & translation2, double iTol = 0.);

  static CATBoolean BVOverlapNoPos(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                   double iTol = 0.);

  /** Minimal distance along a direction between two bounding volumes.
   * @param eps1 should be an espilon for lengthtest
   * @return TRUE if a distance exists, FALSE otherwise.
   */
  static CATBoolean GetSquareMinDirDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                            const CATMathVector & iDirection, double & oDistance, double iTol = 0.0,
                                            CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL,
                                            const double eps1 = CATGetDefaultTolerance().EpsgForLengthTest() * 1000.);

  /** Returns a negative penetration distance if the two BV's overlap,
   *  or else the positive minimal distance.
   */
  static double GetOverlapDistance(const CATPolyBoundingVolume * ipBV1, const CATPolyBoundingVolume * ipBV2,
                                   CATMathTransformation * ipPosition1 = NULL, CATMathTransformation * ipPosition2 = NULL);
};

#endif // !CATPolyBVBVOperations_H
