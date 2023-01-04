#ifndef CATIPGMTopologicalOpeItfBldr3_h
#define CATIPGMTopologicalOpeItfBldr3_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCollec.h"
#include "CATDynOperatorDef.h"
#include "CATDynDraftDef.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CATTopDefine.h"
#include "CATMinMax.h"
#include "CATBodyFreezeMode.h"
#include "CATSkillValue.h"
#include "CATICGMHybSplit.h"
#include "CATIPGMHybSplit.h"
#include "CATHybDef.h"
#include "CATDir.h"
#include "CATExtremumCoordCrvDef.h"
#include "CATDynFilletBlendVertex.h"
#include "CATTopToolsGapCheckMode.h"
#include "CATDynValidShell.h"
#include "CATIsoParameter.h"
#include "CATTopDef.h"

class CATIPGMTopSmartProject;
class CATIPGMTopThickWire;

class CATIPGMDistanceMaxBodyBody;
class CATIPGMTopSkinBorderSorting;
class CATIPGMHybConfusion;

class CATIPGMTopNonLinearTransformation;
class CATMathNonLinearTransformation;
class CATIPGMTopPreTransformation;
class CATIPGMHybRegularize;
class CATIPGMTopRibbonHomotopy;
class CATRibTopOp; // This class is not yet interfaced because it's not used by clients
class CATLoop;
class CATFilletSurface;
class CATCompositeLaw;
class CATPlane;

class CATBody;
class CATIPGMConnectTool;
class CATIPGMShellFromClosedWire;
class CATIPGMTopCorner;
class CATMathVector;
class CATLaw;
class CATDynFilletRibbon;
class CATBlendParams;
class CATDynVariableFilletLaw;
class CATIPGMTopDevelop;
class CATICGMHybProject;
class CATSimplifyParallelTool;
class CATPGMTopBeamInverseBend;
class CATPGMDisconnectGateway;
class CATDisconnectEngine;
class CATLISTP(CATVertex);
class CATLISTP(CATCGMJournalInfo);
class CATLISTP(CATMathTransformation);
class CATIPGMSweep2;
class CATLISTP(CATICGMTopPropagationEdge);
class CATLISTP(CATSurface);
class CATLISTP(CATDynFilletRadius);
class CATLISTP(CATCurve);
class CATIPGMDynMassProperties2D;
class CATDynMassProperties1DOnEdge;
class CATLISTP(CATEdge);
class CATLISTP(CATDomain);
class CATLISTP(CATICGMObject);
class CATICGMSurTo2DGlobalMapping;
class CATICGMDynMassProperties3D;
class CATLISTP(CATFace);
class CATLISTP(CATBody);
class CATMathTransformation;
class CATIPGMSkinExtrapolThickPlus;

