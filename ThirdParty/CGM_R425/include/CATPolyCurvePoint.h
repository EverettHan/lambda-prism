// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurvePoint.h
//
//===================================================================
// June 2016  Creation NDO
//===================================================================
#ifndef CATPolyCurvePoint_H
#define CATPolyCurvePoint_H

#include "PolyMeshImpl.h"
#include "CATIPolyCurvePoint.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathPoint.h"
#include "CATPoly.h"

class CATIPolyCurve;


/**
 * Class defining a curve-point.
 * A curve-point lies on a CATIPolyCurve. 
 */
class ExportedByPolyMeshImpl CATPolyCurvePoint : public CATIPolyCurvePoint
{

public:

  /**
   * Construction of a CATPolyCurvePoint.
   * @param curve
   *   The curve on which the point lies.
   */
  static CATPolyCurvePoint* New (const CATIPolyCurve& curve);

  CATBoolean IsEditable () const;

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyPoint as a const CATPolyCurvePoint.
   */
  static const CATPolyCurvePoint* Cast (const CATIPolyPoint* P);

  /**
   * Casts a CATIPolyPoint as a CATPolyCurvePoint.
   */
  static CATPolyCurvePoint* Cast (CATIPolyPoint* P);

/** @} */

public:

  const CATIPolyCurve& GetCurve () const;

  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  CATBoolean IsLyingOn (const CATIPolyCurve& c) const;

  const CATIPolyCurve* IsStartVertex () const;
  CATIPolyCurve* IsStartVertex ();

  const CATIPolyCurve* IsEndVertex () const;
  CATIPolyCurve* IsEndVertex ();

public:

/** @name Curve-Point Definition
    @{ */

  /**
   * Sets the definition of the curve point given a vertex and a barycentric weight: alpha.
   * The curve point lies on the curve between the vertex v and the next vertex n on the curve.
   * The parameter alpha is the barycentric weight for the vertex v.
   * The barycentric weight for the vertex n is 1 - alpha.
   * The position of the curve-point is given by: alpha * Position (v) + (1 - alpha) * Position (n)
   * where v and n are two consecutive vertices along the curve.
   * @param v
   *   The vertex representing the start of the segment on which the curve-point lies.
   * @param alpha
   *   The barycentric weight to apply to the vertex v.
   */
  HRESULT SetCurvePoint (int v, double alpha);

  /**
   * Returns a curve-vertex given its index: 0 or 1.
   */
  int GetVertex (unsigned int index = 0) const;

  /**
   * Returns a barycentric coordinate given its index: 0 or 1.
   */
  double GetBarycentricCoordinate (unsigned int index = 0) const;

/** @} */

public:

  HRESULT GetPosition (CATMathPoint& P) const;
  HRESULT SetPosition (const CATMathPoint& P);

  HRESULT SetSupport (CATIPolySupport* iSupport);
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

public:

  HRESULT RegisterObserver (CATIPolyPointObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver &iObserver);

  HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const;
  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);

  CATIPolyPointConstTools* GetConstTools () const;
  CATIPolyPointTools* GetTools ();

private:

  const CATIPolyCurve& _Curve;
  CATIPolyPointObserver* _Observer;

  int _Vertex;
  double _Alpha;
  CATMathPoint _Position;  // Computed from the barycentric coordinates.

private:

  // Copy constructor/operator are forbidden.
  CATPolyCurvePoint (const CATPolyCurvePoint& iRHS);
  CATPolyCurvePoint& operator= (const CATPolyCurvePoint& iRHS);

private:

  CATPolyCurvePoint (const CATIPolyCurve& curve);
  virtual ~CATPolyCurvePoint ();

};

#endif
