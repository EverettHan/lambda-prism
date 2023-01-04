// COPYRIGHT DASSAULT SYSTEMES 2010

//===================================================================
//=================================================================== 
//
// CATMath3x3SymMatrix :
// Square Symetric matrix of dimension 3 
//
//===================================================================


//===================================================================
// Usage notes:
//
//   We define and manipulate square symetric matrix of dimension 3
//   Matrix = (A11, A21 , A31; 
//             A21, A22 , A32;
//             A31, A32 , A33)
//
//   Only the diagonal and the lower part of the matrix is stocked in a CATMathVector L=(A11,A21,A22,A31, A32 , A33)
//   .. so you should pay attention when using SetCoeff methods
//
//===================================================================


#ifndef CATMath3x3SymMatrix_H  
#define CATMath3x3SymMatrix_H 


#include "CATMathLimits.h"
#include "CATMath3x3Matrix.h"
#include "CATTolerance.h"

class CATMathMxNMatrix;
class CATMathNxNBandSymMatrix;

class ExportedByCATMathematics CATMath3x3SymMatrix : public CATMath3x3Matrix 
{ 

public: 
  //
  //- Constructor -------------------------------------------------------
  //
  CATMath3x3SymMatrix ();

  CATMath3x3SymMatrix (const double A[]);

  CATMath3x3SymMatrix (const double iA1,
                       const double iA21, const double iA22,
                       const double iA31, const double iA32, const double iA33);

  CATMath3x3SymMatrix (const CATMath3x3SymMatrix & copy);

  //  
  //- Destructor -------------------------------------------------------------- 
  //  
  virtual ~CATMath3x3SymMatrix ();

  //  
  //- Set/Get Methods -------------------------------------------------------------- 
  //  
  //////////////////////////////////////////// Overloaded methods from the mother class CATMath3x3Matrix
  /**
  * Sets the coefficients of <tt>this</tt> CATMath3x3SymMatrix.
  * This method is overloaded from the mother class CATMath3x3Matrix to avoid possible ambiguities
  * WARNING : The matrix symmetry is never checked. 
  *                       Only the coefficients of the diagonal and the lower part are used to set the matrix as follows :
  *                        Matrix= (A11, A21 , A31; 
  *                                 A21, A22 , A32;
  *                                 A31, A32 , A33)
  */
  void SetCoef (const double iA11, const double iA12, const double iA13,
                const double iA21, const double iA22, const double iA23,
                const double iA31, const double iA32, const double iA33);

  /**
  * Modifies the first column of <tt>this</tt> CATMath3x3SymMatrix.
  * This method is overloaded from the mother class CATMath3x3Matrix to avoid possible ambiguities
  * WARNING : The matrix symmetry is never checked. 
  *                       As the matrix is symmetrical, replace the first column means also replace the first row of the matrix as follows :
  * Let V(V1, V2,V3)
  * and  M = (A11, A21, A31;
  *           A21, A22, A32;
  *           A31, A32, A33) be a CATMathVector and a CATMath3x3SymMatrix
  * M.SetFirstColumn (V) leads to the following  Matrix :(V1,  V2 ,  V3; 
  *                                                       V2, A22 , A32;
  *                                                       V3, A32 , A33)
  */
  void SetFirstColumn (const CATMathVector &iFirstColumn) ;



  /**
  * Modifies the first column of <tt>this</tt> CATMath3x3SymMatrix.
  * This method is overloaded from the mother class CATMath3x3Matrix to avoid possible ambiguities
  * WARNING : The matrix symmetry is never checked. 
  *                      As the matrix is symmetrical, replace the second column means also replace the  second row of the matrix as follows :
  * Let V(V1, V2, V3)
  * and  M = (A11, A21, A31;
  *           A21, A22, A32;
  *           A31, A32, A33) be a CATMathVector and a CATMath3x3SymMatrix
  *  M.SetSecondColumn (V) leads to the following  Matrix :(A11, V1 , A31; 
  *                                                         V1,  V2 ,  V3 ;
  *                                                         A31, V3 , A33)
  */
  void SetSecondColumn (const CATMathVector &iSecondColumn) ;

