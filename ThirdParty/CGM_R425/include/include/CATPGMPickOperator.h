#ifndef CATPGMPickOperator_h_
#define CATPGMPickOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATCGMPickOperator.h"

class CATBody;
class CATCGMPickOperatorResultIterator;
class CATGeoFactory;
class CATGeometry;
class CATMathDirection;
class CATMathPlane;
class CATMathPoint;
class CATMathTransformation;
class CATPGMPickOperatorResultIterator;
class CATPickOperatorCallback;
class CATPickOperatorRecorder;
class CATTessSettings;

/**
* Picking operator.  
* Given one or more <code>CATBody</code>s and a ray defined by a view point and a direction, the picking
* operator finds the <code>CATBody</code> and the geometry (<code>CATGeometry</code>) intersected by the ray.
*/
class ExportedByCATGMModelInterfaces CATPGMPickOperator: public CATCGMPickOperator
{

public:

  /**
   * Constructor.
   */
  CATPGMPickOperator();

  /**
   * Destructor.
   */
  virtual ~CATPGMPickOperator();

public:

  //////////////
  // Core Methods
  //////////////

  /**
   * Adds a body to the picking operator.
   * The last three parameters are the tessellation settings that are used should the operator
   * need to tessellate partly or fully the body for picking.
   * This function can be called multiple times for different bodies.
   * In order that an end user does not see any discrepancy during picking, the client may use the same
   * tessellation settings as it has used for visualization.
   * But note that, tighter the tessellation settings, higher will be the computation cost of the 
   * pick operator.
   * @param iPartBody
   *   The body from the part that is added to the operator.
   * @param iTransform
   *   The transformation matrix corresponding to the positioning 
   *   of this body in global coordinates.
   * @param iPartId
   *   Void pointer that the caller can use to identify the given
   *   body with a part for its own reference. Multiple iPartId's can be 
   *   associated with the same body (e.g. when there are multiple instances 
   *   of the same part in an assembly). This PartId is returned back in the
   *   results, so that the caller can identify which instance of the body
   *   got picked.
   * @param iSag
   *   Tessellation parameter: Sag.
   * @param iStep
   *   Tessellation parameter: An optional step size parameter not to be exceeded.  
   * @param iMaxAngle
   *   Tessellation parameter: An optional angle parameter not to be exceeded.
   * @return
   *   <code>S_OK</code> if the <code>CATBody</code> is added successfully.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT AddBody(
    CATBody &iPartBody,
    const CATMathTransformation &iTransform,
    const void *iPartId,
    double iSag,
    double iStep = CATMathInfinite,
    double iMaxAngle = 0.25* CATPI) = 0;

  /**
   * This method can be called any number of times, after any/every call to AddBody().
   * It adds another instance of the previous added body.
   * @param iTransform
   *   Transformation matrix corresponding to the positioning in global coordinates
   *   of this instance of the previously added body.
   * @param iPartId
   *   Void pointer that the caller can use to identify another instance 
   *   of the previously added body, for its own reference. Multiple iPartId's can be 
   *   associated with the same body (e.g. when there are multiple instances 
   *   of the same part in an assembly. This PartId is returned back in the
   *   results, so that the caller can identify which instance of the body
   *   got picked.
   * @return
   *   <code>S_OK</code> if the instance is added successfully.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT AddAnotherInstanceOfPreviousBody(
    const CATMathTransformation &iTransform,
    const void *iPartId) = 0;

  /**
   * Runs the picking operator.
   * @param iViewPoint
   *   The start of the picking ray.
   * @param iViewDirection
   *   The direction of the picking ray.
   * @return 
   *   0 if the picking operator runs successfully and 1 otherwise.
   */
  virtual int Run(
    const CATMathPoint &iViewPoint,
    const CATMathDirection &iViewDirection) = 0;

  virtual int Run(
                const CATMathPoint& iViewPoint, 
                const CATMathDirection& iViewDirection, 
                const CATMathDirection& iWidthDirection, 
                double iHeight, 
                double iWidth) = 0;
  /**
   * Returns the results of picking. 
   * @param oResultIterator
   *   Iterator that can be used to iterate through picked objects.
   *   This returned iterator is owned by caller, i.e. the caller will need to delete it after use.
   *   It can be deleted using regular C++ delete.
   *   Note that the returned iterator is invalid after the next "Run" or if the operator is deleted.
   *   The returned iterator should be deleted before the next Run or before the operator is deleted, whichever is earlier
   * @return
   *   <code>S_OK</code> if an iterator is successfully returned.
   *   <code>S_FALSE</code> if no iterator is returned (no picked object.) ?
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetResult(
    CATCGMPickOperatorResultIterator *&oResultIterator) const = 0;

  //////////////
  // Methods for modifying options
  //////////////

  /**
   * Sets the aperture radius of picking.
   * @param iApertureRadius
   *   Aperture radius to be used for picking of vertices and edges.
   *   If this is too low, then picking of vertices and edges may become problematic.
   *   By default, this value is 0.0, but it is recommended not to use this default value,
   *   It is recommended that aperture radius be larger than tessellation sag.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> if iApertureRadius is less than 0.
   */
  virtual HRESULT SetApertureRadius(double iApertureRadius) = 0;

