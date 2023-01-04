// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathIntDirSort: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//
//---------------------------------------------------------------------------
//
//  function:         quick sort of the array ioInt on criterion
//                    type CATLONG32 
//                    direct sort, with memory move
//
//    sort of iCnt articles of _RowSize integers each, using a selective
//    sorting on the _CurCrit'th integer
//
//---------------------------------------------------------------------------
//
//  call:
//
//  CATMathIntDirSort ( ioInt, iCnt, oTemp )
//
//---------------------------------------------------------------------------
//  input:
//
//        iCnt  { CATLONG32  }     number of elements of ioInt
//
//---------------------------------------------------------------------------
//  input & output:
//
//        ioInt { CATLONG32  * }   [iCnt][_RowSize]
//                               array to be sorted
//                               ( variable type )
//        oTemp { * CATLONG32  }   temporary working area [_RowSize]
//
//---------------------------------------------------------------------------


   void CATMathIntDirSort
   ( CATLONG32  * ioInt, CATLONG32  iCnt, CATLONG32  * oTemp );

//---------------------------------------------------------------------------
