// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//=================================================================== 
//
// CATMathNxNFullSymMatrix :
// Square Symetric matrix of dimension N  
//
//===================================================================


//===================================================================
// Usage notes:
//
//   We define and manipulate square symetric matrix of dimension N
//   Only the lower part of the matrix is stocked L=(a00,a10,a11,a20,a21,a22...)
//   .. so you should pay attention when using SetCoef or GetCoef
//   method with indix i : 0<= i < N(N+1)/2.
//   ( Nevertheless, you can get or set a coefficient located by (row,col)
//   with col>row with the GetCoeff(row,column) method. )
//  -----------------------------------------
//   Symetric/ Symetric positive definite :
//   1 - For symetric matrices, use Determinant, DeterminantFast, Solve 
//   matrices ( best so far, those methods don't use the symetry of matrix ).
//   2 - For symetric definite positive matrices use faster method, 
//   deriving of Cholesky factorisation: DeterminantCholeky, 
//   DeterminantFastCholesky, SolveCholesky, InverseCholesky.
//
//===================================================================
// 12Jul17 KJD Addition of _NMax (initial dimension used for memory allocation)
//             which can be different from _N
//===================================================================
#ifndef CATMathNxNFullSymMatrix_H  
#define CATMathNxNFullSymMatrix_H 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "CATMathNxNMatrix.h"

#include "CATMathDiagnostic.h"
#include "CATMathLimits.h"
#include "CATMath3x3Matrix.h"
#include "CATTolerance.h"

class CATMathMxNMatrix;
class CATMathNxNBandSymMatrix;

