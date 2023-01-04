// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// StackThenHeapAllocator
//
// StackThenHeapAllocator have a default allocation on stack
// If the number of element exceed the allocation on stack, allocation
// on heap is performed and the elements are moved to the new mem allocation
// Same goes for shriking but in reversed
//
// Compatible with the std containers
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#include <memory>
#include "MemoryOps.h"

namespace Poly
{
  template<typename T, unsigned int NumStackElement, typename SecondaryAllocator=std::allocator<T> >
  class StackThenHeapAllocator
  {
  private:
    SecondaryAllocator _heapAllocator;
    using AlignedStackArray = alignas(alignof(T)) unsigned char data[sizeof(T)]; 
    AlignedStackArray _data[NumStackElement]; // Stack memory allocation with correct alignment requirement without any call on T constructor
    bool _stackUsed; // only possible for one storage allocation.

  public:
    // Rebind to have the allocator for another element type
    template<class U> struct rebind{
      typedef StackThenHeapAllocator<U> other;
    };

  public:
    StackThenHeapAllocator()
    {
      _stackUsed = false;
    };

    template<typename U, unsigned int UN, typename USecAllo>
    StackThenHeapAllocator(const StackThenHeapAllocator<U, UN, USecAlloc) = delete; // not allowed since can be based on stack

    // Allocation
    T* allocate(std::size_t n) {
      if(_stackUsed || n>=NumStackElement)
        return _heapAllocator.allocate(n);
      else
      {
        _stackUsed = true;
        return _data;
      }
    }

    // Desallocation
    void deallocate(T* p, std::size_t n) noexcept {
      if(_stackUsed && p==&_data)
        _stackUsed = false;
      else
        _heapAllocator.desallocate(p,n);
    }

  };
};
