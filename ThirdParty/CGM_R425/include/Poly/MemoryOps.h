// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// MemoryOps
//
// Operations on memory
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX

#include <type_traits>
#include <string.h>
#include <cstddef>

#include "TypeTraits.h"

namespace Poly
{
  /**
  * Relocates a range of elements to a new memory location as a new type. This is a so-called 'destructive move' for which
  * there is no single operation in C++ but which can be implemented very efficiently in general.
  *
  * @param	Dest  The memory location to relocate to.
  * @param	From  A pointer to the first item to relocate.
  * @param	Count The number of elements to relocate.
  */
  template <typename ToElementType, typename FromElementType>
  inline typename std::enable_if<!CanBitwiseRelocate<ToElementType, FromElementType>::value>::type RelocateConstruct(void* Dest, const FromElementType* From, std::size_t Count)
  {
    while (Count)
    {
      typedef FromElementType RelocateConstructItemsElementTypeTypedef;

      new (Dest) ToElementType(*From);
      ++(ToElementType*&)Dest;
      (From++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
      --Count;
    }
  }

  template <typename ToElementType, typename FromElementType>
  inline typename std::enable_if<CanBitwiseRelocate<ToElementType, FromElementType>::value>::type RelocateConstruct(void* Dest, const FromElementType* From, std::size_t Count)
  {
    memmove(Dest, From, sizeof(FromElementType) * Count); // avoid constructor call since trivial copy impl
  }
};

namespace Poly
{
  /**
  * Constructs a range of elements into memory from a set of arguments.  The arguments come from an another array.
  *
  * @param	Dest  The memory location to start copying into.
  * @param	From  A pointer to the first argument to pass to the constructor.
  * @param	Count The number of elements to copy.
  */
  template <typename ToElementType, typename FromElementType>
  inline typename std::enable_if<!CanBitwiseRelocate<ToElementType, FromElementType>::value>::type Construct(void* Dest, const FromElementType* From, std::size_t Count)
  {
    while (Count)
    {
      new (Dest) ToElementType(*From);
      ++(ToElementType*&)Dest;
      ++From;
      --Count;
    }
  }


  template <typename ToElementType, typename FromElementType>
  inline typename std::enable_if<CanBitwiseRelocate<ToElementType, FromElementType>::value>::type Construct(void* Dest, const FromElementType* From, std::size_t Count)
  {
    memmove(Dest, From, sizeof(FromElementType) * Count);
  }

  // Same but based on a default value (copy constructor)
  template<typename ToElementType, typename FromElementType>
  inline void ConstructFromValue(void *Dest, const FromElementType & iDefaultValue, std::size_t Count)
  {
    while (Count)
    {
      new (Dest) ToElementType(iDefaultValue);
      ++(ToElementType*&)Dest;
      --Count;
    }
  }

  template<typename ElementType>
  inline typename std::enable_if<!IsBitwiseConstructible<ElementType,ElementType>::value>::type Construct(void * Dest, std::size_t Count)
  {
    while(Count)
    {
      new (Dest) ElementType();
      ++(ElementType*&)Dest;
      --Count;
    }
  }

  template<typename ElementType>
  inline typename std::enable_if<IsBitwiseConstructible<ElementType,ElementType>::value>::type Construct(void * Dest, std::size_t Count)
  {
    memset(Dest, 0, sizeof(ElementType)*Count);
  }
};

namespace Poly
{
  /**
  * Destructs a single element in memory.
  *
  * @param	Elements	A pointer to the element to destruct.
  *
  * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
  */
  template <typename ElementType>
  inline typename std::enable_if<Not<IsTriviallyDestructible<ElementType> >::value>::type Destruct(ElementType* Element)
  {
    typedef ElementType DestructElementTypeTypedef;

    Element->DestructElementTypeTypedef::~DestructElementTypeTypedef();
  }


  template <typename ElementType>
  inline typename std::enable_if<IsTriviallyDestructible<ElementType>::value>::type Destruct(ElementType* Element)
  {
  }

  /**
  * Destructs a range of elements in memory.
  *
  * @param	Elements	A pointer to the first element to destruct.
  * @param	Count		The number of elements to destruct.
  *
  * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
  */
  template <typename ElementType>
  inline typename std::enable_if<Not<IsTriviallyDestructible<ElementType> >::value>::type Destruct(ElementType* Element, std::size_t Count)
  {
    typedef ElementType DestructElementTypeTypedef;
    while (Count)
    {
      // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
      Element->DestructElementTypeTypedef::~DestructElementTypeTypedef();
      ++Element;
      --Count;
    }
  }


  template <typename ElementType>
  inline typename std::enable_if<IsTriviallyDestructible<ElementType>::value,void>::type Destruct(ElementType* Elements, std::size_t Count)
  {
  }
};

#endif
