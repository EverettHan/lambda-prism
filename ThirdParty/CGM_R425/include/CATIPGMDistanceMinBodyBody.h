#ifndef CATIPGMDistanceMinBodyBody_h_
#define CATIPGMDistanceMinBodyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class BodyFDM;
class CATDistanceMinBodyFDM;
class CATPoint;
class CATCell;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDistanceMinBodyBody;

///////////////////////////////////////////////////////////////
// This API has been deprecated. 
// Please use the new API instead:
//    CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
///////////////////////////////////////////////////////////////


/**
 * @deprecated V5R27-R419 CATICGMDistanceBodyBody
 *
 * This API has been deprecated. Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 *
 * Class defining the operator that computes the minimum distance between two bodies.
 * To use the operator:
 * <ul><li>Create it with the <tt>CATPGMCreateDistanceMinTopo</tt> global function,
 * <li>Set parameters to tune its use (<tt>ADVANCED</tt> mode),
 * <li>Run the operator (<tt>ADVANCED</tt> mode),
 * <li>Retrieve the results with the <tt>Get</tt> methods, 
 * <li>If needed, change an input body and rerun the modified operator (<tt>ADVANCED</tt> mode),
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 * Note: If the operator is used in <tt>BASIC</tt> mode, the operation is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * But you cannot tune the parameters, nor reuse it in another run with other input bodies.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceMinBodyBody();

  /**
		 * Defines a maximum distance between the two bodies (<tt>ADVANCED</tt> mode).
		 * @param iDistance
		 * The value of the distance known to be an upper bound of the distance between the 
		 * two bodies. This can optimize the performance of the computation.
		 */
  virtual void SetDistanceMax(double iDistance) = 0;

  /**
		 * Asks for the computation of the points realizing the minimum distance (<tt>ADVANCED</tt> mode).
		 * This method is to be used prior to calling the GetSupportCells method.
		 *<br>The life cycle of the points is managed by the operator: they are deleted at the
		 * operator deletion, or when another computation is asked for 
		 * (@href CATIPGMDistanceMinBodyBody#ReplaceBody. This is not applicable to the GetPoints method.
		 * Points retrieved by using GetPoints must be deleted when they become useless.
		 * @param iTrueOrFalse
		 * The computation mode.
		 * <br><b>Legal values</b>:
		 * <tt>TRUE</tt> if the points must be computed, <tt>FALSE</tt> otherwise.
		 */
  virtual void SetPointComputationMode(CATBoolean iTrueOrFalse) = 0;

  /** 
		* Defines another computation (<tt>ADVANCED</tt> mode).
		* <br>If points were computed, they are deleted.
		* @param iBodyToReplace
		* The pointer to the body to be replaced in the definition of the operator.
		* @param iNewBody
		* The pointer to the body replacing <tt>iBodyToReplace</tt> in this operator.
		*/
  virtual void ReplaceBody(CATBody *iBodyToReplace, CATBody *iNewBody) = 0;

  //-------------------------------------------------------------------------
  // Run and Result Access
  //-------------------------------------------------------------------------
  /**
		 * Computes the distance (<tt>ADVANCED</tt> mode).
		 */
  virtual int Run() = 0;

  /**
		 * Returns the computed minimum distance between the two bodies.
		 * @return
		 * The minimum distance. If the distance could not be computed, returns <tt>-1</tt>.
		 */
  virtual double GetDistance() = 0;

  /**
		 * Returns the points realizing the minimum distance (<tt>ADVANCED</tt> mode).
		 * <br>Useless points must be deleted. Their life cycle is not managed by the operator.
		 * @param oPoint1
		 * The pointer to the point on the first body.
		 * @param oPoint2
		 * The pointer to the point on the second body.
		 */
  virtual void GetPoints(CATPoint *&oPoint1, CATPoint *&oPoint2) = 0;

  /**
		 * Returns the cells on which are the points realizing the minimum distance (<tt>ADVANCED</tt> mode).
		 * The SetPointComputationMode method should be called before, otherwise NULL pointers are returned.
		 * <br>The life cyle of the cells is managed by the operator.
		 * @param oCell1
		 * The pointer to the cell on the first body.
		 * @param oCell2
		 * The pointer to the cell on the second body.
		 */
  virtual void GetSupportCells(CATCell *&oCell1, CATCell *&oCell2) = 0;

  /**
		 * Returns the computation mode (<tt>ADVANCED</tt> mode).
		 * @return
		 * The computation mode.
		 * <br><b>Legal values</b>:
		 * <tt>TRUE</tt> if the points must be computed, <tt>FALSE</tt> otherwise.
		 */
  virtual CATBoolean GetPointComputationMode() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceMinBodyBody(); // -> delete can't be called
};

/**
 * @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinBodyBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATIPGMDistanceMinBodyBody_h_ */
