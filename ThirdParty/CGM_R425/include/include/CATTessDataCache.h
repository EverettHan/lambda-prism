// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessDataCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessDataCache_H
#define TessDataCache_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessDataCache  
{
public:

  // A Note on Ref-Counting:
  //
  //    Although, AddRef() and Release() are technically non-const methods, yet from the point 
  //    of view of "const-correctness" they have been tactically declared as const.
  //    This is because functionally, these method do not really change any data of the class.
  //    Yes, the ref-count is modifed, but its just meant for memory-management.
  //    If a client just wants to refer to the data (without changing it), it would like 
  //    keep a const reference to the data and would still like be able to an AddRef() and
  //    Release() on it.
  
  // Increments the reference count
  void AddRef() const;

  //Decrements the reference count 
  void Release() const;

  INLINE CATUINT32 RefCount() const;

  // Warning : for CATTessCacheAccess internal use only
  // Tag is used to identify the cache
  INLINE void SetTag(CATULONG32 iTag) const;
  INLINE CATULONG32 GetTag() const;

public:

  virtual void Stream(CATCGMStream& iStream) const = 0;
  virtual void UnStream(CATCGMStream& iStream) = 0;

protected:

  INLINE CATTessDataCache ();
  virtual ~CATTessDataCache ();

private:

  CATUINT32 _RefCount;
  CATULONG32 _Tag;

};


INLINE 
CATTessDataCache::CATTessDataCache () 
:_RefCount (1),_Tag(0)
{
}

INLINE CATUINT32 
CATTessDataCache::RefCount() const
{
  return _RefCount;
}

INLINE void 
CATTessDataCache::SetTag(CATULONG32 iTag) const
{
  // "const-correctness" tactic
  CATTessDataCache* This = (CATTessDataCache*)this;
  This->_Tag = iTag;
}

INLINE CATULONG32 
CATTessDataCache::GetTag() const
{
  return _Tag;
}

#endif // !TessDataCache_H
