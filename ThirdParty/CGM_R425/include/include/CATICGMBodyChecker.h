#ifndef CATICGMBodyChecker_h_
#define CATICGMBodyChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATCGMBodyCheckerDef.h" // enum...

class CATBody;
class CATGeoFactory;
class CATTopData;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMBodyChecker;

//=============================================================================
/**
* Class defining the operator to check a given body.
* <br><tt>CATICGMBodyChecker</tt> follows the global frame of the topological operators.
* <ul>
* <li>Create it with the <tt>Create</tt> static function.
* <li>Run it.
* <li>Get the result (diagnosis).
* <li>Remove it with the <tt>Remove</tt> static function.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMBodyChecker: public CATICGMTopOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMBodyChecker();

	/**
	* Constructs an operator that checks a body.
	* <br>The body to check can contain several domains. All the cells of relevant type from all domains will
	* be checked for the active body checker rules.
	* @param ipFactory
	* The pointer to the factory of the body to check.
	* @param ipData
	* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>ipData</tt> 
	* is <tt>NULL</tt>, it is not filled. 
	* @param ipBodyToCheck
	* The pointer to the body to check. It can contain several domains.
	* In this case, the operator processes all the cells from all the domains.
	* @return [out, IUnknown#Release]
	* The pointer to the created operator. 
	* To remove the operator from memory, use <tt>Release</tt> method after use.
	*/
	static CATICGMBodyChecker *Create(
		CATGeoFactory *ipFactory,
		CATTopData *ipData,
		CATBody *ipBodyToCheck);

	/**
	* Checks a given body.
	* <br>The body to check can contain several domains. All the cells of relevant type from all domains will
	* be checked for the active body checker rules.
	* @param ipFactory
	* The pointer to the factory of the body to check.
	* @param ipBodyToCheck
	* The pointer to the body to check. It can contain several domains.
	* In this case, the operator processes all the cells from all the domains.
	* @param ioNumberOfSevereAnomalies
	* Total number of severe anomalies found during check operation.
	* @param ioDetailsOfAnomalies
	* The details of severe anomalies found during check operation.
	* @param ibFullCheck
	* CATBoolean(0) indicates that body check operator would run in "Light" check mode.<br>
	* CATBoolean(1) indicates that body check operator would run in "Full" check mode.
	* @return
	* The result of the check operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if no errors were found, <tt>FALSE</tt> otherwise.
	*/
	static CATBoolean Check(
		CATGeoFactory *ipFactory,
		CATBody *ipBodyToCheck,
		CATLONG32 &ioNumberOfSevereAnomalies,
		ostream &ioDetailsOfAnomalies,
		const CATBoolean &ibFullCheck = FALSE);

	// Operator services/specific methods
	/**
	* Runs <tt>this</tt> operator.
	* @return
	* <br><b>Legal values</b>: <tt>1</tt> if ok, <tt>0</tt> if failed.
	*/
	virtual int Run() = 0;

	/**
	* Type of <tt>this</tt> operator.
	* @return
	* <br><b>Legal values</b>:  <tt>>1</tt>.
	*/
	virtual int Type() const = 0;

	// Methods for querying/altering operator behaviour.
	/**
	* Gets the active check mode of the operator.
	* <br>Note that the default check mode of the operator is <tt>Light</tt> mode.
	* @param oCheckMode
	* The active check mode of the operator.
	* @return
	* The result of the operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if succeeded, <tt>FALSE</tt> otherwise.
	*/
	virtual CATBoolean GetCheckMode(CATCGMBodyCheckMode &oCheckMode) = 0;

	/**
	* Sets the new active check mode of the operator.
	* <br>Note that the default check mode of the operator is <tt>Light</tt> mode.
	* @param iCheckMode
	* The new active check mode of the operator to be set.
	* @return
	* The result of the operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if succeeded, <tt>FALSE</tt> otherwise.
	*/
	virtual CATBoolean SetCheckMode(const CATCGMBodyCheckMode &iCheckMode) = 0;

	/**
	* Sets the check rules for the operator.
	* <br>Use this method to restrict the check operation to certain rules of interest.
	* <br>One can use this method and then set the check mode to <tt>CATICGMBodyChecker::BodyChkModeLightPlus</tt>,
	* in which case, the operator checks for rules set by <tt>this</tt> method in addition to <tt>Light</tt> rules.
	* @param iplsCheckRuleIDs
	* The list of check rule IDs of type <tt>CATCGMBodyCheckerRuleID</tt> to be checked.
	* @return
	* The result of the operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if succeeded, <tt>FALSE</tt> otherwise.
	*/
	virtual CATBoolean SetCheckRules(CATListOfInt *&iplsCheckRuleIDs) = 0;

	/**
	* Sets the check cells for the operator.
	* <br>Use this method to restrict the check operation to certain cells of interest.
	* @param ilsCheckCells
	* The list of cells to be used for check (a subset from <tt>ipBodyToCheck</tt>, i.e. body being checked).
	* @return
	* The result of the operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if succeeded, <tt>FALSE</tt> otherwise.
	*/
	virtual CATBoolean SetCheckCells(CATLISTP(CATCell) &ilsCheckCells) = 0;

	// Methods for diagnosis/results analysis/iterators
	/**
	* Gets the number of diagnoses found after the operator run.
	* @return
	* <br>The <b>count</b> of diagnoses found.
	*/
	virtual CATLONG32 GetNbDiagnoses() const = 0;

	/**
	* Initializes the iterator of the resulting diagnosis.
	*<br>By default, the initialization is performed once the operator runs, 
	* and this is therefore only used to read the diagnosis again.
	*/
	virtual void BeginningDiagnosis() = 0;

	/**
	* Skips to the next diagnosis of <tt>this</tt> operator results, if any.
	* <br>After <tt>BeginningDiagnosis</tt>, it skips to the first diagnosis. 
	* @return
	* The existence of the next diagnosis.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>TRUE</tt> <dd>if there is a diagnosis
	*    <dt><tt>FALSE</tt> <dd>if no more diagnosis.</dl>
	*/
	virtual CATBoolean NextDiagnosis() = 0;

	/**
	* Gets the current diagnosis of <tt>this</tt> operator results.
	* @param oDiagnosisString
	* The reference to the string to be filled out with diagnosis details.
	* @return
	* The result of the operation.
	* <br><b>Legal values</b>: <tt>TRUE</tt> if succeeded, <tt>FALSE</tt> otherwise.
	*/
	virtual CATBoolean GetDiagnosis(CATUnicodeString &oDiagnosisString) const = 0;

	/**
	* Gets all the diagnoses of <tt>this</tt> operator results after run.
	* @param ioOutput
	* The details of severe anomalies found during check operation.
	*/
	virtual void Dump(ostream &ioOutput) const = 0;

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMBodyChecker(); // -> delete can't be called
};

#endif /* CATICGMBodyChecker_h_ */
