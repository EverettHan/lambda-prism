// COPYRIGHT DASSAULT SYSTEMES 2000

/**
 *=======================================================================================
 * Juillet  00  Creation                           D. Johansson 
 * Mars     02  QR methods                         D. Johansson
 * April    02  SVD                                D. Johansson
 * Juin     02  Eigen system of symmetric state    D. Johansson
 * Juillet  02  Eigen values but not eigen vectors D. Johansson 
 *=======================================================================================
 *
 * CATMathMxNBandMatrix :
 * Matrix of dimension _M x _N with a "banded" structure. 
 * At work (but not neccessarily at creation), _M >= _N. 
 * This object also handle the symmetric product of ("this transposed") * "this"
 * and also handle the LDLt factorization of that symmetric product.
 * The objective is least square solutions of equations related to NURBS and to be
 * able to work on small allocated memory area, without much need of "new" operations .
 *
 *=======================================================================================
 *   Introduction:
 *
 *   Example of the stucture of a matrix M:
 *
 *            | a0  a1  a2   0   0  ...    0    0    0|
 *            | a3  a4  a5   0   0  ...    0    0    0|
 *            |  0   0   0  a6  a7  a8   ...    0    0|
 *       M1 = |  0   0  a9 a10 a11  ...    0    0    0|
 *            |  0 a12 a13 ...             0    0    0|
 *            |              ...                      |
 *            |  0   0  0   0   0  ...  ak-3 ak-2 ak-1|   
 *
 *   Only the elements a0, a1, ...ak-1 are stored in the array _A of size _M * _B 
 *   where _M are the number of rows and _B is the bandwidth, i.e. _B is the number 
 *   of stored, generally non zero, elements of each row.
 *  
 *   We use one indices array _C of size _M:  
 *   The indices of the first non zero element in the i:th row is   
 *   (i, _C[i]). This element itsef is stored in _A[_B*i].
 * 
 *     M[i,j] = _A[_B*i + j -_C[i]] if _C[i] <= j < _C[i]+_B.  
 *     M[i,j] = 0 oterwise.         
 *
 *   To handle periodic problems we might consider a generalization
 *   exemplified by:
 *
 *            |  a2   0   0   0   ...    0   a0   a1|
 *            |  a5   0   0   0   ...    0   a3   a4|
 *            |  a6  a7  a8   0   ...    0    0    0|
 *            |  a9 a10 a11   0   ...    0    0    0|
 *       M2 = | a12 a13 a14   0   ...    0    0    0|
 *            |   0 a15 a16 a17   ...               |
 *            |                   ...               |
 *            |   0   0   0   0   ... ak-6 ak-5 ak-4|   
 *            |   0   0   0   0   ... ak-3 ak-2 ak-1|   
 *
 *   All above holds for this generalization except that the first 
 *   elements in _C may be negative and a column index j is interpreded
 *   as j%_N (modulo _N). We have:
 * 
 *     M[i,j] = _A[_B*i + j + _N - _C[i]] if _C[i] + _N <= j.  
 *     M[i,j] = _A[_B*i + j      - _C[i]] if _C[i]      <= j < _C[i] + _B.
 *     M[i,j] = 0 oterwise.
 *
 *   Diffrent states of the matrix:
 *     1. The state described above. It can be created and used as such.
 *     2. A symetric state: Let MxN be a matrix of in the state given above
 *        then this state is given by (MxN transposed) * MxN. This may directly
 *        be created as well.
 *     3. The LDLt factorization of a matrix in symetric state.
 *     4. QR-Factorized state. 
 *     5. SVD state.
 *     6. Eigen system of a matrix in symmetric state
 *     The states may be created by overwriting the previous state or as 
 *     other matrices depending on the current use. 
 *     Only at creation or by "Reset(...)" and only the states 1 or 2 can be 
 *     directly set by the user.
 *
 *	 Monotone column index condition in one case:
 *     This is only mandatory if you will use the method "TransGramProduct()".
 *     That metod overwrite the result on itself without extra storage.
 *     Generally, the sequence _C[i] may be arbitrary but the method needs that
 *     the sequence _C is increasing. You must build the matrix in correct row
 *     sequence like in M2. In M1 the rows should have been added in sequence
 *     0, 1, 4, 3, 2, ... 
 *
 *     The QR and SVD metods also need non-decreasing column indices. //DJN April 2002 
 *     
 *   To permit resizing and repeated use of the same memory area the matrix may
 *   be created with extra big size of maximal _M or maximal value of SizeData.
 *   The current_M may increase up to this maximal value without the need of  
 *   new memory allocation. 
 *
 *=======================================================================================
 *   Usage:
 *
 *   Let MxN be a matrix and MxNt its transpose.
 *
 *   Consider the equation                    MxN * X = RHS  ( = Right Hand Side ).
 *
 *   Let Sym be the product MxNt * MxN and let MtR be the product MxNt * RHS.
 *   Let LDLt be the LDLt-factorization of Sym.
 *
 *   The normal solution is given by solving   Sym * X = MtR. 
 *   which, in turn, is handled by solving    LDLt * X = MtR.   
 *
 *   If M >> _N. Methods exists that permits the direct building of Sym (= MxNt * MxN )
 *   and of MtR (= MxNt * RHS ).
 *
 *   Constraints and imposition:
 *     So far, this can be used only on non-periodic matrices! 
 *     Consider the solution an equation MxN * X = RHS. If some rows of MxN and of RHS are  
 *     to define constraints we may extract a (small) equation system MxN0 * X0 = RHS0  
 *     defining these constraingts. In "CATMathMxNBandMatrix" we demand that MxN0 is  
 *     square, i.e. in MxN the correspondig rows has only zeroes in all other columns.
 *
 *     In the MxN state some rows define constraints. See "IdentifyConstraints(...)".
 *     In the Sym state we use the word imposition since you must impose the result of
 *     the constraints into X in advance of the factorization and solution.
 *
 *   Stabilizing:
 *     At the LDLt factorization a (small) number may be added to the diagonal. This 
 *     permits the stabilizing of the solution at iterative work. Also consider the
 *     "Levenberg-Marquardt method" at non-linear least sqares problem.
 *
 *   Smoothing:
 *     Smooth factors can, of course, be added to the matrtrix in the MxN state but
 *     may also be addded directly into the Sym state, selectively or by adding a
 *     complete (symetric) smoothing CATMathMxNBandMatrix.
 *
 *   Remark:
 *     The LDLt factorization is (almost) equivaltent to the Cholesky factorization
 *     but somewhat faster - particularly in narrowly banded cases.
 *
 *   The objective is to avoid too much allocation of memory. It is generally possible to 
 *   do the product MxNt * MxN and the LDLt factorization on existing memory and hereby
 *   change the state of the matrix. Also, for instance when RHS actually is a grid of
 *   points, it is possible to do the operatons "MxNt * RHS" and "Solve(...)" directly on 
 *   the relevant axis of the grid without (allmost) no extra allocation of data. 
 */

