#ifndef CATMATHINTERVAL_H
#define CATMATHINTERVAL_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


// (DS ONLY. temporary) Detection/traitement des intervalles vides dans operateurs || et &&
// #define CATMATHINTERVAL_ThrowIfInvalid_TestOnlyNLD180516 "********* TEST ONLY NE PAS LIVRER ACTIF ********"
// #define CATMATHINTERVAL_FixIfInvalid_TestOnlyNLD180516   "********* TEST ONLY NE PAS LIVRER ACTIF ********"

   #ifdef CATMATHINTERVAL_ThrowIfInvalid_TestOnlyNLD180516
    #define CATMATHINTERVAL_DetectInvalid
   #endif
   #ifdef CATMATHINTERVAL_FixIfInvalid_TestOnlyNLD180516
    #define CATMATHINTERVAL_DetectInvalid
   #endif



/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"

#include "CATIACGMLevel.h"
#include "CATMathDef.h"
#include "CATMathLimits.h"
#include "CATMathInline.h"
#include "CATThrowForNullPointer.h"

/**
 * Class representing a closed bounded interval of R. 
 * <br>A CATMathInterval is the set of the reals <tt>x</tt> lying between two 
 * real bounds <tt>Low</tt> and <tt>High</tt>: <tt>Low <= x <= High</tt>.
 * If <tt>Low > High</tt>, the interval is empty.
 */
