#ifndef CATIPGMTopologicalOpeItfBldr4_h
#define CATIPGMTopologicalOpeItfBldr4_h

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
#include "CATSkillValue.h"
#include "CATSubdIntersectingFunction.h"
#include "CATGMLiveShapeSelectFacePropagateMode.h"
#include "ListPOfCATEdge.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATIPGMGlobalThicknessAnalyserOpe.h" // For Thickness type
#include "CATIPGMTopSightDistanceChecker.h"
#include "CATIPGMTopRelimitBodyByBox.h"

class CATIPGMManifoldEditor;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATLISTP(CATFace);
class CATIPGMWirePolyline;
class CATMathPoint;
class CATCGMJournalList;
class CATIPGMBRepToDRepOperator;
class CATICGMTopExtrapolWireOpe;
class CATIPGMTopExtrapolWireOpe;
class CATCompositeLaw;
class CATFace;
class CATSurParam;
class CATMathVector;
class CATPersistentBody;
class CATIPGMShellOperator;
class CATIPGMRemoveEdge;
class CATICGMRemoveEdge;
class CATIPGMFuzzyExtrapolOpe;
class CATICGMFuzzyExtrapol;
class CATIPGMLiveShapeSelectFaceOpe;
class CATIPGMTopFaceReplaceSurface;
class CATIPGMMidSurfaceOperator;
class CATIPGMMidSurfaceAdvancedOperator;
class CATGMLiveShapeRunOptions;
class CATICGMDistanceTool;
class CATPGMChain;
class CATIPGMTopTrimMultiShellByWires;
class CATIPGMTopTrimMultiWiresByVertices;
class CATIPGMTopAdaptiveClone;
class CATLISTP(CATBody);
class CATICGMTopFaceReplaceSurface;
class CATIPGMDynVertexChamfer;
class CATVertex;
class CATCell;
class CATIPGMTopDisconnectOneCellOnly;
class CATDeclarativeContext;
class CATSoftwareConfiguration;
class CATIPGMTopMultiTrimPieces;
class CATPersistentCellInfra;
class CATPGMBodyAnalyzer;
class CATPGMTrdReportBody;
class CATICGM2DBoxComputation;
class CATIPGM2DBoxComputation;
class CATIPGMTopRelimitBody;
class CATIPGMAdvancedStampOpe;
class CATIPGMAutoFilletBiW;
class CATFaceHashTable;
class CATIPGMBodySymmetryOpe;
class  CATLISTP(CATFace);
class CATIPGMClosedFilletRibbonFinder;
class CATMathAdvancedBox;
class CATIPGMLimitingBodyCreatorOpe;
class CATIPGMVolumeMergerOpe;
class CATVolume;
class CATIPGMRibbonPropagationFinder;
class CATIPGMFilletRibbonAroundRibFinder;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalOpeItfBldr4;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr4: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual const CATString *CATGMLiveShapeSelectFaceOpe_CATPGMGetDefaultOperatorId() = 0;

  virtual CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
    CATTopData *iTopData,
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) *iStoppingFaces) = 0;
   
  virtual CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
    CATTopData *iTopData,
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    const CATLISTP(CATCell) *iStoppingCells) = 0;

  virtual CATIPGMWirePolyline *CATPGMCreateWirePolyline(
    CATGeoFactory *iFactory,
    const int numberOfPoints,
    CATMathPoint **points,
    CATCGMJournalList *iReport) = 0;

  virtual CATIPGMWirePolyline *CATPGMCreateWirePolyline(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const int numberOfPoints,
    CATMathPoint **points) = 0;

  virtual CATICGMTopExtrapolWireOpe *CATCGMCreateTopExtrapolWireOpe(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iBodyWire,
    CATBody *iBodyShell) = 0;

  virtual CATIPGMTopExtrapolWireOpe *CATPGMCreateTopExtrapolWireOpe(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iBodyWire,
    CATBody *iBodyShell) = 0;

  virtual CATSubdIntersectionType CATShellOperator_CATPGMFacesIntersectionType(
    CATFace *iFace1,
    CATFace *iFace2) = 0;

  virtual CATIPGMShellOperator *CATPGMCreateShellOperator(
    CATBody *iBody,
    CATLength iInternalOffsetValue,
    CATLength iExternalOffsetValue,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMShellOperator *CATPGMCreateShellOperator(
    CATBody *iBody,
    CATTopData *iTopData,
    CATLength iInternalOffsetValue,
    CATLength iExternalOffsetValue) = 0;

  virtual CATIPGMRemoveEdge *CATPGMCreateRemoveEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMRemoveEdge *CATPGMCreateRemoveEdge(CATTopData *iTopData, CATBody *iBody) = 0;

  virtual CATIPGMTopFaceReplaceSurface *CATPGMCreateFaceReplaceSurfaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATGMLiveShapeRunOptions *CATPGMCreateGMLiveShapeDefaultRunOptions() = 0;

  virtual CATGMLiveShapeRunOptions *CATPGMCreateGMLiveShapeRunOptionsForDeformPreview() = 0;

   virtual CATICGMRemoveEdge *CATCGMCreateRemoveEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMTopTrimMultiShellByWires *CATPGMCreateTrimMultiShellByWires(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) &iSplittingBodies,
    CATLISTP(CATBody) &iSkinBodies) = 0;

   virtual CATIPGMTopTrimMultiWiresByVertices *CATPGMCreateTrimMultiWiresByVertices(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) &iSplittingBodies,
    CATLISTP(CATBody) &iSkinBodies) = 0;

  virtual CATIPGMTopAdaptiveClone *CATPGMCreateTopAdaptiveClone(
    CATGeoFactory *iFactory,
    CATTopData &iTopData) = 0;

  virtual CATICGMTopFaceReplaceSurface *CATCGMCreateFaceReplaceSurfaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynVertexChamfer *CATPGMCreateDynVertexChamfer(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynVertexChamfer *CATPGMCreateDynVertexChamfer(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    CATVertex *iVertex,
    const CATLISTP(CATEdge) &iEdges,
    const CATListOfDouble &iSetbacks) = 0;

  virtual CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToDisconnect,
    CATCell *ipCellToDisconnect,
    CATBody *ipDisconnectingBody) = 0;

  virtual CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToDisconnect,
    CATCell *ipCellToDisconnect,
    const CATLISTP(CATBody) &iDisconnectingBodies) = 0;
  
  virtual CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToDisconnect,
    const CATLISTP(CATCell) &iCellsToDisconnect,
    const CATLISTP(CATBody) &iDisconnectingBodies) = 0;

  virtual CATIPGMBRepToDRepOperator *CATPGMCreateBRepToDRepOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATDeclarativeApplication iAppli,
    CATDeclarativeContext &iContext,
    CATDeclarativeOriginModeler iModeler) = 0;

  virtual CATIPGMBRepToDRepOperator *CATPGMCreateBRepToDRepOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual const char *CATGMLiveShapeSelectFaceOpe_CATPGMGetPropagationName(
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFaces(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) &oResultFaceList,
    CATLISTP(CATFace) *iStoppingFaces,
    CATBoolean iLiveBodyAllowed,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMFuzzyExtrapolOpe *CATPGMCreateFuzzyExtrapolOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iReferenceBody) = 0;

  virtual CATICGMFuzzyExtrapol *CATCGMCreateFuzzyExtrapol(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iReferenceBody) = 0;

  virtual CATIPGMTopMultiTrimPieces *CATPGMCreateMultiTrimPieces(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) &iSplittingBodies,
    CATLISTP(CATBody) &iPieceBodies) = 0;
  virtual CATICGM2DBoxComputation *CATCGMCreate2DBoxComputation(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATFace *ipInputFace) = 0;

  virtual CATICGM2DBoxComputation *CATCGMCreate2DBoxComputation(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATEdge *ipInputEdge,
    CATFace *ipSupportFace) = 0;

  virtual CATIPGM2DBoxComputation *CATPGMCreate2DBoxComputation(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATFace *ipInputFace) = 0;

  virtual CATIPGM2DBoxComputation *CATPGMCreate2DBoxComputation(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATEdge *ipInputEdge,
    CATFace *ipSupportFace) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFaces(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) &oResultFaceList,
    CATLISTP(CATFace) *iStoppingFaces,
    CATBoolean iLiveBodyAllowed,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iTestTypeMode) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFaces(
    CATPersistentBody *iPersistentBody,
    CATPersistentCellInfra &iInfra,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) &oResultFaceList,
    CATLISTP(CATFace) *iStoppingFaces,
    CATBoolean iLiveBodyAllowed,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iTestTypeMode) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesWithAnglePropagation(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATAngle iPropagationMaxRadAngle,
    CATLISTP(CATFace) &oResultFaceList,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iLiveBodyAllowed) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesInRangeRibbons(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody,
    double iMinRadius,
    double iMaxRadius,
    CATLISTP(CATFace) &oResultFaceList,
    const CATLISTP(CATFace) *iSubBodyFaceList) = 0;

	virtual HRESULT CATPGMLiveShapeSelectFacesWithMoveExtension(
		CATSoftwareConfiguration *iConfig,
		CATBody *iBody,
		const CATLISTP(CATFace) &iInputFaceList,
		const CATMathTransformation *ipMathTransformation,
		CATLISTP(CATFace) &oResultFaceList) = 0;


  virtual CATBoolean CATPGMLiveSelectFaceReverseDepressionProtrusion(
    CATBody *ipBody,
    CATFace *ipFace,
    CATSoftwareConfiguration *ipConfig,
    CATMathPoint &i3DClickPoint,
    CATMathDirection &iSightDirection) = 0;

  //virtual CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
  //  CATTopData *iTopData,
  //  CATPersistentBody *iPersistentBody,
  //  CATPersistentCellInfra &iInfra,
  //  const CATLISTP(CATFace) &iInputFaceList,
  //  CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
  //  CATLISTP(CATFace) *iStoppingFaces) = 0;

  virtual HRESULT CATPGMGlobalThicknessAnalyse(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig, 
    double & oResultThickness,
    CATIPGMGlobalThicknessAnalyserOpe ::ThicknessType iThicknessType) = 0;

  virtual HRESULT CATPGMGlobalThicknessAnalyse(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig, 
    double &oResultMaxThickness,
    double &oResultMaxThicknessLimit) = 0;

  virtual HRESULT CATPGMGlobalThicknessAnalyse(
    CATBody *iBody,
    CATSoftwareConfiguration *iConfig, 
    double &oResultMaxThickness,
    CATLISTP(CATFace) &oLateralFaceList,
    CATBoolean iComputePairingThickness = FALSE) = 0;

  virtual CATIPGMGlobalThicknessAnalyserOpe *CATPGMCreateGlobalThicknessAnalyserOpe(
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATPGMBodyAnalyzer *CATPGMCreateBodyAnalyzer(
    CATGeoFactory &iFactory,
    CATSoftwareConfiguration &iConfig,
    CATLISTP(CATBody) &iBodies) = 0;

  virtual CATPGMTrdReportBody *CATPGMCreateTrdReportBody() = 0;

  virtual CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToDisconnect,
    const CATLISTP(CATBody) &iDisconnectingBodies) = 0;

  virtual CATIPGMTopRelimitBody *CATPGMCreateTopRelimitBody(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *iTrimmingBody,
    CATBody *iRelimitedBody,
    int iSideToKeep) = 0;

  virtual CATIPGMTopRelimitBodyByBox *CATPGMCreateTopRelimitBodyByBox(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToRelimit,
    const CATMathAdvancedBox &iAdvBox) = 0;

  virtual CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    double iFilletRadius,
    CATMathDirection &iPullDir,
    CATAngle &iDraftAngle,
    double iAdvancedStampHeight) = 0;

  virtual CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATLISTP(CATEdge) &iInputEdgeList,
    double iFilletRadius,
    CATMathDirection &iPullDir,
    CATAngle &iDraftAngle,
    double iAdvancedStampHeight) = 0;

  virtual CATIPGMAutoFilletBiW *CATPGMCreateAutoFilletBiW(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    const CATBoolean iConvexFirst) = 0;

  virtual CATIPGMLiveShapeSelectFaceOpe *CATPGMCreateLiveSelectFaceOpe(
    CATTopData *iTopData,
    CATBody *iBody,
    const CATFaceHashTable &iInputFaceHT,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    const CATCellHashTable *iStoppingCells) = 0;

  virtual CATIPGMLiveShapeSelectFaceOpe * CATPGMCreateLiveSelectFaceOpe(
    CATTopData                            * iTopData,
    CATBody                               * iInputBody,
    CATBody                               * iLimitingBody,
    CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
    const CATLISTP(CATFace)               * iSubFaceList) = 0;

  virtual CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATBody &iOpenCurveBody,
    double iFilletRadius,
    CATMathDirection &iPullDir,
    CATAngle &iDraftAngle,
    double iAdvancedStampHeight) = 0;

  virtual CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATOrientation iKeepTopOrBottom,
    double iFilletRadius,
    CATMathDirection &iPullDir,
    CATAngle &iDraftAngle,
    double iAdvancedStampHeight) = 0;

  virtual CATIPGMAdvancedStampOpe *CATPGMCreateGMAdvancedStampOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATOrientation iKeepTopOrBottom,
    CATBody &iOpenCurveBody,
    CATOrientation iKeepRightOrLeft,
    double iFilletRadius,
    CATMathDirection &iPullDir,
    CATAngle &iDraftAngle,
    double iAdvancedStampHeight) = 0;

  virtual CATIPGMBodySymmetryOpe *CATPGMCreateGMBodySymmetryOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iFirstBody,
    CATBody &iSecondBody,
    CATMathPlane &iMirrorPlane) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesWithAngleByConvexityPropagation(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATAngle iPropagationMaxRadConvexAngle,
    CATAngle iPropagationMaxRadConcaveAngle,
    CATLISTP(CATFace) &oResultFaceList,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iLiveBodyAllowed,
    CATLISTP(CATFace) * iStoppingFaces) = 0;

  virtual CATIPGMTopSightDistanceChecker *CATPGMCreateTopSightDistanceChecker(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody) = 0;

  virtual CATIPGMClosedFilletRibbonFinder *CATPGMCreateClosedFilletRibbonFinder(
    CATGeoFactory &iFactory,
    CATSoftwareConfiguration &iConfig,
    CATBody &iBody) = 0;

  virtual CATIPGMLimitingBodyCreatorOpe *CATPGMCreateLimitingBodyCreatorOpe(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody,
    CATFace *iLimitedFace) = 0;

  virtual CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATVolume &iFirstVolume,
    CATVolume &iSecondVolume) = 0;

  virtual CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATLISTP(CATCell) &iVolumeList) = 0;

   virtual CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATCellHashTable &iVolumeHT) = 0;

  virtual CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iBody,
    CATCellHashTable &iVolumeHT,
    CATFaceHashTable &iInterfaceHT) = 0;

  virtual CATIPGMRibbonPropagationFinder *CATPGMCreateRibbonPropagationFinder(
    CATGeoFactory& iFactory,
    CATSoftwareConfiguration& iConfig,
    CATBody& iBody) = 0;

  virtual CATIPGMFilletRibbonAroundRibFinder* CATPGMCreateFilletRibbonAroundRibFinder(
    CATGeoFactory& iFactory,
    CATSoftwareConfiguration& iConfig,
    CATBody& iBody) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOpe3rators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr4 *CATCGMGetTopologicalOpeItfBldr4();

#endif /* CATIPGMTopologicalOpeItfBldr4_h */
