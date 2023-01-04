// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceBVComputeVisitor.h
//
//===================================================================
//
// Usage notes: Visitor on a Math Surface to compute a Bounding Volume
// (BV) from such a surface.
//
//===================================================================
//
// 2010-10-11 XXC: Creation
//===================================================================

#ifndef CATPolyMathSurfaceBVComputeVisitor_H
#define CATPolyMathSurfaceBVComputeVisitor_H

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "PolyMathSurfaces.h"
#include "CATPolyMathSurfaceConstVisitor.h"

class CATMathSurface;
class CATPolyMathClosedCylinderSurface;
class CATPolyMathPlaneSurface;
class CATPolyMathSphereSurface;
class CATPolyMathTorusSurface;
class CATPolyMathBoxSurface;
class CATPolyMathCapsuleSurface;
class CATMathTransformation;
class CATMathOBBBase;
class CATMathOBB;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingSphere;
class CATPolyBoundingCylinder;
class CATMathBox;
class CATPolyBoundingPlane;

/**
 * Some useful functions to compute Bounding Volumes.
 */
class ExportedByPolyMathSurfaces CATPolyMathSurfaceBVComputeVisitor : public CATPolyMathSurfaceConstVisitor
{
public:

  /** The tolerance iTolerance is used to inflate every bounding
   *  volume created by the instance of this visitor. If the radius of
   *  the bounding volume is lower than 1, the tolerance is first
   *  multiplied by this radius before beeing used to inflate the
   *  bounding volume.
   */
  CATPolyMathSurfaceBVComputeVisitor(double iTolerance = 0.0);
  ~CATPolyMathSurfaceBVComputeVisitor();

public:

  /**
   * Compute an OBB from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oOBB: result of the computation.
   */
  HRESULT ComputeOBB(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                     CATPolyOBB & oOBB);

  /**
   * Compute an AABB from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oAABB: result of the computation.
   */
  HRESULT ComputeAABB(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                      CATPolyAABB & oAABB);

  /**
   * Compute a Sphere from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oSphere: result of the computation.
   */
  HRESULT ComputeSphere(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                        CATPolyBoundingSphere & oSphere);

  /**
   * Compute a Cylinder from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oCylinder: result of the computation.
   */
  HRESULT ComputeCylinder(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                        CATPolyBoundingCylinder & oCylinder);

  /**
   * Compute a Plane from a surface. Only relevant when the surface is a CATPolyMathPlaneSurface
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oPlane: result of the computation.
   */
  HRESULT ComputePlane(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                       CATPolyBoundingPlane & oPlane);

  /**
   * Compute an OBB from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oOBB: result of the computation.
   */
  HRESULT ComputeOBB(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                     CATMathOBB & oOBB);

  /**
   * Compute an AABB from a math surface.
   * @param iSurface: the surface
   * @param iPos: if not NULL, addtional position to apply to the surface.
   * @param oAABB: result of the computation.
   */
  HRESULT ComputeAABB(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                      CATMathBox & oAABB);

protected:

  HRESULT Visit(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos);

protected:

  /** For internal use only, to compute an OBB CATMathOBB or CATPolyOBB.
   */
  HRESULT ComputeOBB(const CATPolyMathSurface & iSurface, const CATMathTransformation * iPos,
                     CATMathOBBBase & oOBB);

protected:
  
  HRESULT VisitConcrete (const CATPolyMathClosedCylinderSurface& iSurface);
  HRESULT VisitConcrete (const CATPolyMathPlaneSurface& iSurface);
  HRESULT VisitConcrete (const CATPolyMathSphereSurface& iSurface);
  HRESULT VisitConcrete (const CATPolyMathBoxSurface& iSurface);
  HRESULT VisitConcrete (const CATPolyMathCapsuleSurface& iSurface);
  HRESULT VisitConcrete (const CATPolyMathCylinderSurface& iSurface);

private:
  double _Tolerance;

  CATPolyBoundingSphere * _Sphere;
  CATPolyBoundingPlane * _Plane;
  CATPolyBoundingCylinder * _Cylinder;
  CATMathBox * _Box;
  CATMathOBBBase * _OBB;
};

#endif // CATPolyMathSurfaceBVComputeVisitor
