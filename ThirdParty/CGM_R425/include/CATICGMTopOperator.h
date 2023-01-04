#ifndef CATICGMTopOperator_h_
#define CATICGMTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"
#include "CATBodyFreezeMode.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATTopCheckJournalType.h"
#include "CATGeometryType.h"
#include "CATIACGMLevel.h"
//#ifdef CATIACGMR215CAA
#include "CATListPOfCATCGMDiagnoses.h"
//#endif 

class CATBody;
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMStream;
class CATError;
//class CATExtTopOperator;
class CATGeometry;
class CATICGMUnknown;
class CATSoftwareConfiguration;
class CATTopCheckJournalData;
class CATLISTP(CATICGMObject);
class CATCGMCellTracker;
 
extern ExportedByCATGMModelInterfaces IID IID_CATICGMTopOperator;

/**
* Abstract class for the topological operators.
* <br>
* The topological operators follow the use frame of all operator and satisfy to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input ones. They are not streamable.
* To use a topological operator:
* <ul>
* <li>Create it with the <tt>CATCGMCreateTopXxx</tt> global methods
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
* <li>Run it
* <li>Get the result with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul> 
*/
class ExportedByCATGMModelInterfaces CATICGMTopOperator: public CATICGMOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMTopOperator();

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
	* Returns a pointer to the topological journal associated with <tt>this</tt> CATICGMTopOperator.
	* <br>Only available if a journal was given at the operator creation.
	* @return
	* The pointer to the journal of the operation.
	*/
	virtual CATCGMJournalList *GetJournal() = 0;

	/**
	* Returns the input objects used by <tt>this</tt> CATICGMTopOperator to create its journal.
	* @param oSucceeded
	* This returned value tells whether <tt>this</tt> CATICGMTopOperator
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

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMTopOperator(); // -> delete can't be called
};

#endif /* CATICGMTopOperator_h_ */
