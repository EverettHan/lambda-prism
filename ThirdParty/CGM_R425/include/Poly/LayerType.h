// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPoly.h
//
//===================================================================
// Feb 2021 : F1Z : Creation
//===================================================================

#pragma once

#ifndef _AIX

namespace Poly
{
  /** @name Polyhedral Precision
      @{ */
  enum LayerType /// not an enum class since each value is a bit, the use is to combine them
  {
    ePosition = 1<<0,
    eNormal = 1<<1,
    eUV = 1<<2
  };

  /** @} */
}

#else

namespace Poly
{
  namespace LayerType
  {
    enum
    {
      ePosition = 1<<0,
      eNormal = 1<<1,
      eUV = 1<<2
    };
  }
}
#endif
