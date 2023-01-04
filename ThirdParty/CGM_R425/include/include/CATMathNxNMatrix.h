// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//===================================================================
//
// Abstract class CATMathNxNMatrix 
// Square matrix of dimension N
//
//===================================================================


#ifndef CATMathNxNMatrix_H  
#define CATMathNxNMatrix_H 
#include "CATMathMxNMatrix.h"

class CATMathNxNFullSymMatrix;
class CATMathNxNBandSymMatrix;

class ExportedByYN000FUN CATMathNxNMatrix  : public CATMathMxNMatrix    
{  

public: 
//----------------------------------------------------------  
//- Constructors  
//----------------------------------------------------------  
  //- 1 default constructor
  //- 2 constructor from size (not initialized to zero)
  //- 3 constructor from size and coefficient array ( Mcol,row=A[row*N+col])
  //- 4 constructor from size (coefficients initialized to zero except the diagonal ones
  //    initialized to a)
  //- 5 copy constructor 
  //- 6 constructor from lower-half matrix (type CATMathNxNFullSymMatrix), if option=0 
  //    construction of a symetric matrix, if option=1 construction of a lower matrix
  //- 7 constructor from CATMathNxNBandSymMatrix
  //
  CATMathNxNMatrix ();
  CATMathNxNMatrix (const CATLONG32 N); 
  CATMathNxNMatrix (const CATLONG32 N, const double *A);
  CATMathNxNMatrix (const CATLONG32 N, const double & a); 
  CATMathNxNMatrix (const CATMathNxNMatrix & copy) ;
  CATMathNxNMatrix (const CATMathNxNFullSymMatrix * S, const CATLONG32 option=0);
  CATMathNxNMatrix (const CATMathNxNBandSymMatrix & base);

 // No effect on NxN matrices
   virtual void InsertRow(const double *row, const CATLONG32 iIndex);

 // No effect on NxN matrices
   virtual void RemoveRow(const CATLONG32 iIndex);

//-----------------------------------------------------------  
//- Destructor  
//-----------------------------------------------------------  
  virtual ~CATMathNxNMatrix () ;

//-----------------------------------------------------------
//-  Operator =  
//-----------------------------------------------------------
  virtual CATMathNxNMatrix& operator= (const CATMathNxNMatrix& equals) ;

//-----------------------------------------------------------
//- Get the size of the matrix 
//-----------------------------------------------------------  
  virtual CATLONG32 GetSizeOfMatrix () const;  

//-----------------------------------------------------------
//- Get the type of the matrix 
//-----------------------------------------------------------  
  virtual CATMathMatrixType GetTypeOfMatrix () const;  

//----------------------------------------------------------
//- Transpose the matrix
//----------------------------------------------------------- 
  virtual void Transpose () ;

//-------------------------------------------------------------
//- Get the trace of the matrix 
// ------------------------------------------------------------ 
  virtual double Trace () const;

//-----------------------------------------------------------  
//- Determinant 
//---------------------------------------------------------- 
  virtual double Determinant () ;
  //  
  //- Determinant the matrix is modified
  //  
  virtual double DeterminantFast ();

//------------------------------------------------------------
//- Solve a AX=B where A is the matrix NxN 
//	BX is a NxNbCol matrix
//
// Attention: The matrix and vector are modified
//-----------------------------------------------------------
   virtual CATMathDiagnostic Solve (double *BX, const CATLONG32 NbCol=1) ;

//-----------------------------------------------------------
//- Solve a AX=B where A is the matrix NxN
//	B and X are NxNbCol matrix
//
//  The matrix remains unchanged.
//-----------------------------------------------------------
  virtual CATMathDiagnostic Solve (const double *B, double *X, const CATLONG32 NbCol=1) const;

//-----------------------------------------------------------
// Put in B the inverse of *this
//-----------------------------------------------------------
  virtual CATMathDiagnostic Inverse(CATMathNxNMatrix & B) const;

//---------------------------------------------------------------------   
// Overload operator
//---------------------------------------------------------------------   

//- Self Product by a scalar
CATMathNxNMatrix & operator *=(const double alpha) ;       

//
// This method exists on non-officiel for debug.                      
//
  friend ostream & operator<< (ostream &op, const  CATMathNxNMatrix &);
};

#endif  
