// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyObject.h
//
//===================================================================
// January 2011  Creation: NDO
//===================================================================
#ifndef CATIPolyObject_H
#define CATIPolyObject_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "Poly/Precision.h"

// Subclasses.
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;


/**
* Interface to a polyhedral object.
* The following discrete geometry interfaces derive from this class:
* <ul>
*   <li> CATIPolySurface
*   <li> CATIPolyCurve
*   <li> CATIPolyPoint
* </ul>
*/
class ExportedByPolyhedralModel CATIPolyObject : public CATPolyRefCounted
{

public:

#ifndef _AIX_SOURCE
  using PrecisionVertexPosition = Poly::Precision;
  static const PolyPrecision eFloat = Poly::Precision::eFloat;
  static const PolyPrecision eDouble = Poly::Precision::eDouble;
#else
  //typedef PolyPrecision PrecisionVertexPosition;
  //static const PolyPrecision eFloat = Poly::Precision::eFloat;
  //static const PolyPrecision eDouble = Poly::Precision::eDouble;

  enum PrecisionVertexPosition
  {
    /** Vertex positions in float precision. */           eFloat = Poly::Precision::eFloat,
    /** Vertex positions in double presison. */           eDouble = Poly::Precision::eDouble
  };
#endif


public:

/** @name Downcasters
    @{ */

  /**
   * Casts a const CATIPolyObject as a const CATIPolySurface.
   */
  virtual const CATIPolySurface* CastToPolySurface () const { return 0; }

  /**
   * Casts a CATIPolyObject as a CATIPolySurface.
   */
  virtual CATIPolySurface* CastToPolySurface () { return 0; }

  /**
   * Casts a const CATIPolyObject as a const CATIPolyCurve.
   */
  virtual const CATIPolyCurve* CastToPolyCurve () const { return 0; }

  /**
   * Casts a CATIPolyObject as a CATIPolyCurve.
   */
  virtual CATIPolyCurve* CastToPolyCurve () { return 0; }

  /**
   * Casts a const CATIPolyObject as a const CATIPolyPoint.
   */
  virtual const CATIPolyPoint* CastToPolyPoint () const { return 0; }

  /**
   * Casts a CATIPolyObject as a CATIPolyPoint.
   */
  virtual CATIPolyPoint* CastToPolyPoint () { return 0; }

/** @} */

};

#endif // !CATIPolyObject_H
