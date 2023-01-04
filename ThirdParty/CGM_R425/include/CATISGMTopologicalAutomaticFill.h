#ifndef CATISGMTopologicalAutomaticFill_h_
#define CATISGMTopologicalAutomaticFill_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATSGMOperatorsInterfaces.h"
#include "CATIPGMTopologicalFill.h"
#include "CATTopologicalFillType.h"

class CATBody;
class CATCGMJournalList;
class CATCldPolygon;
class CATGeoFactory;
class CATShell;

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMTopologicalAutomaticFill;

/**
* Class defining the topological operator that fills in a space defined by a set of wires.
* <br> The wires must define a closed area and be connected.
* Continuity criteria can be precised: G0, G1 if the supporting surfaces of the wire
* are given, G0 otherwise. The supporting surfaces must be coherent to allow the operator to
* compute a G1 continuity.
* If the given continuity constraints are not compatible, the fill result could not
* not satisfy the continuity contraints. 
* If the given continuity constraints define a too scattered set of normals, the shape of
* fill result could not be correct.It is also possible to have no result.  
* <br>The CATISGMTopologicalAutomaticFill operator creates the resulting filling skin body
* separately from the inputs: the wires of the input bodies are not used to define the topology
* of the resulting fill body.  
*<ul>
* <li>A CATISGMTopologicalAutomaticFill operator is created with the <tt>CATPGMCreateTopologicalAutomaticFill</tt> global function.
* It must be directly released with the <tt>Release</tt> method. It is is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* <li>The journal corresponding to the filling operation is not yet implemented.
*</ul>
*/
//-----------------------------------------------------------------------------
class ExportedByCATSGMOperatorsInterfaces CATISGMTopologicalAutomaticFill: public CATIPGMTopologicalFill
{
public:
  /**
  * Constructor
  */
  CATISGMTopologicalAutomaticFill();

  /** 
  * Sets one inner wire. An inner wire is an inner boundary of the fill result. 
  * To set N inner wires, the method AddInnerWires must be called N times. 
  * @Param iListOfWires
  * The list of pointers to wire bodies representing the inner wire.
  * @Param iListOfSupports
  * The list of pointers to shell bodies representing the supports associated with the wire bodies.
  * if a  wire  body has no support, the corresponding element of <tt> iListOfSupports</tt> must be
  * set to <tt> NULL</tt>.  
  * @Param iListOfInnerTransitionContinuity
  * The list of the continuity criteria associated with the wires bodies.
  * The continuity criteria
  * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity.
  */
  virtual void AddInnerWires(
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports,
    CATListOfInt &iListOfInnerTransitionContinuity) = 0;

  /** 
  * Sets a list of passing curves. The resulting fill surface must pass by the passing curves,
  * but the passing curves do not belong to the resulting topology. In particular a passing curve
  * is not a boundary of the fill surface.  
  * @Param iListOfWires
  * The list of bodies (wires) representing the passing curves.
  */
  virtual void SetPassingCurves(CATLISTP(CATBody) const &iListOfWires) = 0;

  /** 
  * Sets a passing curve. The resulting fill surface must pass by this passing curve.
  * but the passing curve does not belong to the resulting topology. In particular a passing curve
  * is not a boundary of the fill surface.  
  * @Param iWire
  * The body wire representing the passing curve.
  * @Param iTolerance
  * The Tolerance corresponding to iWire. If iTolerance =0.0 default 
  * tolerance 0.001 is taken into account.
  */
  virtual void AddPassingCurve(CATBody *iWire, double iTolerance = 0.0) = 0;

  /** 
  * Sets a list of passing points. The fill result must pass through this points.   
  * @Param iListOfVertices  
  * The list  of pointers to vertex bodies representing the passing points.  
  */
  virtual void SetPassingPoints(CATLISTP(CATBody) const &iListOfVertices) = 0;

  /** 
  * Sets a passing point. The fill result must pass through this point.   
  * @Param iVertex  
  * The pointer to vertex body representing the passing point. 
  * @Param iTolerance
  * The Tolerance corresponding to iVertex. If iTolerance =0.0 default 
  * tolerance 0.001 is taken into account.
  */
  virtual void AddPassingPoint(CATBody *iVertex, double iTolerance = 0.0) = 0;

  /**
  * Defines the continuity criteria to take into account for a given wire (<tt>ADVANCED mode</tt>).
  * @param iWhichWire
  * The rank (beginning at 1) of the input wire.
  * @param iTransitionContinuity
  * The continuity criteria
  * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity.
  */
  virtual void SetTransitionContinuity(
    const CATLONG32 iWhichWire,
    const CATLONG32 iTransitionContinuity) = 0;

