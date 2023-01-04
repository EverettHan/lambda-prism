#ifndef CATMathSparseSymMatrix_H
#define CATMathSparseSymMatrix_H


#include "YN000FUN.h"

#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATListOfDouble.h"
#include "CATListOfInt.h"

class CATMathSparseMxNMatrix;

/***********************************************************************
   * Sparse Symetric Matrix
   *           
   *    A is a sparse square symetric definite positive matrix
   *    Only the lower part of the matrix and the non zero values are stocked
   *
   ***************************************************************************
   *
   *
   *    Example:  a01 to a12 are the non-zero values of the matrix
   *   
   *         1   2   3   4   5   6
   *    1   a01 0.0 0.0 0.0 0.0 0.0
   *    2   0.0 a02 a03 a05 0.0 0.0
   *    3   0.0 a03 a04 0.0 a07 a10 
   *    4   0.0 a05 0.0 a06 a08 0.0 
   *    5   0.0 0.0 a07 a08 a09 a11
   *    6   0.0 0.0 a10 0.0 a11 a12 
   *      
   *
   *  iNumberOfLine = 6
   *  iNumberOfCoefficient = 12
   *  iEndOflinePointer[7] = 0, 1, 2, 4, 6, 9, 12 
   *  iColumn =  0 ,  1 , 1 ,  2 ,  1 ,  3 ,  2 , 3 ,  4 ,  2 ,  4 ,  5 (begin to 0)
   *  iValues = a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11, a12
   *
   *
**************************************************************************/

class ExportedByYN000FUN  CATMathSparseSymMatrix
{
public:

  /** 
  * Copy Constructor
  *
  * <br><b>Role</b>: Copy a subMatrix
  *
  *
  * @return
  *   The copied matrix 
  *
  */

  CATMathSparseSymMatrix( const CATMathSparseSymMatrix& iMatrixToCopy);
	
  /** 
  * Copy Constructor
  *
  * <br><b>Role</b>: Copy a subMatrix
  *
  * @param iSize [in]
  *   The number (L) of line to copy.
  * @param iMatrixToCopy [in]
  *   The pmatrix to copy
  *
  * @return
  *   The copied matrix LxL from the initial Matrix MxM (M>L)
  *
  */
  CATMathSparseSymMatrix( const int iSize, const CATMathSparseSymMatrix* iMatrixToCopy);
	
  /** 
  * COnstructor
  *
  * <br><b>Role</b>: Explain what this method does.
  *
  * @param iSize [in]
  *   The parameter role...
  * @param iNumberOfCoeffs [in]
  *   The number of coefficient no nulls
  * @param iQuickMutiply [in]
  *   Advanced use ONLY 
  *
  * @return
  *   The Sparse and symetric Matrix 
  *
  */
  CATMathSparseSymMatrix( const int iSize, const int iNumberOfCoeffs);


	/** 
	* Destructor
	*
	*/
	virtual ~CATMathSparseSymMatrix();

	INLINE int GetSizeOfMatrix()const ;
	INLINE int GetSizeOfCoeffs()const ;

	INLINE const double * GetCoef() const;
	INLINE const int * GetColumns() const;
	INLINE const int * GetEndOfLines() const;

	/** 
	* Reset the matrix ( A = 0)
	*
	* @return
	*   0 : OK
  *  > 0 : One error has occured
	*
	*/
	int Reset();

	/** 
	* Perform A x
	*
	* <br><b>Role</b>: Compute opVector = this * ipVector;
	*
	* @param ipVector [in]
	*   The vector to multiply by this
	* @param opVector [out]
	*   The result vector
	*
	* @return
	*   0 : OK
  *  > 0 : One error has occured.
	*
	*/
	virtual int Multiply( const double * ipVector,double * opVector)const ;

	/** 
	* Perform A x B
	*
	* <br><b>Role</b>: Compute opResultMatrix = this * ipSecondMatrix;
	*
	* @param ipSecondMatrix [in]
	*   The matrix to multiply by this
	* @param opResultMatrix [out]
	*   The result matrix. If it is not <tt>NULL</tt>, the matrix will be deleted
	*
	* @return
	*   -1: if the result is zero matrix. in this case opResultMatrix is <tt>NULL</tt>
	*   0 : OK 
    *  > 0 : One error has occured.
	*
	*/
	int  Multiply( const CATMathSparseSymMatrix *ipSecondMatrix, CATMathSparseMxNMatrix *&opResultMatrix )const;

