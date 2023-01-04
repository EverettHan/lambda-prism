//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATOffsetPCurve
//  Base class for offseting a PCurve on a target offset surface with management
//  of non isoparametric offsets 
//
//=============================================================================
//   /06/05 CQI Creation
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATOffsetPCurve_H
#define CATOffsetPCurve_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

// GeometricObjects libraries
#include "CATCrvParam.h"
#include "CATCrvLimits.h"
#include "CATCGMVirtual.h"

// Other libraries
#include "CATMathDef.h"

class CATGeoFactory;
class CATPCurve;
class CATSurface;
class CATSoftwareConfiguration;
class CATMathTransformation1D;
class CATMathTransformation2D;

class ExportedByY30C3XGG CATOffsetPCurve  : public CATGeoOperator
{

 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATOffsetPCurve(CATGeoFactory * iFactory,
                  CATSoftwareConfiguration * iConfig,
                  CATPCurve * iPCurve,
                  const CATCrvLimits & iLimits,
                  CATSurface * iTargetOffsetSupport);
  
  ~CATOffsetPCurve();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  int RunOperator();

  // Returns the offseted PCurve that has been computed
  CATPCurve * GetResult();

  // Manages the report from input PCurve(iParam) ---> Offset PCurve(oParamOffset)
  void Report(const CATCrvParam & iParam, CATCrvParam & oParamOffset);

  // Retrieves the parametric orientation of 'Offset PCurve' with regards to the 
  // orientation of 'input PCurve'.
  // Conventions:
  //      +1 if 'Offset PCurve' has the same orientation as 'input PCurve'
  //      -1 if 'Offset PCurve' and 'input PCurve' have opposite orientations
  short GetRelativeOrientation();

  // Fills coefficients of oTransfoUV if UV non-isoparametric offset has been detected
  // It does nothing if offsets are isoparametric
  CATBoolean GetLinearTransfoUV(CATMathTransformation2D & oTransfoUV);

  // Fills coefficients of oTransfoW if offseted PCurve is W non-isoparametric
  // It does nothing if PCurves are isoparametric
  CATBoolean GetLinearTransfoW(CATMathTransformation1D & oTransfoW);

  // Returns TRUE if non-isoparametric UV offset has been detected,
  // FALSE otherwise
  CATBoolean IsIsoParametricUV();

  // Returns TRUE if offseted PCurve is W non-isoparametric,
  // FALSE otherwise
  CATBoolean IsIsoParametricW();

 protected:
   //-----------------------------------------------------------------------
   //- Protected methods
   //-----------------------------------------------------------------------
   CATBoolean Initialize();
   CATBoolean ComputeUVTransfo();
   CATBoolean OffsetPCurve();
   
   //-----------------------------------------------------------------------
   //- Data
   //-----------------------------------------------------------------------
   
   CATGeoFactory            * _Factory;
   CATSoftwareConfiguration * _Config;
   
   // Input PCurve
   CATPCurve          * _PCrv;  
   CATCrvLimits         _UseLimits;
   CATSurface         * _InputSupport;
   // Offset PCurve on target surface
   CATPCurve          * _PCrvOffset;
   CATSurface         * _TargetSupport;
   
   // Linear UV-transformation for non-isoparametric offset
   CATMathTransformation2D * _LinearTransfoUV;

   // Linear W-transformation between input PCurve and target PCurve
   CATMathTransformation1D * _LinearTransfoW;
   
   // Tolerance requested by CloneAndMovePCurve operator
   double _Tol;
   
   // Run diagnostic
   CATBoolean _RunDiag;

  // CGMReplay integration
protected:
  friend class CATGeoStreamFactory; 
  static CATString _OperatorId;

public:
	const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};


#endif

