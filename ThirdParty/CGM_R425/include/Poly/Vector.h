// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// Vector
//
// As opposed to the std implementation, this vector directly handle one
// mem storage at a given time, and can avoid when possible copy report of
// content when a resize occurs according the allocator specify. This improves the performances
// in sensible context. If the resize performance isn't an issue, use std::vector instead.
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX_SOURCE

// PolyhedralMathematics
#include "Poly/AllocatorOneStorage.h"
#include "Poly/MemoryOps.h"
#include "Poly/TypeTraits.h"

// std
#include <cstddef>
#include <utility>
#include <iterator>

namespace Poly
{
  template <typename VectorType>
  struct ContainerTraits : public Poly::ContainerTraitsBase<VectorType>
  {
    enum { moveWillEmptyContainer = Poly::AllocatorTraits<typename VectorType::allocator_type>::supportsMove };
  };

  template<typename ToVectorType, typename FromVectorType>
  struct CanMoveVectorPtr
  {
    enum {
      value = std::is_same<typename ToVectorType::allocator_type, typename FromVectorType::allocator_type>::value &&
      /*////////*/ ContainerTraits<FromVectorType>::moveWillEmptyContainer &&
      /*////////*/ (std::is_same<typename ToVectorType::value_type, typename FromVectorType::value_type>::value ||
                    IsBitwiseConstructible<typename ToVectorType::value_type, typename FromVectorType::value_type>::value)
    };
  };

  template<typename ElementType, typename Allocator = Poly::HeapAllocatorOneStorage>
  class Vector
  {
  private:
    typename std::conditional<Allocator::NeedsElementsType, typename Allocator::template ForElementType<ElementType>, typename Allocator::ForAnyElementType >::type _allocator;
    std::size_t _size;
    std::size_t _capacity;

  public:
    using allocator_type = Allocator;
    using value_type = ElementType;
    using reference = ElementType&;
    using const_reference = const ElementType&;
    using pointer = ElementType*;
    using const_pointer = const ElementType*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  public:
    inline Vector()
    {
      _size = 0;
      _capacity = 0;
    }

    inline Vector(const std::size_t iSI, const ElementType & iVal = ElementType())
    {
      _size = 0;
      _capacity = 0;
      reserve(iSI);
      _size = iSI;
      Poly::ConstructFromValue<ElementType>(_allocator.GetAllocation(), iVal, _size);
    }

    template<typename OtherAllocator>
    inline Vector(const Vector<ElementType, OtherAllocator> & iToCopy)
    {
      _size = 0;
      _capacity = 0;
      reserve(iToCopy._capacity);
      _size = iToCopy._size;
      Poly::Construct<ElementType>(_allocator.GetAllocation(), iToCopy._allocator.template GetAllocation<OtherAllocator>(), iToCopy._capacity);
    }

    inline Vector(const Vector & iToCopy)
    {
      _size = 0;
      _capacity = 0;
      reserve(iToCopy._capacity);
      _size = iToCopy._size;
      Poly::Construct<ElementType>(_allocator.GetAllocation(), iToCopy._allocator.template GetAllocation<ElementType>(), iToCopy._capacity);
    }

    inline Vector(Vector && iToMoveOrCopy)
    {
      _size = 0;
      _capacity = 0;
      MoveOrCopy(iToMoveOrCopy);
    }

    inline ~Vector()
    {
      clear();
    };

    template<typename OtherAllocator>
    Vector<ElementType, Allocator> & operator=(const Vector<ElementType, OtherAllocator> & iToCopy)
    {
      clear();
      reserve(iToCopy._capacity);
      _size = iToCopy._size;
      Poly::Construct<ElementType>(_allocator.GetAllocation(), iToCopy._allocator.template GetAllocation<ElementType>(), iToCopy._capacity); 
      return *this;
    }

    Vector & operator=(const Vector & iToCopy)
    {
      clear();
      reserve(iToCopy._capacity);
      _size = iToCopy._size;
      Poly::Construct<ElementType>(_allocator.GetAllocation(), iToCopy._allocator.template GetAllocation<ElementType>(), iToCopy._capacity); 
      return *this;
    }

    Vector & operator=(Vector && iToMoveOrCopy)
    {
      clear();
      MoveOrCopy(iToMoveOrCopy);
      return *this;
    }

    inline void reserve(std::size_t iSize)
    {
      if(_capacity<iSize)
      {
        _allocator.template ResizeAllocation<ElementType>(_capacity, iSize);
        _capacity = iSize;
      }
    }

    inline void resize(std::size_t iSize)
    {
      reserve(iSize);

      if(iSize > _size)
        Construct<ElementType>(begin() + _size, iSize-_size);
      else
        Destruct<ElementType>(begin() + iSize, _size-iSize);

      _size = iSize;
    }

