// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleServices.h
//
//===================================================================
// January 2014 Creation: ndo
//===================================================================
#ifndef CATPolyTriangleServices_h
#define CATPolyTriangleServices_h

#include "PolyMathUtils.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATMathPoint;
class CATMathVector;


/** @file 
 * Various services about triangles.
 *
 * List of services:
 * <ul>
 *   <li> Check the geometry and aspect ratio of a triangle.
 *  </ul>
 */


/** @name Triangle Services
    @{ */

/**
 * Checks the geometry of a triangle and particularly its aspect ratio.
 * If the triangle is degenerate (triangle is flat or one side has length 0), the method returns FALSE.
 * The method is scale-invariant.  The result returned is the same regardless of the scale of the triangle.
 * Specifically, the methods checks that:
 *   o The ratio of the smallest to the longest sides does not fall below an input threshold: iRelativeLengthRatio.
 *   o The mimimum angle in the triangle is not below a given value.
 * @param P
 *   An array of three points each having three double-precision coordinates.
 * @param iRelativeLengthRatio
 *   The ratio for comparison of the longest and smallest triangle sides.
 * @param 
 *   The sine of the smallest acceptable angle for the triangle. Any triangle with an angle whose sine is smaller than the input value is invalid.
 * @param
 *   If this argument is set, returns the squares of the lengths of the sides of the triangle, P[0]P[1], P[1]P[2], P[2]P[0], respectively.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the triangle passes the geometry check.
 *   <li> <tt>S_FALSE</tt> if the triangle fails the geometry check.
 * </ul>
 */
ExportedByPolyMathUtils CATBoolean CATPolyCheckTriangleGeometry (const double* P[3], const double iRelativeLengthRatio, const double iSineOfMinimumAngle,
                                                                 double** oSquaredLengths = 0);

/**
 * Checks the geometry of a triangle and particularly its aspect ratio.
 * If the triangle is degenerate (triangle is flat or one side has length 0), the method returns FALSE.
 * The method is scale-invariant.  The result returned is the same regardless of the scale of the triangle.
 * Specifically, the methods checks that:
 *   o The ratio of the smallest to the longest sides does not fall below an input threshold: iRelativeLengthRatio.
 *   o The mimimum angle in the triangle is not below a given value.
 * @param P
 *   An array of three CATMathPoint.
 * @param iRelativeLengthRatio
 *   The ratio for comparison of the longest and smallest triangle sides.
 * @param 
 *   The sine of the smallest acceptable angle for the triangle. Any triangle with an angle whose sine is smaller than the input value is invalid.
 * @param
 *   If this argument is set, returns the squares of the lengths of the sides of the triangle, P[0]P[1], P[1]P[2], P[2]P[0], respectively.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the triangle passes the geometry check.
 *   <li> <tt>S_FALSE</tt> if the triangle fails the geometry check.
 * </ul>
 */
ExportedByPolyMathUtils CATBoolean CATPolyCheckTriangleGeometry (const CATMathPoint P[3], const double iRelativeLengthRatio, const double iSineOfMinimumAngle,
                                                                 double** oSquaredLengths = 0);


/**
 * Given three points, P[0], P[1] and P[2], computes the triangle normal, N.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> A triangle normal was computed.
 *   <li> <tt>E_FAIL</tt> A triangle normal cannot be computed.
 * </ul>
 */
ExportedByPolyMathUtils HRESULT CATPolyComputeTriangleNormal (const CATMathPoint P[3], CATMathVector& N);

/**
 * Computes and returns the area of the triangle (A, B, C).
 */
ExportedByPolyMathUtils double CATPolyComputeTriangleArea (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C);

/**
 * Given three points, P[0], P[1] and P[2], computes the shape factor of a triangle.
 * The shape factor is a double ranging from 0 to 1.  An equilateral triangle has a shape factor equals to 1.
 * A degenerate triangle has a shape factor equals to 0.
 * @return
 *   The shape factor 
 */
ExportedByPolyMathUtils double CATPolyComputeShapeFactor (const CATMathPoint P[3]);

/** @} */

#endif
