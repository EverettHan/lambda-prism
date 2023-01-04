#ifndef CATIPGMBaseHealing_h_
#define CATIPGMBaseHealing_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATCGMJournalList;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATLISTP(CATEdge);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBaseHealing;

/**
 * Class defining the topological operator that heals geometric holes and geometric tangency
 * defaults inside skin bodies.
 * <br>The principle is to create new surfaces by deforming the initial surfaces, so that the
 * the gap of the edges and if required the angle between the two surfaces are
 * reduced to a given value. Continuity objectives can be precised between
 * the surfaces. The healed body is created, using these new surfaces and 
 * sharing the non-modified geometry and topology of the initial body (smart concept).
 * The Healing operator failed in case of non-manifold topology detected on an edge impacted
 * by the Healing.
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
class ExportedByCATGMOperatorsInterfaces CATIPGMBaseHealing: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBaseHealing();

  /** 
 * Appends the body to heal. Can be used when the body to heal has not been
 * initialized in the constructor
 * @param iBodyToHeal
 * The Body to heal
 */
  virtual int SetBodyToHeal(CATBody *iBodyToHeal) = 0;

  /**
 * Defines whether the resulting body must be frozen.
 * @param iFreezeMode
 * The freeze mode.
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iFreezeMode = CATBodyFreezeOn) = 0;

  /**
 * Defines the default global continuity of <tt>this</tt> Healing operator. 
 * @param iOrder
 * The default global continuity for <tt>this</tt> Healing operator. This default can be overridden
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
 * after Healing.
 * @param iTolG0
 * The G0 continuity tolerance. By default (when the method is not called), 
 * <tt>iTolG0</tt> is set to the factory resolution.
 */
  virtual void SetG0Tolerance(const double iTolG0) = 0;

  /** 
 * Defines the maximum G0 default for selecting the edges to be healed 
 * @param iTolG0Max
 * The G0 Maximum continuity tolerance. 
 * The Healing only applies to the edges whose initial default 
 * is lower than this tolerance.
 */
  virtual void SetMaxG0Tolerance(const double iTolG0Max) = 0;

  /** 
 * Defines the maximum G1 default for selecting the edges to be healed 
 * for G1 Healing only.
 * @param iTolAngular
 * The G1 continuity tolerance. 
 * The Healing only applies to the edges whose initial default 
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
  virtual int SetCanonic(
    const CATBoolean iIsGeomFree,
    const CATBoolean iIsTypeFree) = 0;

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
 *				for G1 healing only, the vertex will be adjusted in tangency.
 */
  virtual int SetAdjustPCurve(const short iAdjustPCurve) = 0;

  /**
 * Appends a vertex to be healed.(Healing Local G0 only)
 * @param iVertexToHeal
 * The pointer to the vertex to be healed.
 * @param iEdgeToFix
 * The pointer to the edge to be fixed if needed. The vertex must belong to the edge.
 * @param iOrder
 * The associated continuity objective (G0 only).
 */
  virtual int Add(
    CATVertex *iVertexToHeal,
    CATEdge *iEdgeToFix = 0,
    const short iOrder = 0) = 0;

  /**
 * Defines the constraints on the geometry of a vertex.(Healing Local G0 only)
 * @param iVertexToFix
 * The pointer to the vertex to be fixed. Warning : a vertex to heal can not be fixed.
 * @param iEdge
 * The pointer to the edge with tangency constraint. The vertex must belong to the edge.
 * @param iOrder
 * The associated continuity objective (G1 only).
 */
  virtual int SetVertex(
    CATVertex *iVertexToFix,
    CATEdge *iEdge,
    const short iOrder) = 0;

  /** 
 * @nodoc
 * Internal use for debug purpose.
 * To set the maximum number of iterations in the Healing process
 */
  virtual void SetMaxIter(const int iMaxIter) = 0;

  //---------
  // Results
  //---------    
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
 * This method can be called before Healing and after Healing
 * Before Healing, it returns the list of the edges with G1 continuity 
 * default relatively to the tolerance (See SetMaxG1Tolerance) : 
 * it is the list of edges to be healed with tangency.
 * After Healing, it returns the list of the edges with remaining G1 
 * continuity default relatively to the tolerance (See SetG1Tolerance).
 * @param ioListOfEdges
 * The list of the pointers to the Edges that have not been corrected.
 * @return
**/
  virtual int GetSharpEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

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
  virtual ~CATIPGMBaseHealing(); // -> delete can't be called
};

#endif /* CATIPGMBaseHealing_h_ */
