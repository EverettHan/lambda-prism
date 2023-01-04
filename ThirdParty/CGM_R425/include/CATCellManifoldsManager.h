#ifndef CATCellManifoldsManager_H
#define CATCellManifoldsManager_H

#include "CATIAV5Level.h"

#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
// #include "CATCGMJournalList.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDeclarativeManifoldAgent.h"
#include "CATCollec.h"
#include "CATXBoolean.h"
#include "ListPOfCATVertex.h"

// #include "CATGeoFactory.h"
#include "CATTolerance.h"
#include "CATGetTolerance.h"
#include "CATIACGMLevel.h"
#include "CATMathInline.h"

// Proto Pattern Remove/Redo Drop 3 (JJ3)
#include "CATPatternDefine.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"

#include "CATPGMCellManifoldsManager.h"
#include "CATBoolean.h"
#include "ListPOfCATLiveBody.h"
// #include "CATVariationalPatternParameters.h"

// #include "CATWeekVersioning.h"
// #include "CATlsoAgentInputDataCarrier.h"
#include "CATSysDeletePtrList.h"
// #include "CATCellManifoldsManagerOpe.h"

class CATPersistentBody;
class CATDeclarativeManifoldAgent;
class CATLISTP(CATDeclarativeManifoldAgent);
class CATCellManifold;
#ifndef TestPatternRemoveRedo_Drop3_JJ3 // Doublon avec le include rajoute.
class CATLISTP(CATCellManifold);
#endif
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATBody;
class CATSoftwareConfiguration;
class CATDeclarativeManifoldCarrierTransfoContext;
class CATDatumManifoldCreator;
class CATDeclarativeManifoldDuplicationCarrier;
class CATFilletRecognizer;
class CATCanonicRecognizer;
class CATCellManifoldGroupCarrier;
class CATPersistentCellsBasedCellManifoldsManager;
class CATCellFollower;
class CATCellHashTable;
class CATCGMHashTable;
class CATPersistentCellInfra;
class CATDeclarativeOperatorsBridge;
class CATDeclarativeContext;
class CATlsoAgentInputDataCarrier;
class CATPGMDRepBehavior;
class CATCellManifoldsManagerOpe;
class CATCellManifoldsManagerImpl;
class CATIPGMTopOperator;
class CATVariationalPatternParameters;
class CATCGMHashTableWithAssoc;


