// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMergeSort.h
//
//===================================================================
//
// August 2011  Creation: NDO
//  
//===================================================================
#ifndef CATMergeSort_h
#define CATMergeSort_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"

class CATCompareElements;


/*
Implements the merge sort algorthm to sort an array of elements.
Worst, best and average case performance if O(n log n).
(Multi-thread implementation.)
*/
class ExportedByPolyMathContainers CATMergeSort
{

public:

  CATMergeSort (const CATCompareElements& iComparator, unsigned int iNbThreads = 1) : _Comparator (iComparator), _NbThreads (iNbThreads) {}
  ~CATMergeSort () {}

public:

  HRESULT Sort (void* iElements[], const unsigned int iNbElements);

  //HRESULT Sort (void* iElements[], void* oSortedElements[], const unsigned int iNbElements);

private:

  const CATCompareElements& _Comparator;
  unsigned int _NbThreads;

private:

  //void SortWithoutNestedCalls (void* iData[], void* ioSortedData[], const unsigned int iNbData);

};

#endif
