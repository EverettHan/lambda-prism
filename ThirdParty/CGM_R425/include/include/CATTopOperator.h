#ifndef CATTopOperator_H
#define CATTopOperator_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMOperator.h"
#include "CATTopData.h"
#include "CATMathDef.h"
#include "CATBodyFreezeMode.h"

#include "ListPOfCATBody.h"
#include "CATListOfCATGeometries.h"
#include "ListPOfCATCell.h"
#include "CATTopOpInError.h"
#include "CATListPOfCATCGMDiagnoses.h"
#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
#include "CATGeometryType.h"
#include "CATTopCheckJournalType.h"
#ifdef CATIACGMV5R22
struct CATCGMVoBResult;
class CATLISTP(CATCGMVoBResult);
#endif 


class CATICGMUnknown;
class CATGeometry;
class CATBody;
class CATError;
class CATCGMJournal;
class CATCGMJournalList;
class CATSoftwareConfiguration;
class CATTopCheckJournalData;
class CATCGMStream;
class CATExtTopOperator;
class CATCGMODTScaleManager;
class CATCellManifoldsManager;
class CATExtTopOperator;
#ifdef CATIACGMV5R20
class CATTopMultiResult;
class CATCGMCellTracker;
#endif 

#ifdef CATIACGMV5R20
class CATContextForFastRun;
class CATContextForFastRunExt;
#endif 
class CATDeclarativeManifoldAgent;
class CATLISTP(CATDeclarativeManifoldAgent);
#ifdef CATIACGMV5R22
struct CATCGMVoBTool;
#endif 
#ifdef CATIACGMR215CAA
class CATPGMDRepBehavior;
#endif

  /**
*  ***********************************************************************
*  *******                         WARNING                         *******
*  ***********************************************************************
*  *******
*  *******  This class is Not supported any longer.
*  *******  it has been replaced by CATICGMTopOperator
*  *******
*  *******
*  ***********************************************************************
*  ***********************************************************************
*
*  CATTopOperator  class has been removed from CAA in 3DEXPERIENCE level and
*  has been replaced by CATICGMTopOperator.
*  We recommend you to use only CATICGMTopOperator, in order you will  be
*  able to easily migrate your CAA code from  V5 to 3DEXPERIENCE level.
*
   * Abstract class for the topological operators.
   *<br>
   * The topological operators follow the use frame of all operator and satisfy to the smart mechanism: the
   * input bodies are not modified. A new resulting body is created, 
   * possibly sharing data with the input ones. They are not streamable.
   * To use a topological operator:
   *<ul>
   * <li>Create it with the <tt>CATCreateTopXxx</tt> global methods
   * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
   * <li>Run it
   * <li>Get the result with the <tt>GetResult</tt> method. If you do not want 
   * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory.
   *<li><tt>delete</tt> it after use.
   *</ul> 
   */
class ExportedByCATTopologicalObjects CATTopOperator : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATTopOperator);
public:
   
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   /**
   * Destructor.
   */
   virtual ~CATTopOperator();
   
 	/**
 	* Returns a pointer to the resulting body.
	* The body is frozen and completed if <tt>CATBodyFreezeOn</tt> is active (default mode).
	* @return
	* The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
	*/
  virtual CATBody * GetResult();
   
   /**
   * Returns the pointer to the resulting body.
   * The pointer to the journal of the operation.
   * @param iJournal
   * The pointer to the journal to fill.
   * @return
   * The pointer to the resulting body. If you do not want to keep it, 
   * use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory.
   */
   virtual CATBody* GetResult(CATCGMJournalList* iJournal);
 
   
	/**
	 * Defines the state of the resulting body.
	 * @param iOnOrOff
	 * The state of the resulting body. 
	 */
  void SetFreezeMode(CATBodyFreezeMode iOnOrOff);
	
	/**
	 * Returns the mode in which the resulting body is created.
	 * @return
	 * The smart mode.
	 */
  CATBodyFreezeMode GetFreezeMode()const;
 
   /**
   * Returns a pointer to the topological journal associated with <tt>this</tt> CATTopOperator.
   * <br>Only available if a journal was given at the operator creation.
   * @return
   * The pointer to the journal of the operation.
   */
   CATCGMJournalList* GetJournal() ;

   /**
   * Returns the input objects used by <tt>this</tt> CATTopOperator to create its journal.
   * @param oSucceeded
   * This returned value tells whether <tt>this</tt> CATTopOperator
   * actually defined its journal inputs or not. If <tt>FALSE</tt>,
   * the content of <tt>oObjects</tt> should not be relied on.
   * @param oObjects
   * The list of requested inputs.
   * @param iCopy_Or_Not
   * The copy status of requested input objects.
   * <br><b>Legal values</b>:
   * <dl><dt><tt> CATTopCheckCopy </tt></dt><dd>
   *     <dt><tt> CATTopCheckNoCopy </tt></dt><dd>
   *     <dt><tt> CATTopCheckNeutral </tt></dt><dd></dl>   
   * @param iTypeOfObjects
   * The geometric type of the requested input objects.
   */
   virtual void GetInputObjectsForJournal(CATBoolean              & oSucceeded,
                                          CATLISTP(CATICGMObject) & oObjects,
                                          CATTopCheckJournalType    iCopy_Or_Not = CATTopCheckCopy,
                                          CATGeometricType          iTypeOfObjects = CATBodyType) ;
  
