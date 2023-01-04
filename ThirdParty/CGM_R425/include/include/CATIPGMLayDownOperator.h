#ifndef CATIPGMLayDownOperator_h_
#define CATIPGMLayDownOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCGMJournal.h"
#include "CATLayDownOperatorDef.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATDomain;
class CATGeoFactory;
class CATIPGMHybOperator;
class CATShell;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLayDownOperator;

/**
* Class defining the operator that projects a body onto another one referred to as the support and returns a solution
* only if the distance is lower than the factory resolution. If the body to be projected
* is lying on the support, the operator returns the input body (the body to be projeceted).
* The body to be projected and the support body (on which the projection is made) can contain 
* several domains.
* <br><b>Orientation</b>:(In case of the projection of a wire on a shell).
* The orientation of two points on the resulting wire is the same as
* the orientation of the points from which they are projected.
* <br><b>Journal</b>: 
*<ul>
* <li>Edges are written as <tt>CATCGMJournal::Creation</tt> from their corresponding
* edge (in the body to be projected project) and face (on the body support).
* <li>The first and last vertices are written as  <tt>CATCGMJournal::Creation</tt>.
* </ul>
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATLayDown is created with the <tt>CATCreateTopLaydown</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopLayDown
*/
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMLayDownOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMLayDownOperator();

  /** 
	* @nodoc 
	* Sets the type of journal items 
	* (CATCGMJournal::Creation or CATCGMJournal::Modification)
	* default is Creation
	*/
  virtual void SetJournalType(CATCGMJournal::Type ) = 0;

  /**  
	* Runs the operator.
	*/
  virtual int Run() = 0;

  /**  
	* Returns the projected body or the initial body.
	* @return
    * The result Body.
	*/
  virtual CATBody *GetResult() = 0;

  // ======================================================
  // NOT CAA
  // ======================================================
  /** @nodoc
	* Get diagnostic after running operator.
	* @return
    * LayDown operation diagnostic.
	* <br><b>Legal values</b>:
    * <dl><dt><tt>NoLayDown</tt> <dd> 
    *     <dt><tt>BodyIsLyingOn</tt> <dd>
	*     <dt><tt>BodyHasBeenLaidDown</tt> <dd>
	*     <dt><tt>BodyPartiallyLaid</tt> <dd></dl>
	*/
  virtual CATLayDownDiagnostic GetDiagnostic() = 0;

  /** @nodoc 
	* Get result analysis after running operator.
	* @return
    * LayDown operation analysis.
	* <br><b>Legal values</b>:
    * <dl><dt><tt>EmptyResult</tt> <dd> The Result Body is empty: Diagnostic is NoLayDown.
    *     <dt><tt>AlreadyLyingOn</tt> <dd> The Input Body is already LyingOn: Diagnosis is BodyIsLyingOn.
	*     <dt><tt>AfterComputationResultIsLayDown</tt> <dd> The Result Body is correctly Layed Down: Diagnostic is BodyHasBeenLaidDown.
	*     <dt><tt>TooMuchResultDomain</tt> <dd> The Result Body has more domains than Input Body: Diagnostic is BodyPartiallyLaid.
	*     <dt><tt>NotEnoughResultDomain</tt> <dd> The Result Body has less domains than Input Body: Diagnostic is BodyPartiallyLaid.
	*     <dt><tt>DifferentExtremity</tt> <dd> The Extremities of Result Body are different from Input Body: Diagnostic is BodyPartiallyLaid.
	*     <dt><tt>DifferentExtremityRelimitation</tt> <dd>idem DifferentExtremity and the reason is Relimitation. </dl>
	*/
  virtual CATLayDownAnalysis GetAnalysis() = 0;

  /** @nodoc
	* Change default tolerance for operation.
	* To be called before running operator.
	* @param iTol
    * The tolerance value to set.
	*/
  virtual void SetTolerance(double iTol) = 0;

  /** @nodoc
	* Get current tolerance for operation.
	* @return
    * Value of tolerance for operator.
	*/
  virtual double GetTolerance() const = 0;

  /** @nodoc
	* Set simplification mode.
	* To be called before running operator.
	* @param iMode
	* Simplification mode.
	* <br><b>Legal values</b>:
    * <dl><dt><tt>FALSE</tt> <dd> No wire simplification on Result (default value).
    *     <dt><tt>TRUE</tt> <dd> Apply wire simplification on Result.
    *</dl>
	*/
  virtual void SetSimplificationMode(CATBoolean iMode) = 0;

  /** @nodoc
	* Get simplification mode.
	* @return
    * Simplication mode.
	* <br><b>Legal values</b>:
    * <dl><dt><tt>FALSE</tt> <dd> No wire simplification on Result.
    *     <dt><tt>TRUE</tt> <dd> Apply wire simplification on Result.
    *</dl>
	*/
  virtual CATBoolean GetSimplificationMode() const = 0;

#ifdef CATIACGMR417CAA
    /** @nodoc
	* Remove cusp and other artefacts from the result.
	* @param iRemoveArtefacts
    * 0 to keep artefacts, 1 to remove them.
	*/
  virtual void SetRemoveArtefacts(int iRemoveArtefacts) = 0;
#endif
#ifdef CATIACGMR418CAA
  /** @nodoc */
  virtual void SetCheckReport(int i_yes_or_no) = 0;

  /** @nodoc */
  virtual int GetCheckReport() = 0;

  /** @nodoc */
  virtual void SetSuppressFlattenDomainMode(CATBoolean sfdm) = 0;

  /** @nodoc */
  virtual CATBoolean GetSuppressFlattenDomainMode() = 0;
#endif
  /** @nodoc */
  virtual void ActivateOldJournal() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLayDownOperator(); // -> delete can't be called
};

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMLayDownOperator *CATPGMCreateLayDownOperator(
  CATGeoFactory *iFactory,
  CATBody *iBodyWireOrVertex,
  CATBody *iBodyShellOrWire,
  CATCGMJournalList *iReport = NULL);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMLayDownOperator *CATPGMCreateLayDownOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyWireOrVertex,
  CATBody *iBodyShellOrWire);

#endif /* CATIPGMLayDownOperator_h_ */
