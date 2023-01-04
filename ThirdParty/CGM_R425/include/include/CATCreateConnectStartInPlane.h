//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//==========================================================================
//
// 
//
//========================================================================== 
// June 2016                                                   SMT1
//========================================================================== 

#ifndef CATCreateConnectStartInPlane_h
#define CATCreateConnectStartInPlane_h

#include "CATConnectStartInPlaneBase.h"
#include "CATCrvParam.h"
#include "CATSurLimits.h"
#include "Connect.h"
#include "CATMathPoint.h"

class CATConnectStartInPlane3D;
class CATConnectStartInPlane;
class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATConnectTool;
class CATSurface;
class CATMathPlane;
class CATSoftwareConfiguration;
class CATIPGMConnectTool;
class CATTritangentFilletTool;
class CATVariableFilletTool;
class CATChordalFilletTool;
class CATConstantFilletTool;


//###################### Universal constructor ###############
// Can be used with ConstantFilletTool, ChordalFilletTool and VariableFilletTool and selects the appropriate constructor internally. 
// In an old version it uses CATConnectStartInPlane.h for all, the new version uses CATConstantConnectStartInPlane.h for constant and chordal fillets,
// and CATVariableConnectStartInPlane.h for variable fillets.
ExportedByConnect 
CATConnectStartInPlaneBase * CreateConnectStartInPlane(CATGeoFactory * iFactory,
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

//######################  CATIPGMConnectTool ###############
// Can be used with CATIPGMConnectTool. Currently this only supports CATIPGMConstantFilletTool.h 
ExportedByConnect 
CATConnectStartInPlaneBase * CreateConnectStartInPlane(CATGeoFactory * iFactory,
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

//###################### ConstantFilletTool ###############
// Use for constant edge fillets with PCurves and CrvParam inputs

ExportedByConnect 
CATConnectStartInPlaneBase * CreateConstantConnectStartInPlane(CATGeoFactory * iFactory,
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
                                                     const CATConstantFilletTool * iConnectTool);

//######################  ChordalFilletTool ###############
// Use for chordal edge fillets with PCurves and CrvParam inputs

ExportedByConnect 
CATConnectStartInPlaneBase * CreateChordalConnectStartInPlane(CATGeoFactory * iFactory,
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
                                                     const CATChordalFilletTool * iConnectTool);

//######################  VariableFilletTool ###############
// Use for variable edge fillets with PCurves and CrvParam inputs. The Spine is optional and will be extracted from the tool if not specified.

ExportedByConnect 
CATConnectStartInPlaneBase * CreateVariableConnectStartInPlane(CATGeoFactory * iFactory,
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
                                                     const CATVariableFilletTool * iConnectTool,
                                                     CATCurve * iSpine = NULL);

//######################  ConstantFilletTool 3D ###############
// Use for constant edge fillets with Surface/Surface and CATMathPoint inputs. If the SetLimits method is not used, the current limits of the surfaces will be used. 

ExportedByConnect  
CATConnectStartInPlaneBase * CreateConstantConnectStartInPlane3D(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATSurface * iSupport1,
                                                       const CATLONG32 iSupportOrientation1,
                                                       CATSurface * iSupport2,
                                                       const CATLONG32 iSupportOrientation2,
                                                       CATMathPoint & iFixedPoint,
                                                       const CATConstantFilletTool * iConnectTool);

//######################  ChordalFilletTool 3D ###############
// Use for chordal edge fillets with Surface/Surface and CATMathPoint inputs. If the SetLimits method is not used, the current limits of the surfaces will be used. 

ExportedByConnect  
CATConnectStartInPlaneBase * CreateChordalConnectStartInPlane3D(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATSurface * iSupport1,
                                                       const CATLONG32 iSupportOrientation1,
                                                       CATSurface * iSupport2,
                                                       const CATLONG32 iSupportOrientation2,
                                                       CATMathPoint & iFixedPoint,
                                                       const CATChordalFilletTool * iConnectTool);


//######################  VariableFilletTool 3D ###############
// Use for variable edge fillets with Surface/Surface and CATMathPoint inputs. If the SetLimits method is not used, the current limits of the surfaces will be used. 
//The Spine is optional and will be extracted from the tool if not specified.

ExportedByConnect  
CATConnectStartInPlaneBase * CreateVariableConnectStartInPlane3D(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATSurface * iSupport1,
                                                       const CATLONG32 iSupportOrientation1,
                                                       CATSurface * iSupport2,
                                                       const CATLONG32 iSupportOrientation2,
                                                       CATMathPoint & iFixedPoint,
                                                       const CATVariableFilletTool * iConnectTool,
                                                       CATCurve * iSpine = NULL);


//######################  TritangentFilletTool 3D ###############
// Use for tritangent fillets with Surface/Surface/Surface and CATMathPoint inputs. If the SetLimits method is not used, the current limits of the surfaces will be used. 

ExportedByConnect  
CATConnectStartInPlaneBase * CreateTritangentConnectStartInPlane3D(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATSurface * iSupport1,
                                                       const CATLONG32 iSupportOrientation1,
                                                       CATSurface * iSupport2,
                                                       const CATLONG32 iSupportOrientation2,
                                                       CATSurface * iSupport3,
                                                       const CATLONG32 iSupportOrientation3,
                                                       CATMathPoint & iFixedPoint,
                                                       const CATTritangentFilletTool * iConnectTool);

//######################  TritangentFilletTool 3D ###############
// Use for tritangent fillets with Surface/Surface/Surface and CATMathPoint inputs. The input limits are preferred over current limits 
ExportedByConnect  
CATConnectStartInPlaneBase * CreateTritangentConnectStartInPlane3D(CATGeoFactory * iFactory,
                                                       CATSoftwareConfiguration * iConfig,
                                                       CATSurface * iSupport1,                                                      
                                                       const CATLONG32 iSupportOrientation1,
                                                       CATSurLimits &iLimit1,
                                                       CATSurface * iSupport2,                                                     
                                                       const CATLONG32 iSupportOrientation2,
                                                       CATSurLimits &iLimit2,
                                                       CATSurface * iSupport3,                                                   
                                                       const CATLONG32 iSupportOrientation3,
                                                       CATSurLimits &iLimit3,
                                                       CATMathPoint & iFixedPoint,
                                                       const CATTritangentFilletTool * iConnectTool);


ExportedByConnect  void Remove (CATConnectStartInPlaneBase * iOperator);

#endif
