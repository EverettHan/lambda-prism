// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyListPVIterator.h
//
//===================================================================
// 22/10/18 F1Z : Creation
// DD/MM/YY
//===================================================================

#ifndef CATPolyListPVIterator_H
#define CATPolyListPVIterator_H

// System
#include "CATListPV.h"

template<class PointerType = void>
class CATPolyListPVIterator
{
public:
  CATPolyListPVIterator(const CATListPV & iToIterateOn) : _list(iToIterateOn), _position(1) {};
  virtual ~CATPolyListPVIterator(){};

  inline CATPolyListPVIterator   &  Begin     ()       { _position = 1; return *this; };
  inline PointerType           *    operator* () const { return (PointerType*) _list[_position]; };
  inline CATPolyListPVIterator   &  operator++()       { ++_position; return *this; };
  inline bool                       End       ()       { return _position>_list.Size(); };

private:
  const CATListPV & _list;
        int         _position;
};

#endif

