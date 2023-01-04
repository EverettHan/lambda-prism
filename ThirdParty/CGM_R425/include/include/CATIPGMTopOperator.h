#ifndef CATIPGMTopOperator_h_
#define CATIPGMTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATBodyFreezeMode.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATTopCheckJournalType.h"
#include "CATGeometryType.h"
#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R22
#include "CATCGMVoBResult.h"
#endif 
#ifdef CATIACGMR215CAA
#include "CATListPOfCATCGMDiagnoses.h"
#endif 

class CATBody;
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMODTScaleManager;
class CATCGMStream;
class CATPGMCellManifoldsManager;
class CATContextForFastRun;
class CATError;
class CATExtTopOperator;
class CATGeometry;
class CATICGMUnknown;
class CATSoftwareConfiguration;
class CATTopCheckJournalData;
class CATTopData;
class CATTopOpInError;
class CATCGMDiagnosis;
class CATLISTP(CATBody);
class CATLISTP(CATGeometry);
class CATLISTP(CATICGMObject);
class CATCGMCellTracker;
class CATDeclarativeManifoldAgent;
#ifdef CATIACGMV5R22
struct CATCGMVoBTool;
struct CATCGMVoBResult;
#endif 
#ifdef CATIACGMR215CAA
class CATPGMDRepBehavior;
#endif

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopOperator;

/**
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
   *<li>Release the operator with the <tt>Release</tt> method after use.
   *</ul> 
   */
class ExportedByCATGMModelInterfaces CATIPGMTopOperator: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopOperator();

  /**
 	* Returns a pointer to the resulting body.
	* The body is frozen and completed if <tt>CATBodyFreezeOn</tt> is active (default mode).
	* @return
	* The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
	*/
  virtual CATBody *GetResult() = 0;

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
  virtual CATBody *GetResult(CATCGMJournalList *iJournal) = 0;

  /**
	 * Defines the state of the resulting body.
	 * @param iOnOrOff
	 * The state of the resulting body. 
	 */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

  /**
	 * Returns the mode in which the resulting body is created.
	 * @return
	 * The smart mode.
	 */
  virtual CATBodyFreezeMode GetFreezeMode() const = 0;

  /**
   * Returns a pointer to the topological journal associated with <tt>this</tt> CATIPGMTopOperator.
   * <br>Only available if a journal was given at the operator creation.
   * @return
   * The pointer to the journal of the operation.
   */
  virtual CATCGMJournalList *GetJournal() = 0;

  /**
   * Returns the input objects used by <tt>this</tt> CATIPGMTopOperator to create its journal.
   * @param oSucceeded
   * This returned value tells whether <tt>this</tt> CATIPGMTopOperator
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
  virtual void GetInputObjectsForJournal(
    CATBoolean &oSucceeded,
    CATLISTP(CATICGMObject) &oObjects,
    CATTopCheckJournalType iCopy_Or_Not = CATTopCheckCopy,
    CATGeometricType iTypeOfObjects = CATBodyType) = 0;

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
   * @nodoc
   */
  virtual CATBoolean HasConsistentResult(
    CATLONG32 &nberr,
    CATError **&Diagnostic) const = 0;

  /** @nodoc */
  virtual void GetTopData(CATTopData &oTopData) const = 0;

  /** 
   * @nodoc
   * Defines the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @param iConfig
   * The Software configuration.
   */
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig) = 0;

  /** 
   * @nodoc
   * Returns the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @return
   * The Software configuration.
   */
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /** @nodoc */
  virtual CATTopOpInError *GetWarning() = 0;

  /** @nodoc */
  virtual void AppendWarning(CATCGMDiagnosis *iWarning) = 0;

  /** @nodoc */
  virtual void RemoveAllWarning() = 0;

  /** @nodoc CATIPGMTopCheckJournal : returns null value only if no error detected,   */
  virtual int BasicCheckJournal(int iLevelOfCheck = 10, CATCGMOutput *iForceDump = NULL) = 0;

  /**
   * @nodoc
   */
  virtual CATBoolean GivesBodyAsResult() const = 0;

  /**
   * @nodoc
   */
  virtual CATBoolean GivesValidJournalAsResult(
    CATCGMJournalList **ioDuplicatedButExpectedValid) const = 0;

  /** @nodoc  */
  virtual CATExtTopOperator *GetTopExtensible(CATBoolean iRequired = TRUE) const = 0;

  /** 
  *  @nodoc 
  *  Warning: This API is not stable and is only used for debug.
  *  NOT TO BE USED IN CAA APPLICATIONS
  */
  static int CleanNewerUnused(CATICGMUnknown *ipBodyOrFactory);

  /** @nodoc : debug objets + bodies implicites */
  static int CleanAnyNewerUnused(CATICGMUnknown *ipBodyOrFactory);

  /** @nodoc  */
  virtual void CreateManifolds(
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *iOutputBody,
    CATCGMJournalList *iTopOpJournal,
    CATCGMJournalList *ioManifoldBasedJournal = NULL) = 0;

  /** @nodoc */
  virtual HRESULT AppendDeclarativeManifoldAgent(CATDeclarativeManifoldAgent *&ioAgent) = 0;

  /** @nodoc */
  virtual CATBody *GetLiveResult() = 0;

  /** @nodoc */
  virtual CATBody *GetLiveResult(CATCGMJournalList *ioManifoldBasedJournal) = 0;

  /**
   * @nodoc
   * @return [out, CATBaseUnknown#Release]
  */
  virtual CATContextForFastRun *GetContextForFastRun(CATBoolean iGetOnly = FALSE) = 0;

  /** 
   * @nodoc
   *  Enable the cell tracking
   * @param iEnable
   * value used to enable or disable the cell tracking. 
   * Default value: TRUE (Enable)  
   */
  virtual void EnableCellTracker(CATBoolean iEnable = TRUE) = 0;

  /** 
   * @nodoc
   *  Returns the current status of Cell Tracker Activation
   * @return
   * return TRUE if enable otherwise FALSE
   */
  virtual CATBoolean IsCellTrackerEnable() = 0;

  /** 
   * @nodoc
   *  Must be called after Run() 
   *  Create a cell tracker service 
   * @return
   * A pointer on the created cell tracker
   * You must delete the cell tracker after usage
   */
  virtual CATCGMCellTracker *CreateCellTracker() = 0;

