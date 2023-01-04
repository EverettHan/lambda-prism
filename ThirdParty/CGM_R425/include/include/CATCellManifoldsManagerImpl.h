#ifndef CATCellManifoldsManagerImpl_H
#define CATCellManifoldsManagerImpl_H

#include "PersistentCell.h"
#include "CATAdvancedExtTopOperator.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATDeclarativeManifoldAgent.h"
#include "ListPOfCATCell.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDeclarativeApplication.h"
#include "CATlsoAgentInputDataCarrier.h"
#include "CATCellManifoldsManager.h"
#include "CATSysDeletePtrList.h"
#include "CATGeoFactory.h"
#include "CATTopData.h"
#include "ListPOfCATPersistentBodies.h"

class CATCellManifoldsManagerOpe;
class CATDeclarativeManifoldCarrierTransfoContext;
class CATFilletRecognizer;
class CATDeclarativeManifoldDuplicationCarrier;
class CATDatumManifoldCreator;
class CATCellManifoldGroupCarrier;
class CATDeclarativeOperatorsBridge;
class CATDMAgentContext;
class CATCGMJournalList;
class CATSharedManifoldAgent;
class CATCellManifoldCreator;
class CATDeclarativeManifoldCarrier;
class CATDatumManifoldCarrier;
class CATAdvancedManifoldCarrier;
class CATCanonicRecognizer;
class CATCellManifoldMerger;
class CATDeclarativeManifoldAgent;
class CATBody;
class CATPersistentBody;
class CATMathTransformation;
class CATCGMHashTable;
class CATLiveBody;
class CATCGMProgressBar;
class CATVariationalPatternParameters;
class CATPersistentCellInfra;
class CATExtTopOperator;
class CATGMLiveExtrusionPrimitivesContainer;
class CATDeclarativeContext;
class CATCellManifoldsManager;
class CATCellFollower;
class CATPersistentCellsBasedCellManifoldsManagerImpl;
class CATIPGMTopOperator;
class CATRibbonSeedsSharedSorter;


// @nocgmitf
class ExportedByPersistentCell CATCellManifoldsManagerImpl : public CATAdvancedExtTopOperator
{
public:
  
/** @nodoc 
  * cannot be called
  */
  // Constructor
  CATCellManifoldsManagerImpl(CATGeoFactory              & iFactory,
                              CATTopData                 & iTopData,
                              ListPOfCATBody             & iListOfCopyInputBodies,
                              CATBody                   *  iOutputBody,
                              CATCGMJournalList         *  iTopOpJournal,
                              CATCellManifoldsManager   *  iCMManager);

  CATCellManifoldsManagerImpl(CATGeoFactory              & iFactory,
                              CATTopData                 & iTopData,
                              CATBody                   *  iBody,
                              CATCellManifoldsManager   *  iCMManager);

  // iNoCopyInputBodies : spécifie si les Bodies doivent pris en mode NoCopy (0=Copy,1=NoCopy). 
  // Si non spécifiés, ils sont tous vu en mode Copy
  CATCellManifoldsManagerImpl(CATPersistentCellInfra     & iLiveInfra,
                              CATTopData                 & iTopData,
                              ListPOfCATPersistentBodies & iInputPersistentBodies,
                              CATPersistentBody         *  iOutPersistentBody,
                              CATCellManifoldsManager   *  iCMManager,
                              const CATListOfInt        *  iNoCopyInputBodies=NULL);

  CATCellManifoldsManagerImpl(CATGeoFactory              & iFactory,
                              CATTopData                 & iTopData,
                              ListPOfCATBody             & iListOfCopyInputBodies,
                              ListPOfCATBody             & iListOfNoCopyInputBodies,
                              CATBody                   *  iOutputBody,
                              CATCGMJournalList         *  iTopOpJournal,
                              CATCellManifoldsManager   *  iCMManager);

  //ForCGMreplay
  CATCellManifoldsManagerImpl(CATGeoFactory              & iFactory,
                              CATTopData                 & iTopData,
                              ListPOfCATBody             & iListOfCopyInputBodies,
                              ListPOfCATBody             & iListOfNoCopyInputBodies,
                              CATBody                   *  iOutputBody);

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;

                void                    Init();

  // Replaced by the calling of RunAdvancedOperator();
  // int  RunOperator();

