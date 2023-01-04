// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// LogicalTraits
//
// Performs logical operations on a sequence of traits
// Can be switched to std::conjunction/disjunction when C++17 is
// avalaible in DS
//
//===================================================================
// 10/20 : F1Z : Creation
// DD/MM
//===================================================================

#pragma once

#ifndef _AIX

namespace Poly
{
  /**
  * Does a boolean AND of the sequence of traits (expect ::value static members).
  */
  template <typename... Types>
  struct And;

  template <bool LHSValue, typename... RHS>
  struct AndValue
  {
    enum { value = And<RHS...>::value };
  };

  template <typename... RHS>
  struct AndValue<false, RHS...>
  {
    enum { value = false };
  };

  template <typename LHS, typename... RHS>
  struct And<LHS, RHS...> : AndValue<LHS::value, RHS...>
  {
  };

  template <>
  struct And<>
  {
    enum { value = true };
  };

  /**
  * Does a boolean OR of the sequence of traits (expect ::value static members).
  */
  template <typename... Types>
  struct Or;

  template <bool LHSValue, typename... RHS>
  struct OrValue
  {
    enum { value = Or<RHS...>::value };
  };

  template <typename... RHS>
  struct OrValue<true, RHS...>
  {
    enum { value = true };
  };

  template <typename LHS, typename... RHS>
  struct Or<LHS, RHS...> : OrValue<LHS::value, RHS...>
  {
  };

  template <>
  struct Or<>
  {
    enum { value = false };
  };

  /**
  * Does a boolean NOT of the ::value static members of the type.
  */
  template <typename Type>
  struct Not
  {
    enum { value = !Type::value };
  };
};

#endif
