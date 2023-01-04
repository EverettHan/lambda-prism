//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CATVariableFilletG1InitInPlaneSystem
// Class derived from CATMathSystem to find Inits for the Connect Operator
// 
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Dec. 2003   Creation                                           FCX
// Octobre 2004 - Versionning Interne - EAB
//=============================================================================

#ifndef CATVariableFilletG1InitInPlaneSystem_H
#define CATVariableFilletG1InitInPlaneSystem_H

#include "Connect.h"
#include "CATMathSystem.h"
#include "CATMathNormal.h" 

class CATMathFunctionXY;
class CATMathFunctionX;
class CATVariableFilletTool;
class CATCurve;
class CATSoftwareConfiguration;

class CATVariableFilletG1InitInPlaneSystem : public CATMathSystem
{
public:

  CATVariableFilletG1InitInPlaneSystem(CATSoftwareConfiguration * iConfig,
                                       const CATMathFunctionXY * iS1x,
                                       const CATMathFunctionXY * iS1y,
                                       const CATMathFunctionXY * iS1z,
                                       const CATMathFunctionXY * iS2x,
                                       const CATMathFunctionXY * iS2y,
                                       const CATMathFunctionXY * iS2z,
                                       const double iFixedPoint[3],
                                       const CATVariableFilletTool * iRadiusTool,
                                       const double * iDomainCenter1,
                                       const double * iDomainCenter2,
                                       const CATLONG32 & iOrientation1,
                                       const CATLONG32 & iOrientation2,
                                       const CATTolerance & iTolObject);

 CATVariableFilletG1InitInPlaneSystem(      CATSoftwareConfiguration * iConfig,
                                    const CATMathFunctionXY        * iS1x,
                                    const CATMathFunctionXY        * iS1y,
                                    const CATMathFunctionXY        * iS1z,
                                    const CATMathFunctionXY        * iS2x,
                                    const CATMathFunctionXY        * iS2y,
                                    const CATMathFunctionXY        * iS2z,
                                    const double                     iFixedPoint[3],
                                     CATCurve* iSpine,
                                    const double iRadius,
                                    const double                   * iDomainCenter1,
                                    const double                   * iDomainCenter2,
                                    const CATLONG32                & iOrientation1,
                                    const CATLONG32                & iOrientation2,
                                    const CATTolerance             & iTolObject);

  ~CATVariableFilletG1InitInPlaneSystem();

  void Eval         (const double *iX, double *oFX);
  //void EvalJacobian (const double *iX, CATMathNxNFullMatrix *oJacobianFX); 
  //void Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix * oJacobianFX);

private:

  const CATMathFunctionXY * _S1[3];
  const CATMathFunctionXY * _S2[3];
  double _FixedPoint[3];
  CATLONG32 _Orientation1, _Orientation2;
  const CATMathFunctionX *_Radius;
  const double _ConstRadius;
  const CATMathFunctionX *_Spine[3];
  CATCurve *_SpineCurve;
  CATMathNormal _NormalEvaluatorS1, _NormalEvaluatorS2;
  CATSoftwareConfiguration * _Config;
};
#endif