                void                    TransferDataFromDRepBehavior(const CATPGMDRepBehavior * ipDRepBehavior);

                void                    SetUserDefinedCuttingVertices(ListPOfCATVertex &iUserDefinedCuttingVertices);

                void                    SetDeclarativeContext        (CATDeclarativeContext * iCATDeclarativeContext);

  INLINE        void                    SetDeclarativeApplication    (CATDeclarativeApplication iDeclarativeApplication);

  INLINE        void                    SetDeclarativeOriginModeler  (CATDeclarativeOriginModeler iDeclarativeOriginModeler);

  INLINE        void                    SetDeclarativeOriginModelerForDRepOptions(CATDeclarativeOriginModeler iDeclarativeOriginModeler);

                void                    SetUserDefinedSelection      (ListPOfCATFace &iUserSelection);
                void                    GetUserDefinedSelection      (ListPOfCATFace &ioUserSelection);

                HRESULT                 AddAgent                     (CATDeclarativeManifoldAgent *&ioAgent);

                void                    GetDeclarativeManifoldAgents      (ListPOfCATDeclarativeManifoldAgent &ioAgents);

                void                    GetCreatedCellManifoldsWithoutParentOrWithDatumManifoldParents
                                                                          (CATLISTP(CATCellManifold) &ioCreatedCellManifolds);

                void                    GetSharedDeclartiveManifoldsWithoutParentOrWithDatumManifoldParents
                                                                          (ListPOfCATDeclarativeManifold &ioSharedDeclarativeManifolds);

  INLINE        void                    StoreNotUpToDateDeclarativeManifolds(CATBoolean iStoreMode = TRUE);

  INLINE        CATBoolean              GetStoreNotUpToDateDeclarativeManifolds();

                void                    GetNotUpToDateDeclarativeManifolds(CATLISTP(CATDeclarativeManifold) &ioNotUpToDateDeclarativeManifold,
                                                                           CATLISTP(CATDeclarativeManifold) *ioNotUpToDateDeclarativeManifoldParent);


                void                    SetTypeChangeAllowedDeclarativeManifolds(ListPOfCATDeclarativeManifold &iDeclarativeManifolds);

                void                    SetCarrierTypeChangeAllowed(CATBoolean iCarrierAuthorized);

                void                    SetDeclarativeManifoldsNotToBeShared(ListPOfCATDeclarativeManifold &iDeclarativeManifoldsNotToBeShared);

                void                    ForbidDMCreationFromDatumManifoldCarrier();

                void                    SetForceCreationOrders(CATBoolean iMode); // default is mode is false

                void                    SetGlobalTransformation(CATMathTransformation &iGlobalTransformation);


  INLINE        void                    AllowSubdivision();

  INLINE        void                    SetNoFacePropagation();

  INLINE        void                    SetCanonicRecognizerMode(CATBoolean iMode); // default is mode is true

                void                    SetExpectedCellsForReporting(ListPOfCATCell& iReportingCells);

  INLINE        void                    SetNumFatherOperator(int iNumFatherOperator);
  INLINE        int                     GetNumFatherOperator();

                CATBoolean              AllDomainsFromOutputBodyAreInInputBodies();

                CATBoolean              AllDomainsFromInputBodiesAreInOutputBody();

  INLINE        CATBody               * GetOutputBody()const;

                CATPersistentBody     * GetOutputPersistentBody();
  INLINE        void                    GetInputPersistentBodies(ListPOfCATPersistentBodies & oInputPersistentBodies) const;

  INLINE        int                     GetNbOfInputBodies();

                CATBody               * GetInputBody(int iNumInputBody); // iNumInputBody [1,N]

  INLINE        void                    GetCopyInputBodies(ListPOfCATBody &oListOfCopyInputBodies) const;

                CATPersistentBody     * GetInputPersistentBody(int iNumInputBody);

          const ListPOfCATCell        * GetExpectedCellsForReporting();

          const CATCellHashTable      * GetOutputBodyCellHashTable();

                CATCGMHashTable       * GetOutBodyCellManifoldHashTable();

  INLINE        CATCGMJournalList     * GetCellManifoldJournal() const;

                double                  GetLengthTolerance();

                double                  GetAngleTolerance();

  INLINE        CATMathTransformation * GetGlobalTransformation();

