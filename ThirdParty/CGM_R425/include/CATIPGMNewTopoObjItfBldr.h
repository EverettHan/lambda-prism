#ifndef CATIPGMNewTopoObjItfBldr_h
#define CATIPGMNewTopoObjItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATBody.h"
#include "CATBodyFreezeMode.h"
#include "CATTopToolsGapCheckMode.h"
#include "CATCGMTransaction.h"
#include "CATBoolean.h"
#include "CATTopBodyToolsFreezeMode.h"
#include "CATTopGeometricalMapType.h"
#include "CATlsoUtilTraceDef.h"
#include "CATSkillValue.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "ListVOfLong.h"
#include "CATCGMVersionCommonEdges.h"
#include "CATTopGeoMapping_QueryType.h"
#include "CATCGMJournal.h"
#include "CATIACGMLevel.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATIPGMTopGNCommonEdgeData.h"
#include "CATTopData.h"
#include "CATBodyMode.h"
#include "CATDeclarativeContext.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDomain.h"
#include "CATListOfInt.h"
#include "ListPOfListPOfCATTopology.h"

class CATICGMTopEdgePropagation;
class CATIPGMTopEdgePropagation;
class CATICGMBoundaryIterator;
class CATIPGMBoundaryIterator;
class CATICGMObject;
class CATICGMTopPropagationEdge;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopPropagationEdge;
class CATICGMPositionPtFaceOperator;
class CATSurParam;
class CATICGMPositionPtVolOperator;
class CATIPGMPositionPtVolOperator;
class CATCrvParam;
class CATEdgeCurve;
class CATPCurve;
class CATSurLimits;
class CATBody;
class CATBodiesMapping;
class CATIPGMBodyDatumiser;
class CATCGMOperatorRunTransaction;
class CATMacroPoint;
class CATCurve;
class CATPoint;
class CATIPGMChecker;
class CATIPGMSimplifyOperator;
class CATIPGMTopBooleanOperator;
class CATIPGMTopologicalOperator;
class CATIPGMTopCheckJournal;
class CATICGMTopOperator;
class CATPGMTopJournalTools;
class CATPGMTopMathEvalToolKit;
class CATPGMTopMathEvalToolKit2D;
class CATIPGMTopModify;
class CATIPGMTopToolsCreateDomains;
class CATIPGMTopToolsDuplicateDomains;
class CATCXTopology; // Not interfaced
class CATCX_CHECKUP;
class CATCXVertexIter; // Not interfaced
class CATCXConnectedCells; // Not interfaced
class CATPointOnEdgeCurve;
class CATIPGMTopBodyHealerOperator;
class CATIPGMFaceBoundaryIntersectionChecker;
class CATIPGMTopFaceHealerOperator;
class CATIPGMTopPropagationFace;
class CATIPGMTopRelimitByVolume;
class CATICGMTopRelimitByVolume;
class CATIPGMShellIntersectionChecker;
class CATIPGMTopSplitBySkin;
class CATPlane;
class CATIPGMWireIntersectionChecker;
class CATJournalsMapping;
class CATMultiBodiesMapping;
class CATCGMJournal;
class CATIPGMTopWireHealerOperator;
class CATIPGMTopWireMultiTrim;
class CATPGMDisconnectGateway;
class CATDisconnectEngine;
struct CATCGMVisuData;
class CATCGMODTScaleManager;
class CATPGMCellManifoldsManager;
class CATDeclarativeManifoldAgent;
class CATLiveBody;
class CATFaceAnalyzer;
class CATWallFacesAnalyzer;
class CATTopAnalysisTools;
class CATLISTP(CATCellManifold);
class CATLISTP(CATCGMJournal);
class CATLISTP(CATTopology);
class CATLISTP(CATWire);
class CATLISTP(CATPoint);
class CATLISTP(CATCurve);
class CATLISTP(CATBody);
class CATLISTP(CATCell);
class CATCellManifold;
class CATIPGMTopGeometricalMapping;
class CATLISTP(CATICGMUnknown);
class CATCGMCellTracker;
class CATSubdContextForFastRunExt;
class CATIPGMChamferTool;
class CATIPGMTopCreateBody;
class CATIPGMTrimByThick;
class CATPGMChain;
class CATContextForFastRun;
class CATIPGMTopoChain;
class CATRecognizerContext;
class CATCGMObject;
class CATPGMExplicitCheck;
class CATPGMExplicitReport;
class CATManifoldParameter;
class CATDRepNavigatorBridge;
class CATDRepNavigatorInterface;
class CATPGMIntersectFilteringTools;
class CATPGMDRepBehavior;
class CATLISTP(CATConnectedCellsIterator);
class CATIPGMExplicitCheckOperator;
class CATIPGMEdgeToCanonic;
class CATPGMODTScaleManager;
class CATGeometry;
class CATCellHashTable;
class CATIPGMDRepGroupThread;
class CATDoubleManifoldParam;
class CATIntManifoldParam;
class CATManifoldParamId;
class CATCGMStream;
class CATSoftwareConfiguration;
class CATCGMHashTableWithAssoc;
class CATIPGMDRepLabelServices;
class CATPGMCellSupportOfConstraintService;
class CATCGMJournalCompletion;
class CATPGMDRepLabelUtilities;
class CATDRepLabel;
class CATManifoldModification;
class CATMathStream;
class CATICGMContainer;
class CATManifold;
class CATMathVector;
class CATVectorManifoldParam;
class CATTransfoManifoldParam;
class CATDRepLabelRequest;
class CATNullManifoldParam;
class CATIPGMMultiProcRunner;
class CATLISTP(CATCGMBoundedCellGroup);
class CATDomain;
class CATIPGMTopGNCommonTopologyData;


extern ExportedByCATGMModelInterfaces IID IID_CATIPGMNewTopoObjItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework NewTopologicalObjects.
 */
