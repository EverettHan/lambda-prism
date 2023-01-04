// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurface.h
//
//===================================================================
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathSurface_H
#define CATPolyMathSurface_H

#include "PolyMathSurfaces.h"
#include "CATErrorDef.h"
#include "CATPolyMathObject.h"

class CATPolyMathPlaneSurface;
class CATPolyMathCylinderSurface;
class CATPolyMathSphereSurface;
class CATPolyMathTorusSurface;
class CATPolyMathConeSurface;
class CATPolyMathCubicBSplineSurface;
class CATPolyMathSolidOfRevolutionSurface;
class CATPolyMathBoxSurface;
class CATPolyMathCapsuleSurface;

class CATPolyMathSurfaceConstVisitor;
class CATPolyMathSurfaceVisitor;


/**
 * Describe your class here.
 */
class ExportedByPolyMathSurfaces CATPolyMathSurface : public CATPolyMathObject
{

public:

  CATPolyMathSurface () {}
  virtual ~CATPolyMathSurface () {}

  /**
   * Returns a clone of this instance.
   */
  virtual CATPolyMathSurface* Clone () const = 0;

public:

  const CATPolyMathSurface* CastAsSurface () const;
  CATPolyMathSurface* CastAsSurface ();

  // Const casts
  virtual const CATPolyMathQuadSurface* CastAsQuadSurface()const;
  virtual const CATPolyMathPlaneSurface* CastAsPlane () const;
  virtual const CATPolyMathCylinderSurface* CastAsCylinder () const;
  virtual const CATPolyMathSphereSurface* CastAsSphere () const;
  virtual const CATPolyMathTorusSurface* CastAsTorus () const;
  virtual const CATPolyMathConeSurface* CastAsCone () const;
  virtual const CATPolyMathCubicBSplineSurface* CastAsCubicBSpline () const;
  virtual const CATPolyMathSolidOfRevolutionSurface* CastAsSolidOfRevolution () const;

  virtual const CATPolyMathBoxSurface* CastAsBox () const;
  virtual const CATPolyMathCapsuleSurface* CastAsCapsule () const;

  // Non-const casts
  virtual CATPolyMathQuadSurface* CastAsQuadSurface();
  virtual CATPolyMathPlaneSurface* CastAsPlane () ;
  virtual CATPolyMathCylinderSurface* CastAsCylinder () ;
  virtual CATPolyMathSphereSurface* CastAsSphere () ;
  virtual CATPolyMathTorusSurface* CastAsTorus () ;
  virtual CATPolyMathConeSurface* CastAsCone () ;
  virtual CATPolyMathCubicBSplineSurface* CastAsCubicBSpline () ;
  virtual CATPolyMathSolidOfRevolutionSurface* CastAsSolidOfRevolution ();

  virtual CATPolyMathBoxSurface* CastAsBox () ;
  virtual CATPolyMathCapsuleSurface* CastAsCapsule () ;

public:

  /**
   * Access the concrete type through a const visitor
   * @return
   *   The status of the application of the visitor
   */
  virtual HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const = 0;

  /**
   * Access the concrete type through a non-const visitor
   * @return
   *   The status of the application of the visitor
   */
  virtual HRESULT Accept (CATPolyMathSurfaceVisitor &iV) = 0;

};

#endif
