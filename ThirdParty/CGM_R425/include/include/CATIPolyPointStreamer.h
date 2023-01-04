// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPointStreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyPointStreamer_H
#define CATIPolyPointStreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolyPoint;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;


/**
 * Interface for streaming a CATIPolyPoint on a CATMathStream.
 */
class CATIPolyPointStreamer
{

public:

  virtual ~CATIPolyPointStreamer () {}

public:

  /**
   * Set the compression mode.
   * The default is medium compression.
   * @param c
   *   The compression mode.  (@see CATPolyStreamOptions::Compression.)
   */
  virtual void SetCompression (CATPolyStreamOptions::Compression c) {}

public:

  /**
   * Streams a CATIPolyPoint onto a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iPolyPoint
   *   The CATIPolyPoint to stream.
   * @param ioStreamRecord
   *   An optional argument that records the streamed CATIPolyPoint.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Stream (CATMathStream& iStream, const CATIPolyPoint& iPolyPoint,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord* ioStreamRecord = 0) = 0;

protected:

  CATIPolyPointStreamer () {}

};

#endif