                CATLONG32               GetCreationOrder(CATCellManifold *iCreatedCellManifold);

                CATCGMHashTable       * GetGroupsCarriedBeforeManifoldGroupCarrier();

  INLINE        void                    SetBRepToDRepMode(CATBoolean iBRepToDRepMode);
  INLINE        void                    SetPatternOfPatternCollisionCM(ListPOfCATCellManifold & iCollisionCMList);
  INLINE        ListPOfCATCellManifold  GetPatternOfPatternCollisionCM();
  INLINE        void                    SetPatternNumberOfInstances(int iNbInstances);
  INLINE        int                     GetPatternNumberOfInstances();
  INLINE        void                    SetPatternGroupsInInstances(ListPOfCATCellManifoldGroup * iGroupLists);
  INLINE        ListPOfCATCellManifoldGroup * GetPatternGroupsInInstances();

  INLINE        void                    SetLivificationInputLiveBodyList(ListPOfCATLiveBody * ipLivificationInputLiveBodyList);

  INLINE        void                    SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds);

#ifdef TestPatternRemoveRedo_Drop3_JJ3
  INLINE        ListPOfCATCellManifold  GetPatternCMSetToRemoveByClashAnalysis();
#endif

  INLINE        void                    SetLiveInfra(CATPersistentCellInfra * iLiveInfra);

  INLINE        CATPersistentCellInfra * GetLiveInfra();

                void                    SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);

  INLINE        void                    SetFullDomainMove();
  INLINE        void                    SetIsLastRun(CATBoolean iIsLastRun);
  INLINE        void                    SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet);

                void                    SetSplitterMode(int iContextualSplitterMode=0);
                int                     GetSplitterMode();

  INLINE        CATBoolean              GetCellManifoldsCuttingMode() const;

  INLINE        void                    SetCellManifoldsCuttingMode(CATBoolean iBoolValue);

                CATlsoAgentInputDataCarrier * GetAgentInputDataCarrier();

                void                    SetAgentInputDataCarrier(CATlsoAgentInputDataCarrier * iAgentInputDataCarrier);

                void                    SetJournalForTransfo(CATCGMJournalList * iJournalForTransfo);

                CATCGMJournalList     * GetJournalForTransfo();

  INLINE        void                    SetProgressBar(CATCGMProgressBar * ipProgressBar);

                HRESULT                 AddAdvancedRecognizer(CATBoolean iNeedChamfer=TRUE);

                HRESULT                 AddAdvancedRecognizerWithBPDCheck(CATExtTopOperator * iExtTop);

                HRESULT                 AddAdvancedRecognizerWithNaturalShapeCheck();

                HRESULT                 AddDRepLabelCarrier();

                CATBoolean              IsNaturalShapeApplication();

                CATBoolean              IsSHMApplication();

                CATBoolean              IsCartonApplication();

                CATBoolean              IsCGMInternalUse();

  INLINE        CATDeclarativeContext       * GetDeclarativeContext() const;

  INLINE        CATDeclarativeApplication     GetDeclarativeApplication() const;

  INLINE        CATDeclarativeOriginModeler   GetDeclarativeOriginModeler() const;

                CATDeclarativeManifoldCarrierTransfoContext * GetDeclarativeManifoldCarrierTransfoContext();

                CATFilletRecognizer           * GetFilletRecognizer();

                CATDeclarativeManifoldDuplicationCarrier *GetDuplicationCarrier();

                CATDatumManifoldCreator       * GetDatumManifoldCreator();

                CATCellManifoldGroupCarrier   * GetCellManifoldGroupCarrier();

                void                            SetDeclarativeOperatorsBridge(CATDeclarativeOperatorsBridge * iDeclarativeOperatorsBridge);

                CATDeclarativeOperatorsBridge * GetDeclarativeOperatorsBridge();

  INLINE        void SetRedeclaredCMG(ListPOfCATCellManifoldGroup * iCMGToIgnore);

  virtual       CATCellFollower * CreateCellFollower(CATBoolean iModificationOnly);
  
  virtual       CATCellManifoldGroupCarrier * CreateCellManifoldGroupCarrier();

  virtual       CATPersistentCellsBasedCellManifoldsManagerImpl * GetAsPersistentCellsBasedCellManifoldsManagerImpl();

  INLINE        void SetSmartContext(CATBoolean iSmartContext);
  INLINE        void SetAssembleContext(CATBoolean iAssembeContext);
  INLINE        void SetSmartFacesOnInputBodies(CATCGMHashTableWithAssoc * iSmartFacesOnInputBodies);
  INLINE        CATCGMHashTableWithAssoc * GetSmartFacesOnInputBodies() const;
  CATBoolean    InSmartContext() const;
  CATBoolean    InAssembleContext() const;

  //Local parameters
  INLINE        void                 SetLocalJournalList(CATCGMJournalList * iLocalJournalList);
  INLINE        CATCGMJournalList  * GetLocalJournalList();
  INLINE        void                 CleanLocalJournalList();
  INLINE        void                 SetLocalNoLiveBodyChecker(CATBoolean iLocalNoLiveBodyChecker);
  INLINE        void                 SetLocalGroupMode(CATBoolean iLocalGroupMode);
  //End Local parameters

  INLINE        void                 SetExternalOperatorForDataComputing(CATIPGMTopOperator * iExternalOperatorForDataComputing);
  INLINE        CATIPGMTopOperator * GetExternalOperatorForDataComputing();

                void                 SetCMGError(const char * iErrorMessageID, const CATLISTP(CATCellManifoldGroup) &iCMGroupList);

                void                 CreateCATCellManifoldsManager(CATCellManifoldsManagerOpe * iOpe);

  // ------------------
  // CGMReplay Methodes
  // ------------------
  static const CATString       * GetDefaultOperatorId() { return &_OperatorId; }
         const CATString       * GetOperatorId       () const;
               CATExtCGMReplay * IsRecordable        ( short & LevelOfRuntime, short &VersionOfStream);
               void              WriteInput          ( CATCGMStream  & Str);
               void              Dump                ( CATCGMOutput& os ) ;
               void              RequireDefinitionOfInputAndOutputObjects();

  static       CATPersistentCellInfra   * UnStreamPersistentCellInfra  (ListPOfCATBody              & iInputBodyList,
                                                                        CATBody                    *  iOutputBody,
                                                                        CATGeoFactory              *  iFactory,
                                                                        CATSoftwareConfiguration   *  iConfig,
                                                                        CATCGMStream                & Str);

  static void                             ReadCellManifoldsManager     (CATCGMStream                & Str,
                                                                        CATGeoFactory              *  iFactory,
                                                                        CATTopData                  & iData,
                                                                        short                         iVersion,
                                                                        CATCellManifoldsManagerOpe *& ioOpe);

          CATCGMJournalList             * GetTopOpJournal();
          void                            SetTopOpJournal(CATCGMJournalList * iTopOpJournal, CATBoolean iOwner=FALSE);

