// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessFaceDataCache.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef TessFaceDataCache_H
#define TessFaceDataCache_H

#include "CATMathInline.h"
#include "TessCacheObjects.h"
#include "CATTessDataCache.h"
#include "CATDataType.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATCGMMemoryManager.h"

class CATTessVertexPositionCache;
class CATTessVertexPositionCacheD;
class CATTessVertexVectorCache;
class CATTessVertexUVParamCache;
class CATTessTriangleStripFanCache;
class CATTessVertexIndexCache;
class CATTessSubdivision2DCache;
class CATEdge;
class CATMathPolyBuffers;


/*
* This is a class encapsulating the discrete tessellation data for CATFace's.
* Instances of this class are ref-counted.  
* Instances should only be allocated dynamically and released when no longer needed.
*/
class ExportedByTessCacheObjects CATTessFaceDataCache : public CATTessDataCache
{

public:

  /*
   * Construction of the cache containing the various buffers for the tessellation data
   * requires the number of edges adjacent to the face.
   */
  static CATTessFaceDataCache* New(CATLONG32 iNbEdges);

public:

  //
  // Allocation methods to be called before populating the various buffers with the tessellation data.
  //
  /*
   * Reserve memory to store different buffers (geometry : position, normal, UV and topology: triangles, strips, fans).
	 * ReserveGeometryBuffers should called first and ReserveTopologyBuffers further, these methods should only be called once,
	 * then GetPolyBuffers can be called providing access to fill in different buffers.
   */
  HRESULT ReserveGeometryBuffers (CATLONG32 iNbVertices, int iPositionPrecision = 1 /* 0: float - 1: double */, CATBoolean iHasUniqueVertexNormal = FALSE, CATCGMMemoryManager* iMemoryManager = 0);
  HRESULT ReserveTopologyBuffers (CATLONG32 iNbIsolatedTriangles,	CATLONG32 iNbStrips, CATLONG32 iNbStripIndices,	CATLONG32 iNbFans, CATLONG32 iNbFanIndices);
  HRESULT ReserveVertexLineBuffers (CATLONG32 iNbVertexLines, CATLONG32 iNbVertexLineIndices);
  INLINE CATMathPolyBuffers* GetPolyBuffers_ForUpdate ();
  INLINE const CATMathPolyBuffers* GetPolyBuffers () const;
	//
  // Methods providing access to the various buffers containing the tessellation data.
  // 
  // Return the vertex position cache.
  INLINE const CATTessVertexPositionCache* GetVertexPositionCache () const;
  INLINE const CATTessVertexPositionCacheD* GetVertexPositionCacheD () const;

  // Return the vertex normal cache.
  INLINE const CATTessVertexVectorCache* GetVertexNormalCache () const;

  // Return the vertex UV-param cache.
  INLINE const CATTessVertexUVParamCache* GetVertexUVParamCache () const;

  // Return the triangle, strip and fan cache.
  INLINE const CATTessTriangleStripFanCache* GetTriangleStripFanCache () const;

  // Return the vertex index cache associated to a CATEdge.
  const CATTessVertexIndexCache* GetVertexIndexCache (CATEdge& iEdge) const;

  // Return the vertex index cache associated to a CATEdge.
  const CATTessVertexIndexCache* GetVertexIndexCache (CATULONG32 iEdgeTag) const;

  //Return subdiv cache
  INLINE const CATTessSubdivision2DCache* GetSubdivisionCache() const;

  /*
   * For each CATEdge adjacent to the CATFace, allocate memory to store the vertex indices corresponding 
   * to the tessellated edge.
   * This method should only be called once for each edge before filling in the index buffers.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexIndexCache* NewVertexIndexCache (CATEdge& iEdge, int iNbVertices, CATBoolean iSameSens);

  /*
   * Allocate memory to store the face subdivision (compact)
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   * Compressed subdivision
   */
  CATTessSubdivision2DCache* NewSubdivisionCache (unsigned int iHorizSubdivBufferSize, unsigned int iVertSubdivBufferSize);

