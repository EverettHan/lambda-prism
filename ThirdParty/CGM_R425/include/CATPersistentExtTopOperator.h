#ifndef CATPersistentExtTopOperator_H
#define CATPersistentExtTopOperator_H

#include "PersistentCell.h"
#include "CATAdvancedExtTopOperator.h"
#include "CATCGMJournalList.h"
#include "CATGMLivePersistentCellInformer.h"
#include "CATXBooleanTrue.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
// #include "CATlsoPersistentContext.h"
#include "CATExtGeoOperator.h"
#include "CATlsoBodyTrackerDebug.h"
#include "CATlsoError.h"// Tres moche. => Engendre un temps de compilation fou.
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATPersistentBodies.h"

class CATAutoBaseThreadContext;
class CATPersistentBody;
class CATGeoFactory;
class CATSofwareConfiguration;
class CATlsoPersistentContext;
class CATBody;
class CATGMLiveShapeExtTopOperator;
class CATCGMOutput;
class CATTopOpInError;
class CATlsoStreamableAlgoElt;
class CATlsoAgentInputDataCarrier;
class CATPersistentCellInfra;

// For CGMReplay multi-run
ExportedByPersistentCell CATBoolean CATPersistentExtTopOperator_FirstWriteInput(CATCGMStream  & ioStr);

class ExportedByPersistentCell CATPersistentExtTopOperator : public CATAdvancedExtTopOperator
{
public:
  
/** @nodoc 
  * cannot be called
  */
  // Constructor
  CATPersistentExtTopOperator(CATGeoFactory            & iFactory,
                              CATBody                  & iInputBody,
                              CATSoftwareConfiguration * iConfig,
                              CATPersistentCellInfra   * iPersistentInfra=NULL,
                              CATBoolean                 iMultiRunOperator=FALSE,
                              CATBoolean                 iCreatePersistentBodies=TRUE /*To remvove !*/); 

  CATPersistentExtTopOperator(CATGeoFactory            & iFactory,
                              CATPersistentBody        & iInputPersistentBody,
                              CATSoftwareConfiguration * iConfig,
                              CATPersistentCellInfra   & iPersistentInfra,
                              CATBoolean                 iMultiRunOperator=FALSE);
  
  CATPersistentExtTopOperator(CATGeoFactory             & iFactory,
                              const ListPOfCATBody      & iInputBodies,
                              CATSoftwareConfiguration * iConfig,
                              CATPersistentCellInfra   * iPersistentInfra=NULL,
                              CATBoolean                 iMultiRunOperator=FALSE,
                              CATBoolean                 iCreatePersistentBodies=TRUE /*To Remove !*/);                              

  CATPersistentExtTopOperator(CATGeoFactory                    & iFactory,
                              const ListPOfCATPersistentBodies & iInputPersistentBodies,
                              CATSoftwareConfiguration         * iConfig,
                              CATPersistentCellInfra           & iPersistentInfra,
                              CATBoolean                         iMultiRunOperator=FALSE);

  // Constructeur sans input body. Pour les operateurs multi-inputs.
  CATPersistentExtTopOperator(CATGeoFactory              & iFactory,
                              CATSoftwareConfiguration   * iConfig,
                              CATPersistentCellInfra     * iPersistentInfra=NULL,
                              CATBoolean                   iMultiRunOperator=FALSE );

  
  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  //------------------------------------------------------
  // CastToCATGMLiveShapeExtTopOperator
  //------------------------------------------------------
  virtual CATGMLiveShapeExtTopOperator * CastToCATGMLiveShapeExtTopOperator() const;
  virtual CATPersistentExtTopOperator  * GetAsPersistentExtTopOperator() const;

  CATSoftwareConfiguration * GetSoftwareConfiguration() const;

  //------------------------------------------------------
  // Autorise le MultiRun (en mode CATCGMReplay)
  // WARNING : It's a derivated metyhode from CATExtGeoOperator
  //------------------------------------------------------
  virtual CATBoolean AllowMultiRun() const; // from CATExtGeoOperator.h
  virtual CATBoolean IsMultipleRun();       // from CATExtGeoOperator.h

  // Surchage du Run() principal.
  // -------------------------------------------------------------
  int RunOperator();
  // -------------------------------------------------------------

