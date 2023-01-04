// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// 
//
//=============================================================================
// Usage notes:
//  This operator is used to check the internal validity of a surface on a given SurLimits:
//  
//=============================================================================
#ifndef CATCheckNLTSurface_H
#define CATCheckNLTSurface_H

#include "Y30UIUTI.h"

#include "CATCGMOperator.h"

#include "CATSurLimits.h"
#include "CATMathDef.h"

class CATGeoFactory;
class CATSurface;
class CATPlane;
class CATError;
class CATCGMOutput;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATCheckNLTSurface  : public CATCGMOperator
{
public:
	//-----------------------------------------------------------------------
	//- Object management
	//-----------------------------------------------------------------------
	CATCheckNLTSurface  (CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig,
		CATSurface  *iSurface);
  ~CATCheckNLTSurface();
	
	//-----------------------------------------------------------------------
	//- Settings methods
	//-----------------------------------------------------------------------
	
	void SetLimits(const CATSurLimits & iLimits);
	
	//-----------------------------------------------------------------------
	//- Get methods

	
	int CheckCutRipPlane();
 //   int CheckRegularNeighboorHood();
	//-----------------------------------------------------------------------
	//- For internal use only : Write in the console the detected errors when
	//  encountered during the Run()
	//-----------------------------------------------------------------------
	void SetConsoleOutput();
	void SetOutput(CATCGMOutput & os);
	
	//-----------------------------------------------------------------------
	// Perform more check. Warning : this mode is expensive
	//-----------------------------------------------------------------------
	void SetAdvancedMode();
    //-----------------------------------------------------------------------
    //Get les elements de la deformation
    //-----------------------------------------------------------------------
  //  int GetTheDeformation();
  //  CATPlane * GetTheRipPlane();

    void CreateTransfoElements();
	
protected:
	void Initialize();
	
	
	CATSurLimits _Limits;
	CATSurface * _Surface;
	
	CATBoolean _SurfaceKO;
	CATBoolean _IsContainingAxis;
    CATBoolean _CheckNeighboorhood ;
	// - Internal data 
	CATBoolean _CGMOutput;
	CATCGMOutput *_os;
	
	// - Advanced mode
	CATBoolean _AdvancedMode;

  CATSoftwareConfiguration * _Config;
};

#endif
