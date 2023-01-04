
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathMxNMatrix :
//
// Rectangular matrix of dimension MxN (M is the number of rows
//                                      N is the number of colummns)
//
//===================================================================


#ifndef CATMathMxNMatrix_H  
#define CATMathMxNMatrix_H 

#include "YN000FUN.h"
#include "CATMathDiagnostic.h"

#include "CATCGMOutput.h"
#include "CATCGMVirtual.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATMathGrid;
class CATMathNxNFullSymMatrix;
class CATMathSparseMxNMatrix;

enum CATMathMatrixType { MxNMatrix, NxNMatrix, NxNFullSymMatrix, NxNBandSymMatrix };

class ExportedByYN000FUN CATMathMxNMatrix  : public CATCGMVirtual
{  

public: 
  //----------------------------------------------------------------
  //- Object Management
  //----------------------------------------------------------------
  //
  // Constructors 
  // 0. default constructor
  // 1. constructor from sizes (no initialization)
  // 2. constructor from sizes and coefficient array. 
  // 3. constructor from sizes (all coefficients initialized to a)
  // 4. Copy constructor
  //
  CATMathMxNMatrix ();
  CATMathMxNMatrix (const CATLONG32 M, const CATLONG32 N) ; 
  CATMathMxNMatrix (const CATLONG32 M, const CATLONG32 N, const double *A) ; 
  CATMathMxNMatrix (const CATLONG32 M, const CATLONG32 N, const double &a) ;
  CATMathMxNMatrix (const CATMathMxNMatrix& copy) ;
  //  
  //- Destructor  
  //  
  virtual ~CATMathMxNMatrix () ;
  
  //
  //-  Operator =  
  //
  virtual CATMathMxNMatrix& operator= (const CATMathMxNMatrix& equals) ;

  //----------------------------------------------------------------
  //- Information methods
  //----------------------------------------------------------------
  //
  //- Get the size of the matrix 
  //  
  virtual void                    GetSizeOfMatrix (CATLONG32 &M, CATLONG32 &N) const; 
 
  //
  //- Get the type of the matrix 
  //  
  virtual CATMathMatrixType       GetTypeOfMatrix () const;  

  //----------------------------------------------------------------
  //- Set Coefficients/ Reset /Set SubMatrix methods
  //----------------------------------------------------------------
  // CAUTION: Some CATMathMxNMatrix derivated classes (for instance CATMathNxNFullSymMatrix)
  //          may have optimized, hence different, coefficients storage mode.
  //          On such matrices, setting a coefficient may also set another coefficient (the symetric one for instance)
  //          Two imbedded loops for applying a factor to all coefficients by GetCoef() + SetCoef() would not do the right job on such matrices.
  //
  //- 1 Set all the coefficents of the matrix 
  //- 2 Set one of the coefficents of the matrix 
  //    0 <= row< M and  0 <= column < N
  //- 3 Set one of the coefficents of the matrix with the generalized index
  //    0 <= iIndex < M*N : the coefficient  (row,column) is set to A
  //    where row*N+column = iIndex.
  //- 4 Set a block of coefficents of the matrix 
  //    0 <= iIndexStart <= M*N-1 ;  iIndexEnd < end <= M*N-1
  //- 5 Reset ( set all coefficient to 0 ) 
  //- 6 Set rectangular sub matrix of size PxQ in current matrix at
  //     rowstart <= row < rowstart+P  ;  colstart <= column < colstart+Q
  //     
  virtual void                    SetCoef     (const double *A) ;
  virtual void                    SetCoef     (const CATLONG32 row, const CATLONG32 column, const double A) ; 
  virtual void                    SetCoef     (const CATLONG32 iIndex, const double A) ; 
  virtual void                    SetCoef     (const CATLONG32 iIndexStart, const CATLONG32 iIndexEnd, const double *A) ; 
  virtual void                    Reset       ();
  virtual void                    SetSubMatrix(const CATMathMxNMatrix & SubMatrixPQ, 
                                               const CATLONG32           rowstart,
                                               const CATLONG32           colstart);

  void  SetSizeOfMatrix (CATLONG32 &M, CATLONG32 &N);

//------------------------------------------------------------------------------------

// Inserts row as a new row into *this and increases M by 1 
   virtual void InsertRow(const double *row, const CATLONG32 iIndex);

//Reverse of the above
   virtual void RemoveRow(const CATLONG32 iIndex);