  virtual int   RunPersistentOperator() = 0;
  virtual void  CleanResultForMultiRun();
  virtual CATBoolean JustBeforeRunPersistentOperator(); // Return if run is needed
  virtual int   JustAfterRunSpecialInterruptCheck();
  virtual void  JustAfterRunPersistentOperator();
  virtual void  CleanMemoryAfterRunPersistentOperator();

  // GetResult : overloaded method
  virtual CATBody * GetResult();

  // -------------
  // Set Methodes
  // -------------
  // Do not use : call SetPersistentBodyResultAndLastJournalResult
  void SetPersistentResultBody(CATPersistentBody * iResultPBody);
  // Do not use : call SetPersistentBodyResultAndLastJournalResult
  void SetJournalForLastResult(CATCGMJournalList * iJournal,CATBoolean iRecordACopy=FALSE, CATBoolean iAllowEmptyJournal=FALSE);

  // Return TRUE if the record is done.
  CATBoolean SetPersistentBodyResultAndLastJournalResult(CATPersistentBody * iResultPBody,
                                                         CATCGMJournalList * iJournal,
                                                         CATBoolean          iRecordAJournalCopy=FALSE);

  INLINE void SetInputWorkPersistentBody(CATPersistentBody * iInputWorkPersistentBody);
  void ReplaceInputPersistentBodyOrder(int iNum, CATPersistentBody * iPersistentBody);
  CATPersistentBody * ComputeInputPersistentBodyWithJournal(CATBody * iBody, CATCGMJournalList * iJournal);

  // -------------
  // Get Methodes
  // -------------
  INLINE void SetInputAsOutputProtection(CATBoolean iProtection);
  INLINE CATGMLivePersistentCellInformer &GetPersistentCellInformer();
  virtual INLINE int GetNumberOfRun() const;

  CATPersistentCellInfra  & GetPersistentCellInfra() const;
  CATBoolean                IsPersistentCellInfra()  const;

  CATBody                        & GetInputBody(CATBoolean iForceRealInput=FALSE) const;
  CATPersistentBody              * GetInputPersistentBody(CATBoolean iForceInputOnly=FALSE,int index=1) const;
  void                             GetInputPersistentBodies(ListPOfCATPersistentBodies & oInputPersistentBodies, CATBoolean iForceInputOnly=FALSE) const;
  CATPersistentBody              * GetResultPersistentBodyForSharedInfra() const;
  CATlsoPersistentContext        & GetPersistentContext() const; // safe
  INLINE CATPersistentBody       * GetResultPersistentBody() const; // LAP: a remetre en protected une fois la migration TFEngine finie.
  INLINE CATlsoPersistentContext * GetContext() const;

  virtual void GetLocalInputPersistentBodyList(CATLISTP(CATPersistentBody) &ioLocalInputPersistentBodyList) const;

  void TransfertInterruptionToOtherContext(CATlsoContext * iContext);

  // ----------------
  // for debug only
  // ----------------
  // Only use in the CATLoad of CGMReplay
  // SetCGMMode(0) ou SetCGMMode(CtxClassicMode)           : classic mode
  // SetCGMMode(1) ou SetCGMMode(CtxDebugWithoutErrorBody) : debug mode without error body
  // SetCGMMode(2) ou SetCGMMode(CtxDebugWithErrorBody)    : debug mode with error body
  // Do not use.
  void SetCGMMode(short iCGMMode);  // Le calleur doit passer par le Context directement.


  virtual void ReplacePersistentContext(CATlsoPersistentContext  * iNewContext, CATBoolean iDeleteBasicContext=TRUE);

  // ----------------
  // For debug only
  // ----------------
  void SetAllowMultiRunCGMReplay(CATBoolean iAllowMultiRunCGMReplay, CATBoolean iTestMode=FALSE);

  // for CGMReplay Only
  virtual void Dump(CATCGMOutput& os);
  virtual void DumpOutput(CATCGMOutput& os);
  void CreateCGMRunTransactionForCGMReplay(CATCGMWarning iMode=Warning_On) const;

  // For CGMReplay
  // Multi-InputData  Stream/Unstream
  // Read and Write input data from lsoPersistentContext -> _PersistentContext
  virtual void WriteMultiInputData(CATCGMStream  &ioStr) const;
  virtual void ReadMultiInputData (CATCGMStream  &iStr) const;
  virtual CATlsoStreamableAlgoElt * GetInputDataObject (int iAdminIndex) const;

