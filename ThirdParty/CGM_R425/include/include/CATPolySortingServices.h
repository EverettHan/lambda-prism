// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySortingServices.h
//
//===================================================================
// August 2018  Creation NDO
//===================================================================
#ifndef CATPolySortingServices_h
#define CATPolySortingServices_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"

class CATCompareElements;


namespace Poly
{

/** @name Sorting Services
 *
 * CATPolySortingServices.h
 * @{ */

  /**
   * Sorts the elements in an c-style array in ascending order.
   * The elements are compared using the CATCompareElements binary comparison class.
   * The underlying implementation calls std::sort of O(n log n) complexity.
   */
  ExportedByPolyMathContainers HRESULT Sort (void* iElements[], const unsigned int iNbElements, const CATCompareElements& iComparator);

/** @} */

};

#endif