#ifdef CATIACGMV5R21
   /**
   * @nodoc
   * Associates an interruption function with this operator.
   * @param ipInterruptFunction
   * The interruption function to be written by the application calling this operator.
   * Must return TRUE if the operator is to be interrupted.
   */
   void EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction);
#endif
  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   /**
   * @nodoc
   */
   virtual CATBoolean HasConsistentResult(CATLONG32 & nberr, CATError **& Diagnostic) const;
   
   /** @nodoc */
   void GetTopData(CATTopData& oTopData) const;
   
   /** 
   * @nodoc
   * Defines the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @param iConfig
   * The Software configuration.
   */
   virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig);
   
   /** 
   * @nodoc
   * Returns the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @return
   * The Software configuration.
   */
   virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;
   
   /** @nodoc */
   CATTopOpInError* GetWarning();

   /** @nodoc */
   void AppendWarning(CATCGMDiagnosis* iWarning);


   /** @nodoc */
   void RemoveAllWarning();

   
   /** @nodoc @nocgmitf  CheckJournal / pour donner les entrees de l'operateur ... */
   void AddInputBody(CATBody* input, CATTopCheckJournalType copy_or_not = CATTopCheckCopy);
   
   /** @nodoc @nocgmitf  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
   void AddInputObject(CATICGMObject* obj, CATTopCheckJournalType copy_or_not = CATTopCheckNoCopy);
   
   /** @nodoc @nocgmitf  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
   void AddInputObjects(const CATLISTP(CATGeometry)& objs, CATTopCheckJournalType copy_or_not = CATTopCheckNoCopy);
   
   
   /** @nodoc @nocgmitf  CheckJournal /pour donner d'autres entree non Body (elements de sketch ...) ... */
   void GetInputBodies(CATLISTP(CATBody)& );
   
   /** @nodoc @nocgmitf  CheckJournal /... */
   void SetOutputBody(CATBody* iResult);
   
   /** @nodoc @nocgmitf  CheckJournal /... */
   CATBody* GetOutputBody();
   

    /** @nodoc @nocgmitf CATTopCheckJournal : returns null value only if no error detected,   */
   int BasicCheckJournal(int iLevelOfCheck = 10, CATCGMOutput *iForceDump=NULL);

    /** @nodoc @nocgmitf CATTopCheckJournal   */
   virtual void RequireDefinitionOfInputAndOutputObjects();

    /** @nodoc @nocgmitf CATTopCheckJournal   */
   CATBoolean IsFullyDefinedForInputAndOutputObjects();

    /** @nodoc @nocgmitf CATTopCheckJournal   */
    void SetFullyDefinedForInputAndOutputObjects(CATBoolean iStatus);



    /** @nodoc @nocgmitf CATCGMReplay associe avec CATTopOperator::WriteInput()  */
   static void LoadInOutput(CATCGMStream& ioStream, 
     CATGeoFactory*          &iFactory,
     CATTopData              &ioTopData,
     CATBodyFreezeMode       &iFreezeMode,
     CATLISTP(CATICGMObject) &ioInputCopy,
     CATLISTP(CATICGMObject) &ioInputNoCopy, 
     CATBody*                &ioOutputBody,
     CATLISTP(CATICGMObject) *ioInputNeutral = NULL,
     // l'appelant passe un ScaleManager s'il est pret a gerer
     // le rescale des donnees, ainsi que l'acces aux elements
     // par leur tag via ce ScaleManager. NLD020807
#ifdef CATIACGMV5R20
     CATCGMODTScaleManager   *iCGMODTScaleManager=NULL,
     CATContextForFastRunExt* iopCtxExt = NULL);
