#ifndef CATIPGMGeometricOpeItfBldr3_h
#define CATIPGMGeometricOpeItfBldr3_h

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
#include "CATIntersectionSign.h"

// Civil
#include "CATCivilCurveDef.h"
#include "CATIPGMApproxClothoide.h" // for CATApproxClothoide_ClockOrientation
class CATCivilCurveParam;

// Geo oct-tree
#include "CATIPGMGeoOctreeSolver.h"
#include "CATPGMGeoBox.h"

class CATPGMSimplifEdgeCrvOnSupport;
class CATIPGMSurfaceToCanonic;
class CATIPGMSurfacesGridConcatenate;
class CATNurbsSurface;
class CATIPGMTryConfusionCrvCrv;
class CATIPGMTwistAnalysis;
class CATIPGMConnectCheckerInterfaceOfCurveSurface;
class CATIPGMConnectCheckerInterfaceOfSurfaces;
class CATMathBox;
class CATIPGMConnectCheckerInterfaceOfCurves;
class CATIPGMCornerPCrvPCrv;
class CATIPGMCurveAffineSupport;
class CATIPGMDistanceCrvSur;
class CATIPGMFrFApproxCurve;
class CATIPGMFrFApproxSurface;
class CATIPGMIdenticalSurSur;
class CATIPGMTangentLinePtPCrv;
class CATIPGMCrvLengths;
class CATIPGMExtractSameTangent;
class CATIPGMDistanceSurSur;
class CATFilletSurface;
class CATIPGMLayDownCrvSur;
class CATMultiSurface;
class CATIPGMProjectionInDirectionPtSur;
class CATIPGMExtractTangentAlongDir;
class CATPCurve;
class CATCrvParam;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATCrvLimits;
class CATFrFNurbsBipar;
class CATPGMBreakPCurveImport;
class CATSurfaceImport;
class CATFrFNurbsMultiForm;
class CATPointOnSurface;
class CATIPGMCurveToCanonic;
class CATIPGMOrientationLoop;
class CATMathDirection;
class CATIPGMIntersectionCrvSur;
class CATIPGMIntersectionSurSur;
class CATIPGMIntersectionCrvCrv;
class CATIPGMProjectionCrvSur;
class CATIPGMProjectionPtSur;
class CATPoint;
class CATIPGMProjectionPtCrv;
class CATIPGMDistanceMinCrvCrv;
class CATIPGMDistanceMinPtSur;
class CATIPGMDistanceMinPtCrv;
class CATSurParam;
class CATMathImplicitSystem;
class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathVector2D;
class CATMathSetOfPoints;
class CATPointOnCurve;
class CATIPGMInclusionPtSur;
class CATIPGMConfusionCrvCrv;
class CATKnotVector;
class CATMathGridOfPoints;
class CATIPGMTriTangentPCrv;
class CATIPGMSurTo2DGlobalCompositionMapping;
class CATIPGMBoxUVFrom3DLoop;
class CATIPGMMassProperties1D;
class CATMathVector2D;
class CATLISTP(CATSurParam);
class CATIPGMSurTo2DGlobalPlanarMapping;
class CATIPGMSurTo2DGlobalMapping;
class CATIPGMLocalAnalysis2D;
class CATICGMLocalAnalysis2D;
class CATICGMLocalAnalysis1D;
class CATIPGMDynMassProperties1D;
class CATICGMDynMassProperties1D;
class CATSurface;
class CATLISTP(CATCurve);
class CATLISTP(CATSurface);
class CATICGMCurveUserParameterization;
class CATIPGMCurveUserParameterization;
struct CATPipeData;
class CATGenericFillet;
class CATMathPlane;
class CATPlane;
class CATIPGMInclusionPtPCrv;
class CATIPGMIntersectionMultiSurface;
class CATIPGMSurfaceRecognizer;
class CATIPGMBendOperator;
class CATMathSetOfPointsNDWithVectors;
class CATCone;
class CATIPGMReflectCurve;
class CATIPGMPLineOnMultiSurface;
class CATIPGMSurfaceClosure;
class CATSphere;
class CATLISTP(CATMathPoint);
class CATLISTP(CATCrvLimits);
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATPCurve);
class CATIPGMLocalComparison2D;
class CATMathLine2D;
class CATPLine;
class CATPCircle;
class CATIPGMExtrapolMultiSurface;
class CATIPGMUnfoldCreaseCurveToExtrudeProfile;
//Civil
class CATIPGMApproxClothoide;
class CAT2DCurveEvaluator;
class CATCivilCurveEvaluator;
class CATIPGMApproxCivilCurve;
//class CATIPGMComputeCivilTransitionCurves;
class CATIPGMCivilCurveRecognizer;
class CATPGMCivilTransitionInfo;
class CATLISTP(CATPGMGeoFace);

class CATIPGMProfileRecognizer;


// Clash2D
class CATIPGMClash2D;

// Temp
#include "CATGeoOpArchiTEMP.h"
#include "CATCivilCurveArchiTEMP.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGeometricOpeItfBldr3;

/**
 * Factory of implementations of CGM interfaces for the framework GeometricOperators.
 */
