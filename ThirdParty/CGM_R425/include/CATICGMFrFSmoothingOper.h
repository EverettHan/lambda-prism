#ifndef CATICGMFrFSmoothingOper_h_
#define CATICGMFrFSmoothingOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/
#include "CATIACGMLevel.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMOperator.h"
#include "CATFreeFormDef.h"
#include "CATFrFSmoothingDef.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"

class CATCldScan;
class CATCurve;
class CATGeoFactory;
class CATMathSetOfPointsND;
class CATMathVector;
class CATSoftwareConfiguration;
class CATLISTP(CATCurve);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMFrFSmoothingOper;

/**
 * Class defining a geometric operator that smoothes a set of iNbrePts points to create a set of curves "SetOfCurves".
 * <br>The CATICGMFrFSmoothingOper operator follows the global frame of the geometric operators:
 * <ul>
 * <li>A CATICGMFrFSmoothingOper operator is created with the <tt>CATFrFCreateSmoothingOper</tt> global method
 * and must be directly <tt>delete</tt>d with the usual C++ delete operator after use.
 * It is is not streamable.
 * <li>Options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 * <li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMFrFSmoothingOper: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMFrFSmoothingOper();

  /**
  * Defines the Topological PassPoint constraint corresponding to each internal point of the initial set of points.
  * The point iPoints[iRankPoint-1] is an Extremity of curve in the SetOfCurves result.
  * Size of SetOfCurves increase by one.
  * The final size of SetOfCurves is equal to Number of Internal Topological PassPoint Constraint + 1 .
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 < iRankPoint < iNbrePts.
  * @param iContinuity
  * <ul>
  *  <li>iContinuity = CATFrFNoCont        -> Reset Geometrical constraint,
  *  <li>iContinuity = CATFrFPointCont     -> SetOfCurves is G0 at this point,
  *  <li>iContinuity = CATFrFTangentCont   -> SetOfCurves is G1 at this point,
  *  <li>iContinuity = CATFrFCurvatureCont -> SetOfCurves is G2 at this point.
  * </ul>
  * @param iTangentVect
  * The Tangency vector (normalized) corresponding to each point of the initial set of points.
  * (if 0, a default value is computed)
  * @param iratio
  * Parameter to increase or decrease the norm of tangency vector (which is computed automatically).
  * @param iCurvatureVect
  * The Normal vector (normalized) corresponding to each point of the initial set of points.
  * (if 0, a default value is computed)
  * @param iCurvatureValue
  * Imposed curvature value at the iRankPoint point.
  */
  virtual void SetTopConstraint(
    const int iRankPoint,
    CATFrFContinuity iContinuity = CATFrFPointCont,
    CATMathVector *iTangentVect = 0,
    double iRatio = 1.,
    CATMathVector *iCurvatureVect = 0,
    const double iCurvatureValue = 0.0) = 0;

  /**
  * Resets the Topological constraint corresponding to each point of the initial set of points.
  * The point iPoints[iRankPoint-1] is not a limitCurve in the result SetOfCurves.
  * Size of SetOfCurves decrease by one.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 < iRankPoint < iNbrePts
  */
  virtual void ResetTopConstraint(const int iRankPoint) = 0;

  /**
  * Defines the PassPoint constraint corresponding to each point of the initial set of points.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 <= iRankPoint <= iNbrePts
  * @param iContinuity
  * <ul>
  * <li> iContinuity = CATFrFNoCont        -> Reset constraint,
  * <li> iContinuity = CATFrFPointCont     -> PassPoint constraint,
  * <li> iContinuity = CATFrFTangentCont   -> tangency constraint
  * <li> iContinuity = CATFrFCurvatureCont -> curvature constraint
  * </ul>
  * @param iTangVect
  * The Tangency vector (normalized) corresponding to each point of the initial set of points.
  * (if 0, a default value is computed)
  * @param iratio
  * parameter to increase or decrease the norm of tangency vector (which is computed automatically)
  */
  virtual void SetConstraint(
    const int iRankPoint,
    CATFrFContinuity iContinuity = CATFrFPointCont,
    CATMathVector *iTangVect = 0,
    double iratio = 1.0) = 0;

  /**
  * Reset the constraint corresponding to each point of the initial set of points.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 <= iRankPoint <= iNbrePts
  */
  virtual void ResetConstraint(const int iRankPoint) = 0;

  /**
  * Defaults Options for parametrisation of set of points.
  * @param iParamType
  * The type of parametrization. Examples :
  * <ul>
  * <li>CATFrFSmoothingParamUniform = 0
  * <li>CATFrFSmoothingParamChordal = 1
  * </ul>
  */
  virtual void SetParamType(
    CATFrFSmoothingParamType iParamType = CATFrFSmoothingParamChordal) = 0;

  /**
  * Defines the degree of the resulting curve.
  * @param iDegree
  * The degree value for each curve .
  */
  virtual void SetDegree(const int iDegree = 5) = 0;

  /**
  * Defines the Maxdegree of the resulting curve.
  * @param iDegree
  * The Max degree value for each curve .
  */
  virtual void SetMaxDegree(const int iDegree = 5) = 0;

  /**
  * Defines the parameters corresponding to each point of the initial set of points.
  * @param iNbreOfPts
  * Number of initial set of points.
  * @param iParameters
  * The array of the parameter values that correspond on the smoothed curve to
  * each point of the input set.
  */
  virtual void SetParametrization(int iNbreOfPts, double *iParameters) = 0;

  /**
  * Defines List of Parametric Cutting points corresponding to list of points of the initial set of points.
  * The point iListOfPoints[index] is an Arc limit in the result SetOfCurves .
  * @param iListOfPoints
  * List of Parametric Cutting points,  1 < iListOfPoints[index] < iNbrePts
  * @param iWithImposedPoint
  * if (TRUE) each cutting point is imposed by passpoint constraint; else No Constraint.
  */
  virtual void ImposedCuttingPoints(
    CATListOfInt &iListOfPoints,
    CATBoolean iWithImposedPoint = FALSE) = 0;

  /**
  * Defines the maximum number of arcs of the created curve.
  * @param iMaxNumberOfArcs
  * The maximum number of arcs of each created curve
  * @param iInternalContinuity
  * The Internal continuity of each created curve, iInternalContinuity = 2, 3, 4.
  */
  virtual void SetMaxNumberOfArcs(
    int iMaxNumberOfArcs = 64,
    int iInternalContinuity = 3) = 0;

  /**
  * Defines automatically the maximum number of arcs of the created curve.
  * @param iRespectTolerance
  * if (TRUE), we imposed automatically cutting points until that tolerance is reached.
  */
  virtual void CuttingUntilReachTolerance(CATBoolean iRespectTolerance = TRUE) = 0;

  /**
  * Compute automatically the number of Arcs by CurvatureAnalysis.
  * @param iCurvatureVariationThreshold
  * Criteria used to decide to insert arc limit is based on a factor of curvature variation
  * between the beginning and the end of the curve, for example 5.
  * @param iCurvatureRatio
  * The position of the arc limit is computed at best using area repartition criteria.
  * A parameter defining the ratio between the surfaces is then used to compute this position.
  * @param iCase : CATFrFInflexionTreatment
  * The type of Inflexion Treatment :
  * <ul>
  * <li>CATFrFNone  = 0
  * <li>CATFrFInsertAtInflexion = 1
  * <li>CATFrFSurroundingInflexion = 2
  * </ul>
  * @param iWithImposedPoint
  * if ( TRUE ) each cutting point computed is imposed by passpoint constraint; else No Constraint
  */
  virtual void SetCuttingByCurvatureAnalysis(
    const double iCurvatureVariationThreshold = 5,
    const double iCurvatureRatio = 0.5,
    CATFrFInflexionTreatment iCase = CATFrFSurroundingInflexion,
    CATBoolean iWithImposedPoint = FALSE) = 0;

  /**
  * Defines CuttingDefault Option.
  * @param iCuttingType
  * The type of Cutting Option :
  * <ul>
  * <li>CATFrFCuttingAutoLength  = 1
  * <li>CATFrFCuttingAutoAreaCurvatr = 2
  * <li>CATFrFCuttingAutoLengthCurvatr = 3
  * </ul>
  */
  virtual void SetCuttingDefault(CATFrFCuttingOption iCuttingType) = 0;

  /**
  * Defines the Tolerance of the result.
  * @param iTol3d
  * The maximum distance between the input points and the SetOfCurves.
  * @param iTest
  * <ul>
  * <li>iTest = CATFrFTestByAverageDeviation : Average Deviation is satisfied
  * <li>iTest = CATFrFTestByMaxDeviation     : Max Deviation is satisfied
  * </ul>
  */
