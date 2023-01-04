// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathIntDirMerge : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//   oCnt = CATMathIntDirMerge ( iUp, iBot, oTot, iCntUp, iCntBot,
//                               iChoiceIdx );
//
//===========================================================================
//
// function:   merge of 2 sorted arrays on criterion type integer,
//             with memory move
//
//    merge of 2 sorted arrays iUp[iCntUp][_RowSize] and
//    iBot[iCntBot][_RowSize], avoiding the duplicate of 2 equivalent rows.
//    equivalence = equality of _CritSize integers at ranks _pCriterion.
//    one choices to keep the greetest integer at rank iChoiceIdx.
//    if iChoiceIdx = -1, both equivalent rows are kept.
//
//===========================================================================
// input:
//
//    iUp        { CATLONG32  * }  [iCntUp][_RowSize]
//    iBot       { CATLONG32  * }  [iCntBot][_RowSize]
//                               arrays to be merged
//    iCntUp     { CATLONG32  }    number of elements of the first array
//    iCntBot    { CATLONG32  }    number of elements of the second array
//    iChoiceIdx { CATLONG32  }    rank of the integer which is tested for
//                               keeping
//                               (if -1, both rows in Up and Bot are kept)
//===========================================================================
// output:
//
//    oTot       { CATLONG32  * }  [iCntUp + iCntBot][_RowSize]
//                               sorted array resulting from the merge
//                               gives [CATMathIntDirMerge][_RowSize]
//                               as output
//    CATMathIntDirMerge { CATLONG32  }   useful oTot size
//
//===========================================================================


 CATLONG32  CATMathIntDirMerge
    ( CATLONG32  * iUp,      CATLONG32  * iBot,  CATLONG32  * oTot,
      CATLONG32  iCntUp,     CATLONG32  iCntBot, CATLONG32  iChoiceIdx );
