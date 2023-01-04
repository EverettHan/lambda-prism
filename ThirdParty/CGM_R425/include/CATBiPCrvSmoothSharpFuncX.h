// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CATBiPCrvSmoothSharpFuncX:
//
//=============================================================================
//
//=============================================================================
// Feb. 2003   Creation                                   S. Dauby
//=============================================================================

#ifndef CATBiPCrvSmoothSharpFuncX_h
#define CATBiPCrvSmoothSharpFuncX_h

#include "CATMathFunctionX.h"
#include "CATMathBasisFunctionX.h"


class CATPCurve;
class CATMathVector;

class CATSetOfPointsMapX;
class CATSoftwareConfiguration;

class CATBiPCrvSmoothSharpFuncX : public CATMathBasisFunctionX
{
public:
  CATBiPCrvSmoothSharpFuncX(      CATSoftwareConfiguration *       iConfig,
                            const CATPCurve                * const iPCrv[2],
                            const double                           iExtremities[4],
                            const double                           iThreshold,
                            const CATTolerance             &       iTolObject);

  virtual ~CATBiPCrvSmoothSharpFuncX();

  double Eval(const double & w) const;
  
  CATMathFunctionX * Duplicate() const;
  
  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;

  void SetThreshold(const double threshold);
  void SetExtremities(const double extremities[4]);

  void SetMapX(const CATSetOfPointsMapX * iMapX);

private:

  double EvalWithMapX(const double & iW) const;
  double EvalFromNormal(const CATMathVector iSupportNormal[]) const;

  CATSoftwareConfiguration * _Config;

  const CATPCurve * _PCrv[2];
  
  double _Extremities[4];
  double _Threshold;

  const CATSetOfPointsMapX * _MapX;
};

#endif
