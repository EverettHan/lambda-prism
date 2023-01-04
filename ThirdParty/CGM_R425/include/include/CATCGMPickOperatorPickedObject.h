// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCGMPickOperatorPickedObject.h
//
//===================================================================
// May 2010  MPX/NDO
//===================================================================
#ifndef CATCGMPickOperatorPickedObject_H
#define CATCGMPickOperatorPickedObject_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"

class CATGeometry;
class CATBody;


/**
 * A picked object as computed by the picking operator CATCGMPickOperator.
 */
class ExportedByCATGMModelInterfaces CATCGMPickOperatorPickedObject
{

public:

  /**
   * Returns the picked geometry.
   * @param oGeometry
   *   The picked geometry.
   * @return
   *   S_OK on success or E_FAIL on failure.
   */
  virtual HRESULT GetPickedGeometry(CATGeometry*& oGeometry) const = 0;

  /**
   * Returns the distance of the object-ray intersection point
   * from the view point.
   * @param oDistanceFromViewPoint
   *   The distance from the view point to the object.
   * @return
   *   S_OK on success or E_FAIL on failure.
   */
  virtual HRESULT GetDistanceFromViewPoint(double& oDistanceFromViewPoint) const = 0;

  /**
   * Returns the distance of the object from the ray
   * @param oDistanceFromRay
   *   The distance from the ray to the object.
   * @return
   *   S_OK on success or E_FAIL on failure.
   */
  virtual HRESULT GetDistanceFromRay(double& oDistanceFromRay) const = 0;

  /**
   * Returns the CATBody that owns the picked geometry.
   * If picked geometry is a CATBody, the GetOwningBody will return the same
   * @param oBody
   *   The CATBody that owns the picked geometry.
   * @return
   *   S_OK on success or E_FAIL on failure.
   */
  virtual HRESULT GetOwningBody(CATBody*& oBody) const = 0;

  /**
   * Returns the associated PartId of the owning CATBody of the picked geometry.
   * @param oPartId
   *   The part ID.
   * @return
   *   S_OK on success or E_FAIL on failure.
   */
  virtual HRESULT GetPartId(const void*& oPartId) const = 0;

public:

  virtual ~CATCGMPickOperatorPickedObject();
};

#endif
