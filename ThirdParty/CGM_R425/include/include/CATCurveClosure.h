//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Usage notes:
//  This operator is used to get the closure information of a curve on given
//  CrvLimits.
//=============================================================================
#ifndef CATCurveClosure_H
#define CATCurveClosure_H

#include "Y30A3HGG.h"

#include "CATCGMOperator.h"


#include "CATCrvLimits.h"

class CATGeoFactory;
class CATCurve;
class CATSoftwareConfiguration;

class ExportedByY30A3HGG CATCurveClosure : public CATCGMOperator
{
public:
	//-----------------------------------------------------------------------
	//- Object management
	//-----------------------------------------------------------------------
	
	CATCurveClosure (CATGeoFactory *iFactory, CATCurve  *iCurve, CATCrvLimits & iLimits);
  CATCurveClosure (CATGeoFactory *iFactory, 
    CATSoftwareConfiguration * iConfig,CATCurve  *iCurve, CATCrvLimits & iLimits);
	~CATCurveClosure ();
	
	//-----------------------------------------------------------------------
	//- Settings methods
	//-----------------------------------------------------------------------
	
	void SetLimits(const CATCrvLimits & iLimits);
	
	//-----------------------------------------------------------------------
	//- Get methods
	//-----------------------------------------------------------------------
	
	CATLONG32 IsClosedG0();
	CATLONG32 IsClosedG1();
	CATLONG32 IsClosedG2();
	
	//-----------------------------------------------------------------------
	//- Running the operator
	//-----------------------------------------------------------------------
	
	
	int Run();
	
protected:
	CATLONG32 ComputeG1Closure();
	CATLONG32 ComputeG2Closure();
	
protected:
  CATSoftwareConfiguration * _Config;
	CATCurve * _Curve;
	CATCrvLimits _CrvLimits;
	
	CATLONG32 _IsClosedG0, _IsClosedG1, _IsClosedG2; // =-1 if not evaluated
};

#endif
