// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurvePoint.h
//
//===================================================================
// June 2016  Creation NDO
//===================================================================
#ifndef CATIPolyCurvePoint_H
#define CATIPolyCurvePoint_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"

class CATIPolyCurve;


/**
 * Interface to a polyhedral curve-point.
 *
 * A curve-point is a CATIPolyPoint that lies on a CATIPolyCurve.  
 * Implementations of this interface should be thread-safe for use with the polyhedral operators.
 */
class ExportedByPolyhedralModel CATIPolyCurvePoint : public CATIPolyPoint
{

public:

  /** @name Casting Methods
      @{ */

  inline static CATIPolyCurvePoint* Cast (CATIPolyPoint&);

  inline static const CATIPolyCurvePoint* Cast (const CATIPolyPoint&);

  inline static CATIPolyCurvePoint* Cast (CATIPolyPoint*);

  inline static const CATIPolyCurvePoint* Cast (const CATIPolyPoint*);

  inline static CATIPolyCurvePoint* Cast (CATIPolyObject&);

  inline static const CATIPolyCurvePoint* Cast (const CATIPolyObject&);

  inline static CATIPolyCurvePoint* Cast (CATIPolyObject*);

  inline static const CATIPolyCurvePoint* Cast (const CATIPolyObject*);

  /** @} */

public:

  /**
   * Returns the curve on which the curve-point is defined.
   */
  virtual const CATIPolyCurve& GetCurve () const = 0;

public:

/** @name Curve-Point Definition
    @{ */

  /**
   * Returns a curve-vertex given its index: 0 or 1.
   */
  virtual int GetVertex (unsigned int index = 0) const = 0;

  /**
   * Returns a barycentric coordinate given its index: 0 or 1.
   */
  virtual double GetBarycentricCoordinate (unsigned int index = 0) const = 0;

/** @} */

protected:

  virtual ~CATIPolyCurvePoint () {}

public:

  const CATIPolyCurvePoint* CastToCurvePoint () const;
  CATIPolyCurvePoint* CastToCurvePoint ();

};

inline CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (CATIPolyPoint& P)
{
  return P.CastToCurvePoint ();
}

inline const CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (const CATIPolyPoint& P)
{
  return P.CastToCurvePoint ();
}

inline CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline const CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (const CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline const CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (const CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

inline const CATIPolyCurvePoint* CATIPolyCurvePoint::Cast (const CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

#endif // !CATIPolyCurvePoint_H