class ExportedByCATGMModelInterfaces CATIPGMGeometricOpeItfBldr3: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iNbCrv,
    CATPCurve **iTabPCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSurface) = 0;

  virtual CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iNbCrv,
    CATEdgeCurve **iTabECrv,
    CATPCurve **iTabPCrv,
    CATPointOnEdgeCurve **iStartPOEC,
    CATPointOnEdgeCurve **iEndPOEC,
    CATSurface *iSurface) = 0;

  virtual CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
    CATGeoFactory *iFactory,
    const CATLONG32 iNbCrv,
    CATPCurve **iTabPCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSurface) = 0;

  virtual CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
    CATGeoFactory *iFactory,
    const CATLONG32 iNbCrv,
    CATEdgeCurve **iTabECrv,
    CATPCurve **iTabPCrv,
    CATPointOnEdgeCurve **iStartPOEC,
    CATPointOnEdgeCurve **iEndPOEC,
    CATSurface *iSurface) = 0;

  virtual CATMathFunctionXY *CATPGMCreateSurfaceCurvatureFunction(
    const CATMathFunctionXY *iFX,
    const CATMathFunctionXY *iFY,
    const CATMathFunctionXY *iFZ,
    const CATTolerance &iTolObject,
    const CATCurvatureType itype) = 0;

  virtual CATIsoParameter CATSurfaceToCanonic_CATCGMIsRuledSurface(
    const CATSurface *iSurface,
    const CATSurLimits &iSurLimits,
    double iTolerance) = 0;

  virtual CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    double iTolApprox,
    CATSkillValue iMode) = 0;

  /* NLD220120
  virtual CATIPGMSurfacesGridConcatenate *CATPGMCreateSurfacesGridConcatenate(
    CATGeoFactory *factory,
    CATNurbsSurface **initialSurfaces,
    CATLONG32 nbSurfI,
    CATLONG32 nbSurfJ,
    CATLONG32 *iExchangeIJFlags,
    CATLONG32 *iInvertIFlags,
    CATLONG32 *iInvertJFlags,
    double *internalStartIParameters,
    double *internalEndIParameters,
    double *internalStartJParameters,
    double *internalEndJParameters) = 0;
  */

  virtual CATIPGMSurfacesGridConcatenate *CATPGMCreateSurfacesGridConcatenate(
    CATGeoFactory *factory,
    CATSoftwareConfiguration *iConfig,
    CATNurbsSurface **initialSurfaces,
    CATLONG32 nbSurfI,
    CATLONG32 nbSurfJ,
    CATLONG32 *iExchangeIJFlags,
    CATLONG32 *iInvertIFlags,
    CATLONG32 *iInvertJFlags,
    double *internalStartIParameters,
    double *internalEndIParameters,
    double *internalStartJParameters,
    double *internalEndJParameters) = 0;

  virtual CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(CATGeoFactory *) = 0;

  virtual CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(
    CATGeoFactory *iWhere,
    CATCurve *iCrv1,
    const CATCrvLimits &iLimits1,
    CATCurve *iCrv2,
    const CATCrvLimits &iLimits2,
    const double iTolerance) = 0;

  virtual CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCrv1,
    const CATCrvLimits &iLimits1,
    CATCurve *iCrv2,
    const CATCrvLimits &iLimits2,
    const double iTolerance) = 0;

  virtual CATIPGMTwistAnalysis *CATPGMCreateTwistAnalysis(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATSurLimits &iSurLim) = 0;

  virtual CATIPGMTwistAnalysis *CATPGMCreateTwistAnalysis(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    const CATSurLimits &iSurLim) = 0;

  virtual CATIPGMBoxUVFrom3DLoop *CATPGMCreateBoxUVFrom3DLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsBipar *iSurface) = 0;

  virtual CATIPGMBoxUVFrom3DLoop *CATPGMCreateBoxUVFrom3DLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *initialPCurve,
    CATSurfaceImport *surfaceImport) = 0;

  virtual CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
    CATSoftwareConfiguration *iConfig,
    CATFrFNurbsMultiForm *mf,
    CATLONG32 nbKnotsU,
    double *knotsU,
    CATLONG32 nbKnotsV,
    double *knotsV) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfCurveSurface *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATPointOnEdgeCurve *iPOECOnCrv,
    CATSurface *iSurface,
    const CATSurLimits &iLimitSurf) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATPCurve *iPCrv1,
    const CATPCurve *iPCrv2,
    int iOriPCrv1VsSurf1,
    int iOriPCrv2VsSurf2) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    const CATSurLimits &iLimitSurf1,
    const CATSurLimits &iLimitSurf2,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATPCurve *iPCrv1,
    const CATPCurve *iPCrv2,
    int iOriPCrv1Mat,
    int iOriPCrv2Mat,
    CATBoolean iIsSmooth) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    const CATSurLimits &iLimSurf1,
    const CATSurLimits &iLimSurf2,
    const CATMathBox *iBoxFace1,
    const CATMathBox *iBoxFace2,
    const CATPointOnEdgeCurve *iPOECStart,
    const CATPointOnEdgeCurve *iPOECEnd,
    const CATPCurve *iPCrv1,
    const CATPCurve *iPCrv2,
    int iOriPCrv1Mat,
    int iOriPCrv2Mat,
    int iOriPCrv1Face1,
    int iOriPCrv2Face2) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfCurves *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    CATCrvLimits &iLimits1,
    int iOriCrv1,
    CATCurve *iCurve2,
    CATCrvLimits &iLimits2,
    int iOriCrv2,
    CATCrvParam &iPointToAnalyze1,
    CATCrvParam &iPointToAnalyze2) = 0;

  virtual CATIPGMConnectCheckerInterfaceOfCurves *CATPGMCreateConnectChecker(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve1,
    const CATPointOnEdgeCurve *iPOECStart1,
    const CATPointOnEdgeCurve *iPOECEnd1,
    int iOriEdgeCrv1,
    CATEdgeCurve *iEdgeCurve2,
    const CATPointOnEdgeCurve *iPOECStart2,
    const CATPointOnEdgeCurve *iPOECEnd2,
    int iOriEdgeCrv2,
    const CATPointOnEdgeCurve *iPOECOnCrv1,
    const CATPointOnEdgeCurve *iPOECOnCrv2) = 0;

  virtual CATIPGMCornerPCrvPCrv *CATPGMCreateCornerPCrvPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    CATPCurve *PCurve1,
    int Sign1,
    CATPCurve *PCurve2,
    int Sign2,
    CATPositiveLength &Radius,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCornerPCrvPCrv *CATPGMCreateCornerPCrvPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    CATPCurve *PCurve1,
    CATPCurve *PCurve2,
    CATPointOnSurface *PPoint,
    CATPositiveLength &Radius,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveAffineSupport *CATPGMCreateCurveAffineSupport(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATCurve **iCurves,
    const CATLONG32 iNbCurves,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveAffineSupport *CATPGMCreateCurveAffineSupport(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATCurve *iCurve,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iNbCrv,
    CATCurve **iTabCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSupport) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurveToCanonic,
    CATCrvLimits &iLimits,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurveToCanonic,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceCrvSur *CATPGMCreateDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATSurface *iSurface,
    CATDistanceType iDistanceType,
    CATSkillValue mode) = 0;

  virtual CATIPGMFrFApproxCurve *CATPGMCreateFrFApproxCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATMathFunctionX *iEvalX,
    const CATMathFunctionX *iEvalY,
    const CATMathFunctionX *iEvalZ,
    const CATMathInterval &iLimits,
    double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFApproxCurve *CATPGMCreateFrFApproxCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATMathFunctionX *iEvalU,
    const CATMathFunctionX *iEvalV,
    const CATMathInterval &iLimits,
    CATSurface *iSupport,
    double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFApproxCurve *CATPGMCreateFrFApproxCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iTolerance,
    int iForce3DCurveCreation,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFApproxSurface *CATPGMCreateFrFApproxSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATMathFunctionXY *iEvalX,
    const CATMathFunctionXY *iEvalY,
    const CATMathFunctionXY *iEvalZ,
    const CATMathInterval &iLimitsU,
    const CATMathInterval &iLimitsV,
    double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFApproxSurface *CATPGMCreateFrFApproxSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATSurface *iSurface,
    const CATSurLimits &iLimits,
    double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIdenticalSurSur *CATPGMCreateIdentical(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMOrientationLoop *CATPGMCreateOrientationLoop(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iNbPCrv,
    const CATPCurve **iPCrv,
    const CATCrvParam *iStartParam,
    const CATCrvParam *iEndParam) = 0;

  virtual CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATSurface) *iSurList,
    double iTolApprox,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    double iTolApprox,
    CATSkillValue iMode) = 0;

  virtual CATIPGMTangentLinePtPCrv *CATPGMCreateTangentLinePtPCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    CATPointOnSurface *iPoint,
    CATPCurve *iPCurve,
    CATSkillValue iMode,
    short VerificationMode) = 0;

  virtual CATIPGMCrvLengths *CATPGMCreateCATCrvLengths(
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCRV,
    CATSkillValue mode) = 0;

  virtual CATIPGMCrvLengths *CATPGMCreateCATCrvLengths(
    const CATCurve *iCRV,
    CATSkillValue mode) = 0;

  virtual CATIPGMCrvLengths *CATPGMCreateCrvLengths(
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCRV) = 0;

  virtual CATIPGMCrvLengths *CATPGMCreateCrvLengths(const CATCurve *iCRV) = 0;

  virtual CATIPGMCornerPCrvPCrv *CATPGMDynCreateCornerPCrvPCrv(
    CATGeoFactory *iFactory,
    CATPCurve *PCurve1,
    CATPCurve *PCurve2,
    CATPointOnSurface *PPoint,
    CATPositiveLength &Radius,
    CATSkillValue imode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMDynCreateIntersection(
    CATGeoFactory *iFactory,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue mode) = 0;

  virtual CATIPGMIntersectionCrvSur *CATPGMDynCreateIntersection(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATSurface *iSurface,
    CATSkillValue mode) = 0;

  virtual CATIPGMIntersectionCrvCrv *CATPGMDynCreateIntersection(
    CATGeoFactory *iFactory,
    CATCurve *iCurve1,
    CATCurve *iCurve2,
    CATSkillValue mode) = 0;

  virtual CATIPGMProjectionCrvSur *CATPGMDynCreateProjection(
    CATGeoFactory *iFactory,
    const CATCurve *iCurve,
    const CATCrvLimits *iCrvLim,
    const CATSurface *iSurface,
    const CATSurLimits *iSurLim,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtSur *CATPGMDynCreateProjection(
    CATGeoFactory *iFactory,
    const CATPoint *iPoint,
    const CATSurface *iSurface,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtCrv *CATPGMDynCreateProjection(
    CATGeoFactory *iFactory,
    const CATPoint *iPoint,
    const CATCurve *iCurve,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceSurSur *CATPGMDynCreateDistanceMin(
    CATGeoFactory *iFactory,
    const CATSurface *iSur1,
    const CATSurface *iSur2,
    CATSkillValue mode) = 0;

  virtual CATIPGMDistanceCrvSur *CATPGMDynCreateDistanceMin(
    CATGeoFactory *iFactory,
    const CATCurve *iCurve,
    const CATSurface *iSurface,
    CATSkillValue mode) = 0;

  virtual CATIPGMDistanceMinCrvCrv *CATPGMDynCreateDistanceMin(
    CATGeoFactory *iFactory,
    const CATCurve *iCrv1,
    const CATCurve *iCrv2,
    CATSkillValue mode) = 0;

  virtual CATIPGMDistanceMinPtSur *CATPGMDynCreateDistanceMin(
    CATGeoFactory *iFactory,
    const CATPoint *Pt,
    const CATSurface *Sur,
    CATBoolean SearchOnBoundary,
    CATSkillValue mode) = 0;

  virtual CATIPGMDistanceMinPtCrv *CATPGMDynCreateDistanceMin(
    CATGeoFactory *iFactory,
    CATPoint *iPt,
    CATCurve *iCrv,
    CATSkillValue iMode) = 0;

  virtual void CATCGMGetSurfaceValidMaxBox(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    CATSurParam &iParam,
    CATSurLimits &oSurLimits,
    CATLONG32 *oSideDiffFromMaxLim,
    CATBoolean DirtyHomotopyFlag,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATPGMIsPointOnBorder(
    CATSoftwareConfiguration *iConfig,
    const CATMathIntervalND &iDomain,
    const double *iPoint,
    CATLONG32 *ioSaturatedVar,
    const double iTol,
    const double iDomainScale) = 0;

  virtual void CATPGMProjectTangent(
    const CATMathIntervalND &iDomain,
    double iStartPoint[4],
    const CATTolerance &iTol,
    double ioStartTangent[4]) = 0;

  virtual void CATPGMProjectTangent(
    CATSoftwareConfiguration *iConfig,
    const CATMathIntervalND &iDomain,
    double iStartPoint[4],
    const CATTolerance &iTol,
    double ioStartTangent[4]) = 0;

  virtual CATLONG32 CATPGMCurvatureTransverseToDirection(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const double *iUV,
    const double *iDirUV,
    double &oCurvature) = 0;

  virtual CATLONG32 CATPGMCompareCurvatureAtPoint(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface0,
    CATSurface *iSurface1,
    const double *iUVRS,
    const double *iDirUVRS) = 0;

#ifdef Q48_IntSurSur_KeepImproveStartingPointInterface
  virtual CATLONG32 CATPGMImproveStartingPoint(
    CATSoftwareConfiguration *iConfig,
    const double iStartPoint[4],
    CATMathIntervalND *iDomain,
    CATMathImplicitSystem *iImplicitSystem,
    const CATTolerance &iTol,
    double oStartPoint[4]) = 0;
#endif // Q48_IntSurSur_KeepImproveStartingPointInterface

  virtual CATLONG32 CATPGMIsFilletIntersectingSurface(
    CATSoftwareConfiguration *iConfig,
    CATFilletSurface *iFillet,
    CATSurLimits *iLimitOnFillet,
    CATSurface *iSurface,
    CATSurLimits *iLimitSurface,
    double iTol) = 0;

  virtual CATLONG32 CATPGMIsFilletIntersectingSurface(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iFillet,
    CATSurface *iRepFillet,
    CATSurLimits *iLimitOnFillet,
    CATSurface *iSurface,
    CATSurface *iRepSurface,
    CATSurLimits *iLimitOnSurface,
    double iTol) = 0;

  virtual double CATPGMDistance(
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iNbPt0,
    const CATMathPoint iSet0[],
    const CATLONG32 iNbPt1,
    const CATMathPoint iSet1[],
    const CATTolerance &iTol,
    double &oW0,
    double &oW1,
    CATLONG32 &oDiag,
    CATBoolean iDoublePoint) = 0;

  virtual double CATPGMDeviationPolygonCircle(
    CATSoftwareConfiguration *iConfig,
    const CATMathSetOfPointsND &iPolygon,
    const double iRadius,
    const double iC[3],
    const double iI[3],
    const double iJ[3],
    const double iK[3]) = 0;

  virtual CATLONG32 CATPGMIsProcOffsetOfSameIntersecting(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurf0,
    CATSurface *iRep0,
    CATSurLimits &iLim0,
    CATSurface *iSurf1,
    CATSurface *iRep1,
    CATSurLimits &iLim1,
    double iTol) = 0;

  virtual CATLONG32 CATPGMIsFirstProcOffsetIntersecting(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurf0,
    CATSurface *iRep0,
    CATSurLimits &iLim0,
    CATSurface *iSurf1,
    CATSurface *iRep1,
    CATSurLimits &iLim1,
    double iTol) = 0;

  virtual CATIPGMDistanceSurSur *CATPGMCreateDistance(
    CATGeoFactory *iFactory,
    CATSurface *iSur1,
    CATSurface *iSur2,
    CATDistanceType iDistanceType,
    CATSkillValue mode) = 0;

  virtual CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATCrvLimits &iCrvLimits,
    CATSurface *iSurface,
    CATSurLimits &iSurLimits,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
    CATGeoFactory *iWhere,
    CATLISTP(CATCurve) *iCurveList,
    CATMultiSurface *iMultiSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionInDirectionPtSur *CATPGMCreateProjectionInDirectionPtSur(
    CATGeoFactory *iFactory,
    const CATMathVector *iDir,
    const CATMathSetOfPoints *iSet,
    const CATSurface *isurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurTo2DGlobalCompositionMapping *CATPGMCreateCompositionMapping(
    CATGeoFactory *iFactory,
    CATIPGMSurTo2DGlobalMapping *iGlobalMapping,
    const CATMathFunctionXY *iNewX,
    const CATMathFunctionXY *iNewY,
    const CATMathFunctionXY *iOldX,
    const CATMathFunctionXY *iOldY) = 0;

  virtual CATIPGMExtractTangentAlongDir *CATPGMCreateTangentAlongDir(
    CATGeoFactory *Factory,
    CATCurve *Curve,
    CATMathDirection &Direction,
    CATPointOnCurve *StartPoc,
    CATPointOnCurve *EndPoc,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnCurve *iStartPtOnCrv1,
    const CATPointOnCurve *iEndPtOnCrv1,
    const CATPointOnCurve *iStartPtOnCrv2,
    const CATPointOnCurve *iEndPtOnCrv2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnEdgeCurve *iStartPtOnECrv1,
    const CATPointOnEdgeCurve *iEndPtOnECrv1,
    const CATCurve *iCrv1,
    const CATPointOnEdgeCurve *iStartPtOnECrv2,
    const CATPointOnEdgeCurve *iEndPtOnECrv2,
    const CATCurve *iCrv2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCrv1,
    const CATCurve *iCrv2,
    const double iTol,
    const CATCrvParam &iStartParam1,
    const CATCrvParam &iEndParam1,
    const CATCrvParam &iStartParam2,
    const CATCrvParam &iEndParam2,
    const CATEdgeCurve *iECrv1,
    const CATEdgeCurve *iECrv2) = 0;

  virtual CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    const CATPointOnCurve *iStartPtOnCrv1,
    const CATPointOnCurve *iEndPtOnCrv1,
    const CATPointOnCurve *iStartPtOnCrv2,
    const CATPointOnCurve *iEndPtOnCrv2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionCrvCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    const CATPointOnEdgeCurve *iStartPtOnECrv1,
    const CATPointOnEdgeCurve *iEndPtOnECrv1,
    const CATCurve *iCrv1,
    const CATPointOnEdgeCurve *iStartPtOnECrv2,
    const CATPointOnEdgeCurve *iEndPtOnECrv2,
    const CATCurve *iCrv2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATBoolean CATCGMConcatenateNurbsCurves(
    CATLISTP(CATCurve) *iCurveList,
    CATMathSetOfPoints *&ioControlPoints,
    double *&ioWeights,
    CATKnotVector *&ioKnotVector) = 0;

  virtual CATBoolean CATCGMConcatenateNurbsSurfaces(
    CATLISTP(CATSurface) *iSurfList,
    CATLONG32 iNbSurfacesU,
    CATLONG32 iNbSurfacesV,
    CATMathGridOfPoints *&ioControlPoints,
    double *&ioWeights,
    CATKnotVector *&ioKnotVectorU,
    CATKnotVector *&ioKnotVectorV) = 0;

  virtual CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATLISTP(CATCurve) *iCurveList,
    CATMultiSurface *iMultiSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    CATCurve *iCurve,
    CATCrvLimits &iCrvLimits,
    CATSurface *iSurface,
    CATSurLimits &iSurLimits,
    CATSkillValue iMode) = 0;

  virtual CATIPGMTriTangentPCrv *CATPGMCreateTriTangentPCrv(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    CATPCurve *PCurve1,
    CATLONG32 iSide1,
    CATPCurve *PCurve2,
    CATLONG32 iSide2,
    CATPCurve *PCurve3,
    CATLONG32 iSide3,
    CATSkillValue iMode) = 0;

  virtual CATICGMCurveUserParameterization *CATCGMCreateCurveUserParameterization(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    CATMathFunctionX *iReparametrizationFunction,
    double iTolerance) = 0;

  virtual CATIPGMCurveUserParameterization *CATPGMCreateCurveUserParameterization(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    CATMathFunctionX *iReparametrizationFunction,
    double iTolerance) = 0;

  virtual CATIPGMExtractSameTangent *CATPGMDynCreateExtractSameTangent(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATMathDirection &iDirection,
    CATSkillValue iMode,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATLONG32 CATPGMIsSurfaceIntersecting(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface0,
    CATSurLimits *iLimitOn0,
    CATSurface *iSurface1,
    CATSurLimits *iLimitOn1,
    CATMathBox &iSearchBox,
    double iTol) = 0;

  virtual CATLONG32 CATPGMIsCanonicalIntersecting(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface0,
    CATSurLimits *iLimitOn0,
    CATMathBox &iSurfBox0,
    CATSurface *iSurface1,
    CATSurLimits *iLimitOn1,
    CATMathBox &iSurfBox1,
    CATMathBox &iSearchBox,
    double iTol) = 0;

  virtual CATLONG32 CATPGMIsFirstImplicitIntersecting(
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface0,
    CATSurface *iSurface1,
    CATSurLimits *iLimitOn,
    CATMathBox &iSurfBox1,
    CATMathBox &iSearchBox,
    double iTol) = 0;

  virtual CATIPGMCurveAffineSupport *CATPGMCreateCurveAffineSupport(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATCurve *iCurve,
    CATCrvLimits &iCrvLim,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCurveAffineSupport *CATPGMCreateCurveAffineSupport(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATCurve **iCurves,
    CATCrvLimits *iCrvLims,
    const CATLONG32 iNbCurves,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLocalComparison2D *CATPGMCreateLocalComparison2D(
    CATSoftwareConfiguration *iConfig,
    const CATSurface *iRedSurface,
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetMinDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble & oMinList,
    CATListOfDouble & owsList) = 0;

virtual HRESULT CATExtremumTools_CATPGMGetMinDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,  
    const CATCrvLimits & iLim,
    CATListOfDouble & oMinList,
    CATListOfDouble & owsList) = 0;

 virtual HRESULT CATExtremumTools_CATPGMGetMinDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    const CATCrvLimits & iLim1,
    CATCurve *iCurve2,
    const CATCrvLimits & iLim2,
    CATListOfDouble & oMinList,
    CATListOfDouble & oCrv1WsList,
    CATListOfDouble & oCrv2WsList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetMaxDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble & oMaxList,
    CATListOfDouble & owsList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetMaxDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble & oMaxList,
    CATListOfDouble & owsList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalMinDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oMinList,
    CATListOfDouble &owsList,
    CATListOfInt &oMinNatureList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalMaxDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oMaxList,
    CATListOfDouble &owsList,
    CATListOfInt &oMaxNatureList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalExtremumDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oExtrList,
    CATListOfDouble &owsList,
    CATListOfInt &oExtrNatureList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalMinDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oMinList,
    CATListOfDouble &owsList,
    CATListOfInt &oMinNatureList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalMaxDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oMaxList,
    CATListOfDouble &owsList,
    CATListOfInt &oMaxNatureList) = 0;

  virtual HRESULT CATExtremumTools_CATPGMGetLocalExtremumDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oExtrList,
    CATListOfDouble &owsList,
    CATListOfInt &oExtrNatureList) = 0;

  virtual CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iPt,
    const CATEdgeCurve *iECrv,
    const CATPCurve *iPCrv,
    const double iTol,
    CATSkillValue mode) = 0;

  virtual CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iPt,
    const CATPCurve *iPCrv,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInclusionPtPCrv *CATPGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iPt,
    const CATPCurve *iPCrv,
    const double &iTol,
    const CATCrvLimits &iLim,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionMultiSurface *CATPGMCreateIntersectionMultiSurface(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATMultiSurface *iSurface1,
    CATMultiSurface *iSurface2) = 0;

  virtual CATBoolean CATPGMIsPointOnBorder(
    CATSoftwareConfiguration *iConfig,
    const CATMathIntervalND &iDomain,
    const double *iPoint,
    CATLONG32 *ioSaturatedVar,
    const double iTol,
    const double iDomainScale,
    const CATSurface **iSurface) = 0;

  virtual CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    int iNumberOfCurves,
    CATPCurve **iListOfPCurves,
    CATCrvLimits *iListCrvLimits,
    const CATSurLimits *iSurLimits,
    double iLinearTol,
    double iAngularTol) = 0;

  virtual CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
    CATLISTP(CATPCurve) &iListOfPCurvesOnSupport,
    CATLISTP(CATEdgeCurve) &iListOfEdges,
    CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
    const CATSurLimits *iSurLimits,
    double iLinearTol,
    double iAngularTol) = 0;

  virtual CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
    CATListOfInt &iListOfPCurvesRepartitionOnFace,
    CATLISTP(CATPCurve) &iListOfPCurvesOnSupport,
    CATLISTP(CATEdgeCurve) &iListOfEdges,
    CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
    const CATSurLimits *iSurLimits,
    double iLinearTol,
    double iAngularTol) = 0;

  virtual CATIPGMBendOperator *CATPGMCreateBendOperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsNDWithVectors *iPassingPtsAndTgts,
    double iMinBendRadius) = 0;

  virtual int CATPGMIntersectionMultiSurface_OrderInitExit(
    CATGeoFactory *_Factory,
    CATLISTP(CATMathPoint) *_InitPointList,
    CATBoolean &_Closed_Points,
    CATBoolean &_Closed_InitExits,
    int _IndexLim[2][2]) = 0;

  virtual CATIPGMReflectCurve *CATPGMCreateSweepCharacteristicCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATMathVector &iLinVelocity,
    const CATMathVector &iAngVelocity,
    CATSkillValue iMode) = 0;

  virtual CATIPGMPLineOnMultiSurface *CATPGMCreatePLineOnMultiSurface(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATMultiSurface *iSurface,
    CATMathPoint2D &iStart,
    CATMathPoint2D &iEnd) = 0;

  virtual CATIPGMSurfaceClosure *CATPGMCreateSurfaceClosure(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface) = 0;

  virtual CATIPGMReflectCurve *CATPGMCreateSweepCharacteristicCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    const CATMathVector &iLinVelocity,
    const CATMathVector &iAngVelocity,
    CATMathSetOfPointsND const &SeedPts,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface,
    CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
    CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
    CATLISTP(CATPCurve) &iListOfPCurvesOnSupports,
    CATLISTP(CATCrvLimits) &iListCrvLimitsOnSupports,
    CATLISTP(CATEdgeCurve) &iListOfEdges,
    CATLISTP(CATCrvLimits) &iListCrvLimitsOnEdges,
    const CATSurLimits *iSurLimits,
    double iLinearTol,
    double iAngularTol) = 0;

