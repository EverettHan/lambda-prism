// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// AllocatorOneStorage
//
// Handle one mem storage at a given time, and avoid (when possible) constructor copy call to
// report the old content when a resize occurs. This improves the performances
// in sensible context.
// If the resize performance isn't an issue, use std conventionnal allocator
// Possible to control larger alignment too.
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX

// PolyhedralMathematics
#include "MemoryOps.h"
#include "LogicalTraits.h"

// std
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <cstring>


namespace Poly
{
  template <typename AllocatorType>
  struct AllocatorTraitsBase
  {
    enum { supportsMove    = false };
  };

  template <typename AllocatorType>
  struct AllocatorTraits : AllocatorTraitsBase<AllocatorType>
  {
  };
}

namespace Poly
{
  // Default heap allocator based on the system alignment
  class HeapAllocatorOneStorage
  {
  public:
    enum { NeedsElementsType = false };

    class ForAnyElementType
      {
    private:
      void* _pData;

    public:
      ForAnyElementType() : _pData(nullptr) {};
      ~ForAnyElementType()
      {
        if (_pData)
          free(_pData);
        _pData = nullptr;
      }

      inline void Move(ForAnyElementType & iToMove)
      {
        if (this != &iToMove)
        {
          if (_pData)
            free(_pData);

          _pData = iToMove._pData;
          iToMove._pData = nullptr;
        }
      };

      template<typename ElementType=void>
      inline ElementType* GetAllocation() const
      {
        return reinterpret_cast<ElementType*>(_pData);
      }

      template<typename ToElementType, typename FromElementType = ToElementType >
      inline void ResizeAllocation(size_t iPrevNumElements, size_t iNumElements)
      {
        if (_pData || iNumElements)
        {
          void* _pNewData = malloc(iNumElements * sizeof(ToElementType));
          if(_pData)
          {
            RelocateConstruct<ToElementType, FromElementType>(_pNewData, reinterpret_cast<FromElementType*>(_pData), iPrevNumElements); 
            free(_pData);
          }
          _pData = _pNewData;
        }
      }

      inline void ResizeAllocation(size_t iPrevNumElements, size_t iNumElements, size_t iNbBytesPerElement)
      {
        if(_pData || iNumElements)
        {
          void* _pNewData = iNumElements? malloc(iNumElements*iNbBytesPerElement) : nullptr;
          if(_pData)
          {
            std::memcpy(_pNewData, _pData, iPrevNumElements*iNbBytesPerElement);
            free(_pData);
          }
          _pData = _pNewData;
        }
      }

      inline std::size_t ComputeGrow(std::size_t iMinNumElements, std::size_t iNumAllocatedElements, std::size_t iNbBytesPerElement)
      {
        std::size_t grow = std::max<std::size_t>(1,iMinNumElements);
        if(iMinNumElements>iNumAllocatedElements)
        {
          grow = (std::size_t)std::ceil(1.5*iMinNumElements + 4); 
        }
        return grow;
      }

      template <typename ElementType>
      inline std::size_t ComputeGrow(std::size_t iMinNumElements, std::size_t iNumAllocatedElements)
      {
        return ComputeGrow(iMinNumElements, iNumAllocatedElements, sizeof(ElementType));
      }

      inline std::size_t GetInitialCapacity() { return 0; };

    private:
      // not allowed : which one delete the ptr otherwise?
      ForAnyElementType (const ForAnyElementType&) = delete;
      ForAnyElementType& operator=(const ForAnyElementType&) = delete;
    };

    template<typename ElementType>
    class ForElementType : public ForAnyElementType
    {
    public:
      ForElementType(){};
    };

  };

  template <>
  struct  AllocatorTraits<HeapAllocatorOneStorage> : AllocatorTraitsBase<HeapAllocatorOneStorage>
  {
    enum { supportsMove = true };
  };

  // -------------------------------------------------------------------------------------------------------------- //

  // Implementation with a default stack allocation
  template<std::size_t NumStackElements, typename GeneralAllocatorOneStorage=HeapAllocatorOneStorage>
  class StackThenHeapAllocatorOneStorage
  {        
  public:
    enum { NeedsElementsType = true };

    using ForAnyElementType = void;

    template<typename ElementType>
    class ForElementType
    {
    private:
      alignas(std::alignment_of<ElementType>::value) unsigned char _data[sizeof(ElementType)*NumStackElements]; // Stack memory allocation with correct alignment requirement without any call on ElementType constructor
      typename GeneralAllocatorOneStorage::template ForElementType<ElementType> _allocator;

    public:
      ForElementType(){};

      inline void Move(ForElementType<ElementType> & iToMove)
      {
        if (this != &iToMove)
        {
          if(iToMove._allocator.GetAllocation()!=nullptr)
            _allocator.Move(iToMove._allocator);
          else
            RelocateConstruct<ElementType, ElementType>(_data, reinterpret_cast<ElementType*>(iToMove._data), NumStackElements);
        }
      };

      template<typename EType=ElementType>
      inline EType* GetAllocation() const
      {
        EType * allocData = _allocator.template GetAllocation<EType>();
        return allocData? allocData : (EType*)(_data);
      }


      template<typename U=ElementType>
      inline void ResizeAllocation(size_t iPrevNumElements, size_t iNumElements)
      {
        if(iNumElements<=NumStackElements)
        {
          if(_allocator.template GetAllocation<U>()!=nullptr)
          {
            RelocateConstruct<U,U>(_data, _allocator.template GetAllocation<U>(), iPrevNumElements);
            _allocator.template ResizeAllocation<U>(0,0); // free allocator memory
          }
        }
        else
        {
          if (_allocator.template GetAllocation<U>() == nullptr)
          {
            _allocator.template ResizeAllocation<U>(0, iNumElements);
            RelocateConstruct<U, U>(_allocator.template GetAllocation<U>(), (U*)_data, iPrevNumElements);
          }
          else
          {
            _allocator.template ResizeAllocation<U>(iPrevNumElements, iNumElements);
          }
        }
      }

      inline std::size_t ComputeGrow(std::size_t iMinNumElements, std::size_t iNumAllocatedElements, std::size_t iNbBytesPerElement)
      {
        return iMinNumElements<=NumStackElements? NumStackElements : _allocator.ComputeGrow(iMinNumElements, iNumAllocatedElements, iNbBytesPerElement);
      }

      template <typename EType=ElementType>
      inline std::size_t ComputeGrow(std::size_t iMinNumElements, std::size_t iNumAllocatedElements)
      {
        return ComputeGrow(iMinNumElements, iNumAllocatedElements, sizeof(EType));
      }

      inline std::size_t GetInitialCapacity() { return NumStackElements; };

    private:
      // not allowed
      ForElementType<ElementType> (const ForElementType<ElementType>&) = delete;
      ForElementType<ElementType>& operator=(const ForElementType<ElementType>&) = delete;
    };
  };

  template <std::size_t NumInlineElements, typename GeneralAllocatorOneStorage>
  struct AllocatorTraits<StackThenHeapAllocatorOneStorage<NumInlineElements, GeneralAllocatorOneStorage> > : AllocatorTraitsBase<StackThenHeapAllocatorOneStorage<NumInlineElements, GeneralAllocatorOneStorage> >
  {
    enum { supportsMove = AllocatorTraits<GeneralAllocatorOneStorage>::supportsMove };
  };
};

#endif

