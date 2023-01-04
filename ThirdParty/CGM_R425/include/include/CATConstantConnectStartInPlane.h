//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//==========================================================================
//
// 
//
//========================================================================== 
// June 2016                                                   SMT1
//========================================================================== 

#ifndef CATConstantConnectStartInPlane_H
#define CATConstantConnectStartInPlane_H

#include "Connect.h"

#include "CATSurLimits.h"
#include "CATCrvParam.h"
#include "CATMathPoint.h"
#include "CATGeoOperator.h"
#include "CATConnectStartInPlane3D.h"

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATConnectTool;
class CATSurface;
class CATSoftwareConfiguration;
class CATIPGMConnectTool;

class ExportedByConnect  CATConstantConnectStartInPlane : public CATConnectStartInPlane3D
{ 
public:

  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATConstantConnectStartInPlane(CATGeoFactory * iFactory,
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

  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATConstantConnectStartInPlane(CATGeoFactory * iFactory,
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

  ~CATConstantConnectStartInPlane();

  CATBoolean GetPoints(CATMathPoint &ioPointOnEdge,
                 CATMathPoint &ioPointOnSupport11,
                 CATMathPoint &ioPointOnSupport2,
                 CATMathPoint &ioCenterPoint,
                 double &oMaxDistFromEdge); 

  CATBoolean GetPoints(CATSurParam &oPointOnSupport1, CATSurface *& oSupport1,
                 CATSurParam &oPointOnSupport2, CATSurface *& oSupport2);

  const CATString * GetOperatorId();

protected:
  static CATString _OperatorId;

  CATPCurve *_PCrv1, *_PCrv2;
  CATLONG32  _PCurveOrientation1, _PCurveOrientation2;
  CATIPGMConnectTool *_ITool;
  CATCrvParam _ParamOnCrv1,_ParamOnCrv2;
  CATMathPoint _CenterPoint, _Point1, _Point2;
  
  void ConstantInit( CATPCurve * iPcrv1,
                     const CATCrvParam &iParamOnPcrv1,
                     const CATLONG32 iPCurveOrientation1,
                     CATSurLimits &iLimit1,
                     CATPCurve * iPcrv2,
                     const CATCrvParam &iParamOnPcrv2,
                     const CATLONG32 iPCurveOrientation2,
                     CATSurLimits &iLimit2,
                     const CATConnectTool * iConnectTool,
                     CATIPGMConnectTool * iIConnectTool);

  int ComputeDefaultResult();
  CATBoolean SelectSolution(CATMathSetOfPointsND &iSolutionPoints);

};


#endif

