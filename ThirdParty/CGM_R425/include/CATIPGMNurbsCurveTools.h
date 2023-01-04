#ifndef CATIPGMNurbsCurveTools_h_
#define CATIPGMNurbsCurveTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATNurbsToolsInfo.h"

class CATCurve;
class CATGeoFactory;
class CATKnotVector;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMNurbsCurveTools;

/**
 * Class used to manipulate a Nurbs curve. 
 */
class ExportedByCATGMModelInterfaces CATIPGMNurbsCurveTools: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMNurbsCurveTools();

  /**
 * @nodoc
 * Sets the tolerance of minimal 3D size for the geometric elements created.
 * @param iTolKnotConfusion
 * Specifies the tolerance.
 * <br>By default, the tolerance is the resolution.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 * <dl><dt><tt>Info_InvalidTolConfusion</tt> <dd>The confusion tolerance is lower than the resolution. The resolution is used.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo SetTolKnotConfusion(
    const double iTolKnotConfusion = 0.) = 0;

  /** 
 * @nodoc
 * Sets the max degree authorized in the SetDegree method.
 * Max degree must be => 3 and <=15
 * default value (for CAA) = 11
 * 
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo SetMaxDegree(const int iDegree) = 0;

  /**
 * Retrieves the curve degree.
 * @param oDegree
 * The degree.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include for the list of information values.
 */
  virtual CATNurbsToolsInfo GetDegree(int &oDegree) = 0;

  /**
 * Retrieves the number of knot values of the Nurbs curve.
 * @param oNumberOfKnots
 * The number of distinct knot values.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetNumberOfKnots(int &oNumberOfKnots) = 0;

  /**
 * Retrieves the number of control points of the Nurbs curve.
 * @param oNumberOfControlPoints
 * The number of control points.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetNumberOfControlPoints(
    int &oNumberOfControlPoints) = 0;

  /**
 * Retrieves a knot value from its rank.
 * @param iKnotRank
 * The rank of the knots. The rank starts from 1.
 * @param oKnotValue
 * The parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than number of knots.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo KnotRankToKnotValue(
    const int iKnotRank,
    double &oKnotValue) = 0;

  /**
 * Retrieves the rank of a knot from its value.
 * The parameter corresponds to a knot if the length between the input parameter and the
 * knot value is lower than TolKnotConfusion.
 * @param iKnotValue
 * The parameter value of the knot.
 * @param oKnotRank
 * The rank of the knot. The rank starts from 1.
 * if the parameter value not corresponding to a knot, iKnotRank = 0;
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
  virtual CATNurbsToolsInfo KnotValueToKnotRank(
    const double iKnotValue,
    int &oKnotRank) = 0;

  /**
 * Inserts a knot.
 * @param iKnotValue
 * The parameter value of the new knot.
 * @param iMultiplicity
 * The multiplicity value of the new knot (by default, the multiplicity is the one 
 * corresponding to a C2 continuity). 
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than last knot value.
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo KnotInsertion(
    const double iKnotValue,
    const int iMultiplicity = 0) = 0;

  /**
 * Inserts several knots.
 * @param iNumberOfKnotsToInsert
 * The number of knots to be inserted.
 * @param iKnotValues
 * The array of parameters value of the new knots.
 * @param iMultiplicities
 * The array of multiplicities value of the new knots.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits </tt> <dd>Input value is lower than first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all information values.  
 */
  virtual CATNurbsToolsInfo MultipleKnotInsertion(
    const int iNumberOfKnotsToInsert,
    const double *iKnotValues,
    const int *iMultiplicities = 0) = 0;

  /**
 * Removes a knot.
 * This method deforms the curve. Use @href CATIPGMNurbsCurveTools#GetDeformation to compute this deformation
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits</tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 *     <dt><tt>Error_ExtremityKnot    </tt> <dd>An extremity knot cannot be removed.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo KnotRemoval(const int iKnotRank) = 0;

  /**
 * Replaces a knot.
 * This method deforms the curve. Use @href CATIPGMNurbsCurveTools#GetDeformation to compute this deformation
 * @param iKnotRank
 * The rank of the knot to be replaced. The rank starts from 1.
 * @param iKnotNewValue
 * The new parameter value of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                 </tt> <dd>No info. It is OK.
 *     <dt><tt>Error_KnotRankOutLimits </tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 *     <dt><tt>Error_ExtremityKnot     </tt> <dd>An extremity knot cannot be modified.
 *     <dt><tt>Error_KnotValueOnAKnot  </tt> <dd>The new knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>The new value is lower than the first knot value or greater than the last knot value.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all information values.
 */
  virtual CATNurbsToolsInfo KnotReplace(
    const int iKnotRank,
    const double iKnotNewValue,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Imposes the parameterization of another curve.
 * This method deforms the curve. Use @href CATIPGMNurbsCurveTools#GetDeformation to compute this deformation.
 * @param iCurve
 * The curve whose parameterization is to be kept.
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
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Input pointer of curve is null.
 *     <dt><tt>Error_InputCurveNotNurbs</tt> <dd>Input curve is not a Nurbs.
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>Input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all information values. 
 */
  virtual CATNurbsToolsInfo ImposeParametrization(
    CATCurve *iCurve,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Modifies the knot vector of a curve.
 * This method deforms the curve. Use @href CATIPGMNurbsCurveTools#GetDeformation to compute this deformation
 * @param iNewKnotVector
 * The new knot vector.
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
 *     <dt><tt>Error_InputPtrNull      </tt> <dd>Input pointer of new knot vector is null
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greatest than 2
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal nb of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all values of informations
 */
  virtual CATNurbsToolsInfo ChangeKnotVector(
    const CATKnotVector *iNewKnotVector,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Modifies the multiplicity of a knot.
 * This method deforms the curve if the new multiplicity is lower than the old multiplicity. 
 * Use @href CATIPGMNurbsCurveTools#GetDeformation to compute this deformation.
 * @param iKnotRank
 * The rank of the knot to be removed. The rank starts from 1.
 * @param iMultiplicity
 * The new multiplicity of the knot.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                  </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_NoModification      </tt> <dd>No modification: new multiplicity is equal to former ultiplicity.
 *     <dt><tt>Error_InvalidMultiplicity</tt> <dd>The input multiplicity is lower than 1 or greater than Degree-2.
 *     <dt><tt>Error_KnotRankOutLimits  </tt> <dd>The input rank is lower than 1 or greater than the number of knots.
 *     <dt><tt>Error_ExtremityKnot      </tt> <dd>An extremity knot cannot be modified.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values. 
 */
  virtual CATNurbsToolsInfo SetMultiplicity(
    const int iKnotRank,
    const int iMultiplicity) = 0;

  /**
 * Splits the curve.
 * @param iStartKnotValues
 * The new start value of the curve.
 * @param iEndKnotValues
 * The new end value of the curve.
 * @return
 * The information value.
 *     <dt><tt>Info_KnotValueOnAKnot   </tt> <dd>The input knot value is corresponding to an existing knot.
 *     <dt><tt>Error_KnotValueOutLimits</tt> <dd>The value is lower than the first knot value or greater than the last knot value.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo ActiveSplit(
    const double iStartKnotValues,
    const double iEndKnotValues) = 0;

  /**
 * Inverts the curve.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.
 *</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo Invert() = 0;

  /**
 * Modifies the curve degree.
 * @param iDegree
 * The new curve degree.
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
 *     <dt><tt>Error_InvalidDegree     </tt> <dd>The input degree is lower than 3 (1 in single-arc case) or greater than the MaxDegree (11).
 *     <dt><tt>Error_InvalidContinuity </tt> <dd>The input continuity is lower than 0 or greater than 2.
 *     <dt><tt>Error_UncompContinuities</tt> <dd>2 + startcontinuity + endcontinuity must be lower or equal to the number of control points.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.  
 */
  virtual CATNurbsToolsInfo SetDegree(
    const int iDegree,
    const int iLeftContinuity = 0,
    const int iRightContinuity = 0) = 0;

  /**
 * Runs <tt>this</tt> operator.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> 0 </tt> <dd>It is OK.
 *     <dt><tt> 1 </tt> <dd>Error
 *     <dt><tt>100</tt> <dd>Fatal Error
 * </dl>
 * If an error has occurred, use @href CATNurbsCurveTools#GetInfo for more information.
 */
  virtual int Run() = 0;

  /**
 * Returns the new curve computed by <tt>this</tt> operator.
 * @return
 * The pointer of the new curve (0 if an error has occurred, use @href CATIPGMNurbsCurveTools#GetInfo for more information).
 */
  virtual CATCurve *GetResult() = 0;

  /**
 * Retrieves the CATNurbsToolsInfo.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetInfo() = 0;

  /**
 * Computes an estimation of the deformation value.
 * @param oDeformation
 * The deformation is the max distance between the input curve and the current curve.
 * It can be called several times and before @href CATIPGMNurbsCurveTools#Run.
 * @param oParamValue
 * The parameter value where the maximum deformation is computed.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK</tt> <dd>No info. It is OK.</dl>
 * Use @href CATNurbsToolsInfo include to see all the information values.
 */
  virtual CATNurbsToolsInfo GetDeformation(
    double &oDeformation,
    double &oParamValue) = 0;

  /**
 * Checks the current curve.
 * @return
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>Info_OK                </tt> <dd>No info. It is OK.
 *     <dt><tt>Info_InternalContinuity</tt> <dd>The internal continuity must be greater or equal to C2.
 *     <dt><tt>Info_ConfusedKnots     </tt> <dd>Two knots are coincident.
 * </dl>
 * Use @href CATNurbsToolsInfo include to see all information values. 
 */
  virtual CATNurbsToolsInfo Check() = 0;

  /** 
 * @nodoc
 * @return
 * The pointer to the current curve.
 */
  virtual CATCurve *GetCurrentCurve() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMNurbsCurveTools(); // -> delete can't be called
};

/**
 * Creates an operator to manipulate a Nurbs curve.
 * @param iFactory
 * The pointer to the geometry factory needed for the creation of the resulting curve.
 * @param iCurve
 * The pointer to the Nurbs curve to be manipulated.
 * @return
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method after use.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMNurbsCurveTools *CATPGMCreateNurbsCurveTools(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve);

#endif /* CATIPGMNurbsCurveTools_h_ */