  /**
  * Defines the orientation of the fill face 
  * The fill face is oriented according to the orientation of the first
  * edge in the first wire. 
  */
  virtual void OrientationByFirstEdge() = 0;

  /**
  * Activates the flat face mode.
  * @param iMode
  * The flat mode.
  * <br><b>Legal values</b>: 
  * <dl><dt>1</dt><dd> to activate the flat face mode: in this case, it creates a planar face if the hole
  * to fill is flat.
  * <dt>0</dt><dd> to deactivate the flat face mode.
  *</dl>
  */
  virtual void SetFlatFaceMode(const CATLONG32 iMode = 1) = 0;

  /**
  * @nodoc
  * @param iTolerance
  * the required maximum  tolerance on the result surface with iTolerance<=0.1 
  */
  virtual void SetGapTolerance(const double iTolerance) = 0;

  /**
  * Specifies the parameters of the filling surface.
  * @param iDegreeU 
  * The maximum required degree in U of the resulting surface. 
  * If iDegreeU is greater than 11, the maximum degree in U will be 11. 
  * If iDegreeU is lower than 4, the degree in U of the result surface can be greater than the required
  * degree except when:
  * <ul>
  * <li>the type of the resulting surface is analytic and the contour to fill in has four curves. 
  * <li>the type of the resulting surface is powerfill and the result surface is a plane. 
  * </ul>
  * @param  iDegreeV 
  * The maximum required degree in V of the resulting surface. 
  * If iDegreeV is greater than 11, the maximum degree in V will be 11. 
  * If iDegreeV is lower than 4, the degree in V of the resulting surface can be greater than the required
  * degree except when: 
  * <ul>
  * <li>the type of the resulting surface is analytic and the contour to fill in has four curves. 
  * <li>the type of the resulting surface is powerfill and the result surface is a plane. 
  * </ul>
  **/
  virtual void SetSurfaceParameters(
    int iDegreeU,
    int iDegreeV,
    int iNumberUOfPatch,
    int iNumberVOfPatch) = 0;

  /**
  * @nodoc
  * Not yet implemented.
  * Defines whether the computed topology must be linked to the inputs (<tt>ADVANCED mode</tt>).
  * @param iLevel
  * The option value.
  * <br><b>Legal values</b>: 
  * <dl><dt><tt>0</tt></dt><dd> if the computed topology is not linked to the input bodies. This
  * is the default value. 
  * <dt><tt>1</tt></dt><dd> if the computed topology is linked to the input bodies, and the smart
  * mechanism applies. 
  * </dl>
  */
  virtual void SetLinkedTopology(const CATLONG32 iLevel) = 0;

  /**  
  *  @nodoc 
  *  <dl>
  *  <dt>If the type of filling is analytic: </dt> 
  *  <dd>defines the center point inside the hole to fill (<tt>ADVANCED  mode</tt>).  
  *  <br>The filling algorithm fills in the hole with four sided faces. In case of not four sided input holes,  
  *  this method defines a center point allowing the algorithm to create four sided faces.</dd> 
  *  <dt>Otherwise: </dt>
  *  <dd>Defines a passing point for the filling surface.</dd> 
  *  </dl>
  *  @param iCenterPoint  
  *  The vertex representing the center point.  
  */   
  virtual void SetCenterPoint(CATVertex &iCenterPoint) = 0;

  /**

  * Only available if the type of fill is analytic 
  * Lets the algorithm define the default center point.
  */
  virtual void ResetCenterPoint() = 0;

  /**
  *@nodoc
  * Checks whether holes must be detected in the input wires (<tt>ADVANCED mode</tt>).
  * Only available if the type of fill is analytic 
  * @param iMode
  * The validation mode.
  * <br><b>Legal values</b>: <tt>1</tt> to check the inputs, <tt>0</tt> for no check (default mode).
  */
  virtual void SetInputValidationMode(const CATLONG32 iMode = 1) = 0;

  /**
  * @nodoc
  * Only available if the type of fill is analytic 
  * Set the Simplify option. Only available in FreeStyle.
  * Default value is TRUE, i.e. the operator will never try
  * to simplify the geometry in input.
  */
  virtual void SetSimplifyOption(CATBoolean iSimplify = TRUE) = 0;

  /**
  * @nodoc
  * Only available if the type of fill is analytic 
  */
  virtual void SetTangencyParameter(
    const CATLONG32 iside,
    const double iTangencyParameter) = 0;

  /**
  * @nodoc
  * This method allows SmartGeometryTreatment. If two consecutives input edges have same Geometry
  * corresponding Fill result edges have also same Geometry
  */
  virtual void SetSmartGeometryTreatment() = 0;

