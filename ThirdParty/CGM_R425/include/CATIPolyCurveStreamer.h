// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveStreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyCurveStreamer_H
#define CATIPolyCurveStreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolyCurve;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;


/**
 * Interface for streaming a CATIPolyCurve on a CATMathStream.
 */
class CATIPolyCurveStreamer
{

public:

  virtual ~CATIPolyCurveStreamer () {}

public:

/** @name Options 
    Modify how the CATIPolyCurve is streamed.
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
     * Streams a CATIPolyCurve onto a CATMathStream.
     * @param iStream
     *   The stream.
     * @param iPolyCurve
     *   The CATIPolyCurve to stream.
     * @param ioStreamRecord
     *   An optional argument that records the streamed CATIPolyCurve.
     * @return
     * <ul>
     *   <li> <code> S_OK </code> if the entity has been successfully streamed.
     *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
     *   <li> <code> E_FAIL </code> or any other error if an error occurs.
     * </ul>
     */
  virtual HRESULT Stream (CATMathStream& iStream, const CATIPolyCurve& iPolyCurve,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord* ioStreamRecord = 0) = 0;

protected:

  CATIPolyCurveStreamer () {}

};

#endif
