//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-05-13 - T6L : Creation
//==============================================================================================================

#ifndef CATExpEnums_H
#define CATExpEnums_H
#include "CATIAV5Level.h"

#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif

enum CATExpBool_t { CATExpTRUE = 1, CATExpFALSE = 0, CATExpBOOLUNDEF = -2 };
inline CATExpBool_t operator! (CATExpBool_t b) __EXPNOEXCEPT__
{ 
  switch (b)
  {
  case CATExpTRUE: return CATExpFALSE;
  case CATExpFALSE: return CATExpTRUE;
  default: return b;
  };
}

enum CATExpSign_t { CATExpNEGATIVE = -1, CATExpZERO = 0, CATExpPOSITIVE = 1, CATExpSIGNUNDEF = -2 };
inline CATExpSign_t operator! (CATExpSign_t s) __EXPNOEXCEPT__
{ 
  switch (s)
  {
  case CATExpNEGATIVE: return CATExpPOSITIVE;
  case CATExpPOSITIVE: return CATExpNEGATIVE;
  default: return s;
  };
}
inline CATExpSign_t operator* (CATExpSign_t a, CATExpSign_t b) __EXPNOEXCEPT__
{ 
  if (a == CATExpSIGNUNDEF || b == CATExpSIGNUNDEF) return CATExpSIGNUNDEF;
  else return static_cast<CATExpSign_t>(static_cast<int>(a) * static_cast<int>(b));
}



/** Position of a point on an arc / segment : inside, outside, on extremity 1/2 */
enum CATExpPosition_t { CATExpOUTSIDE = -1, CATExpEXTREMITY1 = 0, CATExpINSIDE = 1, CATExpEXTREMITY2 = 2, CATExpPOSUNDEF = -2 };
inline CATExpPosition_t operator! (CATExpPosition_t p) __EXPNOEXCEPT__
{
  switch (p)
  {
  case CATExpOUTSIDE: return CATExpINSIDE;
  case CATExpEXTREMITY1: return CATExpEXTREMITY2;
  case CATExpINSIDE: return CATExpOUTSIDE;
  case CATExpEXTREMITY2: return CATExpEXTREMITY1;
  default: return p;
  };
}

#endif 
