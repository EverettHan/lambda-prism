//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2010
//==============================================================================================================
//==============================================================================================================
// 15/06/2015 - RNO - Version Thread-Safe mais moins rapide en monothread
// 23-Oct-2012 - DGA/T6L - Replace CATCloudExactPredicate (Shewchuk) by Big Integer
// 15-Jul-2010 - ALA - Creation.

#ifndef CATExpFloatFieldExtensionTS_H
#define CATExpFloatFieldExtensionTS_H


#include "CATExpExactArithmetic.h"
#include "CATExpFloatRingExtensionTS.h"




class ExportedByCATExpExactArithmetic CATExpFloatFieldExtensionTS
{
  friend ExportedByCATExpExactArithmetic CATExpFloatFieldExtensionTS operator+
    (const CATExpFloatFieldExtensionTS &f1, const CATExpFloatFieldExtensionTS &f2); 
  friend ExportedByCATExpExactArithmetic CATExpFloatFieldExtensionTS operator-
    (const CATExpFloatFieldExtensionTS &f1, const CATExpFloatFieldExtensionTS &f2);

  friend inline CATExpFloatFieldExtensionTS operator- (const CATExpFloatFieldExtensionTS &f)
  {
    if (f.IsZero()) return CATExpFloatFieldExtensionTS(0.);
    else return CATExpFloatFieldExtensionTS(f._Numerator, f._Denominator, - f._Isign);
  }

  friend inline CATExpFloatFieldExtensionTS operator- (CATExpFloatFieldExtensionTS &&f)
  {
    if (f.IsZero()) return CATExpFloatFieldExtensionTS(0.);
    else return CATExpFloatFieldExtensionTS(std::move(f._Numerator), std::move(f._Denominator), - f._Isign);
  }

  friend inline CATExpFloatFieldExtensionTS operator*
    (const CATExpFloatFieldExtensionTS &f1, const CATExpFloatFieldExtensionTS &f2)
  {
    if (f1.IsZero() || f2.IsZero()) return CATExpFloatFieldExtensionTS(0.);
    else return CATExpFloatFieldExtensionTS
      (f1._Numerator * f2._Numerator, f1._Denominator * f2._Denominator, f1._Isign * f2._Isign);
  }

  friend inline CATExpFloatFieldExtensionTS operator/
    (const CATExpFloatFieldExtensionTS &f1, const CATExpFloatFieldExtensionTS &f2)
  {
    if (f1.IsZero()) return CATExpFloatFieldExtensionTS(0.);
    else return CATExpFloatFieldExtensionTS
      (f1._Numerator * f2._Denominator, f1._Denominator * f2._Numerator, f1._Isign * f2._Isign);
  }


public :

  /**
   * Constructors / Destructor<br>
   */
  CATExpFloatFieldExtensionTS() = default;
  ~CATExpFloatFieldExtensionTS() = default;
  CATExpFloatFieldExtensionTS(const CATExpFloatFieldExtensionTS & iOther) = default;
  CATExpFloatFieldExtensionTS& operator= (const CATExpFloatFieldExtensionTS &iOther) = default;
  CATExpFloatFieldExtensionTS(CATExpFloatFieldExtensionTS &&iOther) noexcept = default;
  CATExpFloatFieldExtensionTS& operator= (CATExpFloatFieldExtensionTS &&iOther) noexcept = default;

  CATExpFloatFieldExtensionTS (double iValue) 
  : _Numerator(iValue >= 0 ? iValue : -iValue), _Denominator(1.), _Isign(iValue == 0. ? 0 : (iValue >= 0 ? 1 : -1))
  { }

  void swap(CATExpFloatFieldExtensionTS &iOther) noexcept
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
  const int compare (const CATExpFloatFieldExtensionTS &iOther) const;

  /**
  * comparison operators
  */
  const bool operator == (const CATExpFloatFieldExtensionTS &iOther) const { return ( compare (iOther) == 0); }
  const bool operator != (const CATExpFloatFieldExtensionTS &iOther) const { return ( compare (iOther) != 0); }
  const bool operator < (const CATExpFloatFieldExtensionTS &iOther) const { return (compare (iOther) < 0); }
  const bool operator > (const CATExpFloatFieldExtensionTS &iOther) const { return (compare (iOther) > 0); }

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

  CATExpFloatFieldExtensionTS
    (const CATExpFloatRingExtensionTS &Numerator, const CATExpFloatRingExtensionTS &Denominator, int isign)
  : _Numerator(Numerator), _Denominator(Denominator), _Isign(isign)
  { Normalize(); }

  CATExpFloatFieldExtensionTS (CATExpFloatRingExtensionTS &&Numerator, CATExpFloatRingExtensionTS &&Denominator, int isign)
  : _Numerator(std::move(Numerator)), _Denominator(std::move(Denominator)), _Isign(isign)
  { Normalize(); }

  friend double ToDouble(const CATExpFloatFieldExtensionTS &iV1)
  { return ToDouble(iV1._Numerator) / ToDouble(iV1._Denominator); }


	// fields :

  CATExpFloatRingExtensionTS _Numerator;
  CATExpFloatRingExtensionTS _Denominator;

  // we enforce that _Numerator and _Denominator be nonnegative
  int _Isign = 0;
};

inline void swap(CATExpFloatFieldExtensionTS &a, CATExpFloatFieldExtensionTS &b) noexcept { a.swap(b); }

//Template Specialization // [7/12/2016 RNO] :  
template <> inline double ToDouble<CATExpFloatFieldExtensionTS>(const CATExpFloatFieldExtensionTS & FR)
{
  return static_cast<double>(FR);//CALL THE double() operator
}
// [7/12/2016 RNO] : SignOf 
template <> inline CATExpSign_t  SignOf(const CATExpFloatFieldExtensionTS &a)
{
  //enum CATExpSign_t { CATExpNEGATIVE = -1, CATExpZERO = 0, CATExpPOSITIVE = 1, CATExpSIGNUNDEF = -2 };
  return static_cast<CATExpSign_t>(a.Sign());//car meme convention ==-1<0;  ==0 Zero et ==1 >0
}

#endif

