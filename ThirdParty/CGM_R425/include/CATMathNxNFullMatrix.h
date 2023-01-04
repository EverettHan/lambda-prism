// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathNxNFullMatrix:
// Class representing a temporary full square matrix in dimemsion N
//
//=============================================================================

#ifndef CATMathNxNFullMatrix_H  
#define CATMathNxNFullMatrix_H 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"
#include "CATMathNxNMatrix.h"

#include "CATMathNxNFullSymMatrix.h"


class ExportedByYN000FUN CATMathNxNFullMatrix : public CATMathNxNMatrix 
{ 
  public: 
//----------------------------------------------------------  
//- Constructors  
//----------------------------------------------------------  
  //- 1 constructor from size and coefficient array ( Mcol,row=A[row*N+col])
  //- 2 constructor from size (not initialized to zero)
  //- 3 constructor from size (coefficients initialized to zero except the diagonal ones
  //    initialized to a)
  //- 4 copy constructor
  //- 5 constructor from lower-half matrix (type CATMathNxNFullSymMatrix), if option=0 
  //    construction of a symetric matrix, if option=1 construction of a lower matrix
  //- 6 constructor from a NxNMatrix 
  //
  CATMathNxNFullMatrix ();
  CATMathNxNFullMatrix (const CATLONG32 N, const double *A);
  CATMathNxNFullMatrix (const CATLONG32 N); 
  CATMathNxNFullMatrix (const CATLONG32 N, const double & a); 
  CATMathNxNFullMatrix (const CATMathNxNFullMatrix & copy) ;
  CATMathNxNFullMatrix (const CATMathNxNFullSymMatrix * S, const CATLONG32 option=0);
  CATMathNxNFullMatrix (const CATMathNxNMatrix & matrix) ;
//----------------------------------------------------------- 
//- Destructor  
//-----------------------------------------------------------  
  ~CATMathNxNFullMatrix ();

};

ExportedByYN000FUN CATMathNxNFullMatrix * CreateCATMathNxNFullMatrix (const CATLONG32 N);    
#endif  
