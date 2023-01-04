//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCompareFloatPoints.h
//
//===================================================================
// February 2010 Creation: ndo
//===================================================================
#ifndef CATCompareFloatPoints_H
#define CATCompareFloatPoints_H

#include "PolyMathArithmetic.h"
#include "CATCompareElements.h"


/**
 * Comparaison service between two float points represented by triplets of floats.
 * The comparaison function must be antisymmetric and return 0 if the two triplets are equal.
 * The comparaison function should be transitive.
 * Returns:
 * <ul>
 *   <li> +1 if (da[0], da[1], da[2]) > (db[0], db[1], db[2])
 *   <li>  0 if (da[0], da[1], da[2]) = (db[0], db[1], db[2])
 *   <li> -1 if (da[0], da[1], da[2]) < (db[0], db[1], db[2])
 * </ul>
 *
 * By default the comparison function is a lexicographic sort with strict inequalities between floats.
 * It can however be redefined in a derived class.  
 *
*/
class ExportedByPolyMathArithmetic CATCompareFloatPoints : public CATCompareElements
{

public:

  CATCompareFloatPoints () {}
  virtual ~CATCompareFloatPoints () {}

public:

  /**
   * Default lexicographic comparaison between two float points.
   */
  static int CompareLexicographic (const float* da, const float* db);

  /**
   * Returns the hash value given a pointer to a triplet of floats.
   */
  static unsigned int HashThreeFloats (const float* d);

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
   * By default the comparison function is a lexicographic sort with strict inequalities between floats.
  */
  virtual int Compare (const float* da, const float* db) const;

  /**
   * See Compare (const float* da, const float* db).
   */
  virtual int Compare (const void* da, const void* db) const;

public:

  /**
   * Returns an integer hash value given a pointer to a triplet of floats.
   */
  virtual unsigned int Hash (const void* d) const;

};

#endif // !CATCompareFloatPoints_H
