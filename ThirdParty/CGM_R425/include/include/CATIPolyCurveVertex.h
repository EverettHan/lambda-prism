// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveVertex.h
//
//===================================================================
// April 2009  Creation: NDO
//===================================================================
#ifndef CATIPolyCurveVertex_H
#define CATIPolyCurveVertex_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"

class CATIPolyCurve;


/**
* Interface to a polyhedral curve vertex.
*
* A polyhedral curve vertex is a CATIPolyPoint defined by a CATIPolyCurve vertex.  
* A curve vertex lies on a CATIPolyCurve (at the start or at the end).
* 
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolyCurveVertex : public CATIPolyPoint
{

public:

  /** @name Casting Methods.
      @{ */

  inline static CATIPolyCurveVertex* Cast (CATIPolyPoint&);

  inline static const CATIPolyCurveVertex* Cast (const CATIPolyPoint&);

  inline static CATIPolyCurveVertex* Cast (CATIPolyPoint*);

  inline static const CATIPolyCurveVertex* Cast (const CATIPolyPoint*);

  inline static const CATIPolyCurveVertex* Cast (const CATIPolyObject&);

  inline static CATIPolyCurveVertex* Cast (CATIPolyObject&);

  inline static const CATIPolyCurveVertex* Cast (const CATIPolyObject*);

  inline static CATIPolyCurveVertex* Cast (CATIPolyObject*);

  /** @} */

public:

  /*
   * @return
   *   Returns the CATIPolyCurve on which the point lies.
   */
  virtual CATIPolyCurve& GetCurve () = 0;
  virtual const CATIPolyCurve& GetCurve () const = 0;

  /*
   * @return
   *   Return the index of the curve vertex.
   */
  virtual int GetCurveVertexIndex () const = 0;

protected:

  virtual ~CATIPolyCurveVertex () {}

public:

  const CATIPolyCurveVertex* CastToCurveVertex () const;
  CATIPolyCurveVertex* CastToCurveVertex ();

};

inline CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (CATIPolyPoint& P)
{
  return P.CastToCurveVertex ();
}

inline const CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (const CATIPolyPoint& P)
{
  return P.CastToCurveVertex ();
}

inline CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline const CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (const CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline const CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (const CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline const CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (const CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

inline CATIPolyCurveVertex* CATIPolyCurveVertex::Cast (CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

#endif // !CATIPolyCurveVertex_H
