//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2012
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

//
//    The CATExpPoolAllocator aims at speeding up dynamic allocations by avoiding calls to C++'s "new".
//==============================================================================================================
// 2015-10-XX - RNO/TYF : PLEASE USE NOW THE THREADSAFEVERSION (TS)
// 2012-10-06 - DGA/T6L - Creation
//==============================================================================================================
#ifdef for_coverage
#ifndef CATExpBigInteger_H
#define CATExpBigInteger_H

#include "CATExpExactArithmetic.h"
#include "CATExpNumericDeclarations.h"
#include "CATExpNumbersOperators.h"
#include "CATExpPoolAllocator.h"

#include <algorithm>
#include <utility>
#include <vector>

//#define DEBUG_BIGINT
//#ifdef DEBUG_BIGINT
//#endif

#ifndef __CATExpExactArithmetic
template class ExportedByCATExpExactArithmetic CATExpPoolAllocator<single_uint_t>;
#endif

class CATExpBigInteger;
ExportedByCATExpExactArithmetic CATExpBigInteger operator+ (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
ExportedByCATExpExactArithmetic CATExpBigInteger operator- (const CATExpBigInteger &big1, const CATExpBigInteger &big2);



/**
* This class manages arithmetic operations on big integers.
* The limitation of this implementation is the number of recordable integers blocks, which is INT_MAX.
* So the maximum representable number is 2**(32*INT_MAX). If int have 32 bits, this is 2**(32*(2**31-1)) i.e. about 10**20000000000.
* @pre You must define an object of type SmartAllocator before using this class, refering to a huge Array of single_uint_t you will have allocated, 
* which size is an upper bound on the total number of small integers you will need.
*/
class ExportedByCATExpExactArithmetic CATExpBigInteger
{
public:
  typedef std::vector<single_uint_t, CATExpScopedAllocator<single_uint_t> > UIntVector;

  friend CATExpBigInteger::UIntVector OperationCascading 
    (single_uint_t operation (const single_uint_t, const single_uint_t, single_uint_t &),
    const CATExpBigInteger &big1, const CATExpBigInteger &big2);
  template <bool plus>
  friend CATExpBigInteger Addition (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
  friend CATExpBigInteger::UIntVector MultiplicationCascading(const CATExpBigInteger &big1, const CATExpBigInteger &big2);  
  friend CATExpBigInteger MakeLeftShift(const CATExpBigInteger &big, std::size_t l);
  friend CATExpSign_t compareAbs (const CATExpBigInteger &big1, const CATExpBigInteger &big2);

  friend ExportedByCATExpExactArithmetic CATExpBigInteger operator*
    (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
  friend ExportedByCATExpExactArithmetic CATExpBigInteger operator- (const CATExpBigInteger &big);
  friend inline CATExpBigInteger operator- (CATExpBigInteger &&big)
  {
    CATExpBigInteger result = std::move(big);
    result.sign_ = ! result.sign_;
    return result;
  }

  friend ExportedByCATExpExactArithmetic CATExpFloatRingExtension operator*
    (const CATExpFloatRingExtension &r1, const CATExpFloatRingExtension &r2);

  /**
   * Constructors / Destructor<br>
   */
  
  CATExpBigInteger() = default;
  ~CATExpBigInteger() = default;
  CATExpBigInteger(const CATExpBigInteger &iOther) = default;
  CATExpBigInteger &operator= (CATExpBigInteger const &iOther) = default;
  CATExpBigInteger(CATExpBigInteger &&iOther) noexcept = default;
  CATExpBigInteger &operator= (CATExpBigInteger &&iOther) noexcept = default;

  explicit CATExpBigInteger (single_int_t iValue);
  CATExpBigInteger (single_uint_t iValue, CATExpSign_t isign);
  CATExpBigInteger (single_uint_t iValue1, single_uint_t iValue2, CATExpSign_t isign);

  void swap (CATExpBigInteger &iOther) noexcept;

  bool IsPositive() const { return (sign_ > 0); }
  bool IsNegative() const { return (sign_ < 0); }
  bool IsZero() const { return (sign_ == 0); }
  
  /*
  * @return -1,0,1 if  respectively negative, zero  or positive
  **/
  CATExpSign_t Sign() const { return sign_; }

  /**
  * Flips the object's sign.
  */
  void FlipSign() { sign_ = ! sign_; }

  /**
  * Division by 2**(32*l), i.e. right shift of l blocks; modifies the BigInteger in place,
  *   and the exponent of the corresponding FloatExtension as well.
  */
  void SelfRightBlockShift(int blockShifts, int &exponent);
  

  CATExpBigInteger &operator += (const CATExpBigInteger &iOther)
  {
    *this = *this + iOther;
    return *this;
  }

  CATExpBigInteger &operator -= (const CATExpBigInteger &iOther)
  {
    *this = *this - iOther;
    return *this;
  }

  CATExpBigInteger &operator *= (const CATExpBigInteger &iOther)
  {
    *this = *this * iOther;
    return *this;
  }

  /**
  * Returns how many zeros are on the right, -1 if the number is 0.
  * This can be used by FloatRing to discard them thanks to the exponent.
  */
  int NumberOfRightZeros();
  
  std::size_t size() { return array_.size(); }

  // return a couple (value,exp) such that the big integer equals (value * 2**exp). 
  void ConvertToDouble( double &Value, int& Exponent ) const;

  void Visu()  const;

//==============================================================================================================
// Private Part.
//==============================================================================================================

private :
  /**
  * Private constructor to optimize memory management, and avoid copy of data
  */
  CATExpBigInteger (const UIntVector &tab, CATExpSign_t sign)
  : array_(tab), sign_(sign) {}
  
  CATExpBigInteger (UIntVector &&tab, CATExpSign_t sign)
  : array_(std::move(tab)), sign_(sign) {}
  
  //void DeepCopy (const CATExpBigInteger &iOther);

  //void ShallowCopy (CATExpBigInteger &&iOther)
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
//inline CATExpBigInteger operator- (CATExpBigInteger x1, const CATExpBigInteger &x2)
//{ 
//  x1 -= x2;
//  return x1;
//}
//
//inline CATExpBigInteger operator* (CATExpBigInteger x1, const CATExpBigInteger &x2)
//{
//  x1 *= x2;
//  return x1;
//}
//


//const CATExpBigInteger operator + (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
//const CATExpBigInteger operator - (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
//const CATExpBigInteger operator - (const CATExpBigInteger &big);
//
//const CATExpBigInteger operator * (const CATExpBigInteger &big1, const CATExpBigInteger &big2);

inline void swap (CATExpBigInteger &big1, CATExpBigInteger &big2) noexcept
{ big1.swap(big2); }

/**
* Compares 2 BigIntegers.
* 1 : big1 > big2
* -1 : big1 < big2
* 0 : big1 == big2
*/
CATExpSign_t compare(const CATExpBigInteger &big1, const CATExpBigInteger &big2);

/**
* Compares the absolute values of 2 BigIntegers.
* 1 : |big1| > |big2|
* -1 : |big1| < |big2|
* 0 : |big1| == |big2|
*/
CATExpSign_t compareAbs (const CATExpBigInteger &big1, const CATExpBigInteger &big2);
/**
* comparison operators
*/
inline bool operator == (const CATExpBigInteger &big1, const CATExpBigInteger &big2) { return ( compare (big1, big2) == 0); }
inline bool operator != (const CATExpBigInteger &big1, const CATExpBigInteger &big2) { return ( compare (big1, big2) != 0); }
inline bool operator < (const CATExpBigInteger &big1, const CATExpBigInteger &big2) { return (compare (big1, big2) < 0); }
inline bool operator > (const CATExpBigInteger &big1, const CATExpBigInteger &big2) { return (compare (big1, big2) > 0); }

// convert to double the big integer multiplied by 2 ** Exponent. 
double ConvertToDouble( const CATExpBigInteger &big, int Exponent );


#endif
#endif


