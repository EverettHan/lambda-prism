
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATEvalSurfPtAndDeriv :
// Interface to evaluate points and derivatives for use in
// CATGSDOptimizeSurf 
//
//===================================================================
// Usage notes:
//
//===================================================================
// Dec 02   Creation                         D. Johansson
//===================================================================

#ifndef CATEvalSurfPtAndDeriv_H  
#define CATEvalSurfPtAndDeriv_H 

#include "CATGMOperatorsInterfaces.h"
#include <stdlib.h>
#include "CATCGMVirtual.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class ExportedByCATGMOperatorsInterfaces CATEvalSurfPtAndDeriv : public CATCGMVirtual

{    
 public:

/**
 * Object management
 */	

	virtual ~CATEvalSurfPtAndDeriv ();

/**
 * Tells if, or if not,  Eval( ..., CATMathVector &oD2SDUdV ) vill,
 * be used.
 */	
	virtual CATLONG32 GetIfCrossDerivAreEvaluated() = 0 ;

/**
 * Returns zero if any faliure or if not implemented in derived class.
 */	
	virtual CATLONG32 Eval(double         iU,
		              double         iV,
		              CATMathPoint  &oSurPT,
		              CATMathVector &oDSDU,
		              CATMathVector &oDSDV ) { return 0 ; } ; 

	virtual CATLONG32 Eval(double         iU,
		              double         iV,
		              CATMathPoint  &oSurPT,
		              CATMathVector &oDSDU,
		              CATMathVector &oDSDV,
		              CATMathVector &oD2SDUdV ) { return 0 ; } ; 

} ;

#endif  