#ifdef CATIACGMV5R22
/**
   * @nodoc
 */
  virtual void SetVoBTool(CATCGMVoBTool * iTool)=0;

/**
   * @nodoc
 * @param iFailureResults : list of failure containing the check and the failing operand(s)
 * @param iBlock : 
 * @param iCompletion : True if ended else false (useful when background option is activated)
 */
  virtual void GetVoBResults(
    CATLISTP(CATCGMVoBResult) &iFailureResults,
    CATBoolean iBlock,
    CATBoolean &iCompletion) = 0;
#endif

#ifdef CATIACGMR215CAA
/**
  *  @nodoc 
  *  SetDRepBehavior defines the behavior of the lifivication and of the journal.
  *  @param iDRepBehavior : Use CATDeclarativeContext and CATDeclarativeApplication to create this object. 
  *  NOT TO BE USED IN CAA APPLICATIONS
  */
  virtual void SetDRepBehavior (CATPGMDRepBehavior *iDRepBehavior)=0;

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
  virtual void SetFailsafeMode(CATBoolean iFailsafeMode)=0; 

  /**
  * To be used to know if Failsafe mode is active.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt><dd> Failsafe mode is not active.
  *     <dt><tt>TRUE</tt><dd> Failsafe mode is active.</dl>
  */
  virtual CATBoolean GetFailsafeMode()=0;

  /**
  * If Failsafe mode is active, this method allows to retrieve all failure diagnosis after <tt>Run</tt>.
  * Failsafe mode should be activated using <tt>SetFailsafeMode</tt> method before <tt>Run</tt>.
  * @param oFailsafeDiagnosis
  * The list of failure diagnosis stored during the operation.
  * <br> All diagnosis should be destroyed by the caller using <tt>Release</tt>.
  */
  virtual void GetFailsafeDiagnosis(
    CATLISTP(CATCGMDiagnosis) &oFailsafeDiagnosis) = 0;

#endif

#if (defined(CATIACGMV5R21) || defined(CATIAR210))
  virtual void ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopOperator_h_ */