#else
     CATCGMODTScaleManager   *iCGMODTScaleManager=NULL);
#endif

    /** @nodoc @nocgmitf CATCGMReplay  */
   void WriteTopOperator(CATGeoFactory  *iFactory, 
                         CATCGMStream   &ioStream, 
                         CATBoolean      iWithSpecifiedInOut = FALSE);

    /** @nodoc @nocgmitf CATCGMReplay  */
   static void ReadTopOperator(CATGeoFactory* iFactory,CATCGMStream& ioStream, 
     CATTopData            &ioTopData,
     CATBodyFreezeMode     &iFreezeMode,
     CATBoolean iWithSpecifiedInOut       = FALSE,
     CATLISTP(CATICGMObject) *ioInputCopy   = NULL, 
     CATLISTP(CATICGMObject) *ioInputNoCopy = NULL, 
     CATBody*                *ioOutputBody  = NULL,
     CATLISTP(CATICGMObject) *ioInputNeutral = NULL,
     // l'appelant passe un ScaleManager s'il est pret a gerer
     // le rescale des donnees, ainsi que l'acces aux elements
     // par leur tag via ce ScaleManager. NLD020807
     CATCGMODTScaleManager   *iCGMODTScaleManager=NULL,
     CATContextForFastRunExt* iopCtxExt = NULL);

    /** @nodoc @nocgmitf CATCGMReplay  / CATTopCheckJournal */
   void DefineInputAndOutputObjects(CATLISTP(CATICGMObject) &InputCopy,
                                    CATLISTP(CATICGMObject) &InputNoCopy, 
                                    CATBody*                &OutputBody,
                                    CATLISTP(CATICGMObject) *ioInputNeutral = NULL);
  
   /**
   * @nodoc
   */
   virtual CATBoolean GivesBodyAsResult() const;

   /**
   * @nodoc
   */
   virtual CATBoolean GivesValidJournalAsResult(CATCGMJournalList ** ioDuplicatedButExpectedValid) const;



    /** @nodoc @nocgmitf CATCGMReplay pour obtenir la liste des objets concernees par l'operation  */
   CATBoolean HasInOutReplayDefinition(CATLISTP(CATICGMObject) & ioObjects,
                                       const CATBoolean          iAskForInputCopy    = TRUE,
                                       const CATBoolean          iAskForInputNoCopy  = TRUE,
                                       const CATBoolean          iAskForInputNeutral = TRUE,
                                       const CATBoolean          iAskForOutput       = TRUE);


  /** @nodoc  */
  inline CATExtTopOperator *GetTopExtensible(CATBoolean iRequired = TRUE) const;

   
  /** @nodoc @nocgmitf : CATCGMReplay  / Dump de la definition de l'operateur et son status actuel (Config,Input) + affinite */
  virtual void Dump( CATCGMOutput& os ) ;
   
  /** @nodoc @nocgmitf : CATCGMReplay  / Dump du resultat de l'execution l'operateur (Body,Journal) + affinite */
  virtual void DumpOutput(CATCGMOutput &os);

  /** @nodoc @nocgmitf : CATCGMReplay  / Sauvegarde des informations avant execution (Input/Output ,Config, ..) + affinite */
  void WriteInput(CATCGMStream  & ioStream);

  /** 
  *  @nodoc 
  *  Warning: This API is not stable and is only used for debug.
  *  NOT TO BE USED IN CAA APPLICATIONS
  */
  static int CleanNewerUnused(CATICGMUnknown* ipBodyOrFactory);

  /** @nodoc : debug objets + bodies implicites */
  static int CleanAnyNewerUnused(CATICGMUnknown* ipBodyOrFactory);

   /** @nodoc  */
  void CreateManifolds(ListPOfCATBody &iListOfInputBodies, CATBody * iOutputBody, 
    CATCGMJournalList* iTopOpJournal, CATCGMJournalList* ioManifoldBasedJournal = NULL);

  /** @nodoc */
  HRESULT AppendDeclarativeManifoldAgent(CATDeclarativeManifoldAgent* &ioAgent);

  /** @nodoc */
  CATBody* GetLiveResult();
  /** @nodoc */
  CATBody* GetLiveResult(CATCGMJournalList* ioManifoldBasedJournal);