#ifdef Q48_IntSurSur_KeepImproveStartingPointInterface
  virtual CATLONG32 CATPGMImproveStartingPoint(
    CATSoftwareConfiguration *iConfig,
    const double iStartPoint[4],
    const CATMathIntervalND *iDomain,
    CATMathImplicitSystem *iImplicitSystem,
    const CATTolerance &iTolObject,
    double oStartPoint[4]) = 0;
#endif // Q48_IntSurSur_KeepImproveStartingPointInterface

  virtual CATLONG32 CATPGMFastIntersectionCrvCrv(
    CATSoftwareConfiguration *iConfig,
    const CATMathFunctionX *XYZ0[3],
    const CATMathFunctionX *XYZ1[3],
    const CATMathInterval &I0,
    const CATMathInterval &I1,
    CATLONG32 nbpt0,
    CATLONG32 nbpt1,
    double iTolerance,
    const CATTolerance &iTol,
    CATMathSetOfPointsND &oSolutions,
    CATBoolean iDoublePoint) = 0;

  virtual void CATPGMGetCrossingAndSignature(
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCrv,
    CATPCurve *iPCrv[2],
    CATCrvLimits iPCrvLim[2],
    CATSurface *iSurface[2],
    CATSurLimits iSurLim[2],
    CATIntersectionSign oIntSign[2],
    CATIntersectionCrossing oIntCross[2],
    CATLONG32 *ioCrvType) = 0;

  virtual short CATPGMTransformAngleToWithinConeRange(
    CATSoftwareConfiguration *iConfig,
    const CATTolerance &iTol,
    const CATCone *iCone,
    CATAngle &ioAngle) = 0;

  virtual short CATPGMTransformAngleToWithinSphereRange(
    CATSoftwareConfiguration *iConfig,
    const CATTolerance &iTol,
    const CATSphere *iSphere,
    CATAngle &ioAngle) = 0;

  virtual CATBoolean CATPGMTransformAngleToWithinRange(
    CATSoftwareConfiguration *iConfig,
    const CATTolerance &iTol,
    const CATAngle iMinAngle,
    const CATAngle iMaxAngle,
    CATAngle &ioAngle) = 0;

 ////////////////////////////////////////////////////////
 /////////////  CIVIL CURVES ////////////////////////////
 ////////////////////////////////////////////////////////

