#ifndef CATExpShewchukMacros_H
#define CATExpShewchukMacros_H

/* On some machines, the exact arithmetic routines might be defeated by the  */
/*   use of internal extended precision floating-point registers.  Sometimes */
/*   this problem can be fixed by defining certain values to be volatile,    */
/*   thus forcing them to be stored to memory and rounded off.  This isn't   */
/*   a great solution, though, as it slows the arithmetic down.              */
/*                                                                           */
/* To try this out, write "#define INEXACT volatile" below.  Normally,       */
/*   however, INEXACT should be defined to be nothing.  ("#define INEXACT".) */

#define INEXACT                          /* Nothing */
/* #define INEXACT volatile */

#define REALPRINT doubleprint
#define REALRAND doublerand
#define NARROWRAND narrowdoublerand
#define UNIFORMRAND uniformdoublerand

/* Which of the following two methods of finding the absolute values is      */
/*   fastest is compiler-dependent.  A few compilers can inline and optimize */
/*   the fabs() call; but most will incur the overhead of a function call,   */
/*   which is disastrously slow.  A faster way on IEEE machines might be to  */
/*   mask the appropriate bit, but that's difficult to do in C.              */

//#define Absolute(a)  ((a) >= 0.0 ? (a) : -(a))
#define Absolute(a)  std::fabs(a)

/* Many of the operations are broken up into two pieces, a main part that    */
/*   performs an approximate operation, and a "tail" that computes the       */
/*   roundoff error of that operation.                                       */
/*                                                                           */
/* The operations Fast_Two_Sum(), Fast_Two_Diff(), Two_Sum(), Two_Diff(),    */
/*   Split(), and Two_Product() are all implemented as described in the      */
/*   reference.  Each of these macros requires certain variables to be       */
/*   defined in the calling routine.  The variables `bvirt', `c', `abig',    */
/*   `_i', `_j', `_k', `_l', `_m', and `_n' are declared `INEXACT' because   */
/*   they store the result of an operation that may incur roundoff error.    */
/*   The input parameter `x' (or the highest numbered `x_' parameter) must   */
/*   also be declared `INEXACT'.                                             */

#define Fast_Two_Sum_Tail(a, b, x, y) \
bvirt = x - a; \
y = b - bvirt

#define Fast_Two_Sum(a, b, x, y) \
x = (double) (a + b); \
Fast_Two_Sum_Tail(a, b, x, y)

#define Fast_Two_Diff_Tail(a, b, x, y) \
bvirt = a - x; \
y = bvirt - b

#define Fast_Two_Diff(a, b, x, y) \
x = (double) (a - b); \
Fast_Two_Diff_Tail(a, b, x, y)

#define Two_Sum_Tail(a, b, x, y) \
bvirt = (double) (x - a); \
avirt = x - bvirt; \
bround = b - bvirt; \
around = a - avirt; \
y = around + bround

#define Two_Sum(a, b, x, y) \
x = (double) (a + b); \
Two_Sum_Tail(a, b, x, y)

#define Two_Diff_Tail(a, b, x, y) \
bvirt = (double) (a - x); \
avirt = x + bvirt; \
bround = bvirt - b; \
around = a - avirt; \
y = around + bround

#define Two_Diff(a, b, x, y) \
x = (double) (a - b); \
Two_Diff_Tail(a, b, x, y)

#define Split(a, ahi, alo) \
c = (double) (splitter * a); \
abig = (double) (c - a); \
ahi = c - abig; \
alo = a - ahi

#define Two_Product_Tail(a, b, x, y) \
Split(a, ahi, alo); \
Split(b, bhi, blo); \
err1 = x - (ahi * bhi); \
err2 = err1 - (alo * bhi); \
err3 = err2 - (ahi * blo); \
y = (alo * blo) - err3

#define Two_Product(a, b, x, y) \
x = (double) (a * b); \
Two_Product_Tail(a, b, x, y)

/* Two_Product_Presplit() is Two_Product() where one of the inputs has       */
/*   already been split.  Avoids redundant splitting.                        */

#define Two_Product_Presplit(a, b, bhi, blo, x, y) \
x = (double) (a * b); \
Split(a, ahi, alo); \
err1 = x - (ahi * bhi); \
err2 = err1 - (alo * bhi); \
err3 = err2 - (ahi * blo); \
y = (alo * blo) - err3

/* Two_Product_2Presplit() is Two_Product() where both of the inputs have    */
/*   already been split.  Avoids redundant splitting.                        */

#define Two_Product_2Presplit(a, ahi, alo, b, bhi, blo, x, y) \
x = (double) (a * b); \
err1 = x - (ahi * bhi); \
err2 = err1 - (alo * bhi); \
err3 = err2 - (ahi * blo); \
y = (alo * blo) - err3

/* Square() can be done more quickly than Two_Product().                     */

#define Square_Tail(a, x, y) \
Split(a, ahi, alo); \
err1 = x - (ahi * ahi); \
err3 = err1 - ((ahi + ahi) * alo); \
y = (alo * alo) - err3

#define Square(a, x, y) \
x = (double) (a * a); \
Square_Tail(a, x, y)

