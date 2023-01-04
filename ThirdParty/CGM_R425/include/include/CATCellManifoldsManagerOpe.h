#ifndef CATCellManifoldsManagerOpe_H
#define CATCellManifoldsManagerOpe_H

#include "PersistentCell.h"
#include "CATAdvancedOperator.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATCellManifoldsManagerImpl.h"
#include "CATCellFollower.h"
//#include "CATPersistentCellsBasedCellManifoldsManagerOpe.h"

class CATCellManifoldsManagerImpl; 
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBody;
class CATCGMJournalList;
class CATDeclarativeManifoldCarrierTransfoContext;
class CATFilletRecognizer;
class CATDeclarativeManifoldDuplicationCarrier;
class CATDatumManifoldCreator;
class CATCellManifoldGroupCarrier;
class CATDeclarativeOperatorsBridge;
class CATPersistentCellsBasedCellManifoldsManagerOpe;
class CATIPGMTopOperator;

/** @nodoc @nocgmitf */
class ExportedByPersistentCell CATCellManifoldsManagerOpe : public CATAdvancedOperator
{
  CATCGMVirtualDeclareClass(CATCellManifoldsManagerOpe);
public:
	
/** @nodoc 
  * cannot be called
  */
	// Constructor
  CATCellManifoldsManagerOpe(CATGeoFactory * iFactory, CATTopData * iTopData, CATCellManifoldsManagerImpl *iImpl);
  // Destructor
	virtual ~CATCellManifoldsManagerOpe();

  void TransferDataFromDRepBehavior(const CATPGMDRepBehavior * ipDRepBehavior);

  void SetUserDefinedCuttingVertices(ListPOfCATVertex &iUserDefinedCuttingVertices);

  void SetDeclarativeContext(CATDeclarativeContext * iCATDeclarativeContext);

  void SetDeclarativeApplication(CATDeclarativeApplication iDeclarativeApplication);

  void SetDeclarativeOriginModeler(CATDeclarativeOriginModeler iDeclarativeOriginModeler);

  void SetDeclarativeOriginModelerForDRepOptions(CATDeclarativeOriginModeler iDeclarativeOriginModeler);

  void SetUserDefinedSelection(ListPOfCATFace &iUserSelection);
  void GetUserDefinedSelection(ListPOfCATFace &ioUserSelection);

  HRESULT AddAgent(CATDeclarativeManifoldAgent *&ioAgent);

  void GetDeclarativeManifoldAgents(ListPOfCATDeclarativeManifoldAgent &ioAgents);

  void GetCreatedCellManifoldsWithoutParentOrWithDatumManifoldParents(CATLISTP(CATCellManifold) &ioCreatedCellManifolds);

  void GetSharedDeclartiveManifoldsWithoutParentOrWithDatumManifoldParents(ListPOfCATDeclarativeManifold &ioSharedDeclarativeManifolds);

  void StoreNotUpToDateDeclarativeManifolds(CATBoolean iStoreMode = TRUE);

  CATBoolean GetStoreNotUpToDateDeclarativeManifolds();

  void GetNotUpToDateDeclarativeManifolds(CATLISTP(CATDeclarativeManifold) &ioNotUpToDateDeclarativeManifold,
                                          CATLISTP(CATDeclarativeManifold) *ioNotUpToDateDeclarativeManifoldParent);


  void SetTypeChangeAllowedDeclarativeManifolds(ListPOfCATDeclarativeManifold &iDeclarativeManifolds);

  void SetCarrierTypeChangeAllowed(CATBoolean iCarrierAuthorized);

  void SetDeclarativeManifoldsNotToBeShared(ListPOfCATDeclarativeManifold &iDeclarativeManifoldsNotToBeShared);

  void ForbidDMCreationFromDatumManifoldCarrier();

  void SetForceCreationOrders(CATBoolean iMode); // default is mode is false

  void SetGlobalTransformation(CATMathTransformation &iGlobalTransformation);


  void AllowSubdivision();

  void SetNoFacePropagation();

