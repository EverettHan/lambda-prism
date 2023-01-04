// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathIntDirSearch : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//    where = CATMathIntDirSearch ( iInt, iCnt, iPla, iNit );
//
//===========================================================================
//
// function:         search inside a sorted array on criterion type integer
//                   direct sort: there has been memory move
//
//===========================================================================
//
// description:
//
//     the element iPla[_RowSize] is set immediately after the row of rank
//     CATMathIntDirSearch inside the array iInt[iCnt][_RowSize], which holds
//     the greatest element as possible, less or equal to iPla.
//
//===========================================================================
//
// input:
//
//        iInt  { CATLONG32  * }       [iCnt][_RowSize]
//                                   sorted array by increasing order using
//                                   _CritSize integers at ranks _pCriterion
//                                   in each row
//        iCnt  { CATLONG32  }         number of elements of iInt
//        iPla  { CATLONG32  * }       [_RowSize]
//                                   element to be compared to the integers
//                                   at ranks _pCriterion[0] to
//                                   _pCriterion[_CritSize - 1]
//                                   in each row
//        iNit  { const CATLONG32  }   = 0       no privileged start area
//                                   = +1/-1   search start from
//                                             (the begin)/(the end)
//                                     (interesting each time one knows a
//                                      great probability to find in the
//                                      neighborhood of a limit of the array)
//
//===========================================================================
//
// output:
//
//        CATMathIntDirSearch { CATLONG32  }
//                                rank of the row after which one sets
//                                -1 if one sets before the first one
//
//                                -1 <= CATMathIntDirSearch < iCnt
//
//===========================================================================


 CATLONG32  CATMathIntDirSearch
    ( CATLONG32  * iInt, CATLONG32  iCnt, CATLONG32  * iPla, const CATLONG32  iNit );
