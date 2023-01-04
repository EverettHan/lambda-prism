//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATMathSumSquareXDel :
// class of sum of the square of n  functions  of one variable
//
//=============================================================================
// Usage notes:
//
//=============================================================================


#ifndef CATMathSumSquareXDel_h
#define CATMathSumSquareXDel_h

#include "YN000FUN.h"

#include "CATMathSumSquareX.h"


class ExportedByYN000FUN CATMathSumSquareXDel : public CATMathSumSquareX
{
public:
	//-----------------------------------------------------------------
	//- Object Management
	//-----------------------------------------------------------------
	CATMathSumSquareXDel(CATLONG32 iN, const CATMathFunctionX ** iFunctions);
	virtual ~CATMathSumSquareXDel();
	
};

#endif
