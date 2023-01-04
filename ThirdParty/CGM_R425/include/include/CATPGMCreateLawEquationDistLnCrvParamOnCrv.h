#ifndef CATPGMCreateLawEquationDistLnCrvParamOnCrv_h_
#define CATPGMCreateLawEquationDistLnCrvParamOnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
// 31/10/18 NLD XScale: argument iTolObject
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATTolerance.h"

class CATCrvParam;
class CATCurve;
class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;
class CATMathFunctionX;

// Constructor for an algebraic law
//  NormalLine must be orthogonal to DirectionLine, and in the same plane as the line and the curve.
//  It indicates the positive sense.
//
ExportedByCATGMOperatorsInterfaces CATMathFunctionX *CATPGMCreateLawEquationDistLnCrvParamOnCrv(
        CATSoftwareConfiguration *  iConfig,
        double                      wStart,
        double                      wEnd,
  const CATMathPoint              & StartPointLine,
  const CATMathVector             & DirectionLine,
        CATPositiveLength           LengthRef,
  const CATMathVector             & NormalLine,
        CATCurve                 *  Curve,
  const CATCrvParam               & ParamStartCurve,
  const CATCrvParam               & ParamEndCurve,
  const CATTolerance              & iTolObject = CATGetDefaultTolerance());

// Constructor for a positive law
//
ExportedByCATGMOperatorsInterfaces CATMathFunctionX *CATPGMCreateLawEquationDistLnCrvParamOnCrv(
        CATSoftwareConfiguration *  iConfig,
        double                      wStart,
        double                      wEnd,
  const CATMathPoint              & StartPointLine,
  const CATMathVector             & DirectionLine,
        CATPositiveLength           LengthRef,
        CATCurve                 *  Curve,
  const CATCrvParam               & ParamStartCurve,
  const CATCrvParam               & ParamEndCurve,
  const CATTolerance              & iTolObject = CATGetDefaultTolerance());

#endif /* CATPGMCreateLawEquationDistLnCrvParamOnCrv_h_ */
