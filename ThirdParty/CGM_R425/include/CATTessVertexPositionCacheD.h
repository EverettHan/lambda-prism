// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexPositionCacheD.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessVertexPositionCacheD_H
#define TessVertexPositionCacheD_H

#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessVertexPositionCacheD
{

public:

  CATTessVertexPositionCacheD (CATLONG32 iNbVertices);
  CATTessVertexPositionCacheD (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessVertexPositionCacheD ();

public:

  // Vertices.
  INLINE CATLONG32 GetNbVertices () const;
  INLINE double* GetVertexCoordinatesBuffer () const;

public:

  INLINE double* GetVertexCoordinatesBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVertices);

protected:

  //CATLONG32 _NbVertices;
  //double* _VertexCoordinates;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessVertexPositionCacheD::GetNbVertices () const
{
  //return _NbVertices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVertices();
	else
		return 0;
}

INLINE double* CATTessVertexPositionCacheD::GetVertexCoordinatesBuffer () const
{
  //return _VertexCoordinates;
	if (_PolyBuffers)
		return ((double*)_PolyBuffers->GetVertexCoordinatesBufferDouble());
	else
		return 0;
}

INLINE double* CATTessVertexPositionCacheD::GetVertexCoordinatesBuffer_ForUpdate ()
{
  //return _VertexCoordinates;
	if (_PolyBuffers)
		return (_PolyBuffers->GetVertexCoordinatesBufferDouble_ForUpdate());
	else
		return 0;
}


#endif
