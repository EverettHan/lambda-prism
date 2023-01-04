#ifndef CATIPGMTopCleanLoopOfFaceOperator_h_
#define CATIPGMTopCleanLoopOfFaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDataType.h"
#include "CATMathDef.h"
#include "CATFreeFormDef.h"

class CATMathSetOfPoints;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCleanLoopOfFaceOperator;

/**
 * Class defining the operator to clean (improve) the continuity of all the loops of a face.
 *
 * The cleaning consists in making exactly continuous the connections at vertices between
 * edges in each loop and in reducing the number of edges in each loop. A maximum deformation
 * between input loops and corrected loops is taken into account during the process.
 * The operator produces a new face, except if no cleaning has been necessary.
 *
 * The cleaning is controlled by the user of the operator. The operator is able to correct the
 * following defects without exceeding an input maximum authorized deformation :
 * - Point discontinuities at vertices between edges of a loop according to a distance 
 *   threshold. Each G0 discontinuity lesser than this threshold is corrected to provide
 *   exact G0 continuity.
 * - Tangency discontinuities between edges of a loop according to an angle threshold. Each
 *   G1 discontinuity lesser than this threshold is corrected to provide exact G1 continuity.
 * - Curvature discontinuities between edges of a loop according to a percentage threshold iCurvThres.
 *   Warning : The G2 discontinuity does not directly correspond to the curvature vector
 *   discontinuity : Let C1 and C2 be the curvature vectors to edges E1, E2 incident to vertex V.
 *   Let define R = |C1 - C2 | / max (|C1|,|C2|) to be the curvature vector ratio.
 *   If R is lesser than (1-iCurvThres)/iCurvThres, G2 disccontinuity is corrected 
 *   to provide exact G2 continuity (R=0).
 * - Small edges are removed according to an edge length criterion.
 * The default continuity level to correct is G2 continuity. Upon request, the user may change this
 * level.
 * More over after these corrections, the operator concatenates G2 continuous edges in order to
 * reduce the number of them. Upon request, the user may disable this treatment in order to keep
 * the same topology between each input loop and each corrected loop (one corrected edge
 * corresponding to one input edge).
 *
 * 
 * This operator follows the general scheme of the topological operators:
 * 
 * - Creates the operator with the CATPGMCreateTopCleanLoopOfFaceOperator global function, which defines
 * the shell to clean the loops of.
 * - Sets the cleaning parameters
 * - Runs with the Run method. In case of maximum deformation control mode, if the operator does
 * not find any solution satisfying all the constraints, an error is thrown.
 * - Gets the result body by the GetResult method. 
 * The result body contains at most the same number of edges than the input one. Moreover, one
 * can access to the maximum deformation between the input body and the result.
 * - Release the operator with the <tt>Release</tt> method after use.
 *
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopCleanLoopOfFaceOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCleanLoopOfFaceOperator();

  ////////////////////////////////////////////////////////////////////////////////////////
  // The following SETTING methods follow the creation of a CATIPGMTopCleanLoopOfFaceOperator,
  // (see CATPGMCreateTopCleanLoopOfFaceOperator global function)
  ////////////////////////////////////////////////////////////////////////////////////////
  /**
  * Defines the point discontinuity threshold for G0 correction.
  * @param iG0Threshold
  * The G0 continuity threshold. This applies to the gap at vertices connecting edges.
  * Default value : factory resolution = 0.001 mm
  * All point discontinuity gaps lesser than this threshold are corrected to provide exact
  * G0 continuity.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetG0Threshold(CATLength iG0Threshold) = 0;

  /**
  * Defines the tangency discontinuity threshold for G1 correction.
  * @param iG1Threshold
  * The G1 continuity threshold. This applies to the tangent vectors angle at vertices of
  * connecting edges.
  * Default value : 0.5 degree
  * All tangency discontinuity angles lesser than this threshold are corrected to provide
  * exact G1 continuity.
  * To be G1 corrected, vertices must be G0 in the input wire, or must have been G0 corrected.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetG1Threshold(CATAngle iG1Threshold) = 0;

  /**
  * Defines the curvature discontinuity threshold for G2 correction.
  * @param iG2Threshold
  * The G2 continuity threshold. This applies to the curvature vectors at vertices of
  * connecting edges according to a formula described hereafter. This value corresponds to
  * a percentage in ]0..1]
  * Default value : 0.98
  * Let C1 and C2 be the curvature vectors to edges E1, E2 incident to vertex V.
  * Let R = |C1 - C2 | / max (|C1|,|C2|) be the curvature vector ratio.
  * The formula : R lesser than (1-iG2Threshold)/iG2Threshold describes how to
  * use the curvature continuity threshold.
  * All curvature discontinuities verifying the formula are corrected to provide exact G2
  * continuity.
  * The more a vertex V is G2 continuous, the more iG2Threshold is near 1.
  * The less a vertex V is G2 continuous, the more iG2Threshold is near 0 (excluded).
  * Give a value near 0 to try to make G2 continuous all vertices, near 1 to only correct
  * vertices that are already quite G2 continuous. 
  * To be G2 corrected, vertex V must be G1 in the input wire, or must have been G1 corrected.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetG2Threshold(double iG2Threshold) = 0;

  /**
  * Defines the highest continuity level to achieve on the loops.
  * @param iContinuityLevel
  * Legal values:
  * CATFrFPointCont :To limit the continuity correction to point continuity correction
  * CATFrFTangentCont : To limit the continuity correction to tangency continuity correction
  * CATFrFCurvatureCont : To limit the continuity correction to curvature continuity correction.
  * Default value : CATFrFCurvatureCont
  * A given continuity order can be reached only if its inferior continuity levels are
  * also reached, according to the continuity correction parameters defined.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetContinuityLevel(CATFrFContinuity iContinuityLevel) = 0;

  /**
  * Defines the point discontinuity threshold below which the G0 correction is not applied.
  * @param iMinG0Threshold
  * Default value : 10.e-6 mm
  * If the distance between two consecutive edges is lesser than iMinG0Threshold, G0 correction
  * is not applied.
  *
  *
  *             +---------------+-------------------------------+------------------> G0 Gap
  *             0        iMinG0Threshold                iG0Threshold
  * Correction  :     NO                     YES                        NO
  *
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMinG0Threshold(CATLength iMinG0Threshold) = 0;

  /**
  * Defines the tangency discontinuity threshold below which the G1 correction is not applied.
  * @param iMinG1Threshold
  * Default value : 0.01 degree
  * If |T1,T2| < iMinG1Threshold, then G1 correction is not applied.
  *
  *
  *             +---------------+-------------------------------+------------------> G1 Angle
  *             0        iMinG1Threshold              iG1Threshold
  * Correction  :     NO                     YES                        NO      
  *
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMinG1Threshold(CATAngle iMinG1Threshold) = 0;

  /**
  * Defines the maximum deformation authorized between input and output (corrected) loops. This
  * value should be between 0. and 0.001, otherwise a not null value is returned (error).
  * @param iMaxDeformation
  * Default value : 0.001 mm (corresponds to the maximum value)
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxDeformationThreshold(CATLength iMaxDeformation) = 0;

  /**
  * Defines the minimum size below which an edge is removed of a loop.
  * @param iMinEdgeLength
  * Default value : 10 * Factory resolution.
  * All edges that length is lesser than iMinEdgeLength are removed.
  * @param iAbsoluteMinEdgeLength
  * Legal values :
  * TRUE if iMinEdgeLength is an absolute length value, FALSE if it is a relative wire length.
  * Default value : TRUE
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMinimumEdgeLength(
    double iMinEdgeLength,
    CATBoolean iAbsoluteMinEdgeLength = TRUE) = 0;

  /**
  * In each loop, reduces the number of edges that are G2 continuous at connecting vertices. This
  * treatment occurs after the continuity correction.
  * @param iEdgeReduction
  * Legal values :
  * TRUE to reduce the number of edges , FALSE to keep one corrected edge per input edge.
  * Default value : TRUE
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetEdgeReduction(CATBoolean iEdgeReduction) = 0;

  ////////////////////////////////////////////////////////////////////////////////////////
  // The following GETTING methods may be called directly after the
  // CATPGMCreateTopCleanLoopOfFaceOperator method
  ////////////////////////////////////////////////////////////////////////////////////////
  /**
  * For each continuity level, computes the highest discontinuity for all the loops of the INPUT face.
  * @param oMaxG0
  * Maximum G0 discontinuity gap value in mm.
  * @param oMaxG1
  * Maximum G1 discontinuity angle value in degrees.
  * @param oMinG2
  * Minimum G2 discontinuity percent value. Reminder : the more the value is small, the more the
  * discontinuity is important. In fact, it corresponds to a continuity percentage.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 GetMaxG0G1MinG2InputEdges(
    double &oMaxG0,
    double &oMaxG1,
    double &oMinG2) = 0;

  ////////////////////////////////////////////////////////////////////////////////////////
  // The following GETTING methods must be called after the Run method
  ////////////////////////////////////////////////////////////////////////////////////////
  /**
  * Returns the maximum deformation between input and output (corrected) loops.
  * This method must be called after the Run method (Returns -1. otherwise).
  * If the maximum reached deformation is greater than the maximum authorized deformation
  * (set by SetMaxDeformationThreshold), a NULL body is returned by the GetResult method.
  * @return
  * The maximum reached deformation value.
  */
  virtual CATLength GetMaxReachedDeformation() = 0;

  /**
  * Returns the 3D location on the input face and the 3D location on the output (corrected) face
  * corresponding to the maximum reached deformation. These locations are 3D points computed from
  * the curve geometry of edges. The distance between these two points corresponds to the
  * maximum reached deformation (see GetMaxReachedDeformation).
  * This method must be called after the Run method, otherwise a not null value is returned (error).
  * @param oInputLocation
  * Point on the input face.
  * @param oOutputLocation
  * Point on the output face.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 GetMaxDeformationLocation(
    CATMathSetOfPoints &oInputLocation,
    CATMathSetOfPoints &oOutputLocation) = 0;

  /**
  * For each continuity level, computes the highest discontinuity for all the loops of the OUTPUT face.
  * @param oMaxG0
  * Maximum G0 discontinuity gap value in mm.
  * @param oMaxG1
  * Maximum G1 discontinuity angle value in degrees.
  * @param oMinG2
  * Minimum G2 discontinuity percent value. Reminder : the more the value is small, the more the
  * discontinuity is important. In fact,  In fact, it corresponds to a continuity percentage.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 GetMaxG0G1MinG2OutputEdges(
    double &oMaxG0,
    double &oMaxG1,
    double &oMinG2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCleanLoopOfFaceOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to clean the curve geometry of all the loops of a face.
* @param iFactory
* The factory that creates the resulting face.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside
* iTopData is NULL, it is not filled. 
* @param iFace
* The pointer to the body mono shell mono face to clean the loops of.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCleanLoopOfFaceOperator *CATPGMCreateTopCleanLoopOfFaceOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyShellMonoFace);

#endif /* CATIPGMTopCleanLoopOfFaceOperator_h_ */
