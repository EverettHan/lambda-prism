// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATEquationDistancePtPCrv :
// Function of one variable representing the square of the distance from a point
// to a pcurve (in 2d).
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jul. 97    Creation                                      X. Gourdon
// Nov. 06    depl en ProtectedInterfaces                           P. Catel
//=============================================================================

#ifndef CATEquationDistancePtPCrv_H
#define CATEquationDistancePtPCrv_H

#include "CATMathFunctionX.h"

#include "Y30C1XMM.h"
#include "CATMathBasisFunctionX.h"
#include "CATTolerance.h"



class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByY30C1XMM CATEquationDistancePtPCrv : public CATMathBasisFunctionX
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  
  CATEquationDistancePtPCrv(const CATEquationDistancePtPCrv & iF);
  CATEquationDistancePtPCrv(CATSoftwareConfiguration * iConfig,
                            const double & iPtU, const double & iPtV,
                            const CATMathFunctionX * iFU,
                            const CATMathFunctionX * iFV,
                            const CATTolerance & iTolObject = CATGetDefaultTolerance());
  ~CATEquationDistancePtPCrv();
  CATMathFunctionX * Duplicate() const;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;

  void Eval(const double t, const CATMathOption iOption, double * f, double * df = 0, double * d2f = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
   
private:
  double _u, _v;
  const CATMathFunctionX * _FU, * _FV;
  CATSoftwareConfiguration * _Config;
};

ExportedByY30C1XMM CATMathFunctionX * CATCreateEquationDistancePtPCrv(CATSoftwareConfiguration * iConfig,
                                                                      const double & iPtU,
                                                                      const double & iPtV,
                                                                      const CATMathFunctionX * iFU,
                                                                      const CATMathFunctionX * iFV,
                                                                      const CATTolerance & iTolObject = CATGetDefaultTolerance());

#endif
