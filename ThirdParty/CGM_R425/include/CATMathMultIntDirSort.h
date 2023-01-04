// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathMultIntDirSort : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//  CATMathMultIntDirSort ( ioInt, iCnt );
//
//  when this method finishes, _CurCrit is automatically reset to *_pCriterion
//
//===========================================================================
//
// function:         quick sort of an array on multiple criterion type
//                   CATLONG32 
//
//    sorting of iCnt articles of _RowSize integers using a selective sort
//    on _CritSize integers at ranks _pCriterion
//    direct sort, with memory move
//
//===========================================================================
// input:
//
//        iCnt  { CATLONG32  }     number of elements of the array
//===========================================================================
// input & output:
//
//        ioInt { CATLONG32  * }   [iCnt][_RowSize]
//                               array to be sorted by increasing order
//===========================================================================

 void CATMathMultIntDirSort ( CATLONG32  * ioInt, CATLONG32  iCnt );
