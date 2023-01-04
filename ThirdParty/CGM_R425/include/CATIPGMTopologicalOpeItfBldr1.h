#ifndef CATIPGMTopologicalOpeItfBldr1_h
#define CATIPGMTopologicalOpeItfBldr1_h

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

class CATICGMBodyChecker;
class CATGeoFactory;
class CATTopData;
class CATBody;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATICGMCloseOperator;
class CATIPGMCloseOperator;
class CATICGMHybAssemble;
class CATIPGMHybAssemble;
class CATICGMDynBoolean;
class CATIPGMDynBoolean;
class CATCGMJournalList;
class CATICGMDynChamfer;
class CATIPGMDynChamfer;
class CATICGMDynDraft;
class CATIPGMDynDraft;
class CATICGMDynFillet;
class CATIPGMDynFillet;
class CATWire;
class CATCell;
class CATMathDirection;
class CATFace;
class CATGeometry;
class CATEdge;
class CATICGMDynShell;
class CATIPGMDynShell;
class CATICGMDynSplit;
class CATIPGMDynSplit;
class CATICGMDynThickness;
class CATIPGMDynThickness;
class CATICGMDynTransformation;
class CATIPGMDynTransformation;
class CATIPGMRemoveEdgePlusOpe;

class CATCompositeLaw;
class CATLaw;
class CATSoftwareConfiguration;

class CATICGMExtrapolateBody;
class CATIPGMExtrapolateBody;
class CATSurface;
class CATICGMSkinExtrapol;
class CATIPGMSkinExtrapol;
class CATICGMSolidCuboid;
class CATIPGMSolidCuboid;
class CATMathPoint;
class CATICGMSolidCylinder;
class CATIPGMSolidCylinder;
class CATICGMSolidPyramid;
class CATIPGMSolidPyramid;

class CATIPGMSolidTorus;
class CATICGMSolidTorus;
class CATMathAxis;
class CATICGMTopBodyExtremum;
class CATIPGMTopBodyExtremum;
class CATMathVector;
class CATICGMTopCorner;
class CATIPGMTopCorner;
class CATICGMTopDevelop;
class CATIPGMTopDevelop;
class CATICGMTopExtrapolWireOnShell;
class CATIPGMTopExtrapolWireOnShell;
class CATCGMStream;

class CATICGMTopPrism;
class CATIPGMTopPrism;
class CATICGMTopRevol;
class CATIPGMTopRevol;
class CATICGMTopSimplify;
class CATIPGMTopSimplify;
class CATPCurve;
class CATCrvLimits;
class CATSurLimits;
class CATICGMTopSweepSkinSkinSegment;
class CATIPGMTopSweepSkinSkinSegment;
class CATICGMTopSweepWireSkin;
class CATIPGMTopSweepWireSkin;
class CATICGMTopSweepWireSkinCircle;
class CATIPGMTopSweepWireSkinCircle;
class CATICGMTopVertex;
class CATIPGMTopVertex;
class CATPoint;
class CATCurve;
class CATICGMWireExtrapolationOp;
class CATIPGMWireExtrapolationOp;
class CATICGMDistanceMinBodyBody;
class CATIPGMDistanceMinBodyBody;
class CATIPGMDynMassProperties3D;
class CATLISTP(CATDomain);
class CATICGMSurTo2DGlobalMapping;
class CATICGMDynMassProperties3D;
class CATLISTP(CATFace);
class CATLISTP(CATBody);
class CATIPGMBasicFastRun;
class CATIPGMAdvancedFastRun;
class CATContextForFastRun;
class CATEdgeRibbon;
class CATDynFilletRadius;
class CATDynEdgeFilletRibbon;
class CATIPGMConnectTool;
class CATLISTP(CATDynFilletRibbon);
class CATLISTP(CATEdge);
class CATIPGMMassProperties3DAPP;
class CATIPGMCavityExtractOperator;
class CATIPGMFluidRegionLidOperator;

