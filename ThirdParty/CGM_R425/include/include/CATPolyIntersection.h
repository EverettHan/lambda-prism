// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersection.h
//
//===================================================================
// January 2006 Creation: NDO
//===================================================================
#ifndef CATPolyIntersection_H
#define CATPolyIntersection_H


class CATPolyIntersection 
{

public:

  /**
   * Enumerator defining the type of the intersection.
   */
  enum Type
  {
    /** The intersection has not been determined. */      eUndetermined             = -1, 
    /** There is no intersection. */                      eNoIntersection           =  0,
    /** The intersection is a point. */                   ePointIntersection        =  1,
    /** The intersection is a line segment. */            eSegmentIntersection      =  2,
    /** The intersection is a geodesic. */                eGeodesicIntersection     =  eSegmentIntersection,
    /** The intersection is a polygon. */                 ePolygonIntersection      =  3,
    /** There is an unspecified intersection. */          eIntersection             =  4
  };

  /**
   * Enumerator listing various error codes that prevented the computation of an intersection.
   */
  enum Error
  {
    /** No error. */                                              eNoError                   =  0,
    /** Fatal error. */                                           eFatalError                = -2,
    /** Colinear operands. */                                     eColinearOperands          = -3,
    /** Coplanar operands. */                                     eCoplanarOperands          = -4,
    /** Degenerate segment. */                                    eDegenerateSegment         = -5,
    /** Degenerate triangle. */                                   eDegenerateTriangle        = -6,
    /** Degenerate rectangle. */                                  eDegenerateRectangle       = -7,
    /** Degenerate geodesic. */                                   eDegenerateGeodesic        = -8,
    /** Ill-defined geodesic (diametrically opposite points.) */  eIllDefinedGeodesic        = -9,
    /** Bad construction of the intersection point. */            eBadConstruction           = -10
  };

};

#endif

