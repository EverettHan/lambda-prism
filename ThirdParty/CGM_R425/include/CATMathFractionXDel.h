// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathFractionXDel:
// Class like CATMathFractionX but which deletes the composite 
// functions in the destructor
//
//===================================================================

#ifndef CATMathFractionXDel_h
#define CATMathFractionXDel_h

#include "CATMathFractionX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathFractionXDel : public CATMathFractionX
{
 public:
  CATMathFractionXDel(CATMathFunctionX *P, CATMathFunctionX *Q, const CATTolerance &iTol=CATGetDefaultTolerance());

  ~CATMathFractionXDel();
  CATCGMNewClassArrayDeclare;
};
#endif