/////// Civil Curves - Generic
/////// Civil Curves - Generic - Approx

  virtual CATIPGMApproxCivilCurve *CATPGMCreateApproxCivilCurve(
          CATGeoFactory            *iFactory             ,
          CATSoftwareConfiguration *iConfig              ,
          CATCivilCurveEvaluator   *iCivilCurveEvaluator ,
          CATSurface               *iSurface             ) = 0;

  // deprecated (Q48 22/02/21: called from CATIPGMApproxCivilCurve)
  virtual CATIPGMApproxCivilCurve *CATPGMCreateApproxCivilCurve(
        CATGeoFactory            * iFactory             ,
        CATSoftwareConfiguration * iConfig              ,
  const CAT2DCurveEvaluator      * iCivilCurveEvaluator ,
        CATSurface               * iSurface             ) = 0;

/////// Civil Curves - Generic - Evaluator

   // --------------------------------------------------------------------------------------
   // Line - params
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator( const CATTolerance              & iTolerance        ,
                                                          CATSoftwareConfiguration *  iConfig           ,
                                                    const CATMathPoint2D            & iPt               ,
                                                    const CATMathVector2D           & iDir              ,
                                                    const CATMathVector2D           & iDirOrtho         ,
                                                    const CATCivilCurveType           iCurveType        ,
                                                          CATCivilCurveEvaluator   *& oEvaluator        ,
                                                    const double                   *  iA2        = NULL ,
                                                    const double                   *  iLength    = NULL ,
                                                    const double                   *  iRadius    = NULL ,
                                                    const double                   *  iAngle     = NULL ,
                                                    const double                   *  iShifting  = NULL ,
                                                    const CATBoolean                  iAccurate  = FALSE) = 0 ;

   // --------------------------------------------------------------------------------------
   // Line - Circle
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance              & iTolerance   ,
                                                          CATSoftwareConfiguration *  iConfig      ,
                                                    const CATMathPoint2D            & iLineOrigin  ,
                                                    const CATMathVector2D           & iLineDir     ,
                                                    const CATMathPoint2D            & iCircleCenter,
                                                    const double                      iCircleRadius,
                                                    const CATCivilCurveType           iCurveType   ,
                                                          CATMathPoint2D            & oCharactPt   ,
                                                          double                    & oLength      ,
                                                          double                    & oA           ,
                                                          CATCivilCurveEvaluator   *& oEvaluator   ,
                                                    const CATBoolean                  iAccurate = FALSE) = 0 ;

   // --------------------------------------------------------------------------------------
   // Circle - Params
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
                                                         CATSoftwareConfiguration             *  iConfig,
                                                   const CATMathPoint2D                        & iCircleCenter,
                                                   const double                                  iCircleRadius,
                                                   const CATCivilInput_ClockOrientation          iCircleOrientation,
                                                   const CATMathPoint2D                        & iCircleStartPoint,
                                                   const CATCivilCurveType                       iCurveType,
                                                   const CATCivilCurveParam                    & iParam1,
                                                   const CATCivilCurveParam                    & iParam2,
                                                   const CATCivilCurve_CircleCircleTransition    iTransitionTypeCSC,
                                                         CATCivilCurveEvaluator               *& oCivilEvaluator) = 0;

   // --------------------------------------------------------------------------------------
   // Circle - Params (end at a line ==> R2 is infinite)
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
                                                         CATSoftwareConfiguration             *  iConfig,
                                                   const CATMathPoint2D                        & iCircleCenter,
                                                   const double                                  iCircleRadius,
                                                   const CATCivilInput_ClockOrientation          iCircleOrientation,
                                                   const CATMathPoint2D                        & iCircleStartPoint,
                                                   const CATCivilCurveType                       iCurveType,
                                                   const CATCivilCurveParam                    & iParam1,
                                                         CATCivilCurveEvaluator               *& oCivilEvaluator) = 0;
         
   // --------------------------------------------------------------------------------------
   // Sprial - Params
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
                                                         CATSoftwareConfiguration             *  iConfig,
                                                   const CATCivilCurveEvaluator               *  iCivilEvaluator,
                                                   const CATCivilCurveType                       iCurveType,
                                                   const CATCivilCurveParam                    & iParam1,
                                                   const CATCivilCurveParam                    & iParam2,
                                                   const CATCivilCurve_CircleCircleTransition    iTransitionTypeCSC,
                                                         CATCivilCurveEvaluator               *& oCivilEvaluator) = 0;

   // --------------------------------------------------------------------------------------
   // Sprial - Params (end with a line ==> R2 = infinite)
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance              & iTolerance,
                                                         CATSoftwareConfiguration *  iConfig,
                                                   const CATCivilCurveEvaluator   *  iCivilEvaluator,
                                                   const CATCivilCurveType           iCurveType,
                                                   const CATCivilCurveParam        & iParam1,
                                                         CATCivilCurveEvaluator   *& oCivilEvaluator) = 0;
   
   // --------------------------------------------------------------------------------------
   // Circle - Circle
   // --------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance                    & iTolerance          ,
                                                          CATSoftwareConfiguration       *  iConfig             ,
                                                    const CATMathPoint2D                  & iCircleCenter1      ,
                                                    const double                            iCircleRadius1      ,
                                                    const CATCivilInput_ClockOrientation    iCircleOrientation1 ,
                                                    const CATMathPoint2D                  & iCircleCenter2      ,
                                                    const double                            iCircleRadius2      ,
                                                    const CATCivilCurveType                 iCurveType          ,
                                                    const CATCivilCurveEvaluator         *  iInitEvaluator      ,
                                                          CATMathPoint2D                  & oCharactPt          ,
                                                          CATMathInterval                 & oParamInterval      ,
                                                          double                          & oA                  ,
                                                          CATCivilCurveEvaluator         *& oEvaluator          ,
                                                    const CATBoolean                        iAccurate = FALSE) = 0;
      
   // --------------------------------------------------------------------------------------------------------------------------------
   // Circle - Circle (no init)
   //  DEPRECATED - please use the "with init" version
   // --------------------------------------------------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance                    & iTolerance          ,
                                                          CATSoftwareConfiguration       *  iConfig             ,
                                                    const CATMathPoint2D                  & iCircleCenter1      ,
                                                    const double                            iCircleRadius1      ,
                                                    const CATCivilInput_ClockOrientation    iCircleOrientation1 ,
                                                    const CATMathPoint2D                  & iCircleCenter2      ,
                                                    const double                            iCircleRadius2      ,
                                                    const CATCivilCurveType                 iCurveType          ,
                                                          CATMathPoint2D                  & oCharactPt          ,
                                                          CATMathInterval                 & oParamInterval      ,
                                                          double                          & oA                  ,
                                                          CATCivilCurveEvaluator         *& oEvaluator          ,
                                                    const CATBoolean                        iAccurate = FALSE) = 0;

   // --------------------------------------------------------------------------------------------------------------------------------
   // Circle - Circle (fixed length)
   //  DEPRECATED - please use the "circle + params" version with LENGTH and RADIUS
   // --------------------------------------------------------------------------------------------------------------------------------
   virtual HRESULT CATPGMCreateCivilCurveEvaluator( const CATTolerance                          & iTolerance          ,
                                                          CATSoftwareConfiguration             *  iConfig             ,
                                                    const CATMathPoint2D                        & iCircleCenter1      ,
                                                    const double                                  iCircleRadius1      ,
                                                    const CATCivilInput_ClockOrientation          iCircleOrientation1 ,
                                                    const CATMathPoint2D                        & iStartPointOnCircle1,
                                                    const double                                  iCircleRadius2      ,
                                                    const CATCivilCurve_CircleCircleTransition    iTransitionType     ,
                                                    const double                                  iLength             ,
                                                    const CATCivilCurveType                       iCurveType          ,
                                                          CATMathPoint2D                        & oCharactPt          ,
                                                          CATMathInterval                       & oParamInterval      ,
                                                          double                                & oA                  ,
                                                          CATCivilCurveEvaluator               *& oEvaluator          ,
                                                    const CATBoolean                              iAccurate = FALSE   ) = 0 ;