  /**
  * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
  * @return 
  * <ul>
  * <li><tt>0</tt>: no problem occurs   
  * <li><tt>-1</tt>: no result because option powerplane and initial surface not plane (only for fillet use)
  * <li><tt>-2</tt>: no result because it is impossible to find an initial surface because the set of normals defined by the tangency constraints is too scattered
  * <li><tt>-3</tt>: G2 constraints are not loaded because  the set of normals defined by the tangency constraints is too scattered
  * <li><tt>-4</tt>: G2 constraints are not loaded because of G0G0 G0G1 or G1G1 incompatibilities 
  * <li><tt>-10</tt>: The Fill result is the result of Topological Healing 
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8001</tt>: the point is too close from the wire 
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8002</tt>: a too small curve in the wire 
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8003</tt>: the wire is  degenerated
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8007</tt>: self intersections detected in the inputs 
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8008</tt>: self intersections created by the fill  
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8009</tt>: the hole between two consecutive curves is greater than the lenght of the curve
  * <li><tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8012</tt>: the point outside of the wire to fill. 
  * </ul>
  */
  virtual int Run() = 0;

  /**
  * Returns the result of <tt>this</tt> operator.
  * @return
  * The pointer to the created body. You must remove it with the @href CATICGMContainer#Remove 
  * method if you do not want to keep it. Note: in case of multiple <tt>Run</tt>s, the operator
  * deletes the intermediate bodies.
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Returns the fill type.
  * @return
  * <dl>
  * <dt>analytic :</dt>
  * <dd>The edges of the domain to fill in are isoparametric curves of the final surfaces. The number
  * of generated faces is depending on the number of wires.
  *	Use it for simple domain to fill, as rectangular area.
  * <br>Useful in automatic mode to know which solution was chosen.</dd>
  * <dt>powerfill</dt>
  * <dd>The area is filled with a single surface. This allows you to manage wires which describe 
  * a complex topology.</dd>
  * </dl>
  */
  virtual CATTopologicalFillType GetFillType() = 0;

  /**
  * Returns the maximum continuity gap on the result. 
  * @return
  * The maximum continuity gap.
  */
  virtual double GetG0MaxDeviation() = 0;

  /**
  * Returns the maximum  tangency gap (in radians) on the result.
  * @return
  * The maximum tangency gap.
  */
  virtual CATAngle GetG1MaxDeviation() = 0;

  /**
  * @nodoc
  * Returns the maximum curvature gap on the result.
  * @return
  * The maximum curvature gap.
  */
  virtual double GetG2MaxDeviation() = 0;

  /**
  * @nodoc
  * Returns the maximum continuity gap with respect to a particular edge.
  * @param iEdge
  * The edge which is used as a reference for the curvature.
  * @param ioMaxPoint
  * If not null, the coordinates of the point where the 
  * maximum continuity is obtained.
  * @return
  * The maximum continuity gap.
  */
  virtual double GetG0MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
  * @nodoc
  * Returns the maximum tangency gap with respect to a particular edge.
  * @param iEdge
  * The edge which is used as a reference for the curvature.
  * @param ioMaxPoint
  * If not null, the coordinates of the point where the 
  * maximum tangency is obtained.
  * @return
  * The maximum tangency gap.
  */
  virtual CATAngle GetG1MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
  * @nodoc
  * Returns the maximum curvature gap with respect to a particular edge.
  * @param iEdge
  * The edge which is used as a reference for the curvature.
  * @param ioMaxPoint
  * If not null, the coordinates of the point where the 
  * maximum curvature is obtained.
  * @return
  * The maximum curvature gap.
  */
  virtual double GetG2MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
  * Returns  the maximum admissible continuity gap on the result.
  * This value is computed by taking into account some incompatibilities in the input model 
  * Hence, it can be larger than the factory resolution.
  */
  virtual double GetG0MaxAccuracy() = 0;

  /**
  * Returns the maximum admissible tangency gap (in radians)on the result.
  * This value is computed by taking into account some incompatibilities in the model.
  * It is not available in case of AnalyticFill 
  */
  virtual double GetG1MaxAccuracy() = 0;

  /**
  * @nodoc
  * Checks the computation.
  * @return
  * <tt>0</tt> when the computation completes successfully.
  */
  virtual CATLONG32 Check() = 0;

  /**
  * @nodoc
  * Retrieves the surface parameters.
  * @param oDegreeU 
  * The degree in U of the result surface. 
  * @param oDegreeV
  * The degree in V of the result surface. 
  * @param oNumberUOfPatch
  * The number of patches in U of the result surface. 
  * @param oNumberVOfPatch
  * The number of patches in V of the result surface. 
  */
  virtual void GetSurfaceParameters(
    int &oDegreeU,
    int &oDegreeV,
    int &oNumberUOfPatch,
    int &oNumberVOfPatch) = 0;