#ifdef CATIACGMV5R20
  public :
  /**
   * @nodoc
   * @return [out, CATBaseUnknown#Release]
  */
  virtual CATContextForFastRun* GetContextForFastRun(CATBoolean iGetOnly = FALSE);
#endif
#ifdef CATIACGMV5R20
   public :
     /** 
   * @nodoc
   *  Enable the cell tracking
   * @param iEnable
   * value used to enable or disable the cell tracking. 
   * Default value: TRUE (Enable)  
   */
	void       EnableCellTracker(CATBoolean iEnable = TRUE);

     /** 
   * @nodoc
   *  Returns the current status of Cell Tracker Activation
   * @return
   * return TRUE if enable otherwise FALSE
   */
	CATBoolean IsCellTrackerEnable();




protected :

    /** 
   * @nodoc
   * @return
   * The pointer to the journal of the operation.
   */
   virtual  CATCGMJournalList* GetJournalForCellTracker() ;

public:

     /** 
   * @nodoc
   *  Must be called after Run() 
   *  Create a cell tracker service 
   * @return
   * A pointer on the created cell tracker
   * You must delete the cell tracker after usage
   */
	virtual    CATCGMCellTracker * CreateCellTracker();

    /** 
   * @nodoc @nocgmitf
   *  Returns CATTopMultiResult if this operator is multiple result.
   * @return
   * return CATTopMultiResult * result
   */
	virtual  CATTopMultiResult * IsMultiResult();
  
#endif

#ifdef CATIACGMR217CAA
   /** 
   * @nodoc @nocgmitf
   *  Returns true for this class.
   * @return
   * return CATBoolean 
   */
   virtual  CATBoolean IsACATTopOperator();
#endif

#ifdef CATIACGMV5R22
/**
   * @nodoc
 */
  virtual void SetVoBTool(CATCGMVoBTool * iTool);

/**
   * @nodoc
 */
  virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) & iFailureResults, CATBoolean iBlock, CATBoolean &iCompletion);
#endif

#ifdef CATIACGMR215CAA
/**
  *  @nodoc 
  *  SetDRepBehavior defines the behavior of the lifivication and of the journal.
  *  @param iDRepBehavior : Use CATDeclarativeContext and CATDeclarativeApplication to create this object. 
  *  NOT TO BE USED IN CAA APPLICATIONS
  */
  virtual void SetDRepBehavior (CATPGMDRepBehavior *iDRepBehavior);

  /**
  * Activates Failsafe mode : in the case of failure, instead of throwing an error,
  * a partial or non-optimal result is returned.
  * <br> Please notice that not all operators support this mode. By default an operator doesn't support Failsafe,
  * except where it is explicitly declared.
  * <br> This option is not activated by default.
  * <br> The error diagnosis are stored by the operator, and can be retrieved via <tt>GetFailsafeDiagnosis</tt> method.
  * @param iFailsafeMode
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt><dd> Failsafe mode not active: if a failure occurs, an error is thrown.
  *     <dt><tt>TRUE</tt><dd> Failsafe mode active: if a failure occurs, a partial result is returned.</dl>
  */
  virtual void SetFailsafeMode(CATBoolean iFailsafeMode); 

  /**
  * To be used to know if Failsafe mode is active.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt><dd> Failsafe mode is not active.
  *     <dt><tt>TRUE</tt><dd> Failsafe mode is active.</dl>
  */
  virtual CATBoolean GetFailsafeMode();

  /**
  * If Failsafe mode is active, this method allows to retrieve all failure diagnosis after <tt>Run</tt>.
  * Failsafe mode should be activated using <tt>SetFailsafeMode</tt> method before <tt>Run</tt>.
  * @param oFailsafeDiagnosis
  * The list of failure diagnosis stored during the operation.
  * <br> All diagnosis should be destroyed by the caller using <tt>Release</tt>.
  */
  virtual void GetFailsafeDiagnosis(CATLISTP(CATCGMDiagnosis) & oFailsafeDiagnosis);

#endif

