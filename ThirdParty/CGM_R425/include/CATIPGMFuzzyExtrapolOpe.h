#ifndef CATIPGMFuzzyExtrapolOpe_h_
#define CATIPGMFuzzyExtrapolOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"

class CATBody;
class CATEdge;
class CATFuzzyExtrapolImpl;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATShell;
class CATString;
class CATLISTP(CATVertex);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFuzzyExtrapolOpe;

/**
 * Class representing an operator that extrapolates a shell body with respect to surface curvature.
 * Some border and internal details may be skipped for robustness purpose.
 *<br>The edges to be extrapolated must belong to the boundary of the shell.
 *<br>The extrapolation values can be different for each edge. A positive
 * value defines an extrapolation along the outside direction of the shell.
 *<br>Target bodies can be defined instead of distances.
 *<br>The extrapolation gives a result that is continuous in curvature.
 * To use it:
 * <ul>
 * <li>Create it with the <tt>CATPGMCreateFuzzyExtrapolOpe</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 *<li>Delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMFuzzyExtrapolOpe: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFuzzyExtrapolOpe();

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
  * Appends a target body for a boundary edge
  * so that the boundary will be extrapolated enough to reach the body.
  * Several target bodies can be defined for a same edge.
  * @param iBoundaryEdge
  * The edge to append
  * @param iTargetBody
  * A target body for <tt>iBoundaryEdge</tt>.
  * @param iTargetShell
  * A specific shell of the iTargetBody, NOT IMPLEMENTED YET
  */
  virtual void Append(
    CATEdge *iBoundaryEdge,
    CATBody *iTargetBody,
    CATShell *iTargetShell = NULL) = 0;

  /**
  * Appends a target body for a list of edges
  * so that the boundary will be extrapolated enough to reach the body.
  * Several target bodies can be defined for a same edge.
  * @param iBoundaryEdges
  * The list of edges to append
  * @param iTargetBody
  * A target body for edges from <tt>iBoundaryEdges</tt> list.
  * @param iTargetShell
  * A specific shell of the iTargetBody, NOT IMPLEMENTED YET
  */
  virtual void Append(
    const CATLISTP(CATEdge) &iBoundaryEdges,
    CATBody *iTargetBody,
    CATShell *iTargetShell = NULL) = 0;

  /**
  * Appends a wire to extrapolate.
  * It appends a wire to extrapolate of <tt>iExtrapolValue</tt>.
  * @param iWire
  * The wire body to extrapolate
  * @param iExtrapolValue
  * The extrapolation value for the <tt>iWire</tt> wire.
  */
  virtual void Append(CATBody *iWire, CATLength iExtrapolValue) = 0;

  /**
  * Appends a target body for a wire input
  * so that the boundary will be extrapolated enough to reach the body.
  * Several target bodies can be defined for a same wire.
  * @param iWire
  * The wire body to extrapolate
  * @param iTargetBody
  * A target body for <tt>iWire</tt>.
  * @param iTargetShell
  * A specific shell of the iTargetBody
  */
  virtual void Append(CATBody *iWire, CATBody *iTargetBody, CATShell *iTargetShell = NULL) = 0;

  /**
  * Selects all the edges of the shell boundary and sets to them a common extrapolation value.
  * @param iExtrapolValue
  * The new current extrapolation value for all the edges of the shell boundary.
  * Only for input given as edges
  */
  virtual void SetDefaultExtrapolationValue(CATLength iExtrapolValue) = 0;

  /**
  * Selects all the edges of the shell boundary and add to them a common target Body.
  * @param iTargetBody
  * The new current target body for all the edges of the shell boundary.
  * Only for input given as edges
  */
  virtual void AppendDefault(CATBody *iTargetBody) = 0;

  /**
  * Defines the propagation mode of the extrapolation value.
  * @param iPropagationMode
  * <dl>
  * <dt><tt>0</tt></dt><dd> No propagation of the extrapolation value.
  * <dt><tt>1</tt></dt><dd> Defines the automatic definition of the extrapolation value on an edge
  * to the one of its tangential adjacent edges.
  * This mode is used by default at the creation of the operator.
  * </dl>
  * Only for input given as edges
  */
  virtual void SetPropagationMode(short iPropagationMode) = 0;

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
  * Defines whether holes should be removed from the skin or not
  * @param iRemoveHoles
  * <dl>
  * <dt><tt>0</tt></dt><dd> Holes remain on the skin.
  * This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> Holes are removed from the skin.
  * <dt><tt>2</tt></dt><dd> Remove holes whose boundaries include specified edges to extrapolate.
  * The other holes remain intact.
  *</dl>
  * Only for C2 continuity
  */
  virtual void SetRemoveHoles(short iRemoveHoles) = 0;

  /**
  * Enables or disables twist detection.
  * @param iTwistDetection
  * <dl>
  * <dt><tt>0</tt></dt><dd> Twist detection is disabled : result skin may lie on twisted surfaces.
  * This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> Twist detection is enabled : extrapolation is not possible if a twist is detected.
  * </dl>
  */
  virtual void SetTwistDetection(short iTwistDetection) = 0;

  /**
  * @nodoc
  * Defines whether UpThrough TargetBody option must be activated or not
  * @param iUpThroughBody
  *<dl>
  *<dt><tt>0</tt></dt><dd> Usual Run.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> Extrapol through all target if input laid down on target
  *</dl>
  */
  virtual void SetUpThroughBody(short iUpThroughBody) = 0;

  /**
  * Enables or disables deviation checking.
  * @param iWithDeviation
  * <dl>
  * <dt><tt>1</tt><dd> Check if surface deviations are below maximum value.
  * This value can be provided by the user through <tt>SetDeviationAllowed</tt> method.
  * Default value is the factory resolution
  * <dt><tt>0</tt><dd> No deviation checking is performed
  * This mode is used by default at the creation of the operator.
  * </dl>
  * Only for C2 continuity
  **/
  virtual void SetDeviationMode(short iDeviationMode) = 0;

  /**
  * Defines the maximum deviation value allowed by the user.
  * @param iDeviation
  * The value of the deviation. This value must be positive.
  * Only for C2 continuity
  */
  virtual void SetDeviationAllowed(CATLength iMaxDeviation) = 0;

  /**
  * Enables or disables Tolerance checking.
  * @param itoleranceMode
  * <dl>
  * <dt><tt>1</tt><dd> Check if wire target for extrapol is facing input skin at given tolerance
  * This value can be provided by the user through <tt>SetToleranceAllowed</tt> method.
  * Default value is the factory resolution * 100
  * <dt><tt>0</tt><dd> No tolerance checking is performed under resolution * 100
  * This mode is used by default at the creation of the operator.
  * </dl>
  **/
  virtual void SetToleranceModeForWireTarget(short itoleranceMode) = 0;

  /**
  * Defines the maximum tolerance value to consider that the wire target is facing the input body
  * @param iMaxTolerance
  * The value of the tolerance. This value must be positive.
  * Default Value is 100 * factory resolution. Possible value between 0 and 100 * factory resolution
  */
  virtual void SetToleranceAllowedForWireTarget(CATLength iMaxTolerance) = 0;

  /**
  * Defines the extrapolation behaviour around the extremities of the selected boundaries
  * @param iExtremitiesMode
  * <dl>
  * <dt><tt>0</tt></dt><dd> The extrapolation sides are tangent to the edges adjacent to the surface boundary
  *  This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> The extrapolation sides are normal to the original surface boundary.
  * </dl>
  */
  virtual void SetExtremitiesMode(short iExtremitiesMode) = 0;

  /**
  * Enables or disables skin relimitation along target bodies.
  * @param iTrimmingMode
  *<dl>
  *<dt><tt>0</tt></dt><dd> The skin is extrapolated enough to reach the target bodies but no trimming is performed.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> The extrapolated area is relimited onto the target bodies.
  *<dt><tt>2</tt></dt><dd> The whole extrapolated skin is relimited onto the target bodies.
  *</dl>
  */
  virtual void SetTargetBodiesTrimmingMode(short iTrimmingMode) = 0;

  /** @nodoc
  * Defines the level of approximation allowed for the reconstruction of the surfaces boundaries.
  * The more this level is high, the more boundaries can be approximated and the more robust is the operation.
  * @param iApproximateExtrapolationLevel
  * <dl>
  * <dt><tt>0</tt></dt><dd> The shape of extrapolated boundaries is preserved. Extrapolation distance is respected.
  *  This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> Some edges from the boundary may be merged and extrapolation distance may not be respected.
  * </dl>
  * Only for C2 continuity
  */
  virtual void SetApproximateExtrapolationLevel(short iApproximateExtrapolationLevel) = 0;

  /**
  * Defines the type of continuity for the extrapolation
  * @param iExtremitiesMode
  * <dl>
  * <dt><tt>1</tt></dt><dd> Tangent mode : G1 continuity
  * <dt><tt>2</tt></dt><dd> Curvature mode : C2 continuity
  * </dl>
  */
  virtual void SetContinuityMode(short iContinuityMode) = 0;

  /**
  * @nodoc
  * Specifies one or several internal edges in order to determine a direction for the extrapolation.
  * The edges will be extrapolated in tangency. It is possible to associate a vertex to each edge
  * to give an orientation to extrapolation.
  * @param iEdgesForDirection
  * The Edges to determine direction for extrapolation.
  * @param iVertexOfEdges
  * The Vertex associated to each Edge for orientation. 
  * Only for G1 continuity
  */
  virtual void SetDirectionnalEdge(
    const CATLISTP(CATEdge) &iEdgesForDirection,
    const CATLISTP(CATVertex) &iVertexOfEdges) = 0;

  /** @nodoc */
  virtual void SetPartialExtrapolationAllowed(short iPartialExtrapolationAllowed) = 0;

  /** @nodoc */
  virtual void GetTrickyEdges(CATLISTP(CATEdge) &oTrickyEdges) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFuzzyExtrapolOpe(); // -> delete can't be called
};

// ----------------------
// CATCreateFuzzyExtrapol
// ----------------------
ExportedByCATGMOperatorsInterfaces CATIPGMFuzzyExtrapolOpe *CATPGMCreateFuzzyExtrapolOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iReferenceBody);

#endif /* CATIPGMFuzzyExtrapolOpe_h_ */
