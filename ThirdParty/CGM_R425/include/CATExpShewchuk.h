#ifndef CATExpShewchuk_H
#define CATExpShewchuk_H

#include "CATMathExactPredicates.h"

class CATExpShewchuk
{
public:
  /* Return a positive value if the point pd lies below the plane passing through pa, pb, and pc; "below" is defined so that pa, pb, and pc appear in counterclockwise order when viewed from above the plane. 
   * Returns a negative value if pd lies above the plane.  Returns zero if the points are coplanar. 
   * The result is also a rough approximation of six times the signed volume of the tetrahedron defined by the four points.
   *
   * @param pa double array of length 3
   * @param pb double array of length 3
   * @param pc double array of length 3
   * @param pd double array of length 3
   * @return Orientation of the four points
   *
   * orient3d should be faster than orient3dexact since it used adaptative computation to do exact computation only when needed.
   */
  ExportedByCATMathExactPredicates static double orient3dexact(double const *pa, double const *pb, double const *pc, double const *pd);
  ExportedByCATMathExactPredicates static double orient3d(double const *pa, double const *pb, double const *pc, double const *pd);
  
  /* Return a positive value if the point pd lies below the plane passing through pa, pb, and pc; "below" is defined so that pa, pb, and pc appear in counterclockwise order when viewed from above the plane.
  * Returns a negative value if pd lies above the plane.  Returns zero if the points are coplanar.
  * The result is also a rough approximation of six times the signed volume of the tetrahedron defined by the four points.
  *
  * @param pa double array of length 3
  * @param pb double array of length 3
  * @param pc double array of length 3
  * @param pd1 double array of length 3
  * @param pd2 double array of length 3
  * @param pd3 double array of length 3
  * @return Orientation of the four points
  *
  * orient3d should be faster than orient3dexact since it used adaptative computation to do exact computation only when needed.
  * VKH1: Same method as  double orient3d(double const *pa, double const *pb, double const *pc, double const *pd);
  *       but 
  */
  ExportedByCATMathExactPredicates static double orient3d(double const *pa, double const *pb, double const *pc, double const *pd1, double const *pd2, double const *pd3);

  /* Return a positive value if the points pa, pb, and pc occur in counterclockwise order; a negative value if they occur  in clockwise order; and zero if they are collinear.
   * The result is also a rough approximation of twice the signed area of the triangle defined by the three points.
   *
   * @param pa double array of length 2
   * @param pb double array of length 2
   * @param pc double array of length 2
   * @return Orientation of the three points
   *
   * orient2d should be faster than orient2dexact since it used adaptative computation to do exact computation only when needed.
   */
  ExportedByCATMathExactPredicates static double orient2dexact(double const *pa, double const *pb, double const *pc);
  ExportedByCATMathExactPredicates static double orient2d(double const* pa, double const* pb, double const* pc);

  /* Compute approximation and exact sign of det(CA, DB)
   */
  ExportedByCATMathExactPredicates static double orient2d(double const *pa, double const *pb, double const *pc, double const* pd);

  /* Return a positive value if the point pe lies inside the sphere passing through pa, pb, pc, and pd; a negative value if it lies outside; and zero if the five points are cospherical.
   * The points pa, pb, pc, and pd must be ordered so that they have a positive orientation (as defined by orient3d()), or the sign of the result will be reversed.
   *
   * @param pa double array of length 3
   * @param pb double array of length 3
   * @param pc double array of length 3
   * @param pd double array of length 3
   * @param pe double array of length 3
   * @return A determinant
   *
   * insphere should be faster than insphereexact since it used adaptative computation to do exact computation only when needed.
   */
  ExportedByCATMathExactPredicates static double insphereexact(double const *pa, double const *pb, double const *pc, double const *pd, double *pe);
  ExportedByCATMathExactPredicates static double insphere(double const *pa, double const *pb, double const *pc, double const *pd, double *pe);

  /* Return a positive value if the point pd lies inside the circle passing through pa, pb, and pc; a negative value if it lies outside; and zero if the four points are cocircular.
   * The points pa, pb, and pc must be in counterclockwise order, or the sign of the result will be reversed.
   * 
   * @param pa double array of length 2
   * @param pb double array of length 2
   * @param pc double array of length 2
   * @param pd double array of length 2
   * @return A determinant
   *
   * incircle should be faster than incircleexact since it used adaptative computation to do exact computation only when needed.
   */
  ExportedByCATMathExactPredicates static double incircleexact(double const *pa, double const *pb, double const *pc, double const *pd);
  ExportedByCATMathExactPredicates static double incircle(double const *pa, double const *pb, double const *pc, double const *pd);

public:
  ExportedByCATMathExactPredicates static int grow_expansion(int elen, double *e, double b, double *h);
  ExportedByCATMathExactPredicates static int grow_expansion_zeroelim(int elen, double *e, double b, double *h);
  
  ExportedByCATMathExactPredicates static int expansion_sum(int elen, double *e, int flen, double *f, double *h);
  ExportedByCATMathExactPredicates static int expansion_sum_zeroelim1(int elen, double *e, int flen, double *f, double *h);
  ExportedByCATMathExactPredicates static int expansion_sum_zeroelim2(int elen, double *e, int flen, double *f, double *h);
  ExportedByCATMathExactPredicates static int fast_expansion_sum(int elen, double *e, int flen, double *f, double *h);
  ExportedByCATMathExactPredicates static int fast_expansion_sum_zeroelim(int elen, double const *e, int flen, double const *f, double *h);
  
  ExportedByCATMathExactPredicates static int linear_expansion_sum(int elen, double *e, int flen, double *f, double *h);
  ExportedByCATMathExactPredicates static int linear_expansion_sum_zeroelim(int elen, double *e, int flen, double *f, double *h);
  
  ExportedByCATMathExactPredicates static int scale_expansion(int elen, double *e, double b, double *h);
  ExportedByCATMathExactPredicates static int scale_expansion_zeroelim(int elen, double const *e, double b, double *h);
  
  ExportedByCATMathExactPredicates static int compress(int elen, double *e, double *h);
  ExportedByCATMathExactPredicates static double estimate(int elen, double const *e);

private:
  static double orient2dfast(double const *pa, double const *pb, double const *pc);
  static double orient2dslow(double const *pa, double const *pb, double const *pc);
  static double orient2dadapt(double const *pa, double const *pb, double const *pc, double const* pd, double detsum);

  static double orient3dfast(double const *pa, double const *pb, double const *pc, double const *pd);
  static double orient3dslow(double const *pa, double const *pb, double const *pc, double const *pd);

  // VKH1: For Shewchuk optimization
  //   double orient3dadapt(double const *pa, double const *pb, double const *pc, double const *pd, double permanent);
  static double orient3dadapt(double const *pa, double const *pb, double const *pc, double const *pd1, double const *pd2, double const *pd3, double permanent);
     
  static double incirclefast(double const *pa, double const *pb, double const *pc, double const *pd);
  static double incircleslow(double const *pa, double const *pb, double const *pc, double const *pd);
  static double incircleadapt(double const *pa, double const *pb, double const *pc, double const *pd, double permanent);
  static double inspherefast(double const *pa, double const *pb, double const *pc, double const *pd, double *pe);
  static double insphereslow(double const *pa, double const *pb, double const *pc, double const *pd, double *pe);
  static double insphereadapt(double const *pa, double const *pb, double const *pc, double const *pd, double *pe, double permanent);
};

#endif
