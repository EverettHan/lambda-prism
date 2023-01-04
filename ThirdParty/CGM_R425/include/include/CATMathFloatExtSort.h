// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathFloatExtSort: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//
//---------------------------------------------------------------------------
//
//  function:         quick sort of an array iFloat on criterion type float
//                    indirect sort, without memory move
//
//    sort of iCnt articles of _RowSize floats each, using a selective
//    sorting on the _CurCrit'th float
//
//    it differs from CATMathDoubleSort by the split of iFloat into the
//    array to be sorted and the separate array iNdir for indirection
//
//---------------------------------------------------------------------------
//
//  call:
//
//  CATMathFloatExtSort ( iFloat, ioIndir, iCnt, iMove );
//
//---------------------------------------------------------------------------
//  input:
//
//        iCnt  { CATLONG32  }     number of elements of iFloat
//        iMove { CATLONG32  }     start shifting on the working area
//                               ioIndir = iMove + (0,1,2,3,...)
//        iFloat { float * }     [iCnt][_RowSize]
//                               array to be sorted
//                               ( variable type )
//
//---------------------------------------------------------------------------
//  input & output:
//
//        ioIndir { CATLONG32  * } [iCnt]
//                               indirect index array
//
//---------------------------------------------------------------------------

   void CATMathFloatExtSort
   ( float * iFloat, CATLONG32  * ioIndir, CATLONG32  iCnt, CATLONG32  iMove );

//---------------------------------------------------------------------------
