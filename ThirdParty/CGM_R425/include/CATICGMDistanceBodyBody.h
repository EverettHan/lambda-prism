#ifndef CATICGMDistanceBodyBody_h_
#define CATICGMDistanceBodyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCell;
class CATDomain;
class CATGeoFactory;
class CATMathPoint;
class CATPoint;
class CATTopData;
class CATLISTP(CATBody);
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDistanceBodyBody;

/**
 * Class defining an operator that computes the distance between two bodies, two groups of bodies  
 * or two groups of cells in the same or different bodies.
 * <ul>
 *     <li> A <tt>CATICGMDistanceBodyBody</tt> operator is created with the <tt>CATCGMCreateDistanceBodyBodyOp</tt> global function.
 *     <li> It is the user's responsibility to release the operator after it has been used.
 *     <li> The results are retrieved by the <tt>Get</tt> methods.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMDistanceBodyBody: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDistanceBodyBody();

  //------------------------------------------------------------------------------------------------
  // CAA Methods 
  //------------------------------------------------------------------------------------------------
  /** 
	* Returns the distance between two bodies.
	* @return 
	* The distance. 
	*/
  virtual double GetDistance() = 0;

  /** 
	* Returns the <tt>CATMathPoint</tt> positions representing the locations of closest approach on each body.
    * @param oPoint1
    * The closest point on the first body.
    * @param oPoint2
    * The closest point on the second body.
	*/
  virtual void GetPoints(CATMathPoint &oPoint1, CATMathPoint &oPoint2) = 0;

  /**
	* Returns the <tt>CATPoint</tt> objects representing the locations of closest approach on each body.
    * The points, once returned, are owned by the caller.
    * @param oPoint1
    * The closest point on the first body.
    * @param oPoint2
    * The closest point on the second body.
	*/
  virtual void GetPoints(CATPoint *&oPoint1, CATPoint *&oPoint2) = 0;

  /** 
	* Returns the <tt>CATCell<tt> objects on which the closest point for each body is found.
    * @param oCell1
    * The support cell on the first body.
    * @param oCell2
    * The support cell on the second body.
	*/
  virtual void GetSupportCells(CATCell *&oCell1, CATCell *&oCell2) = 0;

  /** 
	* Set Reference Point 
	* The reference point is used to specify the nearest solution when there are multiple solutions. 
	* If not set, position (0,0,0) will be used instead.
	* @param iRefPoint
	* The reference point.
	*/
  virtual void SetReferencePoint(const CATMathPoint &iRefPoint) = 0;

  /** 
	* Returns the reference point. 
	* @param oRefPoint
    * The reference point.
	*/
  virtual void GetReferencePoint(CATMathPoint &oRefPoint) = 0;

  /** 
	* Defines an upper bound of the distance between the two bodies. 
	* If known, this can be used to optimize the performance of the computation.
	* @param iDistanceMax
	* The value of the upper bound.
	*/
  virtual void SetDistanceMax(double iDistanceMax) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDistanceBodyBody(); // -> delete can't be called
};

//------------------------------------------------------------------------------------------------
// CAA Create Methods 
//------------------------------------------------------------------------------------------------
/**
 * Creates an operator to compute the distance between body1 and body2.
 * Both bodies must belong to the same factory.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the <tt>CATTopData</tt> defining the software configuration and the journal.  
 * @param iBody1
 * The pointer to the first body.
 * @param iBody2
 * The pointer to the second body.
 * @return
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2);

/**  
 * Creates an operator to compute the distance between two groups of cells.
 * <li><b>Notes:</b>
 * <ul>
 *     <li> All the cells must belong to the same factory.
 *     <li> The cells within a group may or may not be topologically connected.
 *     <li> The cells within a group may or may not belong to the same body.
 * </ul>
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the <tt>CATTopData</tt> defining the software configuration and the journal.  
 * @param iCellsList1
 * The list of cells forming the first group.
 * @param iCellsList2
 * The list of cells forming the second group.
 * @return
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATCell) &iCellsList1,
  CATLISTP(CATCell) &iCellsList2);

/**
 * Creates an operator to compute the distance between two groups of bodies.
 * All the bodies must belong to the same factory.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the <tt>CATTopData</tt> defining the software configuration and the journal.  
 * @param iBodiesList1
 * The list of the bodies forming the first group.
 * @param iBodiesList2
 * The list of the bodies forming the second group.
 * @return
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDistanceBodyBody *CATCGMCreateDistanceBodyBodyOp(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) &iBodiesList1,
  CATLISTP(CATBody) &iBodiesList2);

#endif /* CATICGMDistanceBodyBody_h_ */
