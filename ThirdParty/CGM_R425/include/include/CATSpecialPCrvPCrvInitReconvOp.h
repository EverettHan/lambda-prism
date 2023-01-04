// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CATSpecialPCrvPCrvInitReconvOp:
//   Dedicated to ribbon hermetization between connect surfaces sharing a common
//   support.
//   This simple operator is similar to PCurve/PCurve intersection with the 
//   differences that it is dedicated to tangent and nearly tangent configurations,
//   it requires inits on the PCurves, a single point solution is always returned
//   (no tolerance, no confusion area, no multiple solutions) and stability is
//   emphasized possibly at the expense of accuracy.
//=============================================================================
//   /04/03     Creation                                                    S. Dauby
//   /06/13 R1Y Added _UseRestrictedProjectionDomain and access functions
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATSpecialPCrvPCrvInitReconvOp_h
#define CATSpecialPCrvPCrvInitReconvOp_h

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCrvLimits.h"
#include "CATCrvParam.h"
#include "CATMathPoint.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvParam;

class ExportedByY30C3XGG CATSpecialPCrvPCrvInitReconvOp : public CATGeoOperator
{
public:
  CATSpecialPCrvPCrvInitReconvOp
    (CATGeoFactory * Factory,
     CATSoftwareConfiguration * Config,
     CATPCurve * PC0, 
     CATPCurve * PC1,
     const CATCrvLimits & Lim0,
     const CATCrvLimits & Lim1,
     const CATCrvParam & init0,
     const CATCrvParam & init1);

  ~CATSpecialPCrvPCrvInitReconvOp();

  // 0 = ok
  // 1 = failed
  CATLONG32 GetResult(CATCrvParam & reconv0, CATCrvParam & reconv1);

  int RunOperator();

  virtual void SetUseRestrictedProjectionDomain(const CATBoolean iUseRestrictedProjectionDomain);
  virtual CATBoolean GetUseRestrictedProjectionDomain() const;

  // internal use only - no client may call
  void ForceSingular();

private:

  CATLONG32 Projection();
  CATLONG32 Singular();
  CATLONG32 Regular();
  
  // input
  CATSoftwareConfiguration * _Config;
  CATPCurve * _PCrv[2];
  CATCrvLimits _PCrvLim[2];
  CATCrvParam _Init[2];
  CATBoolean _UseRestrictedProjectionDomain;
  CATBoolean _ForceSingular;

  // output  
  CATLONG32 _result;
  CATCrvParam _Reconv[2];

  // other
  CATCrvParam _Proj[2];
  CATMathPoint _Init3D[2];
  CATMathPoint _Proj3D[2];
  double _d[2];

  // CGMReplay integration
protected:
  friend class CATGeoStreamFactory; 
  static CATString _OperatorId;

public:
	const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & Str);
  virtual void WriteOutput(CATCGMStream & Str);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif
