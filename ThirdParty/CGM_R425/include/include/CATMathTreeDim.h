// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathTreeDim: performant representation class for parallelepipedic
//                 bounding boxes (1 to 3 dimensions)
//                 ( i.e. "blocs d' encombrement" or St Exupery's sheep )
//
//=============================================================================
// Usage notes: (sample)
//
//    #define DIMENS 3                      // Tridimensional
//    CATMathTreeDim Tree ( DIMENS, 16 );   // Binary tree of 16 boxes
//    double         Box[3][2] = { {-1., 1.}, {-1., 1.}, {-1., 1.} };
//                                          // Umin, Umax, Vmin, Vmax,...
//    double         Tol = 1.e-3;           // Tolerance
//    int            Lex[16 * 16], Lox[16]; // Exclude logical values
//    int            ContCnt, ContIdx, CmpIdx;
//
//    ContCnt = 16;
//    Tree->AddBox ( (double *) Box );      // 1st box
//    // fills 15 other boxes...
//    Tree->BuildTree ( Tol );              // build
//
//    Tree->BoolTree ( Lex );               // global compare 1st form
//    for ( ContIdx = 0;   ContIdx < ContCnt;   ContIdx++ )
//       for ( CmpIdx = 0;   CmpIdx < ContCnt;   CmpIdx++ )
//          if ( Lex[ CmpIdx + ContIdx * ContCnt ] == ( 1 << DIMENS ) - 1 )
//             < process 2 intersecting boxes >
//
//    // global compare 2nd form
//    for ( ContIdx = 0;   ContIdx < ContCnt;   ContIdx++ )
//       {
//       Tree->GetBox ( (double *) Box, ContIdx );
//       Tree->BoolBox ( (double *) Box, Lox );
//       for ( CmpIdx = 0;   CmpIdx < ContCnt;   CmpIdx++ )
//          if ( Lox[ CmpIdx ] == ( 1 << DIMENS ) - 1 )
//             < process 2 intersecting boxes >
//       }
//=============================================================================

#ifndef CATMathTreeDim_H
#define CATMathTreeDim_H

#include "YN000TRE.h"
#include "CATDataType.h"
class CATMathTreeBin;

#ifndef NULL
#define NULL 0
#endif

//-----------------------------------------------------------------------------
class ExportedByYN000TRE CATMathTreeDim
{
 public:

   //----------------------------
   // constructors, destructors
   //----------------------------

   CATMathTreeDim (); 

   //-----------------------------------------------------------------------
   //         1 _ creates a binary tree
   //-----------------------------------------------------------------------
   // input:
   //    iDim { int }        Space dimension, hereinafter so called
   //                        "space_dimension"
   //    iCnt { int }        Max number of boxes
   //-----------------------------------------------------------------------

   CATMathTreeDim ( const CATLONG32  iDim, CATLONG32  iCnt ); 

   CATMathTreeDim ( const CATMathTreeDim& iOneOf ); 
   ~CATMathTreeDim ();                        // not virtual

   //-----------------------------------------------------------------------
   //         2 _ adds a box to a binary tree
   //-----------------------------------------------------------------------
   // input:
   //    ipUvw { double * }  Pointer to an array of 2 * space_dimension
   //                        values =
   //                        ( xmin, xmax (, ymin, ymax (, zmin, zmax ) ) )
   //-----------------------------------------------------------------------

   void AddBox ( double * ipUvw );

   //-----------------------------------------------------------------------
   //         3 _ reads the iRank-th box of a binary tree
   //-----------------------------------------------------------------------
   // input:
   //    iRank { int }       Rank of the box in an existing tree
   //-----------------------------------------------------------------------
   // output:
   //    *ipUvw { doubles }  2 * space_dimension values =
   //                        ( xmin, xmax (, ymin, ymax (, zmin, zmax ) ) )
   //-----------------------------------------------------------------------

   void GetBox ( double * ipUvw, CATLONG32  iRank ) const;

   //-----------------------------------------------------------------------
   //         4 _ build of intervals binary trees
   //-----------------------------------------------------------------------
   // input:
   //    iTol { double }     Tolerance for extremities equality
   //-----------------------------------------------------------------------

   void BuildTree ( const double iTol );

   //-----------------------------------------------------------------------
   //         5 _ compare between one box and the N boxes of a binary tree
   //-----------------------------------------------------------------------
   // input:
   //    ipBorne { double * }   New box to be compared to an existing tree
   //                        ( xmin, xmax (, ymin, ymax (, zmin, zmax ) ) )
   //-----------------------------------------------------------------------
   // output:
   //    opExclu { int * }   Array of N integers:
   //                        opExclu[i]   ==   ( 1 << space_dimension ) - 1
   //                        if and only if the box i of the binary tree
   //                        and the box ipBorne are intersecting.
   //                        More precisely, the k-th bit of opExclu[i]
   //                        is 1 if the compared boxes have at least a
   //                        common point in their k-th dimension.
   //-----------------------------------------------------------------------

   void BoolBox ( double * ipBorne, CATLONG32  * opExclu, CATLONG32  * SizeopExclu = NULL );

   //-----------------------------------------------------------------------
   //         6 _ global compare of the N boxes of a tree, 2 by 2
   //-----------------------------------------------------------------------
   // output:
   //    opExclu { int * }   Array of N * N integers:
   //                        opExclu[i][j]   ==   ( 1 << space_dimension ) - 1
   //                        if and only if the boxes i and j are
   //                        intersecting.
   //                        More precisely, the k-th bit of opExclu[i][j]
   //                        is 1 if the boxes i and j have at least a
   //                        common point in their k-th dimension.
   //                        Nota bene: both opExclu[i][j] and opExclu[j][i]
   //                                   are filled.
   //-----------------------------------------------------------------------

   void BoolTree ( CATLONG32  * opExclu );

 protected:

   CATLONG32                  _Dimens         ; // space dimension: 2 or 3
   CATMathTreeBin         * _pBin[3]        ; // array of 2 or 3 trees
   char                   * _pChar          ; // pour new surcharge
};

#endif
