#ifndef CATIPGMThick_h_
#define CATIPGMThick_h_

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
class CATCurve;
class CATEdge;
class CATError;
class CATFace;
class CATGeoFactory;
class CATOpThick;
class CATVertex;
class CATBaseHealing; // Not interfaced for the moment
class CATLISTP(CATEdge);
class CATLISTP(CATFace);
class CATDomain;
class CATMathPoint;
class CATlsoProgressBarManager;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMThick;

/**
 * Class defining the topological operator that offsets a body.
 * <br>The CATIPGMThick operator does not change the dimension of the body: a volume becomes a volume,
 * a skin becomes a skin. It is possible to choose the faces to offset, and the offset values
 * can change from one face to another. The offset specification is propagated on the adjacent faces,
 * if their common edge is smooth. In case of conflict, the last specification is used.
 * <br> The offset values must be consistent with the curvature of the input surface, to avoid
 * twisted geometry.
 *<br>
 * The CATIPGMThick operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the
 * input body is not modified. A new resulting body is created, 
 * sharing as much data as possible with the input body. A CATIPGMThick operator is not streamble.
 * To use it:
 *<ul>
 * <li>Create it with the constructor
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> or <tt>Append</tt> methods.
 * <li>Run it
 * <li>Get the result with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMThick: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMThick();

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
  virtual void SetApproxOffsetMode(short iApproxOffsetMode, short iPostProRequired = 1) = 0;

  /**
  * Defines the tolerance for C1 approximation 
	* @param iTolC1
  * </dl>
  */
  virtual void SetToleranceForApproxC1(double iTolC1) = 0;

  /**
  * Defines the tolerance for C2 approximation 
	* @param iTolC2
  * </dl>
  */
  virtual void SetToleranceForApproxC2(double iTolC2) = 0;

  /**
 * @nodoc
 * Internal use. 
 */
  virtual void SetPropagationOff() = 0;

  /**
 * @nodoc	 
 * Internal use.
 */
  virtual void SetPropagationOn() = 0;


  /**
  * Appends a face to offset in UpTo mode.
  * @param iFace
  * The pointer to the face to offset in direction of <tt>iTargetBody</tt>.
  * @param iTargetBody
  * The pointer to the target body.
  */
  virtual void Append(CATFace *iOffsetFace, CATBody *iTargetBody) = 0;

  /**
 * Defines the state of the resulting body.
 * @param iOnOrOff
 * The state of the resulting body. 
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

  /**
 * @nodoc
 */
  virtual void SetSimplificationMode(short iSimplificationMode) = 0;

  //======================================================================================================
  // SkinExtrapolation only
  // *=*=*=*=*=*=*=*=*=*=*=*
  /**
 * Appends a list of edges to extrapolate.
 * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
 * @param iBoundaryEdges
 * The list of edges to append.
 * @param iExtrapolValue
 * The common extrapolation value for all the edges of the <tt>iBoundaryEdges</tt> list.
 */
  virtual void Append(const CATLISTP(CATEdge) &iBoundaryEdges, CATLength iExtrapolValue) = 0;

  /**
 * Appends an edge to extrapolate.
 * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
 * @param iBoundaryEdge
 * The edge to append.
 * @param iExtrapolValue
 * The extrapolation value for the <tt>iBoundaryEdge</tt> edge.
 */
  virtual void Append(CATEdge *iBoundaryEdge, CATLength iExtrapolValue) = 0;

  /**
 * Selects all the edges of the shell boundary and sets to them a common extrapolation value.
 * @param iExtrapolValue
 * The new current extrapolation value of the already selected edges.
 */
  virtual void SetDefaultExtrapolationValue(CATLength iExtrapolValue) = 0;

  /**
 * Defines the relimitation mode from all boundary extremities in SkinExtrapolation operator.
 * @param iExtremitiesMode
 *<dl>
 *<dt><tt>0</tt></dt><dd> Extrapolate adjacent edges to cut the offset boundary.
 * This mode is used by default at the creation of the operator.
 *<dt><tt>1</tt></dt><dd> Add junction edges in normal direction of boundary extremities
 *</dl>
 */
  virtual void SetExtremitiesMode(int iExtremitiesMode) = 0;

  /**
 * Defines the boundary G0 derivation behaviour in Offset/ThickenOp operator.
 * @param iForceG0Distortion
 *<dl>
 *<dt><tt>0</tt></dt><dd> Natural G0 derivation : each edge of the boundary is offset 
 *                        according to its normal support direction, then junction edges 
 *                        ared added to close the offset boundary when adjacent edges 
 *                        aren't connected to each others anymore after offset.
 * This mode is used by default at the creation of the operator.
 *<dt><tt>1</tt></dt><dd> Force G0 distortion : each edge of the boundary is offset
 *                        according to normal support direction, then a distortion is applied
 *                        to make adjacent edges still connected to each others, 
 *                        without any junction edge.
 *</dl>
 * @param iDistortionOption
 *<dl>
 *<dt><tt> -1 </tt></dt><dd>    MIN : distortion is drived by surface area minimisation,
 *                                    only one boundary edge is modified by vertex.
 *<dt><tt>  0 </tt></dt><dd> MEDIUM : distortion is computed on the 2 adjacent boundary
 *                                    edges around each boundary vertex
 * This mode is used by default at the creation of the operator.
 *<dt><tt> +1 </tt></dt><dd>    MAX : distortion is drived by surface area maximisation,
 *                                    only one boundary edge is modified by vertex.
 *</dl>
 */
  virtual void SetG0DerivationBehaviourOnBoundary(
    int iForceG0Distortion,
    int iDistortionOption = 0) = 0;

  virtual void SetPartialExtrapolationAllowed(short iPartialExtrapolationAllowed) = 0;

  /**
 * @nodoc
 * Mode de reconstruction robuste des bords de skin extrapolee
 */
  virtual void SetApproximateExtrapolationLevel(short iApproximateExtrapolationLevel) = 0;

  /**
 * Defines the specification of relimitation from one boundary extremity.
 * @param iVtxExtremity
 * The vertex extremity of the boundary to offset
 * @param iSpecifiedMode
 *<dl>
 *<dt><tt>0</tt></dt><dd> Extrapolate adjacent edge from iVtxExtremity to cut the offset boundary.
 * This mode is used by default at the creation of the operator.
 *<dt><tt>1</tt></dt><dd> Add junction edges from iVtxExtremity in specified direction.
 *</dl>
 * @param iGuideCurve
 * The Curve which defines the specified direction. 
 * <br> This curve has to be lying on the boundary support to extrapolate.
 * <br> If param iGuideCurve is NULL, the specified direction is normal to the boundary from iVtxExtremity
 */
  virtual void SetExtremitySpecification(
    CATVertex *iVtxExtremity,
    int iSpecifiedMode,
    CATCurve *iGuideCurve = NULL) = 0;

  /**
 * @nodoc
 * Defines whether the result should contain the whole extrapolated surface or only the extrapolated area.
 * @param iKeepOnlyExtrapolatedArea
 *<dl>
 *<dt><tt>0</tt></dt><dd> The whole extrapolated surface is returned.
 * This mode is used by default at the creation of the operator.
 *<dt><tt>1</tt></dt><dd> The result contains the extrapolated area only.
 *</dl>
 */
  virtual void SetKeepOnlyExtrapolatedArea(short iKeepOnlyExtrapolatedArea) = 0;

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

  virtual void GetEdgesToExtrapolAfterPropagation(
    CATLISTP(CATEdge) &oEdgesAfterPropag,
    CATListOfDouble &oValuesAfterPropag) = 0;

  /**
 * Modifies the type of the journal items created during <tt>this</tt> CATIPGMThick operation.
 * @param iTypeForFaceCreation
 * The item type.
 * @param iAdditionalInfo
 * The pointer to an additional information. If <tt>NULL</tt>, no additional information is added.
 */
  virtual void SetJournalTypeForFaceOffset(
    CATCGMJournal::Type iTypeForFaceCreation,
    CATCGMJournalInfo *iAdditionalInfo = NULL) = 0;

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
 * @nodoc
  * Enables or disables deviation checking.
  * @param iWithDeviation
  * <dl>
  * <dt><tt>1</tt><dd> Check if surface deviations are below maximum value.
  * This value can be provided by the user through <tt>SetDeviationAllowed</tt> method.
  * Default value is the factory resolution
  * <dt><tt>0</tt><dd> No deviation checking is performed
  * This mode is used by default at the creation of the operator.
  * </dl>
  **/
  virtual void SetDeviationMode(short iDeviationMode) = 0;

  /**
  * @nodoc
  * Defines the maximum deviation value allowed by the user.
  * @param iDeviation
  * The value of the deviation. This value must be positive.
  */
  virtual void SetDeviationAllowed(CATLength iMaxDeviation) = 0;

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
 * Internal use.
 */
  virtual void SetFinalDimension(short iFinalDimension) = 0;

  /**
 * @nodoc
 * Internal use.
 */
  virtual void SetThickBoundaryMappingRequired(short iThickBoundaryMappingRequired) = 0;

  /**
 * @nodoc
 * Internal use.
 */
  virtual void SetExtrapolationMode(short iExtrapolMode) = 0;

  /**
 * @nodoc
 * Internal use.
 */
  virtual CATBody *GetInitialBody() const = 0;

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
 * @param iFacesToRemove
 * 
 */
  virtual void SetCandidateFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove,
    short iAllOffsetAreNull = 0) = 0;

  /**
 * @nodoc
 * Internal use.
 * 
 */
  virtual void SetKeepBorderEdgeCurves() = 0;

  /**
 * @nodoc
 * @param oTrickyFaces
 * 
 */
  virtual void GetTrickyFaces(
    CATLISTP(CATFace) &oTrickyFaces,
    short iMixRegulDiagForbidden = 0) = 0;

  /**
  * @nodoc
  * Internal use.
  * 
  */
  virtual void GetAllTrickyEdges(CATLISTP(CATEdge) &oAllTrickyEdges) = 0;

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

  // nodoc
  virtual void GetReverseMatterOutputFaces(CATLISTP(CATFace) &oReverseMatterOutputFaces) = 0;

  // nodoc
  virtual void GetNotInverseRazorBladeFaces(CATLISTP(CATFace) &oNotInverseRazorBladeFaces) = 0;

  // nodoc
  virtual void GetInitReverseMatterFaces(CATLISTP(CATFace) &oInitReverseMatterFaces) = 0;

  //Methode d'acces a la liste des Aretes de decrochement (HookingEdge)pour le traitement de la G0 derivation (fkj)
  virtual CATLISTP(CATEdge) &GetHookingEdgesList() = 0;

  // 
  static CATBoolean GetErrorLocation(CATDomain *iDomain, CATMathPoint &oLocation);

  /** @nodoc */
  virtual void SetUpToMode(short iUpToMode) = 0;

  /** @nodoc */
  virtual void SetDiffMode(short iDiffMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMThick(); // -> delete can't be called
};

/**
 * Do not use. 
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMThick *CATPGMCreateThick(CATBody *iBody, CATCGMJournalList *iJournal = NULL);

/**
 * Constructs a CATThick operator.
 * @param iBody
 * The pointer to the body to offset. 
 * @param iTopData
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMThick *CATPGMCreateThick(
  CATTopData *iTopData,
  CATBody *iBody,
  short iExtrapolMode = 0);

#endif /* CATIPGMThick_h_ */