protected:
  // Destructor
  virtual                                ~CATCellManifoldsManagerImpl();

  // -----------------------------------------------------
  // RunAdvancedOperator
  // -----------------------------------------------------
  virtual int                             RunAdvancedOperator(); // Mandatory


          void                            WriteCellManifoldsManager(CATCGMStream  & Str, short iVersion);
  

  INLINE  void                            AddCopyInputBody(CATBody *iInputBody);
  INLINE  void                            AddNoCopyInputBody(CATBody *iInputBody);
          CATBoolean                      HasInputBody();
          CATBoolean                      HasInputLiveBody();
          void                            SetDRepOptions(CATLiveBody * iLiveBody) const;
          HRESULT                         CreateMandatoryAgents(CATCGMJournalList* iCellManifoldsJournal, CATDMAgentContext * iAgentContext);

          CATSharedManifoldAgent        * CreateSharedManifoldAgent();
          CATCellManifoldCreator        * CreateCellManifoldCreator();
          CATDeclarativeManifoldCarrier * CreateDeclarativeManifoldCarrier();
          CATDatumManifoldCarrier       * CreateDatumManifoldCarrier();
          CATAdvancedManifoldCarrier    * CreateAdvancedManifoldCarrier();
          CATDatumManifoldCreator       * CreateDatumManifoldCreator();
          CATFilletRecognizer           * CreateFilletRecognizer();
  
          HRESULT                         AddManifoldGroupCarrier();
          HRESULT                         AddCellManifoldGroupCarrier();

          CATDeclarativeManifoldDuplicationCarrier * CreateDeclarativeManifoldDuplicationCarrier();

          CATCellManifoldCreator        * GetCellManifoldCreator();
          CATCellManifoldMerger         * GetCellManifoldMerger();
          CATDatumManifoldCarrier       * GetDatumManifoldCarrier();
          CATCanonicRecognizer          * GetCanonicRecognizer();

  INLINE  CATDeclarativeOriginModeler     GetDeclarativeOriginModelerForDRepOptions() const;
          void                            InitAllAgentsWithContexts();
  INLINE  ListPOfCATCellManifoldGroup   * GetRedeclaredCMG();

