#ifndef CATIPGMDistanceBodyBody2Light_h_
#define CATIPGMDistanceBodyBody2Light_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATCollec.h"
#include "CATDistanceBodyBodyDef.h"
#include "CATSkillValue.h"

class CATBody;
class CATCell;
class CATDomain;
class CATGeoFactory;
class CATMathPoint;
class CATMathTransformation;
class CATPoint;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDistanceBodyBody2;

/**
 * Class defining the operator that computes the general minimum distance between two bodies 
 * belonging to two different factories.
 * The operator requires that the two factories have compatible tolerances
 * To use the operator:
 * <ul><li>Create it with the <tt>CATPGMCreateDistanceBodyBody2</tt> global function,
 * <li>Run the operator (<tt>ADVANCED</tt> mode),
 * <li>Retrieve the results with the <tt>Get</tt> methods, 
 * Note: If the operator is used in <tt>BASIC</tt> mode, the operation is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * Use @href IUnknown#Release to remove the operator
 * Also note that CATIPGMDistanceBodyBody2 assumes that the two factories are different.
 * If distance is to be found between geometries belonging to the same factory, 
 * then CATIPGMDistanceBodyBody should be used instead.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceBodyBody2();

  //------------------------------------------------------------------------------------------------
  // Methods 
  //------------------------------------------------------------------------------------------------
  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

  /** Return Result
    * @return 
    * Distance between two bodies 
  */
  virtual double GetDistance() = 0;

  /** Returns the points realizing the distance result
    * @param oMathPoint1
    * The result CATMathPoint on the first transformed body
    * @param oMathPoint2
    * The result CATMathPoint on the second transformed body
	*/
  virtual void GetResultPoints(
    CATMathPoint &oMathPoint1,
    CATMathPoint &oMathPoint2) = 0;

  /** Returns the respective CATPoints on the untransformed (input) body, 
    * corresponding to the distance result CATMathPoints on transformed body.
    * These CATPoints can be considered links from the result CATMathPoints
    * to the untransformed (input) bodies.
    * The CATPoints returned are owned by the caller.
    * @param oPoint1
    * The result CATPoint on the first untransformed (input) body
    * @param oPoint2
    * The result CATPoint on the second untransformed (input) body
	*/
  virtual void GetLinkPoints(CATPoint *&oPoint1, CATPoint *&oPoint2) = 0;

  /** Returns Support Cells on the untransformed (input) bodies
    * on which the respective link points (returned by GetLinkPoints) would lie.
    * @param oCell1
    * Support Cells on first untransformed (input) body
    * @param oCell2
    * Support Cells on second untransformed (input) body
	*/
  virtual void GetSupportCells(CATCell *&oCell1, CATCell *&oCell2) = 0;

  /** Set Reference Point 
	* @param iRefPoint
    * Reference Point
	* the Reference Point is used to specify the nearest solution while comparing parallele and infinite elements 
	* If the Reference Point is not set, the Space Origin Point (0,0,0) will be used as Reference Point 
	*/
  virtual void SetReferencePoint(const CATMathPoint &iRefPoint) = 0;

  /** Get Reference Point 
	* @param oRefPoint
    * Reference Point
	*/
  virtual void GetReferencePoint(CATMathPoint &oRefPoint) = 0;

  /** Defines the upper bound of distance between the two bodies.
	  * @param iDistanceUpperBound
	  * The value of the distance known to be an upper bound of the distance between the 
	  * two bodies. This can optimize the performance of the computation.
  */
  virtual void SetDistanceUpperBound(double iDistanceUpperBound) = 0;

  /** Set Target Cells. Note that this method cannot be called if this operator 
    * has already been run previously. This is a current limitation.
		* @param iCellsOnBody1
    * Target Cells on First Body 
    * @param iCellsOnBody2
    * Target Cells on Second Body 
		* If target cells are set, only those cells will be used for computation of distance 
	*/
  virtual void SetTargetCells(
    CATLISTP(CATCell) &iCellsOnBody1,
    CATLISTP(CATCell) &iCellsOnBody2) = 0;

  /** Set the Type of Distance as Maximum, Minimum or Deviation		
    * @param iType
    * Type of distance computation required
	*/
  virtual void SetDistanceType(CATDistanceBodyBodyType iType) = 0;

  /** Returns Type of Distance 
    * @return 
		* Type of Distance as Maximum, Minimum or Deviation		
	*/
  virtual CATDistanceBodyBodyType GetDistanceType() = 0;

  /** Set the Mode of Distance as Directional, Perpendicular or General
    * @param iMode
    * Mode of distance computation required
	*/
  virtual void SetDistanceMode(CATDistanceBodyBodyMode iMode) = 0;

  /** Returns Mode of Distance 
    * @return 
		* Mode of Distance as Directional, Perpendicular or General		
	*/
  virtual CATDistanceBodyBodyMode GetDistanceMode() = 0;

  /** Replace a previous body with a new body for another computation
	  * If a result with the previous body has been computed, then it is deleted.
    * Note that this method cannot be called if the previous run was called
    * with TargetCells. This is a current limitation.
	  * @param iBodyToReplace
	  * The pointer to the body to be replaced in the definition of the operator.
	  * @param iFactoryOfNewBody
	  * The pointer to the factory of the geometry of replacing body.
	  * @param iNewBody
	  * The pointer to the body replacing <tt>iBodyToReplace</tt> in this operator.
    * @param iNewBodyTransformation
    * Tranformation to be applied to iNewBody before calculating distance
  */
  virtual void ReplaceBody(
    CATBody *iBodyToReplace,
    CATGeoFactory *iFactoryOfNewBody,
    CATBody *iNewBody,
    const CATMathTransformation &iNewBodyTransformation) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceBodyBody2(); // -> delete can't be called
};

