// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyhedralObjectsStreamer.h
//
//===================================================================
// September 2015 Creation: NDO
//===================================================================
#ifndef CATPolyhedralObjectsStreamer_H
#define CATPolyhedralObjectsStreamer_H

#include "PolyStream.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATPolyStreamOptions.h"

class CATIPolyObject;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;
class CATPolyBody;

class CATMathStream;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;


/*
 * Streamer for native polyhedral objects implementing the following interfaces:
 * <ul>
 *   <li> CATIPolyObject
 *   <li> CATIPolyPoint
 *   <li> CATIPolyCurve
 *   <li> CATIPolySurface
 * </ul>
 * This streamer only supports the implementations found in PolyhedralObjects.
 */
class ExportedByPolyStream CATPolyhedralObjectsStreamer
{

public :

  /**
   * @param iStreamRecord
   *   The optional records of the polyhedral objects that have been streamed.
   *   The streamer adds to the records each polyhedral object that it streams.
   */
  CATPolyhedralObjectsStreamer (CATMathStream& iStream, CATPolyStreamRecord* iStreamRecord = 0);

  ~CATPolyhedralObjectsStreamer ();

public:

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are streamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or 
   *   any valid combinations of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  inline void SetLayerFilter (unsigned int f);

public:
  /**
  * Sets the compression options.
  * By default, no compression is applied to streamed objects.
  */
  inline void SetCompressionFlags(CATPolyStreamOptions::Compression iCompressionFlags);

public:

  /**
   * Streams a polyhedral object (native to PolyhedralObjects) onto a CATMathStream.
   * The stream of a polyhedral object depending on a parent polyhedral object will 
   * trigger the stream of the parent if it has not been found in the records.
   * @param iPolyObject
   *   The object to stream.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Stream (const CATIPolyObject& iPolyObject);

  /**
   * Streams a polyhedral body (native to PolyhedralObjects) onto a CATMathStream.
   * Polyhedral objects associated to the CATPolyBody will be streamed
   * unless they have already been streamed.
   * @param iPolyBody
   *   The CATPolyBody to stream.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Stream (const CATPolyBody& iPolyBody);

public:

  /**
   * Pushes an object for streaming and returns its tag.
   * A unique tag is associated to an object (regardless of how many times
   * the object is pushed.)
   * NOT YET IMPLEMENTED.
   */
  HRESULT Push (const CATIPolyObject& iPolyObject, unsigned int& tag);

  /**
   * Streams all the polyhedral objects that have been pushed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   * NOT YET IMPLEMENTED.
   */
  HRESULT Stream ();

private:

  unsigned int _LayerFilter;
  CATBoolean _DeleteRecords;
  CATPolyStreamOptions::Compression _CompressionFlags;

  CATMathStream& _Stream;
  CATPolyStreamerRegistry& _StreamerRegistry;
  CATPolyStreamRecord* _Records;

};

inline void CATPolyhedralObjectsStreamer::SetLayerFilter (unsigned int f)
{
  // Force persistence of vertex and facets indices.
  _LayerFilter = f | CATPolyStreamOptions::eVertexIndices | CATPolyStreamOptions::eFacetIndices;

}

void CATPolyhedralObjectsStreamer::SetCompressionFlags(CATPolyStreamOptions::Compression iCompressionFlags)
{
  _CompressionFlags = iCompressionFlags;
}

#endif