private :
          HRESULT                         AnalyseDomains();
          void                            ManageNotUpToDateDeclarativeManifolds();
          void                            AttachCommonExtPrimContainerIfNeeded(CATDeclarativeManifoldAgent* iDMAgent);
          void                            AttachRibbonSeedsSharedSorterIfNeeded(CATDeclarativeManifoldAgent* iDMAgent);

          CATLiveBody                   * CreateLiveBodyWithDRepOptions() const;

  //Create AgentContext. Caller has to delete it
          CATDMAgentContext             * CreateAgentContext();

  // CreateImageManifolds
  // iNoLiveBodyChecker permet de desactive le check du body creer lorsqu'on sait qu'il va etre faux.
  // Utilise dans les ODT pour tester des vieux models.
          HRESULT                         CreateImageManifolds(CATCGMJournalList* iCellManifoldsJournal = NULL);
          HRESULT                         CreateImageManifolds(CATCGMJournalList* iCellManifoldsJournal,
                                                               CATBoolean         iNoLiveBodyChecker);
                                                           //, CATBoolean iCalledByLiveOperator = TRUE);

          HRESULT                         CreateImageManifoldGroups(CATCGMJournalList* iCellManifoldsJournal,
                                                                    CATBoolean         iNoLiveBodyChecker);
  //      void                            UpdatePersistentNaming() const; // To be put in Agent

          void                            StreamPersistentCellInfra(CATCGMStream  & Str);

          CATBoolean                      FromAnExternalCaller();

protected:

  CATCellManifoldsManager          * _CMManager;
  CATBoolean                         _CMManagerOwner;

  ListPOfCATBody                     _ListOfCopyInputBodies;
  ListPOfCATBody                     _ListOfNoCopyInputBodies;
  CATBody                          * _OutputBody;
  CATPersistentBody                * _OutputPersistentBody;
  ListPOfCATPersistentBodies         _InputPersistentBodies;
  CATCGMJournalList                  _CellManifoldJournal;
  ListPOfCATDeclarativeManifoldAgent _DMAgents;
  CATXBooleanFalse                   _AllDomainsFromOutputBodyAreInInputBodies;
  CATXBooleanFalse                   _AllDomainsFromInputBodiesAreInOutputBody;
  ListPOfCATDeclarativeManifold      _TypeChangeAllowedDeclarativeManifolds;
  CATBoolean                         _CarrierTypeChangeAllowed;
  ListPOfCATDeclarativeManifold      _DeclarativeManifoldsNotToBeShared;
  CATBoolean                         _SubdivisionAllowed;
  CATBoolean                         _FacePropagation;
  CATBoolean                         _CanonicRecognizerMode;
  CATBoolean                         _DMCreationFromDatumManifoldCarrier;
  CATBoolean                         _ForceCreationOrders;
  CATMathTransformation            * _GlobalTransformation;
  ListPOfCATCell                     _ReportingCells;
  CATCellHashTable                 * _OutputBodyCellHTable;
  ListPOfCATVertex                   _UserDefinedCuttingVertices;
  CATBoolean                         _StoreNotUpToDateDeclarativeManifold;
  CATLISTP(CATDeclarativeManifold) * _NotUpToDateDeclarativeManifold;
  CATLISTP(CATDeclarativeManifold) * _NotUpToDateDeclarativeManifoldParent;
  // IZE Declaration Operator
  ListPOfCATCellManifoldGroup      * _CMGToIgnore;

  CATCGMHashTable                  * _GroupsCarriedBeforeManifoldGroupCarrier;
  ListPOfCATCellManifold             _PatternOfPatternCollisionCM;
  int                                _PatternNumberOfInstances;
  ListPOfCATCellManifoldGroup      * _PatternGroupsInInstances;

  ListPOfCATLiveBody               * _LivificationInputLiveBodyList;
  CATLiveBody                      * _OriginalBodyForKeepManifolds;
  CATBoolean                         _DuplicationMode;

  //TopOpJournal
  CATCGMJournalList                * _TopOpJournal;
  CATBoolean                         _TopOpJournalOwner;

  CATlsoAgentInputDataCarrier      * _AgentInputDataCarrier;

  //VB7 - Carton - 2014 November
  //------_SplitterMode------
  //TRUE : Create SplitterScrt agent
  CATBoolean                         _SplitterMode;
  //------_ContextualSPlitterMode------
  //0 : split contextual CellManifoldGroup
  //1 : keep  contextual CellManifoldGroup together
  int                                _ContextualSplitterMode;

  CATCGMProgressBar                * _pProgressBar;

#ifdef TestPatternRemoveRedo_Drop3_JJ3
  ListPOfCATCellManifold              _PatternCMToRemoveSetByClashAnalysis;
#endif

  // Ajout JJ3 pour suivi des cells dupliquee par la creation du pattern.
  CATPersistentCellInfra           * _LiveInfra;

  CATVariationalPatternParameters  * _VariationalPatternParameters;

  CATBoolean                        _IsFullDomainMove;
  CATBoolean                        _IsLastRun;
  CATBoolean                        _IsCalledByRedoFillet;
  CATBoolean                        _BRepToDRepMode;

  CATDeclarativeOperatorsBridge   * _DeclarativeOperatorsBridge;

  // For Recognizer
  CATDeclarativeContext           * _DeclarativeContext;
  CATDeclarativeApplication         _DeclarativeApplication;    // enum
  CATDeclarativeOriginModeler       _DeclarativeOriginModeler;  // enum
  CATDeclarativeOriginModeler       _DeclarativeOriginModelerForDRepOptions;  // enum


  //VB7 - August 2014
  int                               _NumFatherOperator;

  // QF2 pour eviter le merge des cellules dans une meme cellmanifold en cas de subdivision de cellules
  CATBoolean                        _CellManifoldsCuttingMode;

  // For local recognition
  ListPOfCATFace                    _UserDefinedSelection;

  // For Global Sahred Primitive Container
  CATGMLiveExtrusionPrimitivesContainer* _SharedExtPrimCont;

  // shared ribbon seeds sorter
  CATRibbonSeedsSharedSorter *_RibbonSeedsSharedSorter;
 
private:
  //Local parameters
  CATCGMJournalList               * _LocalJournalList;
  CATBoolean                        _LocalNoLiveBodyChecker;
  CATBoolean                        _LocalGroupMode;
  ListPOfCATCellManifold            _CreatedWithCreationOrderCellManifolds;
  CATListOfInt                      _CreationOrders;
  CATBoolean                        _CreationOrdersAlreadySearched;

  //VB7 W28 2017 - for shm.
  CATIPGMTopOperator              * _ExternalOperatorForDataComputing;
  //End Local parameters
  // --------------------
  // Data FOR CGMReplay
  static CATString                  _OperatorId;

  //VB7 W24 2020
  CATBoolean                        _InSmartContext;
  CATCGMHashTableWithAssoc        * _SmartFacesOnInputBodies;
  CATBoolean                        _InAssembleContext;

};


