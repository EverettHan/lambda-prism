// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexPositionCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessVertexPositionCache_H
#define TessVertexPositionCache_H

#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessVertexPositionCache
{

public:

  CATTessVertexPositionCache (CATLONG32 iNbVertices);
  CATTessVertexPositionCache (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessVertexPositionCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetNbVertices () const;
  INLINE float* GetVertexCoordinatesBuffer () const;

public:

  INLINE float* GetVertexCoordinatesBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVertices);

protected:

  //CATLONG32 _NbVertices;
  //float* _VertexCoordinates;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessVertexPositionCache::GetNbVertices () const
{
  //return _NbVertices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVertices();
	else
		return 0;
}

INLINE float* CATTessVertexPositionCache::GetVertexCoordinatesBuffer () const
{
  //return _VertexCoordinates;
	if (_PolyBuffers)
		return ((float*)_PolyBuffers->GetVertexCoordinatesBuffer());
	else
		return 0;
}

INLINE float* CATTessVertexPositionCache::GetVertexCoordinatesBuffer_ForUpdate ()
{
  //return _VertexCoordinates;
	if (_PolyBuffers)
		return (_PolyBuffers->GetVertexCoordinatesBuffer_ForUpdate());
	else
		return 0;
}


#endif
