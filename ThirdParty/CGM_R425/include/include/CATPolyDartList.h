//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// List of darts
//
//=============================================================================
//  2006-11-20  BPG: New.
//=============================================================================
#pragma once

#include "CATListPV.h"
#include "Poly/TypeTraits.h"


class CATPolyDartList : public CATListPV
{
public:

  CATPolyDartList () {}

  template<class DART>
  inline int Append (DART* d);

  template<class DART>
  inline DART* Get (int iPos) const;

  template<class DART>
  inline int RemoveValue (DART* d);

};


template<class DART>
inline int CATPolyDartList::Append (DART* d)
{
#ifndef _AIX
  static_assert (Poly::is_same<DART, CATPolyDart2>::value || Poly::is_same<DART, CATPolyDart3>::value);
#endif
  return CATListPV::Append (d);
}


template<class DART>
inline DART* CATPolyDartList::Get (int iPos) const
{
#ifndef _AIX
  static_assert (Poly::is_same<DART, CATPolyDart2>::value || Poly::is_same<DART, CATPolyDart3>::value);
#endif
  return (DART*) operator[] (iPos);
}


template<class DART>
inline int CATPolyDartList::RemoveValue (DART* d)
{
#ifndef _AIX
  static_assert (Poly::is_same<DART, CATPolyDart2>::value || Poly::is_same<DART, CATPolyDart3>::value);
#endif
  return CATListPV::RemoveValue (d);
}
