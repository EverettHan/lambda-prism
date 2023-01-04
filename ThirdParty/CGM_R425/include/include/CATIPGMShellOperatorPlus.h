#ifndef CATIPGMShellOperatorPlus_h_
#define CATIPGMShellOperatorPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"

class CATBody;
class CATCGMJournalItem;
class CATCGMJournalList;
class CATFace;
class CATTopData;
class CAThkShellScenario;
class CATShellOperatorPlusContextForFastRun;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMShellOperatorPlus;

/**
* Interface representing the topological operator of shell.
* A shell operation is available on bodies containing volumes: it corresponds to
* two thickness operations on the body, with two different
* offset values, followed by a subtraction between
* the results of the thickness operations.
* As all the topological operators, the input objects are not modified. The resulting body is
* a new one, that you can get by using the <tt>CATIPGMShellOperatorPlus::GetResult</tt> method.
* To use it:
* <ul>
* <li>Create it with the <tt>CATPGMCreateShellOperatorPlus</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
* <li>Run it
* <li>Get the resulting GetResult method. If you do not want
* to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the
* geometric factory, after the operator deletion.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMShellOperatorPlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMShellOperatorPlus();

  /**
  * Specifies the list of faces to be removed.
  * @param iOpenFaces
  * The list of faces
  */
  virtual void AppendOpening(const CATLISTP(CATFace) &iOpenFaces) = 0;

  /**
  * Modifies the offset values for a list of faces of the body to shell.
  * @param iSpecialOffset
  * A list of faces.
  * @param iInternalSpecialOffset
  * The list of the corresponding internal offsets.
  * @param iExternalSpecialOffset
  * The list of the corresponding external offsets.
  */
  virtual void AppendSpecialOffset(
    const CATLISTP(CATFace) &iSpecOffsetFaces,
    CATLength iInternSpecialOffsetValue,
    CATLength iExternSpecialOffsetValue) = 0;

  /**
  * Runs the operator
  */
  virtual int Run() = 0;

  /**
  * Returns the pointer to the resulting body.
  * @return
  * The pointer to the resulting body, <tt>NULL</tt> if the operation failed. 
  * If you do not want to keep the resulting body, 
  * use the @href CATICGMContainer#Remove method to remove it from the 
  * geometric factory, after the operator deletion.
  */
  virtual CATBody *GetResult() = 0;

  /**
 * @nodoc
 * @param iFacesToRemove
 * @param iExternalThick (0/1)
 * 
 */
  virtual void SetMandatoryFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove,
    short iExternalThick) = 0;

  /**
 * @nodoc
 * @param oTrickyFaces
 * @param iExternalThick (0/1)
 * 
 */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces, short iExternalThick) = 0;

  /**
 * @nodoc
 * @param oFacesToIgnore 
 * @param iExternalThick (0/1)
 * 
 */
  virtual void GetFacesToIgnore(CATLISTP(CATFace) &oFacesToIgnore, short iExternalThick) = 0;

  /**
  * @nodoc
  * @param oNotInverseRazorBladeFaces
  * 
  */
  virtual void GetNotInverseRazorBladeFaces(CATLISTP(CATFace) &oNotInverseRazorBladeFaces) = 0;


  /**
  * @nodoc
  * Defines if procedural Offset surfaces must be approximated and
  * replaced by NurbsSurface
	* @param iApproxOffsetMode
	* <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation not required
  * <dt>1</dt><dd>Approximation required in C1 mode
  * <dt>2</dt><dd>Approximation required in C2 mode
  * @param iPostProRequired
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation required during Offset algorithm
  * <dt>1</dt><dd>Approximation required after Offset algorithm
  * </dl>
  */
  virtual void SetApproxOffsetMode(short iApproxOffsetMode, short iPostProRequired = 0) = 0;

  /**
  * @nodoc
  * Defines the tolerance for C1 approximation 
	* @param iTolC1
  * </dl>
  */
  virtual void SetToleranceForApproxC1(double iTolC1) = 0;

  /**
  * @nodoc
  * Defines the tolerance for C2 approximation 
	* @param iTolC2
  * </dl>
  */
  virtual void SetToleranceForApproxC2(double iTolC2) = 0;

  /**
  * @nodoc
  * Defines whether propagation of opening faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * </dl>
  */
  virtual void SetOpeningFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * @nodoc
  * Defines whether propagation of special offset faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * </dl>
  */
  virtual void SetSpecialOffsetFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * @nodoc
  * Defines whether geometrical and topological simplification in post-treatment 
  *   should be activated or not.
  * By default, it is disabled.
  * @param iLevel
  * </dl>
  */
  virtual void SetSimplificationLevel(short iLevel) = 0;

  /**
  * Sets the OffsetMixte options. <br> 
  * @param iWithRegul
  * <dl><dt><tt>1</tt><dd> Regularization of "tricky faces" with diagnosis.
  *     <dt><tt>0</tt><dd> No regularization</dl>
  */
  virtual void SetOffsetMixte(CATBoolean iWithRegul) = 0;

  /**
  * Requires a local smoothing of a face when this face cannot be offsetted as a whole.
  * This option can result in additional faces. It can only be activated when the 
  * SetOffsetMixte method is used to ask for a surface "regularization".
  * @param iLocalRegul
  * <dl><dt><tt>TRUE</tt><dd> The local regularization is activated.
  *     <dt><tt>FALSE</tt><dd> The local regularization is not activated.</dl>
  **/
  virtual void SetLocalRegularization(CATBoolean iLocalRegul) = 0;

  /**
  * Sets the deviation allowed by the user. 
  * @param iDeviation
  * The value of the deviation. This value must be positive.				
  */
  virtual void SetDeviationAllowed(CATLength iDeviation) = 0;

  /**
  * Sets the deviation mode.
  * @param iWithDeviation
  * <dl><dt><tt>TRUE</tt><dd> the regularizator uses the deviation value which is specified by the user.
  *     <dt><tt>FALSE</tt><dd> the regularizator does not use the user value (default value). 
  * </dl>
  **/
  virtual void SetDeviationMode(CATBoolean iWithDeviation) = 0;

  /**
  * Asks for a constant thickness for the resulting shell when one of the offset values is null.
  * Applies only when the regularization is activated (SetOffsetMixte)
  * @param iConstantThickness
  * <dl><dt><tt>TRUE</tt><dd> Default mode: the smoothed/regularized face with null offset is keep in the resulting shell
  *     <dt><tt>FALSE</tt><dd> The input face with null offset is not modified.</dl>
  **/
  virtual void SetConstantThickness(CATBoolean iConstantThickness = TRUE) = 0;

  /**
  * @nodoc
  * Collision reseach mode.
  * @param iCollisionLevel
  *<dl>
  *<dt><tt>0</tt></dt><dd> Local collisions research only (perfos default mode).
  *<dt><tt>1</tt></dt><dd> Global collisions research (costly).
  *</dl>
  */
  virtual void SetCollisionResearch(short iCollisionLevel) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMShellOperatorPlus(); // -> delete can't be called
};

// 0 : faces d'offset nul identiques aux faces input.
// constructeur a partir d'un CATBody et 2 valeurs d'offsets a appliquer
//  par defaut a toutes les faces (aucune face d'ouverture par defaut) 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMShellOperatorPlus *CATPGMCreateShellOperatorPlus(
  CATBody *iBody,
  CATTopData *iTopData,
  CATLength iInternalOffsetValue,
  CATLength iExternalOffsetValue);

#endif /* CATIPGMShellOperatorPlus_h_ */
