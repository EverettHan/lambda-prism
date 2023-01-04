#ifndef CATICGMBodyFromLengthOnWire_h_
#define CATICGMBodyFromLengthOnWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATMathDef.h"
#include "CATLengthType.h"
#include "CATSkillValue.h"
#include "CATBodyFromLengthOnWireMeasureType.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATWire;
class CATListValCATMathPoint;
class CATLISTP(CATVertex);
class CATLISTV(CATMathVector);

extern ExportedByCATGMModelInterfaces IID IID_CATICGMBodyFromLengthOnWire;

/**
* Class defining an operator to create a point or a series of points at given measures (arc lengths spacings or integrated turning angles) on a Wire.
* <br>
* <br>
* The <tt>CATBodyFromLengthOnWire</tt> operator follows the global frame of the topological
* operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies. The follwing two integral measures are curently supported:
*<ul>
*<li> Arc length spacing specifies the curve length between sample points.
*<li> Integrated turning spacing specifies the total amount the tangent vector changes between sample points. Jumps in 
* the tangent vector between edges are ignored. The expectation is that edge pairs are G1 continuous at vertices.
*<li> The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
*/

class ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMBodyFromLengthOnWire();

  /**
    * Runs the operator.
    * @return
    * <br><b>Legal values</b>: <tt>0</tt> if ok, <tt>1</tt> if failed
    */
  virtual int Run() = 0;

  /**
   * Activates or deactivates the lay-down operation.  If activated, the operator
   * projects the resulting point body upon the specified wire body 
   * if the distance between them is lower than the factory resolution.
   * @param iWireBody
   * The wire body that is the target of the lay-down operation.
   * @param ilaid
   * 0 to turn off lay-down, 1 to turn it on.
   */
  virtual void SetLayDown(CATBody *iWireBody, int ilaid) = 0;

  /**
   * Returns the lay-down setting.
   * @param oLaid
   * 0 if lay-down is turned off, 1 if it is turned on.
   */
  virtual void GetLayDown(int &oLaid) = 0;

 /**
  * Returns the point body computed by the run.  Call this method
  * after the <tt>Run</tt> method has been called.
  */
  virtual CATBody *GetResult() = 0;

#ifdef CATIACGMR418CAA
  /*
  * Returns the resulting locations of point(s) in 3D.
  * The operator must be run prior to the use of this method
  * @return
  * The <tt>oLocations</tt> list of sampled points.
  */
  virtual void GetResult( CATLISTV(CATMathPoint) & oLocations ) const = 0; 

#endif /* CATIACGMR418CAA */

#ifdef CATIACGMR419CAA
  /**
  * Activates or deactivates the computation of tangents at the result vertices.  
  * If activated, the operator evaluates the tangent on the input wire, 
  * or at its extremity in case of extrapolation.
  * @param iActivateTangentMode
  * FALSE to turn off the option, TRUE to turn it on.
  */
  virtual void SetTangentComputation(CATBoolean iActivateTangentMode) = 0;

  /**
  * Returns the result body with tangents (else returns NULL) associated to its vertices, according to the wire orientation.
  * SetTangentComputation(TRUE) then Run() has to be called prior to the use of this method
  * @return
  * The <tt>oResultVertices</tt> list of sampled vertices in the Result CATBody.
  * The <tt>oTangents</tt> list of normalized tangents associated to the vertices.
  * The <tt>oLocations</tt> optional list of vertices locations in 3D.
	* The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
	*/
  virtual CATBody *GetResultWithTangents(
    CATLISTP(CATVertex) &oResultVertices,
    CATLISTV(CATMathVector) &oTangents,
    CATLISTV(CATMathPoint) *oLocations = NULL) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMBodyFromLengthOnWire(); // -> delete can't be called
};

