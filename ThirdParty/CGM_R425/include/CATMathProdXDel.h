// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathProdXDel:
// Class like CATMathProdX but which deletes the composite 
// functions in the destructor 
//
//===================================================================
// Usage notes:
//
//===================================================================

#ifndef CATMathProdXDel_h
#define CATMathProdXDel_h

#include "CATMathProdX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathProdXDel : public CATMathProdX
{
 public:
  CATMathProdXDel(const CATMathFunctionX * iP, const CATMathFunctionX * iQ);
   ~CATMathProdXDel();
};
#endif
