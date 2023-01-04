// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathPackedArray: Sort / Search on packed arrays
//
//===========================================================================
// Usage notes:
//
//    Arrays are sorted by increasing order, on a simple or multiple
//    criterion of type float, double or int, using or not an indirect index.
//    The goal is a performance improvement:
//      when placing a new element into the array or
//      when merging 2 sorted arrays.
//    The indirect index avoids the memory move of whole rows during the
//    sort, but using such a sorted array implies 2 memory accesses instead
//    of one, each time one needs the "k-th row".
//
//    The packaging of arrays lies on a grid: each criterion divides the
//    whole array on the basis of an origin ( <= smallest value ) and a
//    step ( packs are of identical dimensions ).
//
//===========================================================================
#ifndef CATMathPackedArray_H
#define CATMathPackedArray_H

#include "CATMathSortedArray.h"
#include "YN000TRE.h"

//---------------------------------------------------------------------------
class ExportedByYN000TRE CATMathPackedArray : public CATMathSortedArray
{
 public:

   //----------------------------
   // constructors, destructor
   //----------------------------

   CATMathPackedArray (); 
   CATMathPackedArray ( const CATMathPackedArray& iOneOf ); 
   ~CATMathPackedArray (); 

   //-----------------------------------------------------------------------
   //     0 _ object initialization
   //-----------------------------------------------------------------------
   //
   //  function:         given an array Array, one wants to privilege
   //                    its process according to the criterion of one or
   //                    several columns, which are of type float, double
   //                    or int, using or not an indirect index which
   //                    occupies a column of the array with the type int
   //
   //-----------------------------------------------------------------------
   //  input:
   //
   //     iUnitType { CATLONG32  } Array type:
   //                               0 = int
   //                               1 = double
   //                               2 = float
   //     iRowSize { CATLONG32  }  Row size in
   //                               words        if iUnitType = 0 or 2
   //                               double words if iUnitType = 1
   //     iCritSize { CATLONG32  } Number of units of the sorting criterion
   //     ipCriterion { CATLONG32  * }
   //                            [iCritSize]
   //                            Ranks of the sorting criterion units,
   //                            which are of type iUnitType.
   //                            The rank of sorting column is such as
   //                               0 <= ipCriterion[*] < iRowSize
   //
   //        ipCriterion[0] is the column used for the whole array.
   //        Then ipCriterion[1] is used for each subarray holding the
   //        same value in the column number ipCriterion[0].
   //        And so on for higher indices in ipCriterion.
   //
   //     iNdir { CATLONG32  }     Rank of the column, which holds the
   //                            definitive index into an int array
   //                            mapped on Array
   //                            ( 0 for the first word ).
   //                            Unused for direct sorting.
   //
   //        After indirect sort, ((int *) Array)[k][iNdir] points
   //        the row which comes at rank k in the alternative case of
   //        a direct sort.
   //
   //     iOrigin { (typed by iUnitType) * }
   //                            [iCritSize]
   //                            Lower limit of the first pack, less or
   //                            equal to the smallest value in the array.
   //                            Applied for each criterion component.
   //
   //     iStep { (typed by iUnitType) * }
   //                            [iCritSize]
   //                            Constant size of the packs.
   //                            Applied for each criterion component.
   //
   //        Be careful numerically, with type double or float:
   //        set L[k] the upper limit of the k-th pack, with the
   //        convention L[0] = iOrigin
   //        Then L[k] = L[k-1] + iStep, but never L[k] = L[0] + k * iStep
   //
   //-----------------------------------------------------------------------
   
   CATMathPackedArray ( CATLONG32  iUnitType, CATLONG32  iRowSize,
                        CATLONG32  iCritSize, CATLONG32  * ipCriterion,
                        CATLONG32  iNdir,     void     * iOrigin,
                        void     * iStep );

   //-----------------------------------------------------------------------
   //     1 _ packing an array on multiple criterion type float with
   //         memory move (quick sort algorithm)
   //-----------------------------------------------------------------------
   //     iCnt  { CATLONG32  }        number of elements of the array
   //     ioFloat { float * }       [iCnt][_RowSize]
   //                               array to be sorted by increasing order
   //     iPackCnt { CATLONG32  * }   [_CritSize]
   //                               allocation sizes of oPack
   //     oPack { CATLONG32  * }      [iPackCnt[0]][iPackCnt[1]][iPackCnt[2]]...
   //                               ranks of the computed packs in ioFloat
   //
   //     note: when this method finishes, _CurCrit is automatically
   //           reset to *_pCriterion
   //-----------------------------------------------------------------------