  /**
  * Modifies the first column of <tt>this</tt> CATMath3x3SymMatrix.
  * This method is overloaded from the mother class CATMath3x3Matrix to avoid possible ambiguities
  * WARNING : The matrix symmetry is never checked. 
  *                      As the matrix is symmetrical, replace the last column means also replace the last row of the matrix as follows :
  * Let V(V1, V2,V3)
  * and  M= (A11, A21, A31;
  *          A21, A22, A32;
  *          A31, A32 , A33) be a CATMathVector and a CATMath3x3SymMatrix
  * M.SetSecondColumn (V) leads to the following  Matrix :(A11, A12, V1 ;
  *                                                        A12, A22, V2 ;
  *                                                        V1,   V2, V3 )
  */
  void SetThirdColumn (const CATMathVector &iThirdColumn) ;

  /** 
  * Modifies the first column of <tt>this</tt> CATMath3x3SymMatrix.
  * This method is overloaded from the mother class CATMath3x3Matrix to avoid possible ambiguities
  * WARNING : The matrix symmetry is never checked. 
  *                       The three columns as seen as a 3x3 Matrix and the previous rule about setting with 9 coefficient is applied
  * Let V1(V11, V12,V13),  V2(V21, V22,V23), V1(V31, V32,V33)
  * and  M= (A11, A21 , A31;
  *          A21, A22 , A32;
  *          A31, A32 , A33) beCATMathVectors and a CATMath3x3SymMatrix
  * M.SetSecondColumn (V1,V2,V3) leads to the following  Matrix :(V11, V12, V13 ;
  *                                                               V12, V22, V23 ;
  *                                                               V13, V23, V33 )
  */
  void SetMatrix (const CATMathVector & iFirstColumn,
                  const CATMathVector & iSecondColumn,
                  const CATMathVector & iThirdColumn) ;


  ///////////////////////////////////////////// New Methods devoted to the CATMath3x3SymMatrix class 

  /////////Get
  //-  Get the  coefficient located in (row, column) with 0 <= row,column <= N-1 of the associated 3x3 Matrix 
  //  Return E_FAIL if the indexes are invalid, S_OK otherwise
  HRESULT GetCoef    (const CATLONG32 row, const CATLONG32 column, double & oCoeff) const ;
  //-  Get  the coefficents of the matrix with the local index (the one of the associated lower block : 0 <= iIndex < N(N+1)/2 : iIndex=row*(row+1)/2+col)
  //  Return E_FAIL if the index is invalid, S_OK otherwise
  HRESULT GetSymCoef (const CATLONG32 iIndex, double & oCoeff) const; 
  //-  Get all the coefficents of  the associated 3x3 Matrix
  void    GetCoef    (double  oCoeff[]) const ; 
  //-  Get all the coefficents of the lower block of the matrix
  void    GetSymCoef (double oCoeff[]) const ; 

  /////////Set
  //-  Set the  coefficient located in (row, column) with 0 <= row,column <= N-1 of the associated 3x3 Matrix 
  // WARNING : as the matrix is symmetrical, replace a coefficient means also replace its symmetrical one.
  //  Return E_FAIL if the indexes are invalid, S_OK otherwise
  HRESULT SetCoef    (const CATLONG32 row, const CATLONG32 column, const double A) ; 
  //-  Set  the coefficents of the matrix with the local index (the one of the associated lower block : 0 <= iIndex < 6)
  //   Notice that  iIndex=row*(row+1)/2+col with row and column the coord of the associated 3x3 Matrix
  //  Return E_FAIL if the index is invalid, S_OK otherwise
  HRESULT SetSymCoef (const CATLONG32 iIndex, const double A) ; 
  //-  Get all the coefficents of the lower block of the associated 3x3 Matrix
  //   Only the 6 first coefficients are used to define lower block
  void SetSymCoef    (const double * A) ; 


  //- Services -------------------------------------------------------------- 
  // 
  //- Get the matrice's Schur's norm ||A||s =sqrt(Sum ij Aij*Aij)
  virtual double SchurNorm () const ;

  //  Compute the eigenvectors and eigenvalues - Change the Matrix.
  void EigenVectors(int          & ioNbEigenValues,
                    double         ioEigenValues[3],
                    CATBoolean     ioHasAssociatedVector[3],
                    CATMathVector  ioEigenVectors[3],
                    CATBoolean     & ioIsDiagonal) const ;

private :
  double _L[6];
};  
#endif  
