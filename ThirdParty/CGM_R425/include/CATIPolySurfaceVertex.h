// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertex.h
//
//===================================================================
// April 2009  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceVertex_H
#define CATIPolySurfaceVertex_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"

class CATIPolySurface;


/**
* Interface to a polyhedral surface vertex.
*
* A polyhedral surface vertex is a CATIPolyPoint defined by a CATIPolySurface vertex.  
* A surface vertex lies on a CATIPolySurface.
* 
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolySurfaceVertex : public CATIPolyPoint
{

public:

/** @name Casting Methods.
    @{ */
  
  inline static CATIPolySurfaceVertex* Cast (CATIPolyPoint&);

  inline static const CATIPolySurfaceVertex* Cast (const CATIPolyPoint&);

  inline static CATIPolySurfaceVertex* Cast (CATIPolyPoint*);

  inline static const CATIPolySurfaceVertex* Cast (const CATIPolyPoint*);

  inline static const CATIPolySurfaceVertex* Cast (const CATIPolyObject&);

  inline static CATIPolySurfaceVertex* Cast (CATIPolyObject&);

  inline static const CATIPolySurfaceVertex* Cast (const CATIPolyObject*);

  inline static CATIPolySurfaceVertex* Cast (CATIPolyObject*);

/** @} */

public:

  /**
   * Returns the CATIPolySurface on which the point lies.
   */
  virtual CATIPolySurface& GetSurface () = 0;

  /**
   * Returns the CATIPolySurface on which the point lies.
   */
  virtual const CATIPolySurface& GetSurface () const = 0;

  /**
   * Returns the index of the surface vertex.
   */
  virtual int GetSurfaceVertexIndex () const = 0;

protected:

  virtual ~CATIPolySurfaceVertex () {}

public:

  const CATIPolySurfaceVertex* CastToSurfaceVertex () const;
  CATIPolySurfaceVertex* CastToSurfaceVertex ();

};

inline CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (CATIPolyPoint& P)
{
  return P.CastToSurfaceVertex ();
}

inline const CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (const CATIPolyPoint& P)
{
  return P.CastToSurfaceVertex ();
}

inline CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline const CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (const CATIPolyPoint* P)
{
  return P ? Cast (*P) : 0;
}

inline const CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (const CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (CATIPolyObject& O)
{
  return Cast (CATIPolyPoint::Cast (O));
}

inline const CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (const CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

inline CATIPolySurfaceVertex* CATIPolySurfaceVertex::Cast (CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

#endif // !CATIPolySurfaceVertex_H
