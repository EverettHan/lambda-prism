//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyBVOperations.h
// Definine some operators applicable to a single BV.
//
//=============================================================================
// Sep 2009 Creation: JS9
//=============================================================================

#ifndef CATPolyBVOperations_H
#define CATPolyBVOperations_H

#include "PolyMathBV.h"
#include "CATErrorDef.h"

// Other
class CATMathTransformation;
class CATMathBox;

// Polyhedral
class CATPolyBoundingVolume;
class CATPolyOBB;
class CATPolyAABB;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATPolyBoundingCylinder;


/**
 * Definine some operators applicable to a single BV.
 */
class ExportedByPolyMathBV CATPolyBVOperations
{
public:
  CATPolyBVOperations() {}
  ~CATPolyBVOperations() {}

public:

  /**
   * Create a new bounding volume which is the result of the application
   * of the transformation of transfo on bv.
   * @param bv bounding volume to transform
   * @param transfo transformation to apply.
   * @param res resulting bounding volume. Can be deleted with regular delete.
   */
  static HRESULT CreateTransformedInstance(const CATPolyBoundingVolume & bv,
                                           const CATMathTransformation & transfo,
                                           CATPolyBoundingVolume *& res);

  static HRESULT Transform(CATPolyBoundingVolume & bv,
                           const CATMathTransformation & transfo);

  /**
   * Computes a CATMathBox enclosing the bounding volume.
   * @return S_OK on success, E_FAIL if the bounding volume can't be enclosed.
   */
  static HRESULT GetEnclosingBox(const CATPolyBoundingVolume & bv,
                                 CATMathBox & oBox);

  /**
   * Computes a CATMathBox enclosing the bounding volume.
   * @return S_OK on success, E_FAIL if the bounding volume can't be enclosed.
   */
  static HRESULT GetEnclosingBox(const CATPolyBoundingVolume & bv,
                                 CATMathBox & oBox,
                                 const CATMathTransformation * transfo);

  /**
   * Inflate a bounding volume by a certain value.
   * @param value is absolute not realtive to the BV size
   */
  static HRESULT Inflate(CATPolyBoundingVolume & bv, double value);

private:

  static HRESULT CreateAABBTI(const CATPolyAABB & aabb,
                              const CATMathTransformation & transfo,
                              CATPolyBoundingVolume *& res);

  static HRESULT CreateOBBTI(const CATPolyOBB & obb,
                             const CATMathTransformation & transfo,
                             CATPolyBoundingVolume *& res);

  static HRESULT CreateSphereTI(const CATPolyBoundingSphere & sphere,
                                const CATMathTransformation & transfo,
                                CATPolyBoundingVolume *& res);

  static HRESULT CreatePlaneTI(const CATPolyBoundingPlane & plane,
                               const CATMathTransformation & transfo,
                               CATPolyBoundingVolume *& res);

  static HRESULT CreateCylinderTI(const CATPolyBoundingCylinder & cylinder,
                                  const CATMathTransformation & transfo,
                                  CATPolyBoundingVolume *& res);

  static HRESULT TransformAABB(CATPolyAABB & aabb,
                               const CATMathTransformation & transfo);

  static HRESULT TransformOBB(CATPolyOBB & obb,
                              const CATMathTransformation & transfo);

  static HRESULT TransformSphere(CATPolyBoundingSphere & sphere,
                                 const CATMathTransformation & transfo);

  static HRESULT TransformPlane(CATPolyBoundingPlane & plane,
                                const CATMathTransformation & transfo);

  static HRESULT TransformCylinder(CATPolyBoundingCylinder & cylinder,
                                   const CATMathTransformation & transfo);

};

#endif // CATPolyBVOperations_H

