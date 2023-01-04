// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyStreamer.h
//
//===================================================================
// February 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyBodyStreamer_H
#define CATIPolyBodyStreamer_H

#include "PolyhedralModel.h"
#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;

class CATIPolySurfaceStreamer;
class CATIPolyCurveStreamer;
class CATIPolyPointStreamer;


/**
 * Interface for streaming a CATPolyBody on a CATMathStream.
 * @see CATIPolyBodyUnstreamer
 * @see CATCreatePolyBodyStreamer.h
 */
class ExportedByPolyhedralModel CATIPolyBodyStreamer
{

public:

  virtual ~CATIPolyBodyStreamer () {}

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
  virtual void SetCompression (CATPolyStreamOptions::Compression c) = 0;

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are streamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or any valid combinations
   *   of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  virtual void SetLayerFilter (unsigned int f) = 0;

/** @} */

public:

/** @name Reserved Services
    @{ */

  /**
   * @nodoc
   * Returns the name of the library where the implementation of the polyhedral stream is located.
   * @return
   *   The name of the library.
   */
  virtual const char* GetLibraryName () const = 0;

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
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATPolyStreamRecord* ioStreamRecord = 0) = 0;

  virtual HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord* ioStreamRecord);

  /**
   * Streams a CATPolyBody onto a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iPolyBody
   *   The CATPolyBody to stream.
   * @param iSurfaceStreamer
   *   An optional streamer of CATIPolySurface objects that overrides the default streamer (if not null.)
   * @param iCurveStreamer
   *   An optional streamer of CATIPolyCurve objects that overrides the default streamer (if not null.)
   * @param iPointStreamer
   *   An optional streamer of CATIPolyPoint objects that overrides the default streamer (if not null.)
   * @param ioStreamRecord
   *   An optional argument recording the geometrical entities (<code>CATIPolyPoint</code>'s, 
   *   <code>CATIPolyCurve</code>'s and <code>CATIPolySurface</code>'s)
   *   that are sent to the stream.  Geometrical entities from the CATPolyBody that are already recorded 
   *   will not be streamed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody, 
                          CATIPolySurfaceStreamer* iSurfaceStreamer, CATIPolyCurveStreamer* iCurveStreamer, CATIPolyPointStreamer* iPointStreamer,
                          CATPolyStreamRecord* ioStreamRecord = 0);

protected:

  CATIPolyBodyStreamer () {}

};

#endif
