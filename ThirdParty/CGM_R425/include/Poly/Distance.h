// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// Poly/Distance.h
//
//===================================================================
//
// Usage notes: many distance methods between canonical polyhedral objects
//
//===================================================================
// 06/21 : F1Z : Creation (expose low level methods impl in CATPolyOverlayContactDetector)
//===================================================================

#pragma once

// Mathematics & co
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathConstant.h"
#include "CATMathLimits.h"

// PolyhedralMathematics
#include "PolyMathUtils.h"
#include "CATPolyExactArithmetic.h"

namespace Poly
{
  namespace SqDistanceMin
  {
    /**
     *  @brief Computes the squared min distance between a point and a segment.
     *  @param oParam is a pointer toward a double
     *  @param oSqDistance is the computed squared distance
     */
    ExportedByPolyMathUtils void PointSegment(const CATPolyExactArithmetic & ea,
                                              const CATMathPoint& iPt,
                                              const CATMathPoint& iSP0, const CATMathPoint& iSP1,
                                              double & oSqDistance,
                                              double * oParam = NULL);

    /**
     *  @brief Computes the squared min distance between a point and a triangle.
     *  @param iTol is the maximum distance allowed. Use for performance optimisation and validity of the result.
     *  @param oParam is an array of three double (barycentric coordinate on the triangle)
     *  @param oSqDistance is the computed squared distance
     *  @return true if the min distance is computed and under iTol
     */
    ExportedByPolyMathUtils bool PointTriangle(const CATPolyExactArithmetic & ea,
                                               const CATMathPoint& iPt,
                                               const CATMathPoint& iTP0, const CATMathPoint& iTP1, const CATMathPoint& iTP2,
                                               double & oSqDistance,
                                               double * oParam = NULL,
                                               double   iTol = CATdoubleMax);



    /** @name Method for sq min distance computation, where the min distance is strictly IN(side) the elements
     @{ */
    namespace In
    {
      /**
       *  @brief Computes the squared min distance between a point and a segment.
       *  @param oParam is a pointer toward a double
       *  @param oSqDistance is the computed squared distance
       *  @return true if the min distance in in the segment (not on its extremities)
       */
      ExportedByPolyMathUtils bool PointSegment(const CATPolyExactArithmetic & ea,
                                                const CATMathPoint& iPt,
                                                const CATMathPoint& iSP0, const CATMathPoint& iSP1,
                                                double & oSqDistance,
                                                double * oParam = NULL);

      /**
       *  @brief Computes the squared min distance between a point and a triangle.
       *  @param iTol is the maximum distance allowed. Use for performance optimisation and validity of the result.
       *  @param oParam is an array of three doubles
       *  @param oSqDistance is the computed squared distance
       *  @return true if the min distance is computed and under iTol and is in the triangle (not on its borders)
       */
      ExportedByPolyMathUtils bool PointTriangle(const CATPolyExactArithmetic & ea,
                                                 const CATMathPoint& iPt,
                                                 const CATMathPoint& iTP0, const CATMathPoint& iTP1, const CATMathPoint& iTP2,
                                                 double & oSqDistance,
                                                 double * oParam = NULL,
                                                 double   iTol = CATdoubleMax);

      /**
       *  @brief Computes the squared min distance between two segments.
       *  @param oParam is an array of size two (on param per bar)
       *  @param oSqDistance is the computed squared distance
       *  @return true if the min distance is computed and is in each bars (not on their extremities)
       */
      ExportedByPolyMathUtils bool SegmentSegment(const CATPolyExactArithmetic & ea,
                                                  const CATMathPoint& iS0P0, const CATMathPoint& iS0P1,
                                                  const CATMathPoint& iS1P0, const CATMathPoint& iS1P1,
                                                  double & oSqDistance,
                                                  double * oParam = NULL);

      /**
       *  @brief Computes the intersection between a segment and a triangle  
       *  (in this case, intersection <=> min dist since it is strictly internal to the elements).
       *  @param oParamSegment is the parameter on the segment (double)
       *  @param oParamTriangle is the parameter on the triangle (array of three)
       *  @return true if the min distance/intersection is computed.
       */
      ExportedByPolyMathUtils bool SegmentTriangle(const CATPolyExactArithmetic & ea,
                                                  const CATMathPoint& iSP0, const CATMathPoint& iSP1,
                                                  const CATMathPoint& iTP0, const CATMathPoint& iTP1, const CATMathPoint& iTP2,
                                                  double * oParamSegment = NULL,
                                                  double * oParamTriangle = NULL);
    }; // end IN namespace
    /** @} */

  }; // end SqDistanceMin namespace

}; // end Poly namespace
