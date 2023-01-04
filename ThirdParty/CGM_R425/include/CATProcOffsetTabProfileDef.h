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
// May. 00   Creation                                     X. Gourdon
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Aug. 11 Added GetUMin() and GetUMax() (for comparing geometries).      R1Y
//=============================================================================
#ifndef CATProcOffsetTabProfileDef_H
#define CATProcOffsetTabProfileDef_H

#include "YP00IMPL.h"                    

#include "CATProcCurveDef.h"
#include "CATMathDef.h"
#include "CATMathVector.h"

class CATCurve;
class CATMathFunctionX;


//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcOffsetTabProfileDef : public CATProcCurveDef
{
public:

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATProcOffsetTabProfileDef(CATCurve* iCurve,
                             const CATMathVector & iDirection,
                             double iOffsetRadius,
                             double iUMin, double iUMax);

  CATProcOffsetTabProfileDef(CATCurve* iCurve);
  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  ~CATProcOffsetTabProfileDef();
  

  //-------------------------------------------------------------------------
  // Gets the type of proccurve
  //-------------------------------------------------------------------------
  CATProcCurveDef::Type GetType() const;

  void GetDirection(CATMathVector & oDirection) const;
  double GetOffsetRadius() const;

  double GetUMin() const;
  double GetUMax() const;

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
  // For Streaming
  //-------------------------------------------------------------------------
  void Stream( CATCGMStream& Str ) ;
  void UnStream( CATCGMStream& Str ) ;

  CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;


  //-------------------------------------------------------------------------
  // Duplicate this 
  //-------------------------------------------------------------------------
  CATProcCurveDef * Duplicate() const;

  void ApplyTransformation(const CATMathTransformation & iTransfo);


protected:
  CATMathVector _Direction;
  double _OffsetRadius;
  double _UMin;
  double _UMax;
};

#endif
