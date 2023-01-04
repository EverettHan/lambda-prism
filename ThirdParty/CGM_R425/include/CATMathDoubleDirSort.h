// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathDoubleDirSort : method of CATMathSortedArray
//
//===========================================================================
// Function:         quick sort of an array on criterion type double
//
//    sorting of iCnt articles of _RowSize doubles using a selective sort
//    on the _CurCrit th double
//
//    direct sort, with memory move
//
//===========================================================================
// Usage notes:
//
//   CATMathDoubleDirSort ( ioDou, iCnt, oTemp );
//
//===========================================================================
// Input:
//
//        iCnt  { CATLONG32  }        number of rows (elements) of the array
//===========================================================================
// Input & output:
//
//        ioDou { double * }        [iCnt][_RowSize]
//                                  array to be sorted
//                                  ( variable type )
//        oTemp { double * }        temporary internal array [_RowSize]
//===========================================================================
#include "CATDataType.h"


 void CATMathDoubleDirSort ( double * ioDou, CATLONG32  iCnt, double * oTemp );
