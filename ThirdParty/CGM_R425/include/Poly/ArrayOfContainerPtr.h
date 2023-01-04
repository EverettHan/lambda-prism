// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// ArrayOfContainerPtr.h
// Header definition of ArrayOfContainerPtr
//
//===================================================================
//
// Usage notes: Array of a container ptr
// the array is empty, allocate container at a given index.
// Only useful for large array mostly empty for memory optimisation
//
//===================================================================
// oct 2020 : F1Z : Creation
//===================================================================
#pragma once

#ifndef _AIX

// PolyhedralMathematics
#include "CATPolyBuckets.h"
#include "CATPolyBucketsCache.h"
#include "Poly/Vector.h"

// std
#include <cstddef>
#include <utility>
#include <iterator>

namespace Poly
  {
  template<typename Container, typename ArrayType=Poly::Vector<Container*> >
  class ArrayOfContainerPtr
  {
  public:
    using value_type = typename Container::value_type;

  private:
    CATPolyBucketsCache<Container> _containerCache;
    ArrayType _array;

  public:
    inline ArrayOfContainerPtr(std::size_t iSize)
    {
      _array.resize(iSize);
    }

    inline ~ArrayOfContainerPtr()
    {
      _array.clear();
    }

    inline void emplace_back(const std::size_t iIdInsert, const value_type iElement)
    {
      if(_array[iIdInsert]==nullptr)
        _array[iIdInsert] = _containerCache.New();
      _array[iIdInsert]->emplace_back(iElement);
    }

    inline HRESULT erase(const std::size_t iIdErase, const value_type iElement)
    {
      return (_array[iIdErase])? _array[iIdErase]->erase(iElement) : S_OK;
    }

    inline void clear(const std::size_t iIdErase)
    {
      if(_array[iIdErase])
        _array[iIdErase]->resize(0);

      _containerCache.Free(_array[iIdErase]);
      _array[iIdErase] = nullptr;
    }

    inline typename Container::iterator begin(const std::size_t iIdContainer) const { return _array[iIdContainer]? _array[iIdContainer]->begin() : nullptr; };
    inline typename Container::iterator end(const std::size_t iIdContainer) const { return _array[iIdContainer]? _array[iIdContainer]->end() : nullptr; };

    std::size_t size() const { return _array.size(); };

  private:
    ArrayOfContainerPtr(const ArrayOfContainerPtr &) = delete; // to implement
    ArrayOfContainerPtr & operator=(const ArrayOfContainerPtr &) = delete; // to implement
  };
};

#endif
