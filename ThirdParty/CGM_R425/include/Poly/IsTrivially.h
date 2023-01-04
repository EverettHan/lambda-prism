// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// IsTrivially
//
// For metaprogramming, to know if the class/struct has a compilator generated
// operators for optimisation
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX 

namespace Poly
{
  template <typename T>
  struct IsTriviallyCopyAssignable
  {
    enum { value = __has_trivial_assign(T) };
  };

  template <typename T>
  struct IsTriviallyCopyConstructible
  {
    enum { value = __has_trivial_copy(T) };
  };

  namespace Private
  {
    // We have this specialization for enums to avoid the need to have a full definition of
    // the type.
    template <typename T, bool bIsTriviallyTriviallyDestructible = __is_enum(T)>
    struct IsTriviallyDestructibleImpl
    {
      enum { value = true };
    };

    template <typename T>
    struct IsTriviallyDestructibleImpl<T, false>
    {
      enum { value = __has_trivial_destructor(T) };
    };
  };

  template <typename T>
  struct IsTriviallyDestructible
  {
    enum { value = Private::IsTriviallyDestructibleImpl<T>::value };
  };
}

#endif