  /**
   * Enables or disables the pick operator to pick only the first hit object(s).
   * @param iOnlyFirstHit
   *   If this is TRUE, then the pick operator will pick only the first hit object(s).
   *      Note that there could be multiple objects picked in the first hit, if the ray 
   *      simultaneously hits multiple objects (within aperture radius).
   *   If this is FALSE, then the operator will pick all hit objects.
   *
   *   By default value of this option is TRUE.
   *   Setting this to TRUE would give better performance than FALSE.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT SetOnlyFirstHit(CATBoolean iOnlyFirstHit) = 0;

  //////////////
  // Methods for querying current value of options
  //////////////

  /**
   * Gets the currently set aperture radius of picking.
   * Refer "SetApertureRadius" for more details on aperture radius
   * @param oApertureRadius
   *   Currently set aperture radius of picking
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetApertureRadius(double &oApertureRadius) const = 0;

  /**
   * Gets the current state of the "OnlyFirstHit" option
   * Refer "SetOnlyFirstHit" for more details on this option
   * @param oOnlyFirstHit
   *   Current state of the "OnlyFirstHit" option
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetOnlyFirstHit(CATBoolean &oOnlyFirstHit) const = 0;

public:

  //////////////
  // Enum for options
  //////////////

  /**
   * @nodoc
   */
  enum FilterType 
  {
    VertexFilter=0, 
    EdgeFilter, 
    FaceFilter, 
    WireFilter, 
    VolumeFilter,
    BodyFilter,
  };

  /**
   * @nodoc
   */
  enum SortingCriteria
  {
    DistanceFromViewPoint=0,
    DistanceFromRay,
    Dimension,
    Orthogonality
  };

  /**
   * @nodoc
   */
  enum SortingOrder
  {
    HighToLow=0,
    LowToHigh
  };

public:

  ///////////////////////////////////
  // Interfaces not exposed
  ///////////////////////////////////

  /**
   * @nodoc
   * Adds a body to the picking operator.
   * This function can be called multiple times for different bodies.
   * In order that an end user does not see any discrepancy during picking, the client may use the same
   * tessellation settings as it has used for visualization.
   * But note that, tighter the tessellation settings, higher will be the computation cost of the 
   * pick operator.
   * @param iPartBody
   *   The body from the part that is added to the operator.
   * @param iTransform
   *   The transformation matrix corresponding to the positioning 
   *   of this body in global coordinates.
   * @param iPartId
   *   Void pointer that the caller can use to identify the given
   *   body with a part for its own reference. Multiple iPartId's can be 
   *   associated with the same body (e.g. when there are multiple instances 
   *   of the same part in an assembly). This PartId is returned back in the
   *   results, so that the caller can identify which instance of the body
   *   got picked.
   * @param iTessSettings
   *   The tessellation settings that are used should the operator
   *   need to tessellate partly or fully the body for picking.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT AddBody(
    CATBody &iBody,
    const CATMathTransformation &iTransform,
    const CATTessSettings &iTessSettings,
    const void *iPartId) = 0;

  /**
   * @nodoc
   * Sets the maximum depth level of penetration of the ray into the bodies.
   * The lesser the max depth level, the better would be the operator speed.
   * For example, if this is set to 1, 
   * then the operator returns only the first "hit" object(s)
   * Setting "0" means setting unlimited depth level.
   * Note: There could be multiple objects at the same level. 
   * For example, if the ray hits a vertex first, then the edges and faces 
   * that this vertex belongs to are also returned since
   * they will be considered to be at the same depth level 
   * ******* Not fully supported (only 0 and 1 are supported currently) *********
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT SetMaxDepthLevel(CATULONG32 iMaxDepthLevel) = 0;

  /**
   * @nodoc
   * Returns the maximum depth level of penetration of the ray into the bodies
   */
  virtual HRESULT GetMaxDepthLevel(CATULONG32 &oMaxDepthLevel) const = 0;

  /**
   * @nodoc
   * Operator Run
   * Runs the pick operator.
   * iViewPoint: View point from where ray begins
   * iViewDirection: View direction i.e. direction of ray
   * iCallback (not supported yet): Pointer to user-defined class 
   *            derived from CATPickOperatorCallback. This can be used 
   *            for aborting a Run() midway.
   */
  virtual int Run(
    const CATMathPoint &iViewPoint,
    const CATMathDirection &iViewDirection,
    CATPickOperatorCallback *iCallback) = 0;

  virtual int Run(
                const CATMathPoint& iViewPoint, 
                const CATMathDirection& iViewDirection, 
                const CATMathDirection& iWidthDirection, 
                double iHeight, 
                double iWidth,
                CATPickOperatorCallback* iCallback) = 0;
  /**
   * @nodoc
   */
  virtual HRESULT GetResult(
    CATPGMPickOperatorResultIterator *&oResultIterator) const = 0;

};

//////////////
// CATPGMPickOperator creator function
//////////////
/**
 * Global function to create a picking operator.
 */
ExportedByCATGMModelInterfaces CATPGMPickOperator *CATPGMCreatePickOperator(CATSoftwareConfiguration &iConfig);

enum CATRayObjectContainment
{
  RAY_OBJECT_CONTAINMENT_UNKNOWN,
  OBJECT_OUTSIDE_RAY_REGION,
  OBJECT_FULLY_CONTAINED_IN_RAY_REGION,
  OBJECT_INTERSECTING_WITH_RAY_BOUNDARY,
};

#endif /* CATPGMPickOperator_h_ */
