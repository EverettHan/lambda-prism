#ifndef CATIPGMRegul_h_
#define CATIPGMRegul_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

#include "ListPOfCATFace.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATRegulImp;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMRegul;

/**
* Operator to smooth the faces of a volume.
*/
/**
* Operator to smooth the faces of a volume.
* As all the topological operators, the input objects are not modified. The resulting body is
* a new one to retrieve by using the <tt> CATIPGMRegul::GetResult</tt> method.
* To use it:
* <ul>
* <li>Create it with the <tt> CATCreateRegulOperator </tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
* <li>Run it
* <li>Get the result in body with the <tt>GetResult</tt> method. If you do not want 
* to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
* geometric factory, after the operator deletion.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMRegul : public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMRegul();

  /**
  * Set the deviation allowed by the user. <br> 
  * @param iDeviation
  * <b>Legal Values</b>:<br>
  *	<ul>
  *		<li> <tt>iDeviation</tt> : represents the value of the deviation.This
  *								value must be positive.<br>				
  *	</ul>
  *	
  */
  virtual void SetDeviationAllowed(CATLength iDeviation) = 0;
  
  /**
  * Set the DEFAULT offset value (if offset value is the same for all faces). <br> 
  * @param iOffsetValue
  * <b>Legal Values</b>:<br>
  *	<ul>
  *		<li> <tt>iOffsetValue</tt> : the default offset value.<br>
  *	</ul>
  */
  virtual void SetDefaultOffsetValue(CATLength iOffsetValue) = 0;

  /**
  * Activate/Desactivate local regularization treatment (which may split faces) to
  * smooth subparts of the non offsetable faces.
  * @param iLocalRegul
  *	<ul>
  *	<li><tt>TRUE</tt>:  Activates local regularisation.
  *	<li><tt>FALSE</tt>: Deactivates local regularisation.
  *	</ul>
  */
  virtual void SetLocalRegularization(CATBoolean iActivate=TRUE) = 0;

  /**
  * Set the mode of diagnosis to auto compute and run operator.
  * @param iDiagnosisMode
  *	<ul>
  *	<li><tt>0</tt>: no diagnosis (default).
  *	<li><tt>1</tt>: diagnosis for local curvature problem mode (non offsetable).
  *	<li><tt>2</tt>: diagnosis for twisted surface problem mode.
  *	<li><tt>4</tt>: diagnosis for peaked surface mode.
  *	<li><tt>8</tt>: diagnosis for parallel TuTv surface mode.
  *	</ul>
  */
  virtual void SetSelfDiagnosisMode(int iDiagnosisMode=0) = 0;

  /**
  * Set the level of operator computing.
  * @param iLevelOfCompute
  *	<ul>
  *	<li><tt>0</tt>: default.
  *	<li><tt>1</tt>: auto compute all diagnosis and stop.
  *	<li><tt>1</tt>: auto compute all diagnosis and run.
  *	</ul>
  */
  virtual void SetLevelOfCompute(int iLevelOfCompute=0) = 0;

  /**
  * @nodoc
  * @param ipFace
  * @param iDiag
  * @param iOffsetValue
  */
  virtual int SetProblemFace(CATFace * ipFace, int iDiag, double iOffsetValue = 0.) = 0;

  /**
  * Set the level of operator for warning mode.
  * @param iLevelOfWarning
  *	<ul>
  *	<li><tt>0</tt>: default.
  *	<li><tt>1</tt>: warning for smoothed faces ok.
  *	</ul>
  */
  virtual void SetLevelOfWarning(int iLevelOfWarning = 0) = 0;

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
  virtual CATBody * GetResult() = 0;

  /**
  * In case of error, returns the faces that cannot be smoothed. <br>
  * @param oTrickyFaces
  */
  virtual CATBoolean GetRegulTrickyFaces(CATLISTP(CATFace) & oRegulTrickyFaces) = 0;

  /**
  * In case of error, returns the faces that cannot be smoothed. <br>
  * @param oTrickyFaces
  * @param oListDiag
  * @param oListDiagResult
  */
  virtual CATBoolean GetRegulTrickyFaces(
    CATLISTP(CATFace) &oRegulTrickyFaces,
                                         CATListOfInt &oListDiag,
                                         CATListOfInt &oListDiagResult) = 0;

  /**
  * In case of SetLevelOfCompute(1) returns the faces with assciated diagnosis. <br>
  * @param oListFaces
  * @param oListDiags
  */
  virtual int GetFacesWithDiagnosis(
                                    CATLISTP(CATFace) &oListFaces,
                                    CATListOfInt      & oListDiags) = 0;

  /**
  * returns the faces no offsetable that disappear with offset. <br>
  * @param oListNoOffetableToDisappearFaces
  */
  virtual CATBoolean GetNoOffsetableToDisappearFaces(
    CATLISTP(CATFace) &oListNoOffetableToDisappearFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRegul(); // -> delete can't be called
};

// ------------------------
// CATCreateRegulOperator
// ------------------------
/** 
 * Global function for the creation of a CATIPGMRegul operator.
 * @param iFactory
 * The pointer to the factory of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iTopData</tt> 
 * @param iInputBody
 * The pointer to the input body.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMRegul *CATPGMCreateRegulOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

ExportedByCATGMOperatorsInterfaces CATIPGMRegul *CATPGMCreateRegul(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

#endif /* CATIPGMRegul_h_ */
