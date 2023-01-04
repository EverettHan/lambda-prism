// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPoly.h
//
//===================================================================
// Feb 2021 : F1Z : Creation
//===================================================================

#pragma once

#ifndef _AIX_SOURCE
namespace Poly
{
  /** @name Polyhedral Precision
      @{ */
  enum class Precision : unsigned int
  {
    /** Single precision */   eFloat,
    /** Double precision */   eDouble
  };

  /** @} */
};

#define PolyPrecision Poly::Precision

#else

namespace Poly
{
  namespace Precision
  {
    enum
    {
      /** Single precision */   eFloat,
      /** Double precision */   eDouble
    };
  }
}

#define PolyPrecision unsigned int

#endif



