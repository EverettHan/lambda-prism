#ifndef CATPGMLawEquationDistPCrvPCrv_h_
#define CATPGMLawEquationDistPCrvPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATTolerance.h"

class CATIPGMCrvLengths;
class CATCrvParam;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathFunctionX;

ExportedByCATGMOperatorsInterfaces CATMathFunctionX *CATPGMCreateLawEquationDistPCrvPCrv(
        CATSoftwareConfiguration *  iConfig,
        CATPCurve                *  iPCrv1,
        CATPCurve                *  iPCrv2,
        CATPCurve                *  iPCrvRef,
  const CATCrvParam               & iPCrv1Start,
  const CATCrvParam               & iPCrv1End,
  const CATCrvParam               & iPCrv2Start,
  const CATCrvParam               & iPCrv2End,
  const CATCrvParam               & iPCrvRefStart,
  const CATCrvParam               & iPCrvRefEnd,
  const double                      iLambdaStart,
  const double                      iLambdaEnd,
  const short                       iOrientationFlag,
  const CATTolerance              & iTolObject = CATGetDefaultTolerance());

// pour composite constructor
ExportedByCATGMOperatorsInterfaces CATMathFunctionX *CATPGMCreateLawEquationDistPCrvPCrv(
        CATSoftwareConfiguration *  iConfig,
        CATPCurve                *  iPCrvBase,
        CATPCurve                *  iPCrvInf,
        CATPCurve                *  iPCrvSup,
        CATPCurve                *  iPCrvRef,
  const CATCrvParam               & iPCrvBaseStart,
  const CATCrvParam               & iPCrvBaseEnd,
  const CATCrvParam               & iPCrvInfStart,
  const CATCrvParam               & iPCrvInfEnd,
  const CATCrvParam               & iPCrvSupStart,
  const CATCrvParam               & iPCrvSupEnd,
  const CATCrvParam               & iPCrvRefStart,
  const CATCrvParam               & iPCrvRefEnd,
  const double                      iLambdaStart,
  const double                      iLambdaEnd,
  const short                       iOrientationFlag,
  const CATTolerance              & iTolObject = CATGetDefaultTolerance());

#endif /* CATPGMLawEquationDistPCrvPCrv_h_ */
