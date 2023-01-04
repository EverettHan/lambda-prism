#ifndef CATCGMLISTP_Declare_h
#define CATCGMLISTP_Declare_h

#include "CATMathInline.h"
#include "CATCGMPointerList.h"

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

#define CATCGMLISTP_DECLARE_N(ClassName, PointeeTypeName)                              \
class ClassName                                                                         \
{                                                                                       \
public:                                                                                 \
  INLINE ClassName(int iInitAlloc = 0):                                                 \
    _content(iInitAlloc)                                                                \
  {}                                                                                    \
                                                                                        \
  INLINE ClassName(const ClassName& iCopy):                                             \
    _content(iCopy._content)                                                            \
  {}                                                                                    \
                                                                                        \
  INLINE ClassName(PointeeTypeName** iArray, int iSize):                                \
    _content((void**) iArray, iSize)                                                    \
  {}                                                                                    \
                                                                                        \
  /* NO DESTRUCTOR */                                                                   \
                                                                                        \
  INLINE ClassName& operator=(const ClassName& iCopy)                                   \
  {                                                                                     \
    _content = iCopy._content;                                                          \
    return *this;                                                                       \
  }                                                                                     \
                                                                                        \
public:                                                                                 \
  INLINE int Append(PointeeTypeName* iAdd)                                              \
  {                                                                                     \
    return _content.Append((void*) iAdd);                                               \
  }                                                                                     \
                                                                                        \
  INLINE int Append(const ClassName& iConcat)                                           \
  {                                                                                     \
    return _content.Append(iConcat._content);                                           \
  }                                                                                     \
                                                                                        \
  INLINE int InsertAt(int iPos, PointeeTypeName* iAdd)                                  \
  {                                                                                     \
    return _content.InsertAt(iPos, (void*) iAdd);                                       \
  }                                                                                     \
                                                                                        \
  INLINE int Size() const                                                               \
  {                                                                                     \
    return _content.Size();                                                             \
  }                                                                                     \
                                                                                        \
  INLINE void Size(int iSize)                                                           \
  {                                                                                     \
    _content.Size(iSize);                                                               \
  }                                                                                     \
                                                                                        \
  INLINE PointeeTypeName*& operator[] (int iPos)                                        \
  {                                                                                     \
    return (PointeeTypeName*&) _content[iPos];                                          \
  }                                                                                     \
                                                                                        \
  INLINE PointeeTypeName* operator[] (int iPos) const                                   \
  {                                                                                     \
    return (PointeeTypeName*) _content[iPos];                                           \
  }                                                                                     \
                                                                                        \
  INLINE int Locate(PointeeTypeName* iLocate, int iFrom = 1) const                      \
  {                                                                                     \
    return _content.Locate((void*) iLocate, iFrom);                                     \
  }                                                                                     \
                                                                                        \
  INLINE int RemoveValue(PointeeTypeName* iRemove)                                      \
  {                                                                                     \
    return _content.RemoveValue((void*) iRemove);                                       \
  }                                                                                     \
                                                                                        \
  INLINE int Remove(const ClassName& iSubtract)                                         \
  {                                                                                     \
    return _content.Remove(iSubtract._content);                                         \
  }                                                                                     \
                                                                                        \
  INLINE void RemovePosition(int iPos)                                                  \
  {                                                                                     \
    _content.RemovePosition(iPos);                                                      \
  }                                                                                     \
                                                                                        \
  INLINE int RemovePosition(int iIndex, unsigned int iNbElem)                           \
  {                                                                                     \
    return _content.RemovePosition(iIndex, iNbElem);                                    \
  }                                                                                     \
                                                                                        \
  INLINE void RemoveAll(CATCollec::MemoryHandling iMH = CATCollec::ReleaseAllocation)   \
  {                                                                                     \
    _content.RemoveAll(iMH);                                                            \
  }                                                                                     \
                                                                                        \
  INLINE int RemoveNulls()                                                              \
  {                                                                                     \
    return _content.RemoveNulls();                                                      \
  }                                                                                     \
                                                                                        \
  INLINE int RemoveDuplicates(ClassName* ioExtract = NULL)                              \
  {                                                                                     \
    return _content.RemoveDuplicates(ioExtract ? & ioExtract->_content : NULL);         \
  }                                                                                     \
                                                                                        \
  INLINE int operator==(const ClassName& iL) const                                      \
  {                                                                                     \
    return _content == iL._content;                                                     \
  }                                                                                     \
                                                                                        \
  INLINE int operator!=(const ClassName& iL) const                                      \
  {                                                                                     \
    return _content != iL._content;                                                     \
  }                                                                                     \
                                                                                        \
  INLINE static int Compare(const ClassName& iL1, const ClassName& iL2,                 \
                            int (*iPFCompare)(PointeeTypeName*, PointeeTypeName*))      \
  {                                                                                     \
    return CATCGMPointerList::Compare(iL1._content, iL2._content,                       \
                                      (int (*)(void*, void*)) iPFCompare);              \
  }                                                                                     \
                                                                                        \
  INLINE void Swap(int iPos1, int iPos2)                                                \
  {                                                                                     \
    _content.Swap(iPos1, iPos2);                                                        \
  }                                                                                     \
                                                                                        \
  INLINE void QuickSort(int (*iPFCompare)(PointeeTypeName*, PointeeTypeName*))          \
  {                                                                                     \
    _content.QuickSort((int (*)(void*, void*)) iPFCompare);                             \
  }                                                                                     \
                                                                                        \
  INLINE void FillArray(PointeeTypeName** ioArray, int iMaxSize) const                  \
  {                                                                                     \
    _content.FillArray((void**) ioArray, iMaxSize);                                     \
  }                                                                                     \
                                                                                        \
  INLINE int NbOccur(PointeeTypeName* iTest)                                            \
  {                                                                                     \
    return _content.NbOccur(iTest);                                                     \
  }                                                                                     \
                                                                                        \
  INLINE static void Intersection(const ClassName& iL1, const ClassName& iL2,           \
                                  ClassName& ioResult)                                  \
  {                                                                                     \
    CATCGMPointerList::Intersection(iL1._content, iL2._content, ioResult._content);     \
  }                                                                                     \
                                                                                        \
private:                                                                                \
  CATCGMPointerList _content;                                                           \
}

#define CATCGMLISTP_DECLARE(PointeeTypeName) CATCGMLISTP_DECLARE_N(CATListPtr##PointeeTypeName, PointeeTypeName)

#endif
