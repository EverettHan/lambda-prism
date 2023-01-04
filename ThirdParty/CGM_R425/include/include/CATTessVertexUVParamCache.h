// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexUVParamCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessVertexUVParamCache_H
#define TessVertexUVParamCache_H

#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessVertexUVParamCache
{

public:

  CATTessVertexUVParamCache (CATLONG32 iNbVertices);
  CATTessVertexUVParamCache (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessVertexUVParamCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetNbVertices () const;
  INLINE double* GetUVParamBuffer () const;

public:

  INLINE double* GetUVParamBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVertices);

protected:

  //CATLONG32 _NbVertices;
  //double* _UVParams;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessVertexUVParamCache::GetNbVertices () const
{
  //return _NbVertices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVertices();
	else
		return 0;
}

INLINE double* CATTessVertexUVParamCache::GetUVParamBuffer () const
{
  //return _UVParams;
	if (_PolyBuffers)
		return ((double*)_PolyBuffers->GetVertexUVBuffer());
	else
		return 0;
}

INLINE double* CATTessVertexUVParamCache::GetUVParamBuffer_ForUpdate ()
{
  //return _UVParams;
	if (_PolyBuffers)
		return (_PolyBuffers->GetVertexUVBuffer_ForUpdate());
	else
		return 0;
}

#endif