  virtual CATBoolean IsBodyToBeKeptForNextRuns(CATPersistentBody *iPersistentBody) const;
  virtual void GetPersistentBodiesNecessaryForNextRun(ListPOfCATPersistentBodies &oPersistentBodiesNecessaryForNextRun) const;
 
  virtual CATlsoAgentInputDataCarrier * CreateAgentInputDataCarrier();
  virtual void                          UpdateAgentInputDataCarrier(CATlsoAgentInputDataCarrier * iAgentInputDataCarrier);
  virtual void                          ResetAgentInputDataCarrier();

  //VB7 - LocalBuild
  virtual CATBoolean ThisRunIsLocal();
  virtual CATBoolean IsActivatedLocalRun() const;
  virtual void DeclareRunAsLocal(ListPOfCATPersistentFaces * iLocalInputPFaceList);
  //virtual void GetAdditionalPFaceListForLocalBuild(ListPOfCATPersistentFaces & oAdditionalPFaceList);
  virtual void UnDeclareRunAsLocal();
  //virtual CATPersistentBody * GetComplementaryPBodyForLocalBuild(CATBoolean iWithCrownOption=TRUE);
  virtual CATBody * GetLocalComplementaryBodyForLocalBuild(CATMathBox & iModifiedMathBox);
  virtual CATPersistentBody * GetLocalBuildPBody(CATPersistentBody * iRefPBody);

protected:

  // -----------------------------------------------------
  // RunAdvancedOperator
  // -----------------------------------------------------
  virtual int RunAdvancedOperator();

  // -----------------------------------------------------
  // Set Methods
  // -----------------------------------------------------
  void        InsertJournalForLastResult(CATCGMJournalList * iJournal, CATBoolean iRecordACopy=FALSE);
  // CATBoolean  GetInterruptionRequested(const CATBoolean iThrowIfInterrupted=FALSE) const;  // To remove
  void        SetCopyOfMainError(const CATTopOpInError *iLastError); // internal use only
  // To use carefully, only for multi input bodies operators
  int         AppendInputBody(CATBody * iOneInputBody, CATBoolean iCreatePersistentBody, CATPersistentBody **oCreatedPersistentBody=NULL);
  int         AppendInputPersistentBody(CATPersistentBody * iOneInputPBody, CATBoolean iAddToPersistentInfra = FALSE);

  // Fast Run - for odt only
  // Replace and set a new input body
  int        ReplaceInputBody(CATBody * iInputBody, int iNum=1, CATBoolean iCreatePersistentBody=TRUE, CATPersistentBody **oCreatedPersistentBody=NULL);

  // -----------------------------------------------------
  // Get Methods
  // -----------------------------------------------------
  INLINE CATCGMJournalList * GetJournalForLastResult() const; // do not use, please
  CATTopOpInError          * GetCopyOfMainError()      const; // internal use only
  INLINE CATBoolean  IsPersistentInfraExpected() const;

  // ------------------------------------------------------------------------------------
  // Virtual Sub-Methods
  // ------------------------------------------------------------------------------------
  virtual void CheckJournalForDebug(CATCGMJournalList * iJournal = NULL);

  void CreateInputPersistentBodies();

  // Utilities
  CATBoolean AreInputsMultiFactory();

  // For Incremental Run
  INLINE void SetNbIncrementalRunsForCGMReplay(int iNbRuns);
  INLINE int  GetNbIncrementalRunsForCGMReplay() const;
  void ModifyDoubleForIncrementalMultiRun(double & ioDoubleValue, double iStartValue=0.); // Exemple of used in CATGMLiveShapeSingleThicknessFaceImpl::ModifyValueForIncrementalMultiRun()
  void ModifyMathVectorForIncrementalMultiRun(CATMathVector & ioMathVector);  // Exemple of used in CATGMLiveShapeSingleDeformFaceImpl::ModifyValueForIncrementalMultiRun()
  void ModifyMathTransformationForIncrementalMultiRun(CATMathTransformation & ioTransformation);
  void ModifyIntegerForIncrementalMultiRun(int & ioIntegerValue);
  // Sub methode used in RunPersistentOperator
  virtual void ModifyValueForIncrementalMultiRun();
  void CheckForIncrementalMultiRun();

