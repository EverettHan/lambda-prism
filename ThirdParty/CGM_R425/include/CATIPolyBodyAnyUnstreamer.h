// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyAnyUnstreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyBodyAnyUnstreamer_H
#define CATIPolyBodyAnyUnstreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;


/**
 * Interface for unstreaming a CATPolyBody from a CATMathStream.
 * @see CATCreatePolyBodyStreamer.h
 */
class CATIPolyBodyAnyUnstreamer
{

public:

  virtual ~CATIPolyBodyAnyUnstreamer () {}

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
  virtual void SetLayerFilter (unsigned int f) {}

/** @} */

public:

  /**
   * Unstreams a CATPolyBody from a CATMathStream.
   * @param iStream
   *   The stream.
   * @param oPolyBody
   *   The instance of the CATPolyBody constructed during unstreaming.
   *   This instance must be released.
   * @param ioUnstreamRecord
   *   An optional argument recording the geometrical entities (CATIPolyPoint's, CATIPolyCurve's and CATIPolySurface's)
   *   that are obtained from the stream.  If geometrical entities of the CATPolyBody are already recorded onto this 
   *   instance, then they will not be unstreamed.
   * @param iRegistry
   *   An optional registry providing the streaming functions for various polyhedral layers.
   *   Custom applicative layers can be unstreamed via a custom unstreaming function.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    CATPolyUnstreamRecord* ioUnstreamRecord = 0,
    const CATPolyStreamerRegistry* iRegistry = 0) = 0;

protected:

  CATIPolyBodyAnyUnstreamer () {}

};


#endif