   void CATMathFloatDirPackSort ( float    * ioFloat, CATLONG32  iCnt,
                                  CATLONG32  * iPackCnt, CATLONG32  * oPack );

   //-----------------------------------------------------------------------
   //     2 _ packing an array on multiple criterion type float with
   //         external indirect index (quick sort algorithm)
   //-----------------------------------------------------------------------
   //     iCnt  { CATLONG32  }        number of elements of the array
   //     iFloat { float * }        [iCnt][_RowSize]
   //                               array to be sorted by increasing order
   //     oIndir { CATLONG32  * }     [iCnt]
   //                               indirect index array
   //     iPackCnt { CATLONG32  * }   [_CritSize]
   //                               allocation sizes of oPack
   //     oPack { CATLONG32  * }      [iPackCnt[0]][iPackCnt[1]][iPackCnt[2]]...
   //                               ranks of the computed packs in ioFloat
   //
   //     note: when this method finishes, _CurCrit is automatically
   //           reset to *_pCriterion
   //-----------------------------------------------------------------------

   void CATMathFloatExtPackSort ( float    * iFloat, CATLONG32  iCnt,
                                  CATLONG32  * oIndir,
                                  CATLONG32  * iPackCnt, CATLONG32  * oPack );

   //-----------------------------------------------------------------------
   //     3 _ apply the external indirect index to the array ioFloat
   //         by substitution on itself ( after CATMathFloatExtPackSort )
   //-----------------------------------------------------------------------
   //     iCnt  { CATLONG32  }        number of elements of the array
   //     ioFloat { float * }       [iCnt][_RowSize]
   //                               array on which the indirection is applied
   //     iNdir { CATLONG32  * }      [iCnt]
   //                               indirect index array
   //     oTempRow { float * }      [_RowSize]
   //                               internal working area
   //-----------------------------------------------------------------------

   void CATMathFloatExtIndApply ( float    * ioFloat, CATLONG32  iCnt,
                                  CATLONG32  * iNdir,  float * oTempRow );

   //-----------------------------------------------------------------------
   //     4 _ apply the external indirect index to the array ioBit
   //         by substitution on itself
   //-----------------------------------------------------------------------
   //     iCnt  { CATLONG32  }        number of bits of the array
   //     ioBit { CATULONG32   * }      [1 + iCnt / 32]
   //                               array on which the indirection is applied
   //     iNdir { CATLONG32  * }      [iCnt]
   //                               indirect index array
   //-----------------------------------------------------------------------

   void CATMathBitExtIndApply
      ( CATULONG32   * ioBit, CATLONG32  iCnt, CATLONG32  * iNdir );

   //-----------------------------------------------------------------------
   //     5 _ search inside an array packed by FloatDirPackSort
   //-----------------------------------------------------------------------
   //     iPla { * float }          [_RowSize]
   //                               element to be inserted in a pack
   //     CATMathFloatDirPackSearch { CATLONG32  }
   //                               0 <= CATMathFloatDirPackSearch <
   //                                    product of all iPackCnt
   //                               pack rank in which one takes a place
   //-----------------------------------------------------------------------

   CATLONG32  CATMathFloatDirPackSearch ( float * iPla );

 protected:

   void       * _Origin         ; // [_CritSize] lower limit of the 1st pack
                                  // type defined by _UnitType
   void       * _Step           ; // [_CritSize] constant size of each pack
                                  // type defined by _UnitType
   double       _StatiOrigin[8] ; // avoids malloc/free
   double       _StatiStep[8]   ; // avoids malloc/free
   CATLONG32      _StatiPack[8]   ; // avoids malloc/free
   CATLONG32    * _PackCnt        ; // [_CritSize] numbers of packs
   CATLONG32    * _Pack           ; // [_PackCnt[0]][_PackCnt[1]]...
                                  // ranks of the packs in iFloat
   CATLONG32    * _ExtIndir       ; // single array for indirection index
   CATLONG32    * _StepPack       ; // advance in _Pack for each dimension
   CATLONG32      _TotalPack      ; // _StepPack[0] * _PackCnt[0]
};

//--------------------------------------------------------------------------
#endif