  // for CGMReplay
  void DumpOperatorName(CATCGMOutput & os, const char * iOpName=NULL);

  // For Debug ondy
  void CreateBodyTrackerDebug();
  void CreateLSOFileWithAdditionalName();

  // Destructor
  virtual ~CATPersistentExtTopOperator();

  // Internal Data
  CATlsoPersistentContext  * _PersistentContext;
  CATCGMJournalList        * _JournalForLastResult;
  //int                        _NumOperatorId;    //VB7 05-18-2016

private:
 
  // -------------------------------
  // Internal Methodes
  // -------------------------------
  void ClearJournal(CATCGMJournalList &iJournalToCean);
  void CleanDataBeforeRunForMultiRun();

  INLINE void IncrementNumberOfRun();

  // ----------------------------------
  // Internal DEBUG
  // ----------------------------------
  void ForceDRepBehavior_Debug();

  void InitPersistentOperator();
  void InitCOUT();
  void EndCOUT();

  // --------------------------------------------------------------------
  // Internal Data
  // --------------------------------------------------------------------
  // CATPersistentCellInfra           * _PersistentCellInfra; removed week-40 Y2018
  ListPOfCATPersistentBodies         _InputPersistentBodies;
  CATPersistentBody                * _InputWorkPersistentBody;
  CATPersistentBody                * _ResultPersistentBody;
  CATCGMJournalList                * _CopyOfInputJournal;
  CATGMLivePersistentCellInformer    _PersistentCellInformer;
  CATBoolean                         _FirstPass;
  CATBoolean                         _MultiRunOperator;
  CATBoolean                         _AllowMultiRunCGMReplay;
  CATBoolean                         _CreatePersistentBodies;
  int                                _NbIncrementalRunsForCGMReplay;
  CATBoolean                         _InputAsOutputProtection;
  
  // For multiRun
  int                                _CountNumberOfRun;

  // For debug only
  CATTopOpInError                  * _CopyOfMainError;   // Is set in CGMReplayMode Only
  CATlsoBodyTrackerDebug           * _BodyTrackerDebug;  // For debug only

};

// ------------------------------------------------------------------------
// INLINE methodes
// ------------------------------------------------------------------------

INLINE void CATPersistentExtTopOperator::SetInputAsOutputProtection(CATBoolean iProtection) {
  _InputAsOutputProtection = iProtection; }

INLINE CATGMLivePersistentCellInformer & CATPersistentExtTopOperator::GetPersistentCellInformer() {
  return _PersistentCellInformer; }

INLINE void CATPersistentExtTopOperator::IncrementNumberOfRun() {
  _CountNumberOfRun++; }

INLINE int CATPersistentExtTopOperator::GetNumberOfRun() const {
  return _CountNumberOfRun; }

// ------------------------------------------------------------------------
// GetResultPersistentBody
// ------------------------------------------------------------------------
INLINE CATPersistentBody * CATPersistentExtTopOperator::GetResultPersistentBody() const {
  return _ResultPersistentBody; }

// ------------------------------------------------------------------------
// GetContext
// ------------------------------------------------------------------------
INLINE CATlsoPersistentContext *CATPersistentExtTopOperator::GetContext() const{
  return _PersistentContext;
}

// ------------------------------------------------------------------------
// GetJournalForLastResult
// ------------------------------------------------------------------------
INLINE CATCGMJournalList * CATPersistentExtTopOperator::GetJournalForLastResult() const {
  return _JournalForLastResult; }

INLINE CATBoolean  CATPersistentExtTopOperator::IsPersistentInfraExpected() const {
  return _CreatePersistentBodies; }

// ------------------------------------------------------------------------
// SetInputWorkPersistentBody
// ------------------------------------------------------------------------
INLINE void CATPersistentExtTopOperator::SetInputWorkPersistentBody(CATPersistentBody * iInputWorkPersistentBody) {
  _InputWorkPersistentBody = iInputWorkPersistentBody; }

INLINE void CATPersistentExtTopOperator::SetNbIncrementalRunsForCGMReplay(int iNbRuns) {
  _NbIncrementalRunsForCGMReplay=iNbRuns; }

INLINE int CATPersistentExtTopOperator::GetNbIncrementalRunsForCGMReplay() const {
  return _NbIncrementalRunsForCGMReplay; }

#endif
