// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//===================================================================
//
// CATVectorOfType.h
//
//===================================================================
// January 2022  Creation: JBS2
//===================================================================
#ifndef CATVectorOfType_h
#define CATVectorOfType_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include <cstring>
#include <type_traits>
//#include <numeric_limits> // For debugging purpose.
//#include "CATAssert.h"

/*
Fixed size vector N elements of type T.
*/
template <typename T, int N>
class CATVectorOfType
{

public:

  /*
   * Construction of a vector of a given size.
   */
  inline CATVectorOfType(const unsigned int iSize);

  inline ~CATVectorOfType();

  inline unsigned int Size() const;

  inline HRESULT Resize (const unsigned int iSize);

public:

  /**
   * Returns a pointer to N elements of T.
   * The index ranges from 1 to Size () inclusive.
   */
  inline std::conditional_t<(N > 1), const T*, T>  operator [](const unsigned int index) const;

  /**
   * Returns a pointer to N elements of T.
   * The index ranges from 1 to Size () inclusive.
   */
  inline std::conditional_t<(N > 1), T*, T&> operator [](const unsigned int index);

private:

  T* _Data;
  unsigned int _Size;

};


template <typename T, int N>
inline CATVectorOfType<T, N>::CATVectorOfType (const unsigned int iSize) :
  _Data (iSize > 0 ? new T[N * iSize] : 0),
  _Size (iSize)
{
  // For debugging purpose.
  //if (_Data)
  //{
  //  for (unsigned int k = 0; k < N * iSize; ++k)
  //  {
  //    _Data[k] = std::numeric_limits<T>::max();
  //  }
  //}
}

template <typename T, int N>
inline CATVectorOfType<T, N>::~CATVectorOfType ()
{
  delete[] _Data;
  _Data = 0;
}

template <typename T, int N>
inline unsigned int CATVectorOfType<T, N>::Size () const
{
  return _Size;
}

template <typename T, int N>
inline HRESULT CATVectorOfType<T, N>::Resize (const unsigned int iSize)
{
  T* newData = new T[N * iSize];
  if (newData)
  {
    if (iSize > _Size)
      memset (newData + _Size, 0, (iSize - _Size) * N * sizeof (T)); // init.
    if (_Data)
    {
      unsigned int copySize = iSize > _Size ? _Size : iSize;
      memcpy (newData, _Data, copySize * N * sizeof (T)); // Copy the data.
      delete[] _Data;
    }
    _Data = newData;
    _Size = iSize;
  }
  else
    return E_OUTOFMEMORY;
  return S_OK;
}

template <typename T, int N>
inline std::conditional_t<(N > 1), const T*, T> CATVectorOfType<T, N>::operator [] (const unsigned int index) const
{
  //if (index == 0 || index > _Size)  // For debugging purpose.
    //CATAssert (0);
  if constexpr(N > 1)
    return _Data ? _Data + N*(index-1) : 0;  // No check of range.
  else
    return _Data ? _Data[index-1] : 0;  // No check of range.
}

template <typename T, int N>
inline std::conditional_t<(N > 1), T*, T&> CATVectorOfType<T, N>::operator [] (const unsigned int index)
{
  //if (index == 0 || index > _Size)  // For debugging purpose.
    //CATAssert (0);
  if constexpr(N > 1)
    return _Data ? _Data + N*(index-1) : 0;  // No check of range.
  else
    return _Data[index-1];
}

#endif