    inline void shrink_to_fit()
    {
      if(_capacity!=_size)
      {
        _allocator.template ResizeAllocation<ElementType>(_size, _size);
        _capacity = _size;
      }
    }

    inline ElementType & operator[](std::size_t id)
    {
      return begin()[id];
    }

    inline const ElementType & operator[](std::size_t id) const
    {
      return reinterpret_cast<const ElementType&>(begin()[id]);
    }

    template <typename... ArgsType>
    inline std::size_t emplace_back(ArgsType&&... Args)
    {
      const std::size_t pos = AddUninitialized(1);
      new(begin() + pos) ElementType(std::forward<ArgsType>(Args)...);
      return pos;
    }

    template <typename... ArgsType>
    inline iterator emplace(std::size_t iIdInsert, ArgsType&&... Args)
    {
      InsertUninitialized(iIdInsert, 1);
      new(begin() + iIdInsert) ElementType(std::forward<ArgsType>(Args)...);
      return (begin() + iIdInsert);
    }

    template<typename... ArgsType>
    inline iterator emplace(iterator pos, ArgsType&&...Args)
    {
      std::size_t idEmplace = (pos-begin());
      return emplace(idEmplace, std::forward<ArgsType>(Args)...);
    }

    inline void push_back(const ElementType & iToCopy)
    {
      emplace_back(iToCopy);
    }

    inline void pop_back()
    {
      if(_size>0)
        erase(_size-1);
    }

    void clear()
    {
      Poly::Destruct<ElementType>(begin(), _size);
      _size = 0;
    }

    void erase(std::size_t iIdErase)
    {
      Poly::Destruct<ElementType>(begin() + iIdErase, 1);
      std::size_t nbMove = _size - iIdErase - 1;
      if(nbMove>0)
        Poly::RelocateConstruct<ElementType>(begin() + iIdErase, begin() + iIdErase + 1, nbMove);
      _size = _size -1;
    }

    void erase(iterator pos)
    {
      std::size_t idErase = (pos-begin());
      return erase(idErase);
    }

    inline std::size_t size() const { return _size; };

  public:
    inline iterator begin() { return _allocator.template GetAllocation<ElementType>();};
    inline iterator end() { return begin() + _size; };
    inline const_iterator begin() const { return ((Vector<ElementType,Allocator>*)this)->begin();};
    inline const_iterator end() const { return ((Vector<ElementType,Allocator>*)this)->end(); };
    inline const_iterator cbegin() const { return begin(); };
    inline const_iterator cend() const { return end(); };
    inline reverse_iterator rbegin() { return reverse_iterator(begin());};
    inline reverse_iterator rend() {return reverse_iterator(end());};
    inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend());};
    inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin());};

    inline reference front() {return *begin();};
    inline const_reference cfront() const { return *begin();};
    inline reference back() { return *(end()-1); };
    inline const_reference cback() const { return *back();};


  private:
    std::size_t AddUninitialized(std::size_t iNumElements)
    {
      std::size_t newSize = _size + iNumElements;
      ResizeGrow(newSize);
      _size = newSize;
      return _size - iNumElements;
    }

    void InsertUninitialized(std::size_t iIdInsert, std::size_t iNumElements)
    {
      std::size_t newSize = _size + iNumElements;
      ResizeGrow(newSize);

      ElementType* Data = begin() + iIdInsert;
      Poly::RelocateConstruct<ElementType>(Data + iNumElements, Data, _size - iIdInsert);

      _size = newSize;
    }

    void ResizeGrow(std::size_t iNumElements)
    {
      if(_capacity<iNumElements)
      {
        std::size_t grow = _allocator.template ComputeGrow<ElementType>(iNumElements, _size);
        _allocator.template ResizeAllocation<ElementType>(_size, grow);
        _capacity = grow;
      }
    }

    template<typename FromVectorType>
    inline typename std::enable_if<CanMoveVectorPtr<Vector<ElementType, Allocator>, FromVectorType>::value>::type MoveOrCopy(FromVectorType & iFromVector)
    {
      _allocator.Move(iFromVector._allocator);
      _size = iFromVector._size;
      _capacity = iFromVector._capacity;
      iFromVector._size = 0;
      iFromVector._capacity = iFromVector._allocator.GetInitialCapacity();
    }

    template<typename FromVectorType>
    inline typename std::enable_if<!CanMoveVectorPtr<Vector<ElementType,Allocator>, FromVectorType>::value>::type MoveOrCopy(FromVectorType & iFromVector)
    {
       (*this)=iFromVector;
    }
  };
}

#define PolyVector Poly::Vector

#else

#include "CATCGMSTDSafeIncludeStart.h"

#ifndef __IBMCPP_TR1__
#define __IBMCPP_TR1__ 1
#include <vector>
#undef __IBMCPP_TR1__
#else 
#include <vector>
#endif
#define PolyVector std::vector

#include "CATCGMSTDSafeIncludeEnd.h"


#endif

