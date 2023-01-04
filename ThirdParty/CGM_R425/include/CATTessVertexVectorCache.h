// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexVectorCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessVertexVectorCache_H
#define TessVertexVectorCache_H

#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessVertexVectorCache
{

public:

  CATTessVertexVectorCache (CATLONG32 iNbVectors);
  CATTessVertexVectorCache (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessVertexVectorCache ();

public:

  INLINE CATLONG32 GetNbVectors () const;
  INLINE float* GetVectorComponentsBuffer () const;

public:

  INLINE float* GetVectorComponentsBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVectors);

protected:

  //CATLONG32 _NbVectors;
  //float* _VectorComponents;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessVertexVectorCache::GetNbVectors () const
{
  //return _NbVectors;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVectors();
	else
		return 0;
}

INLINE float* CATTessVertexVectorCache::GetVectorComponentsBuffer () const
{
  //return _VectorComponents;
	if (_PolyBuffers)
		return ((float*)_PolyBuffers->GetVertexVectorBuffer());
	else
		return 0;
}

INLINE float* CATTessVertexVectorCache::GetVectorComponentsBuffer_ForUpdate ()
{
  //return _VectorComponents;
	if (_PolyBuffers)
		return (_PolyBuffers->GetVertexVectorBuffer_ForUpdate());
	else
		return 0;
}

#endif