/**
 * Creates a CATICGMBodyFromLengthOnWire operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATWire *aWire,
  CATVertex *aVertex,
  CATLength aDistance,
  CATLengthType iType = CATLengthType_ABSOLUTE_L,
  CATSkillValue iModev = BASIC);

/**
 * Creates a CATICGMBodyFromLengthOnWire operator.
 * @param iFactory
 *    The factory of the geometry. 
 * @param iTopData
 *    The pointer to the data defining the software configuration and the journal.
 *    If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iSamplingArcLengths
 *    Variable arc lengths between the sample points on the wire. The wire will be sampled at
 *    consecutive increments defined in iSamplingArcLengths array starting from the 
 *    ReferenceVertex in the direction of wire orientation.
 * @param iWire
 *    The wire domain to be sampled.
 * @param iReferenceVertex
 *    The reference vertex where the sampling will start.
 * @param iReverseSamplingDirection
 *    Reverse the sampling direction (with respect to the wire orientation)
 * @param iRelativeTolerance
 *    Specifies the relative tolerance (a multiplicative factor of the factory resolution) 
 *    used internally in the integration scheme to determine sample point positions on the
      wire. Lower tolerance values may result in a higher precision of the computation at 
 *	  the expense of a slower performance. The legal values are between 10^-4 and 1.
 * @return [out, IUnknown#Release]
 *	  The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
  CATGeoFactory* iFactory,
  CATTopData* iTopData,
  const CATListOfDouble &iSamplingArcLengths,
  CATWire* iWire,
  CATVertex* iReferenceVertex,
  CATBoolean iReverseSamplingDirection = FALSE,
  double iRelativeTolerance = 0.1 );

/**
 * Creates a CATICGMBodyFromLengthOnWire operator.
 * @param iFactory
 *    The factory of the geometry. 
 * @param iTopData
 *    The pointer to the data defining the software configuration and the journal.
 *    If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
  * @param iSamplingArcLength
 *    The arc length between the sample points on the wire. The wire will be sampled at 
 *    iSamplingArcLength increments starting from the ReferenceVertex in the direction of 
 *    wire orientation.
 * @param iWire
 *    The wire domain to be sampled.
 * @param iReferenceVertex
 *    The reference vertex where the sampling will start.
 * @param iReverseSamplingDirection
 *    Reverse the sampling direction (with respect to the wire orientation)
 * @param iRelativeTolerance
 *    Specifies the relative tolerance (a multiplicative factor of the factory resolution) 
 *    used internally in the integration scheme to determine sample point positions on the
      wire. Lower tolerance values may result in a higher precision of the computation at 
 *	  the expense of a slower performance. The legal values are between 10^-4 and 1.
 * @return [out, IUnknown#Release]
 *	  The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
  CATGeoFactory* iFactory,
  CATTopData* iTopData,
  double iSamplingArcLength,
  CATWire* iWire,
  CATVertex* iReferenceVertex,
  CATBoolean iReverseSamplingDirection = FALSE,
  double iRelativeTolerance = 0.1 );

/**
 * Creates a CATICGMBodyFromLengthOnWire operator.
 * @param iFactory
 *    The factory of the geometry. 
 * @param iTopData
 *    The pointer to the data defining the software configuration and the journal.
 *    If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iSamplingMeasures
 *    Variable measures (arc lengths spacings or integrated turning angles) between the sample points on the wire. 
 *    The wire will be sampled at consecutive increments defined in iSamplingArcMeasures array starting from the 
 *    ReferenceVertex in the direction of wire orientation.
 * @param iMeasureType
 *    Sampling measure type. Sets the operator to either use ArcLength or TurningAngle as the integral measure. 
 * @param iWire
 *    The wire domain to be sampled.
 * @param iReferenceVertex
 *    The reference vertex where the sampling will start.
 * @param iReverseSamplingDirection
 *    Reverse the sampling direction (with respect to the wire orientation)
 * @param iRelativeTolerance
 *    Specifies the relative tolerance, a multiplicative factor of factory length or factory angular resolution
 *    used by this operator internally in the integration scheme to determine sample point positions on the
 *    wire. Lower tolerance values may result in a higher precision of the computation at the expense of a 
 *    slower performance.
 * @return [out, IUnknown#Release]
 *	  The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATListOfDouble &iSamplingMeasures,
  CATBodyFromLengthOnWireMeasureType iMeasureType,
  CATWire *iWire,
  CATVertex *iReferenceVertex,
  CATBoolean iReverseSamplingDirection = FALSE,
  double iRelativeTolerance = 0.1);

/**
 * Creates a CATICGMBodyFromLengthOnWire operator.
 * @param iFactory
 *    The factory of the geometry. 
 * @param iTopData
 *    The pointer to the data defining the software configuration and the journal.
 *    If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
  * @param iSamplingMeasure
 *    Measure interval (arc lengths spacings or integrated turning angles) between the sample points on the wire. 
 *    The wire will be sampled at iSamplingMeasure increments starting from the ReferenceVertex in the direction of 
 *    wire orientation.
 * @param iMeasureType
 *    Sampling measure type. Sets the operator to either use ArcLength or TurningAngle as the integral measure. 
 * @param iWire
 *    The wire domain to be sampled.
 * @param iReferenceVertex
 *    The reference vertex where the sampling will start.
 * @param iReverseSamplingDirection
 *    Reverse the sampling direction (with respect to the wire orientation)
 * @param iRelativeTolerance
 *    Specifies the relative tolerance, a multiplicative factor of factory length or factory angular resolution
 *    used by this operator internally in the integration scheme to determine sample point positions on the
 *    wire. Lower tolerance values may result in a higher precision of the computation at the expense of a 
 *    slower performance.
 * @return [out, IUnknown#Release]
 *	  The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  double iSamplingMeasure,
  CATBodyFromLengthOnWireMeasureType iMeasureType,
  CATWire *iWire,
  CATVertex *iReferenceVertex,
  CATBoolean iReverseSamplingDirection = FALSE,
  double iRelativeTolerance = 0.1);

#endif /* CATICGMBodyFromLengthOnWire_h_ */