class ExportedByCATGMModelInterfaces CATIPGMNewTopoObjItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual ostream &CATCheckTopology(
    CATICGMObject *iObject,
    int &ioNumberOfSevereAnomalies,
    ostream &ioForDumpOfAnomalies) = 0;

  virtual CATICGMTopPropagationEdge *CATCGMCreatePropagationEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATCell) *iInitialEdges,
    CATBody::CATPropagationTypePr3 iPropagationType,
    CATLISTP(CATEdge) *iRollingEdges) = 0;

  virtual CATIPGMTopPropagationEdge *CATPGMCreatePropagationEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData) = 0;

  virtual CATIPGMTopPropagationEdge *CATPGMCreatePropagationEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATCell) *iInitialEdges,
    CATBody::CATPropagationTypePr3 iPropagationType,
    CATLISTP(CATEdge) *iRollingEdges) = 0;

  virtual CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    int iNbPoints,
    CATSurParam iPoints[],
    CATFace *iFace) = 0;

  virtual CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATSurParam &iPoint,
    CATFace *iFace) = 0;

  virtual CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
    CATGeoFactory *iFactory,
    int iNbPoints,
    CATSurParam iPoints[],
    CATFace *iFace) = 0;

  virtual CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
    CATGeoFactory *iFactory,
    CATSurParam &iPoint,
    CATFace *iFace) = 0;

  virtual CATICGMPositionPtVolOperator *CATCGMCreatePositionPtVolOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATMathPoint &iPoint,
    CATVolume *iVolume) = 0;

  virtual CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATMathPoint &iPoint,
    CATFace **iFacesArray,
    CATLONG32 nbFacesInArray,
    CATSide *iSidesArray) = 0;

  virtual CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATMathPoint &iPoint,
    CATVolume *iVolume) = 0;

  virtual CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
    CATGeoFactory *iFactory,
    CATMathPoint &iPoint,
    CATFace **iFacesArray,
    CATLONG32 nbFacesInArray,
    CATSide *iSidesArray) = 0;

  virtual CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
    CATGeoFactory *iFactory,
    CATMathPoint &iPoint,
    CATVolume *iVolume) = 0;

  virtual void CATTopOperator_CATCGMLoadInOutput(
    CATCGMStream &ioStream,
    CATGeoFactory *&iFactory,
    CATTopData &ioTopData,
    CATBodyFreezeMode &iFreezeMode,
    CATLISTP(CATICGMObject) &ioInputCopy,
    CATLISTP(CATICGMObject) &ioInputNoCopy,
    CATBody *&ioOutputBody,
    CATLISTP(CATICGMObject) *ioInputNeutral,
    CATCGMODTScaleManager *iCGMODTScaleManager) = 0;

  virtual void CATTopOperator_CATCGMReadTopOperator(
    CATGeoFactory *iFactory,
    CATCGMStream &ioStream,
    CATTopData &ioTopData,
    CATBodyFreezeMode &iFreezeMode,
    CATBoolean iWithSpecifiedInOut,
    CATLISTP(CATICGMObject) *ioInputCopy,
    CATLISTP(CATICGMObject) *ioInputNoCopy,
    CATBody **ioOutputBody,
    CATLISTP(CATICGMObject) *ioInputNeutral,
    CATCGMODTScaleManager *iCGMODTScaleManager) = 0;

  virtual CATBody *CATTopTools_CATPGMCreateBodyMonoWireMonoEdge(
    CATEdge *iEdge,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody,
    const CATBoolean iDuplicate) = 0;

  virtual CATBoolean CATTopTools_CATPGMComputeMaxGapOnBody(
    CATBody *iBody,
    CATShell *iShell,
    CATLISTP(CATEdge) &oListPOfEdge,
    CATLISTP(CATBody) *oListPOfEdgeBody,
    CATTopToolsGapCheckMode iGapCheckMode,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATTopTools_CATPGMComputeMaxGapOnBody(
    CATBody *iBody,
    CATShell *iShell,
    CATLISTP(CATEdge) &oListPOfEdge,
    CATLISTP(CATBody) *oListPOfEdgeBody,
    CATTopToolsGapCheckMode iGapCheckMode,
    const CATLISTP(CATEdge) &iListPOfEdgeToCheck,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATTopTools_CATPGMCheckSmoothSharpEdge(
    CATEdge *iEdge,
    CATFace *iAdjFace1,
    CATFace *iAdjFace2) = 0;

  virtual void CATTopTools_CATPGMGetAllEdges(CATFace *iFace, CATLISTP(CATEdge) &oEdges) = 0;

  virtual CATShell *CATTopTools_CATPGMGetShell(CATBody *iBody, CATCell *iCell, CATSide *oSide) = 0;

  virtual HRESULT CATTopTools_CATPGMGetBorderedFaces(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oFaces,
    CATListOfLong     & oNbOfFacesByDomain,
    short iSoftwareLevel) = 0;

  virtual int CATTopTools_CATPGMGetBoundedDomains(
    CATCell *iCell,
    CATBody *iBody,
    CATDomain *(oDomains[]),
    CATOrientation *oOrientations,
    const int SizeOutput) = 0;

  virtual void CATTopTools_CATPGMGetBnddEdgesOnFace(
    CATVertex *iVertex,
    CATFace *iFace,
    CATLISTP(CATEdge) &oEdges) = 0;

  virtual void CATTopTools_CATPGMEvalNormalOnShell(
    CATShell *iShell,
    CATMathPoint &oPoint,
    CATMathVector &oNormal,
    CATFace *iFace) = 0;

  virtual double CATTopTools_CATPGMEvalTransversalCurvature(
    CATSoftwareConfiguration *iConfig,
    const CATCrvParam &iCrvParam,
    CATEdge *iEdge,
    CATFace *iFace,
    CATBoolean &oIsOk) = 0;

  virtual double CATTopTools_CATPGMEvalTransversalCurvature(
    const CATCrvParam &iCrvParam,
    CATEdge *iEdge,
    CATFace *iFace,
    CATBoolean &oIsOk) = 0;

  virtual void CATTopTools_CATPGMEvalExtremities(
    CATEdge *iEdge,
    CATMathPoint &oStartPt,
    CATMathPoint &oEndPt) = 0;

  virtual void CATTopTools_CATPGMEvalMiddle(CATEdge *iEdge, CATMathPoint &oMidPt) = 0;

  virtual CATBoolean CATTopTools_CATPGMIsShellAVolume(CATBody *iBody, CATShell *iShell) = 0;

  virtual void CATTopTools_CATPGMGet2DExactBoundingBox(
    CATFace *iFace,
    CATSurLimits &o2DExactBoundingBox) = 0;

  virtual CATBodiesMapping *CATCGMCreateBodiesMapping(
    const CATBody *iReferenceBody,
    const CATBody *iResultBody,
    const int iSilentMode) = 0;

  virtual CATBodiesMapping *CATCGMCreateBodiesMapping(
    CATTopData *iTopData,
    const CATBody *iReferenceBody,
    const CATBody *iResultBody,
    const int iSilentMode) = 0;

  virtual CATIPGMBodyDatumiser *CATPGMCreateFactoryDatumiser(
    CATGeoFactory *iFactory,
    const CATTopData &iTopData) = 0;

  virtual CATIPGMBodyDatumiser *CATPGMCreateBodyDatumiser(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iInputBodies,
    const CATTopData &iTopData,
    const CATLISTP(CATICGMObject) *iInputMapping) = 0;

  virtual CATIPGMBodyDatumiser *CATPGMCreateBodyDatumiser(
    CATGeoFactory *iFactory,
    CATBody *iInputBody,
    const CATTopData &iTopData,
    const CATLISTP(CATICGMObject) *iInputMapping) = 0;

  virtual CATCGMOperatorRunTransaction *CATCXCGMOperatorRunTransaction_CATPGMCreate(CATGeoFactory *ipFactory) = 0;

  virtual CATCGMOperatorRunTransaction *CATCXCGMOperatorRunTransaction_CATPGMCreate(
    CATGeoFactory *ipFactory,
    CATCGMInterruptFunction ipInterruptFunction) = 0;

  virtual void CATCXTools_CATPGMGetExpectedCellsForReporting(
    CATBody *inBody,
    CATLISTP(CATCell) &ioReportingCells,
    const short iListManage_0Define_1Append) = 0;

  virtual void CATCXTools_CATPGMGetExpectedDomainsForReporting(
    CATBody *inBody,
    CATLISTP(CATDomain) &ioReportingDomains,
    const short iListManage_0Define_1Append) = 0;

  virtual void CATCXTools_CATPGMGetComponentsUsedByTopology(
    CATEdgeCurve *iEdgeCurve,
    CATBoolean iWithWeakLinks,
    CATLISTP(CATCurve) &ioReps) = 0;

  virtual CATBoolean CATCXTools_CATPGMIsUsedByTopology(CATCurve *iCurve, CATBoolean iWithWeakLinks) = 0;

  virtual void CATCXTools_CATPGMGetComponentsUsedByTopology(
    CATMacroPoint *iMacroPoint,
    CATBoolean iWithWeakLinks,
    CATLISTP(CATPoint) &ioReps) = 0;

  virtual CATBoolean CATCXTools_CATPGMIsUsedByTopology(CATPoint *iCurve, CATBoolean iWithWeakLinks) = 0;

  virtual void CATCXTools_CATPGMEstimateCenterParamOnShell(
    CATShell *iShell,
    CATFace *&ioFace,
    CATSurParam &ioSurParam) = 0;

  virtual void CATCXTools_CATPGMEstimateCenterParamOnFace(CATFace *iFace, CATSurParam &ioSurParam) = 0;

  virtual void CATCXTools_CATPGMGetWireOrderAndReferenceEdge(
    CATTopData &iTopData,
    CATLISTP(CATWire) &iWiresList,
    CATListOfInt &oWiresOrder,
    CATLISTP(CATEdge) &oReferenceEdges) = 0;

  virtual CATBoolean CATCXTools_CATPGMIsFaceAPlanarRevolCrown(
    CATTopData *iTopData,
    CATFace *iFace,
    CATMathLine &oRevolLine) = 0;

  virtual CATIPGMSimplifyOperator *CATPGMCreateSimplifyOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData) = 0;

  /*virtual void CATTopBodyTools_CATCGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode,
    int wantingHazardousVersion) = 0;

  virtual void CATTopBodyTools_CATCGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode,
    CATLISTP(CATDomain) *oCreatedDomains,
    int wantingHazardousVersion) = 0;*/

  virtual void CATTopBodyTools_CATCGMGetDomainBoundingCells(
    CATBody *iBody,
    CATLISTP(CATCell) &oListOfCell,
    short iDimension,
    CATDomain *iDomain) = 0;

  virtual void CATTopBodyTools_CATCGMMergeBodies(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iList,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode) = 0;

  virtual HRESULT CATTopBodyTools_CATPGMIsDomainsBodyEmpty(CATBody *piBody, CATBoolean &ioIsEmpty) = 0;

  virtual void CATTopBodyTools_CATCGMInvertWire(CATGeoFactory *iFactory, CATBody *iWireBody, CATBody *&oBody) = 0;

  virtual int CATTopBodyTools_CATCGMGetInfinite(CATBody *) = 0;

  virtual void CATTopBodyTools_CATCGMInactivate(CATBody *) = 0;

  virtual void CATTopBodyTools_CATCGMForceActivate(CATBody *) = 0;

  virtual void CATTopBooleanOperator_CATCGMSetMultiThreadMode(int iNbThreads) = 0;

  virtual int CATTopBooleanOperator_CATCGMGetMultiThreadMode() = 0;

  virtual void CATTopBooleanOperator_CATCGMRattrapJournal(
    CATCGMJournalList *iJournal,
    CATBody *iSplitBody,
    CATBody *iResultBody,
    CATBoolean iIgnoreAbsorptionOrder) = 0;

  virtual void CATTopBooleanOperator_CATCGMRattrapJournal(
    CATTopData *iTopData,
    CATBody *iSplitBody,
    CATBody *iResultBody,
    CATBoolean iIgnoreAbsorptionOrder) = 0;

  virtual CATIPGMTopBooleanOperator *CATPGMCreateTopBooleanOperator(
    CATGeoFactory *iFactory,
    CATCGMJournalList *iReport,
    CATBody *iCreationBody) = 0;

  virtual CATIPGMTopBooleanOperator *CATPGMCreateTopBooleanOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iCreationBody) = 0;

  virtual void CATTopCellRetrieve_CATCGMGetCellFromGeometry(
    CATGeoFactory *iFactory,
    CATGeometry *iGeom,
    CATLISTP(CATBody) &oListOfBody,
    CATLISTP(CATCell) &oListOfCell) = 0;

  virtual CATBoolean CATTopCheckJournal_CATCGMCheckOn() = 0;

  virtual void CATTopCheckJournal_CATCGMSetThrowOnError(int lvl) = 0;

  virtual void CATTopCheckJournal_CATCGMUnsetThrowOnError() = 0;

  virtual const CATString *CATTopCheckJournal_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMTopCheckJournal *CATPGMCreateTopCheckJournal(
    CATICGMTopOperator *iOperator,
    CATGeoFactory *iFactory,
    const CATTopData &iReport,
    CATBody *iResult,
    const CATUnicodeString *ipFeatureName,
    CATBoolean iTraceManagement,
    ostream *ipVerdictOutput,
    ostream *ipErrorWarningOutput,
    CATBoolean iVerboseCheckOK,
    CATBoolean iVerboseCheckKO,
    CATBoolean iCAACompliant,
    CATBoolean iHTML_OUTPUT) = 0;

  virtual CATIPGMTopCheckJournal *CATPGMCreateTopCheckJournal(
    CATICGMTopOperator *iOperator,
    CATGeoFactory *iFactory,
    const CATTopData &iReport,
    CATBody *iResult) = 0;

  virtual void CATTopCutting_CATCGMActivateCutting(
    CATCell *iLyingCell,
    CATBody *iBodyToCut,
    int iExclusive) = 0;

  virtual void CATTopCutting_CATCGMActivateCutting(
    CATDomain *iLyingDomain,
    CATBody *iBodyToCut,
    int iExclusive) = 0;

  virtual void CATTopCutting_CATCGMActivateCutting(
    CATBody *iLyingBody,
    CATBody *iBodyToCut,
    int iExclusive) = 0;

  virtual void CATTopCutting_CATCGMDesactivateCutting(CATCell *iCuttingCell) = 0;

  virtual void CATTopCutting_CATCGMDesactivateCutting(CATDomain *iCuttingDomain) = 0;

  virtual void CATTopCutting_CATCGMDesactivateCutting(CATBody *iCuttingBody) = 0;

  virtual void CATTopCutting_CATCGMDestroyCutting(CATCell *iCuttingCell, CATBody *iCutBody) = 0;

  virtual void CATTopCutting_CATCGMDestroyCutting(CATDomain *iCuttingDomain, CATBody *iCutBody) = 0;

  virtual void CATTopCutting_CATCGMDestroyCutting(CATBody *iCuttingBody, CATBody *iCutBody) = 0;

  virtual void CATTopCutting_CATCGMGetCuttingOrLyingOn(
    CATCell *iCell,
    CATLISTP(CATCell) &ioSupports,
    CATBody *iInBody) = 0;

  virtual CATGeometry *CATTopCutting_CATCGMGetCuttingOrLyingGeometryOn(
    CATCell *iCell,
    CATCell *iSupportingCell) = 0;

  virtual CATBoolean CATTopCutting_CATCGMIsCuttingOrLyingOn(CATCell *iCell, CATCell *iSupportingCell) = 0;

  virtual CATTopLyingOnDiagnostic CATTopCutting_CATCGMIsCuttingOrLyingOn(
    CATBody *iBody,
    CATBody *iSuppport) = 0;

  virtual CATTopLyingOnDiagnostic CATTopCutting_CATCGMIsCuttingOrLyingOn(
    CATDomain *iBody,
    CATDomain *iSuppport) = 0;

  virtual CATPGMTopJournalTools *CATPGMCreateTopJournalTools(
    CATCGMJournalList *ipReport,
    CATBody *ipOutBody) = 0;

  virtual CATPGMTopMathEvalToolKit *CATPGMCreateTopMathEvalToolKit(
    CATGeoFactory            * iContainer, 
    CATSoftwareConfiguration * ipConfig) = 0;

  virtual CATPGMTopMathEvalToolKit2D *CATPGMCreateTopMathEvalToolKit2D(
    CATPlane                 * iRefPlane,
    CATSoftwareConfiguration * ipConfig) = 0;

  virtual CATPGMTopMathEvalToolKit2D *CATPGMCreateTopMathEvalToolKit2D(
    CATGeoFactory            * iContainer,
    const CATMathPlane       & iRefMathPlane,
    CATSoftwareConfiguration * ipConfig) = 0;

  virtual CATIPGMTopModify *CATPGMCreateModify(
    CATBody *iCopyBody,
    const CATTopData &iTopData,
    CATTopGeometricalMapType iVertexMapType) = 0;

  virtual CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomains(
    CATBody *iBodyFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATLISTP(CATDomain) &iCreatedDomains,
    CATBoolean iAddDomain,
    CATCell *iMasterCell,
    CATSoftwareConfiguration *iSoftwareVersion,
    CATBoolean iAvoidFirstVersion) = 0;

  virtual CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomainsDEDICATED(
    CATBody *iBodyFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATLISTP(CATDomain) &iCreatedDomains,
    const CATTopData &iTopData,
    CATBoolean iAddDomain,
    CATCell *iMasterCell) = 0;

  virtual CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomains(
    CATBody *iBodyFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATLISTP(CATDomain) &iCreatedDomains,
    const CATTopData &iTopData) = 0;

  virtual CATIPGMTopToolsDuplicateDomains *CATPGMCreateTopToolsDuplicateDomains(
    CATBody *inputBody,
    short iContainedCellsDimension,
    short iContainingCellDimension,
    CATLISTP(CATDomain) &iCreatedDomains,
    const CATTopData &iTopData,
    CATTopology *iBodyOrCell,
    const CATBoolean iWithInvert) = 0;

  virtual short CATTopoDebug_CATPGMIsAvailable() = 0;

  virtual void CATTopoDebug_CATPGMDumpLyingOn(
    CATGeoFactory *iFactory,
    CATCGMOutput &ios,
    int &ioNumberOfCellWithLyingOn,
    int &ioNbCellWithGOODLyingOn,
    int &ioNbCellWithBADLyingOn) = 0;

  virtual void CATTopoDebug_CATPGMDumpHiddenSubdOccurences(
    CATTopology *iTopology,
    CATCGMOutput &ios,
    int &ioNumberOfHiddenSubdOccurences) = 0;

  virtual void CATTopoDebug_CATPGMGetCellWithLyingOns(
    CATGeoFactory *iFactory,
    CATLISTP(CATCell) &ioCells) = 0;

  virtual void CATTopoDebug_CATPGMisLocallyManifold(
    CATBody *iBody,
    const CATLONG32 iCellsMaxDim,
    const CATBoolean isHomogeneous,
    const CATBoolean isLocallyManifold,
    const CATLISTP(CATCell) &iFreeCell,
    const CATLISTP(CATCell) &iNonManifoldCell) = 0;

  virtual void CATTopoDebug_CATPGMCheckActivation(CATCXTopology *iContext) = 0;

  virtual void CATTopoDebug_CATPGMCheckUpwardLinks(CATCXTopology *iTopo, CATCX_CHECKUP *iReport) = 0;

  virtual CATBoolean CATTopoDebug_CATPGMSetCoverageMode_CATCX_UPWARD(CATBoolean _iActive) = 0;

  virtual void CATTopoDebug_CATPGMDebugVertexIter(CATCXVertexIter *iter) = 0;

  virtual void CATTopoDebug_CATPGMDebugIsSharingTopology(
    CATTopology *iFirst,
    CATTopology *iWith,
    CATBoolean result,
    CATLISTP(CATTopology) *ioSharingFederator) = 0;

  virtual void CATTopoDebug_CATPGMDebugHasInfiniteGeometry(CATBody *iBody, CATBoolean result) = 0;

  virtual void CATTopoDebug_CATPGMDebugFacePropagate(
    CATBody *iBody,
    CATLISTP(CATFace) *iInitialFaces,
    CATLISTP(CATFace) &result) = 0;

  virtual void CATTopoDebug_CATPGMDebugBodyCellNeighbours(
    CATBody *iBody,
    const CATLISTP(CATCell) *iCellList,
    const CATListOfLong *inputOrientations,
    const short iVersionGenericNaming,
    CATLISTP(CATCell) &result,
    CATListOfLong &oNbOfCellsByDomain) = 0;

  virtual void CATTopoDebug_CATPGMDebugBorderedFaces(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oFaces,
    CATListOfLong &oNbOfFacesByDomain,
    short iSoftwareLevel,
    HRESULT result) = 0;

  virtual void CATTopoDebug_CATPGMDebugCellNeighbours(
    CATCell *iCell,
    CATBody *inBody,
    CATLISTP(CATCell) &oCell,
    HRESULT result) = 0;

  virtual void CATTopoDebug_CATPGMDebugSelectEdgesFromFaces(
    CATBody *iBody,
    const CATLISTP(CATFace) &iFaceList,
    CATLISTP(CATCell) &result) = 0;

  virtual void CATTopoDebug_CATPGMDebugInternalVertices(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2,
    CATLISTP(CATCell) &iVertices) = 0;

  virtual void CATTopoDebug_CATPGMDebugCommonEdgesBefore(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2) = 0;

  virtual void CATTopoDebug_CATPGMDebugCommonEdges(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2,
    CATLISTP(CATCell) &ioResult,
    CATListOfLong &ioListOrientation,
    CATListOfLong &ioNbOfEdgesByDomain) = 0;

  virtual void CATTopoDebug_CATPGMDebugGroupCells(
    const CATLISTP(CATCell) &cellsInput,
    CATBody *body,
    CATLISTP(CATConnectedCellsIterator) &oCellsIterator) = 0;

  virtual void CATTopoDebug_CATPGMDebugGroupManyCells(
    const CATLISTP(CATCell) &cellsInput,
    CATBody *body,
    CATLISTP(CATConnectedCellsIterator) &oCellsIterator) = 0;

  virtual void CATTopoDebug_CATPGMDebugCommonCells(
    const CATLISTP(CATConnectedCellsIterator) &iList,
    CATLISTP(CATConnectedCellsIterator) &oList) = 0;

  virtual void CATTopoDebug_CATPGMDebugSelectBoundary(
    CATCXConnectedCells *iCtx,
    CATLISTP(CATConnectedCellsIterator) &oList) = 0;

  virtual void CATTopoDebug_CATPGMDebugCreateDomainsBefore(
    CATBody *iBody,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOris) = 0;

  virtual void CATTopoDebug_CATPGMDebugCreateDomains(
    CATBody *iBody,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOris,
    const CATLISTP(CATDomain) &Domains) = 0;

  virtual short CATTopoDebug_CATPGMGetCompletedLevel(CATBody *iBody) = 0;

  virtual CATBoolean TopologicalBasic_CATPGMIsOnBorder(
    CATCell *iCell,
    CATCell *iBoundedCell,
    CATSide &oSide) = 0;

  virtual void TopologicalBasic_CATPGMCreateBorder(
    CATBody *Body,
    CATEdge *Edge,
    CATPointOnEdgeCurve *StartPOEC,
    CATPointOnEdgeCurve *EndPOEC,
    CATVertex **StartVertex,
    CATVertex **EndVertex) = 0;

  virtual void TopologicalBasic_CATPGMGetBoundedCellsOnSide(
    CATCell *iBorderCell,
    CATSide iSide,
    CATBody *inBody,
    CATLISTP(CATCell) &oCell) = 0;

  virtual CATVertex *TopologicalBasic_CATPGMCreateVertexOnEdge(
    CATBody *iBody,
    CATEdge *iEdge,
    CATCrvParam &iParam) = 0;

  virtual void TopologicalBasic_CATPGMSplitEdgeAtPoint(
    CATBody *iBody,
    CATEdge *iEdge,
    CATCrvParam &iParam,
    CATEdge *&LeftEdge,
    CATVertex *&Vertex,
    CATEdge *&RightEdge) = 0;

  virtual CATDomain *TopologicalBasic_CATPGMGetDomain(CATBody *iBody, CATCell *iCell, CATSide &oSide) = 0;

  virtual void TopologicalBasic_CATPGMGetCommonBorderCells(
    CATCell *iCell1,
    CATCell *iCell2,
    CATLONG32 DepthOfSearch,
    CATLISTP(CATCell) &CommonCell) = 0;

  virtual CATDomain *TopologicalBasic_CATPGMGetDomainOfBorderCell(
    CATBody *iBody,
    CATCell *iBorderCell,
    CATCell *iCell) = 0;

  virtual CATDomain *TopologicalBasic_CATPGMGetDomainOfBorderCell(CATCell *iBorderCell, CATCell *iCell) = 0;

  virtual CATSide TopologicalBasic_CATPGMGetSideEdgeVsShell(CATBody *iBody, CATDomain *iDom, CATEdge *iEdge) = 0;

  virtual CATTopGeoContinuity TopologicalBasic_CATPGMCheckNormalContinuity(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace1,
    CATFace *iFace2,
    CATVertex *iVertex,
    CATTopSign &oOrientation) = 0;

  virtual CATTopGeoContinuity TopologicalBasic_CATPGMCheckTangencyContinuity(
    CATEdge *iEdge1,
    CATEdge *iEdge2,
    CATVertex *iVertex,
    CATAngle &oAngle,
    CATTopSign &oOrientation) = 0;

  virtual CATTopGeoContinuity TopologicalBasic_CATPGMCheckTangencyContinuity(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATEdge *iEdge,
    CATBody *inBody,
    CATVertex *iVertex) = 0;

  virtual CATFace *TopologicalBasic_CATPGMGetAdjacentFace(
    CATEdge *iEdge,
    CATFace *iFace,
    CATBody *iBody,
    CATTopSign oOrientation) = 0;

  virtual void TopologicalBasic_CATPGMGetBnddCells(
    CATCell *iCell,
    CATBody *inBody,
    CATLISTP(CATCell) &oBnddCells) = 0;

  virtual void TopologicalBasic_CATPGMGetAllBnddCell(
    CATVertex *iVertex,
    CATBody *inBody,
    CATLISTP(CATEdge) &oEdges,
    CATListOfInt &oSide,
    CATLISTP(CATFace) &oFaces) = 0;

  virtual CATTopSign TopologicalBasic_CATPGMGetGoodOrientation(
    CATCell *iRefCell,
    CATCell *iCell,
    CATCell *iCommonCell) = 0;

  virtual CATPointOnEdgeCurve *TopologicalBasic_CATPGMGetGeometryOn(CATVertex *iVertex, CATEdge *iEdge) = 0;

  virtual void TopologicalBasic_CATPGMGetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATCrvParam &ParmOnMCurve) = 0;

  virtual CATBoolean TopologicalBasic_CATPGMGetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATCrvParam &oParmOnPCurve,
    CATPCurve *&oPCurve) = 0;

  virtual CATBoolean TopologicalBasic_CATPGMGetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATCrvParam &oParmOnPCurve,
    CATPCurve *&oPCurve) = 0;

  virtual CATPointOnEdgeCurve *TopologicalBasic_CATPGMGetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATPCurve *&oPCurve) = 0;

  virtual CATPointOnEdgeCurve *TopologicalBasic_CATPGMGetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATPCurve *&oPCurve) = 0;

  virtual CATPCurve *TopologicalBasic_CATPGMGetGeometryOn(
    CATEdge *iEdge,
    CATFace *iFace,
    CATOrientation &oPCurveOrient) = 0;

  virtual CATPCurve *TopologicalBasic_CATPGMGetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace,
    CATOrientation &oPCurveOrient) = 0;

  virtual void CATPGMBodyRemoveName(CATBody *iBody) = 0;

  virtual void CATPGMBodyGetName(CATBody *iBody, CATUnicodeString &oString) = 0;

  virtual void CATPGMBodyPutName(CATBody *iBody, CATUnicodeString &iString) = 0;

  virtual CATIPGMTopBodyHealerOperator *CATPGMCreateBodyHealerOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToClean) = 0;

  virtual CATIPGMFaceBoundaryIntersectionChecker *CATPGMCreateFaceBoundaryIntersectionChecker(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCheck) = 0;

  virtual CATIPGMTopFaceHealerOperator *CATPGMCreateFaceHealerOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToClean) = 0;

  virtual CATIPGMTopPropagationFace *CATPGMCreatePropagationFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATFace) *iInitialFaces) = 0;

  virtual CATICGMTopRelimitByVolume *CATCGMCreateRelimitByVolume(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToRelimit,
    CATBody *iSolidBody) = 0;

  virtual CATIPGMTopRelimitByVolume *CATPGMCreateRelimitByVolume(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToRelimit,
    CATBody *iSolidBody) = 0;

  virtual CATIPGMShellIntersectionChecker *CATPGMCreateShellIntersectionChecker(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCheck) = 0;

  virtual CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSolidBody,
    CATPlane *iInfinitePlane) = 0;

  virtual CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSolidBody,
    CATSurface *iSurface,
    CATSurLimits *iSurLimits) = 0;

  virtual CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSolidBody,
    CATBody *iSkinBody) = 0;

  virtual CATIPGMWireIntersectionChecker *CATPGMCreateWireIntersectionChecker(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCheck) = 0;

  virtual int CATPGMTopInsertClosureVertex(
    CATGeoFactory *iFactory,
    CATBody *iClosedWireBody,
    CATBody *iVertexBody,
    CATBody *&oBody,
    const CATTopData &iTopData) = 0;

  virtual int CATPGMTopInsertLiveClosureVertex(
    CATGeoFactory *iFactory,
    CATBody *iClosedWireBody,
    CATBody *iVertexBody,
    CATBody *&oBody,
    const CATTopData &iTopData) = 0;

  virtual void CATPGMTopMergeBodies(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iList,
    CATBody *&oBody,
    CATBoolean iFreezeOn,
    const CATTopData &iTopData) = 0;

  virtual CATJournalsMapping *CATCGMCreateJournalsMappingMulti(
    const CATLISTP(CATBody) *ipListReferenceBodies,
    const CATListOfCATString *ipListReferenceJournalFiles,
    const CATLISTP(CATBody) *ipListResultBodies,
    const CATLISTP(CATCGMJournal) *ipListResultJournals,
    const CATMultiBodiesMapping *ipMultiBodiesMapping,
    int iForceWrite) = 0;

  virtual CATJournalsMapping *CATCGMCreateJournalsMappingMulti(
    const CATLISTP(CATBody) *ipListReferenceBodies,
												const char * iReferenceJournalFile,
    const CATLISTP(CATBody) *ipListResultBodies,
    const CATLISTP(CATCGMJournal) *ipListResultJournals,
    const CATMultiBodiesMapping *ipMultiBodiesMapping,
    int iForceWrite) = 0;

  virtual CATJournalsMapping *CATCGMCreateJournalsMapping(
    const CATBody *iReferenceBody,
    const CATCGMJournal *iReferenceJournal,
    const CATBody *iResultBody,
    const CATCGMJournal *iResultJournal,
    CATCGMOutput &os) = 0;

  virtual CATJournalsMapping *CATCGMCreateJournalsMapping(
    const CATBody *iReferenceBody,
    const char *iReferenceJournalFile,
    const CATBody *iResultBody,
    const CATCGMJournal *iResultJournal,
    int iForceWrite) = 0;

  virtual CATICGMTopEdgePropagation *CATCGMCreateTopEdgePropagation(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATEdge *iInitialEdge) = 0;

  virtual CATIPGMTopEdgePropagation *CATPGMCreateTopEdgePropagation(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATEdge *iInitialEdge) = 0;

  virtual CATBoolean CATTopTools_CATPGMFindDegenerateEdges(
    CATGeoFactory *iFactory,
    CATTopData &iTopData,
    CATTopology *iTopology,
    double iMinLength,
    CATLISTP(CATEdge) &DegeneratedEdges,
    CATLISTP(CATBody) *DegeneratedEdgesBodies) = 0;

  virtual void CATTopTools_CATPGMFindBorderedFaces(
    CATGeoFactory *iFactory,
    CATTopData &iTopData,
    CATBody *iBody,
    CATLISTP(CATEdge) &iEdges,
    CATLISTP(CATCell) &oFaces,
    CATLISTP(CATBody) *oFacesBodies) = 0;

  virtual CATIPGMTopWireHealerOperator *CATPGMCreateWireHealerOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToClean) = 0;

  virtual CATIPGMTopWireMultiTrim *CATPGMCreateWireMultiTrim(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWorkingBody,
    CATLISTP(CATBody) *iBodiesToTrim) = 0;

  virtual HRESULT CATPGMTopGN_InternalVerticesOfCommonBoundary(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2,
    CATLISTP(CATCell) &iVertices) = 0;

  virtual HRESULT CATPGMTopGN_CommonEdges(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaceList_1,
    const CATLISTP(CATCell) &iFaceList_2,
    CATLISTP(CATCell) &ioResult,
    CATListOfLong &ioListOrientation,
    CATLISTP(CATDomain) &ioListOfCATDomains,
    CATListOfLong &ioNbOfEdgesByDomain,
    CATCGMVersionCommonEdges iVersion,
    CATBoolean iFirstListIsMatterSideLeft) = 0;

  virtual HRESULT CATPGMTopGN_CellNeighbours(
    CATBody *ipContextBody,
    const CATLISTP(CATCell) *ipCellList,
    const CATListOfLong *ipOris,
    CATLISTP(CATCell) &oResultCells,
    CATListOfLong &oNbOfCellsByDomain,
    const short iVersionGenericNaming,
    CATSoftwareConfiguration *ipConfig = NULL) = 0;

  virtual HRESULT CATPGMTopGN_GroupCells(
    CATBody *ipContextBody,
    const CATLISTP(CATCell) *ipCellsToGroup,
    CATListOfLong & oNbCellByGroup,
    CATLISTP(CATCell) &oGroups,
    CATBoolean iConsiderNonManifold = FALSE,
    CATSoftwareConfiguration *ipConfig = NULL) = 0;

  virtual HRESULT CATPGMTopGN_GetExpectedCellsForReporting(
    CATBody *ipContextBody,
    CATLISTP(CATCell) &ioReportingCells,
    CATSoftwareConfiguration *ipConfig = NULL) = 0;
  
  virtual HRESULT CATPGMTopGN_SelectEdgesFromFaces(
    CATBody *ipContextBody,
    const CATLISTP(CATFace) *ipFaces,
    CATLISTP(CATCell) &oEdges,
    CATBoolean iConsiderNonManifold = FALSE,
    CATSoftwareConfiguration *ipConfig = NULL) = 0;

  virtual HRESULT CATPGMTopGN_VertexBoundedCells(
	  CATBody *iContextBody,
	  CATCell *iVertex,
	  CATLISTP(CATCGMBoundedCellGroup) &oResult,
	  CATSoftwareConfiguration *ipConfig = NULL) = 0;

  virtual HRESULT CATPGMTopGN_IsCandidateForReporting(
    CATBody *ipContextBody,
    CATCell *ipCell,
    CATBoolean& oIsCandidate,
    CATSoftwareConfiguration *ipConfig = NULL) = 0;

  virtual CATBoolean CATCGMGetVisuData(
    CATVertex *ipVertex,
    CATBody *ipBody,
    CATCGMVisuData *iopCGMVisuData,
    unsigned int RequestedDataMask,
    CATAngle iMinSharpAngle) = 0;

  virtual CATBoolean CATCGMGetVisuData(
    CATEdge *ipEdge,
    CATBody *ipBody,
    CATCGMVisuData *iopCGMVisuData,
    unsigned int RequestedDataMask,
    CATAngle iMinSharpAngle) = 0;

  virtual CATBoolean CATCGMGetVisuData(
    CATFace *ipFace,
    CATBody *ipBody,
    CATCGMVisuData *iopCGMVisuData,
    unsigned int RequestedDataMask) = 0;

  virtual void CATCGMDeleteAllVisuData(CATBody *ipBody, int iDimension) = 0;

  virtual void TopologicalBasic_CATPGMGetBnddFaces(
    CATEdge *iEdge,
    CATBody *inBody,
    CATLISTP(CATFace) &oAdjFaces) = 0;

  virtual void TopologicalBasic_CATPGMDone(CATLoop *iLoop) = 0;

  virtual CATPGMDisconnectGateway *CATCGMCreateDisconnectGateway(CATDisconnectEngine *engine, CATSoftwareConfiguration * iConfig = NULL) = 0;

  virtual void TopologicalBasic_CATPGMGetGlobalSharpness(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace1,
    CATFace *iFace2,
    CATTopSharpness &oSharpness,
    CATOrientation *oOrientation,
    CATShell *iShellOwningTheTwoFaces) = 0;

  virtual CATIPGMChecker *CATPGMCreateBodyChecker(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCheck,
    CATLISTP(CATCell) *iCellsToCheck) = 0;

  virtual CATLiveBody* CATLiveBody_GetLiveBody(CATBody *iBody) = 0;

  virtual void CATLiveBody_GetUserColor(CATGeometricType iType, CATDeclarativeApplication iApplication, int &oR, int &oG, int &oB) = 0;

  virtual CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *iOutputBody,
    CATCGMJournalList *iTopOpJournal) = 0;

  virtual CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateFilletRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateSubdivisionRecognizer() = 0;

  virtual short CATCXTools_CATPGMGetGeometryDimension(CATGeometry *iGeometry) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateCanonicRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateCanonicAdvancedRecognizer() = 0;

  virtual CATBody *CATTopoDebug_CATPGMGetLastBodyContextForDebugOnly(CATTopology *iTopology) = 0;

  virtual void CATTopTools_CATPGMLockOrUnlockUnderLyingGeometry(
    int iLock,
    CATLISTP(CATGeometry) &iListInput) = 0;

  virtual void CATPGMSuppressNonCommonDelete(
    const CATLISTP(CATBody) &iListInBodies,
    const CATLISTP(CATBody) &iListOutBodies,
    const CATLISTP(CATCGMJournal) &iListOutJournals) = 0;

  virtual void CATPGMConcatenateWithoutNonCommonDelete(
    const CATLISTP(CATCGMJournal)& iListOfJournals,
    CATCGMJournalList &oOutputJournal) = 0;

  virtual void CATPGMLSOTraceLevel1or2(
    CATlsoUtilTrace_OperatorName iOpName,
    CATlsoUtilTrace_Level1Prefix iPrefix,
    CATBoolean iWithLineBreak) = 0;

  virtual void CATPGMLSOTraceLevelN(
    CATLONG32 iLevel,
    CATlsoUtilTrace_OperatorName iOpName,
    const char *iText,
    HRESULT *iHResult,
    CATBoolean iWithLineBreak) = 0;

