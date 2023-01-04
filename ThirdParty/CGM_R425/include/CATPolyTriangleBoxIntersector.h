// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleBoxIntersector.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// sep 2004 Creation: dhp
//===================================================================
#ifndef CATPolyTriangleBoxIntersector_h
#define CATPolyTriangleBoxIntersector_h

#include "PolyMathIntersectors.h"
#include "CATBoolean.h"

class CATMathPoint;
class CATMathBox;

class ExportedByPolyMathIntersectors CATPolyTriangleBoxIntersector
{

public :

  CATPolyTriangleBoxIntersector (void);

  // Calculate the intersection of a triangle defined by three points with a box.  
  // The last argument is a tolerance for the intersector.
  static CATBoolean Intersects (const CATMathPoint & p0,
                                const CATMathPoint & p1,
                                const CATMathPoint & p2,
                                const CATMathBox & box,
                                const double iEpsilon = 1e-06);

};

#endif
