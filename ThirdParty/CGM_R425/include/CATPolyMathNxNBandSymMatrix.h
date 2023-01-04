// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//=================================================================== 
//
// CATPolyMathNxNBandSymMatrix  :
// Square Symetric banded matrix of dimension _N, and bandwidth _B  
//
//===================================================================
// Usage notes:
//----------------
//   We define and manipulate square banded symetric matrix of dimension N
//   and bandwidth _B.
//   Only the lower part of the matrix is stocked : for example with _B=2
//   A=(m00,m10,m11,m21,m22,m32,m33,m43,m44...) ( A array of constructor )
//
//            | a0 *                     |
//            | a1 a2 *                  |
//            |    a3 a4 *               |
//        M = |       a5 a6 *            |
//            |          a7 a8 *         |
//            |             ............ |
//            |                 ak-2 ak-1|   k = _B*(2*_N-_B+1)/2
//
//   .. so you should pay attention when using SetCoeff or GetCoeff
//   method with indix i : 0<= i < _B*(2*_N-_B+1)/2.
//   ( Nevertheless, you can get a coefficient located by (row,col)
//   with col>row or |row_col|>=_B with the GetCoeff(row,column) method
//   and set a coefficient located by (row,col) with col>row and |row_col|<_B
//   with the SetCoeff(row,column) method.)
 
//   
//
//===================================================================



#ifndef CATPolyMathNxNBandSymMatrix_H  
#define CATPolyMathNxNBandSymMatrix_H 
 

#include "PolyMathUtils.h"
#include "CATDataType.h"



 

class ExportedByPolyMathUtils CATPolyMathNxNBandSymMatrix   
{ 
public: 
//
//- Constructor -------------------------------------------------------------

// 1- construction of matrix with sizes N & B ( not initialized to zero )  
  CATPolyMathNxNBandSymMatrix  (const CATLONG32 N, const CATLONG32 B); 
   
//  
//- Destructor ------------------------------------------------------------------ //  
  ~CATPolyMathNxNBandSymMatrix  ();
 

//
//------------------------------------------------------------------------------------
//- 1 Set all the coefficents of the matrix 
 
//
  void SetCoef (const double *A) ;
   
 
//---------------------------------------------------------------------------------
// - Solve AX=b A symetric definite positive using the Cholesky factorisation.
//  Matrix is unchanged, vector is changed
//
//-  iF is used when some coefficients of the solution X are imposed: iF[i]=0  X[i] is imposed
//																	  iF[i]=1  X[i] is computed
 
 
//
  void SolveCholesky( double *iob, const CATLONG32 *iF=0, CATPolyMathNxNBandSymMatrix  *iL=0);
	 		
   

//-----------------------------------------------------------------------------
//- Find the Cholesky factor C  A=CCt where A is the banded symetric matrix NxN
//  The matrix remains unchanged. C is lower matrix with same band _B than A.
  
//- C is given as a CATPolyMathNxNBandSymMatrix . 
//
   

  void Cholesky (CATPolyMathNxNBandSymMatrix  *C, const CATLONG32 * iF=0) ;

     

private:
//-------------------------------------------------------------------------------------   
//  Compute the modified b of Ax=b when some coefficients of the solution X are imposed
//
	void Modifie(double *iobx, const CATLONG32 *iF, const CATLONG32 iNbCol = 1 ) const;	

//---------------------------------------------------------------------   
// Used in SolveCholesky to solve L(tL)X=b
//
	void Resolution(double *iob, const CATPolyMathNxNBandSymMatrix  * iL, const CATLONG32 * iF=0) ;

 
//-------------------------------------------------------------------------------------
// data:



  CATLONG32 _M ; 
  CATLONG32 _N ;
  CATLONG32 _B ; 
  CATLONG32 _BBA;
  CATLONG32 _BBB;
  double *  _D ;
 
};  
#endif  
