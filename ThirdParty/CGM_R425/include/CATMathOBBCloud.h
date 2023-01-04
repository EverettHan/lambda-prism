// COPYRIGHT DASSAULT SYSTEMES 2009

#ifndef CATMathOBBCloud_H
#define CATMathOBBCloud_H

#include <CATMathOBB.h>

/**
 * Oriented bounding box cloud
 * Groups several oriented bounding boxes in an CATMathAdvancedBox compliant
 * container.
 */
class ExportedByCATMathematics CATMathOBBCloud : public CATMathAdvancedBox
{
public:
  /**
   * Build an empty undefined OBB cloud
   */
  CATMathOBBCloud();

  /**
   * Build an OBB cloud from an OBB array.
   * OBBs will be duplicated.
   * @param[in] iOBBs OBB array
   * @param[in] iLength OBB array length
   */
  CATMathOBBCloud(const CATMathOBB *iOBBs, CATULONG32 iLength);

  /**
   * Duplicate an OBB cloud
   */
  CATMathOBBCloud(const CATMathOBBCloud &);

  /**
   * Build an OBB cloud containing a single OBB.
   * The OBB will be duplicated.
   * @param[in] iOBB The OBB.
   */
  CATMathOBBCloud(const CATMathOBB &iOBB);
  ~CATMathOBBCloud();

  /**
   * @return the advanced box type (CATMathOBBCloudType)
   */
  CATMathAdvancedBoxType GetType() const;

  /**
   * Test for intersection against another OBB cloud
   * @param[in] iCloud the other OBB cloud
   * @param[in] iTolerance a tolerance used when testing for intersection
   * @return 1 if the clouds intersect, 0 if they don't, -1 upon error
   */
  int IsIntersecting(const CATMathOBBCloud &iCloud, double iTolerance) const;

  /**
   * Test for point inclusion 
   * @param[in] iPoint The point.
   * @param[in] iTolerance a tolerance used when testing for inclusion
   * @return 1 if the point is contained by one or more of the cloud's OBBs,
   *         0 if it isn't, -1 upon error
   */
  int IsContaining(const CATMathPoint &iPoint, double iTolerance) const;

  /**
   * Inflate all the OBBs in the cloud.
   * @param[in] iTol the absolute (as opposed to relative) inflation value.
   */
  void Inflate(double iTol);

  /**
   * Get a box containing the OBB cloud.
   * @param[out] oBox the axis aligned box.
   */
  void GetBox(CATMathBox &oBox) const;

  /**
   * Check if the cloud is defined.
   * @return TRUE if the cloud is defined, FALSE otherwise.
   */
  CATBoolean IsDefined() const;

  /**
   * Evaluate the minimum square distance to a point.
   * @param[in] iPoint the point.
   * @return negative value upon error, the square distance otherwise.
   */
  double SquareDistanceTo(const CATMathPoint &iPoint) const;

  /**
   * Evaluate the minimum square distance to another OBB cloud.
   * @param[in] iCloud the other OBB cloud.
   * @return negative value upon error, the square distance otherwise.
   */
  double SquareDistanceTo(const CATMathOBBCloud &iCloud) const;

  /**
   * Duplicate the current advanced box.
   * @return the copy
   */
  CATMathAdvancedBox *Duplicate() const;

  /**
   * Get the cloud's children
   * @param[out] oChildren a pointer to the OBB array
   * @param[out] oCount the array's length.
   */
  void GetChildren(CATMathOBB const **oChildren, CATULONG32 *oCount) const;

  /**
   * Set the cloud's children.
   * The OBBs will be duplicated.
   * @param[in] iChildren an OBB array.
   * @param[in] iCount the array length.
   */
  void SetChildren(const CATMathOBB *iChildren, CATULONG32 iCount);

  /**
   * Set the cloud's children.
   * The OBBs will *not* be duplicated. The array will be delete[]d upon the
   * cloud's destruction.
   * @param[in] iChildren an OBB array.
   * @param[in] iCount the array length.
   */
  void SetChildrenNoAlloc(CATMathOBB *iChildren, CATULONG32 iCount);

  CATMathOBBCloud &operator =(const CATMathOBB &iOBB);
  CATMathOBBCloud &operator =(const CATMathOBBCloud &iCloud);

  friend ExportedByCATMathematics CATMathOBBCloud operator *(const CATMathTransformation & iTransfo, const CATMathOBBCloud & iOBB);

private:
  CATULONG32 _ChildrenCount; /**< The number of OBBs in the cloud */
  CATMathOBB *_Children; /**< The OBBs */
};

#endif