#ifdef CATIAR208
  virtual void CATCXTools_CATPGMGetExpectedCellsForReportingLS(
    CATBody *inBody,
    CATLISTP(CATCellManifold) &ioReportingCells,
    const short iListManage_0Define_1Append) = 0;
#endif

  virtual CATPGMDisconnectGateway *CATPGMCreateDisconnectGateway(
    CATDisconnectEngine *engine,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATTopTools_CATPGMGet2DBoundingBox(
    CATLoop *iLoop,
    CATSurLimits &o2DBoundingBox,
    CATMathBox *ioBox3D,
    CATBoolean iFirstTimeComputedMustBeKept) = 0;

  virtual CATFaceAnalyzer *CATPGMCreateFaceAnalyzer(
    CATSoftwareConfiguration *iConfig,
    CATFace *ipFace,
    CATBoolean iGeometricalRecognition,
    CATBody *ipBody) = 0;

  virtual CATFaceAnalyzer *CATPGMCreateFaceAnalyzer( // A SUPPRIMER
    CATSoftwareConfiguration *iConfig,
    CATFace *ipFace,
    CATBody *ipBody,
    CATBoolean iModeSurface,
    CATBoolean iGeometricalRecognition) = 0;

  virtual CATFaceAnalyzer *CATPGMCreateFaceAnalyzer( // A SUPPRIMER
    CATSoftwareConfiguration *iConfig,
    CATCellManifold *ipCM) = 0;

  virtual CATFaceAnalyzer *CATPGMCreateFaceAnalyzer(
    CATSoftwareConfiguration *iConfig,
    CATCellManifold *ipCM,
    CATLiveBody *ipLiveBody,
    CATBoolean iGeometricalRecognition) = 0;



  virtual CATWallFacesAnalyzer * CATPGMCreateWallFacesAnalyzer(CATGeoFactory            * ipFactory,
                                                               CATSoftwareConfiguration * ipConfig,
                                                               CATFace                  * ipFace1,
                                                               CATFace                  * ipFace2,
                                                               CATBoolean                 iModeSurface,
                                                               CATBoolean                 iCanonicRecognition,
                                                               CATBoolean                 iGeometricalRecognition,
                                                               CATBody                  * ipBody) = 0;



  virtual CATTopAnalysisTools * CATPGMCreateTopAnalysisTools(CATSoftwareConfiguration * ipConfig,
                                                             CATGeoFactory            * ipGeoFactory,
                                                             CATBody                  * ipBody) = 0;

  virtual CATIPGMTopGeometricalMapping *CATPGMCreateTopGeometricalMapping(
    const CATTopData &iTopData,
    const CATLISTP(CATICGMUnknown) &iInputs,
    const CATTopGeometricalMapType iStrategy,
    const CATTopGeoMapping_QueryType iQueries,
    CATGeometricType iFilter) = 0;

  virtual CATIPGMTopGeometricalMapping *CATPGMCreateTopGeometricalMapping(
    const CATTopData &iTopData,
    CATBody *iBody,
    const CATTopGeometricalMapType iStrategy,
    const CATTopGeoMapping_QueryType iQueries,
    CATGeometricType iFilter) = 0;

  virtual int CATTopOperator_CATPGMCleanNewerUnused(CATICGMUnknown *ipBodyOrFactory) = 0;

  virtual int CATTopOperator_CATPGMCleanAnyNewerUnused(CATICGMUnknown *ipBodyOrFactory) = 0;

  virtual CATCGMJournalCompletion *CATPGMCreateCGMJournalCompletion(
    CATListPtrCATBody &ipOldInputs,
    CATBody *ipOldOutput,
    CATCGMJournalList *ipJournal,
    CATSoftwareConfiguration *Config) = 0;

  virtual CATCGMCellTracker *CATCGMCellTrackerImp_CATPGMCreateCellTracker(CATSoftwareConfiguration *iSC) = 0;

  virtual CATBoolean CATTopHiddenSeamCellQuery_CATPGMIsHiddenSeamCell(CATBody *iBody, CATCell *iCell) = 0;

  virtual void CATTopHiddenSeamCellQuery_CATPGMExpandSelection(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oListOfExpandCells,
    CATLISTP(CATCell) &oListOfBorder) = 0;

  virtual CATBoolean CATTopHiddenSeamCellQuery_CATPGMIsActive(CATGeoFactory *iFactory) = 0;

  virtual void CATTopHiddenSeamCellQuery_CATPGMSetActive(CATGeoFactory *iFactory) = 0;

  virtual CATBoolean CATTopTools_CATPGMIsSharingTopology(
    CATTopology *iFirst,
    CATTopology *iWith,
    CATLISTP(CATTopology) *ioSharingFederator) = 0;

  virtual CATIPGMTopologicalOperator *CATPGMCreateTopologicalOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iCreationBody,
    CATSubdContextForFastRunExt *ipCtxExt) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDrivenChamferRecognizer(
    CATIPGMChamferTool *iTool,
    CATLISTP(CATFace)& iRefSupportFaces,
    CATLISTP(CATFace)& iOtherSupportFaces,
    CATLISTP(CATCell)& iCandidateChamferCells) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateChamferManifoldCreator(
    CATIPGMChamferTool *iTool) = 0;

  virtual CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATDomain) &iDomains,
    CATListOfInt &iLocations) = 0;

  virtual CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATDomain) &iDomains) = 0;

  virtual void CATTopJournalTools_CATPGMGetAllGeometries(
    CATCGMJournalList *iJournal,
    unsigned char iGetFirstsAndOrLasts,
    CATCGMHashTable *iCreation,
    CATCGMHashTable *iModification,
    CATCGMHashTable *iSubdivision,
    CATCGMHashTable *iAbsorption,
    CATCGMHashTable *iDeletion,
    CATCGMHashTable *iKeep,
    CATCGMHashTableWithAssoc *iOutputCellWithInfo,
    CATBoolean iGetFaces,
    CATBoolean iGetEdges,
    CATBoolean iGetVertices,
    CATBoolean iWithTass) = 0;

  virtual void CATCGMChain_CATPGMSetCurrentCATCGMChain(CATPGMChain *iChain) = 0;

  virtual CATPGMChain *CATCGMChain_CATPGMGetCurrentCATCGMChain() = 0;
	
  virtual CATDeclarativeManifoldAgent *CATPGMCreateChamferRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateChamferAdvancedRecognizer() = 0;

  virtual int CATCXTools_CATPGMGetDimBody(CATBody *piBody) = 0;

  virtual CATBoolean CATCXTools_CATPGMIsAVolumiqBody(CATBody *piBody) = 0;

  virtual CATPGMExplicitCheck *CATPGMCreateExplicitCheck() = 0;

  virtual CATPGMExplicitCheck *CATPGMCreateExplicitCheck(CATGeoFactory *piGeoFactory,CATSoftwareConfiguration *piSoftConfig) = 0;

  virtual void CATPGMSuppressDeleteInJournal(
    CATCGMJournalList *iInputJournal,
    CATCGMJournalList *oOutputJournal) = 0;

  virtual void CATCXTools_CATPGMAddBorderedCellsInHashTable(CATCGMHashTable *ioHashTableOfCells) = 0;

  virtual CATPGMChain *CATPGMCreateCGMChain(CATGeoFactory *ifactory) = 0;

  virtual CATContextForFastRun * CATPGMCreateContextForFastRunAdaptExt() = 0;

  virtual void TopologicalBasic_CATPGMGetSmoothSkins(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory &iFactory,
    CATLISTP(CATFace) &iFaces,
    CATBody &iBody,
    ListPOfListPOfCATFace    &oSmoothSkins) = 0;

  virtual int CATPGMGetMaxLowDim(CATBody *iBody) = 0;

  virtual void CATTopologicalOperator_CATPGMGetAllCellSupports(
    CATCell *iCell,
    CATLISTP(CATCell) &oListOfCells,
    int iOnlyDirect) = 0;

  virtual HRESULT CATGMLiveSpecChgUtils_CATPGMPutSpecChg(CATManifoldParameter &iCurParam) = 0;

  virtual HRESULT CATGMLiveSpecChgUtils_CATPGMUpdateSpecChg(CATManifoldParameter &iCurParam) = 0;

  virtual HRESULT CATGMLiveSpecChgUtils_CATPGMReleaseSpecChg(CATManifoldParameter &iCurParam) = 0;

  virtual void CATTopTools_CATPGMMinimalPartitionForOrientableSolutions(
    const CATLISTP(CATCell) &inputCells,
    const CATListOfInt &inputOrientations,
    CATBody *iBody,
    CATLISTP(CATConnectedCellsIterator) &oList,
    int &anomaliesDetected) = 0;

  virtual CATDRepNavigatorBridge * CATPGMCreateDRepNavigatorBridge(const CATTopData &iData, CATLiveBody* iLiveBody) = 0;

  virtual CATBoolean CATTopBodyTools_CATPGMIsWithInverseCacheLinks(CATBody *) = 0;

  virtual HRESULT CATTopBodyTools_CATPGMCreateFullSmartBody(
    CATSoftwareConfiguration *iConfiguration,
    CATBody *iBody,
    CATBody *&oBody) = 0;

  /*virtual void CATTopBodyTools_CATPGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    CATBody *&oBody,
    CATBodyFreezeMode iMode,
    int wantingHazardousVersion) = 0;

  virtual void CATTopBodyTools_CATPGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATBody *&oBody,
    CATBodyFreezeMode iMode,
    CATLISTP(CATDomain) *oCreatedDomains,
    int wantingHazardousVersion) = 0;*/

  virtual void CATTopBodyTools_CATPGMGetDomainBoundingCells(
    CATBody *iBody,
    CATLISTP(CATCell) &oListOfCell,
    short iDimension,
    CATDomain *iDomain) = 0;

  virtual void CATTopBodyTools_CATPGMMergeBodies(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iList,
    CATBody *&oBody,
    CATBodyFreezeMode iMode) = 0;

  virtual void CATTopBodyTools_CATPGMInvertWire(CATGeoFactory *iFactory, CATBody *iWireBody, CATBody *&oBody) = 0;

  virtual int CATTopBodyTools_CATPGMGetInfinite(CATBody *) = 0;

  virtual void CATTopBodyTools_CATPGMChainingSmart(CATBody *iInputBody, CATBody *iOutputBody) = 0;

  virtual void CATTopBodyTools_CATPGMChainingSmart(
    const CATLISTP(CATBody) &iInputBodies,
    CATBody *iOutputBody) = 0;

  virtual void CATTopBodyTools_CATPGMInactivate(CATBody *) = 0;

  virtual void CATTopBodyTools_CATPGMForceActivate(CATBody *) = 0;

  virtual HRESULT CATTopBodyTools_CATPGMCreateFullSmartBody(
    CATSoftwareConfiguration *iConfiguration,
    CATBody *iBody,
    CATBody *&oBody,
    const CATBoolean iWithBoundixBox) = 0;

  virtual CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
    const CATUnicodeString &iRoleOfOutput,
    CATBody *iInputBody,
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATDomain) &iDomains,
    CATListOfInt &iLocations) = 0;

  virtual CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
    const CATUnicodeString &iRoleOfOutput,
    const CATLISTP(CATBody) &iInputBodies,
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATDomain) &iDomains) = 0;

  virtual CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
    const CATUnicodeString &iRoleOfOutput,
    const CATLISTP(CATBody) &iInputBodies,
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATDomain) &iDomains,
    CATListOfInt &iLocations) = 0;

  virtual void CATTopTools_CATPGMComputeAngleOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    const CATCrvParam &iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATAngle &oAngle) = 0;

  virtual void CATTopTools_CATPGMComputeAverageAngleOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    CATCrvParam *iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATAngle &oAngle,
    const short iNbSamples) = 0;

  virtual void CATTopTools_CATPGMCalcLength(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATBoolean iExact,
    double &oLength) = 0;

  /*virtual void CATTopBodyTools_CATPGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode,
    int wantingHazardousVersion) = 0;

  virtual void CATTopBodyTools_CATPGMBuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode,
    CATLISTP(CATDomain) *oCreatedDomains,
    int wantingHazardousVersion) = 0;*/

  virtual void CATTopBodyTools_CATPGMMergeBodies(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iList,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode) = 0;

  virtual void CATTopBodyTools_CATPGMIsRunningTessOperator(CATBody *) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateExtrusionManifoldCreatorBase() = 0;

  virtual void TopologicalBasic_CATPGMGetBnddFaces(
    CATLISTP(CATEdge) &iEdgeList,
    CATBody *inBody,
    CATLISTP(CATFace) &oAdjFaces) = 0;

  virtual void CATTopTools_CATPGMComputeAdvancedAnglesOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    CATCrvParam *iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATListOfDouble &ioListOfMinMaxAvgAngles,
    CATListOfDouble &ioListOfMinMaxAvgParams,
    const short iNbSamples) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreatePadPocketManifoldCreator() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateHoleManifoldCreator() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateSlotManifoldCreator() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateNotchManifoldCreator() = 0;

  virtual void CATTopTools_CATPGMComputeGlobalSharpness(
    CATCrvParam PoecCrv[2],
    CATOrientation EdgeCurveOrientation,
    CATEdgeCurve *EdgeCurve,
    CATPCurve *PCurve[2],
    CATBoolean FirstFaceIsLeft,
    CATSide MattSideFace[2],
    CATOrientation faceOrient[2],
    CATSurface *Surface[2],
    CATTopSharpness &oSharpness,
    CATAngle *ioWantingAngleInMiddle,
    CATAngle iMaxSmoothnessAngle) = 0;

  virtual void CATTopTools_CATPGMComputeLocalSharpness(
    const CATCrvParam &iParamOnEdgeCurve,
    CATOrientation EdgeCurveOrientation,
    CATEdgeCurve *EdgeCurve,
    CATPCurve *PCurve[2],
    CATBoolean FirstFaceIsLeft,
    CATSide MattSideFace[2],
    CATOrientation faceOrient[2],
    CATSurface *Surface[2],
    CATTopSharpness &oSharpness,
    CATAngle &Angle,
    CATAngle iMaxSmoothnessAngle) = 0;

  virtual int CATTopTools_CATPGMGetBnddFacesOnShell(
    CATEdge *iEdge,
    CATShell *iShell,
    CATBody *iBody,
    CATFace *oFaces[],
    const int SizeoFaces) = 0;

  virtual CATAngle CATTopTools_CATPGMAverageAngleComputation(
    CATEdge *iEdge,
    CATFace *iFace[2],
    CATBoolean iFirstFaceIsLeft) = 0;

  virtual CATDRepNavigatorInterface *CATPGMCreateDRepNavigatorInterface(
    CATSoftwareConfiguration *iSoftConf,
    CATBody *iBody) = 0;

  virtual CATPGMIntersectFilteringTools *CATPGMCreateIntersectFilteringTools(
    CATBody *ipBody1,
    CATBody *ipBody2) = 0;

  virtual CATPGMDRepBehavior *CATPGMCreateDRepBehavior(
    CATDeclarativeContext *iDeclarativeContext,
    CATDeclarativeApplication iDeclarativeApplication) = 0;

  virtual CATPGMDRepBehavior *CATPGMCreateDRepBehavior(
    CATDeclarativeContext *iDeclarativeContext,
    CATDeclarativeApplication iDeclarativeApplication,
    CATDeclarativeOriginModeler iDeclarativeOriginModeler) = 0;

  virtual CATDeclarativeContext *CATPGMCreateDeclarativeContextForPaste(
    const CATLiveBody *iLiveBody,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATBoolean CATPGMIsAllowedForPaste (
    CATGeoFactory *iFactory, 
    CATBody *iBodyToPaste, 
    CATDeclarativeContext *iContextToCompare, 
    CATSoftwareConfiguration * iConfig) = 0;

  virtual HRESULT CATPGMAttachContextForCopy(
    CATBody *iCopyBody,
    CATDeclarativeContext *iContextToAttach,
    CATSoftwareConfiguration * iConfig) = 0;

  virtual CATDeclarativeContextCompatibility CATPGMCompareContextBeforePaste(
    CATBody *iCopyBody,
    CATDeclarativeContext *iContextToCompare,
    CATSoftwareConfiguration * iConfig) = 0;

    virtual HRESULT CATPGMTopGN_CommonEdges(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaceList_1,
    const CATLISTP(CATCell) &iFaceList_2,
    CATLISTP(CATCell) &ioResult,
    CATListOfLong &ioListOrientation,
    CATListOfLong &ioNbOfEdgesByDomain,
    CATCGMVersionCommonEdges iVersion,
    CATBoolean iFirstListIsMatterSideLeft,
    CATLISTP(CATConnectedCellsIterator) *iPtrLocalCellsIterators) = 0;

  virtual HRESULT CATPGMTopGN_CommonEdges(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaceList_1,
    const CATLISTP(CATCell) &iFaceList_2,
    CATLISTP(CATCell) &ioResult,
    CATListOfLong &ioListOrientation,
    CATLISTP(CATDomain) &ioListOfCATDomains,
    CATListOfLong &ioNbOfEdgesByDomain,
    CATCGMVersionCommonEdges iVersion,
    CATBoolean iFirstListIsMatterSideLeft,
    CATLISTP(CATConnectedCellsIterator) *iPtrLocalCellsIterators) = 0;

  virtual HRESULT CATPGMTopGN_CommonEdges(
    CATBody * iBody,
    CATSoftwareConfiguration * iConfig,
    const ListPOfListPOfCATTopology & iCellLists,
    ListPOfCATIPGMTopGNCommonEdgeData & oEdgeDataList) = 0;

  virtual HRESULT CATPGMTopGN_CommonEdges(
    CATBody *iBody,
    CATSoftwareConfiguration * iConfig,
    const ListPOfListPOfCATCell &iCellLists,
    ListPOfCATIPGMTopGNCommonEdgeData &oEdgeDataList) = 0;

  virtual CATBoolean CATTopoDebug_CATPGMIsTemporaryInactive() = 0;

  virtual CATBoolean CATTopoDebug_CATPGMSetTemporaryInactive(CATBoolean iInactivated) = 0;

  virtual HRESULT CATTopJournalTools_CATPGMComputeJournalOfDomains(
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *piOutputBody,
    CATCGMJournalList *piCGMJournalList,
    CATCGMJournalList *&pioCGMJournalListOfDomains) = 0;

  virtual CATEdge *CATTopTools_CATPGMCreateEdgeFromCurve(
    CATGeoFactory *iGeoFactory,
    CATCurve *iCurve,
    CATBody *iBody) = 0;

  virtual CATIPGMExplicitCheckOperator *CATPGMCreateExplicitCheckOperator(
     CATGeoFactory *piFactory,
     CATSoftwareConfiguration *piConfig) = 0;

  virtual CATIPGMEdgeToCanonic *CATPGMCreateEdgeToCanonic(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdgeToCanonic,
    CATSkillValue iMode) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer(double iMaxRadius) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer(
    CATRecognizerContext &iRecognizerContext) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDraftRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDraftAdvancedRecognizer() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDraftAdvancedRecognizer(
    CATRecognizerContext &iRecognizerContext) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateLogoRecognizer() = 0;

  virtual CATPGMODTScaleManager *CATPGMCreateODTScaleManager() = 0;

  virtual CATGeometry *CATPGMGetDeclarativeReference(CATGeometry *ipGeometry) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateChamferAdvancedRecognizer(
    CATRecognizerContext &iRecognizerContext) = 0;

  virtual void CATCXTools_CATPGMGetExpectedCellsForReporting(
    CATBody *inBody,
    CATLISTP(CATCell) &ioReportingCells,
    const short iListManage_0Define_1Append,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2) = 0;

  virtual void CATCXTools_CATPGMGetExpectedCellsForReporting(
    CATBody *inBody,
    CATCellHashTable *&ioReportingCells,
    const short iListManage_0Define_1Append,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2) = 0;

  virtual CATBoolean CATTopTools_CATPGMIsACGMExactTopology(CATTopology *iTopoInterface) = 0;

  virtual CATBoolean CATTopTools_CATPGMIsACGMPolyhedralTopology(CATTopology *iTopoInterface) = 0;

  virtual double CATTopTools_CATPGMGetCurvatureStep(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody,
    CATEdge *iEdge,
    const double iReferenceCurvature) = 0;

  virtual CATIPGMDRepGroupThread * CATIPGMCreateDRepGroupThread(const CATLISTP(CATCellManifold) &iCellManifoldGroup, 
                                                      const CATLISTP(CATCellManifold) &iCellManifoldContext, CATMathAxis &iAxis, 
                                                      double iDepth, double iDiameter, double iNominalDiameter, double iPitch, int iSens, double iSupportDiameter, 
                                                      CATString &iThreadDescription, int iThreadType, int iDisplayInDrafting, CATString &iKeyOfThread) = 0;

  virtual void CATPGMAPTStart(const char *ipName) = 0;

  virtual void CATPGMAPTEnd(CATBoolean iIsOK) = 0;

  virtual void CATPGMAPTEnv(const char *ipName) = 0;

  virtual void CATPGMAPTMsg(const char *ipName) = 0;

  virtual void CATPGMAPTSetActivation(CATBoolean iActivation) = 0;

  virtual CATBoolean CATPGMAPTGetActivation() = 0;

  virtual void CATPGMAPTSetConsole(CATBoolean iConsole) = 0;

  virtual CATBoolean CATPGMAPTGetConsole() = 0;

  virtual void CATPGMAPTSetDepth(int iDepth) = 0;

  virtual int CATPGMAPTGetDepth() = 0;

  virtual int CATPGMAPTGetLevel() = 0;

  virtual CATBoolean TopologicalBasic_CATPGMIsRectangularShape(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATSurLimits &oLimits) = 0;
  virtual CATBoolean CATLiveShapeServices_CATPGMAreVisuallyIdenticalFaces(
    CATFace &iPreviousFace,
    CATFace &iResultFace,
    CATGeoFactory &iFactory,
    CATSoftwareConfiguration *ipConfig) = 0;

  virtual CATDoubleManifoldParam  * CATCreateDoubleManifoldParam(int iKey, int iDescription, double iValue) = 0;
  virtual CATIntManifoldParam     * CATCreateIntManifoldParam(int iKey, int iDescription, int iValue) = 0;
  virtual CATVectorManifoldParam  * CATCreateVectorManifoldParam(int iKey, int iDescription, const CATMathVector & iValue) = 0;
  virtual CATTransfoManifoldParam * CATCreateTransfoManifoldParam(int iKey, int iDescription, const CATMathTransformation & iValue) = 0;
  virtual CATNullManifoldParam    * CATCreateNullManifoldParam(int iKey, int iDescription) = 0;

  virtual CATManifoldParamId * CATLoadManifoldParamId(CATMathStream &ioStr) = 0;

  virtual HRESULT              CATLoadManifoldParamIdWithoutValue(CATMathStream &ioStr, CATManifoldParamId *& oManifoldParamId) = 0;


  virtual void CATTopTools_CATPGMGetBorderEdges(
    CATLISTP(CATFace) const &iFaces,
    CATLISTP(CATEdge) &oEdges,
    CATLISTP(CATFace) &oBorderFaces) = 0;


  virtual CATBody *CATTopTools_CATPGMCreateBodyWithTheSameTypeOf(
    CATTopology   * iTopoItfRef,
    CATGeoFactory * iGeoFactory,
    CATBodyMode     iMode) = 0;

  virtual CATVertex *TopologicalBasic_CATPGMCreateVertex(
    CATBody *ipBodyCreator,
    CATPointOnEdgeCurve *ipPOEC) = 0;

  virtual CATEdge *TopologicalBasic_CATPGMCreateEdge(
    CATBody *ipBodyCreator,
    CATEdgeCurve *ipEdgeCurve,
    CATOrientation iOriEdgeCurveVsEdge,
    CATPointOnEdgeCurve *ipStartPOEC,
    CATPointOnEdgeCurve *ipEndPOEC) = 0;

  virtual void CATTopTools_CATPGMGetFaces(
    const CATLISTP(CATCell) &iListOfCells,
    CATLISTP(CATFace) &oListOfFaces) = 0;

  virtual void CATTopTools_CATPGMGetCells(
    const CATLISTP(CATFace) &iListOfFaces,
    CATLISTP(CATCell) &oListOfCells) = 0;


  virtual CATPlane *CATTopBodyTools_CATPGMGetInfinitePlanarBodySurface(
    CATBody *iBody,
    CATOrientation *oOriPlaneVsBody) = 0;

  virtual CATBoolean CATTopTools_CATPGMGetInfinite(CATDomain *iDomain) = 0;

  virtual void CATCXTools_CATPGMTransferTopData(
     CATCGMOperator *piCGMOperator, 
     CATTopData *piTopData) = 0;

  virtual void CATCXTools_CATPGMTransferFreezeMode(
    CATCGMOperator *piCGMOperator,
    CATBodyFreezeMode iMode) = 0;

  virtual CATBoolean CATTopBodyTools_CATPGMIsAnInfiniteLinearBody(
    CATBody *iBody,
    CATMathLine *oInfiniteLine) = 0;

  virtual CATBoolean CATTopBodyTools_CATPGMIsBodyPolyLinearCompliant(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody,
    CATBoolean *oIsAnInfiniteLinearBody) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateButtonManifoldGlobalRecognizer() = 0;

  virtual CATBoolean VerifyShellsAreCompletelySplitting(
    CATGeoFactory * ipFactory,
    CATSoftwareConfiguration * ipConfig,
    CATBody * ipShellsBody,
    CATBody * ipSupportBody) = 0;

  virtual CATBoolean CATLiveBodyValidityServices_CATPGMPassedForValidation(const CATLISTP(CATBody) &iBodyList) = 0;

  virtual CATBoolean CATTopBodyTools_CATPGMIsAStraightBody(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody) = 0;

  virtual int CATTopBodyTools_CATPGMGetNbPolySubElementsFromBody(
    CATBody *iBody,
    int      &oPolyGeoDimension012) = 0;

  virtual void CATCXTools_CATPGMGetExpectedCellsForReporting_Helper(
    CATBody *inBody,
    CATLISTP(CATCell) &ioReportingCells,
    const short iListManage_0Define_1Append,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2) = 0;

  virtual CATIPGMDRepLabelServices *CATPGMCreateGMDRepLabelServices(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) &iInputBodyList,
    CATLISTP(CATBody) &iOutputBodyList,
    CATCGMJournalList *iCMJournal) = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampLocalRecognition() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampGlobalRecognition() = 0;

  virtual CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampCreator() = 0;
  
