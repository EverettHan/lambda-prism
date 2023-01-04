#ifndef CATIPGMThickSurfacePlus_h_
#define CATIPGMThickSurfacePlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATFace;
class CATRegul;
class CATShell;
class CATIPGMThickSurface;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMThickSurfacePlus;

/**
	* Class defining the operator to thicken a body in two opposite directions
	* according to the offsets specified for the thickening operation.
	* <br>
	* <ul>
	* <li>A CATIPGMThickSurfacePlus operator is created with the 
	* <tt>CATPGMCreateThickSurface</tt> global function:
	* It must be released with the <tt>Release</tt> method after use.
	* It is not streamable. 
	*<li>Options must be specified with the appropriate methods, before
	* asking for the computation with the <tt>Run</tt> method. 
	*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
	* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
	* geometric factory.
	*</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMThickSurfacePlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMThickSurfacePlus();

  /**
  * @nodoc
  * Defines specific values for a given face.
  * @param iFace
  * The face whose offsets are different from those specified at the operator creation.
  */
  virtual void Append(CATFace *iFace, double iOffset1, double iOffset2) = 0;

  /**
  * @nodoc 
  * To activate/deactivate tangency propagation for faces with special offset values.
  * If not set, there is no propagation.
  */
  virtual void SetSpecialOffsetFacesPropagation(short iPropagation) = 0;

  /** @nodoc 
  * Returns partial result if complete result cannot be computed
  * when iPartialResultMode = 1.
  * Federation is not taken into account */
  virtual void SetPartialResultMode(short iPartialResultMode) = 0;

  /**
  * @nodoc
  * @param oTrickyFaces
  * @param iOffsetIndex (0/1)
  * 
  */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  /**
  * @nodoc
  * Returns the list of result faces that were smoothed during operation.
  * 
  */
  virtual void GetSmoothedResultFaces(CATLISTP(CATFace) &oSmoothedResultFaces) = 0;

  /**
  * @nodoc
  * Returns the list of faces which cannot be offsetted.
  * @param oTrickyFaces
  * The list of tricky faces.
  * @param iOffsetIndex (0/1)
  * The face indexes.
  * 
  */
  virtual void GetAllTrickyFaces(
    CATLISTP(CATFace) &ioAllTrickyFaces,
    CATListOfInt &ioAllDiag) = 0;

  /**
  * Sets the "mixed offset" options. <br> 
  * @param iWithRegul
  * <dl><dt><tt>1</tt><dd> Regularization of the faces that cannot be offsetted accurately due to their geometry.
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
  */
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
  */
  virtual void SetDeviationMode(CATBoolean iWithDeviation) = 0;

  /**
  * Asks for a constant thickness for the resulting shell when one of the offset values is null.
  * Applies only when the regularization is activated (SetOffsetMixte)
  * @param iConstantThickness
  * <dl><dt><tt>TRUE</tt><dd> Default mode: the smoothed/regularized face with null offset is keep in the resulting shell
  *     <dt><tt>FALSE</tt><dd> The input face with null offset is not modified.</dl>
  */
  virtual void SetConstantThickness(CATBoolean iConstantThickness = TRUE) = 0;

  /**
   * @nodoc
	 * Defines a Boolean operation between a given body and the result of 
	 * <tt>this</tt> operator.
	 * @param iOpType
	 * The boolean operation type.
	 * @param iOperandBody
	 * The pointer to the body representing the first operand of the Boolean operation. 
	 * The second operand is the result of the thicken.
	 * @param iReport
	 * A pointer to the journal corresponding to the Boolean operation. This journal can be different
	 * from the journal of the thicken operation itself. If <tt>NULL</tt>, the Boolean journal
	 * is not written.
	 */
  virtual void SetBooleanOperation(
    CATDynBooleanType iOpType,
    CATBody *iOperandBody,
    CATCGMJournalList *iReport = 0) = 0;

  /**
  * Smoothes lateral ribbon and keeps smooth lateral edges where initial border edges
  * were in smooth contact. Lateral faces are no longer normal to input surface.
  * @param iG1HealingMode
  * <dl><dt><tt>TRUE</tt><dd> activates the G1 healing mode.
  *     <dt><tt>FALSE</tt><dd> deactivates the G1 healing mode (default value). 
  * </dl>
  */
  virtual void SetG1HealingMode(CATBoolean iG1HealingMode) = 0;

  /**
  * Sets a maximum deviation on lateral faces if the smoothing deviation exceeds the
  * input tolerance, then the lateral edges are not smoothed.
  * @param iG1HealingTolerance
  * The healing tolerance. By default, the thickness value.
  */
  virtual void SetG1HealingTolerance(double iG1HealingTolerance) = 0;

  /**
  * Simplifies geometry and topology of lateral ribbon.
  * @param iRibbonSimplification
  * <dl><dt><tt>TRUE</tt><dd> activates the simplification option.
  *     <dt><tt>FALSE</tt><dd> deactivates the simplification option (default value). 
   */
  virtual void SetRibbonSimplification(CATBoolean iRibbonSimplification) = 0;

  /**
  * @nodoc
  * same rules as TrimByThick when iAlignOnTrimByThickBehavior is set to 1
  * (allow unsolved topology...).
  */
  virtual void SetAlignOnTrimByThickBehavior(short iAlignOnTrimByThickBehavior=1) = 0;

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
	 * Returns the body created from the Boolean operation between a given body and the thickened body.
	 * @return
	 * The pointer to the Boolean result.
	 * If you do not want to keep the resulting body, 
     * use the @href CATICGMContainer#Remove method to remove it from the 
     * geometric factory, after the operator deletion.
	 */
  virtual CATBody *GetBooleanResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMThickSurfacePlus(); // -> delete can't be called
};

/**
  * @nodoc
* Virtual constructor of a CATIPGMThickSurfacePlus operator.<br>
* Cannot be called. Use the <tt>CATPGMCreateThickSurface</tt> global function
* to create a CATIPGMThickSurfacePlus operator.
* @return [out,IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMThickSurfacePlus *CATPGMCreateThickSurfacePlus(
  CATTopData *iTopData,
  CATBody *iBodyToThick,
  double iOffset_1,
  double iOffset_2);

#endif /* CATIPGMThickSurfacePlus_h_ */
