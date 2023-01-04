// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//===================================================================
//
// CATCrvLength
// Class for operator of 3d curvilign length on curves
//
//===================================================================

//===================================================================
// Feb. 97    Creation                         X. Gourdon
// Oct. 04 Versionning Interne - EAB
// 08/07/08 NLD Suppression valeur par defaut de l'argument tol
//              Suppression des constructeurs sans configuration
// 12/03/20 Q48 Headers etc for math versioning
//===================================================================
//===================================================================

#ifndef CATCrvLength_H
#define CATCrvLength_H

// ExportedBy
#include "Y30A3HGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCrvParam.h"
#include "CATPointOnCurve.h"
#include "CATMathDef.h"
#include "CATMathLimits.h"
#include "CATSoftwareConfiguration.h"
#include "CATCreateCrvLength.h"
#include "CATGeoFactory.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
//BigScale Mod. #SKA
#include "CATTolerance.h"

class CATCurve;

//#define CATGAP

class ExportedByY30A3HGG CATCrvLength : public CATGeoOperator
{
 private:
  double _length;
#ifdef CATGAP
  int _discont; // take discontinuities into account ?
#endif
  double _tolerance;  
  CATCrvParam _start, _end; 
  const CATCurve * _crv;
  CATSoftwareConfiguration * _Config;

 public:
//
//- Constructors
//
	CATCrvLength(CATSoftwareConfiguration * iConfig,
               const CATPointOnCurve *point1, 
               const CATPointOnCurve *point2,
               const double tol
               //const double tol=CATEpsg);
               //const double tol=CATGetDefaultTolerance().EpsgForLengthTest() //@BigScaleError(Use Scaled Value)
               );

  CATCrvLength(CATSoftwareConfiguration * iConfig,
               const CATCurve * crv,
               const CATCrvParam & param1, const CATCrvParam & param2,
               const double tol
               //const double tol=CATGetDefaultTolerance().EpsgForLengthTest());//@BigScaleError(Use Scaled Value)
              );
/*
	// do not use
	CATCrvLength(const CATPointOnCurve *point1, 
               const CATPointOnCurve *point2, 
               const double tol=CATGetDefaultTolerance().EpsgForLengthTest());//@BigScaleError(Use Scaled Value)

	// do not use
  CATCrvLength(const CATCurve * crv,
               const CATCrvParam & param1, const CATCrvParam & param2,
               const double tol=CATGetDefaultTolerance().EpsgForLengthTest());//@BigScaleError(Use Scaled Value)
*/  
  ~CATCrvLength();

//
//- Methods
//
#ifdef CATGAP
  void SetDiscontinuity();
  void UnsetDiscontinuity();
  CATBoolean IsDiscontinuity();  
#endif
  CATLength GetLength();
  int RunOperator();  

//========================================================================
// CGMReplay Implementation - VSJ Creation
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  virtual const CATString * GetOperatorId();
  virtual CATGeoOpTimer * GetTimer();
  virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  virtual void WriteInput(CATCGMStream  & Str);
	virtual void Dump( CATCGMOutput& os ) ;
  virtual void WriteOutput(CATCGMStream & Str);
	virtual void DumpOutput(CATCGMOutput & os) ;
	virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
	virtual CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif
