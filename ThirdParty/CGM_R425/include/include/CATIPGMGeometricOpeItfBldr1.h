#ifndef CATIPGMGeometricOpeItfBldr1_h
#define CATIPGMGeometricOpeItfBldr1_h

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
#include "CATCivilCurveDef.h"

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
class CATSurLimits;
class CATMathDirection;
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
class CATICGMProjectionCrvSur;
class CATICGMProjectionPtSur;
class CATICGMProjectionPtCrv;
class CATGeoODTScaleManager;
class CATICGMSurTo2DGlobalPlanarMapping;
class CATIPGMLocalAnalysis2D;
class CATICGMLocalAnalysis2D;
class CATICGMLocalAnalysis1D;
class CATIPGMDynMassProperties1D;
class CATICGMDynMassProperties1D;
class CATLISTP(CATCurve);
class CATLISTP(CATSurface);
class CATPGMCivilTransitionInfo;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGeometricOpeItfBldr1;

/**
 * Factory of implementations of CGM interfaces for the framework GeometricOperators.
 */
class ExportedByCATGMModelInterfaces CATIPGMGeometricOpeItfBldr1: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATBoolean CATCGMConcatenateNurbsSurfaces(
    CATLISTP(CATSurface) *iSurfList,
    CATLONG32 iNbSurfacesU,
    CATLONG32 iNbSurfacesV,
    CATMathGridOfPoints *&ioControlPoints,
    double *&ioWeights,
    CATKnotVector *&ioKnotVectorU,
    CATKnotVector *&ioKnotVectorV) = 0;

  virtual CATBoolean CATCGMConcatenateNurbsCurves(
    CATLISTP(CATCurve) *iCurveList,
    CATMathSetOfPoints *&ioControlPoints,
    double *&ioWeights,
    CATKnotVector *&ioKnotVector) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATLONG32 iNbCrv,
    CATCurve **iTabCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATCrvLimits &iLimits,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATEdgeCurve *iEdgeCurve,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATICGMConfusionPtOnCrvPtOnCrv *CATCGMCreateConfusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnCurve *iPoint1,
    const CATPointOnCurve *iPoint2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2,
    const CATCurve *iCrv,
    const double &tol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnEdgeCurve *iPECrv1,
    const CATPointOnEdgeCurve *iPECrv2,
    const CATCurve *iCrv,
    double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnCurve *iPoint1,
    const CATPointOnCurve *iPoint2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATICGMConfusionPtOnSurPtOnSur *CATCGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iParam1,
    const CATSurParam &iParam2,
    const CATSurface *iSurface,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATICGMConfusionPtOnSurPtOnSur *CATCGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnSurface *iPoint1,
    const CATPointOnSurface *iPoint2,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnSurPtOnSur *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATSurParam &iParam1,
    const CATSurParam &iParam2,
    const CATSurface *iSurface,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnSurPtOnSur *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATPointOnSurface *iPoint1,
    const CATPointOnSurface *iPoint2,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATICGMConvertCurveToCanonic *CATCGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLONG32 iNbCrv,
    CATCurve **iTabCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATICGMConvertCurveToCanonic *CATCGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATCrvLimits &iLimits,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATICGMConvertCurveToCanonic *CATCGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLONG32 iNbCrv,
    CATCurve **iTabCrv,
    CATCrvParam *iStartParam,
    CATCrvParam *iEndParam,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATCrvLimits &iLimits,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdgeCurve *iEdgeCurve,
    CATPointOnEdgeCurve *iStartPOEC,
    CATPointOnEdgeCurve *iEndPOEC,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinCrvCrv *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCrv1,
    CATCurve *iCrv2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinCrvCrv *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCrv1,
    CATCurve *iCrv2,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinPtCrv *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    CATMathNurbsMultiForm *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinPtCrv *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    CATCurve *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinPtCrv *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATPoint *iPt,
    CATCurve *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    CATMathNurbsMultiForm *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    CATCurve *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtCrv *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    CATPoint *iPt,
    CATCurve *iCrv,
    CATSkillValue iMode) = 0;

  virtual CATICGMDynMassProperties1D *CATCGMDynCreateMassProperties1D(
    CATCurve *iCurveToAnalyze,
    CATSoftwareConfiguration *iSoftwareConfig) = 0;

  virtual CATIPGMDynMassProperties1D *CATPGMDynCreateMassProperties1D(
    const CATCurve *iCurveToAnalyze) = 0;

  virtual CATIPGMDynMassProperties1D *CATPGMDynCreateMassProperties1D(
    CATCurve *iCurveToAnalyze,
    CATSoftwareConfiguration *iSoftwareConfig) = 0;

  virtual CATLONG32 CATPGMIntersectionIsNull(
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSurParam &iParam1,
    CATSurParam &iParam2) = 0;

  virtual CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis1D(
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iSupport,
    const CATCrvParam &iPointToAnalyze) = 0;

  virtual CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis1D(
    const CATCurve *iSupport,
    const CATCrvParam &iPointToAnalyze) = 0;

  virtual CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
    CATSoftwareConfiguration *iConfig,
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual CATIPGMLocalAnalysis2D *CATPGMCreateLocalAnalysis2D(
    CATSoftwareConfiguration *iConfig,
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual CATIPGMLocalAnalysis2D *CATPGMCreateLocalAnalysis2D(
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual CATICGMMathNurbsCurveTools *CATCGMCreateMathNurbsCurveTools(
    const CATKnotVector &iKnotVector,
    const CATLONG32 &iIsRational,
    const CATMathSetOfPoints &iSetOfPoints,
    const MathNurbsDimension &iDimension,
    const double *iWeights) = 0;

  virtual CATICGMMathNurbsSurfaceTools *CATCGMCreateMathNurbsSurfaceTools(
    const CATKnotVector &iUKnotVector,
    const CATKnotVector &iVKnotVector,
    const CATLONG32 &iIsRational,
    const CATMathGridOfPoints &iVertices,
    const double *iWeights) = 0;

  virtual CATICGMNurbsCurveTools *CATCGMCreateNurbsCurveTools(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve) = 0;

  virtual CATIPGMNurbsCurveTools *CATPGMCreateNurbsCurveTools(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve) = 0;

  virtual CATICGMNurbsSurfaceTools *CATCGMCreateNurbsSurfaceTools(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface) = 0;

  virtual CATIPGMNurbsSurfaceTools *CATPGMCreateNurbsSurfaceTools(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface) = 0;

  virtual void CATSurTo2DGlobalMapping_CATCGMUnStream(
    CATCGMStream &Str,
    CATGeoFactory *iFactory,
    CATIPGMSurTo2DGlobalMapping *&oMapping,
    const char *iLabelReserved) = 0;

  virtual CATICGMDistanceMinPtSur *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *iSur,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinPtSur *CATCGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtSur *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *iSur,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtSur *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATICGMEdgeCurveComputation *CATCGMCreateEdgeCurveComputation(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    CATCurve *iCurve2) = 0;

  virtual CATIPGMEdgeCurveComputation *CATPGMCreateEdgeCurveComputation(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    CATCurve *iCurve2) = 0;

  virtual CATICGMInclusionPtCrv *CATCGMCreateInclusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPoint,
    const CATCurve *iCrv,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInclusionPtCrv *CATPGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iM,
    const CATCurve *iCrv,
    const double iTol,
    const CATCrvLimits &iLim) = 0;

  virtual CATIPGMInclusionPtCrv *CATPGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iM,
    const CATCurve *iCrv,
    const double iTol) = 0;

  virtual CATIPGMInclusionPtCrv *CATPGMCreateInclusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPoint,
    const CATEdgeCurve *iECrv,
    const CATCurve *iCrv,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInclusionPtCrv *CATPGMCreateInclusion(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPoint,
    const CATCurve *iCrv,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATICGMInclusionPtSur *CATCGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *Sur,
    const double &iTol,
    const CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATICGMInclusionPtSur *CATCGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    const double &iTol,
    const CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInclusionPtSur *CATPGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *Sur,
    const double &iTol,
    const CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInclusionPtSur *CATPGMCreateInclusion(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    const double &iTol,
    const CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATICGMIntersectionCrvCrv *CATCGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    CATCurve *iCurve2,
    CATSkillValue iMode) = 0;

  virtual CATICGMIntersectionCrvSur *CATCGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATSurface *iSurface,
    CATSkillValue iMode) = 0;

  virtual CATICGMIntersectionSurSur *CATCGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionCrvCrv *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve1,
    CATCurve *iCurve2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionCrvSur *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATCurve *iCurve,
    CATSurface *iSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersectionWithInits(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersectionPlnSur(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATPlane *iPlane,
    CATSurface *iSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionTriSur *CATPGMCreateIntersectionTriSur(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSurface *iSurface3,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionCrvCrv *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATCurve *iCurve1,
    CATCurve *iCurve2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionCrvSur *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATCurve *iCurve,
    CATSurface *iSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersection(
    CATGeoFactory *iWhere,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode,
    CATBoolean iRelimitation) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersectionWithInits(
    CATGeoFactory *iWhere,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionSurSur *CATPGMCreateIntersectionPlnSur(
    CATGeoFactory *iWhere,
    CATPlane *iPlane,
    CATSurface *iSurface,
    CATSkillValue iMode) = 0;

  virtual CATIPGMIntersectionTriSur *CATPGMCreateIntersectionTriSur(
    CATGeoFactory *iWhere,
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSurface *iSurface3,
    CATSkillValue iMode) = 0;

  virtual CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis(
    const CATICGMLocalAnalysis2D *iAnalysisToCopy) = 0;

  virtual CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis(
    CATSoftwareConfiguration *iConfig,
    const CATSurface *iSurface,
    const CATSurParam &iPointToAnalyze) = 0;

  virtual CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis(
    const CATICGMLocalAnalysis1D *iAnalysisToCopy) = 0;

  virtual CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis(
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iSupport,
    const CATCrvParam &iPointToAnalyze) = 0;

  virtual CATICGMProjectionCrvSur *CATCGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCurve,
    const CATCrvLimits *iCrvLim,
    const CATSurface *iSurface,
    const CATSurLimits *iSurLim,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATICGMProjectionPtSur *CATCGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPoint *iPoint,
    const CATSurface *iSurface,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATICGMProjectionPtCrv *CATCGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPoint *iPoint,
    const CATCurve *iCurve,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtCrv *CATPGMCreateProjection(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    const CATMathDirection *iDirection) = 0;

  virtual CATIPGMListOfProjectionCrvSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATLISTP(CATCurve) *iCrvList,
    const CATLISTP(CATSurface) *iSurList,
    CATLONG32 iNPatchU,
    CATLONG32 iNPatchV,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionCrvSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCurve,
    const CATCrvLimits *iCrvLim,
    const CATSurface *iSurface,
    const CATSurLimits *iSurLim,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPoint *iPoint,
    const CATSurface *iSurface,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtCrv *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *iConfig,
    const CATPoint *iPoint,
    const CATCurve *iCurve,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATICGMReflectCurve *CATCGMCreateReflectCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSur,
    CATMathDirection &iDir,
    CATAngle iAngle,
    CATSkillValue mode) = 0;

  virtual CATIPGMReflectCurve *CATPGMCreateReflectCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurface *iSur,
    CATMathDirection &iDir,
    CATAngle iAngle,
    CATSkillValue mode) = 0;

  virtual CATIPGMSurTo2DGlobalPlanarMapping *CATPGMCreatePlanarMapping(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathAxis &iAxis) = 0;

  virtual CATIPGMSurTo2DGlobalPlanarMapping *CATPGMCreatePlanarMapping(
    CATGeoFactory *iFactory,
    const CATMathAxis &iAxis) = 0;

  virtual CATICGMCurveCurvilinearParameterization *CATCGMCreateCurveCurvilinearParameterization(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iTolerance) = 0;

  virtual CATIPGMCurveCurvilinearParameterization *CATPGMCreateCurveCurvilinearParameterization(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iTolerance) = 0;

  virtual CATICGMSurTo2DGlobalPlanarMapping *CATCGMCreatePlanarMapping(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathAxis &iAxis) = 0;

  virtual CATICGMSurTo2DGlobalPlanarMapping *CATCGMCreatePlanarMapping(
    CATGeoFactory *iFactory,
    const CATMathAxis &iAxis) = 0;

  virtual CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
    CATLONG32 iSide,
    CATLaw *iRadiusLaw,
    CATLaw *iMappingLaw,
    CATBoolean iIsEuclidian) = 0;

  virtual CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
    CATSoftwareConfiguration *iConfig,
    CATLONG32 iSide,
    CATLaw *iRadiusLaw,
    CATLaw *iMappingLaw,
    CATBoolean iIsEuclidian) = 0;

  virtual CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
    CATICGMDistanceTool *iDistanceTool,
    CATLaw *iMappingLaw) = 0;

  virtual CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
    CATSoftwareConfiguration *iConfig,
    CATICGMDistanceTool *iDistanceTool,
    CATLaw *iMappingLaw,
    CATBoolean iIsPlanarBody) = 0;

  virtual CATIPGMProjectionPtCrv *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    const CATPoint *iPoint,
    const CATCurve *iCurve,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionPtSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    const CATPoint *iPoint,
    const CATSurface *iSurface,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMProjectionCrvSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    const CATCurve *iCurve,
    const CATCrvLimits *iCrvLim,
    const CATSurface *iSurface,
    const CATSurLimits *iSurLim,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMListOfProjectionCrvSur *CATPGMCreateProjection(
    CATGeoFactory *iWhere,
    const CATLISTP(CATCurve) *iCrvList,
    const CATLISTP(CATSurface) *iSurList,
    CATLONG32 iNPatchU,
    CATLONG32 iNPatchV,
    const CATMathDirection *iDirection,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iWhere,
    const CATPointOnCurve *iPoint1,
    const CATPointOnCurve *iPoint2,
    const double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    const CATPointOnEdgeCurve *iPECrv1,
    const CATPointOnEdgeCurve *iPECrv2,
    const CATCurve *iCrv,
    double iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConfusionPtOnCrvPtOnCrv *CATPGMCreateConfusion(
    CATGeoFactory *iFactory,
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2,
    const CATCurve *iCrv,
    const double &tol,
    CATSkillValue iMode) = 0;

  virtual CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
    const CATICGMLocalAnalysis2D &iAnalysisToCopy) = 0;

  virtual CATIPGMLocalAnalysis2D *CATPGMCreateLocalAnalysis2D(
    const CATIPGMLocalAnalysis2D &iAnalysisToCopy) = 0;

  virtual CATICGMDistanceMinPtSur *CATCGMCreateDistanceMinLim(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    const CATSurLimits *iSurLim,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinPtSur *CATCGMCreateDistanceMinLim(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *iSur,
    const CATSurLimits *iSurLim,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtSur *CATPGMCreateDistanceMinLim(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATPoint *iPt,
    const CATSurface *iSur,
    const CATSurLimits *iSurLim,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinPtSur *CATPGMCreateDistanceMinLim(
    CATGeoFactory *iWhere,
    CATSoftwareConfiguration *Config,
    const CATMathPoint &iPt,
    const CATSurface *iSur,
    const CATSurLimits *iSurLim,
    CATBoolean iSearchOnBoundary,
    CATSkillValue iMode) = 0;

  virtual CATBoolean CATIdenticalSurSur_CATPGMFilterSurfacesToTestTested(
    CATSurface *iSurface1,
    CATSurface *iSurface2) = 0;

  virtual CATLONG32 CATPGMIntersectionIsNull(
    CATSurface *iSurface1,
    CATSurface *iSurface2,
    CATSurParam &iParam1,
    CATSurParam &iParam2,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual void CATConnectTool_CATPGMWriteScaleInfo(CATCGMStream &Str) = 0;

  virtual void CATConnectTool_CATPGMReadScaleInfo(CATCGMStream &Str, double &oRefScale) = 0;

  virtual CATBoolean CATConnectTool_CATPGMGetScaleManager(
    CATGeoFactory *iFactory,
    CATGeoODTScaleManager *&oScaleManager) = 0;

  virtual CATBoolean CATConnectTool_CATPGMGetScaleManager(
    const double iScaleRef,
    CATGeoODTScaleManager *&oScaleManager) = 0;

  virtual CATPGMCivilTransitionInfo *CATPGMCreateCATCivilTransitionInfo(
    const CATCivilTransitionType iTransitionType,
    const double iL1,
    const double iL2,
    const double iR) = 0;

  virtual CATPGMCivilTransitionInfo *CATPGMCreateCATCivilTransitionInfo(
    const CATCivilTransitionType iTransitionType,
    const CATCivilTransitionInfoType iTransitionTypeInfo,
    const double iVal) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGeometricOpeItfBldr1 *CATCGMGetGeometricOpeItfBldr1();

#endif /* CATIPGMGeometricOpeItfBldr1_h */
