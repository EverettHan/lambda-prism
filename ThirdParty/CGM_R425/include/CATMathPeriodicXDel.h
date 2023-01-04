// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathPeriodicXDel :
// Class like CATMathPeriodicX but which deletes the composite 
// functions in the destructor 
//
//===================================================================

#ifndef CATMathPeriodicXDel_h
#define CATMathPeriodicXDel_h

#include "CATMathPeriodicX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathPeriodicXDel : public CATMathPeriodicX
{
 public:
  CATMathPeriodicXDel(CATMathFunctionX *, double, double);


  ~CATMathPeriodicXDel();
  CATCGMNewClassArrayDeclare;
};

#endif
