#ifndef CATIPGMTopoOpeLightItfBldr_h
#define CATIPGMTopoOpeLightItfBldr_h

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCollec.h"
#include "CATICGMHybSplit.h"
#include "CATIPGMHybSplit.h"
#include "CATBodyFreezeMode.h"
#include "CATSkillValue.h"
#include "CATHybDef.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"
#include "CATErrorDef.h" // HRESULT
#include "CATTopToolsGapCheckMode.h"
#include "CATDynValidShell.h"
#include "CATDistanceBodyBodyDef.h"
#include "CATSelectEdgePropagateMode.h"

class CATICGMDistanceMinBodyBody;
class CATIPGMDistanceMinBodyBody;
class CATIPGMEdgeOperator;
class CATIPGMEuclidianDistanceTool;
class CATIPGMExtrapParCornerTool;
class CATIPGMDistanceTool;
class CATICGMDistanceTool;
class CATIPGMExtrapParTangencyTool;
class CATICGMExtrapolParallelTool;
class CATIPGMExtrapolParallelTool;
class CATICGMDistanceTool;
class CATIPGMFaceOperator;
class CATICGMHybAssemble;
class CATIPGMHybAssemble;
class CATIPGMHybSplit;
class CATICGMHybTrim;
class CATICGMHybDisconnect;
class CATIPGMHybTrim;
class CATIPGMHybDisconnect;
class CATICGMHybBoundary;
class CATIPGMHybBoundary;
class CATIPGMDistanceTool;
class CATICGMHybIntersect;
class CATIPGMHybIntersect;
class CATICGMHybProject;
class CATIPGMHybProject;
class CATIPGMTopIntersectByMultiBodies;
class CATICGMLayDownOperator;
class CATIPGMLayDownOperator;
class CATIPGMSkinOperator;
class CATICGMSolidSphere;
class CATIPGMSolidSphere;
class CATIPGMTopCircle;
class CATIPGMTopGeodesicPtPt;
class CATICGMSketchGeodesic;
class CATIPGMSketchGeodesic;
class CATIPGMTopCompatible;
class CATICGMTopCompatible;
class CATICGMTopParallel;
class CATIPGMTopParallel;
class CATIPGMTopParallelFreeze;
class CATIPGMTopProjection;
class CATICGMTopSkin;
class CATIPGMTopSkin;
class CATIPGMTopBoundaryHomogenize;
class CATIPGMTopCoincidentEdgesFinder;
class CATIPGMTopCurveChecker;
class CATIPGMVertexOperator;
class CATICGMTopWire;
class CATIPGMTopWire;
class CATIPGMTopWireExtr;
class CATPGMWireAnalysis;
class CATIPGMWireOperator;
class CATPGMWireStatus;
class CATIPGMRemoveFacesInShell;
class CATICGMTopVertex;
class CATIPGMTopVertex;
class CATIPGMExtractCellsOpe;
class CATIPGMSelectEdgeOpe;

class CATGeoFactory;
class CATGeometry;
class CATError;
class CATTopology;
class CATBody;
class CATDomain;
class CATShell;
class CATFace;
class CATEdge;
class CATVertex;
class CATLoop;
class CATWire;
class CATCell;
class CATPoint;
class CATMacroPoint;
class CATPointOnSurface;
class CATPointOnEdgeCurve;
class CATPointOnCurve;
class CATCurve;
class CATEdgeCurve;
class CATPCurve;
class CATSurface;
class CATFilletSurface;
class CATLaw;
class CATICGMObject;
class CATTopData;
class CATCompositeLaw;
class CATCrvLimits;
class CATCGMJournalList;
class CATLISTP(CATBody);
class CATMathDirection;
class CATMathAdvancedBox;
class CATLISTP(CATCell);
class CATMathBox;
class CATMathPoint;
class CATSurParam;
class CATPlane;
class CATMathVector;
class CATDynMassProperties1DOnEdge;
class CATSimplifyParallelTool;
class CATListPtrCATEdge;
class CATListPtrCATFace;
class CATPGMCheckValidSkin;
class CATIPGMSplitBySurfaceOperator;
class CATMathTransformation;
class CATIPGMDistanceBodyBody;
class CATIPGMExtrapolOpWireOnShell;
class CATICGMRemoveFacesInShell;
class CATIPGMDistanceBodyBody2;
class CATICGMDistancePointBody;
class CATIPGMDistancePointBody;
class CATICGMDistanceBodyBody;
class CATIPGMTopHealOperator;
class CATLISTP(CATTopology);



extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopoOpeLightItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperatorsLight.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopoOpeLightItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCell *iCell1,
    CATCell *iCell2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATCell *iCell1,
    CATCell *iCell2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDomain *iDomain1,
    CATDomain *iDomain2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATDomain *iDomain1,
    CATDomain *iDomain2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATBody *iBody1,
    CATBody *iBody2,
    CATSkillValue iMode) = 0;

  virtual CATICGMDistanceMinBodyBody *CATCGMCreateDistanceMinTopo(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2,
    CATSkillValue iMode) = 0;

  virtual CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinBodyBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCurve *iCurve,
    const CATCrvLimits &iCrvLims) = 0;

  virtual CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
    CATGeoFactory *factory,
    CATCurve *curve,
    CATBody *bodyforcellcreation,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMEdgeOperator *CATPGMCreateEdgeOperator(
    CATGeoFactory *factory,
    CATTopData *iData,
    CATCurve *curve,
    CATBody *bodyforcellcreation) = 0;

#ifndef CATIACGMR214CAA
  virtual CATICGMDistanceTool *CATCGMCreateTopEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;
#else
  virtual CATICGMDistanceTool *CATCGMCreateTopEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;
#endif

  virtual CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;

  virtual CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;

  virtual CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;

  virtual CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;

  virtual CATIPGMExtrapParCornerTool *CATPGMCreateExtrapParCornerTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATICGMDistanceTool *iDist,
    CATBody *iShFond) = 0;

  virtual CATIPGMExtrapParTangencyTool *CATPGMCreateExtrapParTangencyTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATICGMDistanceTool *iDist,
    CATBody *iShFond) = 0;

  virtual CATICGMExtrapolParallelTool *CATCGMCreateExtrapolParallelTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATICGMDistanceTool *iDist,
    CATBody *iSkinBody,
    int iRelimitType) = 0;

  virtual CATIPGMExtrapolParallelTool *CATPGMCreateExtrapolParallelTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATICGMDistanceTool *iDist,
    CATBody *iSkinBody,
    int iRelimitType) = 0;

  virtual CATIPGMFaceOperator *CATPGMCreateFaceOperator(
    CATGeoFactory *factory,
    CATTopData *iData,
    int nbpcurves,
    CATPCurve **pcurves) = 0;

  virtual CATIPGMFaceOperator *CATPGMCreateFaceOperator(
    CATGeoFactory *factory,
    int nbpcurves,
    CATPCurve **pcurves,
    CATBody *targetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMFaceOperator *CATPGMCreateFaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATSurface *iSurface) = 0;

  virtual CATIPGMFaceOperator *CATPGMCreateFaceOperator(
    CATGeoFactory *factory,
    CATSurface *surface,
    CATBody *targetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

#ifndef CATIACGMR214CAA
  virtual CATICGMDistanceTool *CATCGMCreateTopGeodesicDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;
#else
  virtual CATICGMDistanceTool *CATCGMCreateTopGeodesicDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;
#endif

  virtual CATICGMHybAssemble *CATCGMCreateNewTopAssemble(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody)* iBodiesToAssemble) = 0;

  virtual CATICGMHybAssemble *CATCGMCreateTopAssemble(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody)* iBodiesToAssemble) = 0;

  virtual CATIPGMHybAssemble *CATPGMCreateNewTopAssemble(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody)* iBodiesToAssemble) = 0;

  virtual CATIPGMHybAssemble *CATPGMCreateTopAssemble(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody)* iBodiesToAssemble) = 0;

  virtual CATICGMHybBoundary *CATCGMCreateTopBoundary(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *inputBody,
    CATDomain *inputDomain,
    CATCell *initialCell,
    CATHybPropagateMode iPropagateMode) = 0;

  virtual CATIPGMHybBoundary *CATPGMCreateTopBoundary(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *inputBody,
    CATDomain *inputDomain,
    CATCell *initialCell,
    CATHybPropagateMode iPropagateMode) = 0;

  virtual CATICGMHybDisconnect *CATCGMCreateTopDisconnect(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybDisconnect *CATPGMCreateTopDisconnect(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody,
    CATBody *iCuttingBody) = 0;

  virtual CATICGMHybDisconnect *CATCGMCreateTopDisconnectShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody) = 0;

  virtual CATICGMHybDisconnect *CATCGMCreateTopDisconnectWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody) = 0;

  virtual CATIPGMHybDisconnect *CATPGMCreateTopDisconnectShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody) = 0;

  virtual CATIPGMHybDisconnect *CATPGMCreateTopDisconnectWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToDisconnect,
    CATBody *iDisconnectingBody) = 0;

  virtual CATICGMHybIntersect *CATCGMCreateTopIntersect(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1ToIntersect,
    CATBody *iBody2ToIntersect) = 0;

  virtual CATIPGMHybIntersect *CATPGMCreateTopIntersect(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1ToIntersect,
    CATBody *iBody2ToIntersect) = 0;

  virtual CATICGMHybProject *CATCGMCreateTopProject(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToProject,
    CATBody *iBodySupport,
    CATMathDirection *iDirection) = 0;

  virtual CATIPGMHybProject *CATPGMCreateTopProject(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToProject,
    CATBody *iBodySupport,
    CATMathDirection *iDirection) = 0;

  virtual CATIPGMHybProject *CATPGMCreateTopPoseSur(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToProject,
    CATBody *iBodySupport) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitWireWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitWireWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSplit,
    short iSideToKeep,
    CATBody *iSplittingBody,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSplit,
    CATBody *iSplittingBody,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplit(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSplit,
    short iSideToKeep,
    CATBody *iSplittingBody,
    CATBody *iCuttingBody) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopSplitOnSupport(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSplit,
    short iSideToKeep,
    CATBody *iSplittingBody,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopSplitOnSupport(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSplit,
    short iSideToKeep,
    CATBody *iSplittingBody,
    CATBody *iBodySupport) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopNewSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATICGMHybSplit *CATCGMCreateTopNewSplitWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopNewSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopNewSplitWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATIPGMHybSplit *CATPGMCreateTopNewSplitShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCut,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode,
    double iTol,
    CATBoolean iSingleExtrapolMode) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimWireWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimWireWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimShellWithKeepRemove(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimShellWithWirePositionning(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATBody *iCuttingBody,
    CATHybSelectionMode iSelectMode) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimShell(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToTrim,
    CATBody *iTrimmingBody,
    CATHybSelectionMode iSelectMode,
    CATHybExtrapolationMode iExtrapolMode) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrim(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstBodyToCut,
    short iFirstSideToKeep,
    CATBody *iSecondBodyToCut,
    short iSecondSideToKeep,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrim(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstBodyToCut,
    CATBody *iSecondBodyToCut,
    CATBody *iCuttingBody) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrim(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstBodyToCut,
    short iFirstSideToKeep,
    CATBody *iSecondBodyToCut,
    short iSecondSideToKeep,
    CATBody *iCuttingBody) = 0;

  virtual CATICGMHybTrim *CATCGMCreateTopTrimOnSupport(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstBodyToCut,
    short iFirstSideToKeep,
    CATBody *iSecondBodyToCut,
    short iSecondSideToKeep,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMHybTrim *CATPGMCreateTopTrimOnSupport(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iFirstBodyToCut,
    short iFirstSideToKeep,
    CATBody *iSecondBodyToCut,
    short iSecondSideToKeep,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMTopIntersectByMultiBodies *CATPGMCreateTopIntersectByMultiBodies(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopdata,
    CATBody *iBodyToIntersect,
    const CATLISTP(CATBody) &iListOfIntersectingBodies) = 0;

  virtual const CATString *CATLayDownOperator_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMLayDownOperator *CATPGMCreateLayDownOperator(
    CATGeoFactory *iFactory,
    CATBody *iBodyWireOrVertex,
    CATBody *iBodyShellOrWire,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMLayDownOperator *CATPGMCreateLayDownOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyWireOrVertex,
    CATBody *iBodyShellOrWire) = 0;

  virtual CATICGMLayDownOperator *CATCGMCreateTopLayDown(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToLayDown,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMLayDownOperator *CATPGMCreateTopLayDown(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToLayDown,
    CATBody *iBodySupport) = 0;

  virtual const CATString *CATRemoveFacesInShell_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMRemoveFacesInShell *CATPGMCreateRemoveFacesInShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATCell) *iFacesToRemove) = 0;

  virtual CATIPGMTopBoundaryHomogenize *CATPGMCreateTopBoundaryHomogenize(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopdata,
    CATBody *ipGlobalBody,
    const CATLISTP(CATBody) &iBodies,
    double iTol) = 0;
	
  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *factory,
    int nbpcurves,
    CATPCurve **pcurves,
    short *orientations,
    CATBody *targetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *factory,
    int nbpcurves,
    CATPCurve **pcurves,
    CATBody *targetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *factory,
    CATTopData *iData,
    int nbpcurves,
    CATPCurve **pcurves,
    CATCrvLimits *limits) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *factory,
    int nbpcurves,
    CATPCurve **pcurves,
    CATCrvLimits *limits,
    CATBody *targetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPlane *plane,
    CATMathBox &iBox) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    CATPlane *plane,
    CATMathBox &iBox,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATCrvLimits *iLimits,
    short *iOrientations,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface) = 0;

  virtual CATIPGMSkinOperator *CATPGMCreateSkinOperator(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATICGMSolidSphere *CATCGMCreateSolidSphere(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iCenter,
    double iRadius) = 0;

  virtual CATIPGMSolidSphere *CATPGMCreateSolidSphere(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iCenter,
    double iRadius) = 0;

  virtual CATIPGMTopCircle *CATPGMCreateTopCircle(
    CATGeoFactory *iFactory,
    CATTopData *iReport,
    CATBody *iCenter,
    CATBody *iSupport,
    CATICGMDistanceTool *iDistance) = 0;

  virtual CATIPGMTopCircle *CATPGMCreateTopCircle(
    CATGeoFactory *iFactory,
    CATTopData *iReport,
    CATBody *iCenter,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATIPGMTopGeodesicPtPt *CATPGMCreateTopGeodesicPtPt(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iPtOrig,
    CATBody *iPtFin,
    CATBody *iShellSupport) = 0;

  virtual CATICGMSketchGeodesic *CATCGMCreateGeodesicPointDir(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATFace *iFaceSupportPoint,
    CATSurParam *iParamPoint,
    CATMathVector *iTangent,
    CATPositiveLength iLength,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSketchGeodesic *CATPGMCreateGeodesicPointDir(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iSupportShell,
    CATFace *iFaceSupportPoint,
    CATSurParam *iParamPoint,
    CATMathVector *iTangent,
    CATPositiveLength iLength,
    CATSkillValue iMode) = 0;

  virtual CATIPGMTopCompatible* CATPGMCreateCompatibleForCGM(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATBody* iBody1,
    CATBody* iBody2) = 0;

  virtual CATIPGMTopCompatible* CATPGMCreateCompatibleForCVM(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATBody* iBody1,
    CATBody* iBody2) = 0;

  virtual CATICGMTopCompatible* CATCGMCreateCompatibleForCGM(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATBody* iBody1,
    CATBody* iBody2) = 0;


  virtual CATIPGMTopCompatible* CATPGMCreateCompatibleForCGM(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATLISTP(CATBody)* iBodyList) = 0;

  virtual CATIPGMTopCompatible* CATPGMCreateCompatibleForCVM(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATLISTP(CATBody)* iBodyList) = 0;

  virtual CATIPGMTopCompatible* CATPGMCreateCompatibleFull(
    CATGeoFactory* iFactory,
    CATTopData* iTopData,
    CATBody* iBody1,
    CATBody* iBody2) = 0;


  virtual CATIPGMTopCompatible* CATPGMCreateCompatible_Kernel(
    CATGeoFactory* ipFactory,
    CATTopData* ipTopData,
    CATLISTP(CATBody)* ipBodyList,
    CATBoolean iNonManifoldAuthorized,
    CATBoolean iFullJournal) = 0;

  virtual CATICGMTopParallel *CATCGMCreateTopParallel(
    CATICGMExtrapolParallelTool *iOption,
    CATBody *iCurve) = 0;

  virtual CATIPGMTopParallel *CATPGMCreateTopParallel(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iCurve,
    CATBody *iSupport,
    CATICGMDistanceTool *iDistance) = 0;

  virtual CATIPGMTopParallel *CATPGMCreateTopParallel(
    CATICGMExtrapolParallelTool *iOption,
    CATBody *iCurve) = 0;

  virtual CATIPGMTopParallelFreeze *CATPGMCreateNONL1Parallel(
    CATICGMExtrapolParallelTool *iOption,
    CATBody *iCurve) = 0;

  virtual CATIPGMTopProjection *CATPGMCreateTopEuclideanProjection(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToProject,
    CATBody *iBodySupport,
    CATMathDirection *iDirection) = 0;

  virtual void CATTopParallelFreeze_CATPGMGetMappings(
    CATGeoFactory *Facto,
    CATTopData *iData,
    CATBody *iWire,
    CATLONG32 &nblaws,
    CATLaw **&MapLaws) = 0;

  virtual CATIPGMTopParallelFreeze *CATPGMCreateNONL1ParallelLight(
    CATICGMExtrapolParallelTool *iOption,
    CATBody *iCurve) = 0;

  virtual CATICGMTopSkin *CATCGMCreateTopSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATICGMTopSkin *CATCGMCreateTopSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    const CATSurLimits *iLims) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATBody *CATPGMCreateSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    const CATSurLimits *iLims) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    const CATSurLimits *iLims) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopOldSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATCrvLimits *iLims,
    CATBody *TargetBody) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopOldSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    int iNbPcurves,
    CATPCurve **iPcurves,
    CATBody *TargetBody) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopOldSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPlane *plane,
    CATMathBox &iBox,
    CATBody *TargetBody) = 0;

  virtual CATIPGMTopSkin *CATPGMCreateTopSkin(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPlane *plane,
    CATMathBox &iBox) = 0;

  virtual CATICGMTopVertex *CATCGMCreateTopVertex(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPoint *iPoint) = 0;

  virtual CATBody *CATPGMCreateVertex(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPoint *iPoint) = 0;

  virtual CATIPGMTopVertex *CATPGMCreateTopVertex(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPoint *iPoint) = 0;

  virtual CATIPGMVertexOperator *CATPGMCreateVertexOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATPoint *iPoint) = 0;

  virtual CATIPGMVertexOperator *CATPGMCreateVertexOperator(
    CATGeoFactory *iFactory,
    CATPoint *iPoint,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *iReport) = 0;

  virtual CATICGMTopWire *CATCGMCreateTopWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATBody *CATPGMCreateWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATIPGMTopWire *CATPGMCreateTopWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATIPGMTopWireExtr *CATPGMCreateTopOldWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATIPGMTopWireExtr *CATPGMCreateTopWire(
    CATGeoFactory *factory,
    CATTopData *iData,
    CATBody *iBody,
    CATVertex *iEndVertex,
    CATCurve *iExtrapolationCurve) = 0;

  virtual CATPGMWireAnalysis *CATPGMCreateWireAnalysis(
    CATWire *iWire,
    CATCompositeLaw *iOffset,
    CATLONG32 ilevel) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *factory,
    CATBody *iBody,
    CATCurve *iExtrapolationCurve,
    CATOrientation iOriNewEdgeVsWire,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *factory,
    CATTopData *iData,
    CATBody *iBody,
    CATVertex *iEndVertex,
    CATCurve *iExtrapolationCurve) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *factory,
    CATBody *iBody,
    CATVertex *iEndVertex,
    CATCurve *iExtrapolationCurve,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *iFactory,
    int inbcurves,
    CATCurve **icurves,
    short *iorientations,
    CATBody *iTargetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *factory,
    CATCurve *icurve,
    CATBody *iTargetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *factory,
    int inbcurves,
    CATCurve **icurves,
    CATBody *iTargetBody,
    CATBodyFreezeMode bodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    short iOrientation,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *report) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations) = 0;

  virtual CATIPGMWireOperator *CATPGMCreateWireOperator(
    CATGeoFactory *iFactory,
    int iNbCurves,
    CATCurve **iCurves,
    CATCrvLimits *iLimits,
    short *iOrientations,
    CATBody *iTargetBody,
    CATBodyFreezeMode iBodyfreezemode,
    CATCGMJournalList *iReport) = 0;

  virtual CATPGMWireStatus *CATPGMCreateWireStatus(CATWire *iWire) = 0;

  virtual void CATPGMDynMassProperties1DOnEdgeFixed(CATDynMassProperties1DOnEdge *iOp) = 0;

  virtual void CATPGMSetSimplifyTool(
    CATICGMHybProject *iProjection,
    CATSimplifyParallelTool *iCurSimplif) = 0;

  virtual void CATPGMSetSimplifyToolParameters(
    CATICGMHybProject *iProjection,
    double iTolerance,
    CATLONG32 iNewSmoothing,
    CATLONG32 iOutputWire3DCleaning) = 0;

  virtual CATBoolean CATPGMCheckFace(
    CATBody *iBody,
    CATFace *iFace,
    CATLISTP(CATEdge) *oListOfEdgeOfNullLength) = 0;

  virtual CATBoolean CATPGMCheckBodyShellConnexity(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory *iFactory,
    CATBody *iBodyToCheck) = 0;

  virtual CATBoolean CATPGMCheckMaxGapOnShell(
    CATBody *iBody,
    CATShell *iShell,
    CATCGMDiagnosis *&oMaxGapOnResultDiagnosis,
    CATTopToolsGapCheckMode iGapCheckMode,
    CATLISTP(CATEdge) *oGapEdges,
    const CATLISTP(CATEdge) &iListPOfEdgeToCheck) = 0;

  virtual CATBoolean CATPGMCheckMaxGapOnShell(
    CATBody *iBody,
    CATShell *iShell,
    CATCGMDiagnosis *&oMaxGapOnResultDiagnosis,
    CATTopToolsGapCheckMode iGapCheckMode,
    CATLISTP(CATEdge) *oGapEdges) = 0;

  virtual void CATPGMUpdateListOfSkinFaces(
    CATLISTP(CATFace) &iFaces,
    CATListOfInt &iOrientations,
    CATBody *iBody,
    CATCGMJournalList *iJournal) = 0;

  virtual CATTopOpInError *CATPGMMakeDiagError(
    const char *iMsgId,
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iListOfCellToShow) = 0;

  virtual CATTopOpInError *CATPGMMakeDiagError(
    const int iNumberError,
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iListOfCellToShow) = 0;

  virtual CATDynValidShellType CATPGMCheckValidSkin(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory *iFactory,
    CATBody *iBodyToCheck,
    CATLISTP(CATBody) &oListBody) = 0;

  virtual void CATPGMGetNbDomainsPerDimension(
    CATBody *iBody,
    int &oNbLumps,
    int &oNbShells,
    int &oNbWires,
    int &oNbVertex) = 0;

  virtual CATBoolean CATPGMCheckUnhermeticSkin(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBodyToCheck,
    CATShell *iShellToCheck,
    CATBody **oResultBody) = 0;

  virtual CATBoolean CATPGMIsFaceOffsetable(
    CATFace *iFace,
    CATSoftwareConfiguration *iConfig,
    double iOffsetValue) = 0;

  virtual CATBoolean CATPGMIsTwistedFace(
    CATFace *iFace,
    CATBoolean iDoNewTest,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATTopOpInError *CATPGMMakeCollisionError(
    CATShell *iSkin,
    CATLISTP(CATBody) &iCollisionBodies,
    CATGeoFactory *iFactory,
    CATBoolean iForceBlendVertexError) = 0;

  virtual CATTopOpInError *CATPGMMakeTwistError(
    CATShell *iSkin,
    CATLISTP(CATFace) &iTwistedFaces,
    CATGeoFactory *iFactory) = 0;

  virtual CATFace *CATPGMCheckTwistedSkin(
    CATShell *iShellToCheck,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATFace) *oTwistedFaces) = 0;

  virtual CATIPGMHybAssemble *CATPGMCreateNewTopAssembleForCVM(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) *iBodiesToAssemble) = 0;

  virtual CATIPGMSplitBySurfaceOperator *CATPGMCreateSplitBySurfaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATSurface *iSurface,
    CATBody *iBodySupport) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATBody *iBody1,
    const CATMathTransformation &iBody1Transformation,
    CATGeoFactory *iFactory2,
    CATBody *iBody2,
    const CATMathTransformation &iBody2Transformation,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATCell *iCell1,
    const CATMathTransformation &iCell1Transformation,
    CATGeoFactory *iFactory2,
    CATCell *iCell2,
    const CATMathTransformation &iCell2Transformation,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATDomain *iDomain1,
    const CATMathTransformation &iDomain1Transformation,
    CATGeoFactory *iFactory2,
    CATDomain *iDomain2,
    const CATMathTransformation &iDomain2Transformation,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATBody *iBody1,
    const CATMathTransformation &iBody1Transformation,
    CATGeoFactory *iFactory2,
    CATBody *iBody2,
    const CATMathTransformation &iBody2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATCell *iCell1,
    const CATMathTransformation &iCell1Transformation,
    CATGeoFactory *iFactory2,
    CATCell *iCell2,
    const CATMathTransformation &iCell2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATDomain *iDomain1,
    const CATMathTransformation &iDomain1Transformation,
    CATGeoFactory *iFactory2,
    CATDomain *iDomain2,
    const CATMathTransformation &iDomain2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDomain *iDomain1,
    CATDomain *iDomain2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATIPGMExtrapolOpWireOnShell *CATPGMCreateExtrapolOpWireOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *BodyWire,
    CATBody *BodyShell) = 0;

  virtual CATIPGMHybProject *CATPGMCreateTopProjectTrapError(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToProject,
    CATBody *iBodySupport,
    CATMathDirection *iDirection) = 0;

  virtual CATICGMRemoveFacesInShell *CATCGMCreateRemoveFacesInShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATCell) *iFacesToRemove) = 0;

  virtual CATBody *CATPGMCreateBodyMonoWireMonoEdge(
    CATEdge *iEdge,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicate) = 0;

  virtual CATBody *CATPGMCreateBodyMonoShellMonoFace(
    CATFace *iFace,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicate) = 0;

  virtual void CATPGMGet2DBoundingBox(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace,
    CATSurLimits &o2DBoundingBoxForEdge,
    CATVertex *iStart,
    CATVertex *iEnd) = 0;

  virtual void CATPGMGetLimits(CATEdge *iEdge, CATCrvLimits &oLimits, CATCurve *iCurve) = 0;

  virtual CATTopSign CATPGMGetRelativeOrient(
    CATFace *iFace,
    CATMathDirection &iDirection,
    CATOrientation iOrientation,
    CATShell *iShell,
    CATBody *iBody,
    CATVertex *iVertexOnFace,
    CATEdge *iEdgeOnFace,
    double iTol) = 0;

  virtual HRESULT CATPGMEvalTopoAreaOrientation(
    CATSoftwareConfiguration * iConfig,
    CATTopology              * iTopObject,
    const CATMathDirection   & iRefDirection,                                                      
    CATOrientation           & oTopoAreaOrientation) = 0;

  virtual CATMathAdvancedBox * CATPGMComputeTopoAdvancedBox(
    CATSoftwareConfiguration * iConfig,
    CATTopology              * iTopObject) = 0;

  virtual void CATPGMGetComplementaryCell(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig,
    CATCell *iCell,
    CATCell *iBorderCell,
    CATLISTP(CATCell) &oComplementaryCell,
    CATBody *iNewBody,
    CATDomain *iDomain) = 0;

  virtual void CATPGMGetMaxPCurvesBoxUV(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATSurLimits &oBoxUV) = 0;

  virtual CATEdgeCurve *CATPGMMergePCurveWithEdgeCurve(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCurve,
    CATCrvLimits &iPCurveLimits,
    CATEdgeCurve *iEdgeCurve,
    CATCrvLimits &iEdgeCurveLimits,
    double iTolerance,
    CATPCurve *iPCurveUnderEdge,
    CATOrientation &oOriNewEdgeCurveVsPrev) = 0;

  virtual void CATPGMReplaceEdgeCurve(
    CATEdge *iEdge,
    CATEdgeCurve *iNewEdgeCurve,
    CATOrientation iOriNewEdgeCurveVsPrev,
    CATCurve *iCommonCurve) = 0;

  virtual CATICGMDistancePointBody *CATCGMCreateDistancePointBody(
    CATBody *iBody,
    CATTopData *iData) = 0;

  virtual CATIPGMDistancePointBody *CATPGMCreateDistancePointBody(
    CATBody *iBody,
    CATTopData *iData) = 0;

  virtual CATIPGMDistancePointBody *CATPGMCreateDistancePointBody(
    const CATLISTP(CATCell) & iBodyCells, 
    CATTopData *iData) = 0;

  virtual CATBody *CATPGMCreateBodyMonoShell(
    CATShell *iShell,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody) = 0;

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

  virtual CATICGMSolidSphere *CATCGMTopCreateSolidSphere(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iCenter,
    double iRadius) = 0;

  virtual CATIPGMSolidSphere *CATPGMTopCreateSolidSphere(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATMathPoint &iCenter,
    double iRadius) = 0;