#define CATICGMTopSweepWireSkinSegment CATICGMTopSweepWireSkin
#define CATIPGMTopSweepWireSkinSegment CATIPGMTopSweepWireSkin

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalOpeItfBldr1;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr1: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATICGMBodyChecker *CATBodyChecker_CATCGMCreate(
    CATGeoFactory *ipFactory,
    CATTopData *ipData,
    CATBody *ipBodyToCheck) = 0;

  virtual CATBoolean CATBodyChecker_CATCGMCheck(
    CATGeoFactory *ipFactory,
    CATBody *ipBodyToCheck,
    CATLONG32 &ioNumberOfSevereAnomalies,
    ostream &ioDetailsOfAnomalies,
    const CATBoolean &ibFullCheck) = 0;

  virtual CATICGMCloseOperator *CATCGMCreateCloseOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToClose) = 0;

  virtual CATIPGMCloseOperator *CATPGMCreateCloseOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToClose) = 0;

  virtual CATICGMDynBoolean *CATCGMCreateDynBoolean(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDynBooleanType iOperation,
    CATBody *iPart,
    CATBody *iTool) = 0;

  virtual CATIPGMDynBoolean *CATPGMDynCreateBoolean(
    CATGeoFactory *iFactory,
    CATDynBooleanType iOperation,
    CATBody *iPart,
    CATBody *iTool,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynBoolean *CATPGMCreateDynBoolean(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDynBooleanType iOperation,
    CATBody *iPart,
    CATBody *iTool) = 0;

  virtual CATICGMDynChamfer *CATCGMCreateDynChamfer(
    CATGeoFactory *Container,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynChamfer *CATPGMCreateDynChamfer(
    CATGeoFactory *Container,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATICGMDynDraft *CATCGMCreateDynDraft(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    const CATDynDraftType iType) = 0;

  virtual CATIPGMDynDraft *CATPGMCreateDynDraft(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    const CATDynDraftType iType) = 0;

  virtual CATICGMDynFillet *CATCGMCreateDynFillet(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynFillet *CATPGMCreateDynFillet(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATICGMDynMassProperties3D *CATCGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATEdge *iEdgeToAnalyze) = 0;

  virtual CATICGMDynMassProperties3D *CATCGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATFace *iFaceToAnalyze) = 0;

  virtual CATICGMDynMassProperties3D *CATCGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATBody *iToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(const CATBody *iToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
    const CATFace *iFaceToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
    const CATEdge *iEdgeToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATBody *iToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATFace *iFaceToAnalyze) = 0;

  virtual CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
    class CATTopData *iTopData,
    const CATEdge *iEdgeToAnalyze) = 0;

  virtual CATICGMDynShell *CATCGMCreateDynShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLength iInternal,
    CATLength iExternal) = 0;

  virtual CATIPGMDynShell *CATPGMCreateDynShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLength iInternal,
    CATLength iExternal) = 0;

  virtual CATICGMDynSplit *CATCGMCreateDynSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody,
    CATDynSplitType iSplitType) = 0;

#ifdef CATIACGMR215CAA
  virtual CATICGMDynSplit *CATCGMCreateDynSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody,
    CATDynSplitType iSplitType,
    CATDynSelectionMode iSelectionMode) = 0;
