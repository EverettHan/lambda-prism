// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathSortedArray: Sort / Search / Merge trilogy
//
//===========================================================================
// Usage notes:
//
//    Arrays are sorted by increasing order, on a simple or multiple
//    criterion of type double or int, using or not an indirect index.
//    The goal is a performance improvement:
//      when placing a new element into the array or
//      when merging 2 sorted arrays.
//    The indirect index avoids the memory move of whole rows during the
//    sort, but using such a sorted array implies 2 memory accesses instead
//    of one, each time one needs the "k-th row".
//
//===========================================================================
#ifndef CATMathSortedArray_H
#define CATMathSortedArray_H

struct As;
#include "YN000TRE.h"
#include "CATDataType.h"
#include "CATMathInline.h"

//---------------------------------------------------------------------------
class ExportedByYN000TRE CATMathSortedArray
{
 public:

   //----------------------------
   // constructors, destructor
   //----------------------------

   CATMathSortedArray (); 
   CATMathSortedArray ( const CATMathSortedArray& iOneOf ); 
   ~CATMathSortedArray (); 

   //-----------------------------------------------------------------------
   //     0 _ Object initialization
   //-----------------------------------------------------------------------
   //
   //  function:         given an array Array, one wants to privilege
   //                    its process according to the criterion of one or
   //                    several columns, which are of type double or int,
   //                    using or not an indirect index which occupies a
   //                    column of the array with the type int
   //
   //-----------------------------------------------------------------------
   //  input:
   //
   //        iUnitType { CATLONG32  } Array type:
   //                                  0 = int
   //                                  1 = double
   //                                  2 = float
   //        iRowSize { CATLONG32  }  Row size in
   //                                  words        if iUnitType = 0 or 2
   //                                  double words if iUnitType = 1
   //        iCritSize { CATLONG32  } Number of units of the sorting criterion
   //        ipCriterion { CATLONG32  * }
   //                               [iCritSize]
   //                               Ranks of the sorting criterion units, which
   //                               are of type iUnitType.
   //                               The rank of sorting column is such as
   //                                  0 <= ipCriterion[*] < iRowSize
   //
   //           ipCriterion[0] is the column used for the whole array.
   //           Then ipCriterion[1] is used for each subarray holding the
   //           same value in the column number ipCriterion[0].
   //           And so on for higher indices in ipCriterion.
   //
   //        iNdir { CATLONG32  }     Rank of the column, which holds the
   //                               definitive index into an int array
   //                               mapped on Array
   //                               ( 0 for the first word ).
   //                               Unused for direct sorting.
   //
   //           After indirect sort, ((int *) Array)[k][iNdir] points
   //           the row which comes at rank k in the alternative case of
   //           a direct sort.
   //
   //-----------------------------------------------------------------------
   
   CATMathSortedArray ( CATLONG32  iUnitType, CATLONG32  iRowSize,
                        CATLONG32  iCritSize, CATLONG32  * ipCriterion,
                        CATLONG32  iNdir );

   //-----------------------------------------------------------------------
   //     1 _ sorting an array on criterion type double with indirect index
   //-----------------------------------------------------------------------
#include "CATMathDoubleSort.h"

   //-----------------------------------------------------------------------
   //     2 _ sorting an array on multiple criterion type double with
   //         indirect index: CATMathMultDoubleSort
   //-----------------------------------------------------------------------

   //-----------------------------------------------------------------------
   //     3 _ search on an array sorted by DoubleSort
   //-----------------------------------------------------------------------
#include "CATMathDoubleSearch.h"

   //-----------------------------------------------------------------------
   //     4 _ merge of 2 arrays sorted by DoubleSort
   //-----------------------------------------------------------------------
#include "CATMathDoubleMerge.h"

   //-----------------------------------------------------------------------
   //     5 _ sorting an array on criterion type double with memory move
   //-----------------------------------------------------------------------
#include "CATMathDoubleDirSort.h"

   //-----------------------------------------------------------------------
   //     6 _ sorting an array on multiple criterion type double with
   //         memory move: CATMathMultDoubleDirSort
   //-----------------------------------------------------------------------

   //-----------------------------------------------------------------------
   //     7 _ search on an array sorted by DoubleDirSort
   //-----------------------------------------------------------------------
#include "CATMathDoubleDirSearch.h"

   //-----------------------------------------------------------------------
   //     8 _ merge of 2 arrays sorted by DoubleDirSort:
   //         CATMathDoubleDirMerge
   //-----------------------------------------------------------------------