class ExportedByYN000FUN CATMathNxNFullSymMatrix : public CATMathNxNMatrix 
{ 

public: 
//
//- Constructor -------------------------------------------------------
//
// 0- default constructor
// 1- Size N not initialized
// 2- Size N initialized  M(row,col) = A[row*(row+1)/2+col]
// 3- Size N, diagonal initialized to a, other terms to 0
// 4- copy constructeur
// 5- conversion from a right(=symetric) CATMathMxNMatrix
// 6- conversion from a CATMathNxNBandSymMatrix
//
  CATMathNxNFullSymMatrix ();
  CATMathNxNFullSymMatrix (const CATLONG32 N);
  CATMathNxNFullSymMatrix (const CATLONG32 N, const double *A);
  CATMathNxNFullSymMatrix (const CATLONG32 N, const double & a);
  CATMathNxNFullSymMatrix (const CATMathNxNFullSymMatrix & copy);
  CATMathNxNFullSymMatrix (const CATMathMxNMatrix & base);
  CATMathNxNFullSymMatrix (const CATMathNxNBandSymMatrix & base);
//  
//- Destructor -------------------------------------------------------------- 
//  
  virtual ~CATMathNxNFullSymMatrix ();
//  
//- operator = --------------------------------------------------------------- 
//
  virtual CATMathNxNFullSymMatrix & operator= (const CATMathNxNFullSymMatrix & equals) ;
//- Get the size of the matrix. ---------------------------------------------- 
//  
  virtual CATLONG32 GetSizeOfMatrix () const ; 

//
//- Get the type of the matrix. ---------------------------------------------- 
//  
  virtual CATMathMatrixType GetTypeOfMatrix () const ; 

//
//- Set the size of the matrix. --------------------------------------------- 
//  
  virtual void SetSizeOfMatrix (const CATLONG32 N) ;  

//------------------------------------------------------------------------------------
//- 1 Set all the coefficents of the matrix 
//- 2 Set the coefficent of the matrix repered by (row,column ) 0 <= row,column <= N-1
//- 3 Set the coefficent  repered by iIndex= (row*(row+1))/2+col < N(N+1)/2
//- 4 Set a block of coefficents of the matrix reperd by index
//      0 <= start <= (N*(N+1))/2-1 ;  start < end <=(N*(N+1))/2-1
//- 5 Reset : Set all coefficients to zero. 
//
   virtual void SetCoef (const double *A) ;
   virtual void SetCoef (const CATLONG32 row, const CATLONG32 column, const double A) ; 
   virtual void SetCoef (const CATLONG32 iIndex, const double A) ; 
   virtual void SetCoef (const CATLONG32 start, const CATLONG32 end, const double *A) ;
   virtual void Reset ();

//------------------------------------------------------------------------------------
// Let *this have the block form A = (A1, A2)
//                                   (A3, A4)
// with A1 of size iIndex x iIndex and A4 of size (N-iIndex) x (N-iIndex)
// and let a = (x1, y, x2) with x1 of size iIndex, y of size 1, x2 of size (N-iIndex)
// The method modifies *this to A = (A1, x1^t, A2)
//                                  (x1, y,    x2)   
//                                  (A3, x2^t, A4)
//
   virtual void InsertRowAndColumn(const double *a, const CATLONG32 iIndex);

//Reverse of the above
   virtual void RemoveRowAndColumn(const CATLONG32 iIndex);
//
//------------------------------------------------------------------------------------
//- 1 Get a coefficient of the matrix  0 <= row,column <= N-1
//- 2 Get one of the coefficents of the matrix with the generalized index
//    0 <= iIndex < N(N+1)/2 : iIndex=row*(row+1)/2+col
//- 3 Get all the coefficents of the matrix
// 
   virtual double GetCoef (const CATLONG32 row, const CATLONG32 column) const ;
   virtual double GetCoef (const CATLONG32 iIndex) const; 
   virtual double *GetCoef () const ;
   virtual const double *GetFullSymMatrixCoef () const ;

//
//- Compute the transposate of a matrix -----------------------------------------------------
//
   virtual       void              Transpose () ;

// -Computes iA*(*this)*iA^t
   virtual void ConjugateMatrix(const CATMathMxNMatrix &iA) ;
 
//  
//- Get the trace of the matrix -----------------------------------------------------
//  
   virtual double Trace () const ;
//
//- Get the matrice's Schur's norm ||A||s =sqrt(Sum ij Aij*Aij)---------------
//
   virtual double SchurNorm () const ;
//  
//- Determinant,----------------------------------------------------------------
//  1. the matrix remains unchanged (for any matrix...)   
//  2. the definite positive matrix remains unchanged
//  3. the definite positive matrix is changed
//  
   virtual double Determinant () ;
   virtual double DeterminantCholesky () ;
   virtual double DeterminantFastCholesky () ;
//  
//- Multiply the matrix by a vector of dimension N ----------------------------------- 
//
   virtual double * Multiply (const double *v) ;
   virtual void  Multiply (const double *iv, double *oMv);
//  
//- Multiply *this by iA and put the result in oB
//
   virtual void  Multiply (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;

//-----------------------------------------------------------------------------
// Five methods using LDLt factorization. The matrix may be indefinite.
// A is "this" matrix and is of size NxN. Only "Inverse()" changes A. :

//- Solves AX=B where B (= *iobx) contains the coeficients of a NxNbCol matrix. 
//  B is modified to X.
//
   virtual CATMathDiagnostic Solve (double *iobx, const CATLONG32 iNbCol=1) const ;
//
//- Solves AX=B. B (= *ib) and X (= *ox) contain the coeficients of two NxNbCol matrices.
//   B remains unchanged.
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
   virtual CATMathDiagnostic Inverse () ;
   virtual CATMathDiagnostic Inverse (CATMathNxNFullSymMatrix *M) const ;

//-----------------------------------------------------------------------------
// Methods using Cholesky factorization. The matrix must be positive definite!
//
// - Solve AX=b A symetric definite positive using the Cholesky 
// factorisation. Matrix is unchanged, vector is changed.
//
//-1 iF is used when some coefficients of the solution X are imposed: iF[i]=0  X[i] is imposed
//                                                     iF[i]=1  X[i] is computed
//    iL is used when the system AX=b is solved several times with the same A, the same iF and different b
//   iL must be the matrix computed with the Cholesky method
//
   virtual CATMathDiagnostic SolveCholesky ( double *iob, const CATLONG32 *iF=0,   CATMathNxNFullSymMatrix *iL=0);
//
//-----------------------------------------------------------------------------
//- Find the Cholesky factor L  A=LLt where A is the symetric matrix NxN
//  A The matrix remains unchanged.
//
   virtual CATMathDiagnostic Cholesky(CATMathNxNFullSymMatrix *C, const CATLONG32 * iF=0) ;

//
//-----------------------------------------------------------------------------
//- Define the inverse of a symetric positive definite matrix
//
   virtual CATMathDiagnostic InverseCholesky(CATMathNxNFullSymMatrix *M) const;

   virtual CATMathDiagnostic FastInverseCholesky(CATMathNxNFullSymMatrix *M);

//------------------------------------------------------------------------------
//   Condition to stop the iteration of computation of the eigenvalues
//------------------------------------------------------------------------------
   CATLONG32 StopJacobi(const double iSchurxEps) const ;

//---------------------------------------------------------------------   
//  Compute the eigenvectors and eigenvalues - Change the Matrix.
//---------------------------------------------------------------------   
   virtual void EvalEigenVal(CATMathNxNMatrix &oEigenVec, double oEigenVal[], const double iEps=CATGetDefaultTolerance().EpsgForRelativeTest(), CATBoolean iSortEigen =FALSE) ; 

//update of symetric matrix from CATMath3x3Matrix
// --------------------------------------------------------------- 
//  
// <tt>E_FAIL</tt> if an error occurs , <tt>S_OK</tt> otherwise.   
   HRESULT    SetData (const CATMath3x3Matrix & base);

//---------------------------------------------------------------------   
// Overload operator
//---------------------------------------------------------------------   
 //- Self Product by a scalar
   CATMathNxNFullSymMatrix & operator *=(const double alpha) ;

//-----------------------------------------------------------------------------
// Cout : This method exists on non-official for debug.
//-------------------------------------------------------------------------------

   friend ostream & operator<< (ostream &op, const  CATMathNxNFullSymMatrix &);

   //
   // This method exists on non-officiel for debug.
   //
   //                                                                  // Ajout NLD270215 (implementation existante mais non atteignable)
   friend ExportedByYN000FUN CATCGMOutput & operator<< (CATCGMOutput &op, const  CATMathNxNFullSymMatrix &);


 protected:

   double * _L; // Lower part of the symetric matrix   
   CATLONG32 _NMax; //Initial dimension used for memory allocation   

 private :
//-------------------------------------------------------------------------------------   
//  Compute the modified b of Ax=b when some coefficients of the solution X are imposed
//
   virtual void Modifie(double *iobx, const CATLONG32 *iF) const;   

//---------------------------------------------------------------------   
// Used in SolveCholesky to solve L(tL)X=b
//
   virtual void Resolution(double *iob, const CATMathNxNFullSymMatrix * iL, const CATLONG32 * iF=0) ;
   
//-------------------------------------------------------------------------------------
// Used in LDLt factorization.

   // Shifts row and column k by row and column p. k < p.  
   void SymmetricPivot ( const CATLONG32 size, double *ioLD, CATLONG32 *piv, CATLONG32 k, CATLONG32 p ) const ; 

   // Does the LDLt factorization Obs: The inverse of D is stoored in the diagonal!
   CATLONG32 FactorizeLDLt ( const CATLONG32 size, double *ioLD, CATLONG32 *piv, unsigned int *block ) const ;

   // Solves the equations.
   void SolveLDLt ( const CATLONG32 size, double *iLD, CATLONG32 *piv, unsigned int *block, 
      CATLONG32 inrX, double *ioX, double *tmp ) const ;

   // Finds the inverse.
   void InverseLDLt ( const CATLONG32 size, double *iLD, double *oInv, CATLONG32 *piv, unsigned int *block ) ;

   // Extracts a sub matrix. Used when a part of the solution is imposed. See the use of iF earlier. 
   void ExtractLDLt ( const CATLONG32 size, const CATLONG32 *iF, double *ioLD, const double *data ) const ;

};
#endif
