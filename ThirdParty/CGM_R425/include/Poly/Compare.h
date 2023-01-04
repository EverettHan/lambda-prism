//===================================================================
// COPYRIGHT Dassault Systemes 2022
//===================================================================
// Compare.h
//===================================================================
//
// Usage notes:
// General methods for comparison (under Poly namespace)
//
//===================================================================
// Jan 2022 : F1Z : Creation
//===================================================================
#pragma once

// Mathematics
#include "CATMathPoint2D.h"

namespace Poly
{
  bool operator<(const CATMathPoint2D & iFstPnt, const CATMathPoint2D & iSndPnt)
  {
    return iFstPnt.GetX() < iSndPnt.GetX() || (iFstPnt.GetX() == iSndPnt.GetX() && iFstPnt.GetY() < iSndPnt.GetY());
  }

  bool operator==(const CATMathPoint2D & iFstPnt, const CATMathPoint2D & iSndPnt)
  {
    return iFstPnt.GetX() == iSndPnt.GetX() && iFstPnt.GetY() == iSndPnt.GetY();
  }

}
