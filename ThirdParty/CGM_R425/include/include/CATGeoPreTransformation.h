/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATGeoPreTransformation :
//
//=============================================================================
// Usage notes:
// 29/01/04 EAB Versionning
// 12/03/20 Q48 Added GetSoftwareConfiguration for math versioning
//=============================================================================

#ifndef CATGeoPreTransformation_H
#define CATGeoPreTransformation_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathTransformation2D.h"
#include "CATPCurve.h"
#include "CATCrvLimits.h"

class CATGeoFactory;
class CATSurface;
class CATMathNonLinearTransformation;
class CATSoftwareConfiguration;


class ExportedByY30UIUTI CATGeoPreTransformation : public CATGeoOperator {
public :
	//
	//-----------------------------------------------------------------------
	//- Constructor-destructor
	//-----------------------------------------------------------------------
	//
  CATGeoPreTransformation (CATGeoFactory                  * iFactory,
                           CATSoftwareConfiguration       * iConfig,
                           CATSurface                     * iSurfaceToTransform,
                           int                              iNbPCurves,
                           CATPCurve                      * iListOfPCurves[],
                           CATCrvLimits                     iListOfCrvLimits[],
                           CATMathNonLinearTransformation * iTransfo);
  
  //Do not use
  CATGeoPreTransformation (CATGeoFactory                  * iFactory,
                           CATSurface                     * iSurfaceToTransform,
                           int                              iNbPCurves,
                           CATPCurve                      * iListOfPCurves[],
                           CATCrvLimits                     iListOfCrvLimits[],
                           CATMathNonLinearTransformation * iTransfo);
	
	~CATGeoPreTransformation();

	//
	// Launches the operator 
	//
	int RunOperator ();
	//
	// Returns the CATProcSurface Created by the operator
	//
	CATSurface * GetSurface  ();
	//
	// Returns the CATMathTransformation2D between
	// input surface and output surface
	//
	void GetMathTransformation2D(CATMathTransformation2D & oTransfo);
	
	//========================================================================
	// Gestion CGMReplay
	//========================================================================
	
	const CATString * GetOperatorId();
	//-----------------------------------------------------------------------
	//- Gestion timer 
	//-----------------------------------------------------------------------  
	CATGeoOpTimer * GetTimer();
	
	//-----------------------------------------------------------------------
	//- Gestion Mode Record 
	//-----------------------------------------------------------------------  
	
	CATExtCGMReplay *IsRecordable(short & oLevelOfRuntime, short &oVersionOfStream);
	virtual void WriteInput(CATCGMStream  & ioStream);
	virtual void WriteOutput(CATCGMStream & ioStream);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
	virtual void Dump( CATCGMOutput& os ) ;
	virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
	virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & ioStream);
	virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & ioStream);
	
	
protected:
	friend class CATGeoStreamFactory;
	
	
	// protected static data
	static CATString _OperatorId;
	static CATGeoOpTimer _Timer;
	
	
private :
	//
	//-----------------------------------------------------------------------
	//- Private data
	//-----------------------------------------------------------------------
	//
	CATSurface *_SurfaceIn, *_SurfaceOut;
	CATMathTransformation2D _Transfo2D;
	CATPCurve ** _ListPCurves;
	CATCrvLimits * _ListOfCrvLimits;
	int _NbPCurves;
  CATSoftwareConfiguration * _Config;
	
};
//
// Create and remove 
//
ExportedByY30UIUTI CATGeoPreTransformation * CreateGeoPreTransformation (CATGeoFactory * iFactory,
                                                                         CATSurface * iSurfaceToTransform,
                                                                         int iNbPCurves,
                                                                         CATPCurve * iListOfPCurves[],
                                                                         CATCrvLimits iListOfCrvLimits[],
                                                                         CATMathNonLinearTransformation * iTransfo,
                                                                         CATSkillValue iMode=BASIC);

ExportedByY30UIUTI void Remove (CATGeoPreTransformation * iOper);

#endif







