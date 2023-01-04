// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATPolyMathMxNMatrix :
//
// Rectangular matrix of dimension MxN (M is the number of rows
//                                      N is the number of colummns)
//
//===================================================================


#ifndef CATPolyMathMxNMatrix_H  
#define CATPolyMathMxNMatrix_H 

  
#include "PolyMathUtils.h"
#include "CATDataType.h"
 
class ExportedByPolyMathUtils CATPolyMathMxNMatrix   
{  

public: 
  //----------------------------------------------------------------
  //- Object Management
  //----------------------------------------------------------------
  //
   
  // 0. default constructor
  // 1. constructor from sizes (no initialization)
   
  //
   
  CATPolyMathMxNMatrix(const CATLONG32 M,  const CATLONG32 N) ; 
   
  //  
  //- Destructor  
  //  
  virtual ~CATPolyMathMxNMatrix () ;
  
   

   
   
  virtual void SetCoef (const CATLONG32 row, const CATLONG32 column, const double A) ; 
   
  
  //----------------------------------------------------------------
  //- Get Coefficients methods
  //----------------------------------------------------------------
  //
  //- 1 Get a coefficient of the matrix 
  //    0 <= row < M,,column < N-1
   
  //    rowstart <= row <= rowend   linestart <= line <= lineend
  double GetCoef (const CATLONG32 row, const CATLONG32 column) const ;
   
  void Product(CATPolyMathMxNMatrix & A ,CATPolyMathMxNMatrix & B ,CATPolyMathMxNMatrix & C);
   
   
  protected:

  CATLONG32 _M, _N;  // dimension of matrix
  double *_A;   // coefficient of matrix : _A[i*_N+j] is the i-th line j-th column coef.
 

};

#endif  

