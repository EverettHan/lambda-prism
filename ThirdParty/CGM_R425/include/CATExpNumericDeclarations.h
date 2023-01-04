#ifndef CATExpNumericDeclarations_H
#define CATExpNumericDeclarations_H  

#include "CATDataType.h"



// 2015-10-XX - RNO/TYF : THREADSAFEVERSION (TS)

//#include <stdint.h>
//typedef int32_t single_int_t;
//typedef uint32_t single_uint_t;
//typedef uint64_t double_uint_t;

/**
* Width of atomic blocks, i.e. 32-bit unsigned integers.
*/
const int singleIntWidth = 32;
typedef CATINT32 single_int_t;
typedef CATUINT32 single_uint_t;
typedef CATULONG64 double_uint_t;


/* ============================= Forward declarations ================================ */

//#include "CATExpDynamic.h"
//#include "CATExpInterval.h"
//#include "CATExpFloatRingExtensionTS.h"
// //class CATExpFloatRingExtensionTS;
class CATExpDynamic;
class CATExpInterval;
class CATExpFloatRingExtensionTS;
typedef CATExpDynamic CATExpDynamic_t;
typedef CATExpInterval CATExpInterval_t;
typedef CATExpFloatRingExtensionTS CATExpExact_t;

enum CATExpLevel_t { kCATExpDYNAMIC = 0, kCATExpINTERVAL = 1, kCATExpEXACT = 2, kCATExpLEVELS_NUMBER };

template <typename NT>
struct CATExpNumberInfo{};

template <> struct CATExpNumberInfo<CATExpDynamic>
{
  static const CATExpLevel_t level = kCATExpDYNAMIC;
};

template <> struct CATExpNumberInfo<CATExpInterval>
{
  static const CATExpLevel_t level = kCATExpINTERVAL;
};

template <> struct CATExpNumberInfo<CATExpFloatRingExtensionTS>
{
  static const CATExpLevel_t level = kCATExpEXACT;
};


class CATExpLazinessControl;


template <class NT> class CATExpTrinomial;
template <class NT> class CATExpQuadraticNumber;
template <class NT> class CATExpRationalNumber;

//template <class RequiringAllocator> class SmartAllocator;
//template <typename Object> Object *SmartlyAllocate(size_t nbObjects);
//template <typename Object> Object *NewCopy(Object object);


enum CATExpNumber_t { CATExpNUMBERUNDEF, CATExpPLAIN, CATExpRATIONAL, CATExpQUADRATIC };

#endif
