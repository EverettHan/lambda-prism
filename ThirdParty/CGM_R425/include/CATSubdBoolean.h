// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATSubdBoolean :
// type enumere 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 96  Creation                          I. Chauvigne, X. Dupont, L. Laloy
//=============================================================================
#ifndef CATSubdBoolean_H
#define CATSubdBoolean_H

#include "CATBoolean.h"
#include "CATSubdBlockThrow.h"
#include "CATSubdInternalError.h"
#include "CATMathInline.h"
#include "CATTopDefine.h"

typedef enum
{
   CATSubdBooleanFalse = -1,
   CATSubdBooleanUnknown = 0,
   CATSubdBooleanTrue = 1,
   CATSubdBooleanUnset = 2
} 
CATSubdBoolean;

// service de Cast
inline int CATSubdCastBooleanToInt(CATSubdBoolean iBoolean);
inline CATSubdBoolean CATSubdCastIntToBoolean(int iInt);
inline CATBoolean CATSubdCastSubdBooleanToCATBoolean(CATSubdBoolean iA);
inline CATSubdBoolean CATSubdCastCATBooleanToSubdBoolean(CATBoolean iA);

// utile quand on se sert du CATSubdBoolean pour determiner une orientation relative
#define CATSubdBooleanMultiply(Boolean1, Boolean2)                            \
((Boolean1 != CATSubdBooleanUnset && Boolean2 != CATSubdBooleanUnset) ?       \
((CATSubdBoolean)(Boolean1*Boolean2)) : CATSubdBooleanUnset)

// on definit par la suite les operateurs standards pour une utilisation logique 
// de CATSubdBoolean : Or, Xor, And, Not qui rendent le resultat logique associe
// s'il est determinable, Unknown sinon ou Unset si tous les inputs sont Unset

inline int CATSubdCastBooleanToInt(CATSubdBoolean iBoolean)
{
   if (iBoolean == CATSubdBooleanTrue)
      return 1;
   else if (iBoolean == CATSubdBooleanFalse)
      return -1;
   else if (iBoolean == CATSubdBooleanUnknown)
      return 0;
   else
      return 2;
}

inline CATSubdBoolean CATSubdCastIntToBoolean(int iInt)
{   
   if (iInt == 1)
      return CATSubdBooleanTrue;
   else if (iInt == -1)
      return CATSubdBooleanFalse;
   else if (iInt == 0)
      return CATSubdBooleanUnknown;
   else
      return CATSubdBooleanUnset;
}

// WQO Oct. 09 convertisseurs au sens logique
inline CATBoolean CATSubdCastSubdBooleanToCATBoolean(CATSubdBoolean iA)
{
  CATBoolean res;
  if (iA == CATSubdBooleanTrue)
    res = TRUE;
  else if (iA == CATSubdBooleanFalse)
    res = FALSE;
  else 
    CATSubdBlockThrowInternalError();
  return res;
}

inline CATSubdBoolean CATSubdCastCATBooleanToSubdBoolean(CATBoolean iA)
{
  CATSubdBoolean res = CATSubdBooleanUnknown;
  if (iA == TRUE)
    res = CATSubdBooleanTrue;
  else if (iA == FALSE)
    res = CATSubdBooleanFalse;
  return res;
}

// WQO Oct. 09 resultat = a ou b au sens logique
inline CATSubdBoolean CATSubdBooleanOr(CATSubdBoolean iA,
                                       CATSubdBoolean iB)
{   
  CATSubdBoolean res = CATSubdBooleanUnknown;
  if ((iA == CATSubdBooleanTrue) || (iB == CATSubdBooleanTrue))
    res = CATSubdBooleanTrue;
  else if ((iA == CATSubdBooleanFalse) && (iB == CATSubdBooleanFalse))
    res = CATSubdBooleanFalse;
  else if ((iA == CATSubdBooleanUnset) && (iB == CATSubdBooleanUnset))
    res = CATSubdBooleanUnset;
  return res;
}

INLINE CATSubdBoolean operator || (CATSubdBoolean iA,
                                   CATSubdBoolean iB)
{
  return CATSubdBooleanOr(iA, iB);
}

