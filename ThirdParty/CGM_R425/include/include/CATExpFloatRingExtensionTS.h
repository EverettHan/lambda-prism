//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes: 
//    In order to use CATExpBigIntegerTS, you must provide a sufficiently large array
//    to the CATExpPoolAllocator of single_uint_t:
//
//        #include "CATExpBigIntegerTS.h"
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
//============================================================================================================== 
// 03/06/2019 : RNO : NOEXCEPT
// 15/06/2015 - RNO - Version Thread-Safe mais moins rapide en monothread
// 04-Oct-2012 - DGA/T6L - Use of Big Integer
// 26-Jan-2011 - DNR - Suppression du champ prive _MyExactPredicates.
// 15-Jul-2010 - ALA - Creation.
//==============================================================================================================

#ifndef CATExpFloatRingExtensionTS_H
#define CATExpFloatRingExtensionTS_H
#include "CATIAV5Level.h"
//#define DEBUG_RING

#ifdef DEBUG_RING
  #define DEBUG_BIG_INTEGER
#endif

#include "CATExpExactArithmetic.h"
//#include "CATExpNumericDeclarations.h"
#include "CATExpEnums.h"
#include "CATExpBigIntegerTS.h"
#include "CATExpNumbersOperators.h"

#include <algorithm>
#include <utility>
#include <cstddef>

#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif

class ExportedByCATExpExactArithmetic CATExpFloatRingExtensionTS
{
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtensionTS operator-
    (const CATExpFloatRingExtensionTS &r1, const CATExpFloatRingExtensionTS &r2);
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtensionTS operator+
    (const CATExpFloatRingExtensionTS &r1, const CATExpFloatRingExtensionTS &r2);
  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtensionTS operator*
    (const CATExpFloatRingExtensionTS &r1, const CATExpFloatRingExtensionTS &r2);

  friend inline CATExpFloatRingExtensionTS operator- (const CATExpFloatRingExtensionTS &r)
  { return CATExpFloatRingExtensionTS(- r._Mantisse, r._Exposant); }

  friend inline CATExpFloatRingExtensionTS operator- (CATExpFloatRingExtensionTS &&r)
  { return CATExpFloatRingExtensionTS(- std::move(r._Mantisse), r._Exposant); }

public :

  /**
   * Constructors / Destructor<br>
   */
  CATExpFloatRingExtensionTS() __EXPNOEXCEPT__ = default;
  ~CATExpFloatRingExtensionTS() = default;

  explicit CATExpFloatRingExtensionTS (double iValue);

  CATExpFloatRingExtensionTS(const CATExpFloatRingExtensionTS & iOther) = default;
  CATExpFloatRingExtensionTS &operator= (const CATExpFloatRingExtensionTS &iOther) = default;
  CATExpFloatRingExtensionTS(CATExpFloatRingExtensionTS &&iOther) __EXPNOEXCEPT__ = default;
  CATExpFloatRingExtensionTS &operator= (CATExpFloatRingExtensionTS &&iOther) __EXPNOEXCEPT__ = default;

  void swap(CATExpFloatRingExtensionTS &iOther) noexcept;
  
  CATExpFloatRingExtensionTS (CATExpBigIntegerTS && mantisse, int exposant) 
    : _Mantisse(std::move(mantisse)), _Exposant(exposant)
  { rightClean(); }
  
  //Ajout CTOR manisse par reference !! (RNO 19/06/2019)
  CATExpFloatRingExtensionTS (CATExpBigIntegerTS & mantisse, int exposant) 
    : _Mantisse(mantisse), _Exposant(exposant)
  { rightClean(); }

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

  CATExpFloatRingExtensionTS &operator += (const CATExpFloatRingExtensionTS &iOther)
  {
    *this = *this + iOther;
    return *this;
  }

  CATExpFloatRingExtensionTS &operator -= (const CATExpFloatRingExtensionTS &iOther)
  {
    *this = *this - iOther;
    return *this;
  }

  //const CATExpFloatRingExtensionTS operator * (const CATExpFloatRingExtensionTS &iOther) const
  //{ return CATExpFloatRingExtensionTS (_Mantisse * iOther._Mantisse, _Exposant + iOther._Exposant); }

  CATExpFloatRingExtensionTS &operator *= (const CATExpFloatRingExtensionTS &iOther)
  {
    *this = *this * iOther;
    return *this;
  }

  //
  /** Compares the object with another CATExpFloatRingExtensionTS.
  * 1 : > iOther
  * -1 : < iOther
  * 0 : == iOther */
  CATExpSign_t compare (const CATExpFloatRingExtensionTS &iOther) const ;

  /**
  * comparison operators
  */
  const bool operator == (const CATExpFloatRingExtensionTS &iOther) const { return ( compare (iOther) == 0); }
  const bool operator != (const CATExpFloatRingExtensionTS &iOther) const { return ( compare (iOther) != 0); }
  const bool operator < (const CATExpFloatRingExtensionTS &iOther) const { return (compare (iOther) < 0); }
  const bool operator > (const CATExpFloatRingExtensionTS &iOther) const { return (compare (iOther) > 0); }

  void Visu() const;

  // return a couple (value,exp) such that the number equals (value * 2**exp) 
  void ConvertToDouble(double &Value, int& Exponent ) const
  { _Mantisse.ConvertToDouble(Value,Exponent); Exponent += _Exposant; }
  
  //RNO J'implémente cette fonction dans le cpp car je n'arrive pas à linker sur linux
  double Estimate() const; //{ return ::ConvertToDouble(_Mantisse, _Exposant); }

  void EstimateForDebug() const __EXPNOEXCEPT__
  { 
#ifdef DEBUG_RING
    _EstimateValue = Estimate();
#endif
  }

  double LowerBound() const;
  double UpperBound() const;

  std::size_t size() { return _Mantisse.size(); }

  //get approximate Log in base 2
  double GetLog2() const __EXPNOEXCEPT__  { return _Exposant; }


//==============================================================================================================
// Private Part.
//==============================================================================================================

private :



  void rightClean();

  CATExpBigIntegerTS _Mantisse;
  int _Exposant = 666;
 
#ifdef DEBUG_RING
  mutable double _EstimateValue;
#endif
 
};

//
//inline CATExpFloatRingExtensionTS operator+ (CATExpFloatRingExtensionTS x1, const CATExpFloatRingExtensionTS &x2)
//{ 
//  x1 += x2;
//  return x1; // do not write "return x1 += x2;"
//}
//
//inline CATExpFloatRingExtensionTS operator- (CATExpFloatRingExtensionTS x1, const CATExpFloatRingExtensionTS &x2)
//{ 
//  x1 -= x2;
//  return x1;
//}
//
//inline CATExpFloatRingExtensionTS operator* (CATExpFloatRingExtensionTS x1, const CATExpFloatRingExtensionTS &x2)
//{
//  x1 *= x2;
//  return x1;
//}
//


//inline void FlipSign (CATExpFloatRingExtensionTS &a)
//{ a.FlipSign(); }

inline void Visu(const CATExpFloatRingExtensionTS &x)
{ x.Visu(); }

inline CATExpSign_t CompareNumbers(const CATExpFloatRingExtensionTS &iN1, const CATExpFloatRingExtensionTS &iN2)
{ return static_cast<CATExpSign_t>(iN1.compare(iN2)); }


inline void swap(CATExpFloatRingExtensionTS &a, CATExpFloatRingExtensionTS &b) noexcept { a.swap(b); }

#endif



