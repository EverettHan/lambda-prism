#ifndef CATIPGMHealing_h_
#define CATIPGMHealing_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMBaseHealing.h"
#include "CATHealingControlMode.h"

class CATBody;
class CATCGMJournalList;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATLISTP(CATVertex);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);


extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHealing;

/**
 * Class defining the topological operator that heals geometric holes and geometric tangency
 * defaults inside skin bodies.
 * <br>The principle is to create new surfaces by deforming the initial surfaces, so that the
 * the gap of the edges and if required the angle between the two surfaces are
 * reduced to a given value. Continuity objectives can be precised between
 * the surfaces. The healed body is created, using these new surfaces and 
 * sharing the non-modified geometry and topology of the initial body (smart concept).
 * The healing operator failed in case of non-manifold topology detected on an edge impacted
 * by the healing.
 * To use a CATIPGMHealing operator:
 * <ul>
 * <li> Create it with the constructor.
 * <li> Define the parameters (such as the continuity constraints) with the <tt>SetXxx</tt> methods.
 * <li> <tt>run</tt> it.
 * <li> Retrieve the created healed body with the <tt>GetResult</tt> method. Some additional
 * informations are also available with the <tt>GetXxx</tt> methods.
 * <li> Release the operator with the <tt>Release</tt> method after use. 
 * A CATIPGMHealing operator is not a persistent object (it is not streamable).
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMHealing: public CATIPGMBaseHealing
{
public:
  /**
   * Constructor
   */
  CATIPGMHealing();

  /** 
 * Appends the body to heal. Can be used when the body to heal has not been
 * initialized in the constructor
 * @param iBodyToHeal
 * The Body to heal
 */
  virtual int SetBodyToHeal(CATBody *iBodyToHeal) = 0;

  virtual int Reset() = 0;

  /** 
 * @nodoc : Internal Use
 * Requires Healing Topo.
 * @param iHealingTopoOnly
 * <br><b>Legal values</b>: <tt>FALSE</tt> if geometric deformations are allowed (default value), <tt>TRUE</tt>
 * if it wasn't.
 */
  virtual int SetWithHealingTopo(const CATBoolean iHealingTopoOnly = FALSE) = 0;

  /**
 * Appends another edge to be healed.
 * @param
 * The pointer to the edge to be healed. The edge must belong to the input body.
 * @param iOrder
 * The associated continuity objective.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>0</tt></dt><dd> for a G0 continuity 
 * <dt><tt>1</tt></dt><dd> for a G1 continuity 
 * </dl>
 */
  virtual int Add(CATEdge *iE, const short iOrder) = 0;

  /**
 * Appends a list of edges to be healed.
 * @param iEdgeList
 * The list of edge pointers. The edges must belong to the input body.
 * @param iOrder
 * The associated continuity objective.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>0</tt></dt><dd> for a G0 continuity 
 * <dt><tt>1</tt></dt><dd> for a G1 continuity 
 * </dl>
 */
  virtual int Add(CATLISTP(CATEdge) &iEdgeList, const short iOrder) = 0;

  /**
 * Appends a vertex to be healed.(Healing Local G0 only)
 * @param iVertexToHeal
 * The pointer to the vertex to be healed.
 * @param iEdgeToFix
 * The pointer to the edge to be fixed if needed. The vertex must belong to the edge.
 * @param iOrder
 * The associated continuity objective (G0 only).
 */
  virtual int Add(CATVertex *iVertexToHeal, CATEdge *iEdgeToFix = 0, const short iOrder = 0) = 0;

  /**
 * Defines the constraints on the geometry of a vertex.(Healing Local G0 only)
 * @param iVertexToFix
 * The pointer to the vertex to be fixed. Warning : a vertex to heal can not be fixed.
 * @param iEdge
 * The pointer to the edge with tangency constraint. The vertex must belong to the edge.
 * @param iOrder
 * The associated continuity objective (G1 only).
 */
  virtual int SetVertex(CATVertex *iVertexToFix, CATEdge *iEdge, const short iOrder) = 0;

  /**
 * Defines the default global continuity of <tt>this</tt> healing operator. 
 * @param iOrder
 * The default global continuity for <tt>this</tt> healing operator. This default can be overridden
 * by the <tt>Add</tt> method associated with an edge or a list of edges.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>0</tt></dt><dd> for a G0 continuity 
 * <dt><tt>1</tt></dt><dd> for a G1 continuity 
 * </dl>
 */
  virtual int SetGlobalContinuity(const short iOrder) = 0;

  /**
 * Defines the global default for the G0 continuity tolerance required 
 * after healing.
 * @param iTolG0
 * The G0 continuity tolerance. By default (when the method is not called), 
 * <tt>iTolG0</tt> is set to the factory resolution.
 */
  virtual void SetG0Tolerance(const double iTolG0) = 0;

  /** 
 * Defines the maximum G0 default for selecting the edges to be healed 
 * @param iTolG0Max
 * The G0 Maximum continuity tolerance. 
 * The healing only applies to the edges whose initial default 
 * is lower than this tolerance.
 */
  virtual void SetMaxG0Tolerance(const double iTolG0Max) = 0;

 /**
 * Defines the G0 continuity tolerance required for healing topo.
 * @param iTolHT
 * The G0 continuity tolerance. By default (when the method is not called), 
 * <tt>iTolHT</tt> is set to the usual G0 continuity tolerance (see the method SetG0Tolerance(const double iTolG0)). 
*/
  virtual void SetG0ToleranceForHealingTopo(const double iTolHT) = 0;

  /** 
 * Defines the maximum G1 default for selecting the edges to be healed 
 * for G1 healing only.
 * @param iTolAngular
 * The G1 continuity tolerance. 
 * The healing only applies to the edges whose initial default 
 * is lower than this tolerance. By default (when the method is not called), 
 * <tt>iTolAngular</tt> is set to 3 degrees. The maximum value is 5 degrees.
 */
  virtual void SetMaxG1Tolerance(const double iTolAngular) = 0;

  /**
 * Defines the global default for the G1 continuity tolerance.
 * @param iTolAngular
 * The G1 continuity tolerance in degree.
 * default value is 0.5.
 */
  virtual void SetG1Tolerance(const double iTolAngular) = 0;

  /**
 * Defines the Sharpness tolerance.
 * @param iTolSharpness
 * The Sharpness tolerance in degree.
 * default value is 0.5.
 */
  virtual void SetSharpnessTolerance(const double iTolSharpness) = 0;

