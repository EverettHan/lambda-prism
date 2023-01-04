//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 
//==========================================================================
//
// CATConnectStartInPlane
//
//==========================================================================
//

//
//========================================================================== 
//   /09/02 PKC Creation
// 12/03/20 Q48 Headers etc for math versioning
//========================================================================== 

#ifndef CATConnectStartInPlane_H
#define CATConnectStartInPlane_H

// ExportedBy
#include "Connect.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSurLimits.h"
#include "CATCrvParam.h"
#include "CATMathPoint.h"
#include "CATConnectStartInPlaneBase.h"

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATConnectTool;
class CATSurface;
class CATSoftwareConfiguration;
class CATIPGMConnectTool;

//-----------------------------------------------------------------------------
// 
// CATConnectStartInPlane class specification :
// 
//-----------------------------------------------------------------------------

class ExportedByConnect CATConnectStartInPlane : public CATConnectStartInPlaneBase
{    
  
public:
  /**
  * Constructor. Do not use anymore. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  */
  CATConnectStartInPlane(CATGeoFactory * iFactory,
                         CATSoftwareConfiguration* iConfig,
                         CATPCurve * iPcrv1,
                         const CATCrvParam &iParamOnPcrv1,
                         const CATLONG32 iSupportOrientation1,
                         const CATLONG32 iPCurveOrientation1,
                         CATSurLimits &iLimit1,
                         CATPCurve * iPcrv2,
                         const CATCrvParam &iParamOnPcrv2,								
                         const CATLONG32 iSupportOrientation2,
                         const CATLONG32 iPCurveOrientation2,
                         CATSurLimits &iLimit2,
                         const CATConnectTool * iConnectTool);

  /**
  * Constructor.
  */
  CATConnectStartInPlane(CATGeoFactory * iFactory,
                         CATSoftwareConfiguration* iConfig,
                         CATPCurve * iPcrv1,
                         const CATCrvParam &iParamOnPcrv1,
                         const CATLONG32 iSupportOrientation1,
                         const CATLONG32 iPCurveOrientation1,
                         CATSurLimits &iLimit1,
                         CATPCurve * iPcrv2,
                         const CATCrvParam &iParamOnPcrv2,
                         const CATLONG32 iSupportOrientation2,
                         const CATLONG32 iPCurveOrientation2,
                         CATSurLimits &iLimit2,
                         CATIPGMConnectTool * iIConnectTool);

  /**
  * Destructor.
  */
  ~CATConnectStartInPlane();
		
  /**
  * Runs a CATConnectStartHomotopy operator in <tt>ADVANCED</tt> mode.
  */
  int RunOperator();

  CATBoolean GetPoints(CATMathPoint &ioPointOnEdge,
                 CATMathPoint &ioPointOnSupport11,
                 CATMathPoint &ioPointOnSupport2,
                 CATMathPoint &ioCenterPoint,
                 double &oMaxDistFromEdge); 

  CATBoolean GetPoints(CATSurParam &oPointOnSupport1, CATSurface *& oSupport1,
                 CATSurParam &oPointOnSupport2, CATSurface *& oSupport2);

  CATLONG32 GetDiagnostic();

  const CATConnectTool *GetTool();

  double GetRadius();

  CATCurve* GetCurve();
    
private :
  int ComputeDefaultResult();

// data
  CATPCurve *_PCrv1, *_PCrv2;
  CATLONG32 _SupportOrientation1, _SupportOrientation2, _SupportOrientation3, _PCurveOrientation1, _PCurveOrientation2;
  const CATConnectTool *_Tool;
  CATIPGMConnectTool *_ITool;
  CATSurface *_Surf1, *_Surf2;
  CATSurLimits _Limit1, _Limit2, _Limit3;
  CATCrvParam _ParamOnCrv1,_ParamOnCrv2;
  CATMathPoint _FixedPoint, _CenterPoint, _Point1, _Point2, _Point3;
  double _radius; // rayon au point solution
  double *_Init;
  CATLONG32 _Diagnostic;

  const CATCrvParam *_SpineLow;
  const CATCrvParam *_SpineHigh;
  CATSoftwareConfiguration* _SoftwareConfiguration;

  //-----------------------------------------------------------------------
  // - CGMReplay
  //-----------------------------------------------------------------------
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

private:
  void Init(
    CATSoftwareConfiguration* iConfig,
    CATPCurve * iPcrv1,
    const CATCrvParam &iParamOnPcrv1,
    const CATLONG32 iSupportOrientation1,
    const CATLONG32 iPCurveOrientation1,
    CATSurLimits &iLimit1,
    CATPCurve * iPcrv2,
    const CATCrvParam &iParamOnPcrv2,
    const CATLONG32 iSupportOrientation2,
    const CATLONG32 iPCurveOrientation2,
    CATSurLimits &iLimit2,
    const CATConnectTool * iConnectTool,
    CATIPGMConnectTool * iIConnectTool);

  void DumpTool(CATCGMOutput& os);
  void MyDebug();
};

#endif
