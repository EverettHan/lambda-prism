#ifndef CATIPGMTopologicalAutomaticFill_h_
#define CATIPGMTopologicalAutomaticFill_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopologicalFill.h"
#include "CATTopologicalFillType.h"

class CATBody;
class CATCGMJournalList;
class CATCldPolygon;
class CATGeoFactory;
class CATShell;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalAutomaticFill;

/**
* Class defining the topological operator that fills  a space defined by a set of wires.
* <br> The wires must define a closed area and be connected.
* Continuity criteria can be specified: G0, G1, or G2 if the supporting surfaces of the wire
* are given, G0 otherwise. The supporting surfaces must be coherent to allow the operator to
* compute a G1 or G2 continuity.
* If the given continuity constraints are not compatible, the fill result could not
* not satisfy the continuity contraints. 
* If the given continuity constraints define a too scattered set of normals, the shape of
* fill result may not be correct.It is also possible to have no result.  
* 
* <br>The CATIPGMTopologicalAutomaticFill operator creates the resulting filling skin body
* separately from the inputs: the wires of the input bodies are not used to define the topology
* of the resulting fill body.  
*<ul>
* <li>A CATIPGMTopologicalAutomaticFill operator is created with the <tt>CATPGMCreateTopologicalAutomaticFill</tt> global function.
* It must be directly released with the <tt>Release</tt> method. It is is not streamable. 
*<li>Options can be specified with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* <li>The journal corresponding to the fill operation is not yet implemented.
*</ul>
*/
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalAutomaticFill: public CATIPGMTopologicalFill
{
public:
  /**
   * Constructor
   */
  CATIPGMTopologicalAutomaticFill();

  //=============
  //  Set Methods  
  //=============
  /** 
   * Sets one inner wire. An inner wire is an inner boundary of the fill result. 
   * To set N inner wires,the method AddInnerWires must be called N times. 
   * @param iListOfWires
   * The list of pointers to wire bodies representing the inner wire.
   * @param iListOfSupports
   * The list of pointers to shell bodies representing the supports associated with the wire bodies.
   * If a  wire  body has no support, the corresponding element of <tt> iListOfSupports</tt> must be
   * set to <tt> NULL</tt>.  
   * @param iListOfInnerTransitionContinuity
   * The list of the continuity criteria associated with the wire bodies.
   * The continuity criteria
   * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity,
   * or <tt>2</tt> for G2 continuity.
   */
  virtual void AddInnerWires(
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports,
    CATListOfInt &iListOfInnerTransitionContinuity) = 0;

  /** 
   * Sets a list of passing curves. The resulting fill surface must pass by the passing curves,
   * but the passing curves do not belong to the resulting topology. In particular, a passing curve
   * is not a boundary of the fill surface.  
   * @param iListOfWires
   * The list of bodies (wires) representing the passing curves.
  */
  virtual void SetPassingCurves(CATLISTP(CATBody) const &iListOfWires) = 0;

  /** 
   * @nodoc
   * Sets a  passing curve. The resulting fill surface must pass by this passing curve.
   * but the passing curve does not belong to the resulting topology. In particular a passing curve
   * is not a boundary of the fill surface.  
   * @param iWire
   * The body wire  representing the passing curve.
   * @param iTolerance
   * The Tolerance corresponding to iWire. If iTolerance =0.0 default 
   * tolerance 0.001 is taken into account.
  */
  virtual void AddPassingCurve(CATBody *iWire, double iTolerance = 0.0) = 0;

  /** 
   * Sets a list of passing points. The fill result must pass through these points.   
   * @param iListOfVertices  
   * The list  of pointers to vertex bodies representing the passing points.  
   */
  virtual void SetPassingPoints(CATLISTP(CATBody) const &iListOfVertices) = 0;

  /** 
   * @nodoc
   * Sets a  passing point. The fill result must pass through this point.   
   * @param iVertex  
   * The pointer to vertex body representing the passing point. 
   * @param iTolerance
   * The Tolerance corresponding to iVertex. If iTolerance = 0.0, the default 
   * tolerance 0.001 is used.
   */
  virtual void AddPassingPoint(CATBody *iVertex, double iTolerance = 0.0) = 0;

  /**
	 * Defines the continuity criterion to use for a given wire.
	 * @param iWhichWire
	 * The index (beginning at 1) of the input wire.
	 * @param iTransitionContinuity
	 * The continuity criterion.
	 * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity,
	 * or <tt>2</tt> for G2 continuity.
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
 * In this mode, a planar face is created if the hole being filled is flat.
 * @param iMode
 * The flat mode.
 * <br><b>Legal values</b>: 
 * <dl><dt>1</dt><dd> to activate the flat face mode.
 * <dt>0</dt><dd> to deactivate the flat face mode.
 *</dl>
 */
  virtual void SetFlatFaceMode(const CATLONG32 iMode = 1) = 0;

  /**
  *@nodoc
  * @param  iTolerance
  * the required maximum  tolerance on the result surface with iTolerance<=0.1 
  */
  virtual void SetGapTolerance(const double iTolerance) = 0;

  /**
  * @nodoc
  *@param  iDegreeU 
  * the maximum required degree in U of the result surface. 
  * if iDegreeU is greater than 11, the maximum degree in U of the result surface is 11. 
  * if iDegreeU is lower than 4, the degree in U of the result surface can be greater than the required
  * degree except in the following  configurations: 
  * " the type of the result surface is analytic and the contour to fill has four curves". 
  * " the type of the result surface is powerfill and the  result surface is a plane". 
  *@param  iDegreeV 
  * the maximum required degree in V of the result surface. 
  * if iDegreeV is greater than 11, the maximum degree in V of the result surface is 11. 
  * if iDegreeV is lower than 4, the degree in V of the result surface can be greater than the required
  * degree except in the following  configurations: 
  * " the type of the result surface is analytic and the contour to fill has four curves". 
  * " the type of the result surface is powerfill and the  result surface is a plane". 
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
   * @nodoc
   * Sets a list of cutting wires
   * In a first time, if the list iListOfWires has more than one element the method returns 1;
   * 
  */
  virtual int SetCuttingWires(CATLISTP(CATBody) const &iListOfWires) = 0;

  /**
	 * @nodoc
	 * if the type of fill is analytic: 
	 * Defines the center point inside the hole to fill (<tt>ADVANCED mode</tt>).
	 * <br>The fill algorithm fills the hole with four sided faces. In case of not four sided input holes,
	 * this method defines a center point allowing the algorithm to create four sided faces. 
	 * otherwise Defines a passing point for the fill surface 
	 * @param iCenterPoint
	 * The vertex representing the center point.
	 */
  virtual void SetCenterPoint(CATVertex &iCenterPoint) = 0;

  /**
	 * @nodoc
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
   */
  virtual void SetBody(CATBody *ioBody, CATShell *ioShell) = 0;

  /**
   * @nodoc
   * Possibility to create or not merged curves between the boundaries of the wire to fill
   * and the boundaries of fill surface.
   * If the type of the fill is powerfill, the merged curves are created by default.
   * If CreateMergedCurve = FALSE, a simcurve is created from the pcurves of the fill surface. 
   * If the type of the fill is analytic, the merged curves are not created. 
   */
  virtual void SetCreateMergedCurves(const CATBoolean iCreateMergedCurve = TRUE) = 0;

  /**
     * Enables the replacement of the fill surface by a canonical surface when
	 * it is detected that this is valid.
	 * This method is effective only over rectangular regions, and supports
	 * replacement by cylinders, spheres, and cones only.
	 * This method is only active if the type of fill result is analytic.
	 * This method is inactive if the type of fill result is powerfill. 
	 * In this case the resulting surface is always a NURBS surface. 
   */
  virtual void SetCanonicalDetection() = 0;

  /**
   * @nodoc
	 * This method allows SmartGeometryTreatment. If two consecutives input edges have same Geometry
	 * corresponding Fill result edges have also same Geometry
   */
  virtual void SetSmartGeometryTreatment() = 0;

  //=============
  //  Run  Method  
  //=============
  /**
  * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
  * @return 
  *<tt>0</tt> no problem occurs,    
  *<tt>-1</tt>no result because option powerplane and initial surface not plane (only for fillet use ), 
  *<tt>-2</tt>no result because it is impossible to find an initial surface because the set of normals defined by the tangency constraints is too scattered,
  *<tt>-3</tt> G2 constraints are not loaded because  the set of normals defined by the tangency constraints is too scattered,
  *<tt>-4</tt> G2 constraints are not loaded because of G0G0 G0G1 or G1G1 incompatibilities, 
  *<tt>-10</tt> The Fill result is the result of Topological Healing, 
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8001</tt> the point is too close from the wire, 
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8002</tt> a too small curve in the wire, 
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8003</tt> the wire is  degenerated , 
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8007</tt> self intersections detected in the inputs, 
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8008</tt> self intersections created by the fill,  
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8009</tt> the hole between two consecutive curves is greater than the lenght of the curve,
  *<tt>CATTopOpInError SurfacicTopOpInFillInvalidWire_ERR_8012</tt> the point outside of the wire to fill. 
  */
  virtual int Run() = 0;

  //=============
  //  Get Methods  
  //=============
  /**
  * @nodoc
  * Returns the result of <tt>this</tt> operator.
  * @return
  * The pointer to the created body. You must delete it with the @href CATICGMContainer#Remove 
  * method if you do not want to keep it. Note: in case of multiple <tt>Run</tt>s, the operator
  * deletes the intermediate bodies.
  */
  virtual CATBody *GetResult() = 0;

  /**
 * Returns the maximum continuity gap in the result. 
 */
  virtual double GetG0MaxDeviation() = 0;

  /**
 * Returns the maximum tangency gap (in radians) in the result.
 */
  virtual CATAngle GetG1MaxDeviation() = 0;

  /**
 * Returns the maximum curvature gap in the result.
 */
  virtual double GetG2MaxDeviation() = 0;

  /**
* Returns the maximum continuity gap with regard to a particular edge. 
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual double GetG0MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum tangency gap (in radians) with regard to a particular edge.
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual CATAngle GetG1MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum curvature gap with regard to a particular edge.
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual double GetG2MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum admissible continuity gap in the result.
* This value is computed by taking into account some incompatibilities in the input model.
* Hence, it can be larger than the factory resolution.
*/
  virtual double GetG0MaxAccuracy() = 0;

  /**
* Returns the maximum admissible tangency gap (in radians) in the result.
* This value is computed by taking into account some incompatibilities in the  model.
* It is not available in case of AnalyticFill.
*/
  virtual double GetG1MaxAccuracy() = 0;

  /**
   * @nodoc
   * Checks the computation.
   * @return
   * <tt>0</tt> if the computation occured without problem.
   */
  virtual CATLONG32 Check() = 0;

  /**
  *@nodoc
  *@param  oDegreeU 
  * the degree in  U of the result surface 
  * @param oDegreeV
  * the  degree in  V of the result surface 
  *@param  oNumberUOfPatch
  *the number of patches in  U of the result surface 
  *@param  oNumberVOfPatch
  * the  number of patches in V of the result surface 
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

  /** @nodoc */
  virtual void SetGeometricOptimumInitialSurface(CATCldPolygon *icld = 0) = 0;

  /** @nodoc */
  virtual void SetSmoothOption(const double iSmoothDeviation) = 0;

  /**
  * Asks for a lay down of each input wire on the corresponding support.
  * If this method is not called, the wire is presumed to be already laid down on its support.
  * @param iLayDownTolerance
  * The pointer to the lay down tolerance (maximum distance between wire to be laid down
  * and its support surface).
  */
  virtual void SetLayDownRequest(const double iLayDownTolerance) = 0;

  /**
   * @nodoc
  *  To symplify topological journal
  *  in the journal the face fill is created without parents  
  */
  virtual void SetJournalTypeForFaceFill() = 0;

  /**
   * @nodoc
   * Only available if the type of fill is analytic 
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
	 * Only available if the type of fill is analytic 
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
	 * Only available if the type of fill is analytic 
     * TRUE -> there is a center point
     * FALSE -> else.
	 */
  virtual CATBoolean IsCenterPointCreated() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopologicalAutomaticFill(); // -> delete can't be called
};

