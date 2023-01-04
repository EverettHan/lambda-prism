// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// TypeTraits
//
// General type traits
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX
#include <type_traits>
#include "IsTrivially.h"
#include "LogicalTraits.h"

namespace Poly
{
  // To know if T can be memcpy instead of having to go via the constructor
  template <typename T, typename Arg>
  struct IsBitwiseConstructible
  {
    static_assert(
      !std::is_reference<T  >::value &&
      !std::is_reference<Arg>::value,
      "IsBitwiseConstructible do not accept reference types");

    static_assert(
      std::is_same<T  , typename std::remove_cv<T  >::type>::value &&
      std::is_same<Arg, typename std::remove_cv<Arg>::type>::value,
      "IsBitwiseConstructible do not accept qualified types");

    // Assume no bitwise construction in general
    enum { value = false };
  };

  template <typename T, typename U>
  struct IsBitwiseConstructible<const T, U> : IsBitwiseConstructible<T, U>{};

  // Const pointers can be bitwise constructed from non-const pointers.
  // This is not true for pointer conversions in general, e.g. where an offset may need to be applied in the case
  // of multiple inheritance, but there is no way of detecting that at compile-time.
  template <typename T>
  struct IsBitwiseConstructible<const T*, T*>
  {
    // Constructing a const T is the same as constructing a T
    enum { value = true };
  };

  template <typename T>
  struct IsBitwiseConstructible<T, T>
  {
    // T can always be bitwise constructed from itself if it is trivially copyable.
    enum { value = IsTriviallyCopyConstructible<T>::value };
  };

  // Unsigned types can be bitwise converted to their signed equivalents, and vice versa.
  // (assuming two's-complement, which we are)
  template <> struct IsBitwiseConstructible<unsigned int,          int>  { enum { value = true }; };
  template <> struct IsBitwiseConstructible<         int, unsigned int>  { enum { value = true }; };
  // TODO: add default type here too

  template <typename ToElementType, typename FromElementType>
  struct CanBitwiseRelocate
  {
    enum
    {
      value = Or<std::is_same<ToElementType, FromElementType>,
      /*///////*/And<IsBitwiseConstructible<ToElementType, FromElementType>, IsTriviallyDestructible<FromElementType> > >::value
    };
  };
};

namespace Poly
{
  // Traits for containers
  template<typename T>
  struct ContainerTraitsBase
  {
    // This should be overridden by every container that supports emptying its contents via a move operation.
    enum { moveWillEmptyContainer = false };
  };
}

#endif

// AIX compliant
namespace Poly
{
  template<typename A, typename B>
  struct is_same
  {
    enum { value = false };
  };

  template<typename A>
  struct is_same<A, A>
  {
    enum { value = true };
  };
};
