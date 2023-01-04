//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes: 
//    In order to use CATExpBigInteger, you must provide a sufficiently large array
//    to the CATExpPoolAllocator of single_uint_t:
//
//        #include "CATExpBigInteger.h"
//        #include "CATExpExactArithmetic.h"
//        #include "CATExpPoolAllocator.h"
//        template class ExportedByCATExpExactArithmetic CATExpAllocatorsTable<single_uint_t>;
//
//        static const unsigned kDefaultCapacity = (..);
//        static single_uint_t array[kDefaultCapacity];
//        CATExpPoolAllocator<single_uint_t> allocator(array, kDefaultCapacity);
//        /* -- your computations here -- */
//        allocator.Dismiss();
//==============================================================================================================
// 2015-10-XX - RNO/TYF : PLEASE USE NOW THE THREADSAFEVERSION (TS)
// 04-Oct-2012 - DGA/T6L - Use of Big Integer
// 26-Jan-2011 - DNR - Suppression du champ prive _MyExactPredicates.
// 15-Jul-2010 - ALA - Creation.
//==============================================================================================================
#ifdef for_coverage
#ifndef CATExpFloatRingExtension_H
#define CATExpFloatRingExtension_H

//#define DEBUG_RING

#ifdef DEBUG_RING
  #define DEBUG_BIG_INTEGER
#endif

#include "CATExpExactArithmetic.h"
//#include "CATExpNumericDeclarations.h"
#include "CATExpEnums.h"
#include "CATExpBigInteger.h"
#include "CATExpNumbersOperators.h"

#include <algorithm>
#include <utility>
#include <cstddef>

class ExportedByCATExpExactArithmetic CATExpFloatRingExtension
{
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtension operator-
    (const CATExpFloatRingExtension &r1, const CATExpFloatRingExtension &r2);
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtension operator+
    (const CATExpFloatRingExtension &r1, const CATExpFloatRingExtension &r2);
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtension operator*
    (const CATExpFloatRingExtension &r1, const CATExpFloatRingExtension &r2);

  friend inline CATExpFloatRingExtension operator- (const CATExpFloatRingExtension &r)
  { return CATExpFloatRingExtension(- r._Mantisse, r._Exposant); }

  friend inline CATExpFloatRingExtension operator- (CATExpFloatRingExtension &&r)
  { return CATExpFloatRingExtension(- std::move(r._Mantisse), r._Exposant); }

public :

  /**
   * Constructors / Destructor<br>
   */
  CATExpFloatRingExtension() = default;
  explicit CATExpFloatRingExtension (double iValue);
  CATExpFloatRingExtension(const CATExpFloatRingExtension & iOther) = default;
  CATExpFloatRingExtension &operator= (const CATExpFloatRingExtension &iOther) = default;
  CATExpFloatRingExtension(CATExpFloatRingExtension &&iOther) noexcept = default;
  CATExpFloatRingExtension &operator= (CATExpFloatRingExtension &&iOther) noexcept = default;

  void swap(CATExpFloatRingExtension &iOther) noexcept;

  bool IsPositive() const { return (_Mantisse.IsPositive()); }
  bool IsNegative() const { return (_Mantisse.IsNegative()); }
  bool IsZero() const { return _Mantisse.IsZero(); }

  /*
  * return -1,0,1 if  respectively negative, zero or positive
  **/
  CATExpSign_t Sign() const { return _Mantisse.Sign(); }

  /**
  * Flips the object's sign.
  */
  void FlipSign() { _Mantisse.FlipSign(); }

  CATExpFloatRingExtension &operator += (const CATExpFloatRingExtension &iOther)
  {
    *this = *this + iOther;
    return *this;
  }

  CATExpFloatRingExtension &operator -= (const CATExpFloatRingExtension &iOther)
  {
    *this = *this - iOther;
    return *this;
  }

  //const CATExpFloatRingExtension operator * (const CATExpFloatRingExtension &iOther) const
  //{ return CATExpFloatRingExtension (_Mantisse * iOther._Mantisse, _Exposant + iOther._Exposant); }

  CATExpFloatRingExtension &operator *= (const CATExpFloatRingExtension &iOther)
  {
    *this = *this * iOther;
    return *this;
  }

  //
  /** Compares the object with another CATExpFloatRingExtension.
  * 1 : > iOther
  * -1 : < iOther
  * 0 : == iOther */
  CATExpSign_t compare (const CATExpFloatRingExtension &iOther) const ;

  /**
  * comparison operators
  */
  const bool operator == (const CATExpFloatRingExtension &iOther) const { return ( compare (iOther) == 0); }
  const bool operator != (const CATExpFloatRingExtension &iOther) const { return ( compare (iOther) != 0); }
  const bool operator < (const CATExpFloatRingExtension &iOther) const { return (compare (iOther) < 0); }
  const bool operator > (const CATExpFloatRingExtension &iOther) const { return (compare (iOther) > 0); }

  void Visu() const;

  double Estimate() const { return ::ConvertToDouble(_Mantisse, _Exposant); }

  void EstimateForDebug() const
  { 
#ifdef DEBUG_RING
    _EstimateValue = Estimate();
#endif
  }

  double LowerBound() const;
  double UpperBound() const;

  // return a couple (value,exp) such that the number equals (value * 2**exp) 
  void ConvertToDouble(double &Value, int& Exponent ) const
  { _Mantisse.ConvertToDouble(Value,Exponent); Exponent += _Exposant; }

  std::size_t size() { return _Mantisse.size(); }

  //get approximate Log in base 2
  double GetLog2() const { return _Exposant; }

//==============================================================================================================
// Private Part.
//==============================================================================================================

private :

  CATExpFloatRingExtension (CATExpBigInteger &&mantisse, int exposant) 
    : _Mantisse(std::move(mantisse)), _Exposant(exposant)
  { rightClean(); }

  void rightClean();

  CATExpBigInteger _Mantisse;
  int _Exposant = 666;
 
#ifdef DEBUG_RING
  mutable double _EstimateValue;
#endif
 
};

//
//inline CATExpFloatRingExtension operator+ (CATExpFloatRingExtension x1, const CATExpFloatRingExtension &x2)
//{ 
//  x1 += x2;
//  return x1; // do not write "return x1 += x2;"
//}
//
//inline CATExpFloatRingExtension operator- (CATExpFloatRingExtension x1, const CATExpFloatRingExtension &x2)
//{ 
//  x1 -= x2;
//  return x1;
//}
//
//inline CATExpFloatRingExtension operator* (CATExpFloatRingExtension x1, const CATExpFloatRingExtension &x2)
//{
//  x1 *= x2;
//  return x1;
//}
//


//inline void FlipSign (CATExpFloatRingExtension &a)
//{ a.FlipSign(); }

inline void Visu(const CATExpFloatRingExtension &x)
{ x.Visu(); }

inline CATExpSign_t CompareNumbers(const CATExpFloatRingExtension &iN1, const CATExpFloatRingExtension &iN2)
{ return static_cast<CATExpSign_t>(iN1.compare(iN2)); }


inline void swap(CATExpFloatRingExtension &a, CATExpFloatRingExtension &b) noexcept { a.swap(b); }
#endif
#endif


