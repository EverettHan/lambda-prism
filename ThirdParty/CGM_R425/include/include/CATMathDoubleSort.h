// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleSort: method belonging to CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//
//---------------------------------------------------------------------------
//
//  function:         quick sort of an array ioDou on criterion type double
//                    indirect sort, without memory move
//
//    sort of iCnt articles of _RowSize doubles each, using a selective
//    sorting on the _CurCrit'th double
//
//---------------------------------------------------------------------------
//
//  call:
//
//  CATMathDoubleSort ( ioDou, iCnt, iMove );
//
//---------------------------------------------------------------------------
//  input:
//
//        iCnt  { CATLONG32  }     number of elements of ioDou
//        iMove { CATLONG32  }     start shifting on the working area
//                               ioInt[_Indir] = iMove + (0,1,2,3,...)
//
//---------------------------------------------------------------------------
//  input & output:
//
//        ioDou { double * }     [iCnt][_RowSize]
//                               array to be sorted
//                               ( variable type )
//
//---------------------------------------------------------------------------
#include "CATDataType.h"

   void CATMathDoubleSort
   ( double * ioDou, CATLONG32  iCnt, CATLONG32  iMove );

//---------------------------------------------------------------------------