	/** 
	* Perform this^n
	*
	* <br><b>Role</b>: Power <tt>this</tt> by itself n times
	*
	* @param iPower_n [in]
	*   Power n . A positive  integer
	* @param opResultMatrix [out]
	*   The result matrix. If it is not <tt>NULL</tt>, the matrix will be deleted
	*
	* @return
	*   -1: if the result is zero matrix. in this case opResultMatrix is <tt>NULL</tt>
	*   0 : OK 
    *  > 0 : One error has occured.
	*
	*/
	int  Power( const unsigned int iPower_n, CATMathSparseSymMatrix *&opResultMatrix );

  
  /** 
  * Resolution of Ax = b
  *
  * <br><b>Role</b>: Iterative resolution of Ax = b in the case where A is positive.
  *
  * @param iVectorB [in]
  *   The vector "b", second member of the equation
  * @param ioSolution [inout]
  *   [in] the init for the algorithm
  *   [out] the solution "x" for the equation
  * @param epsilon [inout]
  *   The accuracy to validate the solution.
  * @param iNbIterationMax [in]
  *   The maximum number of iteration
  *
  * @return
  *   -1 : The accuracy is not reached, but there is a computed solution.
  *    0 : OK
  *   > 0 : One error has occured, the solution is not computed
  *
  */
  int SolveConjugateGradient(const double *iVectorB, double *ioSolution, const double epsilon, const int iNbIterationMax=500);

	/** 
  * Resolution of Ax = b
  *
  * <br><b>Role</b>: Iterative resolution of Ax = b in the general case.
  *
  * @param iVectorB [in]
  *   The vector "b", second member of the equation
  * @param ioSolution [inout]
  *   [in] the init for the algorithm
  *   [out] the solution "x" for the equation
  * @param epsilon [inout]
  *   The accuracy to validate the solution.
  *
  * @return
  *   -1 : The accuracy is not reached, but there is a computed solution.
  *    0 : OK
  *   > 0 : One error has occured, the solution is not computed
  *
  */
  int SolveBiConjugateGradient( const double *iVector, double *ioSolution, const double epsilon ) ;

  void Dump() const;

 protected:

	int InitSolve();
	int PreSolve(const double* iB,double* oX, const double iEpsilon) const;
	int Copy( const int iSize, const CATMathSparseSymMatrix* iMatrixToCopy );
	

	
private:

	int Power2(  );
	void Init();
	int Multiply( const CATMathSparseSymMatrix *ipSecondMatrix, CATMathSparseSymMatrix *&opResultMatrix )const;
	int MultiplyBy( const CATMathSparseSymMatrix *ipSecondMatrix,CATBoolean iResultIsSym=FALSE );

	void CleanMultiplyTools();
	int GetMultiplyResult(double * opResCoeffs, int * opResEndOfLines, int * opResColumns )const;
	int InitMultiplyTools( const int iExtimatedSize );
	int Resize(const int iNNZ );
	int PrivatePower( const unsigned int n );
	int SQ_R( const unsigned int n );
	int ASQ_R( const unsigned int n );




	CATListOfDouble* _pMultiplyListOfColumnsVals;
	CATListOfInt *_pMultiplyListOfColumnsRows;
	CATListOfInt *_pMultiplyListOfNNZColumns;


	CATMathSparseSymMatrix * _pCachePowerRes;


	
protected:

	double  *_pCoeffs;
	int *_pEndOfLines;
	int *_pColumns;

  // info pour le BiConjugateGradient...
	double * _x_Ml;
	double * _vk_Ml;
	double * _vkd_Ml;
	double * _vTilde_Ml;
	double * _mk_Ml;
	double * _mkd_Ml;

	int _Size;
	int _NumberOfCoeffs;

};

//-----------------------------------------------------------------------------------------------------------------------
// GetSizeOfMatrix
//-----------------------------------------------------------------------------------------------------------------------
INLINE int CATMathSparseSymMatrix::GetSizeOfMatrix()const 
{
	return _Size;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetSizeOfCoeffs
//-----------------------------------------------------------------------------------------------------------------------
INLINE int CATMathSparseSymMatrix::GetSizeOfCoeffs()const 
{
	return _NumberOfCoeffs;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetCoef
//-----------------------------------------------------------------------------------------------------------------------
INLINE const double* CATMathSparseSymMatrix::GetCoef() const
{
	return _pCoeffs;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetColumns
//-----------------------------------------------------------------------------------------------------------------------
INLINE const int* CATMathSparseSymMatrix::GetColumns() const
{
	return _pColumns;
}

//-----------------------------------------------------------------------------------------------------------------------
// GetEndOfLines
//-----------------------------------------------------------------------------------------------------------------------
INLINE const int* CATMathSparseSymMatrix::GetEndOfLines() const
{
		return _pEndOfLines;
}


#endif
