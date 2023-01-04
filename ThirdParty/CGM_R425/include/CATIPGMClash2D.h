#ifndef CATIPGMClash2D_h_
#define CATIPGMClash2D_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCollec.h"

class CATListValCATMathPoint2D;
#include "CATMathDirection2D.h"
class CATClash2DClashRegion;
class CATClash2DCrossing;
class CATClashRegionOption;
class CATEdge;
class CATGeoFactory;
class CATMathTransformation2D;
class CATBody;
class CATCrvParam;
class CATMathPoint2D;
#include "CATTopDefine.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMClash2D;

/**
* Class defining the operator for clashing 2D geometries.
* <br> The operator returns 1 for success and 0 for failure.
*<ul>
*<li>The CATIPGMClash2D operator is created with the <tt>CreateGeoOpTemplate</tt> method and 
* directly <tt>delete</tt>d with the usual C++ delete operator.
*<li>In case of <tt>BASIC</tt>
* mode, the operation is automatically performed at the operator creation. 
* In case of <tt>ADVANCED</tt>
* mode, options can be selected with the <tt>Set</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.ExportedByClash2D
*<li>In both cases, the result is accessed using <tt>GetResult()</tt>.
*</ul>
*/
class ExportedByCATGMModelInterfaces CATIPGMClash2D: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMClash2D();

  /**
  * Returns the tolerance to be used in the clash computation.
  * @return
  * The clash tolerance.
  */
  virtual double GetClashTolerance() const = 0;

  /**
  * Returns the active state of an input body.
  * @param iBody1D
  * The ID of the body (instance).
  * @return
  * The active state of the body (instance).
  */
  virtual CATBoolean GetActivateState(CATLONG32 iBody1D_ID) const = 0;

  /**
  * Returns the option that indicates whether containment data is to be calculated.
  * @return
  * TRUE if containment data is to be calculated, FALSE if it is not to be caclulated.
  */
  virtual CATBoolean GetCalcContainmentData() const = 0;


  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  /**
  * Sets the tolerance to be used in the clash computation.
  * @param iClashTol
  * The tolerance.
  */
  virtual void SetClashTolerance(double iClashTol) = 0;

  /**
  * Sets the pairs of clash bodies which are to be considered by the clash Run.
  * To be called after the bodies have been added, otherwise it will fail.
  * If not called, or unset, then Run will consider all possible pairs of bodies.
  * To unset call UnsetClashBodyPairs.
  * @param iClashBodyIDs1
  * A list of clash body IDs, first of each pair
  * @param iClashBodyIDs2
  * A list of clash body IDs, second of each pair
  * @return
  * TRUE if the ClashBody IDs were valid and the pairs were successfully added
  * FALSE, otherwise.
  */
  virtual CATBoolean SetClashBodyPairs(
    const CATListOfInt &iClashBodyIDs1,
    const CATListOfInt &iClashBodyIDs2) = 0;

  /**
  * Unsets the pairs of clash bodies which are to be considered by the clash Run.
  */
  virtual void UnsetClashBodyPairs() = 0;

  /**
  * Sets the option that indicates whether containment data is to be calculated.
  * @param iCalcContainmentData
  * TRUE if containment data is to be calculated, FALSE if it is not to be calculated
  */
  virtual void SetCalcContainmentData(const CATBoolean iCalcContainmentData) = 0;

  //-----------------------------------------------------------------------
  //- Add/Remove methods
  //-----------------------------------------------------------------------
  /**
  * Adds a 1D body to be considered in the CATIPGMClash2D computation.
  * Instances of a body can share a body pointer but must be given a distinct ID and transform.
  * @param iBody1D
  * The 1D body to be added.
  * @param iCallerBodyID
  * Caller assigned integer tag to identity the body instance (e.g. index in array of body)
  * @param iTransform
  * The 2D transform to be applied to the body.
  * @param iOrientation
  * The orientation of the body.
  * @param iActive
  * The active state of the body; default is TRUE (active).
  * @return
  * Whether the body was successfully added; failure may indicate that the body was previously added.
  */
  virtual CATBoolean AddBody(
    CATBody *iBody1D,
    CATLONG32 iCallerBodyID,
    CATMathTransformation2D *iTransform,
    CATOrientation iOrientation,
    CATBoolean iActive = TRUE) = 0;

  /**
  * Adds multiple bodies to be considered by the CATIPGMClash2D computation.
  * Instances of a body can share a body pointer but must be given a distinct ID and transform.
  * @param iNumberOfClashEntities
  * The number of bodies to be added.
  * @param iBodies1D
  * Array of 1D bodies to be added.
  * @param iCallerBodyIDs
  * Caller assigned array of integer tags to identity the body instance (e.g. index in array of body)
  * @param iTransforms
  * Array of corresponding 2D transforms to be applied to the bodies.
  * @param iOrientations
  * Array of corresponding orientations of the bodies.
  * @param iActives
  * Array of corresponding active states of the bodies.
  * @return
  * Whether the bodies was successfully added; failure may indicate that a body was previously added.
  */
  virtual CATBoolean AddBodies(
    CATLONG32 iNumberOfClashEntities,
    CATBody **iBodies1D,
    CATLONG32 *iCallerBodyIDs,
    CATMathTransformation2D **iTransforms,
    CATOrientation *iOrientation,
    CATBoolean *iActive) = 0;

  //-----------------------------------------------------------------------
  //- Modification methods
  //-----------------------------------------------------------------------
  /**
  * Activates the input body so that it is considered by the CATIPGMClash2D computation.
  * @param iBody1D_ID
  * The ID of the body (instance) to be activated.
  * @return
  * Whether the body was successfully activated.
  */
  virtual CATBoolean ActivateBody(CATLONG32 iBody1D_ID) = 0;

  /**
  * Deactivates the input body so that it is NOT considered by the CATIPGMClash2D computation.
  * @param iBody1D_ID
  * The ID of the body (instance) to be deactivated.
  * @return
  * Whether the body was successfully deactivated.
  */
  virtual CATBoolean DeActivateBody(CATLONG32 iBody1D_ID) = 0;

  //
  // Clash Regions
  //
  /**
  * Gets the number of clash regions.
  * @return
  * The number of clash regions.
  */
  virtual CATLONG32 GetNumberRegions() const = 0;

  /**
  * Initializes the results iterator.
  */
  virtual void BeginRegions() = 0;

  /**
  * Increments the results iterator to the next clash region.
  * @return
  * TRUE if there is a next region, FALSE if the end of the result regions is reached.
  */
  virtual CATBoolean NextRegion() = 0;

  /**
  * Gets the next clash result region.
  * @param oClashRegion
  * The clash result region. Caller takes responsibility for deletion.
  */
  virtual CATBoolean GetRegion(CATClash2DClashRegion *&oClashRegion) const = 0;

  //
  // Clash Point-Regions
  //
  /**
  * Gets the number of clash points.
  * @return
  * The number of clash regions.
  */
  virtual CATLONG32 GetNumberPoints() const = 0;

  /**
  * Initializes the results iterator.
  */
  virtual void BeginPoints() = 0;

  /**
  * Increments the results iterator to the next clash point.
  * @return
  * TRUE if there is a next region, FALSE if the end of the result regions is reached.
  */
  virtual CATBoolean NextPoint() = 0;

  /**
  * Gets the next clash result point.
  * @param oBody1
  * The first body.
  * @param oCallerBodyID1
  * The user ID of the first body.
  * @param oEdge1
  * The first edge of the clash
  * @param oParam1
  * The parameter of the first edge-curve
  * @param oBody2
  * The second body.
  * @param oCallerBodyID2
  * The user ID of the second body.
  * @param oEdge2
  * The second edge of the clash
  * @param oParam2
  * The parameter of the second edge-curve
  * @param oClashPoint
  * The 2D clash point
  * @param oClashDirection
  * The 2D clash normal
  */
  virtual CATBoolean GetPoint(
    CATBody *&oBody1,
    CATLONG32 &oCallerBodyID1,
    CATEdge *&oEdge1,
    CATCrvParam &oParam1,
    CATBody *&oBody2,
    CATLONG32 &oCallerBodyID2,
    CATEdge *&oEdge2,
    CATCrvParam &oParam2,
    CATMathPoint2D &oClashPoint,
    CATMathDirection2D &oClashDirection) const = 0;

  /**
  * Gets the next clash result point.
  * @param oPoint
  * The clash result point.
  */
  virtual CATBoolean GetPoint(CATMathPoint2D &oPoint) const = 0;

  /**
  * Gets all of the clash result points.
  * @param oPoint
  * The clash result point.
  */
  virtual CATBoolean GetPoints(CATLISTV(CATMathPoint2D) &oPointList) const = 0;

  //
  // Containment Data
  //
  /**
  * Gets the data that indicates the containing body of each active body.
  * This method should only be used when there are at least two active bodies, and there are no clashes between them.
  * All pairs of active bodies are considered, including those that have been unset using the function UnsetClashBodyPairs().
  * For example, if there are four active bodies (B1, B2, B3, and B4), with B1 containing B2, B2 containing B3, and B4 being separate.
  * In this case, B1 and B4 would be classified as outer loops, with the containing bodies of B2 and B3 being B1 and B2 respectively.
  * @param oContainmentData
  * Each element of the list contains one of the following:-
  *   the identifier of the body that directly contains it, in the form of the caller assigned integer tag to identity the body instance (for
  *      the functions AddBody() and AddBodies());
  *   -1, which indicates that the body is an outer loop;
  *   -2, which indicates that the body is inactive.
  * For the above example, if the identifiers of B1, B2, B3, and B4 were 1, 2, 3, and 4 respectively, the contents of oContainmentData would be
  *   {-1, 1, 2, -1}.
  * Note that, although both B1 and B2 contain B3, the body that directly contains B3 is B2.
  * The list oContainmentData is emptied when this method is invoked. 
  * @return
  * TRUE if the containment data has been successfully obtained, in which case the data is returned in oContainmentData.
  * FALSE if the containment data has not been obtained, with the reason being one of the following:-
  *   there are fewer than two active bodies,
  *   there is at least one clash between the active bodies,
  *   an internal error has occurred.
  */
  virtual CATBoolean GetContainmentData(CATListOfInt &oContainmentData) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMClash2D(); // -> delete can't be called
};

ExportedByCATGMModelInterfaces CATIPGMClash2D *CATPGMCreateCATClash2D(
  CATGeoFactory *iUserFactory,
  CATSoftwareConfiguration *iConfig,
  double iClashTol);

#endif /* CATIPGMClash2D_h_ */
