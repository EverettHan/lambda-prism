//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Bit set structure (based on buckets).
//
// Here is a snippet to demonstrate its usage:
//
// {
//   CATPolyBitSet s;
//
//   s.Set(2097, TRUE);
//   CATAssert(s.Test(2097));
//
//   CATAssert(!s.Test(0));
//
//   CATAssert(!s.Test(2097297));
//
//   s.Reset();
// }
//
//=============================================================================
// 2007-06-29   BPG: New.
//=============================================================================
#ifndef CATPolyBitSet_H
#define CATPolyBitSet_H

#include "CATPolyBuckets_T.h"

#include "PolyMathContainers.h"
class ExportedByPolyMathContainers CATPolyBitSet
{
  /** @name Life-cycle
      @{ */
public:
  /** Create an empty bitset. */
  CATPolyBitSet() {}
  /** Destroy the bitset. */
  ~CATPolyBitSet() {}
  /** @} */

  /** @name Bitfield access 
      @{ */
public:
  /** Clear every bit. */
  HRESULT Reset();

  /** Clear - quicker than Reset*/
  inline void Clear (CATBoolean iKeepAlloc = 0) {_UInt32Set.Clear (iKeepAlloc);}

  /** Set bit b if iValue is non zero, clear bit b otherwise.
      
      Observe that 0 is a valid value for b. Allocations may be necessary
      (e.g. when resizing internal arrays), so this method may fail due to
      memory exhaustion.
  */
  inline HRESULT Set(unsigned int b, CATBoolean iValue);

  /** Return TRUE if bit b is set.

      No element is added whatsoever. The method will just return FALSE if b
      was never set, especially if b is well beyond internal limits.
   */
  inline CATBoolean Test(unsigned int b) const;

  /** @} */


  // Internals
protected:
  class Specialize_CATPolyBuckets_T(CATPolyUInt32Buckets, unsigned int);

protected:
  CATPolyUInt32Buckets _UInt32Set;
};

// ----------------------------------------------------------------------------

// "/ 32" is translated by optimizing compilers to ">> 5", as it must be.
// "% 32" is translated by optimizing compilers to "& 0x1F", as it must be.

inline HRESULT
CATPolyBitSet::Set(unsigned int b, CATBoolean iValue)
{
  const unsigned int i = 1 + (b / 32);

  const unsigned int Mask = 0x1 << (b % 32);
  unsigned int j = _UInt32Set.Size();
  if (j < i)
  {
    for (++j; j < i; ++j)
      _UInt32Set.PushBack(0);
    return _UInt32Set.PushBack(iValue ? Mask : 0) ? S_OK : E_FAIL;
  }
  else
  {
    if (iValue)
      _UInt32Set[i] |= Mask;
    else
      _UInt32Set[i] &= ~Mask;
  }
  return S_OK;
}

inline CATBoolean
CATPolyBitSet::Test(unsigned int b) const
{
  const unsigned int i = 1 + (b / 32);
  return i <= _UInt32Set.Size() &&
    ((_UInt32Set[i] >> (b % 32)) & 0x1);
}

#endif // !CATPolyBitSet_H
