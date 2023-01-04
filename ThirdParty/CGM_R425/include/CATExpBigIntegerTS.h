//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2012-2018
//==============================================================================================================
// Usage notes: (This is a ThreadSafe copy of CATExpBigInteger using an unoptimsed standard allocator
//==============================================================================================================

//==============================================================================================================
// 03/06/2019 : RNO : NOEXCEPT
// 24/05/2018 : RNO : Suppression de l'utilisation d'un allocateur specifique (R420)
// 15/06/2015 - RNO - Version Thread-Safe mais moins rapide en monothread (Poor performance allocator)
// 2012-10-06 - DGA/T6L - Creation
//==============================================================================================================

#ifndef CATExpBigIntegerTS_H
#define CATExpBigIntegerTS_H
#include "CATIAV5Level.h"
#include "CATExpExactArithmetic.h"
#include "CATExpNumericDeclarations.h"
#include "CATExpNumbersOperators.h"

#include "CATExpPoolAllocatorForBigIntTS.h"



#include <algorithm>
#include <utility>
#include <vector>
#include <tuple>//#define DEBUG_BIGINT
//#ifdef DEBUG_BIGINT
//#endif


class CATExpFloatRingExtensionTS;

class CATExpBigIntegerTS;
ExportedByCATExpExactArithmetic CATExpBigIntegerTS operator+ (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
ExportedByCATExpExactArithmetic CATExpBigIntegerTS operator- (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);



/**
* This class manages arithmetic operations on big integers.
* The limitation of this implementation is the number of recordable integers blocks, which is INT_MAX.
* So the maximum representable number is 2**(32*INT_MAX). If int have 32 bits, this is 2**(32*(2**31-1)) i.e. about 10**20000000000.
* @pre You must define an object of type SmartAllocator before using this class, refering to a huge Array of single_uint_t you will have allocated, 
* which size is an upper bound on the total number of small integers you will need.
*/

#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif


class ExportedByCATExpExactArithmetic CATExpBigIntegerTS
{
public:
#if defined(CATIAR420) ||  defined(CATIAV5R29) 
  //RNO 24/05/2018 :  L'ALLOCATEUR STANDARD EST DEVENU BEAUCOUP PLUS RAPIDE (15 fois plus rapide) que l'allocateur adhoc ...
  typedef std::vector<single_uint_t> UIntVector;
#else
  typedef std::vector<single_uint_t, CATExpPoolAllocatorForBigIntTS<single_uint_t>> UIntVector;
#endif
  //typedef Concurrency::concurrent_vector<single_uint_t> UIntVector;
  //typedef  CATExpBigIntegerTSStorage UIntVector;
  friend CATExpBigIntegerTS::UIntVector OperationCascading 
    (single_uint_t operation (const single_uint_t, const single_uint_t, single_uint_t &),
    const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
  template <bool plus>
  friend CATExpBigIntegerTS Addition (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
  friend CATExpBigIntegerTS::UIntVector MultiplicationCascading(const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);  
  friend CATExpBigIntegerTS MakeLeftShift(const CATExpBigIntegerTS &big, std::size_t l);
  friend CATExpSign_t compareAbs (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);

  friend ExportedByCATExpExactArithmetic CATExpBigIntegerTS operator*
    (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
  friend ExportedByCATExpExactArithmetic CATExpBigIntegerTS operator- (const CATExpBigIntegerTS &big);
  friend inline CATExpBigIntegerTS operator- (CATExpBigIntegerTS &&big)
  {
    CATExpBigIntegerTS result = std::move(big);
    result.sign_ = ! result.sign_;
    return result;
  }

  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtensionTS operator*
    (const CATExpFloatRingExtensionTS &r1, const CATExpFloatRingExtensionTS &r2);

  /**
   * Constructors / Destructor<br>
   */
  
  CATExpBigIntegerTS() __EXPNOEXCEPT__ = default;
  ~CATExpBigIntegerTS() = default;
  CATExpBigIntegerTS(const CATExpBigIntegerTS &iOther) = default;
  CATExpBigIntegerTS &operator= (const CATExpBigIntegerTS &iOther) = default;
  CATExpBigIntegerTS(CATExpBigIntegerTS &&iOther) __EXPNOEXCEPT__ = default;
  CATExpBigIntegerTS &operator= (CATExpBigIntegerTS &&iOther) __EXPNOEXCEPT__ = default;

  explicit CATExpBigIntegerTS (single_int_t iValue) ;
  CATExpBigIntegerTS (single_uint_t iValue, CATExpSign_t isign);
  CATExpBigIntegerTS (single_uint_t iValue1, single_uint_t iValue2, CATExpSign_t isign);

  void swap (CATExpBigIntegerTS &iOther) __EXPNOEXCEPT__;

  bool IsPositive() const __EXPNOEXCEPT__  { return (sign_ > 0); }
  bool IsNegative() const __EXPNOEXCEPT__ { return (sign_ < 0); }
  bool IsZero() const __EXPNOEXCEPT__  { return (sign_ == 0); }
  
  /*
  * @return -1,0,1 if  respectively negative, zero  or positive
  **/
  CATExpSign_t Sign() const __EXPNOEXCEPT__  { return sign_; }

  /**
  * Flips the object's sign.
  */
  void FlipSign() { sign_ = ! sign_; }

  /**
  * Division by 2**(32*l), i.e. right shift of l blocks; modifies the BigInteger in place,
  *   and the exponent of the corresponding FloatExtension as well.
  */
  void SelfRightBlockShift(int blockShifts, int &exponent);
  

  CATExpBigIntegerTS &operator += (const CATExpBigIntegerTS &iOther)
  {
    *this = *this + iOther;
    return *this;
  }

  CATExpBigIntegerTS &operator -= (const CATExpBigIntegerTS &iOther)
  {
    *this = *this - iOther;
    return *this;
  }

  CATExpBigIntegerTS &operator *= (const CATExpBigIntegerTS &iOther)
  {
    *this = *this * iOther;
    return *this;
  }

  /**
  * Returns how many zeros are on the right, -1 if the number is 0.
  * This can be used by FloatRing to discard them thanks to the exponent.
  */
  int NumberOfRightZeros();
  
  std::size_t size() __EXPNOEXCEPT__  { return array_.size(); }

  // return a couple (value,exp) such that the big integer equals (value * 2**exp). 
  std::pair<double, int> ConvertToDouble() const;
  void ConvertToDouble(double &oValue, int &oExponent) const;

  void Visu()  const;

//==============================================================================================================
// Private Part.
//==============================================================================================================

private :
  /**
  * Private constructor to optimize memory management, and avoid copy of data
  */
  CATExpBigIntegerTS (const UIntVector &tab, CATExpSign_t sign)
  : array_(tab), sign_(sign) {}
  
  CATExpBigIntegerTS (UIntVector &&tab, CATExpSign_t sign) __EXPNOEXCEPT__
  : array_(std::move(tab)), sign_(sign) {}
  
  //void DeepCopy (const CATExpBigIntegerTS &iOther);

  //void ShallowCopy (CATExpBigIntegerTS &&iOther)
  //{
  //  array_ = std::move(iOther.array_);
  //  sign_ = iOther.sign_;
  //}

  /**
  * @return a pointer to the array.
  */
  //const single_uint_t *ReadArray() const { return array_.data(); }
  //single_uint_t *WriteArray() { return array_.data(); }
  //void reserve( size_type new_cap ) { array_.reserve(new_cap); }
  //void resize(std::size_t new_size) { array_.resize(new_size); }
  //std::size_t size() const { return array_.size(); }

	// fields :
  UIntVector array_;
  CATExpSign_t sign_ = CATExpSIGNUNDEF;
};


//{ 
//  x1 += x2;
//  return x1; // do not write "return x1 += x2;"
//}
//
//inline CATExpBigIntegerTS operator- (CATExpBigIntegerTS x1, const CATExpBigIntegerTS &x2)
//{ 
//  x1 -= x2;
//  return x1;
//}
//
//inline CATExpBigIntegerTS operator* (CATExpBigIntegerTS x1, const CATExpBigIntegerTS &x2)
//{
//  x1 *= x2;
//  return x1;
//}
//

inline void CATExpBigIntegerTS::ConvertToDouble(double& oValue, int& oExponent) const
{
  std::tie(oValue, oExponent) = ConvertToDouble();
}


//const CATExpBigIntegerTS operator + (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
//const CATExpBigIntegerTS operator - (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
//const CATExpBigIntegerTS operator - (const CATExpBigIntegerTS &big);
//
//const CATExpBigIntegerTS operator * (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);

inline void swap (CATExpBigIntegerTS &big1, CATExpBigIntegerTS &big2) __EXPNOEXCEPT__
{ big1.swap(big2); }

/**
* Compares 2 BigIntegers.
* 1 : big1 > big2
* -1 : big1 < big2
* 0 : big1 == big2
*/
CATExpSign_t compare(const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);

/**
* Compares the absolute values of 2 BigIntegers.
* 1 : |big1| > |big2|
* -1 : |big1| < |big2|
* 0 : |big1| == |big2|
*/
CATExpSign_t compareAbs (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2);
/**
* comparison operators
*/
inline bool operator == (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2) { return ( compare (big1, big2) == 0); }
inline bool operator != (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2) { return ( compare (big1, big2) != 0); }
inline bool operator < (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2) { return (compare (big1, big2) < 0); }
inline bool operator > (const CATExpBigIntegerTS &big1, const CATExpBigIntegerTS &big2) { return (compare (big1, big2) > 0); }

// convert to double the big integer multiplied by 2 ** Exponent. 
double ConvertToDouble( const CATExpBigIntegerTS &big, int Exponent );
#endif