/**
 * Creates an operator for computing general minimum distance from body1 to body2, belonging to different containers.
 * The input surfaces (or volume) must be G1 continuous.
 * @param iData
 * The pointer to the data defining the software configuration and the journal.  
 * @param iFactory1
 * The pointer to the factory of the geometry of first body.
 * @param iBody1
 * The pointer to the first body.
 * @param iBody1Transformation
 * Tranformation to be applied to iBody1 before calculating distance
 * @param iFactory2
 * The pointer to the factory of the geometry of second body.
 * @param iBody2
 * The pointer to the second body.
 * @param iBody2Transformation
 * Tranformation to be applied to iBody2 before calculating distance
 * @param iSkillValue
 * If used with <tt>BASIC</tt> skill value, then distance is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * If used with <tt>ADVANCED</tt> skill value, then one needs to <tt>Run</tt> the operator before
 * accessing the result.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATBody *iBody1,
  const CATMathTransformation &iBody1Transformation,
  CATGeoFactory *iFactory2,
  CATBody *iBody2,
  const CATMathTransformation &iBody2Transformation,
  CATSkillValue iSkillValue = BASIC);

/**
 * Creates an operator for computing general minimum distance from cell1 to cell2, belonging to different containers.
 * The input surfaces (or volume) must be G1 continuous.
 * @param iData
 * The pointer to the data defining the software configuration and the journal.  
 * @param iFactory1
 * The pointer to the factory of the geometry of first cell.
 * @param iCell1
 * The pointer to the first cell.
 * @param iCell1Transformation
 * Tranformation to be applied to iCell1 before calculating distance
 * @param iFactory2
 * The pointer to the factory of the geometry of second cell.
 * @param iCell2
 * The pointer to the second cell.
 * @param iCell2Transformation
 * Tranformation to be applied to iCell2 before calculating distance
 * @param iSkillValue
 * If used with <tt>BASIC</tt> skill value, then distance is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * If used with <tt>ADVANCED</tt> skill value, then one needs to <tt>Run</tt> the operator before
 * accessing the result.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATCell *iCell1,
  const CATMathTransformation &iCell1Transformation,
  CATGeoFactory *iFactory2,
  CATCell *iCell2,
  const CATMathTransformation &iCell2Transformation,
  CATSkillValue iSkillValue = BASIC);

/**
 * Creates an operator for computing general minimum distance from domain1 to domain2, belonging to different containers.
 * The input surfaces (or volume) must be G1 continuous.
 * @param iData
 * The pointer to the data defining the software configuration and the journal.  
 * @param iFactory1
 * The pointer to the factory of the geometry of first domain.
 * @param iDomain1
 * The pointer to the first domain.
 * @param iDomain1Transformation
 * Tranformation to be applied to iDomain1 before calculating distance
 * @param iFactory2
 * The pointer to the factory of the geometry of second domain.
 * @param iDomain2
 * The pointer to the second domain.
 * @param iDomain2Transformation
 * Tranformation to be applied to iDomain2 before calculating distance
 * @param iSkillValue
 * If used with <tt>BASIC</tt> skill value, then distance is directly computed at the 
 * operator creation. So that you directly access the result without <tt>Run</tt>ning the operator.
 * If used with <tt>ADVANCED</tt> skill value, then one needs to <tt>Run</tt> the operator before
 * accessing the result.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATDomain *iDomain1,
  const CATMathTransformation &iDomain1Transformation,
  CATGeoFactory *iFactory2,
  CATDomain *iDomain2,
  const CATMathTransformation &iDomain2Transformation,
  CATSkillValue iMODE = BASIC);

// Functions not supported as of today
/** 
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATBody *iBody1,
  const CATMathTransformation &iBody1Transformation,
  CATGeoFactory *iFactory2,
  CATBody *iBody2,
  const CATMathTransformation &iBody2Transformation,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iSkillValue = BASIC);

/** 
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATCell *iCell1,
  const CATMathTransformation &iCell1Transformation,
  CATGeoFactory *iFactory2,
  CATCell *iCell2,
  const CATMathTransformation &iCell2Transformation,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iSkillValue = BASIC);

/** 
* @nodoc
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2Light(
  CATTopData *iTopData,
  CATGeoFactory *iFactory1,
  CATDomain *iDomain1,
  const CATMathTransformation &iDomain1Transformation,
  CATGeoFactory *iFactory2,
  CATDomain *iDomain2,
  const CATMathTransformation &iDomain2Transformation,
  CATDistanceBodyBodyType iType,
  CATDistanceBodyBodyMode iMode,
  CATSkillValue iMODE = BASIC);

#endif /* CATIPGMDistanceBodyBody2Light_h_ */
