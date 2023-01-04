#ifndef CATMathSparseMxNMatrix_H
#define CATMathSparseMxNMatrix_H


#include "YN000FUN.h"

#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATMathMxNMatrix.h"

class CATMathSparseSymMatrix;
class CATMathMxNFullMatrix;

/** ***********************************************************************
*    A is a sparse NxM matrix
*    Only the non zero values are stocked
*
***************************************************************************
*
*
*    Example:  a01 to a12 are the non-zero values of the matrix
*   
*         1   2   3   4   5   6
*    1   a01 0.0 0.0 0.0 0.0 0.0
*    2   0.0 a02 a03 a04 0.0 0.0
*    3   0.0 a05 a06 0.0 a07 a08 
*    4   0.0 a09 0.0 a10 a11 0.0 
*    
*      
*
*  iNumberOfLine = 4
*  iNumberOfCoefficient = 11
*  iEndOflinePointer[5] = 0, 1, 4, 8, 11 
*  iColumn =  0 ,  1 ,  2 , 3  ,  1 ,  2 ,  4 ,  5 ,  1 ,  3 ,  4 (num column begin to 0) 
*  iValues = a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11
*
*
*
**************************************************************************
*
*  Input:
*
*  int     iNumberOfLine
*
*  int     iNumberOfCoefficient
*
*  int*    iEndOflinePointer[iNumberOfLine+1]
*          Pointer in iColumnNumber and iValues
*
*  int*    iColumn[iNumberOfCoefficient]
*                            
*  double* iValues[iNumberOfCoefficient]
*                             
*    
* ***********************************************************************
*/  

class ExportedByYN000FUN  CATMathSparseMxNMatrix
{
public:
  /** 
  * Constructor
  *
  * @param iNbLines [in]
  *   The number (M) of line in Matrix
  * @param iNbColums [in]
  *   The number (N) of column in Matrix
  * @param iNumberOfCoeffs [in]
  *    The number of coeficient no nulsi n Matrix
  *
  * @return
  *   The sparse MxN matrix
  *
  */
  CATMathSparseMxNMatrix( const int iNbLines, const int iNbColums, const int iNumberOfCoeffs );
  ~CATMathSparseMxNMatrix();

  INLINE void GetSizeOfMatrix(int &oNbLines, int &oNbColums) const; 
  INLINE int GetSizeOfCoeffs()const ;
  void SetSizeOfMatrix(int iNbLines, int iNbColumns, int iNumberOfCoeffs);

  INLINE const double * GetCoef() const;
  INLINE const int * GetColumns() const;
  INLINE const int * GetEndOfLines() const;

  double GetCoef(const CATLONG32 row,const CATLONG32 column) const;

  /**
  *  Schur norme Computation
  * <br><b>Role</b>:  Compute the SchurNorm
  *      ||A||s =sqrt(Sum ij Aij*Aij)
  * @return
  * 
  */
  double SchurNorm() const;


  /**
  *  Set all coefficient to 0
  * <br><b>Role</b>: 
  * @return
  *  0 : OK
  *  >0 : KO...
  * 
  */

  int Reset();


  /**
  * Matrix Vector Product
  * <br><b>Role</b>: Perform Y = AX 
  *  opVector = this * ipVector
  * @param ipVector
  *  The vector to multiply
  * @param opVector
  *  The multiplied vector.
  * @return
  *  0 : OK
  */
  int Multiply( const double * ipVector,double * opVector)const ;


  /**
  * Transposed Matrix Vector Product
  * <br><b>Role</b>: Perform Y = tA . X 
  *  opVector = this * ipVector
  * @param ipVector
  *  The vector to multiply
  * @param opVector
  *  The multiplied vector.
  * @return
  *  0 : OK
  */
  int MultiplyByTranspose( const double * ipVector,double * opVector, const int NbVectors=1)const;


  /**
  * Matrix scalar product
  * <br><b>Role</b>: M *= a, this = iFactor * this
  * @param iFactor
  *  The scalar factor in product
  * @return
  *  O : OK
  */

