// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathCombinationXYDel:
// Class like CATMathCombinationXY but which deletes the composite 
// functions in the destructor 
//
//===================================================================

#ifndef CATMathCombinationXYDel_h
#define CATMathCombinationXYDel_h

#include "CATMathCombinationXY.h"
#include "YN000FUN.h"

class CATMathFunctionXY;

class ExportedByYN000FUN CATMathCombinationXYDel : public CATMathCombinationXY
{
 public:
  CATMathCombinationXYDel(      CATLONG32 N,
			        CATMathFunctionXY ** functions,
			  const double * coef,
			  const double constant = 0.);

  ~CATMathCombinationXYDel();
   CATCGMNewClassArrayDeclare;
};
#endif
