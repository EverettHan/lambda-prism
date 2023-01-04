// COPYRIGHT DASSAULT SYSTEMES 1999

//===================================================================
//=================================================================== 
//
// CATMathNxNMatrixForNewtonBfgs :
// Full Square Symetric matrix of dimension N  
//
//===================================================================


#ifndef CATMathNxNMatrixForNewtonBfgs_H  
#define CATMathNxNMatrixForNewtonBfgs_H 

#include "CATMathNxNMatrix.h"


class ExportedByYN000FUN CATMathNxNMatrixForNewtonBfgs : public CATMathNxNMatrix 
{ 

public: 
//
//- Constructor -------------------------------------------------------
//
// Size N not initialized
//
  CATMathNxNMatrixForNewtonBfgs (const CATLONG32 N);
//  
//- Destructor -------------------------------------------------------------- 
//  
  virtual ~CATMathNxNMatrixForNewtonBfgs ();

//------------------------------------------------------------------------------------

//-  Set 0.  on the row and the column repered by iIndice
//		and set 1. on the diagonal element
// 
	 void SetRowAndColumn (const CATLONG32 iIndice) ;
 
};  
#endif  
