// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleSearch: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//
//---------------------------------------------------------------------------
//
//  function:         search inside a sorted array on criterion type double
//                    indirect sort: there has been no memory move
//
//---------------------------------------------------------------------------
//
//  description:
//
//     inside the array iDou[iCnt][_RowSize], one places the element
//     iPla[_RowSize] immediately after the row number
//     CATMathDoubleSearch of iDou, which holds the element
//     less or equal to iPla, the greatest as possible
//
//---------------------------------------------------------------------------
//
//  call:
//
//    m = CATMathDoubleSearch ( iDou, iCnt, iPla, iMove, iNit );
//
//---------------------------------------------------------------------------
//
//  input:
//
//        iDou { * double }          [iCnt][_RowSize]
//                                   sorted array by increasing order according
//                                   to _CritSize doubles at ranks _pCriterion
//                                   in each row
//        iCnt { CATLONG32  }          number of elements of iDou
//        iPla  { * double }         [_RowSize]
//                                   element to be compared to the doubles at
//                                   ranks _pCriterion[0] to
//                                   _pCriterion[_CritSize - 1] in each row
//        iMove { CATLONG32  }         start shifting on the working area
//                                   ((CATLONG32 *) iDou)[_Indir] =
//                                      iMove + (0,1,2,3,...)
//        iNit  { const CATLONG32  }   = 0       no privileged starting area
//                                   = +1/-1   search is starting from
//                                             (begin)/(end)
//                                     (interesting each time one knows a great
//                                      probability to find in the neighborhood
//                                      of an extremity of the array)
//
//---------------------------------------------------------------------------
//
//  output:
//
//        CATMathDoubleSearch { CATLONG32  }
//                                rank of the row after which one takes
//                                a place
//                                -1 if one takes a place before the first one
//
//                                -1 <= CATMathDoubleSearch < iCnt
//
//---------------------------------------------------------------------------
#include "CATDataType.h"


   CATLONG32  CATMathDoubleSearch
   ( double * iDou, CATLONG32  iCnt, double * iPla,
     CATLONG32  iMove, const CATLONG32  iNit );

//---------------------------------------------------------------------------
