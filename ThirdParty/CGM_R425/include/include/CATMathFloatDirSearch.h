// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathFloatDirSearch : method belonging to CATMathSortedArray
//
//===========================================================================
// Function:         search inside a sorted array on criterion type float
//                   direct sort, with memory move
//
//     inside the array iFloat[iCnt][_RowSize], one places the element
//     iPla[_RowSize] immediately after the row number
//     CATMathFloatDirSearch of iFloat, which holds the element
//     less or equal to iPla, the greatest as possible
//
//===========================================================================
// Usage notes:
//
//    m = CATMathFloatDirSearch ( iFloat, iCnt, iPla, iNit );
//
//===========================================================================
// Input:
//
//        iFloat { * float }        [iCnt][_RowSize]
//                                  sorted array by increasing order according
//                                  to _CritSize floats at ranks _pCriterion
//                                  in each row
//        iCnt { CATLONG32  }         number of elements of iFloat
//        iPla { * float }          [_RowSize]
//                                  element to be compared to the floats at
//                                  ranks _pCriterion[0] to
//                                  _pCriterion[_CritSize - 1] in each row
//        iNit { const CATLONG32  }   = 0       no privileged starting area
//                                  = +1/-1   search is starting from
//                                            (begin)/(end)
//                                    (interesting each time one knows a great
//                                     probability to find in the neighborhood
//                                     of an extremity of the array)
//===========================================================================
// Output:
//
//        CATMathFloatDirSearch { CATLONG32  }
//                                rank of the row after which one takes
//                                a place
//                                -1 if one takes a place before the first one
//
//                                -1 <= CATMathFloatDirSearch < iCnt
//===========================================================================
#include "CATDataType.h"


 CATLONG32  CATMathFloatDirSearch
    ( float * iFloat, CATLONG32  iCnt, float * iPla, const CATLONG32  iNit );

//---------------------------------------------------------------------------
