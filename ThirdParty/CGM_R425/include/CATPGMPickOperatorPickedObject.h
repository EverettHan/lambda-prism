// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPGMPickOperatorPickedObject.h
//
//===================================================================
// May 2010  MPX/NDO
//===================================================================
#ifndef CATPGMPickOperatorPickedObject_H
#define CATPGMPickOperatorPickedObject_H

#include "CATGMModelInterfaces.h"
#include "CATCGMPickOperatorPickedObject.h"
#include "CATErrorDef.h"
#include "CATPGMPickOperator.h"
class CATGeometry;
class CATBody;


/**
 * A picked object as computed by the picking operator CATCGMPickOperator.
 */
class ExportedByCATGMModelInterfaces CATPGMPickOperatorPickedObject : public CATCGMPickOperatorPickedObject
{

public:

  /**
   * Returns the picked geometry.
   * @param oGeometry
   *   The picked geometry.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetPickedGeometry(CATGeometry*& oGeometry) const = 0;

  /**
   * Returns the distance of the object-ray intersection point
   * from the view point.
   * @param oDistanceFromViewPoint
   *   The distance from the view point to the object.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetDistanceFromViewPoint(double& oDistanceFromViewPoint) const = 0;

  /**
   * Returns the distance of the object from the ray
   * @param oDistanceFromRay
   *   The distance from the ray to the object.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetDistanceFromRay(double& oDistanceFromRay) const = 0;

  /**
   * Returns the CATBody that owns the picked geometry.
   * If picked geometry is a CATBody, the GetOwningBody will return the same
   * @param oBody
   *   The CATBody that owns the picked geometry.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetOwningBody(CATBody*& oBody) const = 0;

  /**
   * Returns the associated PartId of the owning CATBody of the picked geometry.
   * @param oPartId
   *   The part ID.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetPartId(const void*& oPartId) const = 0;

  /**
   * Returns the orthogonality index for a picked CATFace or CATEdge. 
   * Note that this is valid only of the picked geometry is a CATFace or a CATEedge
   * For others, this method returns S_FALSE.
   * For a face, the value can range from -1.0 to 1.0.
   * For an edge, the value can range from 0.0 to 1.0.
   * Higher the absolute value of the index, higher the orthogonality.
   * This is only an approximate indicator, since it is calculated from tessellation, 
   * and not from exact geometry.
   * A negative sign indicates that a face is being picked from behind.
   *
   * Some examples:
   * 1. if the orthogonality index is 1.0 then it means that the ray 
   *    is orthogonal to the face or to the edge at the intersection point.
   * 2. if the orthogonality index is 0.0 then it means that the ray 
   *    is tangential to the face or to the edge at the intersection point.
   * 3. if the orthogonality index is -1.0 then it means that the ray 
   *    is orthogonal to the face at the intersection point, but the ray hits 
   *    the face from behind.
   * 4. if the orthogonality index is 0.2 and 0.6 for two picked objects, 
   *    A and B respectively, then it means that the ray hits B with a higher
   *    orthogonality than A.
   * @return
   *   <code>S_OK</code> on success.
   *   <code>S_FALSE</code> if picked geometry is not a CATEdge or a CATFace
   *   <code>E_FAIL</code> otherwise.
   */
  virtual HRESULT GetOrthogonalityIndex(double& oOrthogonalityIndex) const = 0;


  virtual HRESULT GetObjectContainment(CATRayObjectContainment& oContainment) const = 0;

public:

  virtual ~CATPGMPickOperatorPickedObject();

};

#endif
