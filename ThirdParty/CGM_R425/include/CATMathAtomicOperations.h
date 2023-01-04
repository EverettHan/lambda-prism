// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMathAtomicOperations
//
//===================================================================
// 2010-10-11   JXO
//      * New
// 2015-02-01   https://www.youtube.com/watch?v=dQw4w9WgXcQ
//===================================================================
#ifndef CATMathAtomicOperations_H
#define CATMathAtomicOperations_H

// Mathematics
#include "CATMathInline.h"

// System
#include "CATMutex.h"
#include <string.h>
#include "CATDataType.h"
#include "DSYSysAtomic.h"

// ExportedBy
#include "CATMathematics.h"

/**
 * Implementation of Atomic operations.
 * General note: Use int for base type. Never cast another type to int.
 * If so, unpredictable result will happen, dragons might even come out of your nose.
 * Of course, once you use atomic operations for a variable, you have to use atomic
 * operations for ALL operations on this variable. Operations are garantied to be
 * atomic only if NOT mixed with other (non atomic) operations.
 */

class ExportedByCATMathematics CATMathAtomicOperations
{
public:
  /**
   * ++ on ioValue. Returns the resulting incremented value.
   */
  INLINE static int Increment(int * ioValue);
  /**
   * -- on ioValue. Returns the resulting decremented value.
   */
  INLINE static int Decrement(int * ioValue);
  /**
   * Compares destination to comparand and put swap into destination if equal.
   * Returns the initial value of destination.
   * Note: this can be used to retrieve a value atomically:
   * int value = CompareAndSwap(ptrtovalue, 0, 0);
   */
  INLINE static int CompareAndSwap(int * destination, int swap, int comparand);
  /**
   * Performs a bitwise or between destination and value. Result is put into destination.
   * Returns the original value of the destination parameter.
   */
  INLINE static int BitWiseOr(int * destination, int value);
  /**
   * Performs a bitwise test and reset between destination and value. Result is put into destination.
   * Returns the original value of the destination parameter.
   * Note: this does not have the same meaning as the WINDOWS InterlockedBitTestAndReset.
   */
  INLINE static int BitWiseTestAndReset(int * destination, int value);

};


INLINE int CATMathAtomicOperations::Increment(int * ioValue)
{
  return DSYSysInterlockedIncrement(ioValue);
}

INLINE int CATMathAtomicOperations::Decrement(int * ioValue)
{
  return DSYSysInterlockedDecrement(ioValue);
}

INLINE int CATMathAtomicOperations::CompareAndSwap(int * destination, int swap, int comparand)
{
  return DSYSysInterlockedCompareExchangeInt32(destination, swap, comparand);
}

INLINE int CATMathAtomicOperations::BitWiseOr(int * destination, int value)
{
  int init = 0;
  int result = 0;
  do
  {
    init = DSYSysInterlockedCompareExchangeInt32(destination, 0, 0);
    result = init | value;
  }
  while (init != DSYSysInterlockedCompareExchangeInt32(destination, result, init));
  return init;
}

INLINE int CATMathAtomicOperations::BitWiseTestAndReset(int * destination, int value)
{
  int init = 0;
  int result = 0;
  do
  {
    init = DSYSysInterlockedCompareExchangeInt32(destination, 0, 0);
    result = (init | value) ^ value;
  }
  while (init != DSYSysInterlockedCompareExchangeInt32(destination, result, init));
  return init;
}

#endif
