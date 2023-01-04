// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleDirSearch: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//---------------------------------------------------------------------------
//
//  function:         search inside a sorted array on criterion type double
//                    direct sort, with memory move
//
//---------------------------------------------------------------------------
//
//  description:
//
//     inside the array iDou[iCnt][_RowSize], one places the element
//     iPla[_RowSize] immediately after the row number
//     CATMathDoubleDirSearch of iDou, which holds the element
//     less or equal to iPla, the greatest as possible
//
//---------------------------------------------------------------------------
//
//  call:
//
//    m = CATMathDoubleDirSearch ( iDou, iCnt, iPla, iNit );
//
//---------------------------------------------------------------------------
//
//  input:
//
//        iDou { * double }         [iCnt][_RowSize]
//                                  sorted array by increasing order according
//                                  to _CritSize doubles at ranks _pCriterion
//                                  in each row
//        iCnt { CATLONG32  }         number of elements of iDou
//        iPla { * double }         [_RowSize]
//                                  element to be compared to the doubles at
//                                  ranks _pCriterion[0] to
//                                  _pCriterion[_CritSize - 1] in each row
//        iNit { const CATLONG32  }   = 0       no privileged starting area
//                                  = +1/-1   search is starting from
//                                            (begin)/(end)
//                                    (interesting each time one knows a great
//                                     probability to find in the neighborhood
//                                     of an extremity of the array)
//
//---------------------------------------------------------------------------
//
//  output:
//
//        CATMathDoubleDirSearch { CATLONG32  }
//                                rank of the row after which one takes
//                                a place
//                                -1 if one takes a place before the first one
//
//                                -1 <= CATMathDoubleDirSearch < iCnt
//
//---------------------------------------------------------------------------
#include "CATDataType.h"

   CATLONG32  CATMathDoubleDirSearch
   ( double * iDou, CATLONG32  iCnt, double * iPla, const CATLONG32  iNit );

//---------------------------------------------------------------------------
