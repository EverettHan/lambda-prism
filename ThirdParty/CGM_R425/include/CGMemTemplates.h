#ifndef CGMemTemplates_h
#define CGMemTemplates_h

#include "CATCGMemory.h"

//======================================================================
// TEMPLATES
//======================================================================

/**
* You can write:
*   CGMemDeallocate(MyArray);
* instead of
*   CATCGMemClear((void *)ioArray);
*   ioArray = NULL;
*/
template <class T>
void CGMemDeallocate(T *& ioArray)
{
  CATCGMemClear((void *)ioArray);
  ioArray = NULL;
}

/**
* Useful to call CGMemDeallocate in destructor
*/
#define LDestructor(CLASS) CLASS::~CLASS()

/**
* You can write:
*   CGMemInitialize<MyType>(MyArray, NbElements, 0);
* instead of
*   memset(MyArray, 0, NbElements * sizeof(MyType));
* Moreover, memset doesn't work when the filler is not 0!
*/
template <class T>
void CGMemInitialize(T * ioArray, int iNbElem, T iFiller)
{
  T * CurrentElement = ioArray;
  T * LastPlus1 = ioArray + iNbElem;
  while (CurrentElement != LastPlus1)
  {
    (*CurrentElement) = iFiller;
    CurrentElement++;
  }
}

/**
* You can write:
*   MyType * MyArray = CGMemAllocate<MyType>(NbElements);
* instead of
*   MyType * MyArray = (MyType *)CATCGMemBook((size_t)(NbElements * sizeof(MyType)));
*/
template <class T>
T * CGMemAllocate(int iNbElem)
{
  size_t AllocationSize = (size_t)(iNbElem * sizeof(T));
  T * Array = (T *)CATCGMemBook(AllocationSize);
  return Array;
}

/**
* You can write:
*   MyType * MyArray = CGMemAllocateAndInitialize<MyType>(NbElements, 0);
* instead of
*   MyType * MyArray = (MyType *)CATCGMemBook((size_t)(NbElements * sizeof(MyType)));
*   memset(MyArray, 0, NbElements * sizeof(MyType));
*/
template <class T>
T * CGMemAllocateAndInitialize(int iNbElem, T iFiller)
{
  T * Array = CGMemAllocate<T>(iNbElem);
  CGMemInitialize<T>(Array, iNbElem, iFiller);
  return Array;
}

/**
* Copies an array into a new one of a wanted dimension.
* A filler must be defined for empty slots.
*/
template <class T>
void CGMemReallocate(T *& ioArray, int iWantedArraySize, int iNbElementsToCopy, T iFiller)
{
  if (iWantedArraySize > iNbElementsToCopy)
  {
    T * OldArray = ioArray;

    ioArray = CGMemAllocate<T>(iWantedArraySize);

    T * CurrentOldElement = OldArray;
    T * CurrentNewElement = ioArray;
    T * FirstNonUsed = ioArray + iNbElementsToCopy;
    T * FirstNonAllocated = ioArray + iWantedArraySize;

    while (CurrentNewElement != FirstNonUsed)
    {
      (*CurrentNewElement) = (*CurrentOldElement);
      CurrentOldElement++;
      CurrentNewElement++;
    }

    while (CurrentNewElement != FirstNonAllocated)
    {
      (*CurrentNewElement) = iFiller;
      CurrentNewElement++;
    }

    CGMemDeallocate(OldArray);
  }
}

template <class T>
void CGMemDeleteAll(T ** ioArray, int iNbElem)
{
  T ** CurrentElement = ioArray;
  T ** LastPlus1 = ioArray + iNbElem;
  while (CurrentElement != LastPlus1)
  {
    T *& CurrentObject = (*CurrentElement);
    if (CurrentObject)
    {
      delete CurrentObject;
      CurrentObject = NULL;
    }
    CurrentElement++;
  }
}

#endif
