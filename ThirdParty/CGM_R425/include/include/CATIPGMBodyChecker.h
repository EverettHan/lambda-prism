#ifndef CATIPGMBodyChecker_h_
#define CATIPGMBodyChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
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

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBodyChecker;

//=============================================================================
/**
 * Class defining the operator to check a given body.
 * <br><tt>CATIPGMBodyChecker</tt> follows the global frame of the topological operators.
 * <ul>
 * <li>Create it with the <tt>Create</tt> static function.
 * <li>Run it.
 * <li>Get the result (diagnosis).
 * <li>Remove it with the <tt>Release</tt> method.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMBodyChecker: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBodyChecker();

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
    * <br>One can use this method and then set the check mode to <tt>CATCGMBodyChkModeLightPlus</tt>,
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
  virtual ~CATIPGMBodyChecker(); // -> delete can't be called
};

#endif /* CATIPGMBodyChecker_h_ */
