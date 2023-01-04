#ifndef CATIPGMGeometricOpeItfBldr2_h
#define CATIPGMGeometricOpeItfBldr2_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATCGMMathNurbsDimension.h"
#include "CATMathConstant.h"
#include "CATIPGMSurTo2DGlobalPlanarMapping.h"
#include "CATCrvSide.h"
#include "CATExtrapolSurfaceSide.h"
#include "CATIntersectionPCrvPCrvSign.h"
#include "CATGeometryType.h"
#include "CATPGMSurfaceCurvatureFunction.h"
#include "CATIsoParameter.h"
#include "CATDistanceType.h"
#include "CATExtrapolVectFormEnum.h"

class CATMathGridOfPoints;
class CATKnotVector;
class CATMathSetOfPoints;
class CATIPGMConvertCurveToCanonic;
class CATGeoFactory;
class CATCurve;
class CATCrvParam;
class CATSurface;
class CATEdgeCurve;
class CATCrvLimits;
class CATPointOnEdgeCurve;
class CATICGMConfusionPtOnCrvPtOnCrv;
class CATSoftwareConfiguration;
class CATPointOnCurve;
class CATIPGMConfusionPtOnCrvPtOnCrv;
class CATICGMConfusionPtOnSurPtOnSur;
class CATSurParam;
class CATPointOnSurface;
class CATIPGMConfusionPtOnSurPtOnSur;
class CATICGMConvertCurveToCanonic;
class CATICGMDistanceMinCrvCrv;
class CATIPGMDistanceMinCrvCrv;
class CATICGMDistanceMinPtCrv;
class CATIPGMDistanceMinPtCrv;
class CATMathPoint;
class CATMathNurbsMultiForm;
class CATPoint;
class CATICGMMathNurbsCurveTools;
class CATICGMMathNurbsSurfaceTools;
class CATICGMNurbsCurveTools;
class CATIPGMNurbsCurveTools;
class CATIPGMNurbsSurfaceTools;
class CATCGMStream;
class CATICGMDistanceMinPtSur;
class CATIPGMDistanceMinPtSur;
class CATICGMEdgeCurveComputation;
class CATIPGMEdgeCurveComputation;
class CATICGMInclusionPtCrv;
class CATIPGMInclusionPtCrv;
class CATICGMInclusionPtSur;
class CATIPGMInclusionPtSur;
class CATICGMIntersectionCrvCrv;
class CATIPGMIntersectionTriSur;
class CATICGMIntersectionSurSur;
class CATICGMIntersectionCrvSur;
class CATIPGMIntersectionSurSur;
class CATPlane;
class CATIPGMIntersectionCrvSur;
class CATIPGMIntersectionCrvCrv;
class CATICGMProjectionCrvSur;
class CATSurLimits;
class CATMathDirection;
class CATICGMProjectionPtSur;
class CATICGMProjectionPtCrv;
class CATIPGMListOfProjectionCrvSur;
class CATIPGMProjectionCrvSur;
class CATIPGMProjectionPtSur;
class CATIPGMProjectionPtCrv;
class CATICGMNurbsSurfaceTools;
class CATICGMReflectCurve;
class CATIPGMReflectCurve;
class CATMathAxis;
class CATICGMCurveCurvilinearParameterization;
class CATIPGMCurveCurvilinearParameterization;
class CATIPGMParallelConnectTool;
class CATLaw;
class CATICGMDistanceTool;
class CATMathSetOfPointsND;
class CATApproxFunctionXByPiecewisePol;
class CATMathFunctionX;
class CATMathInterval;
class CATIPGMAutoIntersectionPCrv;
class CATPCurve;
class CATPGMBreakPCurveImport;
class CATSurfaceImport;
class CATFrFNurbsMultiForm;
class CATIPGMChamferTool;
class CATCloneAndMovePCurve;
class CATIPGMCombiViewPCrv;
class CATGeometry;
class CATIPGMConnect;
class CATIPGMConnectTool;
class CATIPGMConstantFilletTool;
class CATIPGMCurveToCanonic;
class CATIPGMDesextrapolator;
class CATIPGMDeviationLnCrv;
class CATMathLine;
class CATPGMEdgeCurveQuality;
class CATIPGMExtrapolCurve;
class CATIPGMExtrapolSurface;
class CATIPGMIntersectionPCrvPCrv;
class CATPGMLawUtilities;
class CATIPGMMaxCurveCurvature;
class CATIPGMMaxOffset;
class CATIPGMNurbsQuality;
class CATFrFNurbsBipar;
class CATMathFunctionXY;
class CATIPGMOffsetOperator;
class CATIPGMOrientationLoop;
class CATIPGMPConicsComputation;
class CATIPGMPositionPtLoop;
class CATMathVector;
class CATQuinticInterpolation;
class CATIPGMReflectionLineInterpol;
class CATMathImplicitSystem;
class CATMathIntervalND;
class CATIPGMRollLinesComputation;
class CATIPGMSetOfPointsToCanonic;
class CATIPGMMassProperties1D;
class CATLISTP(CATSurParam);
class CATLISTP(CATCurve);
class CATLISTP(CATSurface);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGeometricOpeItfBldr2;

