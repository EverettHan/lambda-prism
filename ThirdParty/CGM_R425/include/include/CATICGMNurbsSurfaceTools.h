#ifndef CATICGMNurbsSurfaceTools_h_
#define CATICGMNurbsSurfaceTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"
#include "CATNurbsToolsInfo.h"

class CATCurve;
class CATGeoFactory;
class CATKnotVector;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMNurbsSurfaceTools;

/**
 * Class used to manipulate a Nurbs surface. 
 */
class ExportedByCATGMModelInterfaces CATICGMNurbsSurfaceTools: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMNurbsSurfaceTools();

  /**
 * Retrieves the surface degree.
 * @param oDegreeU
 * The degree along U.
 * @param oDegreeV
 * The degree along V.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include for the list of information values.
 */
  virtual CATNurbsToolsInfo GetDegrees(int &oDegreeU, int &oDegreeV) = 0;

  /**
 * Retrieves the number of knot values of the Nurbs surface.
 * @param oNumberOfKnotsU
 * The number of distinct knot values along U.
 * @param oNumberOfKnotsV
 * The number of distinct knot values along V.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetNumberOfKnots(
    int &oNumberOfKnotsU,
    int &oNumberOfKnotsV) = 0;

  /**
 * Retrieves the number of control points of the Nurbs surface.
 * @param oNumberOfControlPointsU
 * The number of control points along U.
 * @param oNumberOfControlPointsV
 * The number of control points along V.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetNumberOfControlPoints(
    int &oNumberOfControlPointsU,
    int &oNumberOfControlPointsV) = 0;

  /**
 * Retrieves a knot value along U from its rank.
 * @param iKnotRank
 * The rank of the knot. The rank starts from 1.
 * @param oKnotValue
 * The parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UKnotRankToKnotValue(
    const int iKnotRank,
    double &oKnotValue) = 0;

  /**
 * Retrieves a knot value along V from its rank.
 * @param iKnotRank
 * The rank of the knot. The rank starts from 1.
 * @param oKnotValue
 * The parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VKnotRankToKnotValue(
    const int iKnotRank,
    double &oKnotValue) = 0;

  /**
 * Retrieves the rank of a knot along U from its value.
 * The parameter corresponds to a knot if the length between the input parameter and 
 * the knot value is lower than TolKnotConfusion.
 * @param iKnotValue
 * The parameter value of the knot.
 * @param oKnotRank
 * The rank of the knot. The rank starts from 1.
 * If the parameter value does not correspond to a knot, iKnotRank = 0;
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_NotAKnot           </tt> <dd>The value is not corresponding to a knot
 *     <dt><tt>Info_KnotValueOnTwoKnots</tt> <dd>The value is corresponding to two knots
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>Input value is lower than first knot value or greater than the last knot value.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UKnotValueToKnotRank(
    const double iKnotValue,
    int &oKnotRank) = 0;

  /**
 * Retrieves the rank of a knot along V from its value.
 * The parameter corresponds to a knot if the length between the input parameter and 
 * the knot value is lower than TolKnotConfusion.
 * @param iKnotValue
 * The parameter value of the knot.
 * @param oKnotRank
 * The rank of the knot. The rank starts from 1.
 * If the parameter value does not correspond to a knot, iKnotRank = 0;
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_NotAKnot           </tt> <dd>The value is not corresponding to a knot
 *     <dt><tt>Info_KnotValueOnTwoKnots</tt> <dd>The value is corresponding to two knots
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>Input value is lower than first knot value or greater than the last knot value.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VKnotValueToKnotRank(
    const double iKnotValue,
    int &oKnotRank) = 0;

  /**
 * Inserts a knot along U.
 * @param iKnotValue
 * The parameter value of the new knot.
 * @param iMultiplicity
 * The multiplicity value of the new knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InvalidDegree      </tt> <dd>The input degree is lower than 3 (1 in a single-arc case) or greater than the maxDegree (11).
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UKnotInsertion(
    const double iKnotValue,
    const int iMultiplicity = 0) = 0;

  /**
 * Inserts a knot along V.
 * @param iKnotValue
 * The parameter value of the new knot.
 * @param iMultiplicity
 * The multiplicity value of the new knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InvalidDegree      </tt> <dd>The input degree is lower than 3 (1 in a single-arc case) or greater than the maxDegree (11).
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VKnotInsertion(
    const double iKnotValue,
    const int iMultiplicity = 0) = 0;

  /**
 * Inserts several knots along U.
 * @param iNumberOfKnotsToInsert
 * The number of knots to be inserted.
 * @param iKnotValues
 * The array of parameter values of the new knots.
 * @param iMultiplicities
 * The array of multiplicity values of the new knots.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knots.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than last knot value
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UMultipleKnotInsertion(
    const int iNumberOfKnotsToInsert,
    const double *iKnotValues,
    const int *iMultiplicities = 0) = 0;

  /**
 * Inserts several knots along V.
 * @param iNumberOfKnotsToInsert
 * The number of knots to be inserted.
 * @param iKnotValues
 * The array of parameter values of the new knots.
 * @param iMultiplicities
 * The array of multiplicity values of the new knots.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knots.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than last knot value
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VMultipleKnotInsertion(
    const int iNumberOfKnotsToInsert,
    const double *iKnotValues,
    const int *iMultiplicities = 0) = 0;

  /**
 * Removes a knot along U.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 *     <dt><tt>Error_ExtremityKnot    </tt> <dd>An extremity knot can not be removed.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UKnotRemoval(const int iKnotRank) = 0;

  /**
 * Removes a knot along V.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 *     <dt><tt>Error_ExtremityKnot    </tt> <dd>An extremity knot can not be removed.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VKnotRemoval(const int iKnotRank) = 0;

  /**
 * Replaces a knot along U.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be replaced. The rank starts from 1.
 * @param iKnotNewValue
 * The new parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits </tt> <dd>The input rank is lower than 1 or greater than the number of knots
 *     <dt><tt>Error_ExtremityKnot     </tt> <dd>An extremity knot can not be modified.
 *     <dt><tt>Error_KnotValueOnAKnot  </tt> <dd>The new knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>The new value is lower than the first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UKnotReplace(
    const int iKnotRank,
    const double iKnotNewValue,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Replaces a knot along V.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be replaced. The rank starts from 1.
 * @param iKnotNewValue
 * The new parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits </tt> <dd>The input rank is lower than 1 or greater than the number of knots
 *     <dt><tt>Error_ExtremityKnot     </tt> <dd>An extremity knot can not be modified.
 *     <dt><tt>Error_KnotValueOnAKnot  </tt> <dd>The new knot value is corresponding to an existent knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>The new value is lower than the first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VKnotReplace(
    const int iKnotRank,
    const double iKnotNewValue,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Imposes the parameterization of another surface
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iSurface
 * The surface whose parametrization is to be kept.
 * @param iLeftContinuityU
 * The left continuity along U.
 * @param iRightContinuityU
 * The right continuity along U.
 * @param iLeftContinuityV
 * The left continuity along V.
 * @param iRightContinuityV
 * The right continuity along V.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (Default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Input pointer of Surface is null
 *     <dt><tt>Error_InputNotNurbs     </tt> <dd>Input Surface is not a Nurbs
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greatest than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal nb of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo ImposeParametrizations(
    CATSurface *iSurface,
    const int iLeftContinuityU = 0,
    const int iRightContinuityU = 0,
    const int iLeftContinuityV = 0,
    const int iRightContinuityV = 0) = 0;

  /**
 * Imposes the parameterization of a surface along U.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iSurface
 * The surface whose parameterization is to be kept.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Surface input pointer is null.
 *     <dt><tt>Error_InputNotNurbs     </tt> <dd>Input surface is not a Nurbs.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo UImposeParametrization(
    CATCurve *iCurve,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Imposes the parameterization of a surface along V.
 * This method deforms the surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iSurface
 * The surface whose parameterization is to be kept.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Surface input pointer is null.
 *     <dt><tt>Error_InputNotNurbs     </tt> <dd>Input surface is not a Nurbs.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo VImposeParametrization(
    CATCurve *iCurve,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Modifies the knot vector along U. 
 * This method deform the Surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation
 * @param iNewKnotVector
 * The Surface to keep the parametrization.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (Default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Input pointer of New Knot Vector is null
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greatest than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal nb of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UChangeKnotVector(
    const CATKnotVector *iNewKnotVector,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Modifies the knot vector along U. 
 * This method deform the Surface. Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation
 * @param iNewKnotVector
 * The surface to keep the parametrization.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (Default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Input pointer of New Knot Vector is null
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greatest than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal nb of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VChangeKnotVector(
    const CATKnotVector *iNewKnotVector,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Modifies the multiplicity of a knot along U.
 * This method deforms the surface if the new multiplicity is lower than the previous multiplicity. 
 * Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @param iMultiplicity
 * The new multiplicity of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_NoModification      </tt> <dd>No modification - new multiplicity is equal to previous multiplicity
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than degree-2
 *     <dt><tt>Error_KnotRankOutLimits  </tt> <dd>The input rank is lower than 1 or greater than number of knots
 *     <dt><tt>Error_ExtremityKnot      </tt> <dd>An extremity knot can not be modified.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
  */
  virtual CATNurbsToolsInfo USetMultiplicity(
    const int iKnotRank,
    const int iMultiplicity) = 0;

  /**
 * Modifies the multiplicity of a knot along V.
 * This method deforms the surface if the new multiplicity is lower than the previous multiplicity. 
 * Use @href CATICGMNurbsSurfaceTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @param iMultiplicity
 * The new multiplicity of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_NoModification      </tt> <dd>No modification - new multiplicity is equal to previous multiplicity
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than degree-2
 *     <dt><tt>Error_KnotRankOutLimits  </tt> <dd>The input rank is lower than 1 or greater than number of knots
 *     <dt><tt>Error_ExtremityKnot      </tt> <dd>An extremity knot cannot be modified.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VSetMultiplicity(
    const int iKnotRank,
    const int iMultiplicity) = 0;

  /**
 * Splits the surface.
 * @param iStartKnotValuesU
 * The start parameter of the surface along U.
 * @param iEndKnotValuesU
 * The end parameter of the surface along U.
 * @param iStartKnotValuesV
 * The start parameter of the surface along V.
 * @param iEndKnotValuesV
 * The end parameter of the surface along V.
 * @return
 * The information value.
 *     <dt><tt>Info_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>value is lower than first knot value or greater than the last knot value.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo ActiveSplits(
    const double iStartKnotValuesU,
    const double iEndKnotValuesU,
    const double iStartKnotValuesV,
    const double iEndKnotValuesV) = 0;

  /**
 * Splits the surface along U.
 * @param iStartKnotValues
 * The start parameter of the surface.
 * @param iEndKnotValues
 * The end parameter of the surface
 * @return
 * The information value.
 *     <dt><tt>Info_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>value is lower than first knot value or greater than the last knot value
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo UActiveSplit(
    const double iStartKnotValues,
    const double iEndKnotValues) = 0;

  /**
 * Splits the surface along V.
 * @param iStartKnotValues
 * The start parameter of the surface.
 * @param iEndKnotValues
 * The end parameter of the surface
 * @return
 * The information value.
 *     <dt><tt>Info_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>value is lower than first knot value or greater than the last knot value
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo VActiveSplit(
    const double iStartKnotValues,
    const double iEndKnotValues) = 0;

  /**
 * Inverts the surface along U.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo UInvert() = 0;

  /**
 * Inverts the surface along V.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo VInvert() = 0;

  /**
 * Reverses U and V along the surface.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo ExchangeUV() = 0;

  /**
 * Modifies the degree of the surface.
 * @param iDegreeU
 * The new degree along U.
 * @param iDegreeV
 * The new degree along V.
 * @param iLeftContinuityU
 * The left continuity along U.
 * @param iRightContinuityU
 * The right continuity along U.
 * @param iLeftContinuityV
 * The left continuity along V.
 * @param iRightContinuityV
 * The right continuity along V.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InvalidDegree     </tt> <dd>The input degree is lower than 3 (1 in a single-arc case) or greater than the MaxDegree (11)
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo SetDegrees(
    const int iDegreeU,
    const int iDegreeV,
    const int iLeftContinuityU = 0,
    const int iRightContinuityU = 0,
    const int iLeftContinuityV = 0,
    const int iRightContinuityV = 0) = 0;

  /**
 * Modifies the degree of the surface along U.
 * @param iDegree
 * The new degree of the surface.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InvalidDegree     </tt> <dd>The input degree is lower than 3 (1 in single-arc case) or greater than the MaxDegree (11)
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all information values. 
 */
  virtual CATNurbsToolsInfo USetDegree(
    const int iDegreeU,
    const int iLeftContinuityU = 0,
    const int iRightContinuityU = 0) = 0;

  /**
 * Modifies the degree of the surface along V.
 * @param iDegree
 * The new degree of the surface.
 * @param iLeftContinuity
 * The left continuity.
 * @param iRightContinuity
 * The right continuity
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt> <dd>C0 continuity (default value).
 *     <dt><tt>1</tt> <dd>C1 continuity.
 *     <dt><tt>2</tt> <dd>C2 continuity.
 *</dl>
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_InvalidDegree     </tt> <dd>The input degree is lower than 3 (1 in single-arc case) or greater than the MaxDegree (11)
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo VSetDegree(
    const int iDegreeV,
    const int iLeftContinuityV = 0,
    const int iRightContinuityV = 0) = 0;

  /**
 * Runs <tt>this</tt> operator.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> 0 </tt> <dd>It is OK.
 *     <dt><tt> 1 </tt> <dd>Error.
 *     <dt><tt>100</tt> <dd>Fatal Error.
 * </dl>
 * If an error has occurred, use @href CATICGMNurbsSurfaceTools#GetInfo for more information.
 */
  virtual int Run() = 0;

  /**
 * Returns the new surface computed by <tt>this</tt> operator.
 * @return
 * The pointer to the new surface.
 * Pointer is 0 if an error has occurred (use @href CATICGMNurbsSurfaceTools#GetInfo for more information).
 */
  virtual CATSurface *GetResult() = 0;

  /**
 * Retrieves the CATNurbsToolsInfo.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.</dl>
 * Use @href CATNurbsToolsInfo include to see all information values.
 */
  virtual CATNurbsToolsInfo GetInfo() = 0;

  /**
 * Computes an estimation of the deformation value.
 * @param oDeformation
 * The deformation is the max distance between the input surface and current surface.
 * It can be called several times and before @href CATICGMNurbsSurfaceTools#Run.
 * @param oParamValueU
 * The parameter value along U where the maximum deformation is computed.
 * @param oParamValueV
 * The parameter value along V where the maximum deformation is computed.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetDeformation(
    double &oDeformation,
    double &oParamValueU,
    double &oParamValueV) = 0;

  /**
 * Checks the current surface.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_InternalContinuity</tt> <dd>The internal continuity must be greater or equal to C2.
 *     <dt><tt>Info_ConfusedKnots     </tt> <dd>Two knots are coincident.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo Check() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMNurbsSurfaceTools(); // -> delete can't be called
};

/**
 * Creates an operator to manipulate a Nurbs Surface.
 * @param iFactory
 * The pointer to the geometry factory needed for the creation of the result surface.
 * @param iSurface
 * The pointer to the Nurbs Surface to be manipulated.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMNurbsSurfaceTools *CATCGMCreateNurbsSurfaceTools(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface);

#endif /* CATICGMNurbsSurfaceTools_h_ */
