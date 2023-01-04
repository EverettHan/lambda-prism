//===================================================================
// COPYRIGHT Dassault Systemes 2010-2019
//===================================================================
//  June 2019  - RNO : Migration Linux
//  Sep 2013 - T6L : tabula rasa
//    (-a) * b != -(a * b) because of rounding 
//    correction of other bugs in * and /
//    sup_ is really the sup_ (and not its opposite) and it is complicated enough like that
//  May 2013 - T6L : Delivery in fw CATMathExactPredicate
//  Jan 2013 - T6L : return value optimization
//  Sep 2012 - DGA/ALA : Correction operateur /
//  Jul 2010 - DNR : Creation
//===================================================================

#ifndef CATExpInterval_H
#define CATExpInterval_H
#include "CATIAV5Level.h"
#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif

#include "CATExpIntervalArithmetic.h"
#include "CATExpEnums.h"
#include "CATExpNumbersOperators.h"

#include <algorithm>
#include <utility>

class ExportedByCATExpIntervalArithmetic CATExpInterval
{
  friend bool operator < (const CATExpInterval &x1, const CATExpInterval &x2)  __EXPNOEXCEPT__
  { return (x1.sup_ < x2.inf_ ? true : false); }

  friend bool operator > (const CATExpInterval &x1, const CATExpInterval &x2) __EXPNOEXCEPT__
  { return (x1.inf_ > x2.sup_ ? true : false); }

  friend bool do_overlap (const CATExpInterval &x1, const CATExpInterval &x2) __EXPNOEXCEPT__
  { return (x1.sup_ > x2.inf_ && x1.inf_ < x2.sup_); }

public :
  CATExpInterval () __EXPNOEXCEPT__  : inf_(666.), sup_(-666.) {}
  explicit CATExpInterval (double x) __EXPNOEXCEPT__  : inf_(x), sup_(x) {}
  explicit CATExpInterval (double mini, double maxi) __EXPNOEXCEPT__  : inf_(mini), sup_(maxi) {}
 
  bool IsPositive() const __EXPNOEXCEPT__ { return (inf_ > 0.); }
  bool IsNegative() const __EXPNOEXCEPT__ { return (sup_ < 0.); }
  bool IsZero() const __EXPNOEXCEPT__  { return (inf_ == 0.0 && sup_ == 0.0); }

  CATExpInterval &operator += (const CATExpInterval &y);
  CATExpInterval &operator -= (const CATExpInterval &y);
  CATExpInterval &operator *= (const CATExpInterval &y);
  CATExpInterval &operator /= (const CATExpInterval &y);

  CATExpInterval operator- () const
  { return CATExpInterval(-sup_, -inf_); }

  CATExpSign_t Sign() const
  {
    if (IsPositive()) return CATExpPOSITIVE;
    else if (IsNegative()) return CATExpNEGATIVE;
    else if (IsZero()) return CATExpZERO;
    else return CATExpSIGNUNDEF;
  }

  CATExpInterval Abs() const;

  double Estimate() const __EXPNOEXCEPT__ { return 0.5 * (inf_ + sup_); }
  double LowerBound() const __EXPNOEXCEPT__ { return inf_; }
  double UpperBound() const __EXPNOEXCEPT__  { return sup_; }
  
private :
  double inf_, sup_;  // lower and upper bounds
} ;

inline CATExpInterval operator+ (CATExpInterval x1, const CATExpInterval &x2)
{ 
  x1 += x2;
  return x1; // do not write "return x1 += x2;"
}

inline CATExpInterval operator- (CATExpInterval x1, const CATExpInterval &x2)
{ 
  x1 -= x2;
  return x1;
}

inline CATExpInterval operator* (CATExpInterval x1, const CATExpInterval &x2)
{
  x1 *= x2;
  return x1;
}

inline CATExpInterval operator/ (CATExpInterval x1, const CATExpInterval &x2)
{ 
  x1 /= x2;
  return x1;
}

inline CATExpInterval CATExpInterval::Abs() const
{
  if (inf_ > 0.)
    return *this;
  else if (sup_ < 0.)
    return -(*this);
  else
    return CATExpInterval(0., (std::max)(-inf_, -sup_));
}

#endif // CATExpInterval_H
