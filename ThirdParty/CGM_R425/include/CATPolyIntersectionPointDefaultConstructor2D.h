// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersectionPointDefaultConstructor2D.h
//
//===================================================================
// December 2011  Creation: ndo
//===================================================================
#ifndef CATPolyIntersectionPointDefaultConstructor2D_H
#define CATPolyIntersectionPointDefaultConstructor2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersectionPointConstructor2D.h"


/**
 * Default implementation of the constructor of an intersection point between two intersecting segments.
 * This implementation computes the point intersection between the two segments.
 * If one of the segment extremity is sufficiently close according to a given distance tolerance, then 
 * it chooses this extremity.
 */
class ExportedByPolyMathIntersectors CATPolyIntersectionPointDefaultConstructor2D : public CATPolyIntersectionPointConstructor2D
{

public:

  /**
   * Construction of a default constructor with a default distance tolerance.
   */
  inline CATPolyIntersectionPointDefaultConstructor2D (const double iTolerance);

  virtual ~CATPolyIntersectionPointDefaultConstructor2D () {}

  /**
   * Implements CATPolyIntersectionPointConstructor2D::Compute.
   */
  HRESULT Compute (const CATMathPoint2D& A, const CATMathPoint2D& B,   // Define Segment AB.
                   const CATMathPoint2D& C, const CATMathPoint2D& D,   // Define Segment CD.
                   CATMathPoint2D& oIntersectionPoint) const;

private:

  const double _Tolerance;

};

inline CATPolyIntersectionPointDefaultConstructor2D::CATPolyIntersectionPointDefaultConstructor2D (const double iTolerance) :
  _Tolerance (iTolerance)
{
}

#endif