#ifdef CATIACGMR421CAA
  virtual HRESULT CATTopImprintCellServices_CATPGMGetStandardAndImprintJournal(
    CATSoftwareConfiguration *piSoftConfig,
    CATCGMJournalList *piMasterJournal,
    CATCGMJournalList *&pioStandardAndImprintJournal) = 0;
#endif

  virtual CATPGMCellSupportOfConstraintService *CATPGMCreateCellSupportOfConstraintService(
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATPointOnEdgeCurve *TopologicalBasic_CATPGMGetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge) = 0;

    virtual void CATlsoJournalUtil_CATPGMCompleteMinimalValidJournal(
    CATLISTP(CATBody) &iInputCopyBodies,
    CATLISTP(CATBody) &iInputNoCopyBodies,
    CATBody *iResultBody,
    CATCGMJournalList &ioCellJournal) = 0;

  virtual CATBoolean CATTopTools_CATPGMIsCellSmooth(
    CATTopData &iTopData,
    CATCell *iCell,
    CATCell *iIncidCell1,
    CATCell *iIncidCell2) = 0;

  virtual CATPGMDRepLabelUtilities *CATPGMCreateGMDRepLabelUtilities(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATBody) &iInputBodyList,
    CATLISTP(CATBody) &iOutputBodyList,
    CATCGMJournalList *iCMJournal) = 0;

  virtual CATPGMDRepLabelUtilities *CATPGMCreateGMDRepLabelUtilities(
    CATSoftwareConfiguration * iConfig) = 0;

  virtual CATManifoldModification * CATCreateManifoldModification(const ListPOfCATBody &iSystemBodies, 
                                                                  const CATDRepLabel *ipLabel, 
                                                                  CATManifoldParamId * ipParamId,
                                                                  CATSoftwareConfiguration *iConfig) = 0;

  virtual CATManifoldModification * CATCreateManifoldModification(const ListPOfCATBody &iSystemBodies, 
                                                                  CATManifold          *iManifold, 
                                                                  CATManifoldParamId   *ipParamId,
                                                                  CATSoftwareConfiguration *iConfig) = 0;

  virtual HRESULT CATLoadManifoldModifWithoutValue(CATMathStream &ioStream, CATICGMContainer *iFactory, CATManifoldModification *& oLoadManifoldModif) = 0;

  virtual CATManifoldModification * CATLoadManifoldModification(CATCGMStream &ioStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *iConfig) = 0;

  virtual HRESULT CATLoadDRepLabel(CATMathStream &ioStr, CATDRepLabel *&oDRepLabel) = 0;

  virtual CATDRepLabelRequest * CATCreateDRepLabelRequest(CATBody * ipBody,      const CATDRepLabel * ipDRepLabel, CATSoftwareConfiguration * ipConfig) = 0;
  virtual CATDRepLabelRequest * CATCreateDRepLabelRequest(CATBody * ipBody,      CATManifold        * ipManifold,  CATSoftwareConfiguration * ipConfig) = 0;
  virtual CATDRepLabelRequest * CATLoadDRepLabelRequest(CATMathStream &ioStream, CATICGMContainer   * iFactory,    CATSoftwareConfiguration * ipConfig) = 0;

  virtual CATIPGMMultiProcRunner * CATPGMCreateMultiProcRunner (CATGeoFactory * iFactory, const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal) = 0;

  virtual CATIPGMTopGNCommonTopologyData * CATIPGMCreateTopGNCommonTopologyData(CATTopology * iCommonTopology, const ListPOfCATTopology & iBordTopoList, const CATListOfInt &iBordTopoIdxList) = 0;

  virtual CATIPGMTopGNCommonEdgeData * CATIPGMCreateTopGNCommonEdgeData(CATEdge *iCommonEdge, const ListPOfCATTopology & iBordTopoList, const CATListOfInt & iBordTopoIdxList, CATOrientation iOrient, CATDomain * iUppDomain) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework NewTopologicalObjects.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMModelInterfaces CATIPGMNewTopoObjItfBldr *CATCGMGetNewTopoObjItfBldr();

#endif /* CATIPGMNewTopoObjItfBldr_h */
