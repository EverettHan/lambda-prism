// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathMultIntSort : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//  CATMathMultIntSort ( ioInt, iCnt, iMove );
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
//    indirect sort, without memory move
//
//===========================================================================
// input:
//
//        iCnt  { CATLONG32  }     number of elements of the array
//        iMove { CATLONG32  }     displacement on start of the working area
//                               ioInt[_Indir] = iMove + (0,1,2,3,...)
//===========================================================================
// input & output:
//
//        ioInt { CATLONG32  * }   [iCnt][_RowSize]
//                               array to be sorted by increasing order
//===========================================================================


 void CATMathMultIntSort ( CATLONG32  * ioInt, CATLONG32  iCnt, CATLONG32  iMove );
