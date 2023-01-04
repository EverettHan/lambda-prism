//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Generic (macro-based) buckets-based vector.
//
// Remark that the implementation uses direct OS memory allocation, and does
// not rely on another, conflicting layer of software memory handling (e.g. a
// memory pool). The malloc/free pair is prefered to new/delete because its
// behavior is more stable across environment (most notably when memory gets
// exhausted).
//
//=============================================================================
// 2007-02-16   BPG: New
//=============================================================================
#ifndef CATPolyBuckets_T_H
#define CATPolyBuckets_T_H

#include <stdlib.h>
#include <string.h>

#include "CATBoolean.h"
#include "CATErrorDef.h"

// <<
#undef nested
#define nested

// We need to remove nested but it fail to compile this fw out of cgm release
// MachinistAlgosWTT\ProtectedInterfaces\CATPolygonVertex3DPositionLayerImpl.h(46): error C2143: syntax error: missing ';' before '<class-head>'
// MachinistAlgosWTT\ProtectedInterfaces\CATPolygonVertex3DPositionLayerImpl.h(46): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int

// >>

//
#define Specialize_CATPolyBuckets_T(Typename, ValueTypename)            \
                                                                        \
Typename                                                                \
{                                                                       \
public:                                                                 \
  typedef ValueTypename ValueType;                                      \
                                                                        \
public:                                                                 \
  Typename():                                                           \
    _NbRegions(0),                                                      \
    _Regions(0),                                                        \
    _NbItems(0)                                                         \
  {}                                                                    \
                                                                        \
  ~Typename()                                                           \
  {                                                                     \
    Clear(FALSE);                                                       \
  }                                                                     \
                                                                        \
  /* Typename(const Typename &iRHS); */                                 \
  /* Typename &operator=(const Typename &iRHS); */                      \
                                                                        \
public:                                                                 \
  /** (Explicit) */                                                     \
  inline unsigned int Size() const                                      \
  {                                                                     \
    return _NbItems;                                                    \
  }                                                                     \
                                                                        \
  /** (Explicit) */                                                     \
  inline CATBoolean Empty() const                                       \
  {                                                                     \
    return _NbItems == 0;                                               \
  }                                                                     \
                                                                        \
public:                                                                 \
  /** Access element i (read-only). */                                  \
  /** WARNING: Assume that `i' is a valid index */                      \
  inline const ValueType &operator[] (unsigned int i) const             \
  {                                                                     \
    const unsigned int r = RegionNum(i);                                \
    const unsigned int c = CellNum(i);                                  \
    return _Regions[r][c];                                              \
  }                                                                     \
                                                                        \
  /** Access element i (read-only). */                                  \
  /** `i' is checked for correctness */                                 \
  inline HRESULT Get(unsigned int i, ValueType &v) const                \
  {                                                                     \
    if (i < 1 || _NbItems < i) return E_FAIL;                           \
    const unsigned int r = RegionNum(i);                                \
    const unsigned int c = CellNum(i);                                  \
    if (!_Regions[r]) return E_FAIL;                                    \
    v = _Regions[r][c];                                                 \
    return S_OK;                                                        \
  }                                                                     \
                                                                        \
  /** Access element i (read-write). */                                 \
  /** WARNING: Assume that `i' is a valid index */                      \
  inline ValueType &operator[] (unsigned int i)                         \
  {                                                                     \
    const unsigned int r = RegionNum(i);                                \
    const unsigned int c = CellNum(i);                                  \
    return _Regions[r][c];                                              \
  }                                                                     \
                                                                        \
  /** Access element i (read-write). */                                 \
  /** `i' is checked for correctness */                                 \
  inline HRESULT Set(unsigned int i, const ValueType &v) const          \
  {                                                                     \
    if (i < 1 || _NbItems < i) return E_FAIL;                           \
    const unsigned int r = RegionNum(i);                                \
    const unsigned int c = CellNum(i);                                  \
    if (!_Regions[r]) return E_FAIL;                                    \
    _Regions[r][c] = v;                                                 \
    return S_OK;                                                        \
  }                                                                     \
                                                                        \
public:                                                                 \
  /** Insert a new element at the end. Return the index of the said new */ \
  /** element, or 0 if a problem was encountered (e.g. memory exhausted) */ \
  unsigned int PushBack(const ValueType &v);                            \
                                                                        \
public:                                                                 \
  inline unsigned int Capacity() const                                  \
  {                                                                     \
    return _Regions ? _NbRegions : 0;                                   \
  }                                                                     \
                                                                        \
  HRESULT Resize(unsigned int n);                                       \
                                                                        \
  HRESULT Clear(CATBoolean iKeepAllocatedMemory = FALSE);               \
                                                                        \
private:                                                                \
  HRESULT Grow();                                                       \
                                                                        \
private:                                                                \
  inline unsigned int RegionNum(unsigned int i) const                   \
  {                                                                     \
    return (i - 1) >> _Shift;                                           \
  }                                                                     \
                                                                        \
  inline unsigned int CellNum(unsigned int i) const                     \
  {                                                                     \
    return (i - 1) & _Mask;                                             \
  }                                                                     \
                                                                        \
private:                                                                \
  static unsigned int Log2(unsigned int i);                             \
                                                                        \
  /* Compile-time constants (only dependant upon size of value type) */ \
private:                                                                \
  static const unsigned int _NbItemsByRegion;                           \
  static const unsigned int _Shift;                                     \
  static const unsigned int _Mask;                                      \
                                                                        \
  /* Actual buckets */                                                  \
private:                                                                \
  unsigned int _NbRegions;                                              \
  ValueType **_Regions;                                                 \
                                                                        \
  /* Tail */                                                            \
private:                                                                \
  unsigned int _NbItems;                                                \
}

