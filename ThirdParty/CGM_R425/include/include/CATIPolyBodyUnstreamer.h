// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyUnstreamer.h
//
//===================================================================
// February 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyBodyUnstreamer_H
#define CATIPolyBodyUnstreamer_H

#include "PolyhedralModel.h"
#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;

class CATIPolySurfaceUnstreamer;
class CATIPolyCurveUnstreamer;
class CATIPolyPointUnstreamer;


/**
 * Interface for unstreaming a CATPolyBody from a CATMathStream.
 * @see CATIPolyBodyStreamer
 * @see CATCreatePolyBodyStreamer.h
 */
class ExportedByPolyhedralModel CATIPolyBodyUnstreamer
{

public:

  virtual ~CATIPolyBodyUnstreamer () {}

public:

/** @name Options
    Modify how a CATPolyBody is unstreamed.
    @{ */

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are unstreamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or any valid combinations
   *   of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  virtual void SetLayerFilter (unsigned int f) = 0;

/** @} */

public:

  /**
   * Unstreams a CATPolyBody from a CATMathStream.
   * @param iStream
   *   The stream.
   * @param oPolyBody
   *   The instance of the CATPolyBody constructed during unstreaming.
   *   This instance must be deleted.
   * @param ioUnstreamRecord
   *   An optional argument recording the geometrical entities (CATIPolyPoint's, CATIPolyCurve's and CATIPolySurface's)
   *   that are obtained from the stream.  If geometrical entities of the CATPolyBody are already recorded onto this 
   *   instance, then they will not be unstreamed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
                            CATPolyUnstreamRecord* ioUnstreamRecord = 0) = 0;

  virtual HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord* ioUnstreamRecord);

  /**
   * Streams a CATPolyBody onto a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iPolyBody
   *   The CATPolyBody to stream.
   * @param iSurfaceUnstreamer
   *   An optional unstreamer of CATIPolySurface objects that overrides the default unstreamer (if not null.)
   * @param iCurveUnstreamer
   *   An optional unstreamer of CATIPolyCurve objects that overrides the default unstreamer (if not null.)
   * @param iPointStreamer
   *   An optional unstreamer of CATIPolyPoint objects that overrides the default unstreamer (if not null.)
   * @param ioUnstreamRecord
   *   An optional argument recording the geometrical entities (CATIPolyPoint's, CATIPolyCurve's and CATIPolySurface's)
   *   that are obtained from the stream.  If geometrical entities of the CATPolyBody are already recorded onto this 
   *   instance, then they will not be unstreamed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody, 
                            CATIPolySurfaceUnstreamer* iSurfaceUnstreamer, CATIPolyCurveUnstreamer* iCurveUnstreamer, CATIPolyPointUnstreamer* iPointUnstreamer,
                            CATPolyUnstreamRecord* ioUnstreamRecord = 0);

protected:

  CATIPolyBodyUnstreamer () {}

};


#endif
