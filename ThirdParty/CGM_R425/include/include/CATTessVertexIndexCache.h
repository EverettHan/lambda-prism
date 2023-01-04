// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessVertexIndexCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessVertexIndexCache_H
#define TessVertexIndexCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCGMStream;
class CATTessSubdivision1DCache;

class ExportedByTessCacheObjects CATTessVertexIndexCache
{

public:

  CATTessVertexIndexCache (CATLONG32 iNbVertices, CATBoolean iSameSens);

  ~CATTessVertexIndexCache ();

public:

  // Vertices.
  INLINE CATLONG32 GetNbVertices () const;
  INLINE CATLONG32* GetVertexIndexBuffer () const;

  // Refer CATTessEdgeIter::GetEdgeW() for documentation
  INLINE double* GetCrvParamBuffer () const;
  INLINE short* GetQualPtsBuffer () const;
  
  // Refer CATTessEdgeIter::GetSameSens() for documentation
  INLINE CATBoolean GetSameSens () const;
  
  /*
   * Allocate memory to store the vertex subdivision parameters (compact form of parameters)
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   * Compressed param Cache
   */
  CATTessSubdivision1DCache* NewVertexSubdivisionCache (unsigned int iSubdivisionBufferSize);

public:

  INLINE CATLONG32* GetVertexIndexBuffer_ForUpdate ();
  INLINE double* GetCrvParamBuffer_ForUpdate ();
  INLINE short* GetQualPtsBuffer_ForUpdate ();
  
  //Return the subdivision cache (compressed param cache)
  INLINE const CATTessSubdivision1DCache* GetVertexSubdivisionCache () const;


public:

  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

protected:

  void Initialize(CATLONG32 iNbVertices);

protected:

  CATLONG32 _NbVertices;
  CATLONG32* _VertexIndices;
  double* _CrvParam;
  short* _QualPts;

  CATBoolean _SameSens;
    
  CATTessSubdivision1DCache*  _VertexSubdivisionCache;

};


INLINE CATLONG32 CATTessVertexIndexCache::GetNbVertices () const
{
  return _NbVertices;
}

INLINE CATLONG32* CATTessVertexIndexCache::GetVertexIndexBuffer () const
{
  return _VertexIndices;
}

INLINE double* CATTessVertexIndexCache::GetCrvParamBuffer () const
{
  return _CrvParam;
}

INLINE short* CATTessVertexIndexCache::GetQualPtsBuffer () const
{
  return _QualPts;
}

INLINE CATBoolean CATTessVertexIndexCache::GetSameSens () const
{
  return _SameSens;
}

INLINE CATLONG32* CATTessVertexIndexCache::GetVertexIndexBuffer_ForUpdate ()
{
  return _VertexIndices;
}

INLINE double* CATTessVertexIndexCache::GetCrvParamBuffer_ForUpdate ()
{
  return _CrvParam;
}

INLINE short* CATTessVertexIndexCache::GetQualPtsBuffer_ForUpdate ()
{
  return _QualPts;
}


INLINE const CATTessSubdivision1DCache* CATTessVertexIndexCache::GetVertexSubdivisionCache () const
{
  return _VertexSubdivisionCache;
}


#endif