/**
 * Factory of implementations of CGM interfaces for the framework GeometricOperators.
 */
class ExportedByCATGMModelInterfaces CATIPGMGeometricOpeItfBldr2: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATIPGMAutoIntersectionPCrv *CATPGMCreateAutoIntersectionPCrv(
    CATGeoFactory *iFactory,
    CATPCurve *iPCrv,
    CATCrvLimits &iCrvLimits) = 0;

  virtual CATIPGMAutoIntersectionPCrv *CATPGMCreateAutoIntersectionPCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCrv,
    CATCrvLimits &iCrvLimits) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATPCurve *initialPCurve,
    CATSurfaceImport *surfaceImport) = 0;

  virtual CATIPGMChamferTool *CATPGMCreateChamferTool(
    CATSoftwareConfiguration *iConfig,
    const double iValue1,
    const double iValue2,
    const CATLONG32 iCATChamferToolType) = 0;

  virtual CATIPGMChamferTool *CATPGMCreateChamferTool(
    CATSoftwareConfiguration *iConfig,
    const double idist1,
    const double idist2,
    CATCurve *iSpine) = 0;

  virtual CATIPGMChamferTool *CATPGMCreateChamferTool(
    const double iValue1,
    const double iValue2,
    const CATLONG32 iCATChamferToolType) = 0;

  virtual CATIPGMChamferTool *CATPGMCreateChamferTool(
    const double idist1,
    const double idist2,
    CATCurve *iSpine) = 0;

  virtual CATCloneAndMovePCurve *CATCGMPrivCreateCloneAndMovePCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPCurve *iPCurve,
    const CATCrvLimits &iLimits,
    CATSurface *iNewSupport,
    double iTolerance) = 0;

  virtual CATCloneAndMovePCurve *CATCGMPrivCreateCloneAndMovePCurve(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPCurve *iPCurve,
    const CATCrvLimits &iLimits,
    CATSurface *iNewSupport,
    double iTolerance) = 0;

  virtual CATIPGMCombiViewPCrv *CATPGMCreateCombiViewPCrv(
    CATGeoFactory *iFactory,
    CATGeometry *iGeometry1,
    CATGeometry *iGeometry2,
    CATPlane *iSupport1,
    CATPlane *iSupport2,
    CATPlane *iResultSupport,
    CATSkillValue iMode) = 0;

  virtual void CATPGMMapOnECrv(
    CATMathSetOfPointsND *ioParamMap,
    const CATCurve *iPCrv1,
    const CATEdgeCurve *iECrv1,
    const CATCurve *iPCrv2,
    const CATEdgeCurve *iECrv2) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve1,
    CATPCurve *iInPCurve1,
    const short iInSurfOrientation1,
    const short iInPCurveSide1,
    CATPCurve *iOutPCurve1,
    const short iOutSurfOrientation1,
    const short iOutPCurveSide1,
    const CATBoolean iFirstIsCovered1,
    CATEdgeCurve *iEdgeCurve2,
    CATPCurve *iInPCurve2,
    const short iInSurfOrientation2,
    const short iInPCurveSide2,
    CATPCurve *iOutPCurve2,
    const short iOutSurfOrientation2,
    const short iOutPCurveSide2,
    const CATBoolean iFirstIsCovered2,
    CATSurface *iParting,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iHoldCurve,
    const CATLONG32 iHCOrientation,
    CATSurface *iSurface,
    const CATLONG32 iSurfaceOrientation,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve1,
    CATPCurve *iInPCurve1,
    const CATLONG32 iInSurfOrientation1,
    const CATLONG32 iInPCurveSide1,
    CATPCurve *iOutPCurve1,
    const CATLONG32 iOutSurfOrientation1,
    const CATLONG32 iOutPCurveSide1,
    const CATBoolean iFirstIsCovered1,
    CATEdgeCurve *iEdgeCurve2,
    CATPCurve *iInPCurve2,
    const CATLONG32 iInSurfOrientation2,
    const CATLONG32 iInPCurveSide2,
    CATPCurve *iOutPCurve2,
    const CATLONG32 iOutSurfOrientation2,
    const CATLONG32 iOutPCurveSide2,
    const CATBoolean iFirstIsCovered2,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve1,
    CATPCurve *iInPCurve1,
    const CATLONG32 iInSurfOrientation1,
    const CATLONG32 iInPCurveSide1,
    CATPCurve *iOutPCurve1,
    const CATLONG32 iOutSurfOrientation1,
    const CATLONG32 iOutPCurveSide1,
    CATEdgeCurve *iEdgeCurve2,
    CATPCurve *iInPCurve2,
    const CATLONG32 iInSurfOrientation2,
    const CATLONG32 iInPCurveSide2,
    CATPCurve *iOutPCurve2,
    const CATLONG32 iOutSurfOrientation2,
    const CATLONG32 iOutPCurveSide2,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    const CATLONG32 iSurfaceOrientation1,
    CATSurface *iSurface2,
    const CATLONG32 iSurfaceOrientation2,
    CATCurve *iSpine,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATLONG32 iSurfaceOrientation,
    CATCurve *iGuide,
    CATCurve *iSpine,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    CATCurve *iGuide,
    CATCurve *iSpine,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iPCurveStart,
    const CATLONG32 iSurfaceStartOrientation,
    const CATLONG32 iPCurveStartSide,
    CATPCurve *iPCurveEnd,
    const CATLONG32 iSurfaceEndOrientation,
    const CATLONG32 iPCurveEndSide,
    const CATBoolean iFirstIsCovered,
    CATSurface *iSurface,
    const CATLONG32 iSurfaceOrientation,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iPCurveStart,
    const CATLONG32 iSurfaceStartOrientation,
    const CATLONG32 iPCurveStartSide,
    CATPCurve *iPCurveEnd,
    const CATLONG32 iSurfaceEndOrientation,
    const CATLONG32 iPCurveEndSide,
    CATSurface *iSurface,
    const CATLONG32 iSurfaceOrientation,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iPCurveStart,
    const CATLONG32 iOrientationStart,
    CATPCurve *iPCurveEnd,
    const CATLONG32 iOrientationEnd,
    CATSurface *iSurface,
    const CATLONG32 iSurfaceOrientation,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATPoint *iPoint,
    CATSurface *iSurface,
    const CATLONG32 iOrientationSurface,
    CATIPGMConnectTool *iProfile,
    CATLISTP(CATSurface) &iSurfList,
    CATLISTP(CATSurParam) &iSurParamList,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATPoint *iPointPtr,
    CATSurface *iSurfacePtr,
    const CATLONG32 iOrientationSurface,
    CATIPGMConnectTool *iProfilePtr,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurvePtr,
    const CATLONG32 iOrientationCurve,
    CATSurface *iSurfacePtr,
    const CATLONG32 iOrientationSurface,
    CATIPGMConnectTool *iProfilePtr,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSupport1,
    CATSurface *iSupport2,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iFactoryPtr,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1Ptr,
    CATSurface *iSurface2Ptr,
    CATSurface *iSurface3Ptr,
    CATIPGMConnectTool *iProfilePtr,
    const CATLONG32 iOrientation1,
    const CATLONG32 iOrientation2,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    const CATLONG32 iOrientation1,
    CATSurface *iSurface2,
    const CATLONG32 iOrientation2,
    CATSurface *iSurface3,
    const CATLONG32 iOrientation3,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    const CATLONG32 iOrientation1,
    CATSurface *iSurface2,
    const CATLONG32 iOrientation2,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConstantFilletTool *CATPGMCreateConstantFilletTool(
    CATSoftwareConfiguration *iConfig,
    const double iRadius) = 0;

  virtual CATIPGMConstantFilletTool *CATPGMCreateConstantFilletTool(const double iRadius) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    const CATLONG32 iNbCrv,
    CATCurve **iTabCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATCrvLimits &iLimits,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATEdgeCurve *iEdgeCurve,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATCrvLimits &iLimits,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATCurve *iCurveToCanonic,
    CATCrvLimits &iLimits,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATEdgeCurve *iEdgeCurveToCanonic,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATSurLimits *iSurLimits,
    CATBoolean iDuplicate,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    const CATCrvLimits *iCrvLimits,
    CATBoolean iDuplicate,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    const CATSurLimits *iSurLimits,
    CATBoolean iDuplicate,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    const CATCrvLimits *iCrvLimits,
    CATBoolean iDuplicate,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDeviationLnCrv *CATPGMCreateDeviationLnCrv(
    CATGeoFactory *iWhere,
    const CATMathLine &iLine,
    CATCurve *iCurve,
    CATSkillValue iMode) = 0;

  virtual CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
    CATGeoFactory *iFactory,
    CATEdgeCurve *iEdgeCurve,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATLONG32 iNbCrv,
    CATCurve **iTabCrv) = 0;

  virtual CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
    CATGeoFactory *iFactory,
    CATEdgeCurve *iEdgeCurve,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATCurve *iCrv1,
    const CATCurve *iCrv2) = 0;

  virtual CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATLONG32 iNbCrv,
    CATCurve **iTabCrv) = 0;

  virtual CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATCurve *iCrv1,
    const CATCurve *iCrv2) = 0;

  virtual CATIPGMExtrapolCurve *CATPGMCreateExtrapolCurve(
    CATGeoFactory *iFactory,
    CATCurve *iCurveToExtrapolate,
    CATCrvParam &iStart,
    const double iLengthEstimation,
    const short iExtrapolDirection,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMExtrapolCurve *CATPGMCreateExtrapolation(
    CATGeoFactory *iFactory,
    CATCurve *iCurveToExtrapolate,
    const CATCrvParam &iStart,
    const double iLengthEstimation,
    CATSkillValue iMode,
    const short iExtrapolDirection,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMExtrapolCurve *CATPGMCreateExtrapolation(
    CATGeoFactory *iFactory,
    CATCurve *iCurveToExtrapolate,
    CATCrvParam &iStart,
    const double iLengthEstimation,
    CATCrvSide iExtrapolDirection,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMExtrapolSurface *CATPGMCreateExtrapolation(
    CATGeoFactory *iFactory,
    CATSurface *iSurfaceToExtrapolate,
    CATSurParam *iStart,
    CATExtrapolSurfaceSide iSurfaceSide,
    const CATMathVector2D &iVectorEstimation,
    short iAllowSurfaceCreation,
    CATSkillValue iMode,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    const CATEdgeCurve *iECrv1,
    const CATPCurve *Pcurve1,
    const CATCrvLimits &Limit1,
    const CATEdgeCurve *iECrv2,
    const CATPCurve *Pcurve2,
    const CATCrvLimits &Limit2,
    const CATPointOnEdgeCurve *iStart1,
    const CATPointOnEdgeCurve *iEnd1,
    const CATPointOnEdgeCurve *iStart2,
    const CATPointOnEdgeCurve *iEnd2) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    const CATPCurve *Pcurve1,
    const CATCrvLimits &Limit1,
    const CATPCurve *Pcurve2,
    const CATCrvLimits &Limit2) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    const CATPCurve *Pcurve1,
    const CATPCurve *Pcurve2) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionNoCheck(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *_Config,
    const CATPointOnEdgeCurve *iPoec1On1,
    const CATPointOnEdgeCurve *iPoec2On1,
    const CATPCurve *iPCrv1,
    const CATPointOnEdgeCurve *iPoec1On2,
    const CATPointOnEdgeCurve *iPoec2On2,
    const CATPCurve *iPCrv2,
    const CATSkillValue skill) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *_Config,
    const CATPointOnEdgeCurve *iPoec1On1,
    const CATPointOnEdgeCurve *iPoec2On1,
    const CATPCurve *iPCrv1,
    const CATPointOnEdgeCurve *iPoec1On2,
    const CATPointOnEdgeCurve *iPoec2On2,
    const CATPCurve *iPCrv2,
    const CATSkillValue skill) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *_Config,
    const CATPCurve *Pcurve1,
    const CATCrvLimits &Limit1,
    const CATPCurve *Pcurve2,
    const CATCrvLimits &Limit2,
    const CATSkillValue skill) = 0;

  virtual CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *_Config,
    const CATPCurve *Pcurve1,
    const CATPCurve *Pcurve2,
    const CATSkillValue skill) = 0;

  virtual CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
    const CATMathVector2D &V1,
    const CATMathVector2D &V2) = 0;

  virtual CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
    const CATPointOnEdgeCurve *iPOEC1,
    const CATPCurve *iPCrv1,
    const CATPointOnEdgeCurve *iPOEC2,
    const CATPCurve *iPCrv2) = 0;

  virtual CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
    const CATPointOnCurve *p1,
    const CATPointOnCurve *p2) = 0;

  virtual CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
    const CATPCurve *Pcurve1,
    const CATCrvParam &p1,
    const CATPCurve *Pcurve2,
    const CATCrvParam &p2) = 0;

  virtual CATPGMLawUtilities *CATPGMCreateLawUtilities(CATGeoFactory *iFactory) = 0;

  virtual CATPGMLawUtilities *CATPGMCreateLawUtilities(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftConfig) = 0;

  virtual CATIPGMMassProperties1D *CATPGMCreateMassProperties1D(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurveToAnalyse) = 0;

  virtual CATIPGMMaxCurveCurvature *CATPGMCreateMaxCurveCurvature(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPCurve *iPCurve,
    const CATCrvLimits &iLimits,
    short iOrientation) = 0;

  virtual CATIPGMMaxCurveCurvature *CATPGMCreateMaxCurveCurvature(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATCurve *iCurve,
    const CATCrvLimits &iLimits) = 0;

  virtual CATIPGMMaxOffset *CATPGMCreateMaxOffset(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATSurLimits &iLimits) = 0;

  //virtual CATIPGMMaxOffset *CATPGMCreateMaxOffset(
  //  CATGeoFactory *iFactory,
  //  CATSurface *iSurface,
  //  CATSkillValue iMode) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsBipar *initialBipar) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsMultiForm *initialMultiForm,
    CATMathFunctionXY *supportXGlobalEquation,
    CATMathFunctionXY *supportYGlobalEquation,
    CATMathFunctionXY *supportZGlobalEquation) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsMultiForm *initialMultiForm) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATFrFNurbsBipar *initialBipar) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATFrFNurbsMultiForm *initialMultiForm,
    CATMathFunctionXY *supportXGlobalEquation,
    CATMathFunctionXY *supportYGlobalEquation,
    CATMathFunctionXY *supportZGlobalEquation) = 0;

  virtual CATIPGMNurbsQuality *CATPGMCreateNurbsQuality(
    CATGeoFactory *factory,
    CATFrFNurbsMultiForm *initialMultiForm) = 0;

  virtual CATIPGMOffsetOperator *CATPGMCreateOffsetOperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurfaceToOffset,
    const double iOffsetValue,
    CATSurLimits *iRequiredMaxLimits) = 0;

  virtual CATIPGMOrientationLoop *CATPGMCreateOrientationLoop(
    CATGeoFactory *iFactory,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam) = 0;

  virtual CATIPGMPConicsComputation *CATPGMCreatePConicsComputation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface) = 0;

  virtual CATIPGMPConicsComputation *CATPGMCreatePConicsComputation(
    CATGeoFactory *iFactory,
    CATSurface *iSurface) = 0;

  virtual CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
    CATGeoFactory *iFactory,
    const CATSurParam &iSurParam,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam) = 0;

  virtual CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
    CATGeoFactory *iFactory,
    const CATSurParam &iSurParam,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam,
    const double iTol3D) = 0;

  virtual CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iSurParam,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam) = 0;

  virtual CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iSurParam,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam,
    const double iTol3D) = 0;

  virtual void CATCGMComputeCurvatureFromSecondDerivative(
    const CATMathVector &iFirstDerivative,
    const CATMathVector &iSecondDerivative,
    CATMathVector &oCurvature,
    const CATTolerance &iTol) = 0;

  virtual void CATCGMComputeSecondDerivativeFromCurvature(
    const CATMathVector &iFirstDerivative,
    const CATMathVector &iCurvature,
    CATMathVector &oSecondDerivative,
    const CATTolerance &iTol) = 0;

  virtual void CATCGMRemove(CATQuinticInterpolation *&iMove) = 0; // Useful

  virtual CATQuinticInterpolation *CATCGMCreateCrvQuinticInterpolation(
    CATSoftwareConfiguration *iConfig,
    const CATMathSetOfPointsND *iPoints,
    const double *iparameter,
    CATMathSetOfPointsND *ioFirstDerivatives,
    CATMathSetOfPointsND *ioSecondDerivatives,
    const CATLONG32 *KindOfImpositions,
    CATSkillValue iMode) = 0;

  virtual CATQuinticInterpolation *CATCGMCreateCrvQuinticInterpolationCx2(
    const CATMathSetOfPointsND *iPoints,
    const double *iparameter,
    CATMathSetOfPointsND *ioFirstDerivatives,
    CATMathSetOfPointsND *ioSecondDerivatives,
    const CATLONG32 *KindOfImpositions,
    CATSkillValue iMode) = 0;

  virtual CATQuinticInterpolation *CATCGMCreateCrvQuinticInterpolation(
    const CATMathSetOfPointsND *iPoints,
    const double *iparameter,
    CATMathSetOfPointsND *ioFirstDerivatives,
    CATMathSetOfPointsND *ioSecondDerivatives,
    const CATLONG32 *KindOfImpositions,
    CATSkillValue iMode) = 0;

  virtual CATQuinticInterpolation *CATCGMPrivCreateCrvQuinticInterpolation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathSetOfPointsND *iPoints,
    const double *iparameter,
    CATMathSetOfPointsND *ioFirstDerivatives,
    CATMathSetOfPointsND *ioSecondDerivatives,
    const CATLONG32 *KindOfImpositions,
    CATLONG32 ComputeSystem) = 0;

  virtual CATIPGMRollLinesComputation *CATPGMCreateRollLinesComputation(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathPoint *iSetOfPoints,
    CATLONG32 NbPoints,
    double iTolApprox,
    CATGeometricType iFormToRecognize,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPoints *iSetOfPoints,
    double iTolApprox,
    CATGeometricType iFormToRecognize,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
    CATGeoFactory *iFactory,
    CATMathPoint *iSetOfPoints,
    CATLONG32 NbPoints,
    double iTolApprox,
    CATGeometricType iFormToRecognize,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
    CATGeoFactory *iFactory,
    CATMathSetOfPoints *iSetOfPoints,
    double iTolApprox,
    CATGeometricType iFormToRecognize,
    CATSkillValue iMode) = 0;

  virtual CATIPGMMassProperties1D *CATPGMCreateMassProperties1D(const CATCurve *iCurveToAnalyse) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iHoldCurve,
    const CATLONG32 iHCOrientation,
    CATEdgeCurve *iEdgeCurve2,
    CATPCurve *iInPCurve2,
    const short iInSurfOrientation2,
    const short iInPCurveSide2,
    CATPCurve *iOutPCurve2,
    const short iOutSurfOrientation2,
    const short iOutPCurveSide2,
    const CATBoolean iFirstIsCovered2,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATIPGMConnect *CATPGMCreateConnect(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    const CATLONG32 iOrientation1,
    CATSurface *iSurface2,
    const CATLONG32 iOrientation2,
    CATSurface *iSurface3,
    const CATLONG32 iOrientation3,
    CATIPGMConnectTool *iProfile,
    const CATSkillValue iMode) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsMultiForm *mf,
    CATLONG32 nbKnotsU,
    double *knotsU,
    CATLONG32 nbKnotsV,
    double *knotsV,
    const CATTolerance &iTolObject) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *initialPCurve,
    CATSurfaceImport *surfaceImport) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATFrFNurbsMultiForm *mf,
    CATLONG32 nbKnotsU,
    double *knotsU,
    CATLONG32 nbKnotsV,
    double *knotsV,
    const CATTolerance &iTolObject) = 0;

  virtual CATApproxFunctionXByPiecewisePol *CATCGMCreateApproxFunctionXByPiecewisePol(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATMathFunctionX *iEval,
    const CATMathInterval &iLimits,
    double iTolerance,
    const CATTolerance &iTolObject) = 0;

  virtual CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iSurParam,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam,
    const double iTol3D,
    const CATBoolean iCopyInputParameter) = 0;

  virtual double CATExtrapolSurface_CATPGMGetExtrapolParamLength(
    CATSoftwareConfiguration * const iConfig,
    const CATTolerance &iTolObject,
    const CATSurface * const iSurface,
    const CATSurParam &iStartParam,
    const CATBoolean iIsParamDirU,
    const double iExtrapol3dLength) = 0;

  virtual CATIPGMExtrapolSurface *CATPGMCreateExtrapolation(
    CATGeoFactory *iFactory,
    CATSurface *iSurfaceToExtrapolate,
    CATSurParam *iStart,
    CATExtrapolSurfaceSide iSurfaceSide,
    const CATMathVector2D &iVectorEstimation,
    short iAllowSurfaceCreation,
    CATSkillValue iMode,
    CATSoftwareConfiguration *iConfig,
    const CATExtrapolVectFormEnum iVectorEstimationForm) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricOpe2rators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGeometricOpeItfBldr2 *CATCGMGetGeometricOpeItfBldr2();

#endif /* CATIPGMGeometricOpeItfBldr2_h */