#ifdef Q48_Civil_Keep_FixedParameterCSC
virtual HRESULT CATPGMCreateCivilCurveEvaluator( const CATTolerance                                   & iTolerance          ,
                                                       CATSoftwareConfiguration                       * iConfig             ,
                                                 const CATMathPoint2D                                 & iCircleCenter1      ,
                                                 const double                                           iCircleRadius1      ,
                                                 const CATCivilInput_ClockOrientation                   iCircleOrientation1 ,
                                                 const CATMathPoint2D                                 & iStartPointOnCircle1,
                                                 const double                                           iCircleRadius2      ,
                                                 const CATCivilCurve_CircleCircleTransition             iTransitionType     ,
                                                 const CATCivilCurveDef::ParamType                      iCivilParameterType ,
                                                 const double                                           iCivilParameterValue,
                                                 const CATCivilCurveType                                iCurveType          ,
                                                       CATMathPoint2D                                 & oCharactPt          ,
                                                       CATMathInterval                                & oParamInterval      ,
                                                       double                                         & oA                  ,
                                                       CATCivilCurveEvaluator                        *& oEvaluator          ,
                                                 const CATBoolean                                       iAccurate = FALSE   ) = 0 ;
#endif // Q48_Civil_Keep_FixedParameterCSC

#ifdef Q48_Civil_KeepOldCreate_PtPtDir
virtual HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance             & iTolerance          ,
                                                      CATSoftwareConfiguration * iConfig             ,
                                                const CATMathPoint2D           & iStartPoint         ,
                                                const CATMathVector2D          & iStartTangent       ,
                                                const CATMathPoint2D           & iEndPoint           ,
                                                const CATCivilCurveType          iCurveType          ,
                                                      CATMathPoint2D           & oCharactPt          ,
                                                      double                   & oLength             ,
                                                      double                   & oA                  ,
                                                      CATCivilCurveEvaluator  *& oEvaluator          ,
                                                const CATBoolean                 iAccurate = FALSE   ) = 0;
