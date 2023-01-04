#ifndef CATICGMShellOperatorPlus_h_
#define CATICGMShellOperatorPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATMathDef.h"

class CATBody;
class CATCGMJournalItem;
class CATCGMJournalList;
class CATFace;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMShellOperatorPlus;

/**
* Interface representing the topological operator of shell.
* A shell operation is available on bodies containing volumes: it corresponds to
* two thickness operations on the body, with two different
* offset values, followed by a subtraction between
* the results of the thickness operations.
* As all the topological operators, the input objects are not modified. The resulting body is
* a new one, that you can get by using the <tt>CATICGMShellOperatorPlus::GetResult</tt> method.
* To use it:
* <ul>
* <li>Create it with the <tt>CATCGMCreateShellOperatorPlus</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
* <li>Run it
* <li>Get the resulting GetResult method. If you do not want
* to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the
* geometric factory, after the operator deletion.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMShellOperatorPlus: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMShellOperatorPlus();

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

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMShellOperatorPlus(); // -> delete can't be called
};


/**
* Creates a topological operator that creates a cavity from a body while keeping a given thickness on its sides. 
* The shelling operation may also consist in adding thickness to the outside. 
* @param iBody
* The input body.
* @param iTopData
* A pointer to the topological data.
* @param iInternalOffsetValue
* The value of the internal offset (negative if the volume of the resulting cavity is smaller that the 
* initial volume).
* @param iExternalOffsetValue
* The value of the external offset.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMShellOperatorPlus *CATCGMCreateShellOperatorPlus(
  CATBody *iBody,
  CATTopData *iTopData,
  CATLength iInternalOffsetValue,
  CATLength iExternalOffsetValue);

#endif /* CATICGMShellOperatorPlus_h_ */
