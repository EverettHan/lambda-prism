// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexWParamCache.h
//
//===================================================================
//
// Aug 2009  Creation: MPX
//===================================================================
#ifndef TessVertexWParamCache_H
#define TessVertexWParamCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessVertexWParamCache
{

public:

  CATTessVertexWParamCache (CATLONG32 iNbVertices);
	CATTessVertexWParamCache (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessVertexWParamCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetNbVertices () const;
  INLINE const double* GetWParamBuffer () const;

public:

  INLINE double* GetWParamBuffer_ForUpdate ();

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVertices);

protected:

  //CATLONG32 _NbVertices;
  //double* _WParams;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessVertexWParamCache::GetNbVertices () const
{
  //return _NbVertices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVertices();
	else
		return 0;
}

INLINE const double* CATTessVertexWParamCache::GetWParamBuffer () const
{
  //return _WParams;
	if (_PolyBuffers)
		return ((double*)_PolyBuffers->GetVertexWBuffer());
	else
		return 0;
}

INLINE double* CATTessVertexWParamCache::GetWParamBuffer_ForUpdate ()
{
  //return _WParams;
	if (_PolyBuffers)
		return (_PolyBuffers->GetVertexWBuffer_ForUpdate());
	else
		return 0;
}

#endif
