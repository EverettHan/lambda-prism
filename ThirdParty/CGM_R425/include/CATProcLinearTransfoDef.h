// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle the procedural definition of a curve defined
// bu the offset the the profile of a tabulated cylinder
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// May. 00 Creation                                                X. Gourdon
// Aug. 11 Added the function GetTransfo() (for comparing geometries).    R1Y
//=============================================================================
#ifndef CATProcLinearTransfoDef_H
#define CATProcLinearTransfoDef_H

#include "YP00IMPL.h"                    

#include "CATProcCurveDef.h"
#include "CATMathTransformation.h"

class CATCurve;
class CATMathFunctionX;
class CATCGMStream;

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcLinearTransfoDef : public CATProcCurveDef
{
public:

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATProcLinearTransfoDef(CATCurve* iCurve,
                          const CATMathTransformation & iTransfo);
  CATProcLinearTransfoDef(CATCurve* iCurve);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  ~CATProcLinearTransfoDef();
  
  //-------------------------------------------------------------------------
  // Gets the type of proccurve
  //-------------------------------------------------------------------------
  CATProcCurveDef::Type GetType() const;

  //-------------------------------------------------------------------------
  // Create the local equations on a given arc
  // (The returned pointers must be deleted by the caller)
  //-------------------------------------------------------------------------
  void CreateLocalEquation(CATLONG32 iArcIndex,
                           CATMathFunctionX * & oFx,
                           CATMathFunctionX * & oFy,
                           CATMathFunctionX * & oFz) const;

  //-------------------------------------------------------------------------
  // Evaluates the proccurve without building the equations
  //-------------------------------------------------------------------------
  void Eval(const CATCrvParam & iParam,
	    const CATCrvEvalCommand & iCommand,
	    CATMathPoint* oPoint,
	    CATMathVector* oFirstDeriv,
	    CATMathVector* oSecondDeriv,
	    CATMathVector* oThirdDeriv ) const;

  //-------------------------------------------------------------------------
  // For Streaming (stream all but the Curve)
  //-------------------------------------------------------------------------
  void Stream( CATCGMStream& Str );
  void UnStream( CATCGMStream& Str );
  CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  CATProcCurveDef * Duplicate() const;
  void ApplyTransformation(const CATMathTransformation & iTransfo);
  const CATMathTransformation & GetTransfo() const;

protected:
  CATMathTransformation _Transfo;
};

#endif