class ExportedByPersistentCell CATCellManifoldsManager: public CATPGMCellManifoldsManager
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructors
  CATCellManifoldsManager(CATGeoFactory *iFactory, CATSoftwareConfiguration * ipConfig, ListPOfCATBody &iListOfCopyInputBodies, CATBody * iOutputBody, CATCGMJournalList* iTopOpJournal);
  CATCellManifoldsManager(CATGeoFactory *iFactory, CATSoftwareConfiguration * ipConfig,CATBody * iBody);
  //@nocgmitf
  CATCellManifoldsManager(CATGeoFactory *iFactory, CATSoftwareConfiguration * ipConfig, ListPOfCATBody &iListOfCopyInputBodies, ListPOfCATBody &iListOfNoCopyInputBodies,
    CATBody * iOutputBody, CATCGMJournalList* iTopOpJournal);
  //@nocgmitf - VB7 for child class
  CATCellManifoldsManager();
  //@nocgmitf - VB7 for CATCellManifoldsManagerImpl CGMReplay
  CATCellManifoldsManager(CATCellManifoldsManagerOpe * iOpe);

  // Destructor
  virtual ~CATCellManifoldsManager();

  void TransferDataFromDRepBehavior(const CATPGMDRepBehavior * ipDRepBehavior);

  // User Defined Cutting Vertices
  void SetUserDefinedCuttingVertices(ListPOfCATVertex &iUserDefinedCuttingVertices);

  // CreateImageManifolds
  // iNoLiveBodyChecker permet de desactive le check du body creer lorsqu'on sait qu'il va etre faux.
  // Utilise dans les ODT pour tester des vieux models.
  HRESULT CreateImageManifolds(CATCGMJournalList* iCellManifoldsJournal = NULL);
  HRESULT CreateImageManifolds(CATCGMJournalList* iCellManifoldsJournal, CATBoolean iNoLiveBodyChecker);//, CATBoolean iCalledByLiveOperator = TRUE);

  HRESULT CreateImageManifoldGroups(CATCGMJournalList* iCellManifoldsJournal, CATBoolean iNoLiveBodyChecker);

  // For Recognizer
  void SetDeclarativeContext(CATDeclarativeContext * iCATDeclarativeContext);

  // For Local Recognition
  void SetUserDefinedSelection(ListPOfCATFace &iUserSelection);

  void GetUserDefinedSelection(ListPOfCATFace &ioUserSelection);
  //@nocgmitf
  HRESULT AddAgent(CATDeclarativeManifoldAgent *&ioAgent);
  //@nocgmitf
  void GetDeclarativeManifoldAgents(ListPOfCATDeclarativeManifoldAgent &ioAgents);

  //@nocgmitf
  void GetCreatedCellManifoldsWithoutParentOrWithDatumManifoldParents(CATLISTP(CATCellManifold) &ioCreatedCellManifolds);
  //@nocgmitf
  void GetSharedDeclartiveManifoldsWithoutParentOrWithDatumManifoldParents(ListPOfCATDeclarativeManifold &ioSharedDeclarativeManifolds);
  
  //@nocgmitf
  void GetNotUpToDateDeclarativeManifolds(CATLISTP(CATDeclarativeManifold) &ioNotUpToDateDeclarativeManifold,
                                          CATLISTP(CATDeclarativeManifold) *ioNotUpToDateDeclarativeManifoldParent);
  //@nocgmitf
  void SetTypeChangeAllowedDeclarativeManifolds(ListPOfCATDeclarativeManifold &iDeclarativeManifolds);
  //@nocgmitf
  void SetCarrierTypeChangeAllowed(CATBoolean iCarrierAuthorized);
  //@nocgmitf
  void SetDeclarativeManifoldsNotToBeShared(ListPOfCATDeclarativeManifold &iDeclarativeManifoldsNotToBeShared);
  //@nocgmitf
  void ForbidDMCreationFromDatumManifoldCarrier();
  //@nocgmitf
  void SetForceCreationOrders(CATBoolean iMode); // default is mode is false
  //@nocgmitf
  void SetGlobalTransformation(CATMathTransformation &iGlobalTransformation);

  //@nocgmitf
  void SetExpectedCellsForReporting(ListPOfCATCell& iReportingCells);

  //@nocgmitf
  CATBoolean AllDomainsFromOutputBodyAreInInputBodies();
  //@nocgmitf
  CATBoolean AllDomainsFromInputBodiesAreInOutputBody();

  //VB7 - get Transfo from FaceToTransfo if each Face of the CellManifold list has the same Transfo
  //@nocgmitf
  CATMathTransformation * GetTransfoFromTransformFaceContext(ListPOfCATCellManifold & iInputCellManifoldList, CATLiveBody & iOutputLiveBody, ListPOfCATCellManifold & iOutputCellManifoldList);

  //@nocgmitf
  CATPersistentBody * GetOutputPersistentBody();
  
  //@nocgmitf
  CATBody * GetInputBody(int iNumInputBody); // iNumInputBody [1,N]

  //@nocgmitf
  CATPersistentBody * GetInputPersistentBody(int iNumInputBody);

  //@nocgmitf
  const ListPOfCATCell* GetExpectedCellsForReporting();
  //@nocgmitf
  const CATCellHashTable* GetOutputBodyCellHashTable();
  //@nocgmitf
  CATCGMHashTable* GetOutBodyCellManifoldHashTable();

  CATCGMHashTable * GetGroupsCarriedBeforeManifoldGroupCarrier();

  //@nocgmitf
  void SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);

  void SetSplitterMode(int iContextualSplitterMode=0);
  int GetSplitterMode();

  //@nocgmitf
  const CATlsoAgentInputDataCarrier * GetAgentInputDataCarrier() const;
  //@nocgmitf
  void SetAgentInputDataCarrier(CATlsoAgentInputDataCarrier * iAgentInputDataCarrier);
  //@nocgmitf
  void SetJournalForTransfo(CATCGMJournalList * iJournalForTransfo);
  //@nocgmitf
  CATCGMJournalList * GetJournalForTransfo();

  // Methods for V5 Operators
  // ------------------------
  //@nocgmitf
  HRESULT AddAdvancedRecognizer(CATBoolean iNeedChamfer=TRUE);
  //@nocgmitf
  HRESULT AddAdvancedRecognizerWithBPDCheck(CATExtTopOperator * iExtTop);
  //@nocgmitf
  static CATDeclarativeApplication GetDeclarativeApplication(CATExtTopOperator * iExtTop);

  //@nocgmitf
  CATBoolean IsSHMApplication() const;
  //@nocgmitf
  CATBoolean IsCartonApplication() const;
  //@nocgmitf
  CATBoolean IsCGMInternalUse() const;
  

  //INLINES
  void SetDeclarativeApplication(CATDeclarativeApplication iDeclarativeApplication);
  //@nocgmitf
  void SetDeclarativeOriginModeler(CATDeclarativeOriginModeler iDeclarativeOriginModeler);
  //@nocgmitf
  void SetDeclarativeOriginModelerForDRepOptions(CATDeclarativeOriginModeler iDeclarativeOriginModeler);
  //@nocgmitf
  void StoreNotUpToDateDeclarativeManifolds(CATBoolean iStoreMode = TRUE);
  //@nocgmitf
  CATBoolean GetStoreNotUpToDateDeclarativeManifolds();
  //@nocgmitf
  void AllowSubdivision();
  //@nocgmitf
  void SetNoFacePropagation();
  //@nocgmitf
  void SetCanonicRecognizerMode(CATBoolean iMode); // default is mode is true
  //@nocgmitf
  void SetNumFatherOperator(int iNumFatherOperator);
  //@nocgmitf
  int GetNumFatherOperator();
  //@nocgmitf
  CATBody * GetOutputBody() const;
  //@nocgmitf
  int GetNbOfInputBodies() const;
  //@nocgmitf
  void GetCopyInputBodies(ListPOfCATBody &oListOfCopyInputBodies) const;
  //@nocgmitf
  CATSoftwareConfiguration* GetSoftwareConfiguration() const;
  //@nocgmitf
  CATGeoFactory* GetFactory() const;
  //@nocgmitf
  CATCGMJournalList * GetCellManifoldJournal() const;

  // Tolerance to be used by the DeclarativeManifoldAgent
  //@nocgmitf
  static double GetLengthTolerance(CATGeoFactory* iFactory);
  //@nocgmitf
  double GetLengthTolerance();
  //@nocgmitf
  double GetAngleTolerance();
  //@nocgmitf
  static double GetAngleTolerance(CATGeoFactory* iFactory);

  CATCGMJournalList* GetJournal();

  CATMathTransformation *GetGlobalTransformation();

  CATLONG32 GetCreationOrder(CATCellManifold *iCreatedCellManifold);

  //@nocgmitf
  virtual CATPersistentCellsBasedCellManifoldsManager* GetAsPersistentCellsBasedCellManifoldsManager();
  void SetBRepToDRepMode(CATBoolean iBRepToDRepMode);
  void SetPatternOfPatternCollisionCM(ListPOfCATCellManifold & iCollisionCMList);
  ListPOfCATCellManifold GetPatternOfPatternCollisionCM();
  void SetPatternNumberOfInstances(int iNbInstances);
  int GetPatternNumberOfInstances();
  void SetPatternGroupsInInstances(ListPOfCATCellManifoldGroup * iGroupLists);
  ListPOfCATCellManifoldGroup * GetPatternGroupsInInstances();

  void SetLivificationInputLiveBodyList(ListPOfCATLiveBody * ipLivificationInputLiveBodyList);
  //@nocgmitf
  void SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds);
