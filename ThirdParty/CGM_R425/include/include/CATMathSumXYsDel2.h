// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSumXYsDel2
//  Destroys fu (and not fv) when destroyed
//
//===================================================================


#ifndef CATMathSumXYsDel2_H
#define CATMathSumXYsDel2_H

#include "CATMathSumXYs.h"
#include "YN000FUN.h"

class  CATMathFunctionX;

class ExportedByYN000FUN CATMathSumXYsDel2 : public CATMathSumXYs
{
public:
  CATMathSumXYsDel2(CATMathFunctionX * fU,
		   CATMathFunctionX * fV);
  ~CATMathSumXYsDel2();
  CATCGMNewClassArrayDeclare;
};

#endif
