//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCompareDoublePoints.h
//
//===================================================================
// February 2012 Creation: ndo
//===================================================================
#ifndef CATCompareDoublePoints_H
#define CATCompareDoublePoints_H

#include "PolyMathArithmetic.h"
#include "CATCompareElements.h"
#include "CATCompareFloatPoints.h"
#include "CATMathInline.h"


/**
 * Comparaison service between two double points represented by triplets of doubles.
 * The comparaison function must be antisymmetric and return 0 if the two triplets are equal.
 * The comparaison function should be transitive.
 * Returns:
 * <ul>
 *   <li> +1 if (da[0], da[1], da[2]) > (db[0], db[1], db[2])
 *   <li>  0 if (da[0], da[1], da[2]) = (db[0], db[1], db[2])
 *   <li> -1 if (da[0], da[1], da[2]) < (db[0], db[1], db[2])
 * </ul>
 *
 * By default the comparison function is a lexicographic sort with strict inequalities between doubles.
 * It can however be redefined in a derived class.  
 *
*/
class ExportedByPolyMathArithmetic CATCompareDoublePoints : public CATCompareElements
{

public:

  CATCompareDoublePoints () {}
  virtual ~CATCompareDoublePoints () {}

public:

  /**
   * Default lexicographic comparaison between two double points.
   */
  static int CompareLexicographic (const double* da, const double* db);

  /**
   * Returns the hash value given a pointer to a triplet of doubles.
   */
  INLINE static unsigned int HashThreeDoubles (const double* d);

public:

  /**
   * Virtual comparison function that returns:
   * <ul>
   *   <li> +1 if (da[0], da[1], da[2]) > (db[0], db[1], db[2])
   *   <li>  0 if (da[0], da[1], da[2]) = (db[0], db[1], db[2])
   *   <li> -1 if (da[0], da[1], da[2]) < (db[0], db[1], db[2])
   * </ul>
   * It can be overriden in a derived class.  It must be:
   * <ul>
   *   <li> Antisymmetric
   *   <li> Equal to 0 if the two triplets are equal.
   *   <li> Transitive
   * </ul>
   * By default the comparison function is a lexicographic sort with strict inequalities between doubles.
   */
  virtual int Compare (const double* da, const double* db) const;

  /**
   * See Compare (const double* da, const double* db).
   */
  virtual int Compare (const void* da, const void* db) const;

public:

  /**
   * Returns an integer hash value given a pointer to a triplet of doubles.
   */
  virtual unsigned int Hash (const void* d) const;

};

INLINE unsigned int CATCompareDoublePoints::HashThreeDoubles (const double* d)
{
  const float df[3] = {(float) d[0], (float) d[1], (float) d[2]};
  return CATCompareFloatPoints::HashThreeFloats (df);
}

#endif // !CATCompareDoublePoints_H
