//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2010
//==============================================================================================================
//==============================================================================================================
// 2015-10-XX - RNO/TYF : PLEASE USE NOW THE THREADSAFEVERSION (TS)
// 23-Oct-2012 - DGA/T6L - Replace CATCloudExactPredicate (Shewchuk) by Big Integer
// 15-Jul-2010 - ALA - Creation.
#ifdef for_coverage
#ifndef CATExpFloatFieldExtension_H
#define CATExpFloatFieldExtension_H


#include "CATExpExactArithmetic.h"
#include "CATExpFloatRingExtension.h"




class ExportedByCATExpExactArithmetic CATExpFloatFieldExtension
{
  friend ExportedByCATExpExactArithmetic CATExpFloatFieldExtension operator+
    (const CATExpFloatFieldExtension &f1, const CATExpFloatFieldExtension &f2); 
  friend ExportedByCATExpExactArithmetic CATExpFloatFieldExtension operator-
    (const CATExpFloatFieldExtension &f1, const CATExpFloatFieldExtension &f2);

  friend inline CATExpFloatFieldExtension operator- (const CATExpFloatFieldExtension &f)
  {
    if (f.IsZero()) return CATExpFloatFieldExtension(0.);
    else return CATExpFloatFieldExtension(f._Numerator, f._Denominator, - f._Isign);
  }

  friend inline CATExpFloatFieldExtension operator- (CATExpFloatFieldExtension &&f)
  {
    if (f.IsZero()) return CATExpFloatFieldExtension(0.);
    else return CATExpFloatFieldExtension(std::move(f._Numerator), std::move(f._Denominator), - f._Isign);
  }

  friend inline CATExpFloatFieldExtension operator*
    (const CATExpFloatFieldExtension &f1, const CATExpFloatFieldExtension &f2)
  {
    if (f1.IsZero() || f2.IsZero()) return CATExpFloatFieldExtension(0.);
    else return CATExpFloatFieldExtension
      (f1._Numerator * f2._Numerator, f1._Denominator * f2._Denominator, f1._Isign * f2._Isign);
  }

  friend inline CATExpFloatFieldExtension operator/
    (const CATExpFloatFieldExtension &f1, const CATExpFloatFieldExtension &f2)
  {
    if (f1.IsZero()) return CATExpFloatFieldExtension(0.);
    else return CATExpFloatFieldExtension
      (f1._Numerator * f2._Denominator, f1._Denominator * f2._Numerator, f1._Isign * f2._Isign);
  }


public :

  /**
   * Constructors / Destructor<br>
   */
  CATExpFloatFieldExtension() = default;
  CATExpFloatFieldExtension(const CATExpFloatFieldExtension & iOther) = default;
  CATExpFloatFieldExtension& operator= (const CATExpFloatFieldExtension &iOther) = default;
  CATExpFloatFieldExtension(CATExpFloatFieldExtension &&iOther) noexcept = default;
  CATExpFloatFieldExtension& operator= (CATExpFloatFieldExtension &&iOther) noexcept = default;

  CATExpFloatFieldExtension (double iValue) 
  : _Numerator(iValue >= 0 ? iValue : -iValue), _Denominator(1.), _Isign(iValue >= 0 ? 1 : -1)
  { if (iValue == 0) _Isign = 0; }

  void swap(CATExpFloatFieldExtension &iOther) noexcept
  {
    std::swap(iOther, *this);
  }

  bool IsZero() const { return (_Isign == 0); }
  bool IsPositive() const { return (_Isign > 0); }
  bool IsNegative() const { return (_Isign < 0); }
  /*
  * return -1,0,1 if  respectively negative, zero   or positive
  **/
  int Sign() const { return _Isign; }

  /**
  * Flips the object's sign.
  */
  void FlipSign() { _Isign = - _Isign; }


  /** Compares the object with another CATCldFloatRingExtension2.
  * 1 : > iOther
  * -1 : < iOther
  * 0 : == iOther */
  const int compare (const CATExpFloatFieldExtension &iOther) const;

  /**
  * comparison operators
  */
  const bool operator == (const CATExpFloatFieldExtension &iOther) const { return ( compare (iOther) == 0); }
  const bool operator != (const CATExpFloatFieldExtension &iOther) const { return ( compare (iOther) != 0); }
  const bool operator < (const CATExpFloatFieldExtension &iOther) const { return (compare (iOther) < 0); }
  const bool operator > (const CATExpFloatFieldExtension &iOther) const { return (compare (iOther) > 0); }

  // convert to double
  operator double() const; // { return _Isign * double(_Numerator) / double(_Denominator); }

 void ShiftExponents(int iShift);

 int GetMaxExponent() const;

 // we enforce that _Numerator and _Denominator be nonnegative
 void Normalize();

 // void Approximate() {	_Numerator.Approximate(); _Denominator.Approximate(); }


//==============================================================================================================
// Private Part.
//==============================================================================================================

private :

  CATExpFloatFieldExtension
    (const CATExpFloatRingExtension &Numerator, const CATExpFloatRingExtension &Denominator, int isign)
  : _Numerator(Numerator), _Denominator(Denominator), _Isign(isign)
  { Normalize(); }

  CATExpFloatFieldExtension (CATExpFloatRingExtension &&Numerator, CATExpFloatRingExtension &&Denominator, int isign)
  : _Numerator(std::move(Numerator)), _Denominator(std::move(Denominator)), _Isign(isign)
  { Normalize(); }

  friend double ToDouble(const CATExpFloatFieldExtension &iV1)
  { return ToDouble(iV1._Numerator) / ToDouble(iV1._Denominator); }


	// fields :

  CATExpFloatRingExtension _Numerator;
  CATExpFloatRingExtension _Denominator;

  // we enforce that _Numerator and _Denominator be nonnegative
  int _Isign = 0;
};

inline void swap(CATExpFloatFieldExtension &a, CATExpFloatFieldExtension &b) noexcept { a.swap(b); }

#endif
#endif