#ifdef TestPatternRemoveRedo_Drop3_JJ3
  //@nocgmitf
  INLINE ListPOfCATCellManifold GetPatternCMSetToRemoveByClashAnalysis();
#endif

  //@nocgmitf
  void SetLiveInfra(CATPersistentCellInfra * iLiveInfra);
  //@nocgmitf
  CATPersistentCellInfra * GetLiveInfra();
  void SetFullDomainMove();
  void SetIsLastRun(CATBoolean iIsLastRun);
  void SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet);
  //@nocgmitf
  CATBoolean GetCellManifoldsCuttingMode() const;
  //@nocgmitf
  void SetCellManifoldsCuttingMode(CATBoolean iBoolValue);

  void SetProgressBar(CATCGMProgressBar * ipProgressBar);
  // For Recognizer
  //@nocgmitf
  CATDeclarativeContext       * GetDeclarativeContext() const;
  //@nocgmitf
  CATDeclarativeApplication     GetDeclarativeApplication() const;
  //@nocgmitf
  CATDeclarativeOriginModeler   GetDeclarativeOriginModeler() const;
  //@nocgmitf
  CATSoftwareConfiguration* GetConfig() const;

  //@nocgmitf
  void SetCMGError(const char * iErrorMessageID, const CATLISTP(CATCellManifoldGroup) &iCMGroupList);

  //@nocgmitf
  CATCGMJournalList * GetTopOpJournal();

  //@nocgmitf
  void SetExternalOperatorForDataComputing(CATIPGMTopOperator * iExternalOperatorForDataComputing);

  //VB7 W24 2020
  CATBoolean InSmartContext() const;
  void SetSmartContext(CATBoolean iSmartContext = TRUE);
  void SetAssembleContext(CATBoolean iAssembleContext = TRUE);
  void SetSmartFacesOnInputBodies(CATCGMHashTableWithAssoc * iSmartFacesOnInputBodies);
  CATCGMHashTableWithAssoc * GetSmartFacesOnInputBodies() const;
  CATBoolean InAssembleContext() const;

  //@nocgmitf
  CATIPGMTopOperator * GetExternalOperatorForDataComputing();

