// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessSubdivision2DCache.h
//
//===================================================================
//
// Nov 2011  Creation: ZFI
//===================================================================

#ifndef CATTessSubdivision2DCache_H
#define CATTessSubdivision2DCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessSubdivision2DCache
{

public:

  CATTessSubdivision2DCache (CATLONG32 iHSubdivisionBufferSize, CATLONG32 iVSubdivisionBufferSize);
  ~CATTessSubdivision2DCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetHBufferSize () const;
  INLINE CATLONG32 GetVBufferSize () const;
  INLINE const unsigned char* GetHSubdivisionBuffer () const;
  INLINE const unsigned char* GetVSubdivisionBuffer () const;

public:

  INLINE unsigned char* GetHSubdivisionBuffer_ForUpdate ();
  INLINE unsigned char* GetVSubdivisionBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iHSubdivisionBufferSize, CATLONG32 iVSubdivisionBufferSize);

protected:

  CATLONG32 _HSubdivisionBufferSize;
  CATLONG32 _VSubdivisionBufferSize;
  
  unsigned char* _HSubdivisionBuffer;
  unsigned char* _VSubdivisionBuffer;

};


INLINE CATLONG32 CATTessSubdivision2DCache::GetHBufferSize () const
{
  return _HSubdivisionBufferSize;
}

INLINE CATLONG32 CATTessSubdivision2DCache::GetVBufferSize () const
{
  return _VSubdivisionBufferSize;
}

INLINE const unsigned char* CATTessSubdivision2DCache::GetHSubdivisionBuffer () const
{
  return _HSubdivisionBuffer;
}

INLINE const unsigned char* CATTessSubdivision2DCache::GetVSubdivisionBuffer () const
{
  return _VSubdivisionBuffer;
}

INLINE unsigned char* CATTessSubdivision2DCache::GetHSubdivisionBuffer_ForUpdate ()
{
  return _HSubdivisionBuffer;
}

INLINE unsigned char* CATTessSubdivision2DCache::GetVSubdivisionBuffer_ForUpdate ()
{
  return _VSubdivisionBuffer;
}
#endif