/**
 * Creates a topological operator that fills a closed area defined by a set of wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iListOfWires
 * The list of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must define a closed area and be connected. 
 * @param iFillType
 * Type of the fill to compute. iFillType can have three values. 
 * CATTopologicalFillType_analytic:
 * The edges of the domain to fill are isoparametric  curves of the final surfaces. The number
 * of generated faces is depending on the number of wires.
 * Use it for simple domain to fill, as rectangular area.
 * CATTopologicalFillType_powerfill
 * The area is filled with a single surface. This allows you to manage wires which describe 
 * a complex topology.
 * CATTopologicalFillType_autofill_level1 
 * Automatically determines the most suitable method according to the input topology.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
 * @see CATIPGMTopologicalFill
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_analytic);

/**
 * Creates a topological operator that fills a closed area defined by a set of wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iListOfWires
 * The list of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must define a closed area and be connected.
 * @param iListOfSupports
 * The list of pointers to the supporting bodies of the wires, thus allowing you to define G1 or G2 continuity
 * criteria. 
 * @param iFillType
 * Type of the fill to compute. iFillType can have three values. 
 * CATTopologicalFillType_analytic:
 * The edges of the domain to fill are isoparametric  curves of the final surfaces. The number
 * of generated faces is depending on the number of wires.
 * Use it for simple domain to fill, as rectangular area.
 * CATTopologicalFillType_powerfill
 * The area is filled with a single surface. This allows you to manage wires which describe 
 * a complex topology.
 * CATTopologicalFillType_autofill_level1 
 * Automatically determines the most suitable method according to the input topology.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  CATLISTP(CATBody) const &iListOfSupports,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_analytic);

// only for fillets use 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATLISTP(CATEdge) *iListOfEdges,
  const CATLISTP(CATFace) *iListOfFaces,
  const CATBody *iBody,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_analytic);

// You have to use this constructor if  no external boundaries  
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iTopData);

#endif /* CATIPGMTopologicalAutomaticFill_h_ */
