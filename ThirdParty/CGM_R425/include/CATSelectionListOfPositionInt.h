// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSelectionListOfPositionInt
//
//===================================================================
// 2015-06-30   OZK
//      * New
//===================================================================
#ifndef CATSelectionListOfPositionInt_h
#define CATSelectionListOfPositionInt_h

#include "CATSysErrorDef.h"
#include "CATSysBoolean.h"
#include "PolyMathContainers.h"
/**
 * This is a container (like std::vector, or CATListOfInt) where you can quickly
 * add elements to the end and randomly access elements (indices start at 1 not 0).
 *
 * Additionally, it supports a selection algorithm (std::nth_element), whereby a range
 * of indices [start,end) is rearranged so that everything below
 *
 */
class CATMathPoint;
class CATListValpositionIntPair;
typedef CATBoolean (*SelectionListComparatorFunction)(CATMathPoint const&, CATMathPoint const&);

class ExportedByPolyMathContainers CATSelectionListOfPositionInt
{
public:
  CATSelectionListOfPositionInt();
  ~CATSelectionListOfPositionInt();
  HRESULT Append(CATMathPoint const& P, int idx);
  int Size() const;
  HRESULT GetIndex(int which, int& oIdx) const;
  HRESULT GetPoint(int which, CATMathPoint& P) const;

  /**
   * comparatorFunction must return 0 if a<b, 1 otherwise.  What a<b means is up to the client,
   * but the relation should be transite and antisymmetric.
   */
  HRESULT select(int start, int end, int nth, SelectionListComparatorFunction cmp);

  /**
   * @nodoc.  unit testing only.  do not use.
   **/
  HRESULT partitionCheck(int start, int end, int nth, SelectionListComparatorFunction cmp);

private:
  // no copies.
  CATSelectionListOfPositionInt(CATSelectionListOfPositionInt const&);
  CATSelectionListOfPositionInt& operator=(CATSelectionListOfPositionInt const&);

  int partition(int start, int end, CATMathPoint const& pivot, SelectionListComparatorFunction cmp);
  int choose_pivot(int start, int end, SelectionListComparatorFunction cmp);

  CATListValpositionIntPair* pairs;
};

#endif
