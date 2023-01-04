#ifndef CATICGMThickPlus_h_
#define CATICGMThickPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATTopData.h"
#include "CATMathDef.h"
#include "ListPOfCATFace.h"
#include "CATCGMJournal.h"

class CATBody;
class CATBorderDerivationCleanerOpe;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATCGMOutput;
class CATContextForFastRun;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATICGMTopOperator;
class CATRegul;
class CATICGMThick;
class CATThickPlusContextForFastRun;
class CATTopOpInError;
class CATlsoProgressBarManager;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMThickPlus;

/**
* Operator to blow or shrink the faces of a volume.
* Each face may have its own offset value. The offset values
* may be negative: the body is shrunk.
* This operator can also be used to offset a shell. In this case, it is recommended to use the
* SetSharpBorderMode API with the optimization parameter.
* As all the topological operators, the input objects are not modified. The resulting body is
* a new one to retrieve by using the <tt> CATICGMThickPlus::GetResult</tt> method.
* To use it:
* <ul>
* <li>Create it with the <tt> CATICGMCreateThickPlus </tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
* <li>Run it
* <li>Get the result in body with the <tt>GetResult</tt> method. If you do not want 
* to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
* geometric factory, after the operator deletion.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMThickPlus: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMThickPlus();

  /**
  * Appends a list of faces to offset by a common offset value.
  * @param iFacesToOffset
  * The list of pointers to faces to offset with <tt>iOffsetValue</tt>.
  * @param iOffsetValue
  * The offset value.
  */
  virtual void Append(const CATLISTP(CATFace) &iFacesToOffset, CATLength iOffsetValue) = 0;

  /**
  * Appends a face to offset.
  * @param iFace
  * The pointer to the face to offset with <tt>iOffsetValue</tt>.
  * @param iOffsetValue
  * The offset value.
  */
  virtual void Append(CATFace *iFaceToOffset, CATLength iOffsetValue) = 0;

  /**
  * Defines the default offset value for all the faces of the input body.
  * <br>The <tt>Append</tt> methods can still be used after this method to
  * locally modify the default on some faces.
  * @param iOffsetValue
  * The default offset value.
  */
  virtual void SetDefaultOffsetValue(CATLength iOffsetValue) = 0;

  /**
  * Defines how borders are transformed in the neighborhood of sharp edges.
  * @param iSharpBorderOptimisation
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Optimization not required
  * <dt>1</dt><dd>Optimization required (Skin handled like a Volume)
  * </dl>
  */
  virtual void SetSharpBorderMode(short iSharpBorderOptimisation) = 0;

  /**
  * Deactivates tangent propagation of offset values.
  */
  virtual void SetPropagationOff() = 0;

  /**
  * Runs <tt>this</tt> operator.
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
  * Modifies the type of the journal items created during <tt>this</tt> CATICGMThickPlus operation.
  * @param iTypeForFaceCreation
  * The item type.
  * @param iAdditionalInfo
  * The pointer to an additional information. If <tt>NULL</tt>, no additional information is added.
  */
  virtual void SetJournalTypeForFaceOffset(
    CATCGMJournal ::Type iTypeForFaceCreation,
    CATCGMJournalInfo *iAdditionalInfo = NULL) = 0;

  /**
  * Sets the OffsetMixte options. <br> 
  * <b>Legal Values</b>:<br>
  *	<ul>
  *	<li><tt>iWithRegul</tt>: Activates the regularisation of tricky faces with a regularisation diagnosis <br>
  * <li><tt>iRemoveTrickyOnlyThenRegul</tt> : Default value: FALSE.
  * If this option is activated, it changes the behaviour of GetTrickyFaces().
  * If there are non regularisable tricky faces, the method
  * GetTrickyFaces() gives only the non regularisable tricky
  * faces. If there are not non regularisable tricky faces,
  * then GetTrickyFaces gives regularisable tricky faces that
  * fail.<br>
  *	</ul>
  * <b>NOTE</b>: iRemoveTrickyOnlyThenRegul should be activated just if you use
  * CATICGMThickPlus in iterative mode with remove faces.
  *
  **/
  virtual void SetOffsetMixte(
    CATBoolean iWithRegul,
    CATBoolean iRemoveTrickyOnlyThenRegul = FALSE) = 0;

  /**
  * Activates/Deactivates local regularisation treatment (which may split faces) to
  * smooth subparts of the non offsetable faces.
  * @param iLocalRegul
  *	<ul>
  *	<li><tt>TRUE</tt>:  Activates local regularisation.
  *	<li><tt>FALSE</tt>: Deactivates local regularisation.
  *	</ul>
  **/
  virtual void SetLocalRegularization(CATBoolean iLocalRegul) = 0;

  /**
  * Sets the deviation allowed by the user. <br> 
  * <b>Legal Values</b>:<br>
  *	<ul>
  *	<li> <tt>iDeviation</tt> : represents the value of the deviation.This
  *	value must be positive.			
  *	</ul>
  * <b>NOTE</b> : If you use this method, the distribution of the tolerances is
  *	determined by the value containing in the file : CATFuzzyOffsetManagerConst.h
  **/
  virtual void SetDeviationAllowed(CATLength iDeviation) = 0;

  /**
  * Sets the deviation mode. <br> 
  * <b>Legal Values</b>:<br>
  *	<ul>
  *	<li> <tt>iWithDeviation</tt>: If it's TRUE, then the regularisator uses the derivation value of the user.
  *	If it's FALSE, then the regularisator does not use the derivation value of the user.			
  *	</ul>
  * <b>NOTE</b> : By default the DeviationMode is false.
  **/
  virtual void SetDeviationMode(CATBoolean iWithDeviation) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMThickPlus(); // -> delete can't be called
};

/**
* Creates an operator to blow or shrink the faces of a volume.
* Each face may have its own offset value. The offset values
* may be negative: the body is shrunk.
* This operator can also be used to offset a shell. 
* @param iTopData
* A pointer to the topological data.
* @param iBody
* The input body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMThickPlus *CATCGMCreateThickPlus(
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATICGMThickPlus_h_ */