#define CATICGMTopSweepWireSkinSegment CATICGMTopSweepWireSkin
#define CATIPGMTopSweepWireSkinSegment CATIPGMTopSweepWireSkin

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalOpeItfBldr3;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr3: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATIPGMTopSmartProject *CATPGMCreateTopSmartProject(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody_To_Project,
    CATBody *iBody_Support,
    CATMathDirection *iDirection) = 0;

  virtual CATIPGMTopThickWire *CATPGMCreateTopThickWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) *iWires,
    CATBody *iSupport,
    double iOffset) = 0;

  virtual CATBody *CATPGMCreateCircularBody(
    CATGeoFactory *iFactory,
    CATMathPoint &iCentre,
    CATPlane *iPlane,
    double iRadius,
    CATTopData *iTopData) = 0;

  virtual CATIPGMDistanceMaxBodyBody *CATPGMCreateDistanceMaxTopo(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATIPGMTopSkinBorderSorting *CATPGMCreateSkinBorderSorting(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATEdge) *iEdgesToSort,
    CATLISTP(CATFace) *iInitialFaces,
    CATLISTP(CATFace) *iPropagatedFaces) = 0;

  virtual CATIPGMHybConfusion *CATPGMCreateTopConfusion(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyCandidate,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMTopNonLinearTransformation *CATPGMCreateTopNonLinearTransformation(
    const CATMathNonLinearTransformation &iMathTransfo,
    CATGeoFactory *iFactory,
    CATBody *iBodytoTransform,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMTopNonLinearTransformation *CATPGMCreateTopNonLinearTransformation(
    const CATMathNonLinearTransformation &iMathTransfo,
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodytoTransform) = 0;

  virtual CATIPGMTopPreTransformation *CATPGMCreateTopPreTransformation(
    const CATMathNonLinearTransformation &iMathTransfo,
    CATGeoFactory *iFactory,
    CATBody *iBodytoTransform,
    CATLISTP(CATFace) *iFacestoTransform,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMTopPreTransformation *CATPGMCreateTopPreTransformation(
    const CATMathNonLinearTransformation &iMathTransfo,
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodytoTransform,
    CATLISTP(CATFace) *iFacestoTransform) = 0;

  virtual CATIPGMHybRegularize *CATPGMCreateTopRegularize(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToRegularize) = 0;

  virtual void CATPGMDoSmoothTgts(
    CATGeoFactory *Builder,
    CATTopData *iData,
    CATBody *TangentBody,
    CATBody *Support1,
    CATBody *PtCrv1,
    CATBody *Support2,
    CATBody *PtCrv2,
    CATBody *&SmoothBody,
    CATLONG32 iTrimFirst,
    CATLONG32 iTrimLast) = 0;

  virtual CATIPGMTopRibbonHomotopy *CATPGMTopCreateRibbonHomotopy(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATEdge *iEdge,
    const CATMathPoint &iPoint,
    CATIPGMConnectTool *iProfilePtr) = 0;

  virtual CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
    CATGeoFactory *iFactory,
    const CATBody *iBody,
    const CATSurface *iSupport,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopOpCornerTgtCenterOnCrvRad(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iCurveCenter,
    CATBody *iCurveTgt,
    double iRadius,
    CATBody *iSupport) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopOpCornerTgtCenterOnPt(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iCurve,
    CATBody *iPoint,
    CATBody *iSupport) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopOpCorner(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iCurve1,
    CATBody *iCurve2,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopOpCornerForPJB(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iCurve1,
    CATBody *iCurve2,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATBoolean CATPGMCheckCutAgain(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iCurTrackEdge,
    CATFace *iCurSupportFace,
    CATBoolean iOnlyEdgeInFace) = 0;

  virtual void CATPGMAddEdgesInsideBody(
    CATBody *iTargetBody,
    CATLISTP(CATEdge) &iEdges,
    CATRibTopOp *iRibTopTopWhoWantsToKeepDomains) = 0;

  virtual CATBody *CATPGMCreateBodyFromEdges(CATGeoFactory *iFactory, CATLISTP(CATEdge) &iEdges) = 0;

  virtual CATIsoParameter CATPGMGetFilletTangencyIsoParam(CATFace *iFace) = 0;

  virtual CATBoolean CATPGMCheckCellBoxesIntersection(
    CATCell *iLeftCell,
    CATCell *iRightCell,
    double iInflateLength) = 0;

  virtual CATOrientation CATPGMGetRelativeEdgeOrientation(
    CATEdge *iCuttingEdge,
    CATEdge *iBaseEdge) = 0;

  virtual CATBoolean CATPGMEvalSharpnessAngle(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATLISTP(CATFace) &iLeftFaces,
    CATLISTP(CATFace) &iRightFaces,
    CATShell *iLeftShell,
    CATShell *iRightShell,
    CATBody *iBody,
    CATOrientation iRightShellOrientation,
    CATAngle &oMaxAngle,
    CATSide iSideOfEdgeVsLeftShell,
    CATTopSharpness *oGlobalSharpness) = 0;

  virtual int CATPGMGetSkinFaces(CATShell *iSkinToSew, CATLISTP(CATFace) &ioSkinFaces) = 0;

  virtual CATBoolean CATPGMInclusionEdgeEdgeDiagnosis(
    CATGeoFactory *iGeoFactory,
    CATEdge *iEdge1,
    CATEdge *iEdge2,
    double iTolerance,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATPGMIsFaceCanBeDegenerated(
    CATFace *iFace,
    double iTolerance,
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBody *CATPGMCreateBodyMonoShell(
    CATShell *iShell,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody) = 0;

  virtual CATBody *CATPGMCreateBodyMonoShellMultiFace(
    CATLISTP(CATFace) &iFaces,
    CATListOfInt &iSides,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody) = 0;

  virtual CATBody *CATPGMCreateBodyMonoShellMonoFace(
    CATFace *iFace,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicate) = 0;

  virtual CATBody *CATPGMCreateBodyMonoWireMonoEdge(
    CATEdge *iEdge,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicate) = 0;

  virtual CATBody *CATPGMCreateBodyMonoVertex(
    CATVertex *iVertex,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicateVertex) = 0;

  virtual void CATPGMEvalLocalAngle(
    CATSoftwareConfiguration* iConfig,
    CATEdge *iEdge,
    CATCrvParam &iParamOnEdgeCurve,
    CATFace *iFace1,
    CATFace *iFace2,
    CATAngle &oAngle,
    double &oCosAngle) = 0;

  virtual void CATPGMFilterAndInsertJournal(
    CATCGMJournalList *iJournal,
    CATCGMJournalList *oJournal,
    CATListOfInt *iGeometricTypesOnly) = 0;

  virtual void CATPGMSeparateShells(
    CATBody *iBody,
    CATShell *iShell,
    CATCGMJournalList *iJournal,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATShell *&iShellToSeparate) = 0;

  virtual CATCell *CATPGMAdvGetCellSupport(
    CATTopologicalOperator *TopOp,
    CATCell *iCell,
    CATCell *iSupportOwningCell,
    int *NbContainers,
    CATCell **iUpperSupport,
    CATBody *iBodyCreation) = 0;

  virtual void CATPGMUpdateOfficialJournalWithPrivate(
    CATCGMJournalList *ioOfficialJournal,
    CATCGMJournalList *iPrivateJournal,
    CATLISTP(CATGeometry) *iOldCells,
    int iEdgeReporting) = 0;

  virtual void CATPGMUpdateEdgesListWithJournal(
    CATLISTP(CATEdge) *ioOldCells,
    CATCGMJournalList *iJournal) = 0;

  virtual void CATPGMUnMergeVertex2(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBodyToModify,
    CATVertex *iVertexToUnMerge,
    CATLISTP(CATCell) *ioNewVertices) = 0;

  virtual void CATPGMUnMergeVertex(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBodyToModify,
    CATVertex *iVertexToUnMerge) = 0;

  virtual void CATPGMUnMergeEdge(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBodyToModify,
    CATEdge *iEdgeToUnMerge,
    CATLISTP(CATDomain) *iModifiedLoop,
    CATLISTP(CATCell) *ioModifiedFaces,
    CATLISTP(CATCell) *ioNewEdges) = 0;

  virtual CATBoolean CATPGMAreVertexLinked(
    CATVertex *iVertex1,
    CATVertex *iVertex2,
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig,
    CATCell **oSuppCell,
    int *oDiag) = 0;

  virtual void CATPGMInsertEdgeInLoop(CATLoop *iLoo, CATEdge *iEdge, int iInsertRank, CATSoftwareConfiguration* iConfig) = 0;

  virtual void CATPGMGetComplementaryCell(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig,
    CATCell *iCell,
    CATCell *iBorderCell,
    CATLISTP(CATCell) &oComplementaryCell,
    CATBody *iNewBody,
    CATDomain *iDomain) = 0;

  virtual CATTopSign CATPGMGetRelativeOrient(
    CATFace *iFace,
    CATMathDirection &iDirection,
    CATOrientation iOrientation,
    CATShell *iShell,
    CATBody *iBody,
    CATVertex *iVertexOnFace,
    CATEdge *iEdgeOnFace,
    double iTol) = 0;

  virtual CATEdge *CATPGMGetAdjacentEdge(CATFace *iFace, CATVertex *iVertex, CATEdge *iKnownEdge) = 0;

  virtual int CATPGMCompareCurvatures(double iC1, double iC2, double iTolZero, double iTolRadius) = 0;

  virtual double CATPGMGetCurvatureOfFace(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATCell *iCell,
    CATVertex *iVertex,
    CATMathVector &iTgt,
    CATMathVector *TgtRef) = 0;

  virtual CATSide CATPGMIsCovered(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATFace *iFace,
    CATMathDirection &iDir,
    CATMathPoint &iPt) = 0;

  virtual CATBoolean CATPGMIsFreeBorderEdge(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATLONG32 &oNbBnddFaces,
    CATLONG32 &oNbCutFaces) = 0;

  virtual void CATPGMReplaceEdgeCurve(
    CATEdge *iEdge,
    CATEdgeCurve *iNewEdgeCurve,
    CATOrientation iOriNewEdgeCurveVsPrev,
    CATCurve *iCommonCurve) = 0;

  virtual CATEdgeCurve *CATPGMMergePCurveWithEdgeCurve(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCurve,
    CATCrvLimits &iPCurveLimits,
    CATEdgeCurve *iEdgeCurve,
    CATCrvLimits &iEdgeCurveLimits,
    double iTolerance,
    CATPCurve *iPCurveUnderEdge,
    CATOrientation &oOriNewEdgeCurveVsPrev) = 0;

  virtual CATEdgeCurve *CATPGMMergePCurveToEdgeCurve(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCurve,
    CATCrvLimits &iPCurveLimits,
    CATEdgeCurve *iEdgeCurve,
    CATCrvLimits &iEdgeCurveLimits,
    double iTolerance,
    CATSurface *iSurfaceUnderEdge,
    CATOrientation &oOriNewEdgeCurveVsPrev) = 0;

  virtual void CATPGMAddPCurveToEdge_2(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCurve,
    CATEdge *iEdge,
    double iTolerance,
    CATSurface *iSurfaceUnderEdge) = 0;

  /*  virtual void CATPGMMergeEdges(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATEdge *iEdge1,
    CATEdge *iEdge2,
    CATBoolean reverse) = 0;*/

  virtual CATBoolean CATPGMGetBorderVertices(
    CATLISTP(CATEdge) &iEdge,
    CATFace *iFace,
    CATVertex *&oStartVertex,
    CATVertex *&oEndVertex,
    CATEdge **oStartEdge,
    CATEdge **oEndEdge) = 0;

  virtual void CATPGMGetAllAdjacentFaces(
    CATSoftwareConfiguration *iConfig,
    CATBody *InitBody,
    CATLISTP(CATFace) *iReferenceListe,
    CATListPV &iKnownFaces,
    int nKF,
    CATLISTP(CATFace) *stopping,
    CATLISTP(CATFace) *faces,
    int iPropagMod,
    CATLISTP(CATEdge) *oTransitEdges,
    CATLISTP(CATEdge) *iPropagEdges,
    CATBoolean OnlyPropag,
    CATLISTP(CATEdge) *oBorders,
    CATLISTP(CATEdge) *iForbiddenBoundingEdges) = 0;

  virtual void CATPGMGetAllAdjacentFaces(
    CATSoftwareConfiguration *iConfig,
    CATBody *InitBody,
    CATFace *RefFace,
    CATLISTP(CATFace) *faces,
    CATDomain *iDomain,
    int iPropagMod,
    CATLISTP(CATFace) *OtherAdjFaces,
    CATLISTP(CATEdge) *oTransitEdges,
    CATLISTP(CATEdge) *iPropagEdges,
    CATBoolean OnlyPropag,
    CATLISTP(CATEdge) *oBorders,
    CATLISTP(CATEdge) *iForbiddenBoundingEdges) = 0;

  virtual void CATPGMCheckEdgeIsValid(CATEdge *iEdge, CATBoolean &oIsEdgeValid) = 0;

  virtual void CATPGMGetLimits(CATEdge *iEdge, CATCrvLimits &oLimits, CATCurve *iCurve) = 0;

  virtual void CATPGMGetMaxPCurvesBoxUV(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATSurLimits &oBoxUV) = 0;

  virtual void CATPGMGet2DBoundingBox(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace,
    CATSurLimits &o2DBoundingBoxForEdge,
    CATVertex *iStart,
    CATVertex *iEnd) = 0;

  virtual CATSide CATPGMGetSideFaceVsShell(CATDomain *shell, CATFace *fac) = 0;

  virtual void CATPGMGetAllLastSupportCells(
    CATBody *iCreationBody,
    CATSoftwareConfiguration *iConfig,
    CATCell *iCell,
    CATLISTP(CATCell) *oSupportCell,
    CATLISTP(CATVertex) *oSupportVertex,
    CATLISTP(CATEdge) *oSupportEdge,
    CATLISTP(CATFace) *oSupportFace) = 0;

  virtual void CATPGMGetBnddEdgesOnFaceAndLoop(
    CATVertex *iVertex,
    CATFace *iFace,
    CATLoop *iLoop,
    CATTopSign iDirection,
    CATLISTP(CATEdge) *oEdge,
    CATListOfInt *oSide) = 0;

  virtual CATVertex *CATPGMGetBrdrVertexOnFace(
    CATBody *iBody,
    CATShell *iShell,
    CATEdge *iEdge,
    CATFace *iFace,
    CATTopSign iDirection,
    CATLoop **oLoop) = 0;

  virtual CATBoolean CATPGMComputeGap(
    CATSoftwareConfiguration *iConfig,
    CATVertex *EndVertex,
    CATCell *Track,
    CATCell *CellSupp,
    CATVertex *Cible,
    CATCell *CommonCell,
    CATCell *CellSupp2,
    double &gaptang,
    double &gapcell,
    CATGeometry *iGeoRef,
    CATBoolean *oGTPSComputed,
    double *oGapTangPS) = 0;

  virtual void CATPGMGetBorderCells(
    CATCell *iCell,
    CATDomain *iDomain,
    CATLISTP(CATCell) &oBorderCell,
    CATSide *&oSide) = 0;

  virtual CATDomain *CATPGMGetDomainOfBorderCell(
    CATBody *iBody,
    CATLoop *iLoop,
    CATEdge *iEdge,
    CATFace *iFace,
    CATBoolean *oDomainFoundWithProvidedEdge) = 0;

  virtual void CATPGMAddPCurveToEdge(
    CATGeoFactory *iGeoFactory,
    CATEdge *iEdge,
    CATEdgeCurve *iEdgeCurve,
    CATPCurve *iPCurve,
    CATTopSign iOrientationOnPCurve,
    CATBoolean iForceAdd) = 0;

  virtual CATEdge *CATPGMCreateEdge(
    CATBody *iCreationBody,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iOrientation,
    CATPointOnEdgeCurve *iStartPOEC,
    CATVertex *iStartVertex,
    CATPointOnEdgeCurve *iEndPOEC,
    CATVertex *iEndVertex,
    CATFace *iFace) = 0;

  virtual void CATPGMFollowEdgeAndRatio(
    CATTopData *iTopData,
    CATEdge *iEdgeToFollow,
    double iRatio,
    CATCGMJournalList &iPrivateEdgesJournal,
    CATEdge *&oEdge,
    double &oRatio) = 0;

  virtual void CATCGMDynFilletRibbon_GetOptions(
    CATDynFilletRibbon &iThis,
    CATBody *iPart,
    CATBlendParams &oBlendParams) = 0;

  virtual void CATCGMGetVariableFilletLaws(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSpine,
    CATLISTP(CATDynFilletRadius) *iRadiusList,
    int iRadiusLawMode,
    CATCompositeLaw *&opMappingLaw,
    CATCompositeLaw *&opRadiusLaw) = 0;

  virtual CATCompositeLaw *CATCGMDynVariableFilletLaw_ExtendVariableFilletLaw(
    CATDynVariableFilletLaw &iThis,
    CATGeoFactory *iFactory,
    CATCompositeLaw *iLaw,
    double iStart,
    double iEnd) = 0;

  virtual CATIPGMTopDevelop *CATPGMCreateTopOpDevelop(
    CATGeoFactory *iFactory,
    CATBody *iWire,
    CATBody *iWireSupport,
    CATBody *iTargetSupport,
    CATICGMSurTo2DGlobalMapping *iMappingIn,
    CATICGMSurTo2DGlobalMapping *iMappingOut,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMTopDevelop *CATPGMCreateTopOpDevelop(
    CATGeoFactory *iFactory,
    CATBody *iWire,
    CATBody *iWireSupport,
    CATBody *iTargetSupport,
    CATICGMSurTo2DGlobalMapping *iMappingIn,
    CATICGMSurTo2DGlobalMapping *iMappingOut,
    CATTopData *iData) = 0;

  virtual CATPlane *CATTopBeamInverseBend_CATCGMFindOutBeamSupportPlane(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBeamWire) = 0;

  virtual CATPGMTopBeamInverseBend *CATPGMCreateTopBeamInverseBend(
    CATGeoFactory *iWorkingFactory,
    CATSoftwareConfiguration *iConfig,
    CATBody *iBeamWire,
    CATPlane *iBeamSupportPlane,
    const CATLength iBeamThicknesses[2],
    const CATPositiveLength iMaxLineLength,
    const CATPositiveLength iLineOverlap) = 0;

  virtual const CATString *CATSkinExtrapolThickPlus_CATPGMGetDefaultOperatorId() = 0;

  virtual CATIPGMSkinExtrapolThickPlus *CATPGMCreateSkinExtrapolThickPlus(
    CATBody *iSkin,
    CATTopData *iTopData) = 0;

  virtual CATIPGMTopRibbonHomotopy *CATPGMTopCreateRibbonHomotopy(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATFace *iLeftFace,
    CATFace *iRightFace,
    CATFace *iCentreFace,
    const CATOrientation *iOri,
    const CATMathDirection *iDir,
    const CATMathPoint &iPoint,
    CATIPGMConnectTool *iProfilePtr) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOpe3rators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr3 *CATCGMGetTopologicalOpeItfBldr3();

#endif /* CATIPGMTopologicalOpeItfBldr3_h */