// ----------------------------------------------------------------------------

// template<unsigned int n>
// struct Log2
// {
//   enum { res = Log2< (n >> 1) >::res + 1 };
// };
//
// template<>
// struct Log2<1>
// {
//   enum { res = 0 };
// };
//
// template<>
// struct Log2<0>
// {
// };

#define Implement_Specialized_CATPolyBuckets_T(Typename)		\
unsigned int Typename::Log2(unsigned int i)                             \
{                                                                       \
  unsigned int r = 0;                                                   \
  while (i >>= 1)                                                       \
    ++r;                                                                \
  return r;                                                             \
}                                                                       \
                                                                        \
/* Compile-time constants */                                            \
                                                                        \
const unsigned int Typename::_Shift = /* Log2(RegionSize) */            \
  Log2(1024 < sizeof (Typename::ValueType) ?                            \
       sizeof (Typename::ValueType) :                                   \
       1024 / sizeof (Typename::ValueType));                            \
                                                                        \
const unsigned int Typename::_Mask = /* (1 << _Shift) - 1 */            \
  (1 << Log2(1024 < sizeof (Typename::ValueType) ?                      \
             sizeof (Typename::ValueType) :                             \
             1024 / sizeof (Typename::ValueType))) - 1;                 \
                                                                        \
const unsigned int Typename::_NbItemsByRegion = /* 1 << _Shift */       \
  1 << Log2(1024 < sizeof (Typename::ValueType) ?                       \
            sizeof (Typename::ValueType) :                              \
            1024 / sizeof (Typename::ValueType));                       \
                                                                        \
/* */                                                                   \
                                                                        \
unsigned int                                                            \
Typename::PushBack(const ValueType &v)                                  \
{                                                                       \
  const unsigned int i = _NbItems + 1;                                  \
                                                                        \
  const unsigned int r = RegionNum(i);                                  \
  const unsigned int c = CellNum(i);                                    \
                                                                        \
  if (_NbRegions <= r)                                                  \
    /* Grow root array */                                               \
    if (FAILED(Grow()) || _NbRegions <= r) return 0;                    \
                                                                        \
  if (!_Regions[r])                                                     \
  {                                                                     \
    /* Grow sub-array */                                                \
    _Regions[r] = new ValueType[_NbItemsByRegion];                      \
    if (!_Regions[r]) return 0;                                         \
  }                                                                     \
                                                                        \
  _Regions[r][c] = v;                                                   \
  return ++_NbItems;                                                    \
}                                                                       \
                                                                        \
/* */                                                                   \
                                                                        \
HRESULT                                                                 \
Typename::Grow()                                                        \
{                                                                       \
  if (_Regions)                                                         \
    /* Grow existing */                                                 \
  {                                                                     \
    const unsigned int NewNbRegions = _NbRegions * 2;                   \
                                                                        \
    ValueType **NewRegions = new ValueType *[NewNbRegions];             \
    if (!NewRegions) return E_OUTOFMEMORY;                              \
                                                                        \
    memcpy(NewRegions, _Regions, _NbRegions * sizeof (ValueType *));    \
    /* Tricky: NewNbRegions - _NbRegions == _NbRegions */               \
    memset(NewRegions + _NbRegions, 0, _NbRegions * sizeof (ValueType *)); \
    delete [] _Regions;                                                 \
    _Regions = NewRegions;                                              \
    _NbRegions = NewNbRegions;                                          \
  }                                                                     \
  else                                                                  \
    /* First allocation */                                              \
  {                                                                     \
    _NbRegions = 2;                                                     \
    _Regions = new ValueType *[_NbRegions];                             \
    if (!_Regions) return E_OUTOFMEMORY;                                \
                                                                        \
    memset(_Regions, 0, _NbRegions * sizeof (ValueType *));             \
  }                                                                     \
                                                                        \
  return S_OK;                                                          \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::Resize(unsigned int n)                                        \
{                                                                       \
  if (n < _NbItems)                                                     \
  {                                                                     \
    const unsigned int NewNbRegions = (0 < n) ? (RegionNum(n) + 1) : 0; \
    if (NewNbRegions < _NbRegions)                                      \
      /* Root array must be resized */                                  \
    {                                                                   \
      /* Kill regions that are beyond future limit */                   \
      while (NewNbRegions < _NbRegions)                                 \
      {                                                                 \
        --_NbRegions;                                                   \
        if (_Regions[_NbRegions])                                       \
        {                                                               \
          delete [] _Regions[_NbRegions];                               \
          _Regions[_NbRegions] = 0;                                     \
        }                                                               \
      }                                                                 \
      /* At this point, NewNbRegions == _NbRegions */                   \
                                                                        \
      /* Resize region pointer array: */                                \
      ValueType **NewRegions = 0;                                       \
      if (0 < NewNbRegions)                                             \
      {                                                                 \
        /* - build new one, copy, */                                    \
        NewRegions = new ValueType *[NewNbRegions];                     \
        memcpy(NewRegions, _Regions, _NbRegions * sizeof (ValueType *)); \
      }                                                                 \
                                                                        \
      /* - kill old one and reassign. */                                \
      delete [] _Regions;                                               \
      _Regions = NewRegions;                                            \
    }                                                                   \
                                                                        \
    /* FIXME: Reset data beyond specified limit in the last sub-array? */ \
                                                                        \
    _NbItems = n;                                                       \
  }                                                                     \
  /* FIXME: else Reserve() */                                           \
  return S_OK;                                                          \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::Clear(CATBoolean iKeepAllocatedMemory)                        \
{                                                                       \
  return Resize(0);                                                     \
}

#endif // !CATPolyBuckets_T_H