INLINE void operator |= (CATSubdBoolean & iA,
                         CATSubdBoolean   iB)
{
  iA = iA || iB;
}

// WQO Oct. 09 resultat = a ou b au sens logique et exclusif
inline CATSubdBoolean CATSubdBooleanXOr(CATSubdBoolean iA,
                                        CATSubdBoolean iB)
{   
  CATSubdBoolean res = CATSubdBooleanUnknown;
  if ( ((iA == CATSubdBooleanTrue) && (iB == CATSubdBooleanTrue))
    || ((iA == CATSubdBooleanFalse) && (iB == CATSubdBooleanFalse)) )
    res = CATSubdBooleanFalse;
  else if ( ((iA == CATSubdBooleanTrue) && (iB == CATSubdBooleanFalse))
         || ((iA == CATSubdBooleanFalse) && (iB == CATSubdBooleanTrue)) )
    res = CATSubdBooleanTrue;
  else if ((iA == CATSubdBooleanUnset) && (iB == CATSubdBooleanUnset))
    res = CATSubdBooleanUnset;
  return res;
}

// WQO Oct. 09 resultat = a et b au sens logique
inline CATSubdBoolean CATSubdBooleanAnd(CATSubdBoolean iA,
                                        CATSubdBoolean iB)
{   
  CATSubdBoolean res = CATSubdBooleanUnknown;
  if ((iA == CATSubdBooleanTrue) && (iB == CATSubdBooleanTrue))
    res = CATSubdBooleanTrue;
  else if ((iA == CATSubdBooleanFalse) || (iB == CATSubdBooleanFalse))
    res = CATSubdBooleanFalse;
  else if ((iA == CATSubdBooleanUnset) && (iB == CATSubdBooleanUnset))
    res = CATSubdBooleanUnset;
  return res;
}

INLINE CATSubdBoolean operator && (CATSubdBoolean iA,
                                   CATSubdBoolean iB)
{
  return CATSubdBooleanAnd(iA, iB);
}

INLINE void operator &= (CATSubdBoolean & iA,
                         CATSubdBoolean   iB)
{
  iA = iA && iB;
}

// WQO Oct. 09 resultat = !a au sens logique
inline CATSubdBoolean CATSubdBooleanNot(CATSubdBoolean iA)
{   
  CATSubdBoolean res = CATSubdBooleanUnknown;
  if (iA == CATSubdBooleanTrue)
    res = CATSubdBooleanFalse;
  else if (iA == CATSubdBooleanFalse)
    res = CATSubdBooleanTrue;
  else if (iA == CATSubdBooleanUnset)
    res = CATSubdBooleanUnset;
  return res;
}

INLINE CATSubdBoolean operator ! (CATSubdBoolean iA)
{
  return CATSubdBooleanNot(iA);
}

// Convertisseurs CATOrientation <-> CATSubdBoolean
inline CATSubdBoolean ConvertOrientationIntoSubdBoolean(CATOrientation iOrientation)
{
  CATSubdBoolean oSubdBoolean = CATSubdBooleanUnset;

  switch (iOrientation)
  {
  case CATOrientationPositive:
    oSubdBoolean = CATSubdBooleanTrue   ; break;
  case CATOrientationNegative:
    oSubdBoolean = CATSubdBooleanFalse  ; break;
  case CATOrientationUnknown :
    oSubdBoolean = CATSubdBooleanUnknown; break;
  default:
    CATSubdBlockThrowInternalError();
  }

  return oSubdBoolean;
}
inline CATOrientation ConvertSubdBooleanIntoOrientation(CATSubdBoolean iSubdBoolean)
{
  CATOrientation oOrientation = CATOrientationUnknown;

  switch (iSubdBoolean)
  {
  case CATSubdBooleanTrue   :
    oOrientation = CATOrientationPositive; break;
  case CATSubdBooleanFalse  :
    oOrientation = CATOrientationNegative; break;
  case CATSubdBooleanUnknown:
  case CATSubdBooleanUnset  :
    oOrientation = CATOrientationUnknown ; break;
  default:
    CATSubdBlockThrowInternalError();
  }

  return oOrientation;
}

#endif
