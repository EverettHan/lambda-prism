// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceUnstreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceUnstreamer_H
#define CATIPolySurfaceUnstreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolySurface;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;


/**
 * Interface for unstreaming a CATIPolySurface from a CATMathStream.
 */
class CATIPolySurfaceUnstreamer
{

public:

  virtual ~CATIPolySurfaceUnstreamer () {}

public:

/** @name Options
    Modify how a CATIPolySurface is unstreamed.
    @{ */

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are unstreamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or any valid combinations
   *   of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  virtual void SetLayerFilter (unsigned int f) {}

/** @} */

public:

  /**
   * Unstreams a CATIPolySurface from a CATMathStream.
   * @param iStream
   *   The stream.
   * @param iRegistry
   *   A registry of streamers/unstreamers (layers).
   *   If the unstreamer is not avaiable in the registry, the object is not unstreamed.
   * @param oPolySurface
   *   The CATIPolySurface that is unstreamed.
   *   The returned instance must be released.
   * @param ioStreamRecord
   *   An optional argument that records the unstreamed CATIPolySurface.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATIPolySurface*& oPolySurface,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord* ioUnstreamRecord = 0) = 0;

protected:

  CATIPolySurfaceUnstreamer () {}

};


#endif