#endif

  virtual CATIPGMDynSplit *CATPGMDynCreateSplit(
    CATGeoFactory *iFactory,
    CATBody *iBody,
    CATDynSplitType iSplitType,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynSplit *CATPGMCreateDynSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody,
    CATDynSplitType iSplitType) = 0;

  virtual CATICGMDynThickness *CATCGMCreateDynThickness(
    CATGeoFactory *iContainer,
    CATTopData *iTopData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynThickness *CATPGMCreateDynThickness(
    CATGeoFactory *iContainer,
    CATTopData *iTopData,
    CATBody *iPart) = 0;

  virtual CATICGMDynTransformation *CATCGMCreateDynTransformation(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodytoTransform) = 0;

  virtual CATIPGMDynTransformation *CATPGMDynCreateTransformation(
    CATGeoFactory *iFactory,
    CATBody *iBodytoTransform,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynTransformation *CATPGMDynCreateTransformation(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodytoTransform) = 0;

  virtual CATIPGMDynTransformation *CATPGMCreateDynTransformation(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodytoTransform) = 0;

  virtual CATICGMExtrapolateBody *CATCGMCreateExtrapolateBody(
    CATGeoFactory *iGeoFactory,
    CATTopData *iTopData,
    CATBody *iBodyToExtrapol,
    CATSurface *iSupport,
    double iMinimumGap) = 0;

  virtual CATIPGMExtrapolateBody *CATPGMCreateExtrapolateBody(
    CATGeoFactory *iGeoFactory,
    CATTopData *iTopData,
    CATBody *iBodyToExtrapol,
    CATSurface *iSupport,
    double iMinimumGap) = 0;

  virtual CATICGMSkinExtrapol *CATCGMCreateSkinExtrapol(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSkin) = 0;

  virtual CATIPGMSkinExtrapol *CATPGMCreateSkinExtrapol(
    CATBody *iSkin,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMSkinExtrapol *CATPGMCreateSkinExtrapol(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSkin) = 0;

  virtual CATICGMSolidCuboid *CATCGMCreateSolidCuboid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iPt4) = 0;

  virtual CATIPGMSolidCuboid *CATPGMCreateSolidCuboid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iPt4) = 0;

  virtual CATICGMSolidCylinder *CATCGMCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    double iRadius) = 0;

  virtual CATICGMSolidCylinder *CATCGMCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    const CATMathPoint &iPointOnSurface) = 0;

  virtual CATIPGMSolidCylinder *CATPGMCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    double iRadius) = 0;

  virtual CATIPGMSolidCylinder *CATPGMCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    const CATMathPoint &iPointOnSurface) = 0;

  virtual CATICGMSolidPyramid *CATCGMCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATFace *iBase,
    const CATMathPoint &iTop) = 0;

  virtual CATICGMSolidPyramid *CATCGMCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iTop) = 0;

  virtual CATIPGMSolidPyramid *CATPGMCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATFace *iBase,
    const CATMathPoint &iTop) = 0;

  virtual CATIPGMSolidPyramid *CATPGMCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iTop) = 0;

  virtual CATICGMSolidTorus *CATCGMCreateSolidTorus(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathAxis &iAxis,
    const CATMathPoint &iMajor,
    const CATMathPoint &iMinor) = 0;

  virtual CATIPGMSolidTorus *CATPGMCreateSolidTorus(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathAxis &iAxis,
    const CATMathPoint &iMajor,
    const CATMathPoint &iMinor) = 0;

  virtual CATICGMTopBodyExtremum *CATCGMCreateDirBodyExtremum(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;

  virtual CATIPGMTopBodyExtremum *CATPGMCreateDirBodyExtremum(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;

  virtual CATICGMTopCorner *CATCGMCreateTopCorner(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iCurve1,
    CATBody *iCurve2,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCorner(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iCurve1,
    CATBody *iCurve2,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATICGMTopDevelop *CATCGMCreateTopDevelop(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iWire,
    CATBody *iWireSupport,
    CATBody *iTargetSupport,
    CATICGMSurTo2DGlobalMapping *iMappingIn,
    CATICGMSurTo2DGlobalMapping *iMappingOut) = 0;

  virtual CATIPGMTopDevelop *CATPGMCreateTopDevelop(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iWire,
    CATBody *iWireSupport,
    CATBody *iTargetSupport,
    CATICGMSurTo2DGlobalMapping *iMappingIn,
    CATICGMSurTo2DGlobalMapping *iMappingOut) = 0;

  virtual CATICGMTopExtrapolWireOnShell *CATCGMCreateTopExtrapolWireOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyWire,
    CATBody *iBodyShell) = 0;

  virtual CATIPGMTopExtrapolWireOnShell *CATPGMCreateTopExtrapolWireOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyWire,
    CATBody *iBodyShell) = 0;

  virtual CATICGMTopPrism *CATCGMCreateTopPrism(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iProfileBody,
    CATMathDirection *iDirection,
    CATLength iStartOffset,
    CATLength iEndOffset) = 0;

  virtual CATIPGMTopPrism *CATPGMTopCreatePrism(
    CATGeoFactory *iFactory,
    CATBody *iProfileBody,
    CATMathDirection *iDirection,
    CATLength iStartOffset,
    CATLength iEndOffset,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMTopPrism *CATPGMCreateTopPrism(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iProfileBody,
    CATMathDirection *iDirection,
    CATLength iStartOffset,
    CATLength iEndOffset) = 0;

  virtual CATICGMTopRevol *CATCGMCreateTopRevol(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iProfile,
    CATMathAxis *iAxis,
    CATAngle iStartAngle,
    CATAngle iEndAngle) = 0;

  virtual CATIPGMTopRevol *CATPGMTopCreateRevol(
    CATGeoFactory *iFactory,
    CATBody *iProfile,
    CATMathAxis *iAxis,
    CATAngle iStartAngle,
    CATAngle iEndAngle,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMTopRevol *CATPGMCreateTopRevol(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iProfile,
    CATMathAxis *iAxis,
    CATAngle iStartAngle,
    CATAngle iEndAngle) = 0;

  virtual CATICGMTopSimplify *CATCGMCreateTopSimplify(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSimplify) = 0;

  virtual CATIPGMTopSimplify *CATPGMCreateTopSimplify(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSimplify) = 0;
	
#if !defined(CATIAV5R28) && !defined(CATIAR420)
  virtual const CATString *CATTopSweepSkinSkinSegment_CATCGMGetDefaultOperatorId() = 0;
#endif

  virtual CATICGMTopSweepSkinSkinSegment *CATCGMCreateTopSweepSkinSkinSegment(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstSupportShell,
    CATBody *iSecondSupportShell,
    CATBody *iSpine) = 0;

  virtual CATIPGMTopSweepSkinSkinSegment *CATPGMCreateTopSweepSkinSkinSegment(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstSupportShell,
    CATBody *iSecondSupportShell,
    CATBody *iSpine) = 0;

  virtual CATIPGMTopSweepWireSkin *CATPGMCreateTopSweepWireSkin(
    CATGeoFactory *iFactory,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine) = 0;

  virtual CATIPGMTopSweepWireSkin *CATPGMCreateTopSweepWireSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine) = 0;

  virtual const CATString *CATTopSweepWireSkinCircle_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMTopSweepWireSkinCircle *CATPGMCreateTopSweepWireSkinCircle(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine,
    CATLaw *iRadiusLaw,
    CATBoolean iRemoveGuide,
    CATBoolean iRemoveSpine) = 0;

  virtual CATIPGMTopSweepWireSkinCircle *CATPGMCreateTopSweepWireSkinCircle(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine,
    double iRadius) = 0;

  virtual CATICGMTopSweepWireSkinSegment *CATCGMCreateTopSweepWireSkinSegment(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine) = 0;

  virtual CATIPGMTopSweepWireSkinSegment *CATPGMCreateTopSweepWireSkinSegment(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATBody *iGuide,
    CATBody *iSpine) = 0;

  virtual CATICGMWireExtrapolationOp *CATCGMCreateWireExtrapolationOp(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToExtrapolate) = 0;

  virtual CATIPGMWireExtrapolationOp *CATPGMCreateWireExtrapolationOp(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToExtrapolate) = 0;

  virtual CATIPGMCloseOperator *CATPGMCreateCloseOperator(
    CATGeoFactory *iFactory,
    CATBody *iBodyToClose,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMCloseOperator *CATPGMCreateCloseOperator(
    CATGeoFactory *iFactory,
    CATBody *iBodyToClose,
    CATTopData *iTopData) = 0;

  virtual CATIPGMBasicFastRun *CATPGMCreateBasicFastRun(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATError** iopError) = 0;

  virtual CATIPGMBasicFastRun *CATPGMCreateBasicFastRun(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATContextForFastRun *ipContext,
    CATError** iopError) = 0;

  virtual CATIPGMAdvancedFastRun *CATPGMCreateAdvancedFastRun(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATError** iopError) = 0;

  virtual CATIPGMAdvancedFastRun *CATPGMCreateAdvancedFastRun(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATContextForFastRun *ipContext,
    CATError** iopError) = 0;


  virtual CATICGMSolidCuboid *CATCGMTopCreateSolidCuboid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iPt4) = 0;

  virtual CATIPGMSolidCuboid *CATPGMTopCreateSolidCuboid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iPt4) = 0;

  virtual CATICGMSolidCylinder *CATCGMTopCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    const CATMathPoint &iPointOnSurface) = 0;

  virtual CATICGMSolidCylinder *CATCGMTopCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    double iRadius) = 0;

  virtual CATIPGMSolidCylinder *CATPGMTopCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    const CATMathPoint &iPointOnSurface) = 0;

  virtual CATIPGMSolidCylinder *CATPGMTopCreateSolidCylinder(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iFirstPointOnAxis,
    const CATMathPoint &iSecondPointOnAxis,
    double iRadius) = 0;

  virtual CATICGMSolidPyramid *CATCGMTopCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iTop) = 0;

  virtual CATICGMSolidPyramid *CATCGMTopCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATFace *iBase,
    const CATMathPoint &iTop) = 0;

  virtual CATIPGMSolidPyramid *CATPGMTopCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iPt1,
    const CATMathPoint &iPt2,
    const CATMathPoint &iPt3,
    const CATMathPoint &iTop) = 0;

  virtual CATIPGMSolidPyramid *CATPGMTopCreateSolidPyramid(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATFace *iBase,
    const CATMathPoint &iTop) = 0;

  virtual CATICGMSolidTorus *CATCGMTopCreateSolidTorus(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathAxis &iAxis,
    const CATMathPoint &iMajor,
    const CATMathPoint &iMinor) = 0;

  virtual CATIPGMSolidTorus *CATPGMTopCreateSolidTorus(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathAxis &iAxis,
    const CATMathPoint &iMajor,
    const CATMathPoint &iMinor) = 0;

  virtual HRESULT CATTopRibbonHomotopy_CATPGMGetRadiusAtPoint(
    CATSoftwareConfiguration *iConfig,
    CATBody *iCreationBody,
    CATBody *iInitialBody,
    CATLISTP(CATDynFilletRibbon) &iFilletSpecs,
    CATDynFilletRadius *&ioRadius) = 0;

  virtual CATEdgeRibbon *CATTopRibbonHomotopy_CATPGMGetEdgeRibbonFromSpecs(
    CATSoftwareConfiguration *iConfig,
    CATBody *iResult,
    CATBody *iSpecsBody,
    CATEdge *iEdge,
    CATLISTP(CATDynFilletRibbon) &iEdgeFilletsSpecs,
    CATLISTP(CATDynFilletRibbon) *iEdgeFilletsNotToLookAt,
    CATBoolean &iTestWithoutParting,
    CATDynEdgeFilletRibbon *&oFoundSpec,
    CATListPV &oRadiusAlloues,
    CATBoolean &oVariable) = 0;

  virtual CATICGMTopBodyExtremum *CATCGMCreateDirNewBodyExtremum(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;

  virtual CATIPGMTopBodyExtremum *CATPGMCreateDirNewBodyExtremum(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;

  virtual CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
    class CATTopData *iTopData,
    const CATBody *iToAnalyze) = 0;

  virtual CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
    class CATTopData *iTopData,
    const CATFace *iFaceToAnalyze) = 0;

  virtual CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
    class CATTopData *iTopData,
    const CATEdge *iEdgeToAnalyze) = 0;

  virtual CATIPGMDynBoolean *CATPGMCreateBooleanDelta(
    CATGeoFactory *ipFactory,
    CATTopData *ipData,
    CATBody *ipPart,
    CATBody *ipTool) = 0;

  virtual CATIPGMRemoveEdgePlusOpe *CATPGMCreateRemoveEdgePlusOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iReferenceBody) = 0;

  virtual CATIPGMRemoveEdgePlusOpe *CATPGMCreateRemoveEdgePlusOpe(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iReferenceBody) = 0;
  
  virtual CATIPGMConnectTool *CATTopRibbonHomotopy_CATPGMGetToolFromSpecs(
    CATSoftwareConfiguration *iConfig,
    CATBody *iCreationBody,
    CATBody *iInitialBody,
    CATLISTP(CATDynFilletRibbon) &iFilletSpecs,
    CATEdge *iEdge) = 0;

  virtual CATIPGMCavityExtractOperator *CATPGMCreateCavityExtractOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) &iSolidContainerBodyList,
    CATLISTP(CATBody) &iLidBodyList) = 0;

  virtual CATIPGMFluidRegionLidOperator* CATPGMCreateFluidRegionLidOperator(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATLISTP(CATBody)& iSolidContainerBodyList,
    CATLISTP(CATEdge)& iEdgeList) = 0;

  virtual CATIPGMFluidRegionLidOperator* CATPGMCreateFluidRegionLidOperator(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATLISTP(CATBody)& iSolidContainerBodyList,
    CATFace* iFace) = 0;

  virtual CATIPGMFluidRegionLidOperator* CATPGMCreateFluidRegionLidOperator(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATLISTP(CATBody)& iSolidContainerBodyList) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr1 *CATCGMGetTopologicalOpeItfBldr1();

#endif /* CATIPGMTopologicalOpeItfBldr1_h */