protected :

  virtual CATCellFollower * CreateCellFollower(CATBoolean iModificationOnly);
  virtual CATCellManifoldGroupCarrier * CreateCellManifoldGroupCarrier();

public:
  //@nocgmitf
  CATDeclarativeManifoldCarrierTransfoContext * GetDeclarativeManifoldCarrierTransfoContext();
  //@nocgmitf
  CATFilletRecognizer * GetFilletRecognizer();
  //@nocgmitf
  CATDeclarativeManifoldDuplicationCarrier *GetDuplicationCarrier();
  //@nocgmitf
  CATDatumManifoldCreator * GetDatumManifoldCreator();
  //@nocgmitf
  CATCellManifoldGroupCarrier * GetCellManifoldGroupCarrier();
  //@nocgmitf
  void SetDeclarativeOperatorsBridge(CATDeclarativeOperatorsBridge * iRemoveFaceRunner);
  //@nocgmitf
  CATDeclarativeOperatorsBridge * GetDeclarativeOperatorsBridge();
  //@nocgmitf
  void SetRedeclaredCMG(ListPOfCATCellManifoldGroup * iCMGToIgnore);
  // @nocgmitf
  CATCellManifoldsManagerImpl * GetCMManagerImpl() const;

protected:

  CATCellManifoldsManagerOpe * _CellManifoldsManagerOpe;
  CATBoolean                   _CellManifoldsManagerOpeOwner;
  CATTopData                 * _TopData;
  CATCGMJournalList          * _CMManagerOpeJournal;
};

INLINE double CATCellManifoldsManager::GetLengthTolerance(CATGeoFactory* iFactory) {
  const CATTolerance & ToleranceObject = CATGetTolerance(iFactory);
  return 10*ToleranceObject.GetResolution(); }

INLINE double CATCellManifoldsManager::GetAngleTolerance(CATGeoFactory* iFactory) {
  const CATTolerance & ToleranceObject = CATGetTolerance(iFactory);
  return ToleranceObject.LargeResolutionForAngleTest(); }


/**
 * @return [out, delete]
 */
ExportedByPersistentCell CATCellManifoldsManager *CATCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration * iConfig,
  CATLISTP(CATBody) &iListOfCopyInputBodies,
  CATBody *iOutputBody,
  CATCGMJournalList *iTopOpJournal);

/**
 * @return [out, delete]
 * Deprecated method : use the methode with a CATSoftwareConfiguration
 */
ExportedByPersistentCell CATCellManifoldsManager *CATCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATLISTP(CATBody) &iListOfCopyInputBodies,
  CATBody *iOutputBody,
  CATCGMJournalList *iTopOpJournal);

/**
 * @return [out, delete]
 */
ExportedByPersistentCell CATCellManifoldsManager *CATCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration * iConfig,
  CATBody *iBody);

/**
 * @return [out, delete]
 * Deprecated method : use the methode with a CATSoftwareConfiguration
 */
ExportedByPersistentCell CATCellManifoldsManager *CATCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATBody *iBody);

#endif
