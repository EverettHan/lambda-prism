#ifndef CATIPGMDistanceBodyBody_h_
#define CATIPGMDistanceBodyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATSkillValue.h"
#include "CATDistanceBodyBodyDef.h"
#include "CATPGMCreateDistanceBodyBody.h" // CPT on May 13th 2014: to be removed

class CATBody;
class CATCell;
class CATGeoFactory;
class CATMathPoint;
class CATPoint;
class CATTopData;
class CATDomain;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDistanceBodyBody;

/**
 * Class defining an operator that computes the distance between two bodies, two groups of bodies  
 * or two groups of cells in the same or different bodies.
 * <ul>
 *     <li> Create it with the <tt>CATPGMCreateDistanceBodyBody</tt> global function,
 *     <li> Set parameters to tune its use (<tt>ADVANCED</tt> mode only),
 *     <li> Run the operator (<tt>ADVANCED</tt> mode only),
 *     <li> Retieve the results with the <tt>Get</tt> methods.
 *     <li> It is the user's responsibility to release the operator after it has been used.
 * </ul>
 * Note: 
 * 1. If the operator is used in <tt>BASIC</tt> mode, the operation is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * Use delete to remove the operator
 * 2. CATIPGMDistanceBodyBody assumes that the input bodies belong to the same factory (CATGeoFactory).
 * If distance is to be found between bodies belong to different factories, then CATIPGMDistanceBodyBody2 
 * should be used instead.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceBodyBody();

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

  /** @nodoc
	* Replaces a previous body with a new body for another computation.
	  * If a result with the previous body has been computed, then it is deleted.
	* The new results will be available after running the operator.
	  * @param iBodyToReplace
	  * The pointer to the body to be replaced in the definition of the operator.
	  * @param iNewBody
	  * The pointer to the body replacing <tt>iBodyToReplace</tt> in this operator.
  */
  virtual void ReplaceBody(CATBody *iBodyToReplace, CATBody *iNewBody) = 0;

  /** 
	* Defines an upper bound of the distance between the two bodies. 
	* If known, this can be used to optimize the performance of the computation.
	  * @param iDistanceMax
	* The value of the upper bound.
  */
  virtual void SetDistanceMax(double iDistanceMax) = 0;

  //------------------------------------------------------------------------------------------------
  // Non-CAA Methods 
  //------------------------------------------------------------------------------------------------
  /** @nodoc 
	* Defines an upper bound of distance between the two bodies.
	  * @param iDistanceUpperBound
	  * The value of the distance known to be an upper bound of the distance between the 
	  * two bodies. This can optimize the performance of the computation.We keep this existing method.
    * This Method is called by SetDistanceMax() internally.
  */
  virtual void SetDistanceUpperBound(double iDistanceUpperBound) = 0;

  /** @nodoc 
	* Sets the target cells.
		* @param iCellsOnBody1
    * Target Cells on First Body 
    * @param iCellsOnBody2
    * Target Cells on Second Body 
		* If target cells are set, only those cells will be used for computation of distance 
	*/
  virtual void SetTargetCells(
    CATLISTP(CATCell) &iCellsOnBody1,
    CATLISTP(CATCell) &iCellsOnBody2) = 0;

  /** @nodoc 
	* Sets the type of distance as Maximum, Minimum or Deviation		
	*/
  virtual void SetDistanceType(CATDistanceBodyBodyType iType) = 0;

  /** @nodoc 
	* Sets the mode of distance as Directional, Perpendicular or General 
	*/
  virtual void SetDistanceMode(CATDistanceBodyBodyMode iMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceBodyBody(); // -> delete can't be called
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
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
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
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
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
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyOp(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) &iBodiesList1,
  CATLISTP(CATBody) &iBodiesList2);

//------------------------------------------------------------------------------------------------
// Non-CAA Create Methods 
//------------------------------------------------------------------------------------------------
/**
 * @nodoc 
 * Creates an operator for computing distance from body1 to body2. Distance type can be Deviation, Maximum, Minimum.
 * Distance mode can be Perpendicular, Directional, General 
 * The input surfaces (or volume) must be G1 continuous.
 * You should set Target Cells to calculate appropriate distance in expected portion of two bodies. You recover appropriate
 * points on two bodies.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal.  
 * @param iBody1
 * The pointer to the first body.
 * @param iBody2
 * The pointer to the second body.
 * @param iType
 * iType = 0 (Deviation Distance) 
 * iType = 1 (Maximum Distance) 
 * iType = 2 (Minimum Distance)
 * @param iMode
 * iMode = 0 (Perpendicular Mode)
 * iMode = 1 (Directional Mode)
 * iMode = 2 (General Mode)
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iMODE = BASIC);

/**
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCell *iCell1,
  CATCell *iCell2,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iMODE = BASIC);

/**
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATDomain *iDomain1,
  CATDomain *iDomain2,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iMODE = BASIC);

/**
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBodyLight(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATIPGMDistanceBodyBody_h_ */
