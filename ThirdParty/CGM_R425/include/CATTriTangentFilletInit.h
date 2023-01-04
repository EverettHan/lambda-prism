//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 
//==========================================================================
//
// CATTriTangentFilletInit : computes the init for the tri tangent fillet
//
//========================================================================== 
// Dec. 98    Documentation                                       F. Bezard
//========================================================================== 


#ifndef CATTriTangentFilletInit_H
#define CATTriTangentFilletInit_H

#include "Connect.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATMathDirection.h"
#include "CATMathPoint.h"
#include "CATCGMVirtual.h"

const CATLONG32 MaxDim = 7;

class CATCurve;
class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATTolerance;

//-----------------------------------------------------------------------------
// 
// CATTriTangentFilletInit class specification :
// 
//-----------------------------------------------------------------------------

class ExportedByConnect CATTriTangentFilletInit  : public CATCGMVirtual
{    
	
public:
	
	//---------------------------------------------------------------	
	//---- Methods for basic manipulations
	//---------------------------------------------------------------
	
	/**
	* Constructor.
	*/
	//Do not use
  CATTriTangentFilletInit(CATGeoFactory * iFactoryPtr,
		 const CATPCurve * iPcrv[4],
		 CATCrvParam iParamOnPcrv[4],
     CATSurLimits iLimits[3],
		 CATLONG32 iOrientation[3]);
  

  CATTriTangentFilletInit(CATGeoFactory * iFactoryPtr,
     CATSoftwareConfiguration * iConfig,
		 const CATPCurve * iPcrv[4],
		 CATCrvParam iParamOnPcrv[4],
     CATSurLimits iLimits[3],
		 CATLONG32 iOrientation[3]);

		
	/**
	* Destructor.
	*/
	~CATTriTangentFilletInit();
		
	/**
	* Runs a CATTriTangentFilletInit operator in <tt>ADVANCED</tt> mode.
	*/
	void Run();
		
	/**
	*  Method GetCurve : Available when Diagnostic=1 
	*  returns the curve solution (circle)
	*/

	CATCurve* GetCurve() const;

  /**
  *  Method GetSurfaceParam : Available when Diagnostic=1 
  *   returns parameters (u,v) of 
	*		point of the profile on surface surf1, surf2 or surf3
  */

	CATSurParam GetSurfaceParam(const CATSurface *) const;
	

  /**
  *  Method GetStartPoint 
	* returns the Init in R7 
  */

	void GetStartPoint(double * oStartPoint) const;
		
	/**
	*  Method GetPointOnSurface : 
	*  returns point of the profile on surface surf1, surf2 or surf3
	*/
	
	CATPointOnSurface* GetPointOnSurface(const CATSurface *) const ;
	
	/**
	*  Method GetRadius : 
	*  returns radius of the profile
	*/
	
	double GetRadius() const ;
  
  /**
	* Method Diagnostic
	* returns 0 if there is no solution
	* returns 1 if there is one exact solution
	*/

	CATLONG32 GetDiagnostic();

  /**
  * Method SetPCurveAndParam
  * Changes the private _Pcrv and _iParamOnCrv
  */

  void SetPCurveAndParam(const CATPCurve * pcrv[4], CATCrvParam param[4]);



private:
	const CATPCurve *_Pcrv[4];
	CATLONG32 _iOrientation[3];
	CATCrvParam _iParamOnCrv[4];
	CATSurParam _iParamOnSur1,_iParamOnSur2, _iParamOnSur3;
  CATSurLimits _limits[3];
	CATMathDirection _N1, _N2, _N3;
	CATMathPoint _P1, _P2, _P3, _C;
  CATSurface *_Surf1, *_Surf2, *_Surf3;
	CATGeoFactory *_Factory;
	double _Init[MaxDim];
  double _radius;
	CATLONG32 _Diagnostic;
  CATSoftwareConfiguration * _Config;
  const CATTolerance & _TolObject;
};

//-----------------------------------------------------------------------------
// 
// Public construction and destruction 
//
//-----------------------------------------------------------------------------

/**
* Creates an operator .
*/

ExportedByConnect  
CATTriTangentFilletInit * CreateConnectTriTangent (CATGeoFactory * iFactoryPtr,
                                                   const CATPCurve * iPcrv[4],
                                                   const CATCrvParam iParamOnPcrv[4],
                                                   CATSurLimits iLimits[3],
                                                   const CATLONG32 iOrientation[3], 
                                                   const CATSkillValue iMode);

/**
*  Remove
*/

ExportedByConnect  void Remove (CATTriTangentFilletInit *iConnectPtr);



#endif
