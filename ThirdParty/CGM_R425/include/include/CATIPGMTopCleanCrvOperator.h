#ifndef CATIPGMTopCleanCrvOperator_h_
#define CATIPGMTopCleanCrvOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATTopCleanCrvOperatorDef.h"
#include "CATFreeFormDef.h"
#include "CATDataType.h"
#include "CATCollec.h"

class CATCell;
class CATEdge;
class CATGeometry;
class CATLISTP_CATCell_;
class CATMathSetOfPoints;
class CATSurface;
class CATVertex;
class CATWire;
class CATIPGMTopWireContinuity;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCleanCrvOperator;

/**
 * Class defining the operator to clean a wire body.
 * <br>
 * The operator produces a wire topology that is at least (G0) continuous. More over, upon request, it can:
 *<ul>
 * <li> Enhance the continuity between edges up to the continuity in curvature (G2 continuity).
 * <li> Concatenate all the edges sharing vertices that are G2 continuous.
 * <li> Allow the continuity enhancement of the wire on a shell topology support (2D cleaning mode).
 *</ul>
 * The operator produces a new wire containing at most the same number of edges than the input wire.
 * The correction is controlled by the user. The operator can correct:
 * <ul>
 *  <ul><li>Point discontinuities between edges, according to a point discontinuity criterion.
 *    All point discontinuity gaps less than this criterion are corrected to be set to the standard G0 gap 
 * (see @href CATGeoFactory#GetResolution ).
 *  <li> Tangency between edges, according to a tangency discontinuity criterion.
 *    The tangency discontinuity angles less than this criterion are corrected to be set to the standard G1 angle
 * (see @href CATGeoFactory#GetResolution ).
 *  <li>Curvature between edges, according to a curvature vector discontinuity criterion. 
 * Let <tt>C1</tt> and <tt>C2</tt> be the curvature vectors to edges <tt>E1</tt>, <tt>E2</tt> incident to vertex <tt>V</tt>.
 * <br>Define <tt>R = |C1 - C2 | / max (|C1|,|C2|)</tt> to be the curvature vector ratio.
 * If <tt>R</tt> is greater than <tt>(1-iCurvatureRatio)/iCurvatureRatio</tt>, G2 continuity will 
 * be corrected to the standard G2 value (see @href CATGeoFactory#GetResolution ).
 *  <li>Small edges to delete, according to an edge length criterion, upon request.
 * </ul>
 *  More over after these corrections, the operator can merge edges that are connected by vertices 
 * that are continuous in curvature.
 * <br>
 * These operations can be driven in two control modes @href CatTopCleanCrvPriorityMode :
 * <ul>
 *  <li>@href CatTopCleanCrvPriorityMode#CatTopCleanCrvContinuity : The priority is given to continuity order achievement, regardless of the geometric deformation.
 *    Some important deformations between the input body and the result may appear.
 *  <li>@href CatTopCleanCrvPriorityMode#CatTopCleanCrvDeformation : The process is run with an additional constraint of maximum deformation around the input wire. 
 *    In this case, it can happen that some required continuity constraints are not reached, producing
 * an error in the <tt>Run</tt> method.
 * </ul> 
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Creates the operator with the <tt>CATPGMCreateTopCleanCrvOperator</tt> global function, which defines
 * the wire to clean
 *<li> Sets the cleaning parameters
 *<li> Runs with the <tt>Run</tt> method. In case of maximum deformation control mode, if the operator does not find
 * any solution satisfying all the constraints, an error is thrown. 
 *<li> Gets the result body by the <tt>GetResult</tt> method. 
 * The result body contains at most the same number of edges 
 * than the input one. Moreover, one can access to the maximum deformation
 * between the input body and the result. 
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 * Remark : In case of 2D cleaning mode (on shell), the continuity at transition vertices between two
 * faces could not be enhanced beyond the continuity between both faces. Indeed, the treatment does not
 * enhance the continuity of the shell.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopCleanCrvOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCleanCrvOperator();

  //
  // The following setting methods follow the creation of a CATIPGMTopCleanCrvOperator,
  // (see CATPGMCreateTopCleanCrvOperator global function)
  //
  /**
  * Defines the point continuity criterion for G0 correction.
  * @param iConnexityGap
  * The G0 continuity criterion, set by default to the factory resolution.
  * This applies to vertices connecting edges.
  * All point discontinuity gaps less than this criterion are corrected to be set to the standard G0 gap.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetConnexityGap       (      CATLength                    iConnexityGap    ) = 0;

  /**
  * Defines the tangency criteria for G1 correction.
  * @param iTangencyAngle
  * The tangence angle in <b>degrees</b>, set by default to 0.5 degree.
  * <tt>iTangencyAngle</tt> is the upper value under which a tangency correction (G1) will be performed.
  * Let <tt>T1</tt> and <tt>T2</tt> be the tangents to the edges <tt>E1</tt>, <tt>E2</tt> incident to vertex <tt>V</tt>.
  * If <tt>|T1-T2|</tt> is less than <tt>iTangencyAngle</tt>, it will be corrected to the standard G1 value.
  * To be G1 corrected, vertex <tt>V</tt> must be G0 in the input wire, 
  * or must have been corrected in G0 by the cleaning process.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetTangencyAngle      (      CATAngle                     iTangencyAngle   ) = 0;

  /**
  * Defines the curvature criterion for G2 correction.
  * @param iCurvatureRatio
  * The curvature ratio in <tt>]0..1]</tt>, set by default to 0.98.
  * Let <tt>C1</tt> and <tt>C2</tt> be the curvature vectors to edges <tt>E1</tt>, <tt>E2</tt> incident to vertex <tt>V</tt>.
  * Let <tt>R = |C1 - C2 | / max (|C1|,|C2|)</tt> be the curvature vector ratio.
  * If <tt>R</tt> is greater than <tt>(1-iCurvatureRatio)/iCurvatureRatio</tt>, G2 continuity will 
  * be corrected to the standard G2 value.
  * The more a vertex <tt>V</tt> is G2 continuous, the more <tt>iCurvatureRatio</tt> is near 1.
  * The less a vertex <tt>V</tt> is G2 continuous, the more <tt>iCurvatureRatio</tt> is near 0 (excluded).
  * Give a value near of 0 to try to make G2 all vertices, near 1 to only correct vertices
  * that are already quite G2. 
  * To be G2 corrected, vertex <tt>V</tt> must be G1 in the input wire, or must have been corrected 
  * in G1 by the cleaning process.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetCurvatureRatio     (      double                       iCurvatureRatio  ) = 0;

  /**
  * Defines the point continuity criterion below which the G0 correction is not applied.
  * @param iConnexityMinGap
  * The G0 continuity criterion minimum, set by default to 0.
  * If the distance between two consecutives Edges < iConnexityMinGap, then 
  * G0 correction is not applied.
  *
  * Default value : 0.
  * <pre>
  *            +---------------+-------------------------------+------------------> G0 Gap
  *            0        iConnexityMinGap                iConnexityGap
  * Correction  :     NO                     YES                        NO </pre>
  *
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetConnexityMinGap    (      CATLength                    iConnexityMinGap  ) = 0;

  /**
  * Defines the tangency criterion below which the G1 correction is not applied.
  * @param iTangencyMinAngle
  * The tangence angle minimum in <b>degrees</b>, set by default to 0 degree.
  * If |T1,T2| < iTangencyMinAngle, then G1 correction is not applied.
  *
  * <pre>
  *        +---------------+-------------------------------+------------------> G1 Gap
  *        0         iTangencyMinAngle                iTangencyAngle
  * Correction  :     NO                     YES                        NO      </pre>
  *
  */
  virtual CATLONG32        SetTangencyMinAngle   (      CATAngle                     iTangencyMinAngle) = 0;

  /**
  * Defines the priority mode of cleaning operations.
  * @param iMode
  * The mode value. By default, it is set <tt>CatTopCleanCrvContinuity</tt>.
  * <br><b>Legal values</b>:
  * <dl>
  * <dt><tt>CatTopCleanCrvContinuity</tt></dt><dd> No Limitation of the deformation.
  * <dt><tt>CatTopCleanCrvDeformation</tt></dt><dd> To limit the deformation (see also <tt>SetMaxDeformation</tt>).
  * </dl>
  * <b>Note</b> : For a better quality result it is recommanded to use the <tt>CatTopCleanCrvDeformation</tt> 
  * and not the default mode.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetPriorityMode       (      CatTopCleanCrvPriorityMode   iMode            ) = 0;

  /**
  * Defines the maximum deformation allowed between the output and input bodies.
  * @param iMaxDeformation
  * The deformation value, set by default to 0.001.
  * This parameter will be used only when working in <tt>CatTopCleanCrvDeformation</tt> priority mode.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetMaxDeformation     (      CATLength                    iMaxDeformation  ) = 0;

  /**
  * Defines the highest continuity level to achieve on the wire.
  * @param iContinuityLevel
  * The continuity level, set by default to <tt>CATFrFTangentCont</tt> for tangency continuity.
  * <br><b>Legal values</b>:
  * <dl>
  * <dt><tt>CATFrFPointCont</tt></dt><dd> To limit the continuity correction to point continuity correction
  * <dt><tt>CATFrFTangentCont</tt></dt><dd> To limit the continuity correction to tangency continuity correction
  * <dt><tt>CATFrFCurvatureCont</tt></dt><dd> To limit the continuity correction to curvature continuity correction.
  * </dl>
  * A given continuity order can be reached only if its inferior continuity levels are also reached,
  * according to the continuity correction parameters defined by <tt>SetConnexityGap</tt>, <tt>SetTangencyAngle</tt>,
  * <tt>SetCurvatureRatio</tt>, <tt>SetConnexityMinGap</tt>,<tt>SetTangencyMinAngle</tt>.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetContinuityLevel    (      CATFrFContinuity             iContinuityLevel ) = 0;

  /**
  * Retrieve the current continuity level to improve defined on operator.
  * @return
  * The current continuity level.
  */
  virtual CATFrFContinuity GetContinuityLevel    ()                                                     = 0;

  /**
  * To use on Closed Wire with SetCellReduction or SetApplyMappingOfInitialVertices only.
  * This allow the CATIPGMTopCleanCrvOperator to	modify where is the Closure Vertex of the wire.
  * Note : by default the operator does not change where is the closure vertex.
  * @param iVertex
  * <dl><b>Legal values</b>:
  * <tt>NULL</tt> (Default) the operator automatically choose a closure vertex with the following preferences.
  * <dt></dt><dd> If SetShell is used (2D Clean) the closure vertex will be at a transition     between two faces.
  * <dt></dt><dd> the closure vertex will be at a vertex that will not be G0 after clean.
  * <dt></dt><dd> the closure vertex will be at a vertex that will not be G1 after clean.
  * <dt></dt><dd> the closure vertex will be at a vertex that will not be G2 after clean.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetSmartClosure       ()                                                     = 0 ;

  /**
  * Defines the way to treat non-C2 edges.
  * @param iC1ToC2Managment
  * By default the value is CATTopCleanCrvDefaultC1ToC2Management
  * <dl><b>Legal values</b>:
  * <dt><tt>CATTopCleanCrvNoC1ToC2Management</tt></dt><dd> No special treatment would be applied
  * <dt><tt>CATTopCleanCrvDefaultC1ToC2Management</tt></dt><dd> Edges that need a modification 
  * and that are not C2 continuous would be C2 continous in the result.
  * <dt><tt>CATTopCleanCrvAllCurvesC1ToC2Management</tt></dt><dd> All non-C2-continuous Edges would be 
  * C2 continous in the result.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetC1ToC2Management   (      CATTopCleanCrvC1ToC2Management iC1ToC2Managment) = 0;

  /**
  * Combined with cell reduction mode, forces the operator to treat either the one-edge-wire case
  * or any one edge case situated between two unsuppressed vertices.
  * In the case of an one-edge-wire, the result wire is by default exactly the same as the input.
  * @param iEnable
  * By default FALSE.
  * <dl><b>Legal values</b>:
  * <tt>TRUE</tt> Forces the operator to treat one edge if cell reduction is activated : a smoothing based
  * on absolute wire length is applied.
  * <tt>FALSE</tt> If there is only one edge in the wire or for cases with one edge between two vertices,
  * nothing is done.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetForceOneEdgeImprovement(  CATBoolean                   iEnable          ) = 0;

  /**
  * Defines the minimum size of an edge to be corrected.
  * @param iMinimumEdgeLength
  * The minimum edge length to be kept, set by default to <tt>10 * Factory resolution</tt>.
  * All edges which length is less than <tt>iAbsoluteMinEdgeLength</tt> are removed.
  * @param iAbsoluteMinEdgeLength
  * <dl><b>Legal values</b>:
  * <tt>TRUE</tt> if <tt>iMinimumEdgeLength</tt> is the absolute wire length, 
  * <tt>FALSE</tt> the <tt>iMinEdgeLength</tt> is understood as a percentile of the total wire length.
  * In this case if the wire as a total length <tt>L</tt>all edges of length <tt>l</tt> are considered as small edges
  * if and only if <tt>l<=iMinEdgeLength*L</tt>.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetMinimumEdgeLength  (      double                       iMinEdgeLength   ,
                                                        CATBoolean                   iAbsoluteMinEdgeLength = TRUE) = 0;

  /**
  * Returns the maximum deformation between input and output wires.
  * <br>This method must be called after the <tt>Run</tt> method.
  * If the priority mode is <tt>CatTopCleanCrvDeformation</tt> and if the 
  * and maximum deformation that is reached is greater than the maximum authorized
  * deformation ( @href CATIPGMTopCleanCrvOperator#SetMaxDeformation ), a NULL body is returned
  * by the <tt>GetResult</tt> method.
  */
  virtual CATLength        GetMaxReachedDeformation()                                                   = 0;

  /**
  * Returns the 3D location on the input wire and the 3D location on the output (corrected) wire
  * corresponding to the maximum reached deformation. These locations are 3D points computed from
  * the curve geometry of edges. The distance between these two points corresponds to the
  * maximum reached deformation (see GetMaxReachedDeformation).
  * This method must be called after the Run method, otherwise a not null value is returned (error).
  * @param oInputLocation
  * Point on the input wire.
  * @param oOutputLocation
  * Point on the output wire.
  * @return
  * Integer not null in case of error.
  */
  virtual int              GetMaxDeformationLocation(   CATMathSetOfPoints         & oInputLocation ,
                                                        CATMathSetOfPoints         & oOutputLocation)=0;

  /**
  * Defines the set of input edges and vertices that must stay unmodified through the operator.
  * The list only contains edges and/or vertices of the input wire. An error is send if not.
  * These cells will be reproduced as the same as they are in the input wire, and their
  * underlying geometry will not be modified.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetFixedCells           (const CATLISTP(CATCell)        & iFixedCells      ) = 0;

  /**
  * Retrieves the result edge corresponding to an input edge.
  * @param iInputEdge
  * The pointer to the edge of the input wire.
  * @param oInputEdgeStatus
  * The status of the input edge.
  * @param oOutputEdge
  * The pointer to the corresponding edge in the result wire.
  * <tt>oOutputEdge</tt> is <tt>NULL</tt> if <tt>oInputEdgeStatus</tt> equals 
  * <tt>CatTopCleanCrvCellDeleted</tt>, not null otherwise.
  * @return
  * Not null if <tt>iInputEdge</tt> is not an edge of the input wire or if edge descendance
  * is not available.
  * Edge descendance is not available if @href CATIPGMTopCleanCrvOperator#SetC3ContinuityAndCellReduction 
  * has been required.
  */
  virtual CATLONG32        GetDescendantEdge       (      CATEdge                 *  iInputEdge      ,
                                                          CatTopCleanCrvCellStatus & oInputEdgeStatus,
                                                          CATEdge                 *& oOutputEdge     ) = 0;

  /**
  * Retrieves the result vertex corresponding to an input vertex.
  * @param iInputVertex
  * The pointer to the vertex of the input wire.
  * @param oInputVertexStatus
  * The status of the input vertex.
  * @param oOutputVertex
  * The pointer to the corresponding vertex in the result wire .
  * <tt>oOutputVertex</tt> is <tt>NULL</tt> if <tt>oInputVertexStatus</tt> equals 
  * <tt>CatTopCleanCrvCellDeleted</tt>, not null else.
  * @return
  * Not null if <tt>iInputVertex</tt> is not a vertex of the input wire.
  */
  virtual CATLONG32        GetDescendantVertex     (      CATVertex               *  iInputVertex      ,
                                                          CatTopCleanCrvCellStatus & oInputVertexStatus,
                                                          CATVertex               *& oOutputVertex     ) = 0;

  /**
  * Defines the 2D cleaning mode.
  * @param iShellBody
  * The shell body on which the wire is cleaned.
  * The topological wire on shell " LyingOnLink " must exist. That is a warranty the
  * wire edges to clean are geometrically represented on the <tt>iShellBody</tt> faces.
  * @return
  * Not null if <tt>iShellBody</tt> is a NULL pointer.
  * <br> An error is thrown if <tt>iShellBody</tt> is not made of a single shell.
  * <br> An error is thrown if the wire on shell " LyingOnLink " does not exist.
  */
  virtual CATLONG32        SetShell                (      CATBody                 *  iShellBody        ) = 0;

  /**
  * Defines the 2D cleaning mode with optional topological wire on shell " LyingOnLink " recovery.
  * @param iShellBody
  * The shell body on which the wire is cleaned.
  * @param iLyingOnLinkRecovery
  * On TRUE, enables the recovery of the topological wire on shell " LyingOnLink " if absent.
  * In this case, the wire edges to clean must be geometrically represented on the
  * <tt>iShellBody</tt> faces.
  * On FALSE, the topological wire on shell " LyingOnLink " must exist.
  * @return
  * Not null if <tt>iShellBody</tt> is a NULL pointer.
  * <br> An error is thrown if <tt>iShellBody</tt> is not made of a single shell.
  * <br> An error is thrown if the wire edges are not geometrically represented on the
  * <tt>iShellBody</tt> faces when recovery option is enabled (TRUE).
  */
  virtual CATLONG32        SetShell                (      CATBody                 *  iShellBody        ,
                                                          CATBoolean                 iLyingOnLinkRecovery) = 0;

  /**
  * Reduce the number of cells after curvature correction.
  * @param iCellReduction
  * iCellReduction = TRUE to concatenate all the result edges sharing vertices that are G2 continuous.
  * If is CellReduction is required it is recommanded for better stability to use it in <tt>CATFrFCurvatureCont</tt>
  * correction mode.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetCellReduction        (      CATBoolean                 iCellReduction    ) = 0;

  /**
  * Retrieve the current status of cell reduction defined on operator.
  * @return
  * The current cell reduction status.
  */
  virtual CATBoolean       GetCellReduction        ()                                                    = 0;

  /**
  * @deprecated V5R15
  * Activate the C3 correction and cell reduction.
  * @param iC3Mode
  * iC3Mode = TRUE to ask for C3 continuity correction and cell reduction of the wire.
  * The operator concatenates all the result edges sharing vertices that are C3 continuous, 
  * and creates vertices at points that are not.
  * Point, tangency and curvature continuity corrections will automatically be performed, controlled
  * by the associated continuity thresholds.
  * if C3 correction an cell reduction is required, the edge descendance informations given
  * by @href CATIPGMTopCleanCrvOperator#GetDescendantEdge are not available.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetC3ContinuityAndCellReduction(CATBoolean                iC3Mode           ) = 0;

  /**
  * @deprecated V5R15
  * do not use.
  * Retrieve the current status of cell reduction defined on operator.
  */
  virtual CATBoolean       GetC3ContinuityAndCellReduction()                                             = 0;

  /**
  * This API should not be used.
  */
  virtual void             SetModeODT              (      char                    *  iScenarioNameStr  ,
                                                          char                    *  iInputFileNameStr ) = 0;

  /**
  * @deprecated V5R15
  * To use local optimization . ONLY AVAILABLE WITH "Deformation" OPTION
  * Local optimization means : new connections are computed to minimize the 3th derivative of 
  * the curves (3 order energy). The goal is to reduce oscillations of curvature combs.
  * The result could be close to we picture.
  * iOptimization = 1 = ON, iOptimization = 0 = OFF (default);
  */
  virtual CATLONG32        SetLocalOptimization    (const int                        iOptimization  = 0) = 0 ;

  /**
  * Allows the activation of the mapping of the input vertices to the output vertices.
  * @param iApplyMapping
  * If TRUE AND SetContinuityLevel(CATFrFCurvatureCont) AND SetLocalOptimization(TRUE) AND SetCellReduction(FALSE) 
  * the mapping could be activated then the quality of the wire is very similar to the quality obtained 
  * when the SetCellReduction is set to TRUE (Smoother result) but the vertices are kept. 
  * <br> After deletion of small edges the position of the remained vertices are saved with their
  * global curvilinear adimensional param (eg Pos(Vi)=Total_Length_From_The_Starting_Extremity_To_Vi/Total_Length_Of_Wire)
  * then a a global smoothing is applyied on a reduced wire and the vertices are reinserted at 
  * New_Pos(Vi)=Pos(Vi)*New_Total_Length_Of_Wire.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetApplyMappingOfInitialVertices (const int               iApplyMapping  = 0) = 0 ;

  /**
  * @nodoc
  * do not use
  */
  virtual CATLONG32        SetLayDown              (const int                        iLayDown       = 1) = 0;

  /**
  * @deprecated V5R15
  * do not use
  */
  virtual CATLONG32        SetForceFillEdgeTreatment(const int                       iForceFillEdgeTreatment = 0)=0;

  /**
  * @nodoc
  * do not use
  */
  virtual CATLONG32        SetFixLines             (      int                        iFixLines      = 0) = 0;

  /**
  * @nodoc
  * do not use
  */
  virtual CATLONG32        SetFixCanonics          (      int                        iFixLevel      = 0) = 0; 

  /**
  * @nodoc
  * do not use
  */
  virtual CATLONG32        SetHybridMode2D3D       (      int                        iHybridMode2D3D   = 0) = 0; 

  /**
  * @nodoc
  * do not use
  */
  virtual CATLONG32        SetLayDownToleranceForHybridMode2D3D(double               iLDTFHM2D3D       ) = 0; 

  /**
  * @nodoc
  * do not use
  * @param oTWCOIB [out, IUnknown#Release]
  */
  virtual CATLONG32        GetTopWireContinuityOnInputWireBody(CATIPGMTopWireContinuity *&oTWCOIB      ) = 0;

  /**
  * @nodoc
  * do not use
  * @param oTWCORB [out, IUnknown#Release]
  */
  virtual CATLONG32        GetTopWireContinuityOnResultWireBody(CATIPGMTopWireContinuity *&oTWCORB     ) = 0;

  /**
  * Defines the highest continuity level at the START extremity between the input wire and the
  * result wire.
  * @param iStartContLevel
  * The continuity level, set by default to <tt>CATFrFCurvatureCont</tt> for curvature continuity.
  * <br><b>Legal values</b>:
  * <dl>
  * <dt><tt>CATFrFPointCont</tt></dt><dd> To limit the continuity to point continuity
  * <dt><tt>CATFrFTangentCont</tt></dt><dd> To limit the continuity to tangency continuity
  * <dt><tt>CATFrFCurvatureCont</tt></dt><dd> To limit the continuity to curvature continuity.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32        SetStartExtremityContinuityLevel(CATFrFContinuity         iStartContLevel   ) = 0;

  /**
  * Defines the highest continuity level at the END extremity between the input wire and the
  * result wire.
  * @param iEndContLevel
  * The continuity level, set by default to <tt>CATFrFCurvatureCont</tt> for curvature continuity.
  * <br><b>Legal values</b>:
  * <dl>
  * <dt><tt>CATFrFPointCont</tt></dt><dd> To limit the continuity to point continuity
  * <dt><tt>CATFrFTangentCont</tt></dt><dd> To limit the continuity to tangency continuity
  * <dt><tt>CATFrFCurvatureCont</tt></dt><dd> To limit the continuity to curvature continuity.
  * </dl>
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetEndExtremityContinuityLevel (      CATFrFContinuity           iEndContLevel     ) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCleanCrvOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to clean the curve geometry of a wire.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iWireBody
* The pointer to the wire body which edges will be cleaned,
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCleanCrvOperator *CATPGMCreateTopCleanCrvOperator(
  CATGeoFactory * iFactory ,
  CATTopData    * iTopData ,
  CATBody       * iWireBody);

#endif /* CATIPGMTopCleanCrvOperator_h_ */