#ifdef CATIACGMR419CAA 

  /** @nodoc @nocgmitf Operator Delegation Management */
  virtual int TransferGenericSettingsToDelegateBeforeRun(CATTopOperator &iDelegateOperator);  
  /** 
  * @nodoc @nocgmitf 
  * Operator Delegation Management : ioDelegateJournal might be a concatenated journal different from the one filled by the Delegate Operator
  * The mechanism allows the caller to insert an operation (conversion from exact to poly ...) before the Run and then merge the 2 journals before recording the results
  * If ioDelegateJournal is not valuated to NULL during this call, the caller is still responsible of its life cycle management
  */
  virtual int TransferResultDataFromDelegateAfterRun(CATTopOperator &iDelegateOperator, CATCGMJournalList * &ioDelegateJournal);

#endif


protected:

   /**
   * @nodoc
   * Virtual constructor.<br>
   * Cannot be called. Use the <tt>CATCreateTopX</tt> global functions
   * to create the Xxx operator.
   */
   CATTopOperator(CATGeoFactory*     iFactory, 
                  CATTopData*        iTopData,
                  CATBodyFreezeMode  iBodyFreezeMode=CATBodyFreezeOn,
                  CATExtTopOperator *iExtensible = NULL);
   
   /** @nodoc */
   CATTopOperator(CATGeoFactory     * factory, 
                  CATCGMJournalList * journal=NULL,
                  CATBodyFreezeMode   iBodyFreezeMode=CATBodyFreezeOn,
                  CATExtTopOperator *iExtensible = NULL);


   /** @nodoc  To be or not to be a Topological Operator ...   */
   virtual CATTopOperator* IsTopological();
   
   /** @nodoc : CATCGMReplay  / Controle des donnees d'entree avant execution (Check Body d'Input) */
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);

   /** @nodoc : CATCGMReplay  / Controle de validite des resultats (TopCheckJournal +..) */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  


  /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual void                               WriteTopOutput(CATCGMStream & ioStream);

  /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual CATTopCheckJournal*                ReadTopOutput(CATCGMStream& ioStream);

  /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual void                               DumpTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);

  /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
	virtual CATBoolean                         ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);



   /** @nodoc */
   CATBody*           _Result;
   /** @nodoc */
   void SetResult(CATBody*);
   /** @nodoc */
   void SetJournal(CATCGMJournalList* Journal);
   /** @nodoc */
   virtual CATSoftwareConfiguration* GetConfig();
   /** @nodoc */
   void SetTopData(CATTopData* iTopData);

   /** @nodoc */
   CATTopData CreateTopDataForInner(CATCGMJournalList  *& ioInnerJournal);

  /**  @nodoc */
#ifndef CATTopOperator_no_freezemode
	CATBodyFreezeMode  _freezemode;
#endif

  /** @nodoc CATTopCheckJournal */
  CATTopCheckJournalData* GetTopCheckJournalData(CATBoolean iRequired);

  /** @nodoc  */
  virtual CATCellManifoldsManager* CreateCellManifoldsManager(ListPOfCATBody &iListOfCopyInputBodies, ListPOfCATBody &iListOfNoCopyInputBodies,
    CATBody * iOutputBody, CATCGMJournalList* iTopOpJournal);

  /** @nodoc  */
#if (defined(CATIACGMV5R21) || defined(CATIAR210))
public:
#else
protected:
#endif
  virtual void ReadInputBodies(ListPOfCATBody &oListOfCopyInputBodies, ListPOfCATBody &oListOfNoCopyInputBodies);

protected:
#if (defined(CATIACGMV5R21) || defined(CATIAR210))
  void GetAddedAgents(CATLISTP(CATDeclarativeManifoldAgent) &iAddedAgents);
#endif

#ifdef CATIACGMR215CAA
  virtual void AppendFailsafeDiagnosis(CATCGMDiagnosis * iDiagnosis);
#endif

private:
  
 
  /** @nodoc  forbidden functionnality */
  CATTopOperator(const CATTopOperator&);

  /** @nodoc   forbidden functionnality */
  CATTopOperator& operator=(const CATTopOperator&);

  
  /** @nodoc CATTopCheckJournal */
  void CalculateInputScope();

   /** @nodoc CATTopCheckJournal */
  void CalculateInputScopeLS();
  
  /** @nodoc CATTopCheckJournal */
#ifdef CATIACGMR421CAA
  void CalculateReportOutputScope(CATBoolean iInternalOrStandardCheck, CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);
#else
  void CalculateReportOutputScope(CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);