  /** 
  * @nodoc
  *  If  all the wires are lying on the same support ,  this support is used  to compute the filled surface.  
  *  Therefore, if  there is no passing point ,  no  inner curve  and no passing curve, the filled surface  is a piece of this support. 
  */
  virtual void UsingCommonSupport() = 0;

  virtual void SetLayDownRequest(const double iLayDownTolerance) = 0;

  /**
  * @nodoc
  * Simplifies the topological journal by discarding the parents of the created faces.
  */
  virtual void SetJournalTypeForFaceFill() = 0;

  /**
  * @nodoc
  * Only available if the type of filling is analytic. 
  * Not yet implemented.
  * Returns whether the computed topology must be linked to the inputs.
  * @return 
  * The option value.
  * <br><b>Legal values</b>: 
  * <dl><dt><tt>0</tt></dt><dd> if the computed topology is not linked to the input bodies. This
  * is the default value. 
  * <dt><tt>1</tt></dt><dd> if the computed topology is linked to the input bodies, and the smart
  * mechanism applies. 
  * </dl>
  */
  virtual CATLONG32 GetLinkedTopology() const = 0;

  /**
  * @nodoc
  * Only available if the type of filling is analytic. 
  * Returns the center point inside the hole to fill.
  * <br>The fill algorithm fills the hole with four sided faces. In case of not four sided input holes,
  * the algorithm defines a center point allowing it to create four sided faces. This point can also
  * be defined by the <tt>SetCenterPoint</tt> method (<tt>ADVANCED mode</tt>).
  * @param ioCenterPoint
  * The vertex representing the center point.
  */
  virtual void GetCenterPoint(CATVertex &ioCenterPoint) = 0;

  /**
  * @nodoc
  * Only available if the type of filling is analytic.<br>
  * <dl>
  * <dt>TRUE</dt>
  * <dd>there is a center point</dd>
  * <dt>FALSE</dt>
  * <dd>else</dd>.
  * </dl>
  */
  virtual CATBoolean IsCenterPointCreated() const = 0;

protected:
  /**
  * Destructor
  */
  virtual ~CATISGMTopologicalAutomaticFill(); // -> delete can't be called
};

/**
* Creates a topological operator that fills in a closed area defined by a set of wires.
* @param iFactory
* The pointer to the geometry factory.
* @param iData
* A pointer to the topological data.
* @param iListOfWires
* The list of pointers to the wire bodies, each containing only one wire. 
* The wires must define a closed area and be all connected.
* @param iFillType
* Filling type. Legal values are. 
* <dl>
* <dt>CATTopologicalFill::analytic:</dt>
* <dd>The edges of the domain to fill in are isoparametric curves of the final surfaces. The number
* of generated faces is depending on the number of wires.
* Use it for simple domain to fill, as rectangular area.</dd>
* <dt>CATTopologicalFill::powerfill</dt>
* <dd>The area is filled with a single surface. This allows you to manage wires which describe 
* a complex topology.</dd>
* <dt>CATTopologicalFill::autofill_level1</dt>
* <dd>Automatically determines the most suitable method according to the input topology.</dd>
* </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATSGMOperatorsInterfaces CATISGMTopologicalAutomaticFill *CATSGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_autofill_level1);

/**
* Creates a topological operator that fills in a closed area defined by a set of wires.
* @param iFactory
* The pointer to the geometry factory.
* @param iData
* A pointer to the topological data.
* @param iListOfWires
* The list of pointers to the wire bodies, each containing only one wire. 
* The wires must define a closed area and be all connected.
* @param iListOfSupports
* The list of pointers to the supporting bodies of the wires, thus allowing you to define the G1 continuity
* criteria. 
* @param iFillType
* Filling type. Legal values are. 
* <dl>
* <dt>CATTopologicalFill::analytic:</dt>
* <dd>The edges of the domain to fill in are isoparametric curves of the final surfaces. The number
* of generated faces is depending on the number of wires.
* Use it for simple domain to fill, as rectangular area.</dd>
* <dt>CATTopologicalFill::powerfill</dt>
* <dd>The area is filled with a single surface. This allows you to manage wires which describe 
* a complex topology.</dd>
* <dt>CATTopologicalFill::autofill_level1</dt>
* <dd>Automatically determines the most suitable method according to the input topology.</dd>
* </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATSGMOperatorsInterfaces CATISGMTopologicalAutomaticFill *CATSGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  CATLISTP(CATBody) const &iListOfSupports,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_autofill_level1);

#endif /* CATISGMTopologicalAutomaticFill_h_ */