#ifndef CATIACGMR214CAA
  virtual CATIPGMDistanceTool *CATPGMCreateTopEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;
#else
  virtual CATIPGMDistanceTool *CATPGMCreateTopEuclidianDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;
#endif

#ifndef CATIACGMR214CAA
  virtual CATIPGMDistanceTool *CATPGMCreateTopGeodesicDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATCompositeLaw *iDistance) = 0;
#else
  virtual CATIPGMDistanceTool *CATPGMCreateTopGeodesicDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;
#endif

  virtual CATIPGMDistanceTool *CATPGMCreateTopDirectionalDistanceTool(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATMathDirection &iDirection,
    CATOrientation iOrientation,
    CATLaw *iDistance) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATCell) &iCellsList1,
    CATLISTP(CATCell) &iCellsList2) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) &iBodiesList1,
    CATLISTP(CATBody) &iBodiesList2) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCell *iCell1,
    CATCell *iCell2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATCell) &iCellsList1,
    CATLISTP(CATCell) &iCellsList2) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) &iBodiesList1,
    CATLISTP(CATBody) &iBodiesList2) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCell *iCell1,
    CATCell *iCell2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyLight(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDomain *iDomain1,
    CATDomain *iDomain2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMTopCurveChecker *CATPGMCreateTopCurveChecker(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopdata,
    const CATLISTP(CATTopology)& iObjectsToCheck) = 0;


  virtual CATFace *CATPGMCheckTwistedSkin(
    CATCellHashTable *ihtShellToCheck,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATFace) *oTwistedFaces) = 0;

  virtual CATFace *CATPGMCheckTwistedSkin(
    CATShell *iShellToCheck,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATFace) *oTwistedFaces,
    CATBoolean iCheckInsideFace) = 0;

  virtual CATFace *CATPGMCheckTwistedSkin(
    CATCellHashTable *ihtShellToCheck,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATFace) *oTwistedFaces,
    CATBoolean iCheckInsideFace) = 0;

  virtual CATBoolean CATPGMIsTwistedFace(
    CATFace *iFace,
    CATBoolean iDoNewTest,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iCheckInsideFace) = 0;

  virtual CATIPGMTopCoincidentEdgesFinder *CATPGMCreateTopCoincidentEdgesFinder(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopdata,
    CATBody *ipGlobalBody,
    const CATLISTP(CATBody) &iBodies,
    const CATLISTP(CATBody) &iEOPBodies,
    double iTol) = 0;

  virtual CATIPGMTopCoincidentEdgesFinder *CATPGMCreateTopCoincidentEdgesFinder(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopdata,
    const CATLISTP(CATBody) &iBodies) = 0;

  virtual CATIPGMExtractCellsOpe *CATPGMCreateExtractCellsOpe(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipInputBody,
    const CATLISTP(CATCell) &iInputCellList) = 0;

  virtual CATIPGMSelectEdgeOpe *CATPGMCreateSelectEdgeOpe(
    CATTopData *ipTopData,
    CATBody *ipInputBody,
    const CATLISTP(CATEdge) &iInputEdgeList,
    CATSelectEdgePropagateMode iPropagationMode,
    const CATLISTP(CATEdge) *iEdgeGuideList,
    const CATLISTP(CATEdge) *iStoppingEdges) = 0;
  
  virtual CATIPGMTopHealOperator *CATPGMCreateTopologicalHealing(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iPart,
    CATShell *iShell) = 0;

};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopoOpeLightItfBldr *CATCGMGetTopoOpeLightItfBldr();

#endif /* CATIPGMTopoOpeLightItfBldr_h */