  void SetCanonicRecognizerMode(CATBoolean iMode); // default is mode is true

  void SetExpectedCellsForReporting(ListPOfCATCell& iReportingCells);

  void SetNumFatherOperator(int iNumFatherOperator);

  int GetNumFatherOperator();

  CATBoolean AllDomainsFromOutputBodyAreInInputBodies();

  CATBoolean AllDomainsFromInputBodiesAreInOutputBody();

  CATBody * GetOutputBody();

  CATPersistentBody * GetOutputPersistentBody();

  int GetNbOfInputBodies();

  CATBody * GetInputBody(int iNumInputBody); // iNumInputBody [1,N]

  void GetCopyInputBodies(ListPOfCATBody &oListOfCopyInputBodies);

  CATPersistentBody * GetInputPersistentBody(int iNumInputBody);

  const ListPOfCATCell* GetExpectedCellsForReporting();

  const CATCellHashTable* GetOutputBodyCellHashTable();

  CATCGMHashTable* GetOutBodyCellManifoldHashTable();

  CATCGMJournalList * GetCellManifoldJournal();

  double GetLengthTolerance();

  double GetAngleTolerance();

  CATCGMJournalList* GetJournal();

  CATMathTransformation *GetGlobalTransformation();

  CATLONG32 GetCreationOrder(CATCellManifold *iCreatedCellManifold);

  CATCGMHashTable * GetGroupsCarriedBeforeManifoldGroupCarrier();

  void SetBRepToDRepMode(CATBoolean iBRepToDRepMode);
  void SetPatternOfPatternCollisionCM(ListPOfCATCellManifold & iCollisionCMList);
  ListPOfCATCellManifold GetPatternOfPatternCollisionCM();
  void SetPatternNumberOfInstances(int iNbInstances);
  int GetPatternNumberOfInstances();
  void SetPatternGroupsInInstances(ListPOfCATCellManifoldGroup * iGroupLists);
  ListPOfCATCellManifoldGroup * GetPatternGroupsInInstances();

  void SetLivificationInputLiveBodyList(ListPOfCATLiveBody * ipLivificationInputLiveBodyList);

  void SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds);

#ifdef TestPatternRemoveRedo_Drop3_JJ3
  ListPOfCATCellManifold GetPatternCMSetToRemoveByClashAnalysis();