  //----------------------------------------------------------------
  //- Get Coefficients methods
  //----------------------------------------------------------------
  //
  //- 1 Get a coefficient of the matrix 
  //    0 <= row < M,,column < N-1
  //- 2 Get one of the coefficents of the matrix with the generalized index
  //    0 <= iIndex < N*M : the coefficient  (row,column) is set to A
  //    where row*N+column = iIndex.
  //- 3 Get all the coefficents of the matrix with the generalized index
  //    0 <= iIndex < N*M : the coefficient  (row,column) is set to A
  //    where row*N+column = iIndex. Duplication of the matrix.
  //- 4 Get all the coefficents of the matrix with the generalized index
  //    0 <= iIndex < N*M : the coefficient  (row,column) is set to A
  //    where row*N+column = iIndex. NO Duplication of the matrix.
  //- 5 Extraction of the submatrixPQ delimited by
  //    rowStart <= row <= rowEnd   ColumnStart <= Column <= ColumnEnd
  //    P = rowEnd - rowStart+1   Q = ColumnEnd - ColumnStart +1
  virtual       double            GetCoef           (const CATLONG32 row,
                                                     const CATLONG32 column)                             const ;
  virtual       double            GetCoef           (const CATLONG32 iIndex)                             const; 
  virtual const double          * GetFullMatrixCoef ()                                                   const;
  virtual       double          * GetCoef           ()                                                   const ;
  virtual       void              Extract           (      CATMathMxNMatrix & ExtractedPQ,
                                                     const CATLONG32           rowStart, const CATLONG32    rowEnd,
                                                     const CATLONG32        columnStart, const CATLONG32 columnEnd) const;
  //----------------------------------------------------------------
  //- Operators on matrices
  //----------------------------------------------------------------  

  //
  //- Get the matrice's Schur's norm 
  //  
  //  ||A||s =sqrt(Sum ij Aij*Aij)
  //
  virtual       double            SchurNorm () const; 
 
  //
  //- Compute the transposate of a matrix
  //
  virtual       void              Transpose (const CATMathMxNMatrix & Trans) ;
  virtual       void              Transpose () ;
 
  //
  //-Store in Prod the product of the matrix by its transposate  : A * tA
  // 
  virtual       void              GramProduct( CATMathNxNFullSymMatrix & Prod) const;
  virtual       void              GramProduct(const CATMathMxNMatrix & Prod) const;
  //
  //-Store in Prod the product of the transposate of the matrix by the matrix  : tA * A
  //
  virtual       void              TransGramProduct(CATMathNxNFullSymMatrix & Prod) const;
  
  // Applies the left multiplication of the grid by a matrix. If the grid is 
  // of size n*m , then the matrix should by p*n, and the result is
  // a p * m grid.
  virtual       void              MatrixTimesGrid (CATMathGrid & ioGrid) const;

  // Applies the right multiplication of the grid by a matrix. If the grid is 
  // of size n*m , then the matrix should by  p*m , and the result is
  // a n * p grid
  virtual       void              GridTimesMatrix (CATMathGrid & ioGrid) const;

  //  
  //- Multiply the matrix by a vector of dimension N 
  //
  virtual       double          * Multiply        (const double *v);
  virtual       void              Multiply        (const double *iv, double *ov) const;

  //  
  //- Multiply a vector, of dimension M, by the matrix.
  // 
                void              LeftMultiply    (const double *iv, double *ov) const ;
  
