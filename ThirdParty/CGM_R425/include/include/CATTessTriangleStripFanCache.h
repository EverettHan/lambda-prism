// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessTriangleStripFanCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessTriangleStripFanCache_H
#define TessTriangleStripFanCache_H

#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATMathInline.h"
#include "CATMathPolyBuffers.h"

class CATCGMStream;

class ExportedByTessCacheObjects CATTessTriangleStripFanCache
{

public:

  CATTessTriangleStripFanCache (CATLONG32 iNbIsolatedTriangles,
                             CATLONG32 iNbStrips, CATLONG32 iNbStripIndices,
                             CATLONG32 iNbFans, CATLONG32 iNbFanIndices);
	CATTessTriangleStripFanCache (CATMathPolyBuffers & iPolyBuffers);

  ~CATTessTriangleStripFanCache ();

public:

  // Isolated triangles.
  INLINE CATLONG32 GetNbIsolatedTriangles () const;
  INLINE CATLONG32* GetIsolatedTriangleBuffer () const;

  // Strips.
  INLINE CATLONG32 GetNbStrips () const;
  INLINE CATLONG32 GetNbStripIndices () const;
  INLINE CATLONG32* GetStripIndicesBuffer () const;
  INLINE CATLONG32* GetNbVerticesPerStripBuffer () const;

  // Fans.
  INLINE CATLONG32 GetNbFans () const;
  INLINE CATLONG32 GetNbFanIndices () const;
  INLINE CATLONG32* GetFanIndicesBuffer () const;
  INLINE CATLONG32* GetNbVerticesPerFanBuffer () const;

  INLINE CATSide GetSide () const;
  INLINE CATBoolean IsPlane () const;

public:

  // Return the total number of strip triangles.
  CATLONG32 ComputeNbStripTriangles () const;

  // Return the total number of fan triangles.
  CATLONG32 ComputeNbFanTriangles () const;

  // Return the total number of triangles.
  INLINE CATLONG32 GetNbTriangles () const;

public:

  INLINE CATLONG32* GetIsolatedTriangleBuffer_ForUpdate ();

  INLINE CATLONG32* GetStripIndicesBuffer_ForUpdate ();
  INLINE CATLONG32* GetNbVerticesPerStripBuffer_ForUpdate ();

  INLINE CATLONG32* GetFanIndicesBuffer_ForUpdate ();
  INLINE CATLONG32* GetNbVerticesPerFanBuffer_ForUpdate ();

  INLINE void SetSide (CATSide iSide);
  INLINE void SetIsPlane (CATBoolean iIsPlane);

public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbIsolatedTriangles,
                  CATLONG32 iNbStrips, CATLONG32 iNbStripIndices,
                  CATLONG32 iNbFans, CATLONG32 iNbFanIndices);

protected:

  //CATLONG32 _NbIsolatedTriangles;
  //CATLONG32* _IsolatedTriangles;


  //CATLONG32 _NbStrips;
  //CATLONG32 _NbStripIndices;
  //CATLONG32* _StripIndices;
  //CATLONG32* _NbVerticesPerStrip;

  //CATLONG32 _NbFans;
  //CATLONG32 _NbFanIndices;
  //CATLONG32* _FanIndices;
  //CATLONG32* _NbVerticesPerFan;

  //CATSide _Side;
  CATBoolean _IsPlane;

	CATMathPolyBuffers * _PolyBuffers;
};


INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbIsolatedTriangles () const
{
  //return _NbIsolatedTriangles;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbIsolatedTriangles();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetIsolatedTriangleBuffer () const
{
  //return _IsolatedTriangles;
	if (_PolyBuffers)
		return (CATLONG32*)_PolyBuffers->GetIsolatedTriangleBuffer();
	else
		return 0;
}

INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbStrips () const
{
  //return _NbStrips;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbStrips();
	else
		return 0;
}

INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbStripIndices () const
{
  //return _NbStripIndices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbStripIndices();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetStripIndicesBuffer () const
{
  //return _StripIndices;
	if (_PolyBuffers)
		return (CATLONG32*)_PolyBuffers->GetStripIndicesBuffer();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetNbVerticesPerStripBuffer () const
{
  //return _NbVerticesPerStrip;
	if (_PolyBuffers)
		return (CATLONG32*)_PolyBuffers->GetNbVerticesPerStripBuffer();
	else
		return 0;
}

INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbFans () const
{
  //return _NbFans;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbFans();
	else
		return 0;
}

INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbFanIndices () const
{
  //return _NbFanIndices;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbFanIndices();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetFanIndicesBuffer () const
{
  //return _FanIndices;
	if (_PolyBuffers)
		return (CATLONG32*)_PolyBuffers->GetFanIndicesBuffer();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetNbVerticesPerFanBuffer () const
{
  //return _NbVerticesPerFan;
	if (_PolyBuffers)
		return (CATLONG32*)_PolyBuffers->GetNbVerticesPerFanBuffer();
	else
		return 0;
}

INLINE CATLONG32 CATTessTriangleStripFanCache::GetNbTriangles () const
{
  //return GetNbIsolatedTriangles () + ComputeNbStripTriangles () + ComputeNbFanTriangles ();
	if (_PolyBuffers)
		return _PolyBuffers->GetNbTriangles();
	else
		return 0;
}

INLINE CATSide CATTessTriangleStripFanCache::GetSide () const
{
  //return _Side;
	if (_PolyBuffers)
		return _PolyBuffers->GetSide();
	else
		return 0;
}

INLINE CATBoolean CATTessTriangleStripFanCache::IsPlane () const
{
  return _IsPlane;
}


INLINE CATLONG32* CATTessTriangleStripFanCache::GetIsolatedTriangleBuffer_ForUpdate ()
{
  //return _IsolatedTriangles;
	if (_PolyBuffers)
		return _PolyBuffers->GetIsolatedTriangleBuffer_ForUpdate();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetStripIndicesBuffer_ForUpdate ()
{
  //return _StripIndices;
	if (_PolyBuffers)
		return _PolyBuffers->GetStripIndicesBuffer_ForUpdate();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetNbVerticesPerStripBuffer_ForUpdate ()
{
  //return _NbVerticesPerStrip;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVerticesPerStripBuffer_ForUpdate();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetFanIndicesBuffer_ForUpdate ()
{
  //return _FanIndices;
	if (_PolyBuffers)
		return _PolyBuffers->GetFanIndicesBuffer_ForUpdate();
	else
		return 0;
}

INLINE CATLONG32* CATTessTriangleStripFanCache::GetNbVerticesPerFanBuffer_ForUpdate ()
{
  //return _NbVerticesPerFan;
	if (_PolyBuffers)
		return _PolyBuffers->GetNbVerticesPerFanBuffer_ForUpdate();
	else
		return 0;
}

INLINE void CATTessTriangleStripFanCache::SetSide (CATSide iSide)
{
  //_Side = iSide;
	if (_PolyBuffers)
		_PolyBuffers->SetSide(iSide);
}

INLINE void CATTessTriangleStripFanCache::SetIsPlane (CATBoolean iIsPlane)
{
  _IsPlane = iIsPlane;
}


#endif
