// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleExtSort: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//
//---------------------------------------------------------------------------
//
//  function:         quick sort of an array iDou on criterion type double
//                    indirect sort, without memory move
//
//    sort of iCnt articles of _RowSize doubles each, using a selective
//    sorting on the _CurCrit'th double
//
//    it differs from CATMathDoubleSort by the split of iDou into the
//    array to be sorted and the separate array iNdir for indirection
//
//---------------------------------------------------------------------------
//
//  call:
//
//  CATMathDoubleExtSort ( iDou, ioIndir, iCnt, iMove );
//
//---------------------------------------------------------------------------
//  input:
//
//        iCnt  { CATLONG32  }     number of elements of iDou
//        iMove { CATLONG32  }     start shifting on the working area
//                               ioIndir = iMove + (0,1,2,3,...)
//        iDou { double * }      [iCnt][_RowSize]
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
#include "CATDataType.h"

   void CATMathDoubleExtSort
   ( double * iDou, CATLONG32  * ioIndir, CATLONG32  iCnt, CATLONG32  iMove );

//---------------------------------------------------------------------------