/* Macros for summing expansions of various fixed lengths.  These are all    */
/*   unrolled versions of Expansion_Sum().                                   */

#define Two_One_Sum(a1, a0, b, x2, x1, x0) \
Two_Sum(a0, b , _i, x0); \
Two_Sum(a1, _i, x2, x1)

#define Two_One_Diff(a1, a0, b, x2, x1, x0) \
Two_Diff(a0, b , _i, x0); \
Two_Sum( a1, _i, x2, x1)

#define Two_Two_Sum(a1, a0, b1, b0, x3, x2, x1, x0) \
Two_One_Sum(a1, a0, b0, _j, _0, x0); \
Two_One_Sum(_j, _0, b1, x3, x2, x1)

#define Two_Two_Diff(a1, a0, b1, b0, x3, x2, x1, x0) \
Two_One_Diff(a1, a0, b0, _j, _0, x0); \
Two_One_Diff(_j, _0, b1, x3, x2, x1)

#define Four_One_Sum(a3, a2, a1, a0, b, x4, x3, x2, x1, x0) \
Two_One_Sum(a1, a0, b , _j, x1, x0); \
Two_One_Sum(a3, a2, _j, x4, x3, x2)

#define Four_Two_Sum(a3, a2, a1, a0, b1, b0, x5, x4, x3, x2, x1, x0) \
Four_One_Sum(a3, a2, a1, a0, b0, _k, _2, _1, _0, x0); \
Four_One_Sum(_k, _2, _1, _0, b1, x5, x4, x3, x2, x1)

#define Four_Four_Sum(a3, a2, a1, a0, b4, b3, b1, b0, x7, x6, x5, x4, x3, x2, \
                  x1, x0) \
Four_Two_Sum(a3, a2, a1, a0, b1, b0, _l, _2, _1, _0, x1, x0); \
Four_Two_Sum(_l, _2, _1, _0, b4, b3, x7, x6, x5, x4, x3, x2)

#define Eight_One_Sum(a7, a6, a5, a4, a3, a2, a1, a0, b, x8, x7, x6, x5, x4, \
                  x3, x2, x1, x0) \
Four_One_Sum(a3, a2, a1, a0, b , _j, x3, x2, x1, x0); \
Four_One_Sum(a7, a6, a5, a4, _j, x8, x7, x6, x5, x4)

#define Eight_Two_Sum(a7, a6, a5, a4, a3, a2, a1, a0, b1, b0, x9, x8, x7, \
                  x6, x5, x4, x3, x2, x1, x0) \
Eight_One_Sum(a7, a6, a5, a4, a3, a2, a1, a0, b0, _k, _6, _5, _4, _3, _2, \
            _1, _0, x0); \
Eight_One_Sum(_k, _6, _5, _4, _3, _2, _1, _0, b1, x9, x8, x7, x6, x5, x4, \
            x3, x2, x1)

#define Eight_Four_Sum(a7, a6, a5, a4, a3, a2, a1, a0, b4, b3, b1, b0, x11, \
                    x10, x9, x8, x7, x6, x5, x4, x3, x2, x1, x0) \
Eight_Two_Sum(a7, a6, a5, a4, a3, a2, a1, a0, b1, b0, _l, _6, _5, _4, _3, \
            _2, _1, _0, x1, x0); \
Eight_Two_Sum(_l, _6, _5, _4, _3, _2, _1, _0, b4, b3, x11, x10, x9, x8, \
            x7, x6, x5, x4, x3, x2)

/* Macros for multiplying expansions of various fixed lengths.               */

#define Two_One_Product(a1, a0, b, x3, x2, x1, x0) \
Split(b, bhi, blo); \
Two_Product_Presplit(a0, b, bhi, blo, _i, x0); \
Two_Product_Presplit(a1, b, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _k, x1); \
Fast_Two_Sum(_j, _k, x3, x2)

#define Four_One_Product(a3, a2, a1, a0, b, x7, x6, x5, x4, x3, x2, x1, x0) \
Split(b, bhi, blo); \
Two_Product_Presplit(a0, b, bhi, blo, _i, x0); \
Two_Product_Presplit(a1, b, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _k, x1); \
Fast_Two_Sum(_j, _k, _i, x2); \
Two_Product_Presplit(a2, b, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _k, x3); \
Fast_Two_Sum(_j, _k, _i, x4); \
Two_Product_Presplit(a3, b, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _k, x5); \
Fast_Two_Sum(_j, _k, x7, x6)

