//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATComparClassID.h
//
//===================================================================
// June 2021 Creation: ndo
//===================================================================
#pragma once

#include "PolyMathArithmetic.h"
#include "CATCompareElements.h"
#include "IUnknown.h"


namespace Poly
{
  /**
   * Returns the hash number of a class id.
   */
  ExportedByPolyMathArithmetic unsigned int Hash (const CLSID& id);
}


/**
 * Specialization CATComparator for class IDs.
 */
template<>
class ExportedByPolyMathArithmetic CATComparator<const CLSID*>
{
public:

  CATComparator<const CLSID*> () {}

  int Compare (const CLSID* iClassID1, const CLSID* iClassID2) const;

  unsigned int Hash (const void* iClassID) const;

  bool Equal (const CLSID* iClassID1, const CLSID* iClassID2) const { return iClassID1 == iClassID2; }

};


/**
 * Comparaison between two class IDs.
 */
class ExportedByPolyMathArithmetic CATCompareClassID : public CATCompareElements
{

public:

  CATCompareClassID () {}
  virtual ~CATCompareClassID () {}

public:

  /**
   * Compare two class ID given their pointers.
   * @return
   * <ul>
   *   <li> +1 if iClassID1 > iClassID2
   *   <li>  0 if iClassID1 = iClassID2
   *   <li> -1 if iClassID1 < iClassID2
   * </ul>
   */
  int Compare (const void* iClassID1, const void* iClassID2) const;

public:

  /**
   * Returns the hash value given a pointer to a class ID.
   */
  unsigned int Hash (const void* iClassID) const;

};

