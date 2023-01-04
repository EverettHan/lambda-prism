//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================

//=============================================================================
// Note : This operator analyse the connection between two edge curves (and two POEC)
// If there are PCurve (in each edge curve) between the two edge curve with can assure the
// continuity the method GetPCurveContinuity() return TRUE.
//
// Fev. 04  Creation                          EAB
//=============================================================================
#ifndef CATContinuousBySamePCrv_H 
#define CATContinuousBySamePCrv_H

#include "CATCGMOperator.h"
#include "Y30UIUTI.h"
#include "CATCreateContinuousBySamePCrv.h"

class CATSoftwareConfiguration;
class CATSurface;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATString;

class ExportedByY30UIUTI CATContinuousBySamePCrv : public CATCGMOperator
{
public:

  //Constructor And Destructor
  CATContinuousBySamePCrv (CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATEdgeCurve * iECrv1,
                           CATEdgeCurve * iECrv2,
                           CATPointOnEdgeCurve * PointOnECrv1,
                           CATPointOnEdgeCurve * PointOnECrv2);
                          
  ~CATContinuousBySamePCrv();

  //Run Operator
  int RunOperator();

  //Return of the result
  CATBoolean GetPCurveContinuity();

private:

  //internal Data
  CATSoftwareConfiguration  * _Config;
  CATEdgeCurve              * _ECrv1, * _ECrv2;
  CATPointOnEdgeCurve       * _PointECrv1, * _PointECrv2;
  CATBoolean                _RunOK;

  //Output
  CATBoolean _PCurveContinuity;

//========================================================================
// CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
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





