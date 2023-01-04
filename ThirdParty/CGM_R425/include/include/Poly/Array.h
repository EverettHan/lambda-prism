// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDeltaMesh.h
//
//===================================================================
// Feb 2021 F1Z : Creation
//===================================================================

#pragma once

#include <utility>

namespace Poly
{
  /// Very simple implementation, to complete
  template<typename Type, unsigned int Size>
  class Array
  {
  private:
    Type _data[Size];
  public:
    Array() {};
    Array(Type * iToCopy) { memcpy(_data, iToCopy, Size * sizeof(Type)); };
    Type * GetData() { return _data; };
    Type operator[](unsigned int iId) const { return _data[iId]; };
    Type & operator[](unsigned int iId) { return _data[iId]; };
    unsigned int size() const { return Size; };
    bool operator==(const Array<Type, Size> & iToCompare)
    {
      bool areEq = true;
      for (int i = 0; i < Size && areEq; ++i)
        areEq = _data[i] == iToCompare._data[i];
      return areEq;
    }
  };

  template<typename Type>
  Array<Type, 2> BuildArray2(Type i0, Type i1) /// mostly for aix compilation...
  {
    Array<Type, 2> ret;
    ret[0] = i0;
    ret[1] = i1;
    return ret;
  }

  template<typename Type>
  Array<Type,3> BuildArray3(Type i0, Type i1, Type i2) /// mostly for aix compilation...
  {
    Array<Type,3> ret;
    ret[0] = i0;
    ret[1] = i1;
    ret[2] = i2;
    return ret;
  }
}