#endif

  void SetLiveInfra(CATPersistentCellInfra * iLiveInfra);

  CATPersistentCellInfra * GetLiveInfra();

  void SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);

  void SetFullDomainMove();
  void SetIsLastRun(CATBoolean iIsLastRun);
  void SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet);

  void SetSplitterMode(int iContextualSplitterMode=0);
  int GetSplitterMode();

  CATBoolean GetCellManifoldsCuttingMode();

  void SetCellManifoldsCuttingMode(CATBoolean iBoolValue);

  CATlsoAgentInputDataCarrier * GetAgentInputDataCarrier();

  void SetAgentInputDataCarrier(CATlsoAgentInputDataCarrier * iAgentInputDataCarrier);

  void SetJournalForTransfo(CATCGMJournalList * iJournalForTransfo);

  CATCGMJournalList * GetJournalForTransfo();

  CATSoftwareConfiguration * GetSoftwareConfiguration();

  void SetProgressBar(CATCGMProgressBar * ipProgressBar);

  HRESULT AddAdvancedRecognizer(CATBoolean iNeedChamfer=TRUE);

  HRESULT AddAdvancedRecognizerWithBPDCheck(CATExtTopOperator * iExtTop);

  CATBoolean IsSHMApplication();

  CATBoolean IsCartonApplication();

  CATBoolean IsCGMInternalUse();

  CATDeclarativeContext       * GetDeclarativeContext();

  CATDeclarativeApplication GetDeclarativeApplication();

  CATDeclarativeOriginModeler   GetDeclarativeOriginModeler();

  CATDeclarativeManifoldCarrierTransfoContext * GetDeclarativeManifoldCarrierTransfoContext();

  CATFilletRecognizer * GetFilletRecognizer();

  CATDeclarativeManifoldDuplicationCarrier *GetDuplicationCarrier();

  CATDatumManifoldCreator * GetDatumManifoldCreator();

  CATCellManifoldGroupCarrier * GetCellManifoldGroupCarrier();

  void SetDeclarativeOperatorsBridge(CATDeclarativeOperatorsBridge * iRemoveFaceRunner);

  CATDeclarativeOperatorsBridge * GetDeclarativeOperatorsBridge();

  void SetRedeclaredCMG(ListPOfCATCellManifoldGroup * iCMGToIgnore);

  CATCellFollower * CreateCellFollower(CATBoolean iModificationOnly);
  
  CATCellManifoldGroupCarrier * CreateCellManifoldGroupCarrier();

  virtual CATPersistentCellsBasedCellManifoldsManagerOpe * GetAsPersistentCellsBasedCellManifoldsManagerOpe();

  void SetLocalJournalList(CATCGMJournalList * iLocalJournalList);

  CATCGMJournalList * GetLocalJournalList();

  void CleanLocalJournalList();

  void SetLocalNoLiveBodyChecker(CATBoolean iLocalNoLiveBodyChecker);

  void SetLocalGroupMode(CATBoolean iLocalGroupMode);

  void SetCMGError(const char * iErrorMessageID, const CATLISTP(CATCellManifoldGroup) &iCMGroupList);

  CATCGMJournalList * GetTopOpJournal();

  void SetTopOpJournal(CATCGMJournalList * iTopOpJournal, CATBoolean iOwner=FALSE);

  void SetExternalOperatorForDataComputing(CATIPGMTopOperator * iExternalOperatorForDataComputing);

  //VB7 W24 2020
  CATBoolean InSmartContext() const;
  void SetSmartContext(CATBoolean iSmartContext);
  void SetAssembleContext(CATBoolean iAssembleContext);
  void SetSmartFacesOnInputBodies(CATCGMHashTableWithAssoc * iSmartFacesOnInputBodies);
  CATCGMHashTableWithAssoc * GetSmartFacesOnInputBodies() const;
  CATBoolean InAssembleContext() const;

  CATIPGMTopOperator * GetExternalOperatorForDataComputing();

public:
  // ------------------
  // CGMReplay Methodes
  // ------------------
  /** @nodoc @nocgmitf */
  static const CATString *GetDefaultOperatorId();
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  void WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  void RequireDefinitionOfInputAndOutputObjects();
	
  CATCellManifoldsManagerImpl * GetCellManifoldsManagerImpl() const;
protected:
  
};

// ----------------------------
// CATCreateCellManifoldsManagerOpe
// ----------------------------

ExportedByPersistentCell CATCellManifoldsManagerOpe * CATCreateCellManifoldsManagerOpe(CATGeoFactory *iFactory, CATTopData * iTopData, ListPOfCATBody &iListOfCopyInputBodies, CATBody * iOutputBody, CATCGMJournalList * iTopOpJournal, CATCellManifoldsManager * iCMManager);
ExportedByPersistentCell CATCellManifoldsManagerOpe * CATCreateCellManifoldsManagerOpe(CATGeoFactory *iFactory, CATTopData * iTopData, CATBody * iBody, CATCellManifoldsManager * iCMManager);
ExportedByPersistentCell CATCellManifoldsManagerOpe * CATCreateCellManifoldsManagerOpe(CATGeoFactory *iFactory, CATTopData * iTopData, ListPOfCATBody &iListOfCopyInputBodies, ListPOfCATBody &iListOfNoCopyInputBodies, CATBody * iOutputBody, CATCGMJournalList * iTopOpJournal, CATCellManifoldsManager * iCMManager);
//For CGMReplay only 
ExportedByPersistentCell CATCellManifoldsManagerOpe * CATCreateCellManifoldsManagerOpe(CATGeoFactory *iFactory, CATTopData * iTopData, ListPOfCATBody &iListOfCopyInputBodies, ListPOfCATBody &iListOfNoCopyInputBodies, CATBody * iOutputBody);


#endif
  
