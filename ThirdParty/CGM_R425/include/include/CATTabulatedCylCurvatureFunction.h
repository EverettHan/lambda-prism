// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATTabulatedCylCurvature Function :
// The principal directions of curvature at (u,v) of a tabulated cylinder of 
// profile C and direction D are e2 = D and e1 = the direction orthogonal to D in 
// the tangent plane. The associated principal curvatures are k2=0 along e2=D and 
// k1 along e1, which is calculated by this function. Of course, k1 depends only on 
// the parametre along C, i.e. u.
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct 2001    Creation                                      LR
// Nov 2001    Modifications                                 SDP
//=============================================================================

#ifndef CATTabulatedCylCurvatureFunction_H
#define CATTabulatedCylCurvatureFunction_H

#include "CATMathFunctionX.h"
#include "Y30C3XGG.h" 
class CATCurve;
#include "CATMathDirection.h"
#include "CATMathBasisFunctionX.h"



class ExportedByY30C3XGG CATTabulatedCylCurvatureFunction : public CATMathBasisFunctionX
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  // copy-constructor  
  CATTabulatedCylCurvatureFunction(const CATTabulatedCylCurvatureFunction & iF);

  // constructor
  CATTabulatedCylCurvatureFunction(const CATCurve * iCurve, const CATMathDirection & iD, const CATTolerance & iTolObject = CATGetDefaultTolerance());
  ~CATTabulatedCylCurvatureFunction();
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
   
  double Eval(const double & u) const;

private:
  const CATCurve * _Curve;
  CATMathDirection _D;

};

ExportedByY30C3XGG CATMathFunctionX * CreateTabulatedCylCurvatureFunction(const CATCurve * iCurve, const CATMathDirection & iD);

#endif