  int Multiplied( const double iFactor);

  //  
  //- Multiply *this by iA and put the result in oB
  //

  void Multiply        (const CATMathMxNMatrix & iA, CATMathMxNMatrix & oB) const ;

  /**
  * TransGram Product
  * <br><b>Role</b>: Build the product of the transposate of the matrix by the matrix  : tA * A
  * @return
  *  The Product Matrix
  */

  CATMathSparseSymMatrix * BuildTransGramProduct() const;


  /**
  *  Build the product of the input matrix by this
  * <br><b>Role</b>: Perform M = A*B = iLefOperand * this
  * @param iLefOperand
  *  The left matrix in product
  * @return
  *  The matrix product's result .
  */
  CATMathSparseMxNMatrix * BuildLeftProduct(const CATMathSparseMxNMatrix * iLefOperand) const;


  /**
  *  Matrix Addition 
  * <br><b>Role</b>: Perform M = A+B = iAddedMatrix + this
  * @param iAddedMatrix
  *  The Matrix to add
  * @return
  *  The matrix addition's result .
  */

  CATMathSparseMxNMatrix * BuildAddition(const CATMathSparseMxNMatrix * iAddedMatrix) const;

  void ConvertToDenseMatrix(CATMathMxNMatrix & oB);

  void Dump() const;

  /**
  *  Convert Full Matrix in Sparse Matrix
  * <br><b>Role</b>: 
  * @param iMatrix
  *   The Full Matrix to convert
  * @return
  *   The converted Sparse Matrix
  */

  static CATMathSparseMxNMatrix* BuildFromMathMxNFullMatrix (CATMathMxNFullMatrix * iMatrix);


  /**
  *  Build an square, diagonal sparse matrix
  * <br><b>Role</b>: Build an square, diagonal sparse matrix
  * @param iVector
  *   The diagonals values.
  * @param iDimension
  *   Size of the square matrix
  * @return
  *   The square, diagonal sparse matrix
  */
  static CATMathSparseMxNMatrix* BuildFromDiagVector (const double * iVector, const int iDimension);


  static CATMathSparseMxNMatrix* BuildFromArrays (const int iNbLines, const int iNbColums, const int iNumberOfCoeffs, 
    const int *iEndOflinePointer,
    const int *iColumn,
    const double *iValues);

  void SetArrays(const int *iEndOflinePointer, const int *iColumn, const double *iValues);

private:

  double  *_pCoeffs; // all coeff no null line by line
  int *_pEndOfLines; // index of latest coefficient in the line
  int *_pColumns;    // Column of each coefficients no null.


  int _L; // number of line s
  int _C; // number of columns
  int _NumberOfCoeffs;

  int _MaxL;
  int _MaxNoC;
};

//-----------------------------------------------------------------------------------------------------------------------
// GetSizeOfMatrix
//-----------------------------------------------------------------------------------------------------------------------
INLINE void CATMathSparseMxNMatrix::GetSizeOfMatrix(int &oNbLines, int &oNbColums)const 
{
  oNbLines = _L;
  oNbColums = _C;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetSizeOfCoeffs
//-----------------------------------------------------------------------------------------------------------------------
INLINE int CATMathSparseMxNMatrix::GetSizeOfCoeffs()const 
{
  return _NumberOfCoeffs;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetCoef
//-----------------------------------------------------------------------------------------------------------------------
INLINE const double* CATMathSparseMxNMatrix::GetCoef() const
{
  return _pCoeffs;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetColumns
//-----------------------------------------------------------------------------------------------------------------------
INLINE const int* CATMathSparseMxNMatrix::GetColumns() const
{
  return _pColumns;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetEndOfLines
//-----------------------------------------------------------------------------------------------------------------------
INLINE const int* CATMathSparseMxNMatrix::GetEndOfLines() const
{
  return _pEndOfLines;
}


#endif
