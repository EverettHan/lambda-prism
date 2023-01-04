// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathDefinitionMemoryXYDel: 
// Class like CATMathDefinitionMemoryXY but which deletes the composite 
// functions in the destructor 
//
//===================================================================

#ifndef CATMathDefinitionMemoryXYDel_H
#define CATMathDefinitionMemoryXYDel_H

#include "CATMathDefinitionMemoryXY.h"
#include "YN000FUN.h"

class CATMathFunctionXY;

class ExportedByYN000FUN CATMathDefinitionMemoryXYDel : public CATMathDefinitionMemoryXY
{
 public:
  CATMathDefinitionMemoryXYDel(      CATMathFunctionXY*  f ,
			       const CATMathInterval & DefU,
			       const CATMathInterval & DefV,
             const CATTolerance & iTolObject);
  ~CATMathDefinitionMemoryXYDel();
  CATCGMNewClassArrayDeclare;
};
#endif