  /*
	 * Deprecated methods. Do not call.
   * Allocate memory to store the vertex positions in float.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexPositionCache* NewVertexPositionCache (CATLONG32 iNbVertices);

  /*
	 * Deprecated methods. Do not call.
   * Allocate memory to store the vertex positions in double.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexPositionCacheD* NewVertexPositionCacheD (CATLONG32 iNbVertices);

  /*
	 * Deprecated methods. Do not call.
   * Allocate memory to store the vertex normals.
   * This method should only be called once before filling in the buffer.
   * The number of normals should be equal to the number of vertices or one if the CATFace refers 
   * to a planar surface.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexVectorCache* NewVertexNormalCache (CATLONG32 iNbNormals);

  /*
	 * Deprecated methods. Do not call.
   * Allocate memory to store the vertex UV parameters.
   * This method should only be called once before filling in the buffer.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessVertexUVParamCache* NewVertexUVParamCache (CATLONG32 iNbVertices);

  /*
	 * Deprecated methods. Do not call.
   * Allocate memory to store the triangles, strips and fans.
   * This method should only be called once before filling in the various buffers.
   * Lifecycle of returned object is managed by this class not the caller!
   */
  CATTessTriangleStripFanCache* NewTriangleStripFanCache (CATLONG32 iNbIsolatedTriangles,
                                                       CATLONG32 iNbStrips, CATLONG32 iNbStripIndices,
                                                       CATLONG32 iNbFans, CATLONG32 iNbFanIndices);
public:

  virtual void Stream(CATCGMStream& iStream) const;

  virtual void UnStream(CATCGMStream& iStream);

protected:

  CATTessFaceDataCache (CATLONG32 iNbEdges = 0);

  virtual ~CATTessFaceDataCache ();
  
  void Initialize(CATLONG32 iNbEdges);

  CATTessVertexIndexCache* NewVertexIndexCache (CATULONG32 iEdgeTag, int iNbVertices, CATBoolean iSameSens);

  static CATTessFaceDataCache* New();

private:

  // Note to future developer(s): If data members in this class are changed/added/removed, in future,
  // then do not forget to update the Stream/UnStream code appropriately.
  CATMathPolyBuffers * _PolyBuffers;
  
	CATTessVertexPositionCache*    _VertexPositionCache;
  CATTessVertexPositionCacheD*   _VertexPositionCacheD;
  CATTessVertexVectorCache*      _VertexNormalCache;
  CATTessVertexUVParamCache*     _VertexUVParamCache;
  CATTessTriangleStripFanCache*  _TriangleStripFanCache;
  CATTessSubdivision2DCache* _SubdivisionCache;

  // Hash table for map of CATEdge to TestVertexIndexCache.
  CATULONGPTR* _Buckets;         // Address of the allocated memory (size is 4 * _NbEdges).
  CATULONGPTR* _FirstFreeBucket; // Address of the first free bucket.

  CATLONG32 _NbEdges; 

private:

  INLINE CATLONG32 ComputeHashNumber (CATULONGPTR iEdgeTag) const;

private:

  friend class CATTessFaceDataCacheAttribute;

};


INLINE const CATTessVertexPositionCache* CATTessFaceDataCache::GetVertexPositionCache () const
{
  return _VertexPositionCache;
}

INLINE const CATTessVertexPositionCacheD* CATTessFaceDataCache::GetVertexPositionCacheD () const
{
  return _VertexPositionCacheD;
}

INLINE const CATTessVertexVectorCache* CATTessFaceDataCache::GetVertexNormalCache () const
{
  return _VertexNormalCache;
}

INLINE const CATTessVertexUVParamCache* CATTessFaceDataCache::GetVertexUVParamCache () const
{
  return _VertexUVParamCache;
}

INLINE const CATTessTriangleStripFanCache* CATTessFaceDataCache::GetTriangleStripFanCache () const
{
  return _TriangleStripFanCache;
}


INLINE CATLONG32 CATTessFaceDataCache::ComputeHashNumber (CATULONGPTR iEdgeTag) const
{
  return (CATLONG32) (iEdgeTag % _NbEdges);
}
  
INLINE const CATTessSubdivision2DCache* CATTessFaceDataCache::GetSubdivisionCache() const
{
  return _SubdivisionCache;
}

INLINE CATMathPolyBuffers* CATTessFaceDataCache::GetPolyBuffers_ForUpdate ()
{
  return _PolyBuffers;
}

INLINE const CATMathPolyBuffers* CATTessFaceDataCache::GetPolyBuffers () const
{
  return _PolyBuffers;
}

#endif // !TessFaceDataCache_H
