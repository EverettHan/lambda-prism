// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathFloatDirSort : method of CATMathSortedArray
//
//===========================================================================
// Function:         quick sort of an array on criterion type float
//
//    sorting of iCnt articles of _RowSize floats using a selective sort
//    on the _CurCrit th float
//
//    direct sort, with memory move
//
//===========================================================================
// Usage notes:
//
//   CATMathFloatDirSort ( ioFloat, iCnt, oTemp );
//
//===========================================================================
// Input:
//
//        iCnt  { CATLONG32  }        number of rows (elements) of the array
//===========================================================================
// Input & output:
//
//        ioFloat { float * }       [iCnt][_RowSize]
//                                  array to be sorted ( variable type )
//        oTemp { float * }         temporary internal array [_RowSize]
//===========================================================================
#include "CATDataType.h"

 void CATMathFloatDirSort ( float * ioFloat, CATLONG32  iCnt, float * oTemp );
