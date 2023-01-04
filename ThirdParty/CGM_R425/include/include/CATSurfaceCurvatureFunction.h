// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSurfaceCurvatureFunction :
// Functions of two variables, each of which needs to compute the
//  first and second fundamental forms.  A flag determines whether
//  the evaluations return Gauss curvature, mean curvature,
//  greater principal curvature, or lesser principal curvature.
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev.98    Creation                                      F.Holt
//=============================================================================

#ifndef CATSurfaceCurvatureFunction_H
#define CATSurfaceCurvatureFunction_H

#include "CATPGMSurfaceCurvatureFunction.h"
#include "CATMathVector.h"
#include "CATMathInterval.h"
//DG
#include "Y30C3XGG.h"
#include "CATMathBasisFunctionXY.h"
#include "CATTolerance.h"

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATSurfaceCurvatureFunction : public CATPGMSurfaceCurvatureFunction
{
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  // copy-constructor  
  CATSurfaceCurvatureFunction(const CATSurfaceCurvatureFunction & iF);

  // constructor
  CATSurfaceCurvatureFunction(const CATMathFunctionXY * iFX,
                              const CATMathFunctionXY * iFY,
                              const CATMathFunctionXY * iFZ,
                              const CATCurvatureType    itype      = GaussianCurvature,
                              const CATTolerance      & iTolObject = CATGetDefaultTolerance());

  ~CATSurfaceCurvatureFunction();
  CATMathFunctionXY * Duplicate() const;

  void  SetType( const CATCurvatureType NewType);
  CATCurvatureType GetType();

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
   
  double Eval(const double & u, const double & v) const;

protected:
  CATCurvatureType  _Type;
  const CATMathFunctionXY * _FX, * _FY, * _FZ;
};

//DG
ExportedByY30C3XGG CATSurfaceCurvatureFunction * CreateSurfaceCurvatureFunction(const CATMathFunctionXY * iFX,
                                                                                const CATMathFunctionXY * iFY,
                                                                                const CATMathFunctionXY * iFZ,
                                                                                const CATTolerance & iTolObject = CATGetDefaultTolerance(),
                                                                                const CATCurvatureType itype = GaussianCurvature); 

#endif
