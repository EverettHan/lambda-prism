#ifndef CATIPGMDistancePointBody_h_
#define CATIPGMDistancePointBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDistanceSignMode.h"
#include "ListPOfCATCell.h"
#include "CATListOfCATCells.h"

class CATBody;
class CATCell;
class CATMathPoint;
class CATPoint;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDistancePointBody;

/**
 * Class defining the operator for finding the minimum distance between 
 * a <code>CATMathPoint</code> and a <code>CATBody</code>.
 * To use the operator:
 * <ul>
 * <li>Create it with the <code>CATPGMCreateDistancePointBody</code> global function, giving the <code>CATBody</code> as input,
 * <li>Call SetPoint method with a @href CATMathPoint,
 * <li>Run the operator,
 * <li>Retrieve the results with the GetResult... methods
 * </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDistancePointBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDistancePointBody();

  /**
   * Set the input point.
   * <br>Note: If you want to find the distance of more than one points from the same body,
   *   then to get better performance, you can call SetPoint and Run as many times on 
   *   the same operator, rather than creating a new operator every time for each point.
   * @param iPoint
   *   The point from which the minimum distance to the given body is to be found
   */
  virtual void SetPoint(const CATMathPoint &iPoint) = 0;

  /**
   * Get the input point.
   * @param oPoint
   *   The point (that has been set using SetPoint method) from which the minimum 
   *   distance to the given body is to be found
   */
  virtual void GetPoint(CATMathPoint &oPoint) = 0;

  /**
   * Define the sign mode. The default is "Signed" mode. 
   * <code>CATDistanceSignModeDefault</code> is interpreted as <code>CATDistanceSignModeSigned</code>.
   * See the documentation of @href CATDistanceSignMode to know more about the different sign modes
   * available and their meanings.
   * @param iSignMode
   *   Sign mode to be defined
   * @see CATDistanceSignMode
   */
  virtual void SetSignMode(CATDistanceSignMode iSignMode) = 0;

  /**
   * Get the sign mode.
   * <code>CATDistanceSignModeDefault</code> is interpreted as <code>CATDistanceSignModeSigned</code>.
   * See the documentation of @href CATDistanceSignMode to know more about the different sign modes
   * @return
   *   Sign mode defined in the operator
   * @see CATDistanceSignMode
   */
  virtual CATDistanceSignMode GetSignMode() = 0;

  /**
  * Defines an upper bound of distance between the point and the body.
  * @param iDistanceUpperBound
  * The value of the distance known to be an upper bound of the distance between the point and the body.
  * This can optimize the performance of the computation.
  */
  virtual void SetDistanceUpperBound(double iDistanceUpperBound) = 0;

  /**
   * Request normal projection information BEFORE RUN.
   * This may impact performance of the operator.
   * This should only be used in conjunction with GetNormalProjectionInfo.
   */
  virtual void EnableNormalProjectionInfo() = 0;

  /**
   * Retrieve normal projection information AFTER RUN.
   * @return
   *   E_FAIL  : if computation failed or was not requested
   *   S_OK    : if computation was successful
   */
  virtual HRESULT GetNormalProjectionInfo(
    CATBoolean &oIsResultNormalProjection) = 0;

  /**
   * Runs this operator.
   * <br>Note: You must call SetPoint before Run.
   * @return 
   *   0 if the operator runs successfully and 1 otherwise.
   */
  virtual int Run() = 0;

  /**
   * Get the result distance.
   * @description
   *   Returns the minimum distance between the given point and body calculated by the operator in the last run.
   *   <br>
   *   <ul>
   *   <li>If the sign mode is <code>CATDistanceSignModeSigned</code>, then result distance 
   *   may be negative. If it is negative, then it means that the point is inside the body and 
   *   the absolute value gives the minimum distance of the point from the shell of the body.
   *   <li>If the sign mode is <code>CATDistanceSignModeZero</code>, and if the point is inside 
   *   the body, then result distance value is returned is zero.
   *   <li>If the sign mode is <code>CATDistanceSignModeUnsigned</code>, and if the point is inside 
   *   the body, then result distance value is always non-negative and is equal to the distance of
   *   the point from the shell of the body.
   *   </ul>
   * @return
   *   Result distance between the point and the body.
   */
  virtual double GetResultDistance() const = 0;

  /** 
   * Get the result <code>CATMathPoint</code>.
   * @description
   *   Returns the result @href CATMathPoint on the given body (calculated by the operator in the last run).
   * @param oPoint
   *   The result @href CATMathPoint on the given body.
	 */
  virtual void GetResultMathPoint(CATMathPoint &oMathPoint) const = 0;

  /** 
   * Get the result <code>CATCell</code>.
   * @description
   *   Returns the @href CATCell in given body on which the result point lies (calculated by the operator in the last run).
   *   This @href CATCell can be @href CATFace, @href CATEdge or @href CATVertex. It can also be @href CATVolume, if the
   *   sign mode is <code>CATDistanceSignModeZero</code> and if the point is found to be inside the volume.
   * @return
   *   The cell in the given body on which the result point lies.
	 */
  virtual CATCell *GetResultCell() const = 0;

  /** 
   * Get the result <code>CATPoint</code>.
   * @description
   *   Returns the result @href CATPoint on the given body calculated by the operator in the last run.
   * @return
   *   The result @href CATPoint on the given body.
   *   This gives the result in the context of the result cell.
   *     <ol>
   *     <li> If the result cell is a @href CATFace,   then the returned @href CATPoint will be of type @href CATPointOnSurface
   *     <li> If the result cell is a @href CATEdge,   then the returned @href CATPoint will be of type @href CATPointOnCurve
   *     <li> If the result cell is a @href CATVertex, then the returned @href CATPoint will be of type @href CATCartesianPoint
   *     <li> If the result cell is a @href CATVolume, then the returned @href CATPoint will be of type @href CATCartesianPoint
   *     </ol>
   *   <br>Note: The returned @href CATPoint is created in the same container as the given @href CATBody and it is owned by the caller.
   *   A new point is created each time this method is called. After use, call the @href CATICGMContainer#Remove method.
	 */
  virtual CATPoint *GetResultPoint() const = 0;

  /** @nodoc */
  virtual void ActivateMultipleUse(CATBoolean iValue) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistancePointBody(); // -> delete can't be called
};

/**
 * Creates an operator for computing the minimum distance from a point to a body.
 * @param iBody
 * The body whose distance from one or more points is to be found.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. Notice that here, the journal is
 * not filled, because there is no body creation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistancePointBody *CATPGMCreateDistancePointBody(
  CATBody *iBody,
  CATTopData *iData);

/**
 * Creates an operator for computing the minimum distance from a point to a list of CATCells defining one input body.
 * @param iBodyCells
 * The list of cells whose distance from one or more points is to be found.
 * All these input cells have to belong to the same CGM Container
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. Notice that here, the journal is
 * not filled, because there is no body creation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistancePointBody *CATPGMCreateDistancePointBody(
  const CATLISTP(CATCell) & iBodyCells, 
  CATTopData              * iTopData);

#endif /* CATIPGMDistancePointBody_h_ */