#ifdef CATIACGMR421CAA
  virtual void SetTolerance (
    const double            iTol3d ,      // = 0.001,
    CATFrFTestOfConvergence iTest = CATFrFTestByAverageDeviation) = 0;
#else
  virtual void SetTolerance(
    const double iTol3d = 0.001,
    CATFrFTestOfConvergence iTest = CATFrFTestByAverageDeviation) = 0;
#endif

  /**
  * Defines the number of iterations necessary to obtain the best resulting curve.
  * Each iteration gives a different result.
  * @param iIterations
  * The Iteration value for each curve.
  */
  virtual void SetSlideIterations(const int iIterations = 5) = 0;

  /**
  * Returns the SetOfCurves Result.
  * @return
  * oNbreOfCurve : The Number of curves of the Result
  * @return
  * Array of oNbreOfCurve curves result according to SetTopConstraint option
  */
  virtual int GetResult(CATCurve **&oResultCurves) = 0;

#if defined CATIACGMR215CAA
  /**
  * Returns the set of result curves.
  * @return
  * The list of result curves.
  */
  virtual void GetResult(CATLISTP(CATCurve) &oResultCurves) = 0;
#endif

  /**
  * Returns the maximum deviation between set of points and the SetOfCurves Result.
  * @return
  * The maximum deviation value.
  * @return
  * Index of point with max deviation.
  */
  virtual int GetIndexMaxDeviation(double &oMaxdeviation) = 0;

  /**
  * Returns the deviation at each point of the initial set of points.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 <= iRankPoint <= iNbrePts
  * @return
  * The deviation at each point.
  */
  virtual double GetDeviation(const int iRankPoint) = 0;

  /**
  * Returns the Average deviation between set of points and the SetOfCurves Result.
  * @return
  * The Mean deviation value.
  */
  virtual double GetAverageDeviation() = 0;

  /**
  * Returns the tangency constraint corresponding to each point of the initial set of points.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 <= iRankPoint <= iNbrePts
  * @return
  * the tangent vector at the current point,  1 <= iRankPoint <= iNbrePts.
  */
  virtual void GetTangentVect(
    const int iRankPoint,
    CATMathVector &oTangentVect) = 0;

  /**
  * Returns the curvature constraint corresponding to each point of the initial set of points.
  * @param iRankPoint
  * The Rank of the point in iPoints,  1 <= iRankPoint <= iNbrePts
  * @return
  * the curvature value and Normal vector at the current point,  1 <= iRankPoint <= iNbrePts.
  */
  virtual void GetCurvatureVect(
    const int iRankPoint,
    double &oCvt,
    CATMathVector &oNormale) = 0;

  /**
  * Returns The parametrization.
  * @return
  * The array of the parameter values that correspond on the SetOfCurves to
  * each point of the input set.
  */
  virtual void GetParametrization(int &oNbreOfPts, double *&oParameters) = 0;

  /**
  * Returns List of indexes corresponding to Vertex of the SetOfCurves result
  */
  virtual void GetGeometricCuttingpoints(CATListOfInt &oGeomList) = 0;

  /**
  * Returns List of indexes corresponding to internal Arc limit of the SetOfCurves result
  */
  virtual void GetParametricCuttingpoints(CATListOfInt &oParamList) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMFrFSmoothingOper(); // -> delete can't be called
};

/**
* Creates the operator that smoothes a set of points to create a Set of curves.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iConfig
* The pointer to configuration defining the level of code to replay.
* @param iPoints
* The pointer to the set of points (Its dimension=3).
* @return
* The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
* @see CATICGMFrFSmoothingOper
*/
ExportedByCATGMOperatorsInterfaces CATICGMFrFSmoothingOper *CATCGMFrFCreateSmoothingOper(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathSetOfPointsND *iPoints);

#endif /* CATICGMFrFSmoothingOper_h_ */
