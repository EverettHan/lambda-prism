// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathDefinitionMemoryXDel: 
// Class like CATMathDefinitionMemoryX but which deletes the composite 
// functions in the destructor 
//
//===================================================================

#ifndef CATMathDefinitionMemoryXDel_H
#define CATMathDefinitionMemoryXDel_H

#include "CATMathDefinitionMemoryX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathDefinitionMemoryXDel : public CATMathDefinitionMemoryX
{
 public:
  CATMathDefinitionMemoryXDel(      CATMathFunctionX*  f ,
			      const CATMathInterval & Def);
  ~CATMathDefinitionMemoryXDel();
  CATCGMNewClassArrayDeclare;
};
#endif
