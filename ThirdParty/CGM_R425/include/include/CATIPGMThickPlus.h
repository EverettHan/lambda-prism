#ifndef CATIPGMThickPlus_h_
#define CATIPGMThickPlus_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"
#include "CATCGMJournal.h"

class CATBody;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATCGMOutput;
class CATContextForFastRun;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATRegul;
class CATIPGMThick;
class CATICGMTopOperator;
class CATLISTP(CATFace);
class CATThickPlusContextForFastRun;


extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMThickPlus;

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
class ExportedByCATGMOperatorsInterfaces CATIPGMThickPlus: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMThickPlus();

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
    * @nodoc
  * Appends a face to offset in UpTo mode.
  * @param iFace
  * The pointer to the face to offset in direction of <tt>iTargetBody</tt>.
  * @param iTargetBody
  * The pointer to the target body.
  */
  virtual void Append(CATFace *iFace, CATBody *iTargetBody) = 0;

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
  * @nodoc
  * Defines the boundary G0 derivation behaviour in Offset/ThickenOp operator.
  * @param iForceG0Distortion
  * <dl>
  * <dt><tt>0</tt></dt><dd> Natural G0 derivation : each edge of the boundary is offset 
  *                        according to its normal support direction, then junction edges 
  *                        ared added to close the offset boundary when adjacent edges 
  *                        aren't connected to each others anymore after offset.
  * This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> Force G0 distortion : each edge of the boundary is offset
  *                        according to normal support direction, then a distortion is applied
  *                        to make adjacent edges still connected to each others, 
  *                        without any junction edge.
  * </dl>
  * @param iDistortionOption
  * <dl>
  * <dt><tt> -1 </tt></dt><dd>    MIN : distortion is drived by surface area minimisation,
  *                                    only one boundary edge is modified by vertex.
  * <dt><tt>  0 </tt></dt><dd> MEDIUM : distortion is computed on the 2 adjacent boundary
  *                                    edges around each boundary vertex
  * This mode is used by default at the creation of the operator.
  * <dt><tt> +1 </tt></dt><dd>    MAX : distortion is drived by surface area maximisation,
  *                                    only one boundary edge is modified by vertex.
  * </dl>
  */
  virtual void SetG0DerivationBehaviourOnBoundary(
    int iForceG0Distortion,
    int iDistortionOption = 0) = 0;

  /**
  * @nodoc
  * Defines if procedural Offset surfaces must be approximated and
  * replaced by NurbsSurface.
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
  * Defines the tolerance for C1 approximation. 
  * @param iTolC1
  * </dl>
  */
  virtual void SetToleranceForApproxC1(double iTolC1) = 0;

  /**
  * @nodoc
  * Defines the tolerance for C2 approximation.
  * @param iTolC2
  * The tolerance.
  */
  virtual void SetToleranceForApproxC2(double iTolC2) = 0;

  /**
  * Deactivates tangent propagation of offset values.
  */
  virtual void SetPropagationOff() = 0;

  /**
  * @nodoc	 
  * Activates tangent propagation of offset values.
  */
  virtual void SetPropagationOn() = 0;

 /**
 * @nodoc
 */
  virtual void SetUpToMode(short iUpToMode) = 0;

  /** 
  * @nodoc 
  */
  virtual void SetDiffMode(short iDiffMode) = 0;

  /** 
  * @nodoc 
  */
  virtual void SetSimplificationMode(short iSimplifMode) = 0;

  /**
  * @nodoc
  * Defines the state of the resulting body.
  * @param iOnOrOff
  * The state of the resulting body. 
  */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

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
  * Modifies the type of the journal items created during <tt>this</tt> CATIPGMThickPlus operation.
  * @param iTypeForFaceCreation
  * The item type.
  * @param iAdditionalInfo
  * The pointer to an additional information. If <tt>NULL</tt>, no additional information is added.
  */
  virtual void SetJournalTypeForFaceOffset(
    CATCGMJournal ::Type iTypeForFaceCreation,
    CATCGMJournalInfo *iAdditionalInfo = NULL) = 0;

  /**
  * @nodoc
  * Internal use.
  */
  virtual void SetThickBoundaryMappingRequired(short iThickBoundaryMappingRequired) = 0;

  /**
  * @nodoc
  * @param iFacesToRemove
  * 
  */
  virtual void SetMandatoryFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove,
    short iAllOffsetAreNull = 0) = 0;

  /**
  * @nodoc
  * @param oTrickyFaces
  * 
  */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  /**
  * @nodoc
  * @param oFacesToIgnore
  * 
  */
  virtual void GetFacesToIgnore(CATLISTP(CATFace) &oFacesToIgnore) = 0;

  /**
  * @nodoc
  * @param oFacesToRegularise
  * @param oDiag
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Regularisation not required [forbidden output value]
  * <dt>1</dt><dd>Optimization required for local curvature problem
  * <dt>2</dt><dd>Optimization required for singular point
  * <dt>3</dt><dd>Optimization required for extrapolation failure
  * </dl>
  */
  virtual void GetFacesToRegularise(
    CATLISTP(CATFace) &oFacesToRegularise,
    CATListOfInt &oDiag) = 0;

  /**
  * @nodoc
  * @param oNotInverseRazorBladeFaces
  * 
  */
  virtual void GetNotInverseRazorBladeFaces(CATLISTP(CATFace) &oNotInverseRazorBladeFaces) = 0;

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
  * CATIPGMThickPlus in iterative mode with remove faces.
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
  * @nodoc
  * Enables or disables twist detection.
  * @param iTwistDetection
  *<dl>
  *<dt><tt>0</tt></dt><dd> Twist detection is disabled : result body may lie on twisted surfaces.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Twist detection is enabled : twists are not allowed on the result body.
  *</dl>
  */
  virtual void SetTwistDetection(short iTwistDetection) = 0;

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

  /**
  * @nodoc 
  * Sets the partial result mode. <br> 
  * <b>Legal Values</b>:<br>
  *	<ul>
  *	<li> <tt>iPartialResultMode</tt>: If it's equal to 1, then the operator returns the best partial result if full result is not possible.
  *	If it's equal to 0, then the operation returns an error if full result is not possible.			
  *	</ul>
  * <b>NOTE</b> : By default the PartialResultMode is turned to off.
  **/
  virtual void SetPartialResultMode(short iPartialResultMode) = 0;

  //-----------------------------------------------------------------------
  //- Methodes pour Fast Update
  //-----------------------------------------------------------------------  
  /**
  * @nodoc
  * @return [out, CATBaseUnknown#Release]
  */
  virtual CATThickPlusContextForFastRun *GetThickPlusContextForFastRun(
    CATBoolean iGetOnly = FALSE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMThickPlus(); // -> delete can't be called
};

/**
 * Constructs a CATIPGMThickPlus operator.
 * @param iBody
 * The pointer to the body to offset. 
 * @param iTopData
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMThickPlus *CATPGMCreateThickPlus(CATTopData *iTopData, CATBody *iBody);

#endif /* CATIPGMThickPlus_h_ */