  //  
  //- Multiply *this by iA and put the result in oB
  //
  virtual       void              Multiply        (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;

  //  
  //- Add *this with iA and put the result in oB
  //
  virtual       void              Add             (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;

  //  
  //- Substract iA from *this and put the result in oB
  //
  virtual       void              Substract       (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;


  //- Multiple iA by iB and store the result in *this.
  // WARNING: The role/order of the different matrices is unlike that of other 'Multiply' methods.
                void              Multiply    (const CATMathSparseMxNMatrix & iA, const CATMathMxNMatrix & iB);

  // QR factorization of "this" is done by Housholder reflections. 
  // _M >= _N.
  // R is returned in the upper triangular part of oQR. 
  // Essential part of Housholder vectors (v) are returned in the 
  // lower part of oQR while 1/<v,v> are in ioBeta (of size _N).
  
  virtual       CATMathDiagnostic QRFactorization (CATMathMxNMatrix & oQR, double *ioBeta ) const ;

  // The pseudoinverse of A is put in B. If A is _Mx_N matrix, B is 
  // _Nx_M matrix. The second signature puts the inverse in "this".
  // The implementation uses "SolveQR". Mandatory: _M >= _N.

  // The vector iConstrRows yield an inverse, consistent with the use of iConstrRows in
  // the "Solve" method. See below. 
  
  virtual       CATMathDiagnostic Inverse         (CATMathMxNMatrix & oB, const CATLONG32 *iConstrRows = 0 ) const ;

  virtual       CATMathDiagnostic Inverse         () ;

  virtual       CATMathDiagnostic Inverse         ( const CATLONG32 *iConstrRows ) ;

  // Mandatory: _M >= _N. If _M > _N this gives the least squares solution
  // NbCol tells the number of right hand sides of the equation.
  // B is of size _M*nrB. 
  // X is of size _N*nrB.
  // The error in the result (compare with next method) will be in the 
  // magnitude of (Data Precision) * (conditon number of "this"). 
   
  // The vector iConstrRows, of size _M, shall contain at most _N zeroes. Each zero in 
  // iConstrRows identifies an equation row, i.e. a row in "this" and an element in iB.
  // These identified equation rows are used as linear equality constraints at the solution.

  virtual       CATMathDiagnostic Solve           (const double *iB, double *oX, const CATLONG32 NbCol = 1 ) const ;

  virtual       CATMathDiagnostic Solve           (const double *iB, double *oX, const CATLONG32 *iConstrRows, const CATLONG32 NbCol = 1 ) const ;
  
  //  Observe that the "Normal" method, being faster than the QR methods above, is far more
  //  sensitive to badly conditioned matrix (this). The error in the result will be 
  //  around (Data Precision) * (SQUARE of conditon number of "this"). For the 
  //  condition number: see SVD.  Mandatory: _M >= _N.

  //virtual CATMathDiagnostic SolveNormal(const double *iB, double *oX, const CATLONG32 NbCol=1 ) const ; 
  
  //
  // SINGULAR VALUE DECOMPOSITION, SVD.
  //
  // DEFINITION (see also the signature) :
  // Let A (this) be a matrix of size _M x _N. (No restriction on relation 
  // between _M and _N.)
  // U is of size _M x _N.  The columns of U will be ortho-normal.
  // V is of size _N x _N.  The columns of V will be ortho-normal.
  // w  is of length _N.     Singular values in descending order. These are
  //                         to be the diagonal in a diagonal matrix W.
  // Then, U x W x ( V transposed ) == A.
  // We say that U, W, V is the SVD of A.
  // SVD on general matrices may be seen as a generalization of the eigen system
  // on a symetric matrix. In fact, if A is a a symetric, U and V are eigen 
  // vectors and, w are the eigenvalues with positive signs. (The negative signs  
  // are handled by oposite directions of correspondig columns in U and V.)
  
  // PERFORMANCE:
  // Number of "flops" to do SVD is around (5*_M + 4*_N)*_N*_N. Observe
  // the linear dependence of _M.
  
  // USAGE:
  // Let tr mean transposed, for instance, let trU be U transposed. Let,
  // for instance,  Ui be the first i-1 columns of U. Equally let Wii be
  // the corresponding first (i-1)*(i-1) sub matrix of W. In the same way, 
  // let Uci and Vci be  the remaining columns and let Wcii the corre-
  // sponding "bottom right" sub matrix of W. (c stands for complement.)  
  
  // a. Let ||.|| be the 2-norm. Then ||A|| = w[0].
  
  // b. Condition nr of A = w[0]/w[_N-1] if w[_N-1]>0, otherwise infinite.
  
  // c. Inversion: If w[_N-1]>0, let Winv be a diagonal matrix with  
  //    Winv[i,i] = 1/w[i]. The inverse or pseudoinverse of A is given by
  //    V*Winv*trU. If _M<<_N, better use SVD of trA since this will give
  //    better performance. Then, the pseudo inverse of A is given by V*Winv*trU. 
  
  // d. Solution to Ax = b: Suppose that w[_N-1]>0 and set  x = V*Winv*trU*b.
  //    If A is square, x is the solution. I A has more rows than columns, x
  //    is the (normal) least squares solution.    
  
  // e. Rank, range and null space: If w[i-1] > 0 but w[i] = 0, then A is of 
  //    rank i, the range of A is spanned by Ui and the null space of A is  
  //    spanned by Vci. 
  
  // f. Numerical rank deficiency and matrix approximation: Similar to the
  //    result above, set B = Ui*Wii*trVi. Then, ||A - B|| = w[i]. Then, if
  //    w[i] is small but not zero B, approximate A with an error given by 
  //    w[i]. Thus, if numerical precision indicates that w[i-1] is suffici- 
  //    ently big but [i] is too small, rank of A is "safely" only i-1. 
  
  // The results, e. and f. indicate very useful methods to manipulate rank,
  // range and null space when solving  Ax = b. Small singular values may be
  // treated as zero. Thus, i decreaces. A smaller and approximative, range Ui
  // is considered as well as a greater and approximative nullspace Vci. 
  
  // g. Precision problem: Suppose that w[i-1] is suficciently big but w[i] 
  //    is smaller than the numerical precision you have, then, either set
  //    0 = Winv[i,i] = Winv[i+1,i+1] = ... and use d. or (identically) use 
  //    x = Vi*(Wii)inv*trUi*b (as indicated by f.).
  
  // h. If you want a reduction of variables to a few with great (robust)
  //    effect on the result, do as in g. but use rougher limits on w[i]
  //    (still smaller i.) Then consider equations like (Ui*Wii)y = b, folowed 
  //    by x = Vi*y. 
  
  // i. This (h.) is also intresting when you couple equations for 
  //    many objects in a big system and only can accept approximative
  //    results. The system may be sustantially reduced.
  
  // You can use the null space, (or approximative null space) to solve 
  // another problem, say Hx = g, under the condition ||Ax - b|| = 0 (or 
  // ||Ax - b|| is "allmost" 0). Observe that you may use a big excess
  // of rows in A without catastrophic decrease of performance. 
  
  // j. Suppose w[i-1] is bigger but w[i] is smaller than a particular limit
  //    you chose. Then, solve H*Vci*y = g folowed by x = Vci*y. 
  
  // A similar idea as in j. may be useful. Suppose we want a solution to an
  // strongly under determined problem Ax = b but with a solution x that is
  // close to a point d. For instance, d represents the position of many
  // control points in a curve or surface. We only want a small change of 
  // these control points. Since here, _M << _N we gain performance by using
  // SVD on trA: 
  
  // k. Let U,W,trV be the SVD of trA !!. Suppose that  w[i-1] is "big" and 
  //    w[i] is "small". Consider Ax = b and let d be a vector of the same
  //    dimension as x. Then set x = d + Ui*((Wii)inv*trVi*b - trUi*d). 
  //    Now, x is the solution to Ax = b that minimizes ||x-d||.    
  
  // The gain in doing SVD on trA (if _M<<_N) is paid by loosing the null
  // space of A.     
  
  CATMathDiagnostic SVD ( CATMathMxNMatrix &U , double *w, CATMathMxNMatrix &V ) ;

  //----------------------------------------------------------------
  //- Overloaded Operators
  //----------------------------------------------------------------  
  //- Addition
  friend ExportedByYN000FUN CATMathMxNMatrix operator +
  (const CATMathMxNMatrix & A, const CATMathMxNMatrix & B);
  //- Substraction
  friend ExportedByYN000FUN CATMathMxNMatrix operator -
  (const CATMathMxNMatrix & A, const CATMathMxNMatrix & B);
  //- Product between two matrix
  friend ExportedByYN000FUN CATMathMxNMatrix operator *
  (const CATMathMxNMatrix & A, const CATMathMxNMatrix & B);
  //- Product by a scalar
  friend ExportedByYN000FUN CATMathMxNMatrix operator *
  (const double alpha, const CATMathMxNMatrix & A);
  //- Self Product by a scalar
  CATMathMxNMatrix & operator *= (const double alpha);
 
  //
  // This method exists on non-officiel for debug.
  //
  friend ExportedByYN000FUN CATCGMOutput & operator<< (CATCGMOutput &op, const  CATMathMxNMatrix &);

protected:
  CATLONG32   _M, _N;  // dimension of matrix
  CATLONG32 _MaxSize;  // maximal size of _A to avoid unnecessary re-allocation
  double    * _A;      // coefficient of matrix : _A[i*_N + j] is the i-th row j-th column coef.

private:

void ComputeFullMatrixCoef (double *& oCoeff) ;
//////////////////////////////////////////////////////////
// Private method for the  methods SolveQR and Inverse.
// QR-factorization of R (copy of _A) is done by Housholder 
// reflections. 
// Essential part of Housholder vectors (v) are returned 
// in lower part of R while <v,v> are in w.
//////////////////////////////////////////////////////////

CATLONG32 QRFactors ( const CATLONG32 _M, const CATLONG32 _N, const double *ioR, double *ow ) const; 

};

#endif  