#endif //Q48_Civil_KeepOldCreate_PtPtDir

  virtual HRESULT CATPGMCreateCivilCurveEvaluator(
    const CATTolerance &iTolerance,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iApex,
    const CATMathVector2D &iDir,
    const double iFocalDist,
    CAT2DCurveEvaluator *&oEvaluator) = 0;

  virtual HRESULT CATPGMCreateCivilCurveEvaluator(
    const CATTolerance &iTolerance,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iPt,
    const CATMathVector2D &iDir,
    const CATMathVector2D &iDirOrtho,
    const double iLength,
    const double iRadius,
    const CATCivilCurveType iCurveType,
    CATCivilCurveEvaluator  *&oEvaluator,
    const CATBoolean iAccurate=FALSE) = 0;

  virtual HRESULT CATPGMCreateCivilCurveEvaluator(
    const CATTolerance &iTolerance,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iStartPoint,
    const CATMathPoint &iEndPoint,
    const double iLength,
    const CATMathVector &iAxis,
    CATMathPlane &oPlane,
    CAT2DCurveEvaluator *&oEvaluator) = 0;

  virtual HRESULT CATPGMCreateCivilCurveEvaluatorFromEnd(
    const CATTolerance &iTolerance,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iPt,
    const CATMathVector2D &iDir,
    const CATMathVector2D &iDirOrtho,
    const double iLength,
    const double iRadius,
    const CATCivilCurveType iCurveType,
    CATCivilCurveEvaluator *&oEvaluator,
    const CATBoolean iAccurate = FALSE) = 0;

 /////// Civil Curves - Clothoides
 /////// Civil Curves - Clothoides - Approx

  /* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
  virtual CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iPt,
    const CATMathVector2D &iDir,
    const CATMathVector2D &iDirOrtho,
    CATSurface *iSurface,
    const double *iA2,
    const double *iLength,
    const double *iRadius,
    const double *iAngle,
    const double *iShifting) = 0;

  /* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
  virtual CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iLineOrigin,
    const CATMathVector2D &iLineDir,
    const CATMathPoint2D &iCircleCenter,
    double iCircleRadius,
    CATSurface *iSurface) = 0;

#ifdef CIVIL_CURVE_OLD
  /* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
  virtual CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATPLine *iPLine,
    const CATPCircle *iPCircle,
    CATBoolean iInverse) = 0;
#endif //CIVIL_CURVE_OLD

  /* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
  virtual CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iStartPoint,
    const CATMathVector2D &iStartTangent,
    const CATMathPoint2D &iEndPoint,
    CATSurface *iSurface) = 0;

  /* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
  virtual CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iCircleCenter1,
    const double iCircleRadius1,
    const CATApproxClothoide_ClockOrientation iCircleOrientation1,
    const CATMathPoint2D &iCircleCenter2,
    const double iCircleRadius2,
    CATSurface *iSurface) = 0;

/////// Civil Curves - Clothoides - Others

  // Q48 17/05/21: This is uesed in CATSkmWireframe.dll
  virtual HRESULT CATPGMComputeParamClothoide(
    CATSoftwareConfiguration *iConfig,
    const CATTolerance &iTol,
    const CATMathPoint2D &iPtLine1,
    const CATMathVector2D &iDirLine1,
    const CATMathVector2D &iDirOrtho1,
    const CATMathPoint2D &iPtLine2,
    const CATMathVector2D &iDirLine2,
    const CATMathVector2D &iDirOrtho2,
    const double iLengthClotho1,
    const double iLengthClotho2,
    const double iRadius,
    CATMathPoint2D &oClotho1OnLine1,
    CATMathPoint2D &oCenterCircle,
    CATMathPoint2D &oClotho2OnLine2,
    CATBoolean &oSelfIntersection,
    CATBoolean &oEndPointsConfused) = 0;

  // Q48 17/05/21: This is uesed in CATSkmWireframe.dll
  virtual HRESULT CATPGMComputeParamClothoide(
    CATSoftwareConfiguration *iConfig,
    const CATTolerance &iTol,
    const CATMathPoint2D &iCircleCenter1,
    const double iCircleRadius1,
    const CATBoolean iLineLeftFromCircle1,
    const CATMathPoint2D &iCircleCenter2,
    const double iCircleRadius2,
    const CATBoolean iLineLeftFromCircle2,
    const double iLengthClotho1,
    const double iLengthClotho2,
    CATMathPoint2D &oClotho1OnLine,
    CATMathPoint2D &oClotho2OnLine,
    CATMathVector2D &oDirClotho1,
    CATMathVector2D &oDirClotho2) = 0;

   virtual HRESULT CATPGMComputeCivilTransitionCurvesInformation(
          CATGeoFactory             * iFactory,
          CATSoftwareConfiguration  * iConfig,
    const CATMathPoint2D            & iPtLine1,
    const CATMathVector2D           & iDirLine1,
    const CATMathVector2D           & iDirOrtho1,
    const CATMathPoint2D            & iPtLine2,
    const CATMathVector2D           & iDirLine2,
    const CATMathVector2D           & iDirOrtho2,
    const CATPGMCivilTransitionInfo * iTransitionInfo,
    const CATCivilCurveType           iCurveType,
          CATMathPoint2D            & oCivilOnLine1,
          CATMathPoint2D            & oCenterCircle,
          CATMathPoint2D            & oCivilOnLine2,
          CATBoolean                & oSelfIntersection,
          CATBoolean                & oEndPointsConfused,
    const CATBoolean                  iReverse = FALSE) = 0;

   virtual HRESULT CATPGMComputeCivilTransitionCurvesInformation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint2D &iPtLine1,
    const CATMathVector2D &iDirLine1,
    const CATMathVector2D &iDirOrtho1,
    const CATMathPoint2D &iPtLine2,
    const CATMathVector2D &iDirLine2,
    const CATMathVector2D &iDirOrtho2,
    const CATPGMCivilTransitionInfo *iTransitionInfo,
    const CATCivilCurveType iCurveType,
    CATMathPoint2D &oCivilOnLine1,
    CAT2DCurveEvaluator *&oCivilCurve,
    CATMathPoint2D &oCivilOnLine2) = 0;

////////////////////////////////////////////////////////
//               END OF CIVIL CURVES                  //
////////////////////////////////////////////////////////

  virtual CATIPGMExtrapolMultiSurface *CATPGMCreateExtrapolation(
    CATGeoFactory * const iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMultiSurface * const iMultiSurfaceToExtrapolate,
    const double * const iRequiredGlobalLimits,
    const CATBoolean iAllowMultipleExtrapolation,
    const CATBoolean iAllowOffsetNurbsExtrapolation) = 0;

  virtual CATIPGMUnfoldCreaseCurveToExtrudeProfile *CATPGMCreateCATUnfoldCreaseCurveToExtrudeProfile(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathDirection &iExtrude1Dir,
    const CATMathDirection &iExtrude2Dir,
    const CATCrvParam &iUnfoldOrigin,
    CATPCurve *iUnfoldCreaseCurve,
    const CATCrvLimits *iLimits) = 0;

  virtual CATIPGMIntersectionMultiSurface *CATPGMCreateIntersectionMultiSurface(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATMultiSurface *iSurface1,
    CATMultiSurface *iSurface2,
    const CATBoolean iInterpolMode) = 0;
  virtual CATIPGMGeoOctreeSolver *CATPGMCreateGeoOctreeSolver(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody) = 0;

  virtual CATPGMGeoBox *CATPGMCreateGeoBox(
    CATGeoFactory *Factory,
    CATSoftwareConfiguration *iConfig,
    const CATMathBox &iBox,
    CATPGMGeoFace **iGeoFaces,
    CATLONG32 iNbFaces) = 0;

  virtual CATIPGMProfileRecognizer *CATPGMCreateProfileRecognizer(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathSetOfPointsND *iPoints) = 0;


////////////////////////////////////////////////////////
//               START OF CLASH2D                     //
////////////////////////////////////////////////////////


  virtual CATIPGMClash2D *CATPGMCreateCATClash2D(
    CATGeoFactory *iUserFactory,
    CATSoftwareConfiguration *iConfig,
    double iClashTol) = 0;

////////////////////////////////////////////////////////
//               END OF CLASH2D                       //
////////////////////////////////////////////////////////


};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricOpe3rators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGeometricOpeItfBldr3 *CATCGMGetGeometricOpeItfBldr3();

#endif /* CATIPGMGeometricOpeItfBldr3_h */
