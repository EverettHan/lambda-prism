#ifndef CATCGMLISTPP_Declare_h
#define CATCGMLISTPP_Declare_h

/**
* @COPYRIGHT DASSAULT SYSTEMES 2019
*/
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************

#include "CATMathInline.h"
#include "CATCGMPointerPList.h"

// Declare & define a list of pointers to PointeeTypeName. This macro
// generates a simple wrapper responsible of "safely" casting void*
// pointers. It is built atop a list of void*.
//
// Following facts are VOLUNTARY, and should NOT BE MODIFIED:
//
// - classes are NOT EXPORTED AT ALL: all their methods are forced to be
// inlined;
//
// - there are no virtual methods, and particularly NO VIRTUAL DESTRUCTOR: the
// underlying list is destructed because it is COMPOSED (as opposed to
// inherited)
//

#define CATCGMLISTPP_DECLARE_N(ClassName, PointeeTypeName)              \
class ClassName                                                         \
{                                                                       \
public:                                                                 \
  INLINE ClassName(int iInitAlloc = 0):                                 \
    _content(iInitAlloc)                                                \
  {}                                                                    \
                                                                        \
  INLINE ClassName(const ClassName& iCopy):                             \
    _content(iCopy._content)                                            \
  {}                                                                    \
                                                                        \
  INLINE ClassName(PointeeTypeName** iArray, int iSize):                \
    _content((void**) iArray, iSize)                                    \
  {}                                                                    \
                                                                        \
  /* DEFAULT DESTRUCTOR IS JUST FINE */                                 \
                                                                        \
  INLINE ClassName& operator=(const ClassName& iCopy)                   \
  {                                                                     \
    _content = iCopy._content;                                          \
    return *this;                                                       \
  }                                                                     \
                                                                        \
public:                                                                 \
  INLINE void Append(PointeeTypeName* iAdd)                             \
  {                                                                     \
    _content.Append((void*) iAdd);                                      \
  }                                                                     \
                                                                        \
  INLINE void Append(const ClassName& iConcat)                          \
  {                                                                     \
    _content.Append(iConcat._content);                                  \
  }                                                                     \
                                                                        \
  INLINE void InsertAt(int iPos, PointeeTypeName* iAdd)                 \
  {                                                                     \
    _content.InsertAt(iPos, (void*) iAdd);                              \
  }                                                                     \
                                                                        \
  INLINE int Size() const                                               \
  {                                                                     \
    return _content.Size();                                             \
  }                                                                     \
                                                                        \
  INLINE void Size(int iSize)                                           \
  {                                                                     \
    _content.Size(iSize);                                               \
  }                                                                     \
                                                                        \
  INLINE PointeeTypeName** Storage() const                              \
  {                                                                     \
    return (PointeeTypeName**) _content.Storage();                      \
  }                                                                     \
                                                                        \
  INLINE PointeeTypeName*& operator[] (int iPos)                        \
  {                                                                     \
    return (PointeeTypeName*&) _content[iPos];                          \
  }                                                                     \
                                                                        \
  INLINE PointeeTypeName* operator[] (int iPos) const                   \
  {                                                                     \
    return (PointeeTypeName*) _content[iPos];                           \
  }                                                                     \
                                                                        \
  INLINE int Locate(PointeeTypeName* iLocate, int iFrom = 1) const      \
  {                                                                     \
    return _content.Locate((void*) iLocate, iFrom);                     \
  }                                                                     \
                                                                        \
  INLINE int RemoveValue(PointeeTypeName* iRemove)                      \
  {                                                                     \
    return _content.RemoveValue((void*) iRemove);                       \
  }                                                                     \
                                                                        \
  INLINE int Remove(const ClassName& iSubtract)                         \
  {                                                                     \
    return _content.Remove(iSubtract._content);                         \
  }                                                                     \
                                                                        \
  INLINE void RemovePosition(int iPos)                                  \
  {                                                                     \
    _content.RemovePosition(iPos);                                      \
  }                                                                     \
                                                                        \
  INLINE void RemoveAll(CATCollec::MemoryHandling iMH = CATCollec::ReleaseAllocation) \
  {                                                                     \
    _content.RemoveAll(iMH);                                            \
  }                                                                     \
                                                                        \
  INLINE int RemoveNulls()                                              \
  {                                                                     \
    return _content.RemoveNulls();                                      \
  }                                                                     \
                                                                        \
  INLINE int RemoveDuplicates(ClassName* ioExtract = NULL)              \
  {                                                                     \
    return _content.RemoveDuplicates(ioExtract ? & ioExtract->_content : NULL); \
  }                                                                     \
                                                                        \
  INLINE int operator==(const ClassName& iL) const                      \
  {                                                                     \
    return _content == iL._content;                                     \
  }                                                                     \
                                                                        \
  INLINE int operator!=(const ClassName& iL) const                      \
  {                                                                     \
    return _content != iL._content;                                     \
  }                                                                     \
                                                                        \
  INLINE static int Compare(const ClassName& iL1, const ClassName& iL2, \
                            int (*iPFCompare)(PointeeTypeName*, PointeeTypeName*)) \
  {                                                                     \
    return CATCGMPointerPList::Compare(iL1._content, iL2._content,      \
                                       (int (*)(void*, void*)) iPFCompare); \
  }                                                                     \
                                                                        \
  INLINE void Swap(int iPos1, int iPos2)                                \
  {                                                                     \
    _content.Swap(iPos1, iPos2);                                        \
  }                                                                     \
                                                                        \
  INLINE void QuickSort(int (*iPFCompare)(PointeeTypeName*, PointeeTypeName*)) \
  {                                                                     \
    _content.QuickSort((int (*)(void*, void*)) iPFCompare);             \
  }                                                                     \
                                                                        \
  INLINE void FillArray(PointeeTypeName** ioArray, int iMaxSize) const  \
  {                                                                     \
    _content.FillArray((void**) ioArray, iMaxSize);                     \
  }                                                                     \
                                                                        \
  INLINE int NbOccur(PointeeTypeName* iTest)                            \
  {                                                                     \
    return _content.NbOccur(iTest);                                     \
  }                                                                     \
                                                                        \
  INLINE static void Intersection(const ClassName& iL1, const ClassName& iL2, \
                                  ClassName& ioResult)                  \
  {                                                                     \
    CATCGMPointerPList::Intersection(iL1._content, iL2._content, ioResult._content); \
  }                                                                     \
                                                                        \
 private:                                                               \
  CATCGMPointerPList _content;                                          \
}

#define CATCGMLISTPP_DECLARE(PointeeTypeName) CATCGMLISTPP_DECLARE_N(CATListPtr##PointeeTypeName, PointeeTypeName)

#endif
