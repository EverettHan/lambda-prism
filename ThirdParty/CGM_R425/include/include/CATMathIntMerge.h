// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathIntMerge : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//  oCnt = CATMathIntMerge ( ioInt, iCntUp, iCntBot, iChoiceIdx, iMove,
//                           iFreeIdx );
//
//===========================================================================
//
// function:   merge of 2 sorted arrays on criterion type integer,
//             without memory move, excepted the equivalence case.
//
//    merge of 2 contiguous sorted arrays ioInt[iCntUp][_RowSize] preceding
//    [iCntBot][_RowSize], avoiding the duplicate of 2 equivalent rows.
//    equivalence = equality of _CritSize integers at ranks _pCriterion.
//    one choices to keep the greetest integer at rank iChoiceIdx.
//    if iChoiceIdx = -1, both equivalent rows are kept.
//
//    this method requires a free column at rank iFreeIdx in the arrays.
//
//===========================================================================
// input:
//
//    iCntUp     { CATLONG32  }    number of elements of the first array
//    iCntBot    { CATLONG32  }    number of elements of the second array
//    iChoiceIdx { CATLONG32  }    rank of the integer which is tested for
//                               keeping
//                               (if -1, both rows in Up and Bot are kept)
//    iMove      { CATLONG32  }    displacement on start of the working area
//                               ioInt[_Indir] = iMove + (0,1,2,3,...)
//    iFreeIdx   { CATLONG32  }    free marker at ioInt[iFreeIdx]
//                               internal to this method
//===========================================================================
// output:
//
//    CATMathIntMerge { CATLONG32  }   final array size
//===========================================================================
// input & output:
//
//    ioInt      { CATLONG32  * }  [iCntUp + iCntBot][_RowSize]
//                               arrays to be merged
//                               gives [CATMathIntMerge][_RowSize] as output
//                               modified column at rank iFreeIdx
//
//===========================================================================


 CATLONG32  CATMathIntMerge
    ( CATLONG32  * ioInt,    CATLONG32  iCntUp, CATLONG32  iCntBot,
      CATLONG32  iChoiceIdx, CATLONG32  iMove,  CATLONG32  iFreeIdx );
