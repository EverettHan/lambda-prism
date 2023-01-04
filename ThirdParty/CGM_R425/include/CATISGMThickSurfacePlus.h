#ifndef CATISGMThickSurfacePlus_h_
#define CATISGMThickSurfacePlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATSGMOperatorsInterfaces.h"
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

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMThickSurfacePlus;

/**
	* Class defining the operator to thicken a body in two opposite directions
	* according to the offsets specified for the thickening operation.
	* <br>
	* <ul>
	* <li>A CATISGMThickSurfacePlus operator is created with the 
	* <tt>CATSGMCreateThickSurface</tt> global function:
	* It must be directly deleted with the usual C++ <tt>delete</tt> operator after use.
	* It is not streamable. 
	*<li>Options must be specified with the appropriate methods, before
	* asking for the computation with the <tt>Run</tt> method. 
	*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
	* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
	* geometric factory.
	*</ul>
 */
class ExportedByCATSGMOperatorsInterfaces CATISGMThickSurfacePlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATISGMThickSurfacePlus();

  // Append special Offset Values on faces.
  virtual void Append(CATFace *iFace, double iOffset1, double iOffset2) = 0;

  /**
  * @nodoc
  * @param oTrickyFaces
  * @param iOffsetIndex (0/1)
  * 
  */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  // Retour de la liste exhaustive des faces posant probleme, 
  // accompagnee de la liste parallele de diagnostics
  virtual void GetAllTrickyFaces(
    CATLISTP(CATFace) &ioAllTrickyFaces,
    CATListOfInt &ioAllDiag) = 0;

  // active l'option de regularisaion. valeur par defaut : FALSE
  virtual void SetOffsetMixte(CATBoolean iWithRegul) = 0;

  /**
  * Activate/Desactivate local regularization treatment (which may split faces) to
  smooth subparts of the non offsetable faces
  Note: this option has no effect if Regularization isn't activated
  **/
  virtual void SetLocalRegularization(CATBoolean iLocalRegul) = 0;

  // pour donner une deviation User. valeur par defaut : 0.
  virtual void SetDeviationAllowed(CATLength iDeviation) = 0;

  // pour activer le mode regularisation manuelle (avec deviation). valeur par defaut : FALSE
  virtual void SetDeviationMode(CATBoolean iWithDeviation) = 0;

  // pour activer le mode epaisseur constante. valeur par defaut : TRUE
  virtual void SetConstantThickness(CATBoolean iConstantThickness = TRUE) = 0;

  /**
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

  // iG1HealingMode = TRUE or FALSE.
  virtual void SetG1HealingMode(CATBoolean iG1HealingMode) = 0;

  // iG1HealingTolerance if iG1HealingMode is TRUE.
  virtual void SetG1HealingTolerance(double iG1HealingTolerance) = 0;

  // Execution de l'operation ThickSurface OneStepVolume  (RunOperator ne doit servir qu'en mode
  // CGMReplay)
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
  virtual ~CATISGMThickSurfacePlus(); // -> delete can't be called
};

/**
  * @nodoc
* Virtual constructor of a CATISGMThickSurfacePlus operator.<br>
* Cannot be called. Use the <tt>CATSGMCreateThickSurface</tt> global function
* to create a CATISGMThickSurfacePlus operator.
* @return [out,IUnknown#Release]
*/
ExportedByCATSGMOperatorsInterfaces CATISGMThickSurfacePlus *CATSGMCreateThickSurfacePlus(
  CATTopData *iTopData,
  CATBody *iBodyToThick,
  double iOffset_1,
  double iOffset_2);

#endif /* CATISGMThickSurfacePlus_h_ */
