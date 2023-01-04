#ifndef CATISGMShellOperatorPlus_h_
#define CATISGMShellOperatorPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATSGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"

class CATBody;
class CATCGMJournalItem;
class CATCGMJournalList;
class CATFace;
class CATTopData;
class CAThkShellScenario;
class CATLISTP(CATFace);

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMShellOperatorPlus;
/**
* Class defining an operator to create a cavity from a body while keeping a given thickness on its sides. 
* The shelling operation may also consist in adding thickness to the outside.
* This operator follows the general frame of all operators and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATISGMShellOperatorPlus is created with the CATSGMCreateShellOperatorPlus global function. 
* It must be directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
*/
class ExportedByCATSGMOperatorsInterfaces CATISGMShellOperatorPlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATISGMShellOperatorPlus();


  /**
  * Specifies the list of faces to be removed.
  * @param iOpenFaces
  * The list of faces
  */
  virtual void AppendOpening(const CATLISTP(CATFace) &iOpenFaces) = 0;


  /**
  * Adds a list of faces with offsets different from
  * those specified in the CATSGMCreateShellOperatorPlus function.
  * @param iSpecOffsetFaces
  * The list of faces with different offset values.
  * @param iInternSpecialOffsetValue
  * The internal offset value.It can be negative if the internal volume of the shell is smaller than the 
  * solid initial volume.
  * @param iExternSpecialOffsetValue
  * The external offset value.
  */
  virtual void AppendSpecialOffset(
    const CATLISTP(CATFace) &iSpecOffsetFaces,
    CATLength iInternSpecialOffsetValue,
    CATLength iExternSpecialOffsetValue) = 0;

  /**
  * Runs the operator.
  * @return
  * <dl><dt><tt>0</tt><dd> The operation has completed.
  *     <dt><tt>1</tt><dd> The operation has not completed.</dl>
  */
  virtual int Run() = 0;

  /**
  * Returns the pointer to the resulting body.
  * @return
  * The pointer to the resulting body, <tt>NULL</tt> if the operation failed. 
  * If you do not want to keep the resulting body, 
  * use the @href CATICGMContainer#Remove method to remove it from the 
  * geometric factory, after the operator Release.
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Defines whether propagation of opening faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * <dl><dt><tt>TRUE</tt><dd> The propagation is activated.
  *     <dt><tt>FALSE</tt><dd> The operation is not activated.</dl>
  */
  virtual void SetOpeningFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * Defines whether propagation of special offset faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * </dl>
  */
  virtual void SetSpecialOffsetFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * Defines whether geometrical and topological simplification in post-treatment 
  * should be activated or not. This option is useful to remove edges or faces relying on the
  * same geometry.
  * By default, this mode is disabled.
  * @param iLevel
  * <dl><dt><tt>1</tt><dd> The simplification is activated.
  *     <dt><tt>0</tt><dd> The simplification is not activated.</dl>
  */
  virtual void SetSimplificationLevel(short iLevel) = 0;

  /**
  * Sets the OffsetMixte options. <br> 
  * @param iWithRegul
  * <dl><dt><tt>1</tt><dd> Regularization of "tricky faces" with diagnosis.
  *     <dt><tt>0</tt><dd> No regularization</dl>
  **/
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
  virtual ~CATISGMShellOperatorPlus(); // -> delete can't be called
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
ExportedByCATSGMOperatorsInterfaces CATISGMShellOperatorPlus *CATSGMCreateShellOperatorPlus(
  CATBody *iBody,
  CATTopData *iTopData,
  CATLength iInternalOffsetValue,
  CATLength iExternalOffsetValue);

#endif /* CATISGMShellOperatorPlus_h_ */
