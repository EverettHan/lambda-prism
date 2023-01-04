// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathIntSort : method of CATMathSortedArray
//
//===========================================================================
// Usage notes:
//
//  CATMathIntSort ( ioInt, iCnt, iMove );
//
//===========================================================================
//
// function:         quick sort of an array on criterion type integer
//
//    sorting of iCnt articles of _RowSize integers using a selective sort
//    on the _CurCrit th integer
//
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
//                               array to be sorted
//===========================================================================
#include "CATDataType.h"

 void CATMathIntSort ( CATLONG32  * ioInt, CATLONG32  iCnt, CATLONG32  iMove );