/**
 * Defines the maximum value allowed for a face deformation.
 * @param iMaxDef
 * if iMaxDef > 0., a deformation of face greater than iMaxDef will be refused
 * if iMaxDef = 0., the control of the deformation is assumed by the healing process
 * default value is 0.
 */
  virtual void SetMaxShapeDeformation(const double iMaxDef) = 0;

/**
 * Defines an automatic control mode for faces deformation.
 * The healing process computes the maximum G0 gap on the whole body : MaxGapG0. 
 * Any deformation of face greater than MaxGapG0 will be refused
 * WARNING : don't use simultaneously with the method SetMaxShapeDeformation (const double iMaxDef);
 */
  virtual void SetAutoMaxShapeDeformation() = 0;

  /** 
 * @nodoc
 * Not Yet Implemented.
 */
  virtual void SetG2Tolerance(const double iTolCurvature) = 0;

  /**
 * Defines  the control mode for improvement of the global continuity 
 * during healing process for a given order.
 * @param iOrder
 * The order of continuity to control.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>0</tt></dt><dd> for a G0 continuity 
 * <dt><tt>1</tt></dt><dd> for a G1 continuity 
 * @param iMode
 * The control mode
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>HealingControlMode::global</tt></dt><dd> for a global control
 * <dt><tt>HealingControlMode::local</tt></dt><dd> for a local control
 * Not Yet Implemented.
 * <dt><tt>HealingControlMode::strict</tt></dt><dd> for a strict control
 * Not Yet Implemented.
 * </dl>
 */
  virtual void SetControlMode(const short iOrder, const CATHealingControlMode iMode) = 0;

  /**
 * Defines the constraints on the geometry of a face.
 * <br>By default
 * <ul>
 * <li>Canonical faces are not free: <tt>iIsTypeFree == FALSE</tt>, <tt>iIsGeomFree == FALSE</tt>.
 * <li>All non-canonical faces are free: <tt>iIsTypeFree == TRUE</tt>, <tt>iIsGeomFree == TRUE</tt>.
 * </ul>
 * @param iF
 * The pointer to the face.
 * @param iIsGeomFree
 * The status of the modification of the face geometry.
 * <br><b>Legal values</b>: <tt>FALSE</tt> if its geometry cannot be changed, <tt>TRUE</tt>
 * if it can.
 * @param iIsTypeFree
 * The status of the preservation of the face geometry type (if <tt>TRUE == iIsGeomFree</tt>).
 * <br><b>Legal values</b>: <tt>FALSE</tt> if the canonicity must be kept (a cylinder
 * cannot become a Nurbs surface), <tt>TRUE</tt>
 */
  virtual int SetFace(
    CATFace *iF,
    const CATBoolean iIsGeomFree,
    const CATBoolean iIsTypeFree) = 0;

  /**
 * Defines the constraints on the geometry of faces.
 * <br>By default
 * <ul>
 * <li>Canonical faces are not free: <tt>iIsTypeFree == FALSE</tt>, <tt>iIsGeomFree == FALSE</tt>.
 * <li>All non-canonical faces are free: <tt>iIsTypeFree == TRUE</tt>, <tt>iIsGeomFree == TRUE</tt>.
 * </ul>
 * @param iListOfFaces
 * The list of the face pointers. 
 * @param iIsGeomFree
 * The status of the modification of the face geometry.
 * <br><b>Legal values</b>: <tt>FALSE</tt> if its geometry cannot be changed, <tt>TRUE</tt>
 * if it can.
 * @param iIsTypeFree
 * The status of the preservation of the face geometry type (if <tt>TRUE == iIsGeomFree</tt>).
 * <br><b>Legal values</b>: <tt>FALSE</tt> if the canonicity must be kept (a cylinder
 * cannot become a Nurbs surface), <tt>TRUE</tt>
 */
  virtual int SetFace(
    const CATLISTP(CATFace) &iListOfFaces,
    const CATBoolean iIsGeomFree,
    const CATBoolean iIsTypeFree) = 0;

  /**
 * Defines the constraints on the geometry of faces of a given type.
 * <br>By default
 * <ul>
 * <li>Canonical faces are not free: <tt>iIsTypeFree == FALSE</tt>, <tt>iIsGeomFree == FALSE</tt>.
 * <li>All non-canonical faces are free: <tt>iIsTypeFree == TRUE</tt>, <tt>iIsGeomFree == TRUE</tt>.
 * </ul>
 * @param iType
 * The geometric type of the faces.
 * @param iIsGeomFree
 * The status of the modification of the face geometry.
 * <br><b>Legal values</b>: <tt>FALSE</tt> if its geometry cannot be changed, <tt>TRUE</tt>
 * if it can.
 * @param iIsTypeFree
 * The status of the preservation of the face geometry type (if <tt>TRUE == iIsGeomFree</tt>).
 * <br><b>Legal values</b>: <tt>FALSE</tt> if the canonicity must be kept (a cylinder
 * cannot become a Nurbs surface), <tt>TRUE</tt>
 */
  virtual int SetFace(
    const CATGeometricType iType,
    const CATBoolean iIsGeomFree,
    const CATBoolean iIsTypeFree) = 0;

  /**
 * Defines the constraints on the geometry of faces of a given type.
 * <br>By default
 * <ul>
 * <li>Canonical faces are not free: <tt>iIsTypeFree == FALSE</tt>, <tt>iIsGeomFree == FALSE</tt>.
 * <li>All non-canonical faces are free: <tt>iIsTypeFree == TRUE</tt>, <tt>iIsGeomFree == TRUE</tt>.
 * </ul>
 * @param iType
 * The geometric type of the faces.
 * @param iIsGeomFree
 * The status of the modification of the face geometry.
 * <br><b>Legal values</b>: <tt>FALSE</tt> if its geometry cannot be changed, <tt>TRUE</tt>
 * if it can.
 * @param iIsTypeFree
 * The status of the preservation of the face geometry type (if <tt>TRUE == iIsGeomFree</tt>).
 * <br><b>Legal values</b>: <tt>FALSE</tt> if the canonicity must be kept (a cylinder
 * cannot become a Nurbs surface), <tt>TRUE</tt>
 */
  virtual int SetCanonic(const CATBoolean iIsGeomFree, const CATBoolean iIsTypeFree) = 0;

  /**
 * Defines the constraints on the geometry of an edge.
 * @param iE
 * The pointer to the edge.
 * @param iOrder
 * <br>By default an edge can be modified.
 * It is possible to keep the initial gap of an edge or to minimize the deformation
 * of an edge.
 * <br>By default the G1 continuity of an edge can be modified.
 * It is possible to keep the initial sharpness of an edge.
 * The angle between the 2 surfaces will be kept relatively to the G1 Tolerance
 * <tt>0</tt> for a G0 continuity.
 * <tt>1</tt> for a G1 continuity.
 */
  virtual int SetEdge(CATEdge *iE, const short iOrder) = 0;

  /**
 * Defines the constraints on the geometry of a list of edges.
 * <br>By default an edge can be modified.
 * It is possible to keep the initial gap of an edge or to minimize the deformation
 * of an edge.
 * By default the G1 continuity of an edge can be modified.
 * It is possible to keep the initial sharpness of an edge.
 * The angle between the 2 surfaces will be kept relatively to the G1 Tolerance
 * <tt>0</tt> for a G0 continuity.
 * <tt>1</tt> for a G1 continuity.
 */
  virtual int SetEdge(const CATLISTP(CATEdge) &iListOfEdges, const short iOrder) = 0;

  /**
 * Defines an option for adjusting PCurves when there is a hole between them.
 * <br>By default the PCurves are adjusted only if their adjacent vertex belongs
 * to an edge to heal.
 * It is possible to adjust the PCurves on other kind of vertex.
 * <tt>0</tt> adjust PCurves adjacent to a vertex of an edge to heal.
 * <tt>1</tt> adjust also PCurves if the vertex belongs to the shell boundary.
 * <tt>2</tt> for G1 healing only, the vertex will be adjusted in tangency.
 */
  virtual int SetAdjustPCurve(const short iAdjustPCurve) = 0;

  /** 
	* Activates multiprocesses mode if  iNumberOfProcessesToUse is greater that 1.
	* @param iNumberOfProcessesToUse [in]
	*  The number of processes to use
	* Return value::<br><tt>
	* <ul>
	* <li> 0     : success
	* <li> other : failure. Only mono process context is availables
	* </ul> 
	*/
  virtual int SetParallelComputingContext(const int iNumberOfProcessesToUse) = 0;

  /** 
 * @nodoc
 * Internal use for debug purpose.
 */
  virtual int SetApproxParam(const int iMaxNumberOfPatch, const short iMaxdegree) = 0;

  /** 
 * @nodoc
 * Internal use for debug purpose.
 * To set the maximum number of iterations in the healing process
 */
  virtual void SetMaxIter(const int iMaxIter) = 0;

  /** 
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  //---------
  // Results
  //---------    
  /**
 * Defines whether the resulting body must be frozen.
 * @param iFreezeMode
 * The freeze mode.
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iFreezeMode = CATBodyFreezeOn) = 0;

  /**
 * Returns the pointer to the resulting healed body.
 * @return
 * The pointer to the resulting body. 
 * If you do not want to keep the resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometry factory.
 */
  virtual CATBody *GetResult() = 0;

  /**
 * Returns the global maximum G0 deviation.
 * @return
 * The maximum G0 gap on the whole body.
 * Can also be used for the initial Body.
 */
  virtual double G0MaxError() = 0;

  /**
 * Returns the global maximum G1 deviation.
 * @return
 * The maximum G1 gap on the whole body.
 */
  virtual double G1MaxError() = 0;

  /** 
 * @nodoc
 * Not Yet Impemented.
 */
  virtual double G2MaxError() = 0;

  /**
 * After healing, this method returns the final maximum G0 gap on Vertices to be healed
 * @return
 * The maximum G0 gap
 */
  virtual double G0MaxErrorOnVertices() = 0;

  /**
 * Retrieves the G0 continuity diagnosis for a given vertex.
 * @param iV
 * The pointer to the vertex to be tested.
 * @param ioG0Error
 * The value of the maximum G0 gap on this Vertex.
 * @return
 * -1 if the vertex has not been impacted by the deformation
 */
  virtual int G0MaxError(CATVertex *iV, double &ioG0Error) = 0;

  /**
 * Tests whether the global continuity constraint is satisfied by the resulting body
 * relatively to the default tolerances or the tolerances entered by the method 
 * SetTolerance.
 * @return
 * The result of the test. 
 * <br>>b<Legal values</b>: <tt>TRUE</tt> if it is, <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean IsSatisfied() = 0;

  /**
 * Retrieves the G0 continuity diagnosis for a given edge.
 * The edges have to belong to one of the deformed faces.
 * @param iE
 * The pointer to the edge to be tested.
 * @param ioG0Error
 * The value of the maximum G0 deviation along the edge.
 * @return
 * -1 if the edge has not been impacted by the deformation
 */
  virtual int G0MaxError(CATEdge *iE, double &ioG0Error) = 0;

  /**
 * Retrieves the G1 continuity diagnosis for a given edge.
 * The edges have to belong to one of the deformed faces.
 * @param iE
 * The pointer to the edge to be tested.
 * @param ioG0Error
 * The value of the maximum G0 deviation along the edge.
 * @return
 * -1 if the edge has not been impacted by the deformation
 */
  virtual int G1MaxError(CATEdge *iE, double &ioG1Error) = 0;

  /** 
 * @nodoc
 * Not Yet Implemented.
 */
  virtual int G2MaxError(CATEdge *iE, double &ioG2Error) = 0;

  /**
 * Tests whether the continuity constraint is satisfied for a given edge relatively 
 * to the required tolerances
 * @param iE
 * The pointer to the edge to be tested.
 * @param ioIsSatisfied
 * The result of the test. 
 * <br>>b<Legal values</b>: <tt>TRUE</tt> if it is, <tt>FALSE</tt> otherwise.
 * @return
 */
  virtual int IsSatisfied(CATEdge *iE, CATBoolean &ioIsSatisfied) = 0;

  /**
 * Tests whether the continuity constraint required for a given edge is compatible
 * with the constraints on its adjacent faces.
 * If two adjacent faces are not Free, the edge is not Compatible.
 * @param iE
 * The pointer to the edge to be tested.
 * @param oIsCompatible
 * The result of the test. 
 * <br>>b<Legal values</b>: <tt>TRUE</tt> if it is, <tt>FALSE</tt> otherwise.
 * @return
 */
  virtual int IsCompatible(CATEdge *iE, CATBoolean &oIsCompatible) = 0;

  /**
 * Tests whether the continuity constraint required for a given edge is compatible
 * with the constraints on its adjacent faces.
 * If two adjacent faces are not Free, the edge is not Compatible for G0 or G1 Healing.
 * @param iE
 * The pointer to the edge to be tested.
 * @param iOrder
 * The order to test 
 * @param oIsCompatible
 * The result of the test. 
 * <br>>b<Legal values</b>: <tt>TRUE</tt> if it is, <tt>FALSE</tt> otherwise.
 * @return
 */
  virtual int IsCompatible(CATEdge *iE, const short iOrder, CATBoolean &oIsCompatible) = 0;

  /**
 * This method can be called before healing and after healing
 * Before healing, it returns the list of the edges with G0 continuity 
 * default relatively to the tolerance : it is the list of edges to be healed.
 * After healing, it returns the list of the edges with remaining G0 
 * continuity default relatively to the tolerance.
 * @param ioListOfEdges
 * The list of the pointers to the Edges that have not been corrected.
 * @return
**/
  virtual int GetOpenEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

  /**
 * This method can be called before healing and after healing
 * Before healing, it returns the list of the edges with G1 continuity 
 * default relatively to the tolerance (See SetMaxG1Tolerance) : 
 * it is the list of edges to be healed with tangency.
 * After healing, it returns the list of the edges with remaining G1 
 * continuity default relatively to the tolerance (See SetG1Tolerance).
 * @param ioListOfEdges
 * The list of the pointers to the Edges that have not been corrected.
 * @return
**/
  virtual int GetSharpEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

  /**
 * After healing, this method returns the list of the vertices with remaining G0 
 * continuity default relatively to the tolerance.
 * @param ioListOfVertices
 * The list of the pointers to the vertices that have not been corrected.
 * @return
**/
  virtual int GetOpenVertices(CATLISTP(CATVertex) &ioListOfVertices) = 0;

  /**
 * Retrieves the value of the maximum deformation for a given edge.
 * @param iE
 * The pointer to the edge to be tested.
 * @param oMaxDef
 * The value of the maximum deformation along the edge.
 * @return
 * -1 if the edge has not been impacted by the deformation
 */
  virtual int GetMaxDeformationOnEdge(CATEdge *iE, double &oMaxDef) = 0;

  /**
 * Retrieves the faces that could not be satisfactorily deformed.
 * <br>In this case, they remain the same.
 * @param ioListOfFaces
 * The list of the pointers to the faces that could not be deformed.
 * @return
 */
  virtual int GetNoDeformedFaces(CATLISTP(CATFace) &ioListOfFaces) = 0;

  /**
 * Retrieves the faces that have been deformed.
 * @param ioListOfFaces
 * The list of the pointers to the faces that have been  deformed.
 * @return
 */
  virtual int GetDeformedFaces(CATLISTP(CATFace) &ioListOfFaces) = 0;

  /**
 * Retrieves the value of the maximum deformation for a given face.
 * @param iF
 * The pointer to the face to be tested.
 * @param oMaxDef
 * The value of the maximum deformation along the face.
 * @return
 * -1 if the face has not been impacted by the deformation
 */
  virtual int GetMaxDeformationOnFace(CATFace *iF, double &oMaxDef) = 0;

  /**
 * Retrieves the value of the maximum deformation allowed, computed by the method SetAutoMaxShapeDeformation();
 * @param oMaxDef
 * The value of the maximum deformation allowed
 * @return
 * -1 if the method SetAutoMaxShapeDeformation() has not been used
 */
  virtual int GetAutoMaxShapeDeformation(double &oMaxDef) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHealing(); // -> delete can't be called
};

/**
 * Creates a topological operator that heals geometric holes and geometric tangency
 * defaults inside skin bodies.
 * <br>The principle is to create new surfaces by deforming the initial surfaces, so that the
 * the gap of the edges and if required the angle between the two surfaces are reduced to a given value.
 * Continuity objectives can be precised between
 * the surfaces. The healed body is created, using these new surfaces and 
 * sharing the non-modified geometry and topology of the initial body (smart concept).
 * @param iGeoFactory
 * The pointer to the factory of the geometry. 
 * @param iData
 * The pointer to the topological data corresponding to the configuration and the journal.
 * @param iBodyToHeal
 * The pointer to the body to be healed.
 * This pointer can be NULL. Then use the method SetBodyToHeal before using all the other
 * methods.
 * @return [out, IUnknown#Release]
 * The pointer ti the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMHealing *CATPGMCreateHealing(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToHeal);

#endif /* CATIPGMHealing_h_ */
