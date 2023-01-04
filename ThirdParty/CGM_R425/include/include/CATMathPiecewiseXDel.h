// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathPiecewiseXDel :
// Class like CATMathPiecewiseX but which deletes the composite 
// functions in the destructor 
//
//===================================================================


#ifndef CATMathPiecewiseXDel_h
#define CATMathPiecewiseXDel_h

#include "CATMathPiecewiseX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathPiecewiseXDel : public CATMathPiecewiseX
{
 public:
  CATMathPiecewiseXDel(const CATLONG32 N,
		       const double * borders,
		             CATMathFunctionX ** functions);


  ~CATMathPiecewiseXDel();
  CATCGMNewClassArrayDeclare;
};

#endif
