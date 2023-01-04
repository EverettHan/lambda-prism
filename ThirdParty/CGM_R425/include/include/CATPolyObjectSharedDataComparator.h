// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyObjectSharedDataComparator.h
//
//===================================================================
// February 2011  Creation: NDO
//===================================================================
#ifndef CATPolyObjectSharedDataComparator_H
#define CATPolyObjectSharedDataComparator_H

#include "PolyMeshTools.h"
#include "CATCompareElements.h"

class CATIPolyObject;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;


/**
 * A service checking if two polyhedral objects share the same data or not.
 * This service is provided as a comparator.  If two CATIPolyObject-s share
 * (or refer to) the same data, then the comparator returns 0.
 * The comparison function is:
 * <ul>
 *  <li> Antisymmetric
 *  <li> Equal to 0 if the two polyhedral object share the same data.
 *  <li> Transitive
 * </ul>
 * Comparison is not stable with respect to streaming operations.  (The Compare methods may return different values after streaming
 * and unstreaming of its arguments.)
*/
class ExportedByPolyMeshTools CATPolyObjectSharedDataComparator : public CATCompareElements
{

public:

  CATPolyObjectSharedDataComparator () {}
  virtual ~CATPolyObjectSharedDataComparator () {}

public:

  /**
   * Compares two CATIPolyObject-s.  
   * If the two instances share the same data then the method returns 0.  Otherwise it returns +1 or -1. 
   * The method is antisymmetric and transitive.
   * @param iInstance1
   *   A pointer to the first instance to compare.
   * @param iInstance2
   *   A pointer to the second instance to compare.
   */
  int Compare (const CATIPolyObject& iPolyObject1, const CATIPolyObject& iPolyObject2) const;

  /**
   * Compares two CATIPolySurface-s.  
   * If the two instances share the same data then the method returns 0.  Otherwise it returns +1 or -1. 
   * The method is antisymmetric and transitive.
   * @param iInstance1
   *   A pointer to the first instance to compare.
   * @param iInstance2
   *   A pointer to the second instance to compare.
   */
  int Compare (const CATIPolySurface& iInstance1, const CATIPolySurface& iInstance2) const;

  /**
   * Compares two CATIPolyCurve-s.  
   * If the two instances share the same data then the method returns 0.  Otherwise it returns +1 or -1. 
   * The method is antisymmetric and transitive.
   * @param iInstance1
   *   A pointer to the first instance to compare.
   * @param iInstance2
   *   A pointer to the second instance to compare.
   */
  int Compare (const CATIPolyCurve& iInstance1, const CATIPolyCurve& iInstance2) const;

  /**
   * Compares two CATIPolyPoint-s.  
   * If the two instances share the same data then the method returns 0.  Otherwise it returns +1 or -1. 
   * The method is antisymmetric and transitive.
   * @param iInstance1
   *   A pointer to the first instance to compare.
   * @param iInstance2
   *   A pointer to the second instance to compare.
   */
  int Compare (const CATIPolyPoint& iInstance1, const CATIPolyPoint& iInstance2) const;

public:

  /**
   * Returns an integer hash value given a pointer to a CATIPolyObject instance.
   */
  unsigned int Hash (const void* d) const;

private:

  int Compare (const void* pe1, const void* pe2) const;

};

#endif
