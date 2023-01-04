#ifndef CATMathFunctionScaleTools_H
#define CATMathFunctionScaleTools_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// Usage:
//
//=============================================================================
// 03/02/16 F1Z : Creation.
//=============================================================================

#include "YN000FUN.h"

class CATMathAttrScaleOption;
class CATMathFunctionX ;

//-----------------------------------------------------------------------------
// Create a new fonction which has the iTargetScaleOption scale properties.
// /!\ : A new fonction is always created even if the scale option are identical.
//       Use CATMathAttrScaleOption::IsEqual to check if the target option is
//       not the same as the current one.
//-----------------------------------------------------------------------------
ExportedByYN000FUN CATMathFunctionX * CATCreateScaledFunction(      double                   iScale            ,
                                                              const CATMathFunctionX       & iF                ,
                                                              const CATMathAttrScaleOption & iFScaleOption     ,
                                                              const CATMathAttrScaleOption & iTargetScaleOption);

#endif
