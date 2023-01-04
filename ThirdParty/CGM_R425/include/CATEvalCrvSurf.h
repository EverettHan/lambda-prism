
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATEvalCrvSurf :
// Evaluate points and derivatives for use in CATGSDOptimizeSurf 
//
//===================================================================
// Usage notes:
//
//===================================================================
// Nov 02   Creation                         D. Johansson
//===================================================================

#ifndef CATEvalCrvSurf_H  
#define CATEvalCrvSurf_H 

#include "CATEvalSurfPtAndDeriv.h"  
#include "CATCurve.h"  
#include "CATGMOperatorsInterfaces.h"
#include <stdlib.h>
#include "CATCGMVirtual.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATKnotVector.h"
#include "CATMath3x3Matrix.h"
#include "CATMathDirection.h"
#include "CATMapParamCrvCrv.h"

class CATInterpolate;

//class ExportedByCATGMOperatorsInterfaces CATEvalCrvSurf : public CATCGMVirtual
class ExportedByCATGMOperatorsInterfaces CATEvalCrvSurf : public CATEvalSurfPtAndDeriv

{    
 public:

/**
 * Object management
 */	
	virtual ~CATEvalCrvSurf ();

/** deprecated
 * 1. Set Frame definition by normal to a plane. V-axis will be // to plane
 */	
	virtual void SetFrameDefI( CATMathDirection &iPlnNormal ){};

/**
 * I:  Set Frame definition by a spine an a normal to a plane. V-axis will be // to plane
 * II: Set MF by an interpolation object
 */	
	virtual void SetFrameDefI( const CATCurve *iSpine, CATMathDirection &iPlnNormal ) = 0 ;
	
	virtual void SetFrameDefII(CATInterpolate *iInterP ) = 0 ;	 

/**
 * Set origin of analyzsis of Profile. The first method creates the analysis data 
 * from the evaluation, at the iSpineParam, of the moving frame.
 * If, and only if the first methot isn't used one of the following must be used! 
 * I:  Common method.
 * II: Method related to "SetFrameDefII(...)". The points are those used in generating
 *     the "iInterP"-object ;
 */	
	virtual void SetProfileAnalysisData( double iSpineParamWhereToAnalyzeProfile ) = 0 ;

	virtual void SetProfileAnalysisDataI(
		CATMathPoint     &iOrigo,
		CATMath3x3Matrix &iONSysem ) = 0 ;

	virtual void SetProfileAnalysisDataII( 
		CATMathPoint   &iOrigo,
		CATMathPoint   &iVdef,
		CATMathPoint   &iWdef ) = 0 ;

/**
 * 1. Guide definition by a reparametrized curve
 */	
	virtual void SetGuidDefI( CATMapParamCrvCrv *iGuide ) = 0 ;

/**
 * Initializes. Returns zero if faliure.
 */
	virtual CATLONG32 Run() = 0 ;

/**
 * ...
 */	
	CATLONG32 GetIfCrossDerivAreEvaluated() { return 1 ; } ;

/**
 * Faster if iU is equal to previous use of Eval(...).
 * Returns zero if spine parametrizatrion is found degenerated.
 */	
	virtual CATLONG32 Eval(double         iU,
		              double         iV,
		              CATMathPoint  &oSurPT,
		              CATMathVector &oDSDU,
		              CATMathVector &oDSDV,
		              CATMathVector &oD2SDUdV ) = 0 ; 
	
/**
 * ... 
 */
	virtual CATKnotVector GetSpineKv() = 0 ;
	virtual CATKnotVector GetProfileKv() = 0 ;

} ;

/**
 * Creator ...
 */
ExportedByCATGMOperatorsInterfaces  
CATEvalCrvSurf * CreateCATEvalCrvSurf( const CATCurve *iProfile ) ;	 

ExportedByCATGMOperatorsInterfaces  
CATEvalCrvSurf * CreateCATEvalCrvSurf(const CATCurve *iSpine, 
									  const CATCurve *iProfile,
									  double iSpineParamWhereToAnalyzeProfile );


#endif  
