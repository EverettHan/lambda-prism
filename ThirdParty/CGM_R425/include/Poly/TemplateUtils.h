// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// TemplateUtils.h
//
// Place to put generic helpers for template/metaprogramming
// /!\ avoid AIX  compilation for most of the implemenation here,
// oh dear when will we get rid of it...
//
//===================================================================
// Feb 2021 : F1Z : Creation
//===================================================================

#pragma once
#ifndef _AIX
#include "CATErrorDef.h"
#include <functional>
namespace Poly
{
  /**
 * Generic type for condition functions
 */
  template<typename ...Args>
  using Condition = std::function<bool(Args ...iArgs)>;

  /**
   * Generic type for observer functions
   */
  template<typename ...Args>
  using Observer = std::function<HRESULT(Args ...iArgs)>;
};
#endif

