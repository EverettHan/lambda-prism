// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessSubdivision1DCache.h
//
//===================================================================
//
// Nov 2011  Creation: ZFI
//===================================================================

#ifndef CATTessSubdivision1DCache_H
#define CATTessSubdivision1DCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessSubdivision1DCache
{

public:

  CATTessSubdivision1DCache (CATLONG32 iSubdivisionBufferSize);
  ~CATTessSubdivision1DCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetBufferSize () const;
  INLINE const unsigned char* GetSubdivisionBuffer () const;
  
  //Sens
  INLINE CATBoolean GetSameSens () const;
  INLINE void SetSameSens(CATBoolean iSameSens);

public:

  INLINE unsigned char* GetSubdivisionBuffer_ForUpdate ();
  

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iSubdivisionBufferSize);

protected:

  CATLONG32 _SubdivisionBufferSize;
  unsigned char* _SubdivisionBuffer;
  CATBoolean _SameSens;

};


INLINE CATLONG32 CATTessSubdivision1DCache::GetBufferSize () const
{
  return _SubdivisionBufferSize;
}

INLINE const unsigned char* CATTessSubdivision1DCache::GetSubdivisionBuffer () const
{
  return _SubdivisionBuffer;
}

INLINE unsigned char* CATTessSubdivision1DCache::GetSubdivisionBuffer_ForUpdate ()
{
  return _SubdivisionBuffer;
}

INLINE CATBoolean CATTessSubdivision1DCache::GetSameSens () const
{
  return _SameSens;
}

INLINE void CATTessSubdivision1DCache::SetSameSens (CATBoolean iSameSens) 
{
  _SameSens=iSameSens;
}
#endif
