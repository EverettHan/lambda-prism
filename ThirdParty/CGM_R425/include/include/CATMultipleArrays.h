#ifndef CATMultipleArrays_h
#define CATMultipleArrays_h
//==========================================================================
//
// Multiple array management in a single allocation
// (intended to allow ease of use and reliability rather than performance)
// (for more general purpose see ALOGEN)
//
// - CATMultipleLongArrays
// - CATMultipleDoubleArrays
//
// Use:
// - Object declaration
// - As many calls to Declare() as necessary in order to declare and initialize to NULL each sub array pointer
// - Allocate() pour for array allocation and all sub array pointers update
// - Object destruction for array free and all sub array pointers reset to NULL
//
//   Ex: (volatile declaration is optional, depending for example on post-exception treatment necessity)
//   CATDoubleArrays DoubleArrays;
//   double * volatile Array1 =  DoubleArrays.Declare(Array1     , Size1);
//   double * volatile Array2 =  DoubleArrays.Declare(Array2     , Size2);
//   DoubleArrays.Allocate(); // Array1 and Array2 will automatically be updated
//   int i;
//   for (i = 0, i < Size1; i++)
//      Array1[i] = 0.0;
//   for (i = 0, i < Size2; i++)
//      Array2[i] = 0.0;
//
//==========================================================================
// 04/05/12 NLD Creation de CATMultipleArrays, CATMultipleLongArrays, CATMultipleDoubleArrays
//              en interne de CATFrFNurbsBipar
// 04/01/18 NLD Externalisation dans framework Mathematics
//==========================================================================


#include "CATDataType.h"
#include "CATListPV.h"
#include "CATListOfInt.h"
#include "CATMathematics.h"

//==========================================================================
// DO NOT USE DIRECTLY
//==========================================================================
class ExportedByCATMathematics CATMultipleArrays
  {
   protected:
   int          _Size      ;
   //                        // parametrer les tailles par defaut pour eviter les allocations?
   CATListPV    _Arrays    ;
   CATListOfInt _ArraySizes;

                      CATMultipleArrays      ();
  virtual            ~CATMultipleArrays      ();
   // Declares the pointer to an array, and its size (number of elements)
           void       Declare                (void     *& Array ,
                                              int         iSize );

   // Allocates all arrays and updates pointers
   virtual void       Allocate               () = 0;


   // Free all arrays and updates pointers
           void       Free                   ();

  };
//--------------------------------------------------------------------------
class ExportedByCATMathematics CATMultipleLongArrays : public CATMultipleArrays
  {
   protected:
   CATLONG32*   _LongAlloc;
   public:
                      CATMultipleLongArrays  ();
   virtual           ~CATMultipleLongArrays  ();
   // Declares the pointer to an array, and its size (number of elements)
           CATLONG32* Declare                (CATLONG32*& Array ,
                                              int         iSize );
           void       Allocate               ();
  };

//--------------------------------------------------------------------------
class ExportedByCATMathematics CATMultipleDoubleArrays : public CATMultipleArrays
  {
   protected:

   double*      _DoubleAlloc;

   public:
                      CATMultipleDoubleArrays();
   virtual           ~CATMultipleDoubleArrays();
   // Declares the pointer to an array, and its size (number of elements)
           double   * Declare                (double   *& Array ,
                                              int         iSize );
           void       Allocate               ();
  };
#endif
