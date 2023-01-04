// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATStackOfInt.h
//
//===================================================================
// January 2012  Creation: NDO
//===================================================================
#ifndef CATStackOfInt_h
#define CATStackOfInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"

#include "CATListOfInt.h"


/*
LIFO stack of integers.
*/
class CATStackOfInt
{

public:

  /*
   * Construction of a stack with an optional pre-allocated dimension.
   */
  inline CATStackOfInt (const unsigned int iInitialAllocation = 0);

  inline ~CATStackOfInt () {}

  /**
   * Returns the number of elements in the stack.
   */
  inline unsigned int Size () const;

public:

  /**
   * Pushes an integer to the stack.
   */
  inline HRESULT Push (const int k);

  /**
   * Pops an integer from the stack.
   * @return 
   *   <ul>
   *      <li> S_OK if an element is returned.
   *      <li> S_FALSE if the stack is empty.
   *   </ul>
   */
  inline HRESULT Pop (int& index);

private:

  CATListOfInt _Stack;
  unsigned int _NbElements;

};


inline CATStackOfInt::CATStackOfInt (const unsigned int iInitialAllocation) : 
  _Stack (iInitialAllocation),
  _NbElements (0)
{
}

inline unsigned int CATStackOfInt::Size () const
{
  return _NbElements;
}

inline HRESULT CATStackOfInt::Push (const int k)
{
  if (_NbElements < (unsigned int)_Stack.Size ())
  {
    _Stack[++_NbElements] = k;
    return S_OK;
  }
  else if (_Stack.Append (k) == 0)
  {
    ++_NbElements;
    return S_OK;
  }
  return E_FAIL;
}

inline HRESULT CATStackOfInt::Pop (int& k)
{
  if (_NbElements)
  {
    k = _Stack[_NbElements--];
    return S_OK;
  }
  return S_FALSE;
}

#endif