#ifndef CATMathMxNBandMatrix_H  
#define CATMathMxNBandMatrix_H 

#include "YN000FUN.h"
#include "CATMathSetOf3DObjects.h"
#include "CATMathGrid.h"
class CATMathMxNMatrix;
#include "CATCGMVirtual.h"

class ExportedByYN000FUN CATMathMxNBandMatrix : public CATCGMVirtual
{ 
public:
/**
 *=======================================================================================	
 *- Constructor 
 *- 1 Default
 */
  CATMathMxNBandMatrix () ;

/**
 *- 2 Just allocate a (big) array
 */ 
  CATMathMxNBandMatrix ( const CATLONG32 iSizeData ) ;

/**
 *- 3 Symmetric
 */ 
  CATMathMxNBandMatrix ( const CATLONG32 iN,    const CATLONG32 iBandWidth ) ;

/**
 *- 4 MxN:
 */ 
  CATMathMxNBandMatrix ( const CATLONG32 iMaxM, const CATLONG32 iN, const CATLONG32 iBandWidth ) ;

/**
 *- 5 Copy:
 */ 
  CATMathMxNBandMatrix ( const CATMathMxNBandMatrix &iCopy ) ;

/**
 *=======================================================================================  
 *- Destructor 
 */  
  virtual ~CATMathMxNBandMatrix () ;

/**
 *=======================================================================================  
 *- Operator =  
 */
  virtual CATMathMxNBandMatrix& operator = (const CATMathMxNBandMatrix& equals) ;

/**
 *=======================================================================================
 *- 1 Get the size of the matrix. 
 */  
  virtual void GetSizeOfMatrix ( CATLONG32 &oCurrentM, CATLONG32 &oCurrentN, CATLONG32 &oBandwidth ) const ;
  virtual void GetSizeOfMatrix ( CATLONG32 &oMaxM, CATLONG32 &oSizeData ) const ;  

/**
 *- 2 Get the state of the matrix. 1 if MxN, 2 if Sym, 3 if LDLt, 4 if QR and 5 if SVD. 
 */  
  virtual CATLONG32 GetState() const { return _State ; } ; 

/**
 *- 3 Returns one if the matrix is periodic. 
 */  
  virtual CATLONG32 GetIfPeriodic() ; 

/**
 *- 4 Sym: The (rough) norm is the vector length of the diagonal.
 */
  virtual double GetNormOfDiag() ;
  
/**
 *=======================================================================================
 * Change of sizes
 *- 1 Symmetric. The total size of data may be increased
 */
  virtual void SetSize ( const CATLONG32 iN, const CATLONG32 iBandWidth ) ;  

/**
 *- 2 MxN: OBS! this changes the maximal number of rows 
 */ 
  virtual void SetRowSize ( const CATLONG32 iN, const CATLONG32 iBandWidth, CATLONG32 &oMaxM ) ;

/**
 *- 3 MxN: Increase maximal column size. The total size of data is probably increased
 *    iNbRows: if used is should not be bigger than iNewMaxM and if it is bigger
 *    than before, rows that are not set may be used.
 */ 
  virtual void SetMaxColSize ( const CATLONG32 iNewMaxM ) ;

/**
 *- 4 MxN: Increase column size. Use with care!
 *    If it is bigger than before, rows that are not yet set may be used.
 *    If it is smaler than before, rows that are set may be overwritten.
 */ 
  virtual void SetColSize ( const CATLONG32 iM ) ;

/**
 *- 5 Minimize allocation to the size of currently used memory. 
 */ 
  virtual void Compress () ;

/**
 *=======================================================================================
 *- 1 Set an element. Returns zero if the indexed position is not in _A. 
 */ 
  virtual CATLONG32 SetCoef ( const CATLONG32 iIndRow, const CATLONG32 iIndCol, const double iDatum ) ;

/**
 *- 2 Set a row. Increaces M by one. Returns zero if the maximl number of rows are 
 *    exceeded, othewise the new total number of rows. The "iData" is supposed be 
 *    of length = bandwidth.
 */ 
  virtual CATLONG32 SetCoef ( const CATLONG32 iIndCol, const double *iData ) ;

/**
 *- 3 Set a block Increaces M by iNbRows. Returns zero if the maximl number of rows are 
 *    exceeded, othewise the new total number of rows. The "iData" is supposed be of 
 *    length = iNbRows * bandwidth.
 */ 
  virtual CATLONG32 SetCoef (const CATLONG32 iIndCol, const CATLONG32 iNbRows, const double *iData) ; 

/**
 *- 4 Reset : If iToState = 1 The matrix becomes to be of kind MxN. 
 *            If iToState = 2 The matrix becomes to be of kind Sym. 
 */ 
  virtual void Reset( const CATLONG32 iToState = 0, const CATLONG32 iKeepImpositions = 0, const CATLONG32 iNewBandWidth = 0 ) ;

/**
 *=======================================================================================
 *- 1 Get a coefficient of the matrix 
 */
  virtual double  GetCoef ( const CATLONG32 iRow, const CATLONG32 iColumn ) const ;

/**
 *- 2 Not for LDLt-state: Get all the non zero coefficents of the matrix.
 *    The array is a part of "this" and must not be deallocated.
 */
  virtual const double *GetCoef () const ;

/**
 *- 3 Not for LDLt-state: Get a CATMathMxNMatrix from "this". ioFull must
 *    have correct size, ( _M, _N or  _N, _N ).
 */
  virtual void GetFullMatrix ( CATMathMxNMatrix &ioFull ) const ;

/**
 *- 4 MxN: Get the column pointer _C ( see the introduction above ) ;
 *    The array is a part of "this" and must not be deallocated.
 */
  virtual const CATLONG32 *GetColStarts () const { return _C ; } ;

/**
 *=======================================================================================
 * Imposition & weight:
 * So far, this can be used only on non-periodic matrices! 
 *- 1 iF is a vector of length _N. For all X[i] such that iF[i] is zero, X[i] is returned
 *    unchanged and these elements effectively work as constraints. All other elements of
 *    X are calculated to give a least squares solution to MxN * X = RHS under these con-
 *    satraints.
 *    NULL deletes all constraint and imposition information from the matrix.
 *    OBS: Only the pointer iF is stored. You must not change its adress while in use!
 */
  virtual void SetImpositions ( const CATLONG32 *iF = NULL ) ;

/**
 *- 2 MxN state only: Affects "TransMultiply" below. iRowIndices is supposed to have the 
 *    same length as the number of zeros in iF. The rows identified must have non-zero 
 *    elements only in the columns corresponding to zeroes in iF.
 *    The relevant rows must be set in advance!!
 *    If iNbRowInd is used more rows than zeroes in iF are considered. 	
 *    OBS: Only the pointer iF is stored. You must not change its adress while in use!
 */
  virtual void IdentifyConstraints ( const CATLONG32 *iF, const CATLONG32 *iRowIndices, const CATLONG32 iNbRowInd = 0 ) ;

/**
 *- 3 MxN state only:
 * the product MxNt * MxN and let MtR be the product MxNt * RHS.
 *
 *    Again, consider the equation MxN * X = RHS. The system may be weighted by multiplying
 *    the rows of MxN and RHS by weights. By giving this "*iWeightOnRows" such weighting can 
 *    be done without changing MxN and RHS, thus permitting repeated solution by only 
 *    changing the elements of "*iWeightOnRows". This array affects "TransMultiply(..)" and 
 *    "TransGramProduct(...)". When forming the products MxNt * MxN and MxNt * RHS the weights
 *    occurs squared thus they are to be given squared. They are not "const" since, if cons-
 *    straints rows are identified, the correspontding wegths are set to one. If "iScale" also
 *    is considered iSquaredRowWeights has priority and iScale is treated as 1.0.
 * 
 *    The length of "*iWeightOnRows" is equal to the numbers of rows in "this".	Empty 
 *    "*iWeightOnRows" deletes this weight. Only the pointer iWeightOnRows is privately 
 *    stored. You must not change its adress while in use!
 */
  virtual void SetRowWeights ( double *iSquaredRowWeights = NULL ) ;
 
/**
 *=======================================================================================
 * At some instances "iLnOfFirstAxis" is an option. The objective is the use on three 
 * axis array (grid of points) with axis length L1, L2 and L3 respectively:
 * Multiply on first  axis ( _M == L1 ): set iNbCol = L2 * L3 and ignore "iLnOfFirstAxis"
 * Multiply on second axis ( _M == L2 ): set iNbCol = L3 and set iLnOfFirstAxis = L1.
 * On two axis arrays you can work row-wise by: iNbCol = 1 and iLnOfFirstAxis = NbRows.
 * 
 * It is, sometimes, possible to use use a segment of the matrix by using "iMatrixStartRow"
 * and "iMatrixEndRow". Also, if the last axis (L3 above) is larger than iNbCol, a segment 
 * of columns may be used by setting "iLnOfLastAxis".
 *
 *- 1 Multiply the matrix by iV of length N*iNbCol. oMV is of length M*iNbCol. 
 *    oMV must have suffucient size and, if set or grid, correct shape. 
 */
  virtual void Multiply (const double *iV, double *oMV, const CATLONG32 iNbCol = 1, const CATLONG32 iLnOfFirstAxis = 1, const CATLONG32 iLnOfLastAxis = 0, const CATLONG32 iMatrixStartRow = 0, const CATLONG32 iMatrixEndRow = -1 ) const ;
  virtual void Multiply (const CATMathSetOf3DObjects  &iV, CATMathSetOf3DObjects  &oMV ) const ;
  virtual void Multiply (const CATMathGrid &iV, CATMathGrid &oMV, const CATLONG32 iOnAxis ) const ;

/** 
 *- 2 MxN only! Multiply an equation solution iX, of length M*iNbRow by the matrix. 
 *    and subtract the result from ioRHS_RES is of length N*iNbCol. 
 */
  virtual void ResidualVector (const double *iX, double *ioRHS_RES, const CATLONG32 iNbCol = 1, const CATLONG32 iLnOfFirstAxis = 1 ) const ;
  virtual void ResidualVector (const CATMathSetOf3DObjects  &iX, CATMathSetOf3DObjects  &ioRHS_RES ) const ;
  virtual void ResidualVector (const CATMathGrid &iX, CATMathGrid &ioRHS_RES, const CATLONG32 iOnAxis ) const ;

/**
 *- 3 MxN only! Multiply an equation solution iX, of length M*iNbRow by the matrix. 
 *    and subtract iRHS of length N*iNbCol. Return the squared length of the
 *    difference. ( The squared norm of the Residual vector. )
 *
  virtual double NormOfRes (const double *iX, const double *iRHS, const CATLONG32 iNbCol = 1, const CATLONG32 iLnOfFirstAxis = 1 ) const ;
  virtual double NormOfRes (const CATMathSetOf3DObjects  &iX, CATMathSetOf3DObjects  &iRHS ) const ;
  virtual double NormOfRes (const CATMathGrid &iX, CATMathGrid &iRHS, const CATLONG32 iOnAxis ) const ;*/

/**
 *- 3 MxN only! Multiply the transpose of the matrix by iRHS of length M*iNbCol. oX is of 
 *    length N*iNbCol. Imposition may be calculated if "IdentifyConstraints(...)" has been
 *    set! oX must have suffucient size and, if set or grid, correct shape. 
 */
  virtual void TransMultiply (const double *iRHS, double *oX, const CATLONG32 iNbCol = 1, const CATLONG32 iCalculateImpositions = 0, const CATLONG32 iLnOfFirstAxis = 1, const CATLONG32 iLnOfLastAxis = 0 ) const ;
  virtual void TransMultiply (const CATMathSetOf3DObjects  &iRHS, CATMathSetOf3DObjects   &oX, const CATLONG32 iCalculateImpositions = 0 ) const ;
  virtual void TransMultiply (const CATMathGrid &iRHS, CATMathGrid  &oX, const CATLONG32 iOnAxis, const CATLONG32 iCalculateImpositions = 0 ) const ;

/**
 *- 4 As the previous but over-write the result on ioRHS_X. If set or grid, the shape of
 *    ioRHS_X is changed.
 */
  virtual void TransMultiply (double *ioRHS_X, const CATLONG32 iNbCol = 1, const CATLONG32 iCalculateImpositions = 0, const CATLONG32 iLnOfFirstAxis = 1 ) const ;
  virtual void TransMultiply (CATMathSetOf3DObjects  &ioRHS_X, const CATLONG32 iCalculateImpositions = 0 ) const ;
  virtual void TransMultiply (CATMathGrid &ioRHS_X, const CATLONG32 iOnAxis, const CATLONG32 iCalculateImpositions = 0 ) const ;

/**
 *- 5 Sym only! OBS: Also runs "UpdateTransGramProduct" as below. This method updates the
 *    "TransMultiply" reults as above but may be used from origin on an ioX and a "this"-
 *    matrix set to zero. ioX and iNewRHSRows must have the same number of columns.
 *    Imposition values in ioX will not be touched if "SetImposioion( iF )" has been 
 *    used. 
 */
  virtual void  UpdateTransMultiplyAndGramProduct (
	  const  CATLONG32    iIndCol, 
	  const  double *iNewMxNMatrixRows, 
	  const  double *iNewRHSRows,
	  const  CATLONG32    iNbRows,  
	         double *ioX, 
	  const  CATLONG32    iNbCol = 1 ) ;

/**
 *=======================================================================================
 * Product: "this transposed" * "this".    
 * It is, sometimes, possible to use use a segment of the matrix by using "iMatrixStartRow"
 * and "iMatrixEndRow".
 *
 *- 1 MxN: Overwrite the matrix by the product of the transpose of the matrix by the matrix
 *    Uses smaller memory if the matrix has increasing column indexing.
 *    The matrix is converted to a symetric one of size NxN!! 
 */
  virtual void TransGramProduct() ;

/**
 *- 2 MxN: Writes into "ioSymetric" the product of the transpose of "this" matrix by "this" 
 *    matrix. 
 *    iScale is multiplied AFTER the product, i.e. usually iScale = weight*weight.
 *    Only a part of the matrix may be considered by using iRowStart and iRowEnd.
 */
  virtual void TransGramProduct( CATMathMxNBandMatrix &ioSymetric, const double iScale = 1.0, const CATLONG32 iMatrixStartRow = 0, const CATLONG32 iMatrixEndRow = -1 ) const ;

/**
 *- 3 Sym: If iMxNOrSym is in MxN-state a "TransGramProduct, as above, is added
 *    If iMxNOrSym is in the state Sym the "TransGramProduct" is (of course) not
 *    done before the multiplication and addition.
 *    The number of columns of "this and iMxNOrSym must be the same and the bandwidth of
 *    "this" must not be smaller.
 */
  virtual void AddGramProduct( const CATMathMxNBandMatrix &iMxNOrSym, const double iScale = 1.0 , const CATLONG32 iMatrixStartRow = 0, const CATLONG32 iMatrixEndRow = -1 ) ;

/**
 *- 4 Add to "this" the TransGramProduct of new rows, starting at iIndCol. "this" must
 *    be symmetric This updates the product but the metod may be used from origin on a 
 *    (symmetric) matrix after "Reset()". The bandwidth of "this" must not be equal or
 *    greater then the iRowLength. (Default value means equal to _B ). 
 */
  virtual void UpdateTransGramProduct( 
	  const CATLONG32    iIndCol, 
	  const double *iNewMxNMatrixRows, 
	  const CATLONG32    iNbRows, 
	  const double  iScale = 1.0, 
	  const CATLONG32    iRowLength = 0 ) ;

/**
 *=======================================================================================
 *-1 Sym: Overwrite the matrix by LDLt factors. The state of the matrix is changed to 3.
 *   returns zero if faliure. 
 *   iAddToDiagonal may be used to stabilize at solution. See "Usage" after the intro-
 *   duction above.
 *   iAddToDiagonal: See "Usage" earlier in this file. Use a fraction of GetNormOfDiag().
 */
	virtual CATLONG32 FactorizeLDLt ( const double iAddToDiagonal = 0.0 ) ;
/**
 *-2 Sym: As above but writes into ioLDLt and do not affect "this".
 */

