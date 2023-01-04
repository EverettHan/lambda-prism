#ifndef CATIPGMNewTopoObjGMOpeItfBldr_h
#define CATIPGMNewTopoObjGMOpeItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "CATGeometryType.h"
#include "CATListOfULONG32.h"
#include "CATGMLiveShapeSelectFacePropagateMode.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"

class CATICGMRecomposeShells;
class CATIPGMRecomposeShells;
class CATICGMTopSewSkin;
class CATIPGMTopSewSkin;
class CATICGMTopCAACompliantJournalChecker;
class CATIPGMGeoPublishOperator;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATCGMJournalList;
class CATSoftwareConfiguration;
class CATICGMObject;
class CATGeometry;
class CATIPGMTopSplitShellByWires;
class CATICGMTopClashOperator;
class CATIPGMTopClashOperator;
class CATIPGMTopPositionPtFaceOperator;
class CATICGMTopPositionPtFaceOperator;
class CATSurParam;
class CATFace;
class CATShell;
class CATIPGMTopVoBOperator;
class CATIPGMSmartifyBody;
class CATIPGMCellManifoldGroupOperator;
class CATCellManifoldGroupLayer;
class CATIPGMTopGeoSimplify;
class CATCell;
class CATMathPoint;
class CATIPGMLiveShapeSelectFaceBasicOpe;
class CATLISTP(CATFace);
class CATLISTP(CATManifoldParameter);
struct CATCGMVoBCheckOptions;
class CATLISTP(CATBody);
class CATLISTP(CATCell);
class CATLISTP(CATManifold);
class CATIPGMTopExtrusionConverger;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMNewTopoObjGMOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework NewTopologicalObjects.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMNewTopoObjGMOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATICGMRecomposeShells *CATCGMCreateRecomposeShells(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToRecompose) = 0;

  virtual CATIPGMRecomposeShells *CATPGMCreateRecomposeShells(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToRecompose) = 0;

  virtual CATICGMTopSewSkin *CATCGMCreateSewSkin(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iTrimmingBody,
    CATBody *iSkinBody) = 0;

  virtual CATIPGMTopSewSkin *CATPGMCreateSewSkin(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iTrimmingBody,
    CATBody *iSkinBody) = 0;

  virtual CATICGMTopCAACompliantJournalChecker *CATCGMCreateTopCAACompliantJournalChecker(
    CATCGMJournalList *iReport,
    CATBody *iResult,
    const CATUnicodeString *iFeatureName,
    ostream *iErrorVerdictOutput,
    ostream *iErrorWarningOutput,
    CATBoolean iVerdictVerbose,
    CATBoolean iHTML_OUTPUT) = 0;

  virtual CATIPGMGeoPublishOperator *CATPGMCreateGeoPublishOperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATICGMObject *iCGMObjectToPublish) = 0;

  virtual CATGeometry *CATPGMCreateCanonicalGeometry(
    CATTopData *ipTopData,
    const CATLISTP(CATCell) &iListInputCells,
    CATGeometricType iRequestedType) = 0;

  virtual CATIPGMTopSplitShellByWires *CATPGMCreateSplitShellByWiresBasicExtrapol(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) *iSplittingBodies,
    CATBody *iSkinBody) = 0;

  virtual CATIPGMTopSplitShellByWires *CATPGMCreateSplitShellByWires(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATBody) *iSplittingBodies,
    CATBody *iSkinBody) = 0;
  virtual CATIPGMTopClashOperator *CATPGMCreateTopClashOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

 virtual CATICGMTopClashOperator *CATCGMCreateTopClashOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATICGMTopPositionPtFaceOperator *CATCGMCreateTopPositionPtFaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbPoints,
    CATSurParam iPoints[],
    CATFace *iFace) = 0;

  virtual CATIPGMTopPositionPtFaceOperator *CATPGMCreateTopPositionPtFaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    int iNbPoints,
    CATSurParam iPoints[],
    CATFace *iFace) = 0;

  virtual CATIPGMTopVoBOperator *CATPGMCreateTopVoBOperator(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToCheck,
    const CATCGMVoBCheckOptions &iTool) = 0;

  virtual CATIPGMSmartifyBody *CATPGMCreateSmartifyBodyUsingJournals(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iToSmartify,
    CATBody *iReference,
    CATCGMJournalList *iToSmartifyJournal,
    CATCGMJournalList *iReferenceJournal) = 0;

  virtual CATIPGMCellManifoldGroupOperator *CATPGMCreateCellManifoldGroupOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATCellManifoldGroupLayer *iCMGroupLayer) = 0;

  virtual HRESULT CATPGMLiveShapeManifoldTracker(
    const CATLISTP(CATBody) &iPreviousBodyList,
    const CATLISTP(CATBody) &iCurrentBodyList,
    const CATCGMJournalList &iCMJournal,
    const CATLISTP(CATManifold) &iPreviousManifoldList,
    CATSoftwareConfiguration &iConfig,
    CATCGMJournalList &oManifoldJournal) = 0;

  virtual CATIPGMTopGeoSimplify *CATPGMCreateTopGeoSimplify(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBodyToSimplify) = 0;

  virtual HRESULT CATPGMLiveShapeManifoldTracker(
    const CATLISTP(CATBody) &iPreviousBodyList,
    const CATLISTP(CATBody) &iCurrentBodyList,
    const CATCGMJournalList &iCMJournal,
    const CATListOfULONG32  &iGeometryTypeList,
    CATSoftwareConfiguration &iConfig,
    CATCGMJournalList &oManifoldJournal) = 0;

  virtual HRESULT CATPGMCreateUXDRepOpe(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATBody *iCurrentBody,
    CATCell *iLocationCell,
    CATMathPoint *iLocationPoint,
    CATLISTP(CATManifold) &iCurrentManifoldList,
    CATBody *iFirstBody,
    CATLISTP(CATManifold) &iFirstManifoldList,
    CATLISTP(CATManifoldParameter) &ioParameterList,
    CATLISTP(CATBody) &oUXPRepBodyList,
    CATLISTP(CATBody) &oUXMRepBodyList) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesBasic(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) &oResultFaceList,
    CATLISTP(CATFace) *iStoppingFaces,
    CATBoolean iLiveBodyAllowed,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iTestTypeMode) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesBasic(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) &oResultFaceList,
    CATLISTP(CATFace) &iSubBodyFilterFaceList,
    CATBoolean iLiveBodyAllowed,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual HRESULT CATPGMLiveShapeSelectFacesWithAnglePropagationBasic(
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATAngle iPropagationMaxRadAngle,
    CATLISTP(CATFace) &oResultFaceList,
    CATSoftwareConfiguration *iConfig,
    CATBoolean iLiveBodyAllowed,
    CATLISTP(CATFace) *iSubBodyFilterFaceList) = 0;

  virtual CATIPGMLiveShapeSelectFaceBasicOpe *CATPGMCreateLiveSelectFaceBasicOpe(
    CATTopData *iTopData,
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    CATLISTP(CATFace) *iStoppingFaces) = 0;

  virtual CATIPGMLiveShapeSelectFaceBasicOpe *CATPGMCreateLiveSelectFaceBasicOpe(
    CATTopData *iTopData,
    CATBody *iBody,
    const CATLISTP(CATFace) &iInputFaceList,
    CATGMLiveShapeSelectFacePropagateMode iPropagationMode,
    const CATLISTP(CATCell) *iStoppingCells) = 0;

  virtual CATOrientation CATPGMTopOriShellVsVolume(
    CATGeoFactory *iFactory,
    CATShell *iShell,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMTopExtrusionConverger *CATPGMCreateTopExtrusionConverger(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework NewTopologicalObjects.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMNewTopoObjGMOpeItfBldr *CATCGMGetNewTopoObjGMOpeItfBldr();

#endif /* CATIPGMNewTopoObjGMOpeItfBldr_h */
