// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyAnyStreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyBodyAnyStreamer_H
#define CATIPolyBodyAnyStreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;


/**
 * Interface for streaming a CATPolyBody on a CATMathStream.
 * @see CATCreatePolyBodyStreamer.h
 */
class CATIPolyBodyAnyStreamer
{

public:

  virtual ~CATIPolyBodyAnyStreamer () {}

public:

/** @name Options 
    Modify how the CATPolyBody is streamed.
    @{ */

  /**
   * Sets the compression mode.
   * @param c
   *   The compression mode.
   * @see CATPolyStreamOptions::Compression
   */
  virtual void SetCompression (CATPolyStreamOptions::Compression c) {}

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are streamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or any valid combinations
   *   of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  virtual void SetLayerFilter (unsigned int f) {}

  /**
   * Defines how the polyhedral data will be streamed.
   *
   * By default, the data are streamed in a native mode; this means that the types of the objects are 
   * preserved by the streaming operation.  To stream in a native mode, a streamer supporting the original
   * data types must be available.  For example, to stream an instance of an adapter on tessellated data, an 
   * implementation of a streamer for this adapter is needed.  The streamer used for this purpose is usually 
   * in the same framework (component) as where the data structures are implemented.
   *
   * The data can also be streamed in a <code>PolyhedralObjects</code> mode. In this mode, the entities are 
   * streamed as if they were implemented as polyhedral objects.  The streamer used for this purpose is 
   * found in the <code>PolyhedralObjects</code> framework.
   *
   * @param m
   *   The streaming mode.
   * @see CATPolyStreamOptions::Mode
   */
  virtual void SetStreamingMode (CATPolyStreamOptions::StreamingMode m) {}

/** @} */

public:

  /**
   * Streams a CATPolyBody onto a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iPolyBody
   *   The CATPolyBody to stream.
   * @param ioStreamRecord
   *   An optional argument recording the geometrical entities (<code>CATIPolyPoint</code>'s, 
   *   <code>CATIPolyCurve</code>'s and <code>CATIPolySurface</code>'s)
   *   that are sent to the stream.  Geometrical entities from the CATPolyBody that are already recorded 
   *   will not be streamed.
   * @param iRegistry
   *   An optional registry providing the streaming functions for various polyhedral layers.
   *   Custom applicative layers can be streamed via a custom streaming function.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATPolyStreamRecord* ioStreamRecord = 0,
    const CATPolyStreamerRegistry* iRegistry = 0) = 0;

protected:

  CATIPolyBodyAnyStreamer () {}

};

#endif
