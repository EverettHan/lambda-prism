// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle the procedural definition of a curve defined
// bu the offset of the profile of a Revolution surface
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// June 00 Creation                                                       FBZ
// Aug. 11 Added GetUMin() and GetUMax() (for comparing geometries).      R1Y
//=============================================================================
#ifndef CATProcOffsetRevolProfileDef_H
#define CATProcOffsetRevolProfileDef_H

#include "YP00IMPL.h"                    

#include "CATProcCurveDef.h"
#include "CATMathDef.h"
#include "CATMathAxis.h"
#include "CATMathVector.h"

class CATCurve;
class CATMathFunctionX;


//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcOffsetRevolProfileDef : public CATProcCurveDef
{
public:
	
	//-------------------------------------------------------------------------
	// Constructors
	//-------------------------------------------------------------------------
  // If specified, iUMin and iUMax give reference limits to correctly orient
  // the offset (change of sign when crossing the axis).
	CATProcOffsetRevolProfileDef(CATCurve* iCurve,
		const CATMathAxis & iAxis,
		const CATMathVector & iVect,
		double iOffsetRadius,
    double iUMin = 1., double iUMax = -1.);
	
	CATProcOffsetRevolProfileDef(CATCurve* iCurve);
	//-------------------------------------------------------------------------
	// virtual Destructor
	//-------------------------------------------------------------------------
	~CATProcOffsetRevolProfileDef();
	
	//-------------------------------------------------------------------------
	// Gets the type of proccurve
	//-------------------------------------------------------------------------
	CATProcCurveDef::Type GetType() const;

  void GetAxis(CATMathAxis & oAxis) const;
  void GetVector(CATMathVector & oVect) const;
  double GetOffsetRadius() const;

  double GetUMin() const;
  double GetUMax() const;

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
	// Create the local equations on a given arc
	// (The returned pointers must be deleted by the caller)
	//-------------------------------------------------------------------------
	void CreateLocalEquation(CATLONG32 iArcIndex,
		CATMathFunctionX * & oFx,
		CATMathFunctionX * & oFy,
		CATMathFunctionX * & oFz) const;

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
	CATMathAxis _Axis;
	CATMathVector _Dir;
	double _OffsetRadius, _UMin, _UMax, _RefDir [3];
  CATLONG32 _RefComputed;

  void ComputeRefDirection () const ;
};

#endif