#endif

  /** @nodoc CATTopCheckJournal */
  void CalculateReportOutputScopeOld(CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);

  /** @nodoc CATTopCheckJournal */
#ifdef CATIACGMR421CAA
  void CalculateReportOutputScopeNew(CATBoolean iInternalOrStandardCheck, CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);
#else
  void CalculateReportOutputScopeNew(CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);
#endif

  
  /** @nodoc CATTopCheckJournal */
  void CalculateReportOutputScopeLS(CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);

#ifdef CATIACGMR421CAA  
  /** @nodoc CATTopCheckJournal */
  //void CalculateReportOutputInternalScope(CATBoolean& iBadGeometryType, CATBoolean& iUnknownCell);
#endif
  
  
  /** @nodoc CATTopCheckJournal */
  void CalculateOutputScope();

   /** @nodoc CATTopCheckJournal */
  void CalculateOutputScopeLS();
   
  void CheckType(CATICGMObject *obj, CATCGMJournal * itm = NULL);
    
#ifdef CATIACGMR421CAA  
  /** @nodoc CATTopCheckJournal */
  int  ObjectIsInInputs(CATICGMObject *obj, CATBoolean iInternalOrStandardCheck = FALSE);
  /** @nodoc CATTopCheckJournal */
  int  ObjectIsInInternalInputs(CATICGMObject *obj);
#else
  int  ObjectIsInInputs(CATICGMObject *obj);
#endif
  
  /** @nodoc CATTopCheckJournal */
#ifdef CATIACGMR421CAA  
  int  ObjectIsInOutPut(CATICGMObject *obj, CATBoolean iInternalOrStandardCheck = FALSE);
  int  ObjectIsInInternalOutPut(CATICGMObject *obj);
#else
  int  ObjectIsInOutPut(CATICGMObject *obj);
#endif

  /** @nodoc CATTopCheckJournal */
  void ThrowError(const char * errmess, CATCGMJournal * itm = NULL);

  /** @nodoc CATTopCheckJournal */
#ifdef CATIACGMR421CAA  
  void FillScope(CATBody * iBody, CATLISTP(CATICGMObject) & iScope,CATLISTP(CATICGMObject) & iInternalScope);
#else
  void FillScope(CATBody * iBody, CATLISTP(CATICGMObject) & iScope);
#endif

  /** @nodoc CATTopCheckJournal LIVE SHAPE */
  void FillScopeLS(CATBody * iBody, CATLISTP(CATICGMObject) & iScope);
  
  /** @nodoc CATTopCheckJournal */
  void FillCells(CATBody * iBody, CATLISTP(CATCell) & iCells);
  
  /** @nodoc CATTopCheckJournal */
  void DumpBodyCells(CATBody * iBody, CATCGMOutput & os, const char * message = NULL);

  
  /** @nodoc mkodtimpact */
  CATSoftwareConfiguration* MustDisappearOldDeprecatedConfiguration() const;
#ifdef CATIACGMR217CAA
  /** @nodoc */
  virtual void CopyTopOperatorDataPreRunFrom (CATCGMOperator const *  iSource);
  /** @nodoc */
  virtual void CopyTopOperatorDataPostRunFrom (CATCGMOperator const *  iSource);
 /** @nodoc */
  virtual void CopyTopMultiResultDataPreRunFrom (CATCGMOperator const *  iSource);
 /** @nodoc */
  virtual void CopyTopMultiResultDataPostRunFrom (CATCGMOperator const *  iSource);
#endif

  /** @nodoc */
  CATBoolean _EmptyInputJournal;

#ifdef CATIACGMV5R20

private:

  /** @nodoc */
  CATBoolean _EnableCellTracker;

#endif 

private:
  CATLISTP(CATDeclarativeManifoldAgent)* _AddedAgents;


  /** @nodoc */
  friend class CATExtTopOperator;
};


/** @nodoc  */
inline CATExtTopOperator *CATTopOperator::GetTopExtensible(CATBoolean iRequired) const
{
  return (CATExtTopOperator *) (void *) ((_Extensible || !iRequired) ? _Extensible  : RequireExtensible() );
}

/** @nodoc @nocgmitf CATCGMReplay  */
// iTopOperator will delete iCGMODTScaleManager at destructor call
extern "C" ExportedByCATTopologicalObjects
void SetCGMODTScaleManager(CATTopOperator* iTopOperator,
                           CATCGMODTScaleManager* iCGMODTScaleManager) ; 

#endif
