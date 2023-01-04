// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleMerge : method of CATMathSortedArray
//
//===========================================================================
//
// Function:   merge of 2 sorted arrays on criterion type double,
//             without memory move, excepted the equivalence case
//
//    merging of 2 contiguous sorted arrays ioDou[iCntUp][_RowSize] preceding
//    [iCntBot][_RowSize], avoiding the duplicate of 2 equivalent rows.
//    equivalence = equality of _CritSize doubles at ranks _pCriterion.
//    one choices to keep the greetest double at rank iChoiceIdx.
//    if iChoiceIdx = -1, both occurences of a same criterion are kept.
//
//    this method requires a free column iFreeIdx in the arrays.
//
//===========================================================================
//
// Usage notes:
//
//   oCnt = CATMathDoubleMerge ( ioDou, iCntUp, iCntBot, iChoiceIdx, iMove,
//                               DynOffset, iFreeIdx );
//===========================================================================
// Input:
//
//    iCntUp     { CATLONG32  }  number of elements in the first array
//    iCntBot    { CATLONG32  }  number of elements in the second array
//    iChoiceIdx { CATLONG32  }  rank of the double which is tested for keeping
//                             (if -1, both rows in Up and Bot are kept)
//    iMove      { CATLONG32  }  displacement on start of the working area
//                             pInt[_Indir] = iMove + (0,1,2,3,...)
//    iFreeIdx   { CATLONG32  }  free marker at ((CATLONG32  *) ioDou)[iFreeIdx]
//                             internal to this method
//===========================================================================
// Output:
//
//    CATMathDoubleMerge { CATLONG32  }   final array size
//===========================================================================
// Input & output:
//
//    ioDou      { double * }  [iCntUp + iCntBot][_RowSize]
//                             arrays to be merged
//                             gives [CATMathDoubleMerge][_RowSize] as output
//                             modified column at rank iFreeIdx
//
//===========================================================================
#include "CATDataType.h"

 CATLONG32  CATMathDoubleMerge
    ( double * ioDou,      CATLONG32  iCntUp, CATLONG32  iCntBot,
      CATLONG32  iChoiceIdx, CATLONG32  iMove,  CATLONG32  iFreeIdx );
