// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveUnstreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyCurveUnstreamer_H
#define CATIPolyCurveUnstreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolyCurve;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;


/**
 * Interface for unstreaming a CATIPolyCurve from a CATMathStream.
 */
class CATIPolyCurveUnstreamer
{

public:

  virtual ~CATIPolyCurveUnstreamer () {}

/** @name Options
    Modify how a CATIPolyCurve is unstreamed.
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
   * Unstreams a CATIPolyCurve from a CATMathStream.
   * @param iStream
   *   The stream.
   * @param oPolyCurve
   *   The CATIPolyCurve that is unstreamed.
   *   The returned instance must be released.
   * @param iRegistry
   *   A registry of streamers/unstreamers (layers).
   *   If the unstreamer is not avaiable in the registry, the object is not unstreamed.
   * @param ioStreamRecord
   *   An optional argument that records the unstreamed CATIPolyCurve.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATIPolyCurve*& oPolyCurve,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord* ioUnstreamRecord = 0) = 0;

protected:

  CATIPolyCurveUnstreamer () {}

};


#endif
