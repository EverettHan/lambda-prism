// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceStreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceStreamer_H
#define CATIPolySurfaceStreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolySurface;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;


/**
 * Interface for streaming a CATIPolySurface on a CATMathStream.
 */
class CATIPolySurfaceStreamer
{

public:

  virtual ~CATIPolySurfaceStreamer () {}

public:

/** @name Options 
    Modify how the CATIPolySurface is streamed.
    @{ */

  /**
   * Sets the compression mode.
   * @param c
   *   The compression mode.
   * @see CATPolyStreamOptions::Compression.
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

/** @} */

public:

  /**
   * Streams a CATIPolySurface onto a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iPolySurface
   *   The CATIPolySurface to stream.
   * @param iRegistry
   *   A registry of streamers/unstreamers (layers).  
   *   If the streamer is not avaiable in the registry, the object is not streamed.
   * @param ioStreamRecord
   *   An optional argument that records the streamed CATIPolySurface.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Stream (CATMathStream& iStream, const CATIPolySurface& iPolySurface,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord* ioStreamRecord = 0) = 0;

protected:

  CATIPolySurfaceStreamer () {}

};

#endif
