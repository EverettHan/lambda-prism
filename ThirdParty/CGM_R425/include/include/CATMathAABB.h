// COPYRIGHT DASSAULT SYSTEMES 2009

#ifndef CATMathAABB_H
#define CATMathAABB_H

#include <CATMathematics.h>
#include <CATMathAdvancedBox.h>
#include <CATMathBox.h>

/**
 * Axis aligned bounding box
 * This is a wrapper around the CATMathBox class and is provided primarily
 * as an example of a CATMathAdvancedBox implementation.
 */
class ExportedByCATMathematics CATMathAABB : public CATMathAdvancedBox
{
public:
  /**
   * Build an emtpy undefined AABB
   */
  CATMathAABB();

  /**
   * Build an AABB from a CATMathBox
   */
  CATMathAABB(const CATMathBox &);

  /**
   * Duplicate an AABB
   */
  CATMathAABB(const CATMathAABB &);

  /**
   * @return the advanced box type (CATMathAABBType)
   */
  CATMathAdvancedBoxType GetType() const;

  /**
   * Test for intersection against another AABB
   * @param[in] iAABB the other AABB
   * @param[in] iTolerance a tolerance used when testing for intersection
   * @return 1 if the boxes intersect, 0 if they don't, -1 upon error
   */
  int IsIntersecting(const CATMathAABB &iAABB, double iTolerance) const;

    /**
   * Test for point inclusion 
   * @param[in] iPoint The point.
   * @param[in] iTolerance a tolerance used when testing for inclusion
   * @return 1 if the point is contained in the AABB, 0 if it isn't, -1 upon error
   */
  int IsContaining(const CATMathPoint &iPoint, double iTolerance) const;

  /**
   * Get the underlying CATMath box.
   * @param[out] oBox the box.
   */
  void GetBox(CATMathBox &oBox) const;

  /**
   * Inflate all the AABB.
   * @param[in] iTol the absolute (as opposed to relative) inflation value.
   */
  void Inflate(double);

  /**
   * @return TRUE if the underlying CATMathBox isn't empty, FALSE otherwise
   */
  CATBoolean IsDefined() const;

  /**
   * Evaluate the minimum square distance to a point.
   * @param[in] iPoint the point.
   * @return negative value upon error, the square distance otherwise.
   */
  double SquareDistanceTo(const CATMathPoint &iPoint) const;

  /**
   * Evaluate the minimum square distance to another AABB.
   * @param[in] iCloud the other AABB.
   * @return negative value upon error, the square distance otherwise.
   */
  double SquareDistanceTo(const CATMathAABB &iBox) const;

  /**
   * Duplicate the current advanced box.
   * @return the copy
   */
  CATMathAdvancedBox *Duplicate() const;

  /**
   * Change the underlying CATMathBox
   * @param[in] iBox the new box value.
   */
  void SetBox(const CATMathBox &iBox);

private:
  CATMathBox box;
};

#endif