//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetDeclarativeApplication(CATDeclarativeApplication iDeclarativeApplication) {
  _DeclarativeApplication = iDeclarativeApplication; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetDeclarativeOriginModeler(CATDeclarativeOriginModeler iDeclarativeOriginModeler) {
  _DeclarativeOriginModeler = iDeclarativeOriginModeler; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetDeclarativeOriginModelerForDRepOptions(CATDeclarativeOriginModeler iDeclarativeOriginModeler) {
  _DeclarativeOriginModelerForDRepOptions = iDeclarativeOriginModeler; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::StoreNotUpToDateDeclarativeManifolds(CATBoolean iStoreMode) {
  _StoreNotUpToDateDeclarativeManifold = iStoreMode; }

//-----------------------------------------------------------------------------
INLINE CATBoolean CATCellManifoldsManagerImpl::GetStoreNotUpToDateDeclarativeManifolds() {
  return _StoreNotUpToDateDeclarativeManifold; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::AllowSubdivision() {
  _SubdivisionAllowed = TRUE; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetNoFacePropagation() {
  _FacePropagation = FALSE; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetCanonicRecognizerMode(CATBoolean iMode) {// default is mode is true
  _CanonicRecognizerMode = iMode; } 

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetNumFatherOperator(int iNumFatherOperator) {
  _NumFatherOperator = iNumFatherOperator; }

//-----------------------------------------------------------------------------
INLINE int CATCellManifoldsManagerImpl::GetNumFatherOperator() {
  return _NumFatherOperator; }

//-----------------------------------------------------------------------------
INLINE CATBody * CATCellManifoldsManagerImpl::GetOutputBody() const{
  return _OutputBody; }

//-----------------------------------------------------------------------------
INLINE int CATCellManifoldsManagerImpl::GetNbOfInputBodies() {
  return _ListOfCopyInputBodies.Size() + _ListOfNoCopyInputBodies.Size(); }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::GetCopyInputBodies(ListPOfCATBody &oListOfCopyInputBodies) const {
  oListOfCopyInputBodies = _ListOfCopyInputBodies; }

//-----------------------------------------------------------------------------
INLINE CATCGMJournalList * CATCellManifoldsManagerImpl::GetCellManifoldJournal() const {
  return (CATCGMJournalList *) &_CellManifoldJournal;  }

//-----------------------------------------------------------------------------
INLINE CATMathTransformation *CATCellManifoldsManagerImpl::GetGlobalTransformation() {
  CATMathTransformation * resultTransfo = NULL;
  if(_AgentInputDataCarrier)
    resultTransfo = _AgentInputDataCarrier->GetGlobalTransformation();
  return resultTransfo;  }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetBRepToDRepMode(CATBoolean iBRepToDRepMode) {
  _BRepToDRepMode = iBRepToDRepMode; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetPatternOfPatternCollisionCM(ListPOfCATCellManifold & iCollisionCMList) {
  _PatternOfPatternCollisionCM = iCollisionCMList; }

//-----------------------------------------------------------------------------
INLINE ListPOfCATCellManifold CATCellManifoldsManagerImpl::GetPatternOfPatternCollisionCM() {
  return _PatternOfPatternCollisionCM; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetPatternNumberOfInstances(int iNbInstances) {
  _PatternNumberOfInstances = iNbInstances; }

//-----------------------------------------------------------------------------
INLINE int CATCellManifoldsManagerImpl::GetPatternNumberOfInstances() {
  return _PatternNumberOfInstances; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetPatternGroupsInInstances(ListPOfCATCellManifoldGroup * iGroupLists) {
  _PatternGroupsInInstances = iGroupLists; }

//-----------------------------------------------------------------------------
INLINE ListPOfCATCellManifoldGroup * CATCellManifoldsManagerImpl::GetPatternGroupsInInstances() {
  return _PatternGroupsInInstances; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetLivificationInputLiveBodyList(ListPOfCATLiveBody * ipLivificationInputLiveBodyList) {
  _LivificationInputLiveBodyList = ipLivificationInputLiveBodyList; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds) {
  _OriginalBodyForKeepManifolds=iOriginalBodyForKeepManifolds; }

//-----------------------------------------------------------------------------
#ifdef TestPatternRemoveRedo_Drop3_JJ3
INLINE ListPOfCATCellManifold CATCellManifoldsManagerImpl::GetPatternCMSetToRemoveByClashAnalysis() {
  return _PatternCMToRemoveSetByClashAnalysis; }
#endif

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetLiveInfra(CATPersistentCellInfra * iLiveInfra) {
  _LiveInfra = iLiveInfra; }

//-----------------------------------------------------------------------------
INLINE CATPersistentCellInfra * CATCellManifoldsManagerImpl::GetLiveInfra() {
  return _LiveInfra; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetFullDomainMove() {
  _IsFullDomainMove = TRUE; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetIsLastRun(CATBoolean iIsLastRun) {
  _IsLastRun = iIsLastRun; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet) {
  _IsCalledByRedoFillet = iIsCalledByRedoFillet; }

//-----------------------------------------------------------------------------
INLINE CATBoolean CATCellManifoldsManagerImpl::GetCellManifoldsCuttingMode() const {
  return _CellManifoldsCuttingMode; } 

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetCellManifoldsCuttingMode(CATBoolean iBoolValue) {
  _CellManifoldsCuttingMode = iBoolValue; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetProgressBar(CATCGMProgressBar * ipProgressBar) {
  _pProgressBar = ipProgressBar; }

//-----------------------------------------------------------------------------
INLINE CATDeclarativeContext * CATCellManifoldsManagerImpl::GetDeclarativeContext() const {
  return _DeclarativeContext; }

//-----------------------------------------------------------------------------
INLINE CATDeclarativeApplication CATCellManifoldsManagerImpl::GetDeclarativeApplication() const {
  return _DeclarativeApplication; }

//-----------------------------------------------------------------------------
INLINE CATDeclarativeOriginModeler CATCellManifoldsManagerImpl::GetDeclarativeOriginModeler() const {
  return _DeclarativeOriginModeler; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetRedeclaredCMG(ListPOfCATCellManifoldGroup * iCMGToIgnore) {
  _CMGToIgnore = iCMGToIgnore; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::AddCopyInputBody(CATBody *iInputBody) {
  _ListOfCopyInputBodies.Append(iInputBody); }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::AddNoCopyInputBody(CATBody *iInputBody) {
  _ListOfNoCopyInputBodies.Append(iInputBody); }

//-----------------------------------------------------------------------------
INLINE CATDeclarativeOriginModeler CATCellManifoldsManagerImpl::GetDeclarativeOriginModelerForDRepOptions() const {
  return _DeclarativeOriginModelerForDRepOptions; }

//-----------------------------------------------------------------------------
INLINE ListPOfCATCellManifoldGroup * CATCellManifoldsManagerImpl::GetRedeclaredCMG() {
  return _CMGToIgnore; }

//-----------------------------------------------------------------------------
//Local parameters
INLINE void CATCellManifoldsManagerImpl::SetLocalJournalList(CATCGMJournalList * iLocalJournalList) {
  if(_LocalJournalList)
    CATSysDeletePtr(_LocalJournalList);
  if(iLocalJournalList)
  {
    _LocalJournalList = new CATCGMJournalList(GetSoftwareConfiguration(), NULL);
    iLocalJournalList->Duplicate(_LocalJournalList);
  }
}

//-----------------------------------------------------------------------------
INLINE CATCGMJournalList * CATCellManifoldsManagerImpl::GetLocalJournalList() {
  return _LocalJournalList; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::CleanLocalJournalList() {
  CATSysDeletePtr(_LocalJournalList); }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetLocalNoLiveBodyChecker(CATBoolean iLocalNoLiveBodyChecker) {
  _LocalNoLiveBodyChecker = iLocalNoLiveBodyChecker; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetLocalGroupMode(CATBoolean iLocalGroupMode) {
  _LocalGroupMode = iLocalGroupMode; }
//End Local parameters
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
INLINE void  CATCellManifoldsManagerImpl::GetInputPersistentBodies(ListPOfCATPersistentBodies & oInputPersistentBodies) const
{
  oInputPersistentBodies.Append(_InputPersistentBodies);
}

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetExternalOperatorForDataComputing(CATIPGMTopOperator * iExternalOperatorForDataComputing) {
  _ExternalOperatorForDataComputing = iExternalOperatorForDataComputing; }

//-----------------------------------------------------------------------------
INLINE CATIPGMTopOperator * CATCellManifoldsManagerImpl::GetExternalOperatorForDataComputing() {
  return _ExternalOperatorForDataComputing; }

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetSmartContext(CATBoolean iSmartContext) {
  _InSmartContext = iSmartContext;
}

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetAssembleContext(CATBoolean iAssembeContext) {
  _InAssembleContext = iAssembeContext;
}

//-----------------------------------------------------------------------------
INLINE void CATCellManifoldsManagerImpl::SetSmartFacesOnInputBodies(CATCGMHashTableWithAssoc * iSmartFacesOnInputBodies) {
  _SmartFacesOnInputBodies = iSmartFacesOnInputBodies;
}

//-----------------------------------------------------------------------------
INLINE CATCGMHashTableWithAssoc * CATCellManifoldsManagerImpl::GetSmartFacesOnInputBodies() const {
  return _SmartFacesOnInputBodies;
}
#endif
