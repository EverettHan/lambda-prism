// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//=================================================================== 
//
// CATMathNxNBandSymMatrix :
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
//-----------------------------------------------------
//   Symetric band/ Symetric band positive definite :
//-----------------------------------------------------
//   1 - For symetric definite positive matrices use fast methods, 
//   deriving of Cholesky factorisation : DeterminantCholeky, 
//   DeterminantFastCholesky, SolveCholesky, InverseCholesky.
//   2 - For other symetric matrices, use slower methods :
//   Determinant, DeterminantFast, Solve ( best so far,
//   ( best so far, those methods don't use the symetry and 
//   the sparsness of the matrix).
//   3 - January 2000: The LDLt methods are almost as fast as the
//   Cholesky metods but open for in-definite cases.
//
//===================================================================



#ifndef CATMathNxNBandSymMatrix_H  
#define CATMathNxNBandSymMatrix_H 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"
#include "CATMathDiagnostic.h"

#include "CATMathNxNFullSymMatrix.h"

class CATMathNxNMatrix;
class CATMathMxNMatrix;

class ExportedByYN000FUN CATMathNxNBandSymMatrix : public CATMathNxNFullSymMatrix 
{ 
public: 
//
//- Constructor -------------------------------------------------------------
// 0- default constructor 
// 1- construction of matrix with sizes N & B ( not initialized to zero )
// 2- construction of matrix with sizes N & B ( diagonal initialized to a, other terms
//    initialized to 0.
// 3- construction of matrix with sizes N & B, initialization with A.
// 4- copy constructor
// 5- construction from a right (=square banded symetric) rectangular matrix and a 
//    band width.
// 6- construction from a right (=banded) symetric matrix and a bandwidth.
// 
  CATMathNxNBandSymMatrix ();
  CATMathNxNBandSymMatrix (const CATLONG32 N, const CATLONG32 B); 
  CATMathNxNBandSymMatrix (const CATLONG32 N, const CATLONG32 B, const double & a);
  CATMathNxNBandSymMatrix (const CATLONG32 N, const CATLONG32 B, const double *A);
  CATMathNxNBandSymMatrix (const CATMathNxNBandSymMatrix & copy);
  CATMathNxNBandSymMatrix (const CATMathMxNMatrix & base, const CATLONG32 B);
  CATMathNxNBandSymMatrix (const CATMathNxNFullSymMatrix & base, const CATLONG32 B);
//  
//- Destructor ------------------------------------------------------------------ 
//  
  ~CATMathNxNBandSymMatrix ();
//  
//- Operator = ------------------------------------------------------------------
//
  CATMathNxNBandSymMatrix & operator= (const CATMathNxNBandSymMatrix & equals);
//
//- Get the size/Band of the matrix. --------------------------------------------- 
//  
  CATLONG32 GetSizeOfMatrix () const ;  
  CATLONG32 GetBandOfMatrix () const ; 
//
//- Set the size of the matrix. --------------------------------------------- 
//  
  void SetSizeOfMatrix (const CATLONG32 N) ;  

//
//- Get the type of the matrix. --------------------------------------------- 
//  
  CATMathMatrixType GetTypeOfMatrix () const ; 

//
//------------------------------------------------------------------------------------
//- 1 Set all the coefficents of the matrix 
//- 2 Set the coefficent of the matrix repered by (row,column ) 0 <= row,column <= N-1
//- 3 Set the coefficent  repered by iIndex  0<= iIndex < _B*(2*_N-_B+1)/2. (see introduction)
//- 4 Set a block of coefficents of the matrix repered by index
//      0 <= start < end < _B*(2*_N-_B+1)/2
//- 5 Reset : all coefficients Set to zero
//
  void SetCoef (const double *A) ;
  void SetCoef (const CATLONG32 row, const CATLONG32 column, const double A) ; 
  void SetCoef (const CATLONG32 iIndex, const double A) ; 
  void SetCoef (const CATLONG32 start, const CATLONG32 end, const double *A) ; 
  void Reset();
//
//------------------------------------------------------------------------------------
//- 1 Get a coefficient of the matrix  0 <= row,column <= N-1
//- 2 Get one of the coefficients of the matrix with the generalized index
//  0 <= iIndex < B*(2N-B+1)/2 
//- 3 Get all the coefficents of the matrix
// 
  double GetCoef (const CATLONG32 row, const CATLONG32 column) const ;
  double GetCoef (const CATLONG32 iIndex) const; 
  double *GetCoef () const ;
//
//- Return a pointer to the private data _D of the Matrix, containing coefficients
//  in the following form :
//  a_{row, col} = _D[row*(row+1)/2+col] if row<_B-1, and row<=col
//  a_{row, col} = _D[_B*(-_B+3)/2-1 + (_B-1)*row+col] if row>=_B-1 and row<=col
//  a_{row, col} = a_{col, row} if row>col
//  a_{row, col} = 0 if (row-col>=_B) or (col-row>=_B)
	const double * GetBandSymCoef();
//  
//- Get the trace of the matrix -----------------------------------------------------
//  
  double Trace () const ;
//
//- Get the matrice's Schur's norm ||A||s =sqrt(Sum ij Aij*Aij)---------------
//
  double SchurNorm () const ;
//  
//- Determinant -----------------------------------------------------------------
//  1. the matrix remains unchanged.  
//  2. the definite positive matrix remains unchanged
//  3. the definite positive matrix is changed
//  
  double Determinant () ;
  double DeterminantCholesky () ;
  double DeterminantFastCholesky () ;
//  
//- Multiply the matrix by a vector of dimension N ----------------------------------- 
//- 1 output = Multiply 
//- 2 input vector iv, output vector oMv
//
  double * Multiply (const double *v) const ;
  void  Multiply (const double *iv, double *oMv) const ;
//  
//- Multiply *this by iA and put the result in oB
//
  void  Multiply (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;
//
//-----------------------------------------------------------------------------
// Four methods using LDLt factorization. The matrix may be indefinite.
// A is "this" matrix and is of size NxN. :

//- Solves AX=B where B (= *iobx) contains the coeficients of a NxNbCol matrix. 
//  B is modified to X.
//
	virtual CATMathDiagnostic Solve (double *iobx, const CATLONG32 iNbCol=1) const ; 
//
//- Solves AX=B. B (= *ib) and X (= *ox) contain the coeficients of two NxNbCol matrices.
//	B remains unchanged.
//
	virtual CATMathDiagnostic Solve (const double *ib, double *ox, const CATLONG32 iNbCol=1) const ;

//- Solves AX=B where B (= *iobx) contains the coeficients of a NxNbCol matrix. 
//  B is modified to X.
//  Imposition: If iF[i]=0, X[i] is imposed. If iF[i]=1, X[i] is computed. 
//  The size of iF is N. 
//
	virtual CATMathDiagnostic Solve (double *iobx, const CATLONG32 *iF, const CATLONG32 iNbCol=1) const ;
   
//- Calculates the inverse of A.
//
	virtual CATMathDiagnostic Inverse (CATMathNxNFullSymMatrix *M) const ;

//
//---------------------------------------------------------------------------------
//- Solve a AX=B where A is the matrix NxN
// bx is a NxNbCol matrix
// Attention: The matrix and vector are modified
//
//  CATMathDiagnostic  Solve (double *iobx, const CATLONG32 iNbCol=1) ;
//
//- Solve a AX=B where A is the matrix NxN
//  b and x are NxNbCol matrix
//  The matrix remains unchanged.
//
//  CATMathDiagnostic  Solve (const double *ib, double *ox, const CATLONG32 iNbCol=1) const;

//---------------------------------------------------------------------------------
// - Solve AX=b A symetric definite positive using the Cholesky factorisation.
//  Matrix is unchanged, vector is changed
//
//-1 iF is used when some coefficients of the solution X are imposed: iF[i]=0  X[i] is imposed
//																	  iF[i]=1  X[i] is computed
//	 iL is used when the system AX=b is solved several times with the same A, the same iF and different b
//   iL must be the matrix computed with the Cholesky method
//
//-2 SolveCholesky used when the system AX=b is solved NbVect times with the same A,
//   the same iF and different b
//
  CATMathDiagnostic SolveCholesky( double *iob, const CATLONG32 *iF=0, CATMathNxNBandSymMatrix *iL=0);
	 		
  CATMathDiagnostic SolveCholesky( double **iob, const CATLONG32 NbVect=1, const CATLONG32 *iF=0);

//-----------------------------------------------------------------------------
//- Find the Cholesky factor C  A=CCt where A is the banded symetric matrix NxN
//  The matrix remains unchanged. C is lower matrix with same band _B than A.
//-1 C is given as a full matrix.  
//-2 C is given as a CATMathNxNBandSymMatrix. 
//
  CATMathDiagnostic  Cholesky (CATMathNxNMatrix *C) ;

  CATMathDiagnostic  Cholesky (CATMathNxNBandSymMatrix *C, const CATLONG32 * iF=0) ;

//-----------------------------------------------------------------------------
//- Define the inverse of a symetric positive definite matrix ( caution inverse 
//  is not banded ... type CATMathNxNFullSymMatrix )
//
  CATMathDiagnostic InverseCholesky (CATMathNxNFullSymMatrix *M);
//
// This method exists on non-officiel for debug.-------------------------------
//
  friend ostream & operator<< (ostream &op, const  CATMathNxNBandSymMatrix &);
//

//---------------------------------------------------------------------   
// Overload operator
//---------------------------------------------------------------------   

//- Self Product by a scalar
CATMathNxNBandSymMatrix & operator *=(const double alpha) ;      

private:
//-------------------------------------------------------------------------------------   
//  Compute the modified b of Ax=b when some coefficients of the solution X are imposed
//
	void Modifie(double *iobx, const CATLONG32 *iF, const CATLONG32 iNbCol = 1 ) const;	

//---------------------------------------------------------------------   
// Used in SolveCholesky to solve L(tL)X=b
//
	void Resolution(double *iob, const CATMathNxNBandSymMatrix * iL, const CATLONG32 * iF=0) ;

//-------------------------------------------------------------------------------------
// Used in LDLt factorization.

	// Shifts row and column k by row and column p. k < p. (Total size is generally increased!)
	CATLONG32 BandSymmetricPivot (CATLONG32 size, CATLONG32 *diag, CATLONG32 maxLDsize, double *ioLD, CATLONG32 *piv, 
							 CATLONG32 k,    CATLONG32 p,     CATLONG32 *insert,   CATLONG32 addBeforeK = 0 ) const ;
	
	// Does the LDLt factorization Obs: The inverse of D is stored in the diagonal!
	CATLONG32 FactorizeLDLtBand (CATLONG32 size, CATLONG32 *ioDiag, CATLONG32 maxLDsize, double *ioLD, CATLONG32 *piv, 
							unsigned int *block ) const ;
	
	// Solves the equations.	
	void SolveLDLtBand (CATLONG32 size, CATLONG32 *iDiag, double *iLD, CATLONG32 *piv, unsigned int *block, 
						CATLONG32 inrX, double *ioX ) const ; 	

	// Extracts a sub matrix. Used when a part of the solution is imposed. 
	// Also modifies iobx. See the use of iF earlier. 
	void ExtractLDLtBand (CATLONG32 size, const CATLONG32 *iF, CATLONG32 *ioDiag, double *oLD, double *data ) const ;	
//-------------------------------------------------------------------------------------
// data:

  // Band width
  CATLONG32 _B; 
  
  // Array to store the coef
  double * _D ;

  //numbers often used in this class
  // _BB = (_B*(2*_N -_B+1))/2 : size of the array _D
  /** @c++ansi fbq 2004-08-06.14:09:31 [_BB already #defined in xlocinfo.h:#define _BB _CONTROL] **/
#if defined(_MSC_VER) && (_MSC_VER>=1310)
#undef _BB
#endif
  CATLONG32 _BB;
  // _BBB = _B*(3 -_B))/2 - 1
  CATLONG32 _BBB;
};  
#endif  
