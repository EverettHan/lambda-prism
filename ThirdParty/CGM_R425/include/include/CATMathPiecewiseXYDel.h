// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathPiecewiseXYDel
//  Class like CATMathPiecewiseXY but which deletes the composite functions
//  in the destructor
//
//===================================================================
// Usage notes:
//
//===================================================================


#ifndef CATMathPiecewiseXYDel_H
#define CATMathPiecewiseXYDel_H

#include "CATMathPiecewiseXY.h"
#include "YN000FUN.h"

class  CATMathFunctionX;

class ExportedByYN000FUN CATMathPiecewiseXYDel : public CATMathPiecewiseXY
{
public:
  CATMathPiecewiseXYDel(const CATLONG32 NU,
			const double * bordersU,
			const CATLONG32 NV,
			const double * bordersV,
			CATMathFunctionXY ** functions,
                        const double * iShiftU=0,
                        const double * iShiftV=0);

  virtual ~CATMathPiecewiseXYDel();
  CATCGMNewClassArrayDeclare;

private:
  CATMathPiecewiseXYDel & operator = (const CATMathPiecewiseXYDel & p);
};

#endif