	virtual CATLONG32 FactorizeLDLt ( CATMathMxNBandMatrix &ioLDLt, const double iAddToDiagonal = 0.0 ) const ; 

/**
 *=======================================================================================
 *-1 "this" is originally in any state but converted to LDLt. 
 *   For the different interpretation of "iRHS" see "Usage" at the begining     
 *
 *   The use on three axis array (grid of points) with axis length L1, L2 and L3 respectively:
 *      Solve along first  axis ( _M == L1 ): set iNbCol = L2 * L3 and ignore "iLnOfFirstAxis"
 *      Solve along second axis ( _M == L2 ): set iNbCol = L3 and set iLnOfFirstAxis = L1.
 *      On two axis arrays you can work row-wise by: iNbCol = 1 and iLnOfFirstAxis = NbRows.
 *      iOnAxis == 1 applies solve on first  axis ( u - direction ) 
 *      iOnAxis == 2 applies solve on second axis ( v - direction ) 
 *   oX must have suffucient size and, if set or grid, correct shape. 
 */
	virtual CATLONG32 Solve ( const double *iRHS, double *oX, const CATLONG32 iNbCol = 1, const CATLONG32 iLnOfFirstAxis = 1 ) ;  
	virtual CATLONG32 Solve ( const CATMathSetOf3DObjects  &iRHS, CATMathSetOf3DObjects  &oX ) ;
	virtual CATLONG32 Solve ( const CATMathGrid &iRHS, CATMathGrid &oX, const CATLONG32 iOnAxis ) ;
	
/**
 *-2 As above but ioX is iSHS at input but oX at output.
 */
	virtual CATLONG32 Solve ( double *ioX, const CATLONG32 iNbCol = 1, const CATLONG32 iLnOfFirstAxis = 1 ) ; 
	virtual CATLONG32 Solve ( CATMathSetOf3DObjects  &ioX ) ;
	virtual CATLONG32 Solve ( CATMathGrid &ioX, const CATLONG32 iOnAxis ) ;  

/**
 * MxN state only. Band-QR methods. Periodic case can be supported later if requested.  
 * _C[0] must be 0, _C must be increasing but _C[i] must nowhere be bigger than row number i.
 * State will be changed to 4.
 *
 * On badly conditioned cases, the presicion is far better than the solve methods above.
 * Performance (speed) is lower than on the methods above, particularly if _M >> _N but,
 * if _N >> _B, far better than the corresponding use of a full matrix solver.
 *
 * 1. & 2.: The result is in the first _N rows of ioRHS or oX. OBS: oX must have length _M.
 * 3. - 5.: Does only "Q-transformation" of RHS. The intention is to enable furter optimi-
 *          zations on the transformed states and thereafter use 6. or 7.
 * 6. & 7.: Completes solving on, and only on, results from 3. - 5. or on consistent changes
 *          of those results. "this" matrix must not be changed in between.
 */
	virtual CATLONG32 SolveQR( double *ioRHS,  CATLONG32 iNbCol,  double *iWeights = NULL )  ;
	virtual CATLONG32 SolveQR( const double *iRHS,  double *oX, CATLONG32 iNbCol,  double *iWeights = NULL ) ;
	virtual CATLONG32 TransfQR( double *ioRHS1, CATLONG32 iNbCol1, double *ioRHS2, CATLONG32 iNbCol2, double *iWeights = NULL )  ;
	virtual CATLONG32 TransfQR( const double *iRHS1, double *oRHS1, CATLONG32 iNbCol1, const double *iRHS2, double *oRHS2, CATLONG32 iNbCol2, double *iWeights = NULL ) ;
	virtual CATLONG32 TransfQR( double *ioRHS1, CATLONG32 iNbCol1, double *ioRHS2, CATLONG32 iNbCol2, double *ioRHS3, CATLONG32 iNbCol3 )  ;
	virtual CATLONG32 SolveQRII( double *ioRHS,  CATLONG32 iNbCol ) ;
	virtual CATLONG32 SolveQRII( const double *iRHS,  double *oX, CATLONG32 iNbCol ) ;
 /**
 * 8.  iImp(-osition) is also of size _N and is an increasing sequence in [0.0, 1.0]. 
 *     If iImp[i] = 1.0, ioX[i] is imposed.
 *     If iImp[i] = 0.0, ioX[i] is solved in accordance with the impositions.
 *     If iImp[i] is, say 0.7, ioX[i] is "70% imposed and 30% solved". In this last case it
 *          might be important to know that the final ioX is calculated backwards (decreasing
 *          index). When calculating ioX[i], ioRHS has been consistently modified for the final
 *          values of ioX[i+1], ioX[i+2], ... ioX[_N-1]. Let xi be the solution using this state
 *          of ioRHS and the i:th diagonal element of R (of QR). Then, the final value of ioX[i] 
 *          will be 0.3 * xi + 0.7 * the given value of ioX[i].
 *     Observe that iRHS isn't constant.
 */
	virtual CATLONG32 SolveQRII( double *iRHS,  double *oX, const double *iImp, CATLONG32 iNbCol = 1.0 ) ;

/**   
 * SINGULAR VALUE DECOMPOSITION, SVD.
 * On State == 1 or State == 4 only! State will be changed to 5.
 * Let A (this) be a matrix of size _M x _N. _M >= _N.
 * Let W be a diagonal matrix of size _N x _N.   
 * Let U be a matrix of size _M x _N with ortho-normal columns.
 * Let V be a matrix of size _N x _N with ortho-normal columns.
 * If U x W x (V transposed) == A, then U, W and V is the SWD of A.
 * For more details, for the use etc: Se SVD in CATMathMxNMatrix.h.
 *
 * The matrix U is not explicitly created. On the other hand, if ioRHS
 * is given, (U transposed) * ioRHS is executed.
 *
 * After execution of SVD(...) :
 * The diagonal elements, in descending order, of W is returned by 
 * "GetSingularValues ()". The correspondingly ordered _N x _N coefficients
 * of V is returned by "GetONRange ()".
 * V multiplied by a vector may be done by (this matrix).Multiply(...) .
 */
	virtual CATLONG32 SVD( double * ioRHS = NULL, CATLONG32 iNbCol = 0 ) ;
	virtual const double * GetSingularValues () const ;	
	virtual const double * GetONRange () const ;

/**   
 * Eigen values and eigen vectors from a symmetric matrix. 
 * On State == 2 only! State will be changed to 6.
 * If 0 == yesEVectors, only the eigen values are calculated ( substantially faster )  
 */
    virtual CATLONG32 SymmetricEigenSystem( CATLONG32 yesEVectors = 1 )  ;
	virtual const double * GetEigenValues () const ;	
	virtual const double * GetEigenVectors () const ;

/**
 * By "SmoothIndices(...)" an interval of indices and singular values may be handeled around 
 * a decimal generalization of the index. The methods also works for eigen values but, may be,
 * useful only if the matrix is possitive (semi-) definite. 
 * The method is only explained by this example:
 * Consider a singular value W44 ( with index 4 ) in a decreasing sequence of nine.
 * If W44 is well separated from other singular values and iInd = 4, then
 * all ioCoef will look: 
 * { 1, 1, 1, 1, 0.5, 0, 0, 0, 0 }.       Their sum is 4.5 = iInd + 0.5.
 * for iInd = 3.5 we will have:
 * { 1, 1, 1, 1, 0, 0, 0, 0, 0 }.         Their sum is   4 = iInd + 0.5.
 * If singular values are clustered such that some has their logarithms in the interval
 * ]log(W44)-iSize , log(W44)+iSize[, the ioCoef are gradually decreasing, with increasing index, 
 * within that interval. For iInd = 4, we may get: 
 * { 1, 1, 1, 0.8, 0.5, 0.2, 0, 0, 0  }.  Their sum is 4.5 = iInd + 0.5.
 * Again with an decimal iInd, say 3.7 we may get: 
 * { 1, 1, 1, 0.7, 0.4, 0.1, 0, 0, 0  }.  Their sum is 4.2 = iInd + 0.5.
 * Returns _N if ioCoef[_N-1] = 1.0 and if not, the smallest index such that ioCoef[i] < 1.0.
 */   
	virtual CATLONG32 SmoothIndices ( double iInd, double *ioCoef, double iSize = 0.5, double iTol = 0.001 ) const ;


/**
 *=======================================================================================
 */

private :
	CATLONG32 _M, _N, _B, _MaxM, _SizeA, _SizeLL, _Periodic ;
	CATLONG32 _State ;            // 1 if MxN, 2 if Sym, 3 if LDLt. 
	CATLONG32 *_C ;               // Column indices of first non zero lelement in each row.  
	double _NormOfDiag ;     // biggest element of the matrix in symmetric state.. 
	double *_A, *_S, *_LL ;  // non zero matrix data.
	double *_RW ;            // Pointer to external array: Row weights. 
	CATLONG32   *_F ;             // Pointer to external array: Impositon information vector iF.
	CATLONG32 _LoF, _HiF ;        // Limits of interval of ones in _F.
    CATLONG32    _ConstrSize, _ConstrNbRows ;
	CATLONG32   *_ConstrRows, *_ConstrCol ; // Constraing information vectors.
	CATMathMxNMatrix *_ConstrInverse ; // To calculate impositions. 

	//virtual void TransGramProduct(double *SS ) const ;

	virtual void TransGramProduct(double *SS, const CATLONG32 SS_B, const CATLONG32 iMatrixStartRow = 0, const CATLONG32 iMatrixEndRow = -1, const double iScale = 1.0 ) const ;

	virtual void SolveLDLt ( double *ioX, const CATLONG32 iNbCol ) const ;

	virtual double SVFunc ( double iS, CATLONG32 &oloI, CATLONG32 &ohiI, double *ioK, double iSize ) const ; 
};  

#endif
