// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSumXYsDel
//  Class like CATMathSumXYs but which deletes the composite functions
//  in the destructor
//
//===================================================================


#ifndef CATMathSumXYsDel_H
#define CATMathSumXYsDel_H

#include "CATMathSumXYs.h"
#include "YN000FUN.h"

class  CATMathFunctionX;

class ExportedByYN000FUN CATMathSumXYsDel : public CATMathSumXYs
{
public:
  CATMathSumXYsDel(CATMathFunctionX * fU,
		   CATMathFunctionX * fV);
  ~CATMathSumXYsDel();
  CATCGMNewClassArrayDeclare;
};

#endif