#define Two_Two_Product(a1, a0, b1, b0, x7, x6, x5, x4, x3, x2, x1, x0) \
Split(a0, a0hi, a0lo); \
Split(b0, bhi, blo); \
Two_Product_2Presplit(a0, a0hi, a0lo, b0, bhi, blo, _i, x0); \
Split(a1, a1hi, a1lo); \
Two_Product_2Presplit(a1, a1hi, a1lo, b0, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _k, _1); \
Fast_Two_Sum(_j, _k, _l, _2); \
Split(b1, bhi, blo); \
Two_Product_2Presplit(a0, a0hi, a0lo, b1, bhi, blo, _i, _0); \
Two_Sum(_1, _0, _k, x1); \
Two_Sum(_2, _k, _j, _1); \
Two_Sum(_l, _j, _m, _2); \
Two_Product_2Presplit(a1, a1hi, a1lo, b1, bhi, blo, _j, _0); \
Two_Sum(_i, _0, _n, _0); \
Two_Sum(_1, _0, _i, x2); \
Two_Sum(_2, _i, _k, _1); \
Two_Sum(_m, _k, _l, _2); \
Two_Sum(_j, _n, _k, _0); \
Two_Sum(_1, _0, _j, x3); \
Two_Sum(_2, _j, _i, _1); \
Two_Sum(_l, _i, _m, _2); \
Two_Sum(_1, _k, _i, x4); \
Two_Sum(_2, _i, _k, x5); \
Two_Sum(_m, _k, x7, x6)

/* An expansion of length two can be squared more quickly than finding the   */
/*   product of two different expansions of length two, and the result is    */
/*   guaranteed to have no more than six (rather than eight) components.     */

#define Two_Square(a1, a0, x5, x4, x3, x2, x1, x0) \
Square(a0, _j, x0); \
_0 = a0 + a0; \
Two_Product(a1, _0, _k, _1); \
Two_One_Sum(_k, _1, _j, _l, _2, x1); \
Square(a1, _j, _1); \
Two_Two_Sum(_j, _1, _l, _2, x5, x4, x3, x2)


/*****************************************************************************/
/*                                                                           */
/*  exactinit()   Initialize the variables used for exact arithmetic.        */
/*                                                                           */
/*  `epsilon' is the largest power of two such that 1.0 + epsilon = 1.0 in   */
/*  floating-point arithmetic.  `epsilon' bounds the relative roundoff       */
/*  error.  It is used for floating-point error analysis.                    */
/*                                                                           */
/*  `splitter' is used to split floating-point numbers into two half-        */
/*  length significands for exact multiplication.                            */
/*                                                                           */
/*  I imagine that a highly optimizing compiler might be too smart for its   */
/*  own good, and somehow cause this routine to fail, if it pretends that    */
/*  floating-point arithmetic is too much like real arithmetic.              */
/*                                                                           */
/*  Don't change this routine unless you fully understand it.                */
/*                                                                           */
/*****************************************************************************/

#ifdef _AIX
#define CONSTEXPR static
#else
#define CONSTEXPR constexpr
#endif // _AIX

#include <utility>
#include <cmath>

namespace
{
  CONSTEXPR std::pair<double, double> ExactInit()
  {
    double half = 0.5;
    double check = 1., lastcheck = 0.;
    int every_other = 1;

    double epsilon = 1.0;
    double splitter = 1.0;
    /* Repeatedly divide `epsilon' by two until it is too small to add to    */
    /*   one without causing roundoff.  (Also check if the sum is equal to   */
    /*   the previous sum, for machines that round up instead of using exact */
    /*   rounding.  Not that this library will work on such machines anyway. */
    do {
      lastcheck = check;
      epsilon *= half;
      if (every_other) {
        splitter *= 2.0;
      }
      every_other = !every_other;
      check = 1.0 + epsilon;
    } while ((check != 1.0) && (check != lastcheck));
    splitter += 1.0;

    return std::make_pair(splitter, epsilon);
  }

  /* Error bounds for orientation and incircle tests. */

  CONSTEXPR std::pair<double, double> const splitterAndEpsilon = ExactInit();
  CONSTEXPR double const splitter = splitterAndEpsilon.first;
  CONSTEXPR double const epsilon = splitterAndEpsilon.second;
  CONSTEXPR double const resulterrbound = (3.0 + 8.0 * epsilon) * epsilon;
  CONSTEXPR double const ccwerrboundA = (3.0 + 16.0 * epsilon) * epsilon;
  CONSTEXPR double const ccwerrboundB = (2.0 + 12.0 * epsilon) * epsilon;
  CONSTEXPR double const ccwerrboundC = (9.0 + 64.0 * epsilon) * epsilon * epsilon;
  CONSTEXPR double const o3derrboundA = (7.0 + 56.0 * epsilon) * epsilon;
  CONSTEXPR double const o3derrboundB = (3.0 + 28.0 * epsilon) * epsilon;
  CONSTEXPR double const o3derrboundC = (26.0 + 288.0 * epsilon) * epsilon * epsilon;
  CONSTEXPR double const iccerrboundA = (10.0 + 96.0 * epsilon) * epsilon;
  CONSTEXPR double const iccerrboundB = (4.0 + 48.0 * epsilon) * epsilon;
  CONSTEXPR double const iccerrboundC = (44.0 + 576.0 * epsilon) * epsilon * epsilon;
  CONSTEXPR double const isperrboundA = (16.0 + 224.0 * epsilon) * epsilon;
  CONSTEXPR double const isperrboundB = (5.0 + 72.0 * epsilon) * epsilon;
  CONSTEXPR double const isperrboundC = (71.0 + 1408.0 * epsilon) * epsilon * epsilon;
}

#endif
