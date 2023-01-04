// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathMxNFullMatrix :
// Implementation class of full rectangular matrix of dimension M x N  
//
//===================================================================


#ifndef CATMathMxNFullMatrix_H  
#define CATMathMxNFullMatrix_H 

#include "YN000FUN.h"
#include "CATMathMxNMatrix.h"

class CATMathNxNMatrix;


class ExportedByYN000FUN CATMathMxNFullMatrix : public CATMathMxNMatrix 
{ 

 public: 
  //----------------------------------------------------------------
  //- Object Management
  //----------------------------------------------------------------
  
  //
  // Constructors 
  //
  // 1. Copy constructor
  // 2. constructor from sizes and coefficient array. 
  // 3. constructor from sizes (no initialization).
  // 4. constructor from sizes (all coefficients initialized to a)
  // 5. constructor from a full symetric matrix.
  // 6. constructor from a MxNMatrix
  //
  CATMathMxNFullMatrix (const CATMathMxNFullMatrix& copy) ;
  CATMathMxNFullMatrix (const CATLONG32 M, const CATLONG32 N, const double *A);
  CATMathMxNFullMatrix (const CATLONG32 M,  const CATLONG32 N); 
  CATMathMxNFullMatrix (const CATLONG32 M, const CATLONG32 N, const double &a);
  CATMathMxNFullMatrix (const CATMathNxNMatrix& Square) ;
  CATMathMxNFullMatrix (const CATMathMxNMatrix& matrix) ;
  //
  //- Destructor  
  //  
  ~CATMathMxNFullMatrix ();
 
};  
#endif  