   //-----------------------------------------------------------------------
   //     9 _ sorting an array on criterion type int with indirect index
   //-----------------------------------------------------------------------
#include "CATMathIntSort.h"

   //-----------------------------------------------------------------------
   //     10 _ sorting an array on multiple criterion type int with
   //          indirect index
   //-----------------------------------------------------------------------
#include "CATMathMultIntSort.h"

   //-----------------------------------------------------------------------
   //     11 _ search on an array sorted by IntSort
   //-----------------------------------------------------------------------
#include "CATMathIntSearch.h"

   //-----------------------------------------------------------------------
   //     12 _ merge of 2 arrays sorted by IntSort
   //-----------------------------------------------------------------------
#include "CATMathIntMerge.h"

   //-----------------------------------------------------------------------
   //     13 _ sorting an array on criterion type int with memory move
   //-----------------------------------------------------------------------
#include "CATMathIntDirSort.h"

   //-----------------------------------------------------------------------
   //     14 _ sorting an array on multiple criterion type int with
   //          memory move
   //-----------------------------------------------------------------------
#include "CATMathMultIntDirSort.h"

   //-----------------------------------------------------------------------
   //     15 _ search on an array sorted by IntDirSort
   //-----------------------------------------------------------------------
#include "CATMathIntDirSearch.h"

   //-----------------------------------------------------------------------
   //     16 _ merge of 2 arrays sorted by IntDirSort
   //-----------------------------------------------------------------------
#include "CATMathIntDirMerge.h"

   //-----------------------------------------------------------------------
   //     17 _ sorting an array on criterion type double with external
   //          indirect index
   //-----------------------------------------------------------------------
#include "CATMathDoubleExtSort.h"

   //-----------------------------------------------------------------------
   //     18 _ sorting an array on criterion type float with external
   //          indirect index
   //-----------------------------------------------------------------------
#include "CATMathFloatExtSort.h"

   //-----------------------------------------------------------------------
   //     19 _ search on an array sorted by FloatExtSort
   //-----------------------------------------------------------------------
#include "CATMathFloatExtSearch.h"

   //-----------------------------------------------------------------------
   //     21 _ sorting an array on criterion type float with memory move
   //-----------------------------------------------------------------------
#include "CATMathFloatDirSort.h"

   //-----------------------------------------------------------------------
   //     23 _ search on an array sorted by FloatDirSort
   //-----------------------------------------------------------------------
#include "CATMathFloatDirSearch.h"

   //-----------------------------------------------------------------------
   //     access to protected data
   //-----------------------------------------------------------------------

   INLINE void SetCurCrit ( const CATLONG32  iCurCrit );
   INLINE void SetIndir   ( const CATLONG32  iNdir );

 protected:

   CATLONG32      _UnitType       ; // 0 or 1: unit = int or double
   CATLONG32      _RowSize        ; // row size (number of units)
   CATLONG32      _CritSize       ; // number of criterions in a row
   CATLONG32      _CurCrit        ; // current criterion rank
   CATLONG32      _Indir          ; // indirect index (as int) rank
   CATLONG32    * _pCriterion     ; // ranks of _CritSize criterions in a row
   CATLONG32      _StatiCritere[8]; // avoids malloc / free

 private:
   //-----------------------------------------------------------------------
   // peculiar cases of CATMathDoubleSort, CATMathFloatExtSort
   //-----------------------------------------------------------------------

   void CATMathDoubleSort3
      ( double * ioDou, CATLONG32  iCnt, CATLONG32  iMove, struct As *iStack );

   void CATMathDoubleSort4
      ( double * ioDou, CATLONG32  iCnt, CATLONG32  iMove, struct As *iStack );

   void CATMathDoubleSort5
      ( double * ioDou, CATLONG32  iCnt, CATLONG32  iMove, struct As *iStack );

   void CATMathFloatExtSort3
      ( float * iFloat, CATLONG32  * ioIndir, CATLONG32  iCnt, CATLONG32  iMove,
        struct As *iStack );
};

//--------------------------------------------------------------------------
// INLINE implementations
//--------------------------------------------------------------------------

INLINE void CATMathSortedArray::SetCurCrit ( const CATLONG32  iCurCrit )
{   _CurCrit = iCurCrit;   }

INLINE void CATMathSortedArray::SetIndir   ( const CATLONG32  iNdir )
{   _Indir = iNdir;   }

//--------------------------------------------------------------------------
#endif