class ExportedByYN000FUN CATMathInterval
{
 public:

/**
 * Constructs a CATMathInterval with <tt> Low = High = 0</tt>.
 */
   INLINE CATMathInterval ();

/**
 * Constructs a CATMathInterval.
 * <br> If <tt>iLow > iHigh</tt>, the interval is empty.
 */
   INLINE CATMathInterval (const double & iLow, const double & iHigh);
  
   
/**
 * Copy Constructor.
 */
   INLINE CATMathInterval (const CATMathInterval & iToCopy);
  
//
//------------------Get/Set methods
//
/**
 * Returns the low limitation of <tt>this</tt> CATMathInterval.
 * @return
 * The low limitation.
 */
  INLINE double GetMin() const;

/**
 * Returns the high limitation of <tt>this</tt> CATMathInterval.
 * @return
 * The high limitation.
 */
  INLINE double GetMax() const;

/**
 * Modifies the low limitation of <tt>this</tt> CATMathInterval.
 * @param iNewLow
 * The new value of the low limitation.
 */
  INLINE void SetMin(const double & iNewLow);

/**
 * Modifies the high limitation of <tt>this</tt> CATMathInterval.
 * @param iNewHigh
 * The new value of the high limitation.
 */
  INLINE void SetMax(const double & iNewHigh);
//
//------------------Main characteristics#
//
/**
 * Returns the center  of <tt>this</tt> CATMathInterval.
 * @return
 * The center (<tt>(High + Low)*0.5</tt>).
 */
  INLINE double Center() const;

/**
 * Returns the width  of <tt>this</tt> CATMathInterval.
 * @return
 * The width (<tt>(High - Low)</tt>).
 */
  INLINE double Width() const;

/**
 * Tests if <tt>this</tt> CATMathInterval is empty.
 * @return
 *  The result of the test.
 * <br><b>Legal values</b>: <tt>1</tt> if <tt>Low > High</tt>,
 * <tt>0</tt> otherwise.
 */
  INLINE CATLONG32    IsEmpty() const;

/**
 * Tests the relative position of <tt>this</tt> CATMathInterval with regards
 * to <tt>0</tt>.
 * @return
 *  The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt><dd> if <tt>Low > 0</tt> or the interval is empty.
 *     <dt><tt>-1</tt><dd> if <tt>Low < 0</tt> and the interval is not empty.
 *     <dt><tt>0</tt><dd> otherwise. In this case, <tt>0</tt> belongs to
 * the interval, which is not empty</dl> 
 */
  CATLONG32    Sign() const;

/**
 * Returns the norm of <tt>this</tt> CATMathInterval.
 * <br> This norm may be negative if the interval is empty.
 * @return
 *  The norm.
 * <dl><dt><tt>High</tt><dd> if <tt>Low > 0</tt>.
 *     <dt><tt>-Low</tt><dd> if <tt>High < 0</tt>.
 *     <dt><tt>High</tt><dd> if <tt>High >= -Low</tt>(and the interval
 * is not empty)
 *     <dt><tt>-Low</tt><dd> <tt>High < -Low</tt>(and the interval
 * is not empty)</dl> 
 * @return
 * The norm.
 */
#ifdef CATIACGMV5R21
  INLINE double Norm() const;
#else
  double Norm() const;
#endif

/**
 * Tests if <tt>this</tt> CATMathInterval is included into an other one.
 * @param iOther
 * The other interval.
 * @return
 *  The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt><dd> if <tt>this</tt> is included.
 *     <dt><tt>0</tt><dd> otherwise</dl>.
 * <br> An empty interval is always included into another one, 
 * except if this other one is empty too. 
 */
  CATLONG32  IsIncludedIn(const CATMathInterval & iOther) const;

/**
 * Tests if <tt>this</tt> CATMathInterval is included into an other one
 * at a given absolute tolerance.
 * @param iOther
 * The other interval
 * @param iTol
 * The tolerance at which the tests is run.
 * @return
 *  The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt><dd> if <tt>this</tt> is included.
 *     <dt><tt>0</tt><dd> otherwise</dl>.
 * <br> An empty interval is always included into another one, 
 * except if this other one is empty too. 
 */
  CATLONG32  IsIncludedIn(const CATMathInterval & iOther, const double iTol) const;

/**
 * Return the distance between <tt>this</tt> CATMathInterval and a point.
 * @param iPoint
 * The value to which the distance is computed.
 * @return
 * <dl><dt><tt>0</tt><dd> if the point is included into <tt>this</tt>.
 *     <dt><tt>iPoint-High</tt><dd> if the point does not belong to <tt>this</tt>
 * and <tt> iPoint >= High</tt>
 *     <dt><tt>Low-iPoint</tt><dd> if the point does not belong to <tt>this</tt>
 * and <tt>Low>=iPoint</tt>
 *</dl>.
 * @return
 The distance.
 */
#ifdef CATIACGMV5R21
  INLINE double DistanceTo(const double & iPoint) const;
#else
  double DistanceTo(const double & iPoint) const;
#endif

/**
 * Translates a point to locate it at <tt>this</tt> CATMathInterval point 
 * such that the distance between these two points
 * is a multiple of <tt>this</tt> CATMathInterval width.<br>
 * This is useful in case of periodic functions to find the parameter of the
 * fundamental interval corresponding to a given point.
 * @param ioToTranslate
 * The point to translate (in input), and the resulting one (in output).
 */
  void PeriodicResidue(double & ioToTranslate);

/**
 * Tests whether a point belongs to <tt>this</tt> CATMathInterval 
 * after a given number of translation of length + or -<tt>iPeriod+iTolerance</tt>.
 * <br>
 * The difference with the preceding method, is that <tt>iPeriod</tt>
 * is greater than the width of the CATMathInterval (the CATMathInterval
 * may be seen as a trimmed interval of the </tt>[0,iPeriod]</tt> one.)
 * @param iPoint
 * The tested point.
 * @param iPeriod
 * A value greater than the with of <tt>this</tt> CATMathInterval.
 * @param iTol
 * The tolerance at which the tests is run.
 * @return
 * TRUE if iPoint is in the interval with regards to iPeriod, FALSE otherwise.
 */
  CATBoolean InPeriodicTrim(const double iPoint , const double iPeriod,
                      const double iTolerance = 0.0);

/**
 * Retrieves the closest external point of <tt>this</tt> CATMathInterval among those obtained
 * by all the successive translations of length + or -<tt>iPeriod</tt>.
 * @param iPoint
 * The initial point (input) and the resulting one (output).
 * @param iPeriod
 * The period.
 * @return
 * The distance between this point and the initial one.
 */
  double ClosestPeriodicEndpoint(double & ioPoint, const double iPeriod);
  

/**
 * @nodoc
 */
  friend ExportedByYN000FUN ostream& operator <<
    (ostream& s, const CATMathInterval & i);

//
//- Operators
//
/**
 * Returns the square root interval of a CATMathInterval.
 * @return
 * <dl><dt><tt>[0]</tt><dd> if <tt>High <= 0</tt>
 *     <dt><tt>[0,sqrt(High)]</tt><dd> if <tt>Low <= 0</tt> and <tt>High <= 0</tt>
 *     <dt><tt>[sqrt(Low),sqrt(High)]</tt><dd> otherwise</dl>
 */
  ExportedByYN000FUN friend CATMathInterval sqrt(const CATMathInterval & iToOperate);  

/**
 * Returns the square interval of a CATMathInterval.
 * @return
 * <dl><dt><tt>[Low*Low,High*High]</tt><dd> if <tt>Low >= 0</tt>
 *     <dt><tt>[High*High,Low*Low]</tt><dd> if <tt>High <= 0</tt> 
 *     <dt><tt>[0,High*High]</tt><dd> if <tt>Low*Low <= High*High </tt>(and the interval
 * is not empty)
 *     <dt><tt>[0,Low*Low]</tt><dd>if <tt>Low*Low > High*High </tt>(and the interval
 * is not empty)</dl>
 */
  ExportedByYN000FUN friend CATMathInterval square(const CATMathInterval & iToOperate); 

/**
 * Returns the absolute value interval of a CATMathInterval.
 * @return
 * <dl><dt><tt>[Low,High]</tt><dd> if <tt>Low >= 0</tt>
 *     <dt><tt>[-High,-Low]</tt><dd> if <tt>High <= 0</tt> 
 *     <dt><tt>[0,High]</tt><dd> if <tt>-Low <= High </tt>(and the interval
 * is not empty)
 *     <dt><tt>[0,-Low]</tt><dd>if <tt>-Low > High </tt>(and the interval
 * is not empty)</dl>
 */  
  ExportedByYN000FUN friend CATMathInterval abs(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the sine function on a CATMathInterval.
 * @return 
 *  <tt>[inf( sin(x),x in iToOperate ),max( sin(x),x in iToOperate )]</tt> 
 */   
  ExportedByYN000FUN friend CATMathInterval sin(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the cosine function on a CATMathInterval.
 * @return 
 *  <tt>[inf( cos(x),x in iToOperate ),max( cos(x),x in iToOperate )]</tt> 
 */   
  ExportedByYN000FUN friend CATMathInterval cos(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of function A*cos(x)+B*sin(x) on a CATMathInterval.
 * @return
 *  <tt>[inf( A*cos(x)+B*sin(x),x in iToOperate ),max( A*cos(x)+B*sin(x),x in iToOperate )]</tt>
 */
  ExportedByYN000FUN friend CATMathInterval ACosPlusBSin(const CATMathInterval & iToOperate, double A, double B);

/**
 * Returns the interval resulting of the application of the arctangent function on a CATMathInterval.
 * @return 
 *  <tt>[inf( arctan(x),x in iToOperate ),max( arctan(x),x in iToOperate )]</tt> 
 */   
  ExportedByYN000FUN friend CATMathInterval atan(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the arctangent function on a CATMathInterval.
 * @return 
 *  <tt>[inf( arctan(x),x in iToOperate ),max( arctan(x),x in iToOperate )]</tt> 
 */   
  ExportedByYN000FUN friend CATMathInterval atan2(const CATMathInterval & iY,
                                                  const CATMathInterval & iX );

/**
 * Returns the interval resulting of the application of the hyperbolic 
 * sine function on a CATMathInterval.
 * @return 
 *  <tt>[sinh(Low),sinh(High)]</tt> 
 */ 
  ExportedByYN000FUN friend CATMathInterval sinh(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the hyperbolic 
 * cosine function on a CATMathInterval.
 * @return 
 *  <tt>[min( cosh(x), x in this ),max (cosh(x),x in this)]</tt> 
 */  
  ExportedByYN000FUN friend CATMathInterval cosh(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the hyperbolic 
 * tangent function on a CATMathInterval.
 * @return 
 *  <tt>[tanh(Low),tanh(High)]</tt> 
 */ 
  ExportedByYN000FUN friend CATMathInterval tanh(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the exponential 
 * function on a CATMathInterval.
 * @return 
 *  <tt>[exp(Low),exp(High)]</tt> 
 */   
  ExportedByYN000FUN friend CATMathInterval exp(const CATMathInterval & iToOperate);

/**
 * Returns the interval resulting of the application of the logarithmic 
 * function on a CATMathInterval.
 * @return 
 *  <tt>[log(Low),log(High)]</tt> 
 */    
  ExportedByYN000FUN friend CATMathInterval log(const CATMathInterval & iToOperate);

//  Comparison
/**
 * Equality operator.
 * @return
 * <dl> <dt><tt>1</tt></dt><dd> if <tt>i1.GetMin==i2.GetMin</tt> and
 * <tt>i1.GetMax()==i2.GetMax()</tt>
 *       <dt><tt>0</tt></dt><dd> otherwise </dl>
 */
  friend ExportedByYN000FUN CATBoolean operator ==
    (const CATMathInterval & i1, const CATMathInterval & i2);

/**
 * Inequality operator.
 * @return
 * <dl> <dt><tt>0</tt></dt><dd> if <tt>i1.GetMin==i2.GetMin</tt> and
 * <tt>i1.GetMax()==i2.GetMax()</tt>
 *       <dt><tt>1</tt></dt><dd> otherwise </dl>
 */
  friend ExportedByYN000FUN CATBoolean operator !=
    (const CATMathInterval & i1, const CATMathInterval & i2);

//  Intersection
/**
 * Returns the interval resulting of the intersection of two CATMathIntervals.
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator &&
    (const CATMathInterval & i1, const CATMathInterval & i2);
      

//  Union
/**
 * Returns the interval resulting of the union of two CATMathIntervals.
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator ||
    (const CATMathInterval & i1, const CATMathInterval & i2);

//  Addition
/**
 * Unary plus operator.
 * @return
 * <tt>[i1.GetMin()+i2.GetMin(),i1.GetMax()+i2.GetMax()]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator +
    (const CATMathInterval & i1, const CATMathInterval & i2);

/**
 * Addition assignment operator.
 * @return 
 * <tt>io1 = [io1.GetMin()+=i2.GetMin(),io1.GetMax()+=i2.GetMax()]</tt>
 */
  INLINE friend ExportedByYN000FUN void operator +=
    (CATMathInterval & io1, const CATMathInterval & i2);
      

//  Substraction
/**
 * Subtraction operator.
 * @return
 * <tt>[i1.GetMin()-i2.GetMin(),i1.GetMax()-i2.GetMax()]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator -
    (const CATMathInterval & i1, const CATMathInterval & i2);
      
/**
 * Subtraction assignment operator.
 * @return 
 * <tt>io1= [i1.GetMin()-=i2.GetMax(),i1.GetMax()-=i2.GetMin()]</tt>
 */
  INLINE friend ExportedByYN000FUN void operator -=
    (CATMathInterval & io1, const CATMathInterval & i2);
      

//  Multiplication
/**
 * Defines the *= operator of a CATMathInterval with a scalar.
 * @return
 * <dl><dt><tt>[io.GetMin()*=iScalar,io.GetMax()*=iScalar]</tt>
 *                 <dd> if <tt>iScalar>0</tt>
 *     <dt><tt>[io.GetMax()*=iScalar,io.GetMin()*=iScalar]</tt>
 *                 <dd> if <tt>iScalar<=0</tt></dl>
 */
  INLINE friend ExportedByYN000FUN void operator *=
    (CATMathInterval & io, const double iScalar);

/**
 * Multiplication operator.
 * @return 
 * [inf (xy, x in i1, y in i2),sup (xy, x in i1, y in i2) ]
 * ne pas passer en forceinline car bug compilo 64 bits sur CATOffsetRevolProfileEquationX
  */
  inline friend ExportedByYN000FUN CATMathInterval operator *
    (const CATMathInterval & i1, const CATMathInterval & i2);
      

//  Division
/**
 * Defines the dividion of a CATMathInterval by another one.
 * @return 
 * <dl> <dt><tt>i1*[1/i2.GetMax(), 1/i2.GetMin()]</tt>
 *          <dd>if <tt>i2.GetMax()*i2.GetMin() >0</tt>
 *     <dt><tt>[-CATMathInfinite,CATMathInfinite]</tt>
 *          <dd>if <tt>i2.GetMax()*i2.GetMin() <=0</tt></dl>
  */
  INLINE friend ExportedByYN000FUN CATMathInterval operator /
    (const CATMathInterval & i1, const CATMathInterval & i2);
  

//  Opposite
/**
 * Defines the opposite of a CATMathInterval.
 * @return
 * <tt>[-i.GetMax(),-i.GetMin()]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator -
    (const CATMathInterval & i);
      

//  Scalar Addition
/**
 * Defines the scalar addition with a CATMathInterval.
 * @return
 * <tt>[i.GetMin()+iScalar,i.GetMax()+iScalar]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator +
    (const double & iScalar, const CATMathInterval & i);
      
/**
 * Defines the addition of a CATMathInterval with a scalar.
 * @return
 * <tt>[i.GetMin()+iScalar,i.GetMax()+iScalar]</tt>
 */
  INLINE friend ExportedByYN000FUN  CATMathInterval operator +
    (const CATMathInterval & i, const double & iScalar);
      
/**
 * Defines the += operator of a CATMathInterval with a scalar.
 * @return 
 * <tt>io = [io.GetMin()+=iScalar,io.GetMax()+=iScalar]</tt>
 */
  INLINE friend ExportedByYN000FUN void operator +=
    (CATMathInterval & io, const double & iScalar);
      

//  Scalar Substraction
/**
 * Defines the scalar substraction with a CATMathInterval.
 * @return  
 * <tt>[iScalar-i.GetMin(),iScalar-i.GetMax()]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator -
    (const double & iScalar, const CATMathInterval & i);
     
/**
 * Defines the scalar substraction with a CATMathInterval.
 * @return
 * <tt>[i.GetMin()-iScalar,i.GetMax()-iScalar]</tt>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator -
    (const CATMathInterval & i, const double & iScalar);
      
/**
 * Defines the -= operator of a CATMathInterval with a scalar.
 * @return 
 * <tt>io = [io.GetMin()-=iScalar,io.GetMax()-=iScalar]</tt>
 */
  INLINE friend ExportedByYN000FUN void operator -=
    (CATMathInterval & io, const double & iScalar);
      

//  Scalar Multiplication
/**
 * Defines the multiplication of a CATMathInterval with a scalar.
 * @return
 * <dl><dt><tt>[i.GetMin()*iScalar,i.GetMax()*iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar>0</tt>
 *     <dt><tt>[i.GetMax()*iScalar,i.GetMin()*iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar<=0</tt></dl>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator *
    (const double & iScalar, const CATMathInterval & i);
 
/**
 * Defines the multiplication of a scalar with a CATMathInterval.
 * @return
 * <dl><dt><tt>[i.GetMin()*iScalar,i.GetMax()*iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar>0</tt>
 *     <dt><tt>[i.GetMax()*iScalar,i.GetMin()*iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar<=0</tt></dl>
 */ 
  INLINE friend ExportedByYN000FUN CATMathInterval operator *
    (const CATMathInterval & i, const double & iScalar);
      

//  Scalar Division
/**
 * Defines the division of a scalar by a CATMathInterval.
 * @return 
 * <dl> <dt><tt>iScalar*[1/i2.GetMax(), 1/i2.GetMin()]</tt></dt>
 *          <dd>if <tt>i2.GetMax()*i2.GetMin() >0</tt>
 *      <dt><tt>[-CATMathInfinite,CATMathInfinite]</tt></dt>
 *          <dd>if <tt>i2.GetMax()*i2.GetMin() <=0</tt></dl>
  */
  friend ExportedByYN000FUN CATMathInterval operator /
    (const double & iScalar, const CATMathInterval & i);

/**
 * Defines the division of a CATMathInterval by a scalar.
 * @return
 * <dl><dt><tt>[i.GetMin()/iScalar,i.GetMax()/iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar>0</tt>
 *     <dt><tt>[i.GetMax()/iScalar,i.GetMin()/iScalar]</tt></dt>
 *                 <dd> if <tt>iScalar<=0</tt></dl>
 */
  INLINE friend ExportedByYN000FUN CATMathInterval operator /
    (const CATMathInterval & i, const double & iScalar);
      

 private:
  double min, max;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE CATMathInterval::CATMathInterval ()
{
    min = 0.;
    max = 0.; 
}

//----------------------------------------------------------------------
INLINE CATMathInterval::CATMathInterval (const double & iLow, const double & iHigh)
{
    min = iLow;
    max = iHigh;
} 
 
//----------------------------------------------------------------------
INLINE CATMathInterval::CATMathInterval (const CATMathInterval & iToCopy)
{
    min = iToCopy.min;
    max = iToCopy.max; 
}

//----------------------------------------------------------------------
INLINE CATLONG32 CATMathInterval::IsEmpty() const
{
    if (min > max) 
       return 1; 
    return 0; 
}

//----------------------------------------------------------------------
#ifdef CATIACGMV5R21
INLINE double CATMathInterval::Norm() const
{
   if (min >= 0.)   return max;
   if (max <= 0.)   return -min;
   if (max >= -min) return max;
   return -min;
}

//----------------------------------------------------------------------
INLINE double CATMathInterval::DistanceTo(const double & iPoint) const
{
   if (iPoint >= min)
   {
      if (iPoint <= max) return 0.;
      else               return iPoint - max;
   }
   else
      return min - iPoint;
}
#endif

//----------------------------------------------------------------------
INLINE double CATMathInterval::Center() const
{
   return (min + max)*.5; 
}

//----------------------------------------------------------------------
INLINE double CATMathInterval::Width()  const
{
   return (max - min);
   //if (min <= max) return (max - min);
   //return 0.;
}

//----------------------------------------------------------------------
INLINE double CATMathInterval::GetMin() const
{
   return min; 
}

//----------------------------------------------------------------------
INLINE double CATMathInterval::GetMax() const
{
   return max; 
}

//----------------------------------------------------------------------
INLINE void CATMathInterval::SetMin(const double & d)
{
   min = d; 
}

//----------------------------------------------------------------------
INLINE void CATMathInterval::SetMax(const double & d)
{
   max = d; 
}

//----------------------------------------------------------------------
INLINE   CATMathInterval operator &&
    (const CATMathInterval & i1, const CATMathInterval & i2)
{
   #ifdef CATMATHINTERVAL_DetectInvalid
   // Cas particulier des intervalles vides. NLD180516
   if (   (i1.min > i1.max)
       || (i2.min > i2.max)
      )
      #ifdef CATMATHINTERVAL_FixIfInvalid_TestOnlyNLD180516
      if (i1.min > i1.max)
         return i1; // i1 vide, on rend i1
      else
         return i2; // i2 vide, on rend i2
      #endif
      #ifdef CATMATHINTERVAL_ThrowIfInvalid_TestOnlyNLD180516
      CATThrowForNullPointerReturnValue(CATMathInterval());
      #endif
   #endif

   double x0, x1;
   if (i1.min > i2.min)
      x0 = i1.min;
   else
      x0 = i2.min;
   if (i1.max > i2.max)
      x1 = i2.max;
   else
      x1 = i1.max;
   return CATMathInterval(x0, x1); 
}

//----------------------------------------------------------------------
INLINE    CATMathInterval operator ||
    (const CATMathInterval & i1, const CATMathInterval & i2)
{
   #ifdef CATMATHINTERVAL_DetectInvalid
   // Cas particulier des intervalles vides. NLD180516
   if (   (i1.min > i1.max)
       || (i2.min > i2.max)
      )
      #ifdef CATMATHINTERVAL_FixIfInvalid_TestOnlyNLD180516
      if (i1.min > i1.max)
         return i2; // i1 vide, on rend i2
      else
         return i1; // i2 vide, on rend i1
      #endif
      #ifdef CATMATHINTERVAL_ThrowIfInvalid_TestOnlyNLD180516
      CATThrowForNullPointerReturnValue(CATMathInterval());
      #endif
   #endif

   double x0, x1;
   if (i1.min > i2.min)
      x0 = i2.min;
   else
      x0 = i1.min;
   if (i1.max > i2.max)
      x1 = i1.max;
   else
      x1 = i2.max;
   return CATMathInterval(x0, x1); 
}

//----------------------------------------------------------------------
INLINE   CATMathInterval operator +
    (const CATMathInterval & i1, const CATMathInterval & i2)
{
   return CATMathInterval(i1.min + i2.min, i1.max + i2.max); 
}

//----------------------------------------------------------------------
INLINE   void operator +=
    (CATMathInterval & i1, const CATMathInterval & i2)
{
   i1.min += i2.min;
   i1.max += i2.max; 
}

//----------------------------------------------------------------------
//  Substraction
//----------------------------------------------------------------------
INLINE  CATMathInterval operator -
    (const CATMathInterval & i1, const CATMathInterval & i2)
{
   return CATMathInterval(i1.min - i2.max, i1.max - i2.min); 
}

//----------------------------------------------------------------------
INLINE   void operator -=
    (CATMathInterval & i1, const CATMathInterval & i2)
{
   i1.min -= i2.max;
   i1.max -= i2.min; 
}

//----------------------------------------------------------------------
//  Multiplication
//----------------------------------------------------------------------
INLINE   void operator *=
    (CATMathInterval & i1, const double alpha)
{
   if (alpha > 0.) 
   {
      i1.min *= alpha;
      i1.max *= alpha; 
   }
   else
   {
      double d = i1.min;
      i1.min = alpha * i1.max;
      i1.max = alpha * d; 
   }
}


//----------------------------------------------------------------------
inline  CATMathInterval operator *
    (const CATMathInterval & i1, const CATMathInterval & i2)
{
   if (i1.min >= 0)
   {  
      if (i2.min >= 0) return CATMathInterval(i1.min*i2.min, i1.max*i2.max);
      if (i2.max <= 0) return CATMathInterval(i1.max*i2.min, i1.min*i2.max);
      return                  CATMathInterval(i1.max*i2.min, i1.max*i2.max); 
   }
   if (i1.max<=0)
   {
      if (i2.min >= 0) return CATMathInterval(i1.min*i2.max, i1.max*i2.min);
      if (i2.max <= 0) return CATMathInterval(i1.max*i2.max, i1.min*i2.min);
      return                  CATMathInterval(i1.min*i2.max, i1.min*i2.min);
   }
  if (i2.min >= 0)     return CATMathInterval(i1.min*i2.max, i1.max*i2.max);
  if (i2.max <= 0)     return CATMathInterval(i1.max*i2.min, i1.min*i2.min);
  double m = i1.min*i2.max;
  double M = i1.min*i2.min;
  double d = i1.max*i2.min;
  if (d < m)
     m = d;
  d = i1.max*i2.max;
  if (d > M)
     M = d;
  return CATMathInterval (m,M); 
}

//----------------------------------------------------------------------
//  Division
INLINE  CATMathInterval operator /
    (const CATMathInterval & i1, const CATMathInterval & i2)
{ 
   CATMathInterval Result;
   if ( i2.min * i2.max <= 0.) 
      Result = CATMathInterval( -CATMathInfinite, CATMathInfinite);
   else
      Result = (i1 * CATMathInterval(1/i2.max, 1/i2.min)); 
   // pour hp1020ansi 1 seul return dans fonction inline
   return Result;
}

//----------------------------------------------------------------------
//  Opposite
//----------------------------------------------------------------------
INLINE  CATMathInterval operator -
    (const CATMathInterval & i)
{
   return CATMathInterval ( - i.max,  - i.min); 
}

//----------------------------------------------------------------------
//  Scalar Addition
//----------------------------------------------------------------------
INLINE   CATMathInterval operator +
    (const double & d, const CATMathInterval & i)
{
   return CATMathInterval( d + i.min, d + i.max ); 
}

//----------------------------------------------------------------------
INLINE CATMathInterval operator +
    (const CATMathInterval & i, const double & d)
{
   return CATMathInterval( d + i.min, d + i.max ); 
}

//----------------------------------------------------------------------
INLINE  void operator +=
    (CATMathInterval & i, const double & d)
{
   i.min += d;
   i.max += d; 
}

//----------------------------------------------------------------------
//  Scalar Substraction
//----------------------------------------------------------------------
INLINE CATMathInterval operator -
    (const double & d, const CATMathInterval & i)
{
   return CATMathInterval( d - i.max, d - i.min ); 
}

//----------------------------------------------------------------------
INLINE CATMathInterval operator -
    (const CATMathInterval & i, const double & d)
{
   return CATMathInterval( i.min-d, i.max-d ); 
}

//----------------------------------------------------------------------
INLINE void operator -=
    (CATMathInterval & i, const double & d)
{
   i.min -= d;
   i.max -= d; 
}

//----------------------------------------------------------------------
//  Scalar Multiplication
//----------------------------------------------------------------------
INLINE   CATMathInterval operator *
    (const double & d, const CATMathInterval & i)
{
   if (d > 0.)
      return CATMathInterval( d*i.min, d*i.max );
   else
      return CATMathInterval( d*i.max, d*i.min ); 
}

//----------------------------------------------------------------------
INLINE CATMathInterval operator *
    (const CATMathInterval & i, const double & d)
{
   if (d > 0.)
      return CATMathInterval( d*i.min, d*i.max );
   else
      return CATMathInterval( d*i.max, d*i.min ); 
}

//----------------------------------------------------------------------
//  Scalar Division
//----------------------------------------------------------------------

INLINE CATMathInterval operator /
    (const CATMathInterval & i, const double & d)
{
   if (d > 0.)
      return CATMathInterval( i.min/d, i.max/d );
   else
      return CATMathInterval( i.max/d, i.min/d ); 
}

#endif
