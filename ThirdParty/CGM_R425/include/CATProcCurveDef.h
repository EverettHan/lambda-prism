// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Base class designed to handle the procedural definition of a curve based other 
// another curve (CATProcCurve class) 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// May. 00   Creation                                     X. Gourdon
//=============================================================================
#ifndef CATProcCurveDef_H
#define CATProcCurveDef_H

#include "YP00IMPL.h"                    
#include "CATCGMDefCurve.h"

class CATCurve;
class CATMathFunctionX;
class CATCGMStream;
class CATMathTransformation;
class CATCrvParam;
class CATCrvEvalCommand;
class CATMathPoint;
class CATMathVector;


//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcCurveDef : public CATCGMDefCurve
{
public:

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATProcCurveDef(CATCurve* iCurve);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATProcCurveDef();
  
  //-------------------------------------------------------------------------
  // Gets the type of proccurve
  //-------------------------------------------------------------------------
  enum Type {
    CATProcOffsetTabProfileDefType=1,
    CATProcOffsetRevolProfileDefType=2,
    CATProcLinearTransfoDefType=3
  };
  virtual CATProcCurveDef::Type GetType() const = 0;

  //-------------------------------------------------------------------------
  // Create the local equations on a given arc
  // (The returned pointers must be deleted by the caller)
  //-------------------------------------------------------------------------
  virtual void CreateLocalEquation(CATLONG32 iArcIndex,
                                   CATMathFunctionX * & oFx,
                                   CATMathFunctionX * & oFy,
                                   CATMathFunctionX * & oFz) const = 0;

  //-------------------------------------------------------------------------
  // Evaluates the proccurve without building the equations
  //-------------------------------------------------------------------------
  virtual void Eval(const CATCrvParam & iParam,
	    const CATCrvEvalCommand & iCommand,
	    CATMathPoint* oPoint,
	    CATMathVector* oFirstDeriv,
	    CATMathVector* oSecondDeriv,
	    CATMathVector* oThirdDeriv ) const = 0;

  //-------------------------------------------------------------------------
  // Gets a pointer toward the reference curve
  //-------------------------------------------------------------------------
  virtual CATCurve* GetCurve() const;

  //-------------------------------------------------------------------------
  // Set a pointer toward the reference curve
  //-------------------------------------------------------------------------
  virtual void SetCurve(CATCurve * iCurve);

  //-------------------------------------------------------------------------
  // Duplicate this 
  //-------------------------------------------------------------------------
  virtual CATProcCurveDef * Duplicate() const = 0;

  //-------------------------------------------------------------------------
  // Apply isometric transformation on the data (not to the curve)
  //-------------------------------------------------------------------------
  virtual void ApplyTransformation(const CATMathTransformation & iTransfo);

protected:
  CATCurve*     _Curve;

  void EvalHighOrderDeriv (int iOrder, 
                           const CATCrvParam & iParam,
                           CATMathVector* iDeriv,
                           CATMathVector* oDeriv) const;


};

#endif
