// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSingleMemoryXYDel:
// Class like CATMathSingleMemoryXY but which deletes the composite 
// functions in the destructor 
//
//===================================================================
// Usage notes:
//
//===================================================================

#ifndef CATMathSingleMemoryXYDel_H
#define CATMathSingleMemoryXYDel_H

#include "CATMathSingleMemoryXY.h"
#include "YN000FUN.h"

class CATMathFunctionXY;

class ExportedByYN000FUN CATMathSingleMemoryXYDel : public CATMathSingleMemoryXY
{
 public:
  CATMathSingleMemoryXYDel(const CATMathFunctionXY *f,
		       const double x = 0. ,const double y = 0. ,const CATTolerance & iTolObject = CATGetDefaultTolerance(), CATBoolean InitAtFirstEval = FALSE);

 ~CATMathSingleMemoryXYDel();
   CATCGMNewClassArrayDeclare;
};
#endif
