//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessEdgeDataCache
//
//=============================================================================
// 2009-07-29 MPX: New
// 2011-11-28 ZFI: Add Subdivision Cache
//=============================================================================

#ifndef TessEdgeDataCache_H
#define TessEdgeDataCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATTessDataCache.h"
#include "CATCGMMemoryManager.h"

class CATTessVertexPositionCache;
class CATTessVertexPositionCacheD;
class CATTessVertexVectorCache;
class CATTessVertexWParamCache;
class CATTessSubdivision1DCache;
class CATMathPolyBuffers;

class ExportedByTessCacheObjects CATTessEdgeDataCache : public CATTessDataCache
{

public:

  /*
   * Construction of the cache containing the various buffers for the tessellation data
   */
  static CATTessEdgeDataCache* New();


public:

  /*
   * Reserve memory to store different buffers (geometry : position, tangent, W), should only be called once.
	 * then GetPolyBuffers can be called providing access to fill in different buffers.
   */
  HRESULT ReserveGeometryBuffers (CATLONG32 iNbVertices, int iPositionPrecision = 1 /* 0: float - 1: double */, CATBoolean iHasUniqueVertexTangent = FALSE, CATCGMMemoryManager* iMemoryManager = 0);
  INLINE CATMathPolyBuffers* GetPolyBuffers_ForUpdate ();
  INLINE const CATMathPolyBuffers* GetPolyBuffers () const;

  //
  // Allocation methods to be called before populating the various buffers with the tessellation data.
  //

  /*
   * Allocate memory to store the vertex positions in float.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexPositionCache* NewVertexPositionCache (unsigned int iNbVertices);

  /*
   * Allocate memory to store the vertex positions in double.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexPositionCacheD* NewVertexPositionCacheD (unsigned int iNbVertices);

  /*
   * Allocate memory to store the vertex tangents.
   * This method should only be called once before filling in the buffer.
   * The number of normals should be equal to the number of vertices or one if the CATEdge refers 
   * to a linear edge.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexVectorCache* NewVertexTangentCache (unsigned int iNbTangents);

  /*
   * Allocate memory to store the vertex W parameters.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexWParamCache* NewVertexWParamCache (unsigned int iNbVertices);
  
  /*
   * Allocate memory to store the vertex subdivision parameters (compact form of parameters)
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   * Compressed param Cache
   */
  CATTessSubdivision1DCache* NewVertexSubdivisionCache (unsigned int iSubdivisionBufferSize);


public:

  //
  // Methods providing access to the various buffers containing the tessellation data.
  // 

  // Return the vertex position cache.
  INLINE const CATTessVertexPositionCache* GetVertexPositionCache () const;
  INLINE const CATTessVertexPositionCacheD* GetVertexPositionCacheD () const;

  // Return the vertex normal cache.
  INLINE const CATTessVertexVectorCache* GetVertexTangentCache () const;

  // Return the vertex UV-param cache.
  INLINE const CATTessVertexWParamCache* GetVertexWParamCache () const;

  //Return the subdivision cache (compressed param cache)
  INLINE const CATTessSubdivision1DCache* GetVertexSubdivisionCache () const;

protected:

  CATTessEdgeDataCache();

  virtual ~CATTessEdgeDataCache();

  virtual void Stream(CATCGMStream& iStream) const;

  virtual void UnStream(CATCGMStream& iStream);

private:

  // Note to future developer(s): If data members in this class are changed/added/removed, in future,
  // then do not forget to update the Stream/UnStream code appropriately.
  CATMathPolyBuffers * _PolyBuffers;

  CATTessVertexPositionCache*    _VertexPositionCache;
  CATTessVertexPositionCacheD*   _VertexPositionCacheD;
  CATTessVertexVectorCache*      _VertexTangentCache;
  CATTessVertexWParamCache*     _VertexWParamCache;
  CATTessSubdivision1DCache*  _VertexSubdivisionCache;

private:

  friend class CATTessEdgeDataCacheAttribute;

};

INLINE const CATTessVertexPositionCache* CATTessEdgeDataCache::GetVertexPositionCache () const
{
  return _VertexPositionCache;
}

INLINE const CATTessVertexPositionCacheD* CATTessEdgeDataCache::GetVertexPositionCacheD () const
{
  return _VertexPositionCacheD;
}

INLINE const CATTessVertexVectorCache* CATTessEdgeDataCache::GetVertexTangentCache () const
{
  return _VertexTangentCache;
}

INLINE const CATTessVertexWParamCache* CATTessEdgeDataCache::GetVertexWParamCache () const
{
  return _VertexWParamCache;
}

INLINE const CATTessSubdivision1DCache* CATTessEdgeDataCache::GetVertexSubdivisionCache () const
{
  return _VertexSubdivisionCache;
}

INLINE CATMathPolyBuffers* CATTessEdgeDataCache::GetPolyBuffers_ForUpdate ()
{
  return _PolyBuffers;
}

INLINE const CATMathPolyBuffers* CATTessEdgeDataCache::GetPolyBuffers () const
{
  return _PolyBuffers;
}

#endif // !TessEdgeDataCache_H

